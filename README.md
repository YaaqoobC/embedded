# Embedded Systems

My embedded systems projects and experiments, written in C.

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

## Build
Each project has its own `CMakeLists.txt`
Example:

```bash
    cd <project>
    mkdir build
    cd build

    cmake -G Ninja -DPICO_BOARD=pico2_w ..
    ninja
```

This produces a `.uf2` firmware file in the build/ directory.

## Flash
1. Hold BOOTSEL while connecting the Pico 2 W over USB.
2. The board appears as the `RP2350` drive.
3. Copy the project's `.uf2` file onto the drive.
4. The Pico automatically reboots and runs the firmware.