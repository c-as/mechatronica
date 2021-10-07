#include <avr/io.h>
#include "pins.h"
#include <util/delay.h>

int main(void)
{
    ZetPinDirectories();

    //brug is dicht doorvaart verboden
    DoorvaartGeslotenBrugMetTegenliggers();

    //sensor ziet boot
    //Meld mensen op de brug met zoemer
    ZOEMERAAN;

    //als brug vrij is:
    //Zoemer uit
    ZOEMERUIT;

    //brug open & lampen brug is bijna open
    DoortvaartBijnaToegestaanLeds();

    //als brug open is:
    //lampen voor boot doorvaart:
    DoorvaartToegestaanLeds();

    //Sensor ziet dat de boot voorbij is:
    //lampen gestremde doorvaart
    DoorvaartGenaderdenLeds();

    //wacht 5 seconden
    //brug dicht & lampen verboden doorvaart
    DoorvaartGeslotenBrugMetTegenliggers();

    while (1)
    {
        while (groeneLedsKnipperen)
        {
            GROENELED1AAN;
            GROENELED2AAN;
            _delay_ms(1000);
            GROENELED1UIT;
            GROENELED2UIT;
            _delay_ms(1000);
        }
    }

    return 0;
}
