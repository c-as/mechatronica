#define PINS_H
#include <util/delay.h>


#define RODELEDSAAN PORTG |= (1 << 2)
#define RODELEDSUIT PORTG &= ~(1 << 2)

#define GROENELEDSAAN PORTC |= (1 << 0)
#define GROENELEDSUIT PORTC &= ~(1 << 0)

#define GELELEDSAAN PORTL |= (1 << 4)
#define GELELEDSUIT PORTL &= ~(1 << 4)

#define SLAGBOOMLED1AAN PORTL |= (1 << 6)
#define SLAGBOOMLED1UIT PORTL &= ~(1 << 6)

#define SLAGBOOMLED2AAN PORTG |= (1 << 0)
#define SLAGBOOMLED2UIT PORTG &= ~(1 << 0)

#define CONTROLEPANEELAUTOMATISCHLEDAAN PORTC |= (1 << 7)
#define CONTROLEPANEELAUTOMATISCHLEDUIT PORTC &= ~(1 << 7)

#define CONTROLEPANEELOPENLEDAAN PORTC |= (1 << 5)
#define CONTROLEPANEELOPENLEDUIT PORTC &= ~(1 << 5)

#define CONTROLEPANEELSLAGBOOMDICHTLEDAAN PORTC |= (1 << 3)
#define CONTROLEPANEELSLAGBOOMDICHTLEDUIT PORTC &= ~(1 << 3)

#define CONTROLEPANEELVOETGANGERSLEDAAN PORTD |= (1 << 7)
#define CONTROLEPANEELVOETGANGERSLEDUIT PORTD &= ~(1 << 7)

#define CONTROLEPANEELBOTENLEDAAN PORTG |= (1 << 1)
#define CONTROLEPANEELBOTENLEDUIT PORTG &= ~(1 << 1)

#define CONTROLEPANEELWEERSOMSTANDIGHEDENLEDAAN PORTL |= (1 << 7)
#define CONTROLEPANEELWEERSOMSTANDIGHEDENLEDUIT PORTL &= ~(1 << 7)

    void init_leds(void)
    {
        DDRC |= _BV(0) | _BV(3) | _BV(5) | _BV(7);
        DDRD |= _BV(7);
        DDRE |= _BV(3);
        DDRF |= _BV(5);
        DDRG |= _BV(0) | _BV(2);
        DDRH |= _BV(3) | _BV(6);
        DDRL |= _BV(4) | _BV(6) | _BV(7);
    }

    //void AlleLedsAan(void){
    //}

    //void AlleLedsUit(void)
    //{
    //}


    void DoorvaartVerbodenLeds(void)
    {
        GROENELEDSUIT;
        RODELEDSAAN;
    }

    void DoorvaartToegestaanLeds(void)
    {
        RODELEDSUIT;
        GROENELEDSAAN;
    }

    void BrugBuitenGebruik(){
        RODELEDSAAN;
        GROENELEDSUIT;
        GELELEDSAAN;
    }


