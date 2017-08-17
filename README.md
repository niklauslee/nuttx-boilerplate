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
$ ./configure.sh -a ../../src nucleo-f4x1re/f411-nsh
$ cd .. # at kameleon-firmware/deps/nuttx
$ make menuconfig
```

3. Change Configuration Variables

* `RTOS Features`
  * `Tasks and Scheduling`
    * `Application entry point` : __kameleon_main__
* `Binary Loader`
  * `Disable BINFMT support` : __Check__
* `Library Routines`
  * `Have C++ compiler` : __Uncheck__
* `Application Configuration`
  * `Platform-specific Support`
    * `Have C++ initialization` : __Uncheck__

3. Make

```sh
$ make
```

4. Flash

```sh
$ st-flash write nuttx.bin 0x8000000
```
