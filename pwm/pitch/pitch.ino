#include "pwm.h"

void setup() 
{
    pinMode(9, OUTPUT);
    pwm_init();
}

void loop() 
{
    pwm_write(30*64);
}
