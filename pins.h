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
// Digital pin 47 -- PL2 -> rode led 3
// Digital pin 46 -- PL3 -> rode led 4
// Digital pin 45 -- PL4 -> groene led 3
// Digital pin 44 -- PL5 -> groene led 4
// Digital pin 43 -- PL6 -> gele led 3
// Digital pin 42 -- PL7 -> gele led
//
// Digital pin 3 -- PE5 -> ZOEMER

#define RODELED1AAN PORTB |= (1 << 0)
#define RODELED1UIT PORTB &= ~(1 << 0)

#define RODELED2AAN PORTB |= (1 << 1)
#define RODELED2UIT PORTB &= ~(1 << 1)

#define RODELED3AAN PORTL |= (1 << 2)
#define RODELED3UIT PORTL &= ~(1 << 2)

#define RODELED4AAN PORTL |= (1 << 3)
#define RODELED4UIT PORTL &= ~(1 << 3)

#define GROENELED1AAN PORTB |= (1 << 2)
#define GROENELED1UIT PORTB &= ~(1 << 2)

#define GROENELED2AAN PORTB |= (1 << 3)
#define GROENELED2UIT PORTB &= ~(1 << 3)

#define GROENELED3AAN PORTL |= (1 << 4)
#define GROENELED3UIT PORTL &= ~(1 << 4)

#define GROENELED4AAN PORTL |= (1 << 5)
#define GROENELED4UIT PORTL &= ~(1 << 5)

#define GELELED1AAN PORTH |= (1 << 4)
#define GELELED1UIT PORTH &= ~(1 << 4)

#define GELELED2AAN PORTL |= (1 << 1)
#define GELELED2UIT PORTL &= ~(1 << 1)

#define GELELED3AAN PORTL |= (1 << 6)
#define GELELED3UIT PORTL &= ~(1 << 6)

#define GELELED4AAN PORTA |= (1 << 7)
#define GELELED4UIT PORTA &= ~(1 << 7)

#define ZOEMERAAN PORTE |= (1 << 5)
#define ZOEMERUIT PORTE &= ~(1 << 5)

#define SLAGBOOMLED1AAN PORTG |= (1 << 0)
#define SLAGBOOMLED1UIT PORTG &= ~(1 << 0)

#define SLAGBOOMLED2AAN PORTC |= (1 << 4)
#define SLAGBOOMLED2UIT PORTC &= ~(1 << 4)

#define CONTROLEPANEELAANLEDAAN PORTA |= (1 << 6)
#define CONTROLEPANEELAANLEDUIT PORTA &= ~(1 << 6)

#define CONTROLEPANEELAUTOMATISCHLEDAAN PORTC |= (1 << 7)
#define CONTROLEPANEELAUTOMATISCHLEDUIT PORTC &= ~(1 << 7)

#define CONTROLEPANEELOPENLEDAAN PORTC |= (1 << 5)
#define CONTROLEPANEELOPENLEDUIT PORTC &= ~(1 << 5)

#define CONTROLEPANEELVOETGANGERSLEDAAN PORTC |= (1 << 3)
#define CONTROLEPANEELVOETGANGERSLEDUIT PORTC &= ~(1 <<3)

#define CONTROLEPANEELBOTENLEDAAN PORTC |= (1 << 1)
#define CONTROLEPANEELBOTENLEDUIT PORTC &= ~(1 << 1)

#define CONTROLEPANEELWEERSOMSTANDIGHEDENLEDAAN PORTD |= (1 << 7)
#define CONTROLEPANEELWEERSOMSTANDIGHEDENLEDUIT PORTD &= ~(1 << 7)

#define CONTROLEPANEELBEZIGLEDAAN PORTG |= (1 << 1)
#define CONTROLEPANEELBEZIGLEDUIT PORTG &= ~(1 << 1)

