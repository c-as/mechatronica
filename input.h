#define INPUT_H

//windsnelheid = port D45
//brug_dicht = port D44
//brug_open = port D43

int fan_counter = 0;
int timer = 0;
char snum[5];

void init_input(){
    DDRL &= ~(1 << PL4);
}

void input(){
    //check windsnelheid
    if(PINL & (1 << PL4)){
        fan_counter += 1;
    }

    itoa(fan_counter, snum, 10);
    puts(snum);
}

bool is_brug_dicht(){
    return false;
}

bool is_brug_open(){
    return !is_brug_dicht();
}
