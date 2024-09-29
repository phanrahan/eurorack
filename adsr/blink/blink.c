#include <avr/io.h>
#include <util/delay.h>

// Hardware Defines
#define LEDS_ATTACK		0x01
#define LEDS_DECAY		0x04
#define LEDS_SUSTAIN	0x02
#define LEDS_RELEASE	0x08
#define LEDS_IDLE_MASK	0xF0

// LED macros
#define LED_ATTACK  {PORTD|=~LEDS_IDLE_MASK;PORTD&=~LEDS_ATTACK;}
#define LED_DECAY   {PORTD|=~LEDS_IDLE_MASK;PORTD&=~LEDS_DECAY;}
#define LED_SUSTAIN {PORTD|=~LEDS_IDLE_MASK;PORTD&=~LEDS_SUSTAIN;}
#define LED_RELEASE {PORTD|=~LEDS_IDLE_MASK;PORTD&=~LEDS_RELEASE;}
#define LED_IDLE    {PORTD|=~LEDS_IDLE_MASK;}

void setup(void)
{
	DDRD  = 0x0F; //PD0-3 outputs
    LED_IDLE
}

// From http://www.bretmulvey.com/avrdelay.html
void delay(void)
{
asm volatile (
    "    ldi  r18, 41"  "\n"
    "    ldi  r19, 150" "\n"
    "    ldi  r20, 128" "\n"
    "1:  dec  r20"  "\n"
    "    brne 1b"   "\n"
    "    dec  r19"  "\n"
    "    brne 1b"   "\n"
    "    dec  r18"  "\n"
    "    brne 1b"   "\n"
);
}

int main(void)
{
    setup();

	while(1)
	{
        /*
        LED_ATTACK
        _delay_ms(1000.0);
        LED_IDLE
        _delay_ms(1000.0);
        LED_DECAY
        _delay_ms(1000.0);
        LED_IDLE
        _delay_ms(1000.0);
        LED_RELEASE
        _delay_ms(1000.0);
        LED_IDLE
        _delay_ms(1000.0);
        */
        LED_ATTACK
        //delay();
        _delay_ms(1000.0);
        LED_IDLE
        //delay();
        _delay_ms(1000.0);
	}
}



