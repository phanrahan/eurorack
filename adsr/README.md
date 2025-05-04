Changes

- Makefile
  - F_CPU 20 Mhz?
  - atmega88 to atmega168

- note fuse settings for m168p and m328p
  - calculated using http://www.engbedded.com/fusecalc/

Arduino pin assignments

- SUSTAIN_POT  A5
- RELEASE_POT  A4
- ATTACK_POT   A3
- DELAY_POT    A2
- ADSR_TIME    A1
- RELEASE_TIME A0

- ATTACK_LED  0
- SUSTAIN_LED 1
- DELAY_LED   2
- RELEASE_LED 3

- GATE 4

- SW0 6
- SW1 7

- EOC 9 (wired to default GATE)

- MCP4921
   SS   10
   MOSI 11
   MISO 12
   SCK  13

5 not used, could free up RX and TX by using these pins
8 not used
