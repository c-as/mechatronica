#define INPUT_H

//bestand waar de meeste sensoren worden geregeld.

//windsnelheid = port D31 PC6
//brug_dicht = port
//brug_open = port

#define WINDMETERHOOG PINC & (1 << 6)
#define ISBRUGDICHT PINC & (1 << 7)
#define ISBRUGOPEN PINA & (1 << 7)
#define VOETGANGERSSENSORHOOG1 PINA & (1 << 6)
#define VOETGANGERSSENSORHOOG2 PINA & (1 << 5)
#define VOETGANGERSSENSORHOOG3 PIND & (1 << 1)
#define VOETGANGERSSENSORHOOG4 PIND & (1 << 2)
#define BOOTSENSORHOOG1 PINA & (1 << 0)
#define BOOTSENSORHOOG2 PIND & (1 << 0)
#define NOODSTOPHOOG PINA & (1 << 4)
#define SCHAKELAARAAN PINA & (1 << 3)
#define SCHAKELAAROPEN PINA & (1 << 2)
#define SCHAKELAARAUTOMATISCH PINA & (1 << 1)

int current_rpm = 0;

void init_input(){
    DDRC &= ~(_BV(6) | _BV(7));
    DDRA &= ~(_BV(6) | _BV(5) | _BV(4) | _BV(3) | _BV(2) | _BV(1));
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
}

bool is_wind_veilig(){
    return current_rpm < 10000;
}

bool is_er_een_boot(){
    return (!BOOTSENSORHOOG1) || (!BOOTSENSORHOOG2);
}

bool is_er_verkeer(){
    return (!VOETGANGERSSENSORHOOG1) || (!VOETGANGERSSENSORHOOG2) || (!VOETGANGERSSENSORHOOG3) || (!VOETGANGERSSENSORHOOG4);
}


