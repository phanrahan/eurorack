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

The PWM frequency in scale.ino is much faster!

RC filter after PWM
R = 1 K
C = 1 uF
f = 15.923566879 Hz


nano on osx
  * reinstalled prolific 2303 driver
  * needed to select OLD bootloader

* check signal on oscilloscope
  * measures 520 Hz
  * switch to div1
  * meaures 4167
  - tail after the signal goes to 0 ...
