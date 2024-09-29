Simple keyboard

PWM

https://softsolder.com/2009/02/21/changing-the-arduino-pwm-frequency/

PWM - https://playground.arduino.cc/Main/TimerPWMCheatsheet
5  6 - timer 0
9 10 - timer 1
3 11 - timer 2

janostman
            pinMode(13, OUTPUT); //Gate is output
            pinMode(9, OUTPUT);  //CV is output
            pinMode(11, OUTPUT); //Audio output

The frequency of the PWM signal on most pins is approximately 490 Hz.

RC filter after PWM
R = 1 K
C = 1 uF
f = 15.923566879 Hz

AnalogWrite(cv, 50) = ~1V
