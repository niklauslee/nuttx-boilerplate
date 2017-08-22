# Overview

* Board: STM32F411E-Discovery
* Use USB CDC/ACM for console (not USART2)

# Development settings

Required packages:
* __GCC ARM__
* __CMake__ : https://cmake.org/
* __kconfig-frontends__

```sh
$ git clone https://github.com/jameswalmsley/kconfig-frontends.git
$ cd kconfig-frontends
$ ./bootstrap
$ ./configure --enable-mconf
$ make
$ sudo make install
$ sudo ldconfig
```

* __St-Util__ for Flash

# Build

1. Checkout repository

```sh
$ git clone https://github.com/niklauslee/kameleon-firmware.git
$ cd kameleon-firmware
$ git submodule init
$ git submodule update
```

2. Configure NuttX

```sh
$ cd kameleon-firmware/deps/nuttx/tools
$ ./configure.sh -a ../../src stm32f411e-disco/nsh
$ cd ..
```
`.config` and `Make.defs` are created at `kameleon-firmware/deps/nuttx`

3. Change Configuration Variables

```sh
# at kameleon-firmware/deps/nuttx
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
