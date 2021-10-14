#define STATUS_H

//dit is het bestand voor alle beslis logica.

enum ENUM {
    DEK_OPEN,
    DEK_DICHT,
    DEK_RESET,
    SLAGBOMEN_DICHT,
    SLAGBOMEN_OPEN,
    SLAGBOMEN_RESET,
    NIET_BEZIG,
    BEZIG_OPEN,
    BEZIG_DICHT,
};

int status_dek = DEK_RESET;
int status_slagbomen = SLAGBOMEN_RESET;
int status_bezig = NIET_BEZIG;
int timer_lampen = 0;

void brug()
{
    if (NOODSTOPHOOG){
        h_bridge_set_percentage(0);
        return;
    }

    if (ISBRUGDICHT) status_dek = DEK_DICHT;
    else if (ISBRUGOPEN)status_dek = DEK_OPEN;
    else status_dek = DEK_RESET;

    if (SCHAKELAARAAN){
        CONTROLEPANEELAANLEDAAN;

        if(SCHAKELAARAUTOMATISCH){
            //todo
        } else {
            if(SCHAKELAAROPEN && status_bezig == NIET_BEZIG) open_brug();
            else if (status_bezig == NIET_BEZIG) sluit_brug();
        }
    } else AlleLedsUit();

    switch(status_bezig){
        case BEZIG_DICHT:
            if(status_dek == DEK_DICHT){
                //brug is dicht gegaan
                h_bridge_set_percentage(0);
                open_slagbomen();
            }
        case BEZIG_OPEN:
            if (status_dek == DEK_OPEN){
                //brug is open gegaan
                h_bridge_set_percentage(0);
            }
    }

    if(status_slagbomen == SLAGBOMEN_DICHT){
        if(abs(millis - timer_lampen) > 1000 && abs(millis - timer_lampen) < 2000){
            SLAGBOOMLED1AAN;
            SLAGBOOMLED2UIT;
        }

        if(abs(millis - timer_lampen) > 2000){
            SLAGBOOMLED2AAN;
            SLAGBOOMLED1UIT;
            timer_lampen = 0;
        }
    }

}

void open_brug(){
    if(status_dek == DEK_OPEN) return;

    if(!is_wind_veilig()) return;

    if(!status_slagbomen == SLAGBOMEN_DICHT){
        sluit_slagbomen();
    }

    h_bridge_set_percentage(50);
}

void sluit_brug(){
    if(status_dek == DEK_DICHT) return;

    h_bridge_set_percentage(-50);
}

void sluit_slagbomen(){
    if(status_slagbomen == SLAGBOMEN_DICHT) return;

    servo1_set_percentage(100);
    servo2_set_percentage(100);

    timer_lampen = millis;

    ZOEMERAAN;

    _delay_ms(1000);

    status_slagbomen = SLAGBOMEN_DICHT;

}

void open_slagbomen(){
    if(status_slagbomen == SLAGBOMEN_OPEN) return;

    servo1_set_percentage(-100);
    servo2_set_percentage(-100);

    ZOEMERUIT;

    _delay_ms(1000);

    status_slagbomen = SLAGBOMEN_OPEN;
}

