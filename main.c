#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "clock.h"
#include "uart.h"
#include "pins.h"
#include "status.h"
#include "servo.h"
#include "h_bridge.h"

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void start_brug()
{
    ZetPinDirectories();
    init_clock();
    init_servo();
    init_uart();
    init_h_bridge();

    stdout = &uart_output;
    stdin  = &uart_input;

    while (1)
    {
        input();
        brug();
    }
}

int main(void)
{
    //brug is dicht doorvaart verboden
//    DoorvaartGeslotenBrugMetTegenliggers();

    //sensor ziet boot
    //Meld mensen op de brug met zoemer
//    ZOEMERAAN;

    //als brug vrij is:
    //Zoemer uit
//    ZOEMERUIT;

    //brug open & lampen brug is bijna open
//    DoortvaartBijnaToegestaanLeds();

    //als brug open is:
    //lampen voor boot doorvaart:
//    DoorvaartToegestaanLeds();

    //Sensor ziet dat de boot voorbij is:
    //lampen gestremde doorvaart
//    DoorvaartGenaderdenLeds();

    //wacht 5 seconden
    //brug dicht & lampen verboden doorvaart
//    DoorvaartGeslotenBrugMetTegenliggers();

//    while (1)
//    {
//        while (groeneLedsKnipperen)
//        {
//            GROENELED1AAN;
//            GROENELED2AAN;
//            _delay_ms(1000);
//            GROENELED1UIT;
//            GROENELED2UIT;
//            _delay_ms(1000);
//        }
//    }

    start_brug();

    return 0;
}
