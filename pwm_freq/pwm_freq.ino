#include "pwm.h"

void setup() 
{
    // output A on timer1 is pin 9
    pinMode(9, OUTPUT);
    pwm_init();
}

void loop() 
{
    pwm_write(30*64); // 50% duty cycle
}
