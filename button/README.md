Gate controlled by button 

Control voltage set with potentiometer

PWM - https://playground.arduino.cc/Main/TimerPWMCheatsheet
5  6 - timer 0
9 10 - timer 1
3 11 - timer 2

The default Arduino frequency of the PWM signal from timer1 is ...
  16000000/64/2/256 = 488.28125000000000000000
  divide clock by 64
  divide by 2 because it is phase correct PWM
  256 widths

AnalogWrite(cv, 50) = ~1V
   1023/20 = 51

RC filter after PWM
R = 1 K
C = 1 uF
f = 15.923566879 Hz

