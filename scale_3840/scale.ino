#include "pwm.h"

const int clock = 2;
const int duration = A1;
const int gate = 13;
const int cv = 9;

unsigned clockstate = 0;

unsigned long lastmillis = 0;
unsigned voltage = 0;

void clockisr()
{
    clockstate = 1;
}

void pulse(unsigned i)
{
    digitalWrite(gate,1);
    delay(i);
    digitalWrite(gate,0);
    //delay(n-i);
}

void setup() 
{
    Serial.begin(115200);
    
    pinMode(clock, INPUT);
    pinMode(duration, INPUT);
    pinMode(gate, OUTPUT);
    pinMode(cv, OUTPUT);

    attachInterrupt(0, clockisr, RISING);

    pwm_init();
    
    lastmillis = millis();
}

void loop() 
{
    if( clockstate ) {
        clockstate = 0;

        unsigned long m = millis();
        unsigned long length = m - lastmillis;
        lastmillis = m;

        Serial.print("bpm: ");
        Serial.println(60000UL/length);
        
        unsigned d =  (length*analogRead(duration))/1023;

        pwm_write(voltage*64);

        voltage = (voltage +1) % 24;

        pulse(d);
 
    }
}
