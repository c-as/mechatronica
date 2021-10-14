#define INPUT_H

//bestand waar de meeste sensoren worden geregeld.

//windsnelheid = port D31
//brug_dicht = port
//brug_open = port

int current_rpm = 0;

void init_input(){
    DDRC &= ~(1 << PC6);
}

void input(){
    static int last_time = 0;
    static int fan_counter = 0;
    //check fan input
    if(PINC & (1 << PC6)){
        fan_counter++;
    }

    //check fan rpm
    if (abs(millis - last_time) >= 1000){
        current_rpm = fan_counter;
        fan_counter = 0;
        last_time = millis;
    }
}

bool is_wind_veilig(){
    return current_rpm < 10000;
}

bool is_brug_dicht(){
    return false;
}

bool is_brug_open(){
    return !is_brug_dicht();
}
