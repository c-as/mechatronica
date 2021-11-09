#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "clock.h"
#include "uart.h"
#include "pins.h"
#include "input.h"
#include "servo.h"
#include "h_bridge.h"
#include "lineair.h"

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

int main(void)
{
    init_leds();
    init_input();
    init_clock();
    init_servo();
    init_uart();
    init_h_bridge();

    //voor het gebruik van uart
    stdout = &uart_output;
    stdin  = &uart_input;

    lineair();

    return 0;
}
