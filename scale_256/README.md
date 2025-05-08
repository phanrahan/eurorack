Generating scales

PWM 
- https://softsolder.com/2009/02/21/changing-the-arduino-pwm-frequency/
- https://playground.arduino.cc/Main/TimerPWMCheatsheet

5  6 - timer 0
9 10 - timer 1
3 11 - timer 2

The default frequency of the PWM signal on timer1 is 490 Hz.

The PWM frequency used in pwm.cpp is 62500 Khz!

Output is on pin 9

RC filter after PWM
R = 1 K
C = 1 uF
f = 15.923566879 Hz

