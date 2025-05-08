#include "pwm.h"

const int duration = A1;
const int gate = 13;
const int cv = 9;

unsigned voltage = 0;

void pulse(unsigned i)
{
    digitalWrite(gate,1);
    delay(i);
    digitalWrite(gate,0);
    //delay(n-i);
}

void setup() 
{
    pinMode(duration, INPUT);
    pinMode(gate, OUTPUT);
    pinMode(cv, OUTPUT);

    pwm_init();
}

void loop() 
{
    unsigned d = analogRead(duration);

    pwm_write(voltage * 40);
    voltage = (voltage +1) % 24;
    
    pulse(d);

    delay(1000);
}
