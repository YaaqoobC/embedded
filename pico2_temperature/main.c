#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main(void) {
    // Configure stdout before the first printf(). CMake routes it to UART0:
    // GP12 (target TX) -> probe GP5 (probe RX) at 115200 baud.
    stdio_init_all();

    // On a Pico 2 W the onboard LED is driven by the CYW43 wireless chip,
    // not directly by RP2350 GPIO25. This initializes that chip interface.
    if (cyw43_arch_init()) {
        printf("CYW43 initialization failed\n");
        return -1;
    }

    printf("Pico 2 W temperature project started\n");

    while (true) {
        // An observable heartbeat: turn on the Pico 2 W's onboard LED.
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        printf("LED on\n");
        sleep_ms(100);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        printf("LED off\n");
        sleep_ms(100);
    }
}
