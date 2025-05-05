/*
HAGIWO MOD1 LFO Ver1.0
Simple LFO. Various CV inputs allow you to create chaotic CVs.

--Pin assign---
POT1  A0  frequeny
POT2  A1  waveform seslect
POT3  A2  output level
F1    A3  frequency CV in
F2    A4  waveform CV in
F3    A5  output level CV in
F4    D11 output
BUTTON    change frequency range
LED       output
EEPROM    Saves the frequency range when the button is pressed
*/
#include <EEPROM.h>
#include "waves.h"

#define Brightness 64//Adjust according to the luminance of the LEDs used. Value range is 0-255

float lfoFrequeny = 0.1;
int waveHeight = 255;
int waveForm = 0;
float waveIndex = 0;
long outputValue = 0;
int outputLed = 0;
int freqRange = 1;

unsigned long previousMillis = 0;  // previous sample time
unsigned long currentMillis = 0;

bool lastButtonState = HIGH;             // last button sutate
unsigned long buttonPreviousMillis = 0;  // previous button pushed time
const unsigned long debounceDelay = 50;  // debounce time (msec)

void setup() {
  pinMode(4, INPUT_PULLUP);  //button setting
  pinMode(3, OUTPUT);        //LED setting
  pinMode(11, OUTPUT);

  freqRange = EEPROM.read(0);

  TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2B1);//fast PWM 62.5kHz setting
  TCCR2B = (1 << CS20);//fast PWM 62.5kHz setting
  TCCR1A = (1 << WGM11) | (1 << COM1A1);//fast PWM 62.5kHz setting
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);//fast PWM 62.5kHz setting
  ICR1 = 255;//fast PWM 62.5kHz setting

}

void loop() {
  currentMillis = millis();

  // Detection of button press
  int reading = digitalRead(4);
  if (currentMillis - buttonPreviousMillis > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {  // when button pusshed
      freqRange = (freqRange == 1) ? 10 : 1;
      EEPROM.write(0, freqRange);
      buttonPreviousMillis = currentMillis;
    }
  }
  lastButtonState = reading;

  int potValueA0 = analogRead(A0);  //frequency
  int CVValueA3 = analogRead(A3);   //frequency
  lfoFrequeny = min(potValueA0 + CVValueA3, 1023) * 0.0015 * freqRange;

  int potValueA1 = analogRead(A1);  //waveform
  int CVValueA4 = analogRead(A4);   //waveform
  waveForm = min(potValueA1 + CVValueA4, 1023);

  int potValueA2 = analogRead(A2);  //level
  int CVValueA5 = analogRead(A5);   //level
  waveHeight = min(potValueA2 / 4 + CVValueA5 / 4, 255);

  if (currentMillis - previousMillis >= 1) {
    previousMillis = currentMillis;

    if (waveForm <= 102) {
      outputValue = pgm_read_byte(&SinTable[(int)waveIndex]) * waveHeight / 255;
    } else if (waveForm <= 308) {
      outputValue = pgm_read_byte(&TriTable[(int)waveIndex]) * waveHeight / 255;
    } else if (waveForm <= 514) {
      outputValue = pgm_read_byte(&SquTable[(int)waveIndex]) * waveHeight / 255;
    } else if (waveForm <= 720) {
      outputValue = pgm_read_byte(&SawTable[(int)waveIndex]) * waveHeight / 255;
    } else if (waveForm <= 926) {
      outputValue = pgm_read_byte(&SawRevWaveTable[(int)waveIndex]) * waveHeight / 255;
    } else {
      outputValue = pgm_read_byte(&MaxTable[(int)waveIndex]) * waveHeight / 255;
    }

    analogWrite(11, outputValue);  //output LFO waveform
    analogWrite(3, (byte)outputValue *Brightness /255);  //output LED


    waveIndex = waveIndex + lfoFrequeny + 0.01;
    if (waveIndex >= TABLE_SIZE) {
      waveIndex -= TABLE_SIZE;
    }
  };
}

