Generating scales

PWM 
- https://softsolder.com/2009/02/21/changing-the-arduino-pwm-frequency/
- https://playground.arduino.cc/Main/TimerPWMCheatsheet

5  6 - timer 0
9 10 - timer 1
3 11 - timer 2

janostman
            pinMode(13, OUTPUT); //Gate is output
            pinMode(9, OUTPUT);  //CV is output
            pinMode(11, OUTPUT); //Audio output

The default frequency of the PWM signal on timer1 is 490 Hz.

This PWM frequency is much faster!

observe pwm signal on oscilloscope
- 16000000/8/3850 = 5-0 Hz
- 16000000/1/3850 = 4156 Hz
