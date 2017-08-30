# Overview

* Board: STM32F411E-Discovery
* Use USB CDC/ACM for console (not USART2)

# Development settings

Required packages:
* __GCC ARM__
* __cmake__ : https://cmake.org/
* __kconfig-frontends__ : https://github.com/PX4/NuttX/tree/master/misc/tools
* __st-link tool__ : https://github.com/texane/stlink

__for Linux__:
https://github.com/niklauslee/kameleon-firmware/wiki/Ubuntu-Linux

__for Atom Editor__: https://github.com/niklauslee/kameleon-firmware/wiki/Development-using-Atom

# Build

1. Checkout repository

```sh
$ git clone https://github.com/niklauslee/nuttx-boilerplate.git
$ cd nuttx-boilerplate
$ git submodule init
$ git submodule update
```

2. Configure NuttX

```sh
$ cd nuttx-boilerplate/deps/nuttx/tools
$ ./configure.sh -a ../../src stm32f411e-disco/nsh
$ cd ..
```
`.config` and `Make.defs` are created at `nuttx-boilerplate/deps/nuttx`

3. Change Configuration Variables

```sh
# at nuttx-boilerplate/deps/nuttx
$ make menuconfig
```

* `System Type`
  * `STM32 Peripheral Support`
    * `OTG FS` : __Check__
* `Board Selection`
  * `Enable boardctl() interface` : __Check__
    * `Enable USB device controls` : __Check__
* `RTOS Features`
  * `Tasks and Scheduling`
    * `Application entry point` : __kameleon_main__
  * `Files and I/O`
    * `Enable /dev/console` : __Uncheck__
* `Device Drivers`
  * `Serial Driver Support`
    * `Serial console` : __No serial console__
  * `USB Device Driver Support` : __Check__
    * `USB Modem (CDC/ACM) support` : __Check__
      * `CDC/ACM console device` : __Check__
      * `Receive buffer size` : __256__
      * `Transmit buffer size` : __256__
* `Binary Loader`
  * `Disable BINFMT support` : __Check__
* `Library Routines`
  * `Have C++ compiler` : __Uncheck__

3. Make

```sh
$ make
```

4. Flash

```sh
$ st-flash write nuttx.bin 0x8000000
```

5. Terminal

```sh
# Press RESET button on board
$ screen /dev/tty.usbmodem1 115200 # macOS
# or
$ screen /dev/ttyACM0 115200 # Linux

# Hit return several times,

# then "Hello, World" will be printed.
```
