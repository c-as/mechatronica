#define CLOCK_H

//als het goed is zijn dit milliseconden
int millis = 0;

void init_clock(){
    //mode 0
    TCCR2A = 0;
    // set prescaler to 1024
    TCCR2B |= (1 << CS01) | (1 << CS00);
    //Set interrupt on compare match
    TIMSK2 |= (1 << TOIE2);

    TCNT2 = 0x00;

    OCR2A = 0;
	OCR2B = 0;

    // enable interrupts
    sei();
}

ISR (TIMER2_OVF_vect)
{
    millis++;
}
