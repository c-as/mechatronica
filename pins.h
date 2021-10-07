#define PINS_H
#include <util/delay.h>

// Digital pins en directory voor MEGA
//
// Digital pin 53 -- PB0 -> rode led 1
// Digital pin 52 -- PB1 -> rode led 2
// Digital pin 51 -- PB2 -> groene led 1
// Digital pin 50 -- PB3 -> groene led 2
// Digital pin 49 -- PL0 -> gele led 1
// Digital pin 48 -- PL1 -> gele led 2
// Digital pin 47 -- PL2
// Digital pin 46 -- PL3
//
// Digital pin 3 -- PE5 -> ZOEMER

#define RODELED1AAN PORTB |= (1 << 0)
#define RODELED1UIT PORTB &= ~(1 << 0)

#define RODELED2AAN PORTB |= (1 << 1)
#define RODELED2UIT PORTB &= ~(1 << 1)

#define GROENELED1AAN PORTB |= (1 << 2)
#define GROENELED1UIT PORTB &= ~(1 << 2)

#define GROENELED2AAN PORTB |= (1 << 3)
#define GROENELED2UIT PORTB &= ~(1 << 3)

#define GELELED1AAN PORTL |= (1 << 0)
#define GELELED1UIT PORTL &= ~(1 << 0)

#define GELELED2AAN PORTL |= (1 << 1)
#define GELELED2UIT PORTL &= ~(1 << 1)

#define ZOEMERAAN PORTE |= (1 << 5)
#define ZOEMERUIT PORTE &= ~(1 << 5)

    bool groeneLedsKnipperen = false;


    void ZetPinDirectories(void)
    {
        DDRB |= _BV(0) | _BV(1) | _BV(2) | _BV(3);
        DDRL |= _BV(0) | _BV(1);
        DDRE |= _BV(5);
    }

    void AlleLedsUit(void)
    {
        groeneLedsKnipperen = false;

        RODELED1UIT;
        RODELED2UIT;
        GROENELED1UIT;
        GROENELED2UIT;
        GELELED2UIT;
        GELELED1UIT;
    }


    void DoorvaartVerbodenLeds(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
    }

    void DoortvaartBijnaToegestaanLeds(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        GROENELED1AAN;
        GROENELED2AAN;
    }

    void DoorvaartToegestaanLeds(void)
    {
        AlleLedsUit();

        GROENELED1AAN;
        GROENELED2AAN;
    }

    void DoorvaartGenaderdenLeds(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;

        groeneLedsKnipperen = true;
    }

    void DoorvaartGeslotenBrugMetTegenliggers(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        GELELED1AAN;
    }

    void DoorvaartGeslotenBrugZonderTegenliggers(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        GELELED1AAN;
        GELELED2AAN;
    }


