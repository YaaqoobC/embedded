# Embedded Systems

My repo for my embedded endeavors and experiments, written in C.

## Hardware

- Raspberry Pi Pico 2 W
    - RP2350 microcontroller
    - 520 KB SRAM
    - 4 MB flash
    - Wi-Fi + Bluetooth

## Development Environment

- Windows
- WSL
- Ubuntu
- C
- ARM GNU Toolchain
- CMake
- Ninja
- Raspberry Pi Pico SDK

## Setup

Set the Pico SDK path:

```bash
export PICO_SDK_PATH=$HOME/projects/embedded/pico-sdk
```
Add this to `~/.bashrc` to make it permanent.

### Debug probe

An RP2040 Pico runs the official `debugprobe_on_pico.uf2` firmware and acts as
a CMSIS-DAP SWD probe for the Pico 2 W target. Attach the probe to WSL with
`usbipd`, then confirm it is visible:

```bash
lsusb
# Raspberry Pi Debugprobe on Pico (CMSIS-DAP)
```

SWD connections are direct (not crossed):

| RP2040 probe | Pico 2 W target |
| --- | --- |
| GP2 | SWCLK |
| GP3 | SWDIO |
| GND | GND |

Keep the target powered from its own USB cable. UART wiring is crossed: target
GP12/TX to probe GP5/RX, target GP13/RX to probe GP4/TX, plus shared GND. The
target uses physical pins 16 (GP12) and 17 (GP13).

### OpenOCD and terminal tools

This repository uses the Raspberry Pi OpenOCD build because Ubuntu's stock
OpenOCD may not include `target/rp2350.cfg`.

```bash
sudo apt update
sudo apt install -y git build-essential autoconf automake libtool pkg-config \
  libusb-1.0-0-dev libhidapi-dev libftdi1-dev libjaylink-dev libcapstone-dev \
  libjim-dev gdb-multiarch picocom

mkdir -p ~/tools
git clone --recursive --branch rpi-common https://github.com/raspberrypi/openocd.git ~/tools/openocd-rp
cd ~/tools/openocd-rp
./bootstrap
./configure --enable-cmsis-dap
make -j"$(nproc)"
```

## Daily workflow

For this Pico 2 W project:

```bash
cd ~/projects/embedded/pico2_temperature
make build    # Configure a Debug build and create ELF/UF2 artifacts.
make flash    # Build, program, verify, reset; no BOOTSEL required.
```

`make flash` uses the OpenOCD build at `~/tools/openocd-rp` by default. Override
the location only if yours differs:

```bash
make flash OPENOCD=/path/to/openocd OPENOCD_SCRIPTS=/path/to/openocd/tcl
```

### Source-level debugging

In terminal one:

```bash
make server
```

In terminal two:

```bash
make gdb
```

At the GDB prompt:

```gdb
break main
continue
next
info locals
continue
```

### UART logs

The application sends `printf()` output over UART0 at 115200 baud. Open it with:

```bash
make monitor
```

This opens `/dev/ttyACM0` by default. If WSL assigns another serial device, find
it with `ls /dev/ttyACM*` and pass it explicitly:

```bash
make monitor UART=/dev/ttyACM1
```

`printf()` formats text on the RP2350 and sends the resulting bytes from target
GP12 to the debug probe. The probe forwards them over USB to WSL, where
`make monitor` displays them. It does not stop the program or require GDB.
