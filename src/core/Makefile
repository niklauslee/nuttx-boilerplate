############################################################################
# apps/examples/hello/Makefile
#
#   Copyright (C) 2008, 2010-2013 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

-include $(TOPDIR)/Make.defs

CONFIG_KAMELEON_PRIORITY ?= SCHED_PRIORITY_DEFAULT
CONFIG_KAMELEON_STACKSIZE ?= 16384

APPNAME = kameleon
PRIORITY = $(CONFIG_KAMELEON_PRIORITY)
STACKSIZE = $(CONFIG_KAMELEON_STACKSIZE)

# TUV_PLATFORM=arm-nuttx
# TUV_BOARD=stm32f4dis
# TUV_SYSTEMROOT=$(TOPDIR)

# LIBTUV_PATH = ../../deps/libtuv

# CFLAGS += -D__NUTTX__ \
          -I$(LIBTUV_PATH)/include \
          -I$(LIBTUV_PATH)/src \
          -I$(LIBTUV_PATH)/src/unix

# ASRCS =
# CSRCS = $(LIBTUV_PATH)/include/uv-unix.h \
        $(LIBTUV_PATH)/include/uv-linux.h \
        $(LIBTUV_PATH)/src/inet.c \
        $(LIBTUV_PATH)/src/threadpool.c \
        $(LIBTUV_PATH)/src/uv-common.c \
        $(LIBTUV_PATH)/src/tuv_debuglog.c \
        $(LIBTUV_PATH)/src/unix/async.c \
        $(LIBTUV_PATH)/src/unix/atomic-ops.h \
        $(LIBTUV_PATH)/src/unix/core.c \
        $(LIBTUV_PATH)/src/unix/fs.c \
        $(LIBTUV_PATH)/src/unix/getaddrinfo.c \
        $(LIBTUV_PATH)/src/unix/internal.h \
        $(LIBTUV_PATH)/src/unix/loop.c \
        $(LIBTUV_PATH)/src/unix/loop-watcher.c \
        $(LIBTUV_PATH)/src/unix/poll.c \
        $(LIBTUV_PATH)/src/unix/process.c \
        $(LIBTUV_PATH)/src/unix/spinlock.h \
        $(LIBTUV_PATH)/src/unix/stream.c \
        $(LIBTUV_PATH)/src/unix/tcp.c \
        $(LIBTUV_PATH)/src/unix/thread.c \
        $(LIBTUV_PATH)/src/unix/timer.c \
        $(LIBTUV_PATH)/src/unix/tty.c \
        $(LIBTUV_PATH)/src/unix/udp.c \
        $(LIBTUV_PATH)/src/unix/nuttx.c

ASRCS=
CSRCS=
MAINSRC = kameleon_main.c

CONFIG_KAMELEON_PROGNAME ?= kameleon$(EXEEXT)
PROGNAME = $(CONFIG_KAMELEON_PROGNAME)

include $(APPDIR)/Application.mk
