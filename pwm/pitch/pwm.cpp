#include "Arduino.h"

void pwm_init() 
{
    // Set up Timer 1 to do PWM for the CV 1v/oct output.

    // Fast PWM mode.
    //
    // COM = 0b01 Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM
    // WGM = 14   Top from ICR1
    TCCR1A = (1 << COM1A1)  | (1 << WGM11);

    // 16000000/8/3840 = 4167 Hz
    // CS = 0b001 clk
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);

    // 16000000/8/3840 = 520 Hz
    // CS = 0b010 clk/8
    //TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11);

    OCR1A = 0;
    TIMSK1 = 0;

    OCR1AH = 0;
    OCR1AL = 0;

    // using 15*256 is clever! - 15*256 is CV=5V
    // mapping a note from 0 to 60 (5 octaves) is done with pwm=note*64
    ICR1H = 15;
    ICR1L = 0;

}

// pwm = 64 * note where 0 <= note <= 60
void pwm_write(unsigned val) 
{
    OCR1AH = val>>8;
    OCR1AL = val&255;
}
