#define INPUT_H

//bestand waar de meeste sensoren worden geregeld.

//windsnelheid = port D31 PC6
//brug_dicht = port
//brug_open = port

#define WINDMETERHOOG PINC & (1 << 6)
#define ISBRUGDICHT PING & (1 << 5)
#define ISBRUGOPEN PINL & (1 << 0)
#define VOETGANGERSSENSORHOOG1 PING & (1 << 2)
#define VOETGANGERSSENSORHOOG2 PINA & (1 << 5)
#define BOOTSENSORHOOG1 PINA & (1 << 3)
#define BOOTSENSORHOOG2 PIND & (1 << 0)
#define SCHAKELAARAAN !(PINA & (1 << 0))
#define SCHAKELAAROPEN PINA & (1 << 4)
#define SCHAKELAARAUTOMATISCH PINA & (1 << 2)

int current_rpm = 0;
int voetgangers_counter = 0;
bool prev_voetgangers_sensor1 = false;
bool prev_voetgangers_sensor2 = false;

void init_input(){
    DDRC &= ~(_BV(6));
    DDRG &= ~(_BV(5) | _BV(2));
    DDRA &= ~(_BV(0) | _BV(2) | _BV(3) | _BV(4) | _BV(5));
    DDRL &= ~(_BV(0));
    DDRD &= ~(_BV(0));
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

    //check voor voetgangers
    if(VOETGANGERSSENSORHOOG1 && !prev_voetgangers_sensor1){
        voetgangers_counter++;
        prev_voetgangers_sensor1 = true;
    }

    if(!VOETGANGERSSENSORHOOG1 && prev_voetgangers_sensor1){
        prev_voetgangers_sensor1 = false;
    }

    if(VOETGANGERSSENSORHOOG2 && !prev_voetgangers_sensor2){
        voetgangers_counter--;
        prev_voetgangers_sensor2 = true;
    }

    if(!VOETGANGERSSENSORHOOG2 && prev_voetgangers_sensor2){
        prev_voetgangers_sensor2 = false;
    }
}

bool is_wind_veilig(){
    return current_rpm < 10000;
}

bool is_er_een_boot(){
    return (!BOOTSENSORHOOG1) || (!BOOTSENSORHOOG2);
}

bool is_er_verkeer(){
    return voetgangers_counter > 0;
    //return (!VOETGANGERSSENSORHOOG1) || (!VOETGANGERSSENSORHOOG2) || (!VOETGANGERSSENSORHOOG3) || (!VOETGANGERSSENSORHOOG4);
}


