cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Name our project
project(pico2_temperature C CXX ASM)

# Init the SDK
pico_sdk_init()

# Make the executable
add_executable(pico2_temperature
    main.c
)

# Link the libraries
target_link_libraries(pico2_temperature
    pico_stdlib
    pico_cyw43_arch_none
)

# Route printf() to UART0. GP12/GP13 match the existing probe UART wiring.
target_compile_definitions(pico2_temperature PRIVATE
    PICO_DEFAULT_UART=0
    PICO_DEFAULT_UART_TX_PIN=12
    PICO_DEFAULT_UART_RX_PIN=13
    PICO_DEFAULT_UART_BAUD_RATE=115200
)

# Keep stdout on the debug probe's UART instead of the target USB port.
pico_enable_stdio_uart(pico2_temperature 1)
pico_enable_stdio_usb(pico2_temperature 0)

# Generate the UF2
pico_add_extra_outputs(pico2_temperature)
