#define STATUS_H

//dit is het bestand voor alle beslis logica.

enum STATUS
{
    RESET,
    DICHT,
    OPEN,
    GAAT_OPEN
};

int status = RESET;

void brug()
{
    switch (status)
    {
    case RESET:
        //brug is weet niet wat de omstandigheden zijn

        if(ISBRUGDICHT){
            status = DICHT;
        }

        if(ISBRUGOPEN){
            status = OPEN;
        }

        break;
    case DICHT:


        break;
    case OPEN:
        break;
    }
}

void open_brug(){
    if(is_wind_veilig()){

    }
}
