# Setup

### Install ARM GCC

Search Google

Check whether installed or not:
```
$ arm-none-eabi-gcc -v
```

### ST-LINK

```
$ brew install stlink
```

### Clone repository

```
$ git clone https://github.com/niklauslee/kameleon-firmware.git
```

### Clone submodules

Typically submodules will be cloned during cloning the repository. If not cloned, try followings:

```
$ git submodule init
$ git submodule update
```

# Build

Move to a target folder

```
$ cd targets/stm32f4
$ make
```

# Flash & Run

Run st-link

```
$ st-util
```

Flash via gdb

```
$ make flash
...
(gdb) run
```
