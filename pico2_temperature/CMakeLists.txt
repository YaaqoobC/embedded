cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico2_temperature C CXX ASM)

pico_sdk_init()

add_executable(pico2_temperature
    main.c
)

target_link_libraries(pico2_temperature
    pico_stdlib
    pico_cyw43_arch_none
)

pico_add_extra_outputs(pico2_temperature)
