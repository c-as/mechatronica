#define INPUT_H

//bestand waar de meeste sensoren worden geregeld.

//windsnelheid = port D31 PC6
//brug_dicht = port
//brug_open = port

#define WINDMETERHOOG PINA & (1 << 1)
#define BRUGDICHTLIMITINGEDRUKT PINC & (1 << 4)
#define VOETGANGERSSENSORINBLOKKEERD !(PINA & (1 << 5))
#define VOETGANGERSSENSORUITBLOKKEERD !(PINC & (1 << 6))
#define BOOTSENSORINBLOKKEERD !(PINA & (1 << 3))
#define BOOTSENSORUITBLOKKEERD !(PINA & (1 << 7))
#define KNOPMODUSINGEDRUKT !(PINA & (1 << 0))
#define KNOPOPENINGEDRUKT !(PINA & (1 << 2))
#define KNOPSLAGBOMENINGEDRUKT !(PINA & (1 << 4))
#define KNOPNOODSTOPINGEDRUKT !(PINL & (1 << 5))


int current_rpm = 0;
int voetgangers_counter = 0;
bool prev_voetgangers_sensor_in = false;
bool prev_voetgangers_sensor_uit = false;

int boten_counter = 0;
bool prev_boten_sensor_in = false;
bool prev_boten_sensor_uit = false;

bool prev_knop_modus = false;

bool schakelaar_modus = false;
bool schakelaar_open = false;
bool schakelaar_slagbomen = false;
bool noodstop = false;

void init_input(){
    //DDRC &= ~(_BV(6));
    //DDRG &= ~(_BV(5) | _BV(2));
    //DDRA &= ~(_BV(0) | _BV(2) | _BV(3) | _BV(4) | _BV(5));
    //DDRL &= ~(_BV(0));
    //DDRD &= ~(_BV(0));
}

void input(){
    static int last_time = 0;
    static int fan_counter = 0;

    //check fan input
    if(WINDMETERHOOG){
        fan_counter++;
    }

    //check de fan rpm elke seconde
    if (abs(millis - last_time) >= 1000){
        current_rpm = fan_counter;
        fan_counter = 0;
        last_time = millis;
    }

    //check knoppen voor input
    if(KNOPMODUSINGEDRUKT && !prev_knop_modus){
        prev_knop_modus = true;
        schakelaar_modus = !schakelaar_modus;
        _delay_ms(10);
    }

    if(!KNOPMODUSINGEDRUKT && prev_knop_modus){
        prev_knop_modus = false;
        _delay_ms(10);
    }

    //check voor voetgangers
    if(VOETGANGERSSENSORINHOOG && !prev_voetgangers_sensor_in){
        voetgangers_counter++;
        prev_boten_sensor_in = true;
    }
    if(!VOETGANGERSSENSORINHOOG && prev_voetgangers_sensor_in){
        prev_boten_sensor_in = false;
    }
    if(VOETGANGERSSENSORUITHOOG && !prev_voetgangers_sensor_uit){
        voetgangers_counter--;
        prev_boten_sensor_uit = true;
    }
    if(!VOETGANGERSSENSORUITHOOG && prev_voetgangers_sensor_uit){
        prev_boten_sensor_uit = false;
    }


    //check voor boten
    if(BOOTSENSORINHOOG && !prev_boten_sensor_in){
        boten_counter++;
        prev_boten_sensor_in = true;
    }
    if(!BOOTSENSORINHOOG && prev_boten_sensor_in){
        prev_boten_sensor_in = false;
    }
    if(BOOTSENSORUITHOOG && !prev_boten_sensor_uit){
        boten_counter--;
        prev_boten_sensor_uit = true;
    }
    if(!BOOTSENSORUITHOOG && prev_boten_sensor_uit){
        prev_boten_sensor_uit = false;
    }
}

bool is_wind_veilig(){
    return current_rpm < 1;
}

bool is_er_een_boot(){
    return boten_counter != 0;
}

bool is_er_verkeer(){
    return voetgangers_counter != 0;
}


