bool slagbomen_zijn_open = false;

void open_brug(){
    if(is_er_verkeer()){
        return;
    }

    if(!is_wind_veilig()){
        return;
    }

    knippper_slagboom_lichten();

    slagbomen_dicht();
    CONTROLEPANEELSLAGBOOMDICHTLEDAAN;

    _delay_ms(1000);

    h_bridge_set_percentage(50);
    _delay_ms(1000);
    h_bridge_set_percentage(0);
    CONTROLEPANEELOPENLEDAAN;
    DoorvaartToegestaanLeds();

    _delay_ms(1000);

    while(1){
        if(KNOPOPENINGEDRUKT){
            brug_dicht();
            break;
        }
    }
}

void brug_dicht(){
    DoorvaartVerbodenLeds();
    h_bridge_set_percentage(-30);
    while(1){
        if(BRUGDICHTLIMITINGEDRUKT){
            h_bridge_set_percentage(0);
            CONTROLEPANEELOPENLEDUIT;

            _delay_ms(1000);

            slagbomen_open();

            CONTROLEPANEELSLAGBOOMDICHTLEDUIT;
            break;
        }
    }
}

void slagbomen_dicht(){
    if(is_er_verkeer()){
        return;
    }

    if(!is_wind_veilig()){
        return;
    }

    servo1_set_percentage(100);
    servo2_set_percentage(100);
    slagbomen_zijn_open = false;
    CONTROLEPANEELSLAGBOOMDICHTLEDAAN;

    SLAGBOOMLED1UIT;
    SLAGBOOMLED2UIT;
}

void slagbomen_open(){
    servo1_set_percentage(-100);
    servo2_set_percentage(-100);
    slagbomen_zijn_open = true;
    CONTROLEPANEELSLAGBOOMDICHTLEDUIT;
}

void knippper_slagboom_lichten(){
    for(int i = 0; i < 2; i++){
        SLAGBOOMLED1AAN;
        SLAGBOOMLED2UIT;
        _delay_ms(250);
        SLAGBOOMLED1UIT;
        SLAGBOOMLED2AAN;
        _delay_ms(250);
    }

    SLAGBOOMLED1AAN;


}

void leds(){
    if(is_er_verkeer()){
        CONTROLEPANEELVOETGANGERSLEDAAN;
    } else {
        CONTROLEPANEELVOETGANGERSLEDUIT;
    }

    if(is_er_een_boot()){
        CONTROLEPANEELBOTENLEDAAN;
    } else {
        CONTROLEPANEELBOTENLEDUIT;
    }

    if(is_wind_veilig()){
        CONTROLEPANEELWEERSOMSTANDIGHEDENLEDUIT;
    } else {
        CONTROLEPANEELWEERSOMSTANDIGHEDENLEDAAN;
    }

    if(schakelaar_modus){
        CONTROLEPANEELAUTOMATISCHLEDAAN;
    } else {
        CONTROLEPANEELAUTOMATISCHLEDUIT;
    }

    if(slagbomen_zijn_open){
        CONTROLEPANEELSLAGBOOMDICHTLEDUIT;
    } else {
        CONTROLEPANEELSLAGBOOMDICHTLEDAAN;
    }

}

void knoppen(){
    if(KNOPOPENINGEDRUKT){
        open_brug();
    }

   if(KNOPSLAGBOMENINGEDRUKT){
        if(slagbomen_zijn_open){
            slagbomen_dicht();
        } else {
            slagbomen_open();
        }
        _delay_ms(500);
    }
}

void lineair(){
    slagbomen_open();
    DoorvaartVerbodenLeds();
    while(1){
        input();
        leds();
        knoppen();
    }
}
