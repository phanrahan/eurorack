#include "Arduino.h"

void pwm_init() 
{
    // Set up Timer 1 to do PWM for the CV 1v/oct output.

    // OC1A = pin 9
    // OC1B = pin 10

    //fast PWM, div 1

    TCCR1A = (1 << WGM11) | (1 << COM1A1);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
    ICR1 = 255;

    //fast PWM 
    //16000000/256 = 62.5kHz 

    OCR1A = 0;
    TIMSK1 = 0;

    OCR1AH = 0;
    OCR1AL = 0;
}

void pwm_write(unsigned val) 
{
    OCR1A = val;
}
