#define STATUS_H

//dit is het bestand voor alle beslis logica.

enum ENUM {
    DEK_OPEN,
    DEK_DICHT,
    DEK_RESET,
    SLAGBOMEN_DICHT,
    SLAGBOMEN_SLUITEN,
    SLAGBOMEN_OPEN,
    SLAGBOMEN_RESET,
    NIET_BEZIG,
    BEZIG_OPEN,
    BEZIG_SLUITEN,
    BEZIG_SLAGBOMEN_SLUITEN
};

const int TIJD_KNIPPERLICHT = 1000;
const int WACHTIJD_BOOT = 10000;
const int WACHTIJD_SLAGBOMEN = 10000;
const int KRACHT_MOTOR = 50;

bool auto_reset = true;
bool noodstop = false;

int status_dek = DEK_RESET;
int status_slagbomen = SLAGBOMEN_RESET;
int status_bezig = NIET_BEZIG;

int timer_lampen = 0;
int timer_boot = 0;
int timer_slagboom = 0;

void brug()
{
    if(noodstop) return;

    if (NOODSTOPHOOG){
        h_bridge_set_percentage(0);
        noodstop = true;
        return;
    }

    if (ISBRUGDICHT) status_dek = DEK_DICHT;
    else if (ISBRUGOPEN)status_dek = DEK_OPEN;
    else status_dek = DEK_RESET;

    if (SCHAKELAARAAN){
        //brug staat aan
        CONTROLEPANEELAANLEDAAN;

        if(SCHAKELAARAUTOMATISCH){
            //automatische stand
            CONTROLEPANEELAUTOMATISCHLEDAAN;

            if(auto_reset){
                //startup
                if (status_dek == DEK_DICHT) sluit_brug();
                else open_brug();
                auto_reset = false;
            } else {
                //autmatic operation
                switch(status_dek){
                    case DEK_DICHT:
                        if (is_er_een_boot()) open_brug();
                    case DEK_OPEN:
                        if (is_er_een_boot()) timer_boot = millis;
                        if (abs(millis - timer_boot) > WACHTIJD_BOOT){
                            sluit_brug();
                        }
                }
            }


        } else {
            //handmatige stand
            CONTROLEPANEELAUTOMATISCHLEDUIT;
            if(SCHAKELAAROPEN && status_bezig == NIET_BEZIG) open_brug();
            else if (status_bezig == NIET_BEZIG) sluit_brug();
        }
    } else {
        //brug staat uit
        AlleLedsUit();
        auto_reset = true;
        h_bridge_set_percentage(0);
        status_dek = DEK_RESET;
        status_bezig = NIET_BEZIG;
        status_slagbomen = SLAGBOMEN_RESET;
    }

    if (status_bezig != NIET_BEZIG) CONTROLEPANEELBEZIGLEDAAN;
    else CONTROLEPANEELBEZIGLEDUIT;

    if(is_wind_veilig()) CONTROLEPANEELWEERSOMSTANDIGHEDENLEDUIT;
    else CONTROLEPANEELWEERSOMSTANDIGHEDENLEDAAN;

    switch(status_bezig){
        case BEZIG_SLUITEN:
            //brug is dicht gegaan
            if(status_dek == DEK_DICHT){
                h_bridge_set_percentage(0);
                CONTROLEPANEELOPENLEDUIT;
                open_slagbomen();
            }
        case BEZIG_OPEN:
            //brug is open gegaan
            if (status_dek == DEK_OPEN){
                h_bridge_set_percentage(0);
                DoorvaartToegestaanLeds();

                if(SCHAKELAARAUTOMATISCH){
                    timer_boot = millis;
                }
            }
        case BEZIG_SLAGBOMEN_SLUITEN:
            if (status_slagbomen == SLAGBOMEN_DICHT) open_brug_volledig();
    }

    //knipperlichten
    if(status_slagbomen == SLAGBOMEN_DICHT){
        if(abs(millis - timer_lampen) > TIJD_KNIPPERLICHT && abs(millis - timer_lampen) < TIJD_KNIPPERLICHT * 2){
            SLAGBOOMLED1AAN;
            SLAGBOOMLED2UIT;
        }

        if(abs(millis - timer_lampen) > TIJD_KNIPPERLICHT * 2){
            SLAGBOOMLED2AAN;
            SLAGBOOMLED1UIT;
            timer_lampen = millis;
        }
    }

    //wachten totdat brug vrij is
    if(status_slagbomen == SLAGBOMEN_SLUITEN){
        if(is_er_verkeer()){
            timer_slagboom = millis;
        }

        if(abs(millis - timer_slagboom) > WACHTIJD_SLAGBOMEN){
            sluit_slagbomen_volledig();
        }
    }
}

void open_brug(){
    CONTROLEPANEELOPENLEDAAN;

    if(status_dek == DEK_OPEN) return;

    if(!is_wind_veilig()) return;

    DoorvaartBijnaToegestaanLeds();

    if(!status_slagbomen == SLAGBOMEN_DICHT){
        sluit_slagbomen();
        status_bezig = BEZIG_SLAGBOMEN_SLUITEN;
        //wacht met het aanzetten van de motor totdat de slagbomen dicht zijn
        return;
    }

    open_brug_volledig();
}

void sluit_brug(){
    if(status_dek == DEK_DICHT) return;
    if(is_er_een_boot()) return;
    if(!is_wind_veilig()) return;

    DoorvaartVerbodenLeds();

    status_bezig = BEZIG_SLUITEN;

    h_bridge_set_percentage(-KRACHT_MOTOR);
}

void open_brug_volledig(){
    //gebruik alleen als slagbomen dicht zijn
    if(!is_wind_veilig()) return;
    status_bezig = BEZIG_OPEN;
    h_bridge_set_percentage(KRACHT_MOTOR);
}

void sluit_slagbomen(){
    if(status_slagbomen == SLAGBOMEN_DICHT) return;

    //zet slagbomen op 45 graden voor waarschuwing
    servo1_set_percentage(0);
    servo2_set_percentage(0);

    timer_lampen = millis;
    timer_slagboom = millis;

    ZOEMERAAN;

    status_slagbomen = SLAGBOMEN_SLUITEN;
}

void sluit_slagbomen_volledig(){
    //toegepast na waarschuwen van verkeer

    servo1_set_percentage(100);
    servo2_set_percentage(100);

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

