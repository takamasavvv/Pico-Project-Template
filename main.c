#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "pinout_xiao.h"

#define UART_ID uart0
#define BAUD_RATE 115200

// // We are using pins 0 and 1, but see the GPIO function select table in the
// // datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// int main() {
//     const uint LED_PIN = PICO_DEFAULT_LED_PIN;
//     gpio_init(LED_PIN);
//     gpio_set_dir(LED_PIN, GPIO_OUT);

//     bool LED_ON = false;
//     while (true) {
//         gpio_put(LED_PIN, LED_ON);
//         LED_ON = !LED_ON;
//         sleep_ms(1000);
//     }
// }

int main() {
    // Set up our UART with the required speed.
    gpio_init(XIAO_LED_RED);
    gpio_set_dir(XIAO_LED_RED, GPIO_OUT);
    gpio_init(XIAO_LED_GREEN);
    gpio_set_dir(XIAO_LED_GREEN, GPIO_OUT);
    gpio_init(XIAO_LED_BLUE);
    gpio_set_dir(XIAO_LED_BLUE, GPIO_OUT);

    gpio_init(XIAO_NEOPIXEL);
    gpio_set_dir(XIAO_NEOPIXEL, GPIO_OUT);



    uart_init(UART_ID, BAUD_RATE);
    bool LED_ON = false;
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    sleep_ms(500);

    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    while(true) {
        // Send out a character without any conversions
        // uart_putc_raw(UART_ID, 'A');
        gpio_put(XIAO_LED_BLUE, LED_ON);
        gpio_put(XIAO_LED_RED, !LED_ON);
        gpio_put(XIAO_LED_GREEN, !LED_ON);
        gpio_put(XIAO_NEOPIXEL, !LED_ON);
        LED_ON = !LED_ON;
        // Send out a character but do CR/LF conversions
        // uart_putc(UART_ID, 'B');

        // Send out a string, with CR/LF conversions
        uart_puts(UART_ID, " Hello, World!\r\n");
        sleep_ms(500);
    }
}
