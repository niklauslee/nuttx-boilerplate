/****************************************************************************
 * examples/hello/hello_main.c
 *
 *   Copyright (C) 2008, 2011-2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <fcntl.h>

#include <sys/boardctl.h>

#ifdef CONFIG_CDCACM
#  include <nuttx/usb/cdcacm.h>
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

 static void nsh_configstdio(int fd)
 {
   /* Make sure the stdin, stdout, and stderr are closed */

   (void)fclose(stdin);
   (void)fclose(stdout);
   (void)fclose(stderr);

   /* Dup the fd to create standard fd 0-2 */

   (void)dup2(fd, 0);
   (void)dup2(fd, 1);
   (void)dup2(fd, 2);

   /* fdopen to get the stdin, stdout and stderr streams. The following logic depends
    * on the fact that the library layer will allocate FILEs in order.  And since
    * we closed stdin, stdout, and stderr above, that is what we should get.
    *
    * fd = 0 is stdin  (read-only)
    * fd = 1 is stdout (write-only, append)
    * fd = 2 is stderr (write-only, append)
    */

   (void)fdopen(0, "r");
   (void)fdopen(1, "a");
   (void)fdopen(2, "a");
 }

static int nsh_nullstdio(void)
{
 int fd;

 /* Open /dev/null for read/write access */

 fd = open("/dev/null", O_RDWR);
 if (fd >= 0)
   {
     /* Configure standard I/O to use /dev/null */

     nsh_configstdio(fd);

     /* We can close the original file descriptor now (unless it was one of
      * 0-2)
      */

     if (fd > 2)
      {
         close(fd);
      }

     return OK;
   }

 return fd;
}

int board_app_initialize(uintptr_t arg)
{
#ifndef CONFIG_BOARD_INITIALIZE
  /* Perform board-specific initialization */

  return stm32_bringup();
#else
  return OK;
#endif
}

#if defined(CONFIG_CDCACM)
#  define CONFIG_NSH_USBCONDEV "/dev/ttyACM0"
#elif defined(CONFIG_PL2303)
#  define CONFIG_NSH_USBCONDEV "/dev/ttyUSB0"
#else
#  define CONFIG_NSH_USBCONDEV "/dev/console"
#endif

static int nsh_waitusbready(void)
{
  char inch;
  ssize_t nbytes;
  int nlc;
  int fd;

  /* Don't start the NSH console until the console device is ready.  Chances
   * are, we get here with no functional console.  The USB console will not
   * be available until the device is connected to the host and until the
   * host-side application opens the connection.
   */

restart:

  /* Open the USB serial device for read/write access */

  do
    {
      /* Try to open the console */

      fd = open(CONFIG_NSH_USBCONDEV, O_RDWR);
      if (fd < 0)
        {
          /* ENOTCONN means that the USB device is not yet connected. Anything
           * else is bad.
           */

          DEBUGASSERT(errno == ENOTCONN);

          /* Sleep a bit and try again */

          sleep(2);
        }
    }
  while (fd < 0);

  /* Now wait until we successfully read a carriage return a few times.
   * That is a sure way of know that there is something at the other end of
   * the USB serial connection that is ready to talk with us.  The user needs
   * to hit ENTER a few times to get things started.
   */

  nlc = 0;
  do
    {
      /* Read one byte */

      inch = 0;
      nbytes = read(fd, &inch, 1);

      /* Is it a carriage return (or maybe a newline)? */

      if (nbytes == 1 && (inch == '\n' || inch == '\r'))
        {
          /* Yes.. increment the count */

          nlc++;
        }
      else
        {
          /* No.. Reset the count.  We need to see 3 in a row to continue. */

          nlc = 0;

          /* If a read error occurred (nbytes < 0) or an end-of-file was
           * encountered (nbytes == 0), then close the driver and start
           * over.
           */

          if (nbytes <= 0)
            {
              (void)close(fd);
              goto restart;
            }
        }
    }
  while (nlc < 3);

  /* Configure standard I/O */

  nsh_configstdio(fd);

  /* We can close the original file descriptor now (unless it was one of 0-2) */

  if (fd > 2)
    {
      close(fd);
    }

  return OK;
}

/****************************************************************************
 * hello_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int kameleon_main(int argc, char *argv[])
#endif
{
  // FAR struct console_stdio_s *pstate = nsh_newconsole();
  struct boardioc_usbdev_ctrl_s ctrl;
  FAR void *handle;
  int ret;

  /* Initialize the USB serial driver */
#if defined(CONFIG_PL2303) || defined(CONFIG_CDCACM)

#ifdef CONFIG_CDCACM
  ctrl.usbdev   = BOARDIOC_USBDEV_CDCACM;
  ctrl.action   = BOARDIOC_USBDEV_CONNECT;
  ctrl.instance = 0;
  ctrl.handle   = &handle;
#endif

  ret = boardctl(BOARDIOC_USBDEV_CONTROL, (uintptr_t)&ctrl);
  UNUSED(ret); /* Eliminate warning if not used */
  DEBUGASSERT(ret == OK);
#endif

  /* Configure to use /dev/null if we do not have a valid console. */

#ifndef CONFIG_DEV_CONSOLE
  (void)nsh_nullstdio();
#endif

  ret = nsh_waitusbready();
  printf("Hello, World!!\n");
  return 0;
}
