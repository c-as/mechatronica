#define STATUS_H

#include "input.h"

enum STATUS
{
    RESET,
    DICHT,
    OPEN
};

int status = RESET;

void brug()
{
    switch (status)
    {
    case RESET:
        //brug is weet niet wat de omstandigheden zijn

        if(is_brug_dicht()){
            status = DICHT;
        }

        if(is_brug_open()){
            status = OPEN;
        }

        break;
    case DICHT:
        break;
    case OPEN:
        break;
    }
}