#define CONTROLEPANEELNOODSTOPLEDAAN PORTL |= (1 << 7)
#define CONTROLEPANEELNOODSTOPLEDUIT PORTL &= ~(1 << 7)

    bool groeneLedsKnipperen = false;


    void init_leds(void)
    {
        DDRB |= _BV(0) | _BV(1) | _BV(2) | _BV(3);
        DDRL |= _BV(1) | _BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7);
        DDRE |= _BV(5);
        DDRG |= _BV(0) | _BV(1);
        DDRA |= _BV(6) | _BV(7);
        DDRD |= _BV(7);
        DDRC |= _BV(1) | _BV(3) | _BV(4) | _BV(5) | _BV(7);
        DDRH |= _BV(4);
    }

    void AlleLedsAan(void){
        RODELED1AAN;
        RODELED2AAN;
        RODELED3AAN;
        RODELED4AAN;
        GROENELED1AAN;
        GROENELED2AAN;
        GROENELED3AAN;
        GROENELED4AAN;
        GELELED1AAN;
        GELELED2AAN;
        GELELED3AAN;
        GELELED4AAN;
        ZOEMERAAN;
        SLAGBOOMLED1AAN;
        SLAGBOOMLED2AAN;
        CONTROLEPANEELAANLEDAAN;
        CONTROLEPANEELAUTOMATISCHLEDAAN;
        CONTROLEPANEELOPENLEDAAN;
        CONTROLEPANEELVOETGANGERSLEDAAN;
        CONTROLEPANEELBOTENLEDAAN;
        CONTROLEPANEELWEERSOMSTANDIGHEDENLEDAAN;
        CONTROLEPANEELBEZIGLEDAAN;
        CONTROLEPANEELNOODSTOPLEDAAN;
    }

    void AlleLedsUit(void)
    {
        groeneLedsKnipperen = false;

        RODELED1UIT;
        RODELED2UIT;
        RODELED3UIT;
        RODELED4UIT;
        GROENELED1UIT;
        GROENELED2UIT;
        GROENELED3UIT;
        GROENELED4UIT;
        GELELED2UIT;
        GELELED1UIT;
        GELELED3UIT;
        GELELED4UIT;
        ZOEMERUIT;
        SLAGBOOMLED1UIT;
        SLAGBOOMLED2UIT;
        CONTROLEPANEELAANLEDUIT;
        CONTROLEPANEELAUTOMATISCHLEDUIT;
        CONTROLEPANEELOPENLEDUIT;
        CONTROLEPANEELVOETGANGERSLEDUIT;
        CONTROLEPANEELBOTENLEDUIT;
        CONTROLEPANEELWEERSOMSTANDIGHEDENLEDUIT;
        CONTROLEPANEELBEZIGLEDUIT;
        CONTROLEPANEELNOODSTOPLEDUIT;
    }


    void DoorvaartVerbodenLeds(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        RODELED3AAN;
        RODELED4AAN;
    }

    void DoorvaartBijnaToegestaanLeds(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        RODELED3AAN;
        RODELED4AAN;
        GROENELED1AAN;
        GROENELED2AAN;
        GROENELED3AAN;
        GROENELED4AAN;
    }

    void DoorvaartToegestaanLeds(void)
    {
        AlleLedsUit();

        GROENELED1AAN;
        GROENELED2AAN;
        GROENELED3AAN;
        GROENELED4AAN;
    }

    void DoorvaartGenaderdenLeds(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        RODELED3AAN;
        RODELED4AAN;

        groeneLedsKnipperen = true;
    }

    void DoorvaartGeslotenBrugMetTegenliggers(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        GELELED1AAN;
        GROENELED3AAN;
        GROENELED4AAN;
    }

    void DoorvaartGeslotenBrugZonderTegenliggers(void)
    {
        AlleLedsUit();

        RODELED1AAN;
        RODELED2AAN;
        GELELED1AAN;
        GELELED2AAN;
        RODELED3AAN;
        RODELED4AAN;
        GELELED3AAN;
        GELELED4AAN;
    }


