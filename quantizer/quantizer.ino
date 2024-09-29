#include <SPI.h> 
#define NOTE_INPUT1         (1) //Quan01input 
#define NOTE_INPUT2         (2) //Quan02input 
#define NOTE_INPUT3         (3) //Quan03input 
#define NOTE_INPUT4         (4) //Quan04input 
#define SCALE_SELECTOR      (5) //ScaleSelect 

int quant1 = -1; 
int quant2 = -1; 
int quant3 = -1; 
int quant4 = -1; 
const int gatePin = 4; // gate out 
const int ledPin = 7;  // LED 
const int clkPin = 2;  // clock input 
volatile int clkState = HIGH; 

uint16_t midiTable[] = { 
//  C    C#     D     D#    E     F   F#    G    G#     A    A#      B 
    0,   1,     2,    3,    4,    5,   6,   7,    8,    9,   10,    11, //0 
   12,   13,   14,   15,   16,   17,  18,  19,   20,   21,   22,    23, //12 
   24,   25,   26,   27,   28,   29,  30,  31,   32,   33,   34,    35, //24 
   36,   37,   38,   39,   40,   41,  42,  43,   44,   45,   46,    47, //36 
   48,   49,   50,   51,   52,   53,  54,  55,   56,   57,   58,    59, //48 
   60                                                                   //60 
}; 

uint16_t mapMidi(uint16_t input) { 
  return (midiTable[(input)]); 
} 

uint16_t majTable[] = { 
     0,  2,  4,  5,  7,  9, 11, //scale01 Major 
    12, 14, 16, 17, 19, 21, 23, 
    24, 26, 28, 29, 31, 33, 35, 
    36, 38, 40, 41, 43, 45, 47, 
    48, 50, 52, 53, 55, 57, 59, 
    60 
}; 

uint16_t minTable[] = { 
    0,  2,  3,  5,  7,  8, 10, //scale02 Minor 
   12, 14, 15, 17, 19, 20, 22, 
   24, 26, 27, 29, 31, 32, 34, 
   36, 38, 39, 41, 43, 44, 46, 
   48, 50, 51, 53, 55, 56, 58, 
   60 
}; 

uint16_t pentaTable[] = { 
    0,  2,  3,  5,  7, 10,     //scale03 Pentatonic 
   12, 14, 15, 17, 19, 22, 
   24, 26, 27, 29, 31, 34, 
   36, 38, 39, 41, 43, 46, 
   48, 50, 51, 53, 55, 58, 
   60 
}; 

uint16_t dorianTable[] = { 
     0,  2,  3,  5, 7,  9,  10, //scale04 Dorian 
    12, 14, 15, 17, 19, 21, 22, 
    24, 26, 27, 29, 31, 33, 34, 
    36, 38, 39, 41, 43, 45, 46, 
    48, 50, 51, 53, 55, 57, 58, 
    60 
}; 

uint16_t maj3rdTable[] = { 
    0, 4,  7, 11,              //scale05Maj7(9) 
   12, 16, 19, 23, 
   24, 26, 31, 35, 
   36, 40, 43, 47, 
   48, 50, 54, 55,  59, 
   60  
}; 

uint16_t min3rdTable[] = { 
    0,   3,   7,  10,          //scale06 Minor7(9,11) 
   14,  15,  19,  22, 
   24,  26,  27,  31,  34, 
   36,  39,  41,  46, 
   48,  50,  51,  55,  58, 
   60      
}; 

uint16_t whTable[] = { 
    0,   2,   4,   6,   8,  10, //scale07 (WholeTone) 
   12,  14,  16,  18,  20,  22, 
   24,  26,  28,  30,  32,  34, 
   36,  38,  40,  42,  44,  46, 
   48,  50,  52,  54,  56,  58, 
   60 
}; 

uint16_t chromaTable[] = { 
    0, 
    1,  2,  3,  4,  5,  6,  7,  8, 9,  10, 11, 12, //scale08 Chromatic 
   13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
   25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 
   37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 
   49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 
   60 
}; 

uint8_t SelectTable[]={0,1,2,3,4,5,6,7,8,9,10,11,12}; 

uint16_t ScaleSelect(uint16_t input) { 
  uint8_t value = (input) / (1024/7); 
  return (SelectTable[value]); 
} 

uint16_t mapMaj(uint16_t input) { 
  uint8_t value = (input) / 36; 
  return(majTable[value]);      
} 

uint16_t mapMin(uint16_t input) { 
  uint8_t value = (input) / 36; 
  return(minTable[value]); 
} 

uint16_t mapPenta(uint16_t input) { 
  uint8_t value = (input) / 42; 
  return (pentaTable[value]); 
} 

uint16_t mapDorian(uint16_t input) { 
  uint8_t value = (input) / 36; 
  return (dorianTable[value]); 
} 

uint16_t mapMaj3rd(uint16_t input) { 
  uint8_t value = (input) / 61; 
  return (maj3rdTable[value]); 
} 

uint16_t mapMin3rd(uint16_t input) { 
  uint8_t value = (input) / 59; 
  return (min3rdTable[value]); 
} 

uint16_t mapWh(uint16_t input) { 
  uint8_t value = (input) / 42; 
  return(whTable[value]); 
} 

uint16_t mapChromatic(uint16_t input) { 
  uint8_t value = (input) / 21; 
  return(chromaTable[value]); 
} 


int deJitter(int v, int test){  
  if (abs(v - test) > 19) { 
    return v; 
  } 
  return test; 
} 

void sendNote1(int key) { 
  int pitch1 = 0xa00L * key / 30.3; 
  digitalWrite(10, LOW); 
  SPI.transfer(0x10 + (pitch1 >> 8)); //DAC a OUTA 
  SPI.transfer(pitch1 & 0xff); 
  digitalWrite(10, HIGH); 
} 

void sendNote2(int key2) { 
  int pitch2 = 0xa00L * key2 / 30.3; 
  digitalWrite(10, LOW); 
  SPI.transfer(0x90 + (pitch2 >> 8)); //DAC a OUTB 
  SPI.transfer(pitch2 & 0xff); 
  digitalWrite(10, HIGH); 
} 

void sendNote3(int key3) { 
  int pitch3 = 0xa00L * key3 / 30.3; 
  digitalWrite(9, LOW); 
  SPI.transfer(0x10 + (pitch3 >> 8)); //DAC b OUTA 
  SPI.transfer(pitch3 & 0xff); 
  digitalWrite(9, HIGH); 
} 

void sendNote4(int key4) { 
  int pitch4 = 0xa00L * key4 / 30.3; 
  digitalWrite(9, LOW); 
  SPI.transfer(0x90 + (pitch4 >> 8)); //DAC b OUTB 
  SPI.transfer(pitch4 & 0xff); 
  digitalWrite(9, HIGH); 
} 

void my_interrupt_handler() 
{ 
  static unsigned long last_interrupt_time = 0; 
  unsigned long interrupt_time = micros(); 

  if (interrupt_time - last_interrupt_time > 100) 
  { 
      clkState = LOW; 
  } 
  last_interrupt_time = interrupt_time; 
} 

void setup() { 
  SPI.begin(); 
  SPI.setBitOrder(MSBFIRST); 
  SPI.setDataMode(SPI_MODE0); 
  SPI.setClockDivider(SPI_CLOCK_DIV128); 
  pinMode(ledPin,OUTPUT); 
  digitalWrite(7,HIGH); 
  pinMode(9,OUTPUT);  //select dacB SS Pin 
  pinMode(10,OUTPUT); //select dacA SS Pin 
  digitalWrite(9,HIGH); 
  digitalWrite(10,HIGH); 
  pinMode(gatePin, OUTPUT); 
  pinMode(clkPin, INPUT); 
  attachInterrupt(0, my_interrupt_handler, LOW); 
} 

void loop() { 
    uint16_t  tmp_midi_note1; 
    uint16_t  tmp_midi_note2; 
    uint16_t  tmp_midi_note3; 
    uint16_t  tmp_midi_note4; 

    uint16_t  tmp_read1 = deJitter(analogRead(NOTE_INPUT1), quant1); 
    uint16_t  tmp_read2 = deJitter(analogRead(NOTE_INPUT2), quant2); 
    uint16_t  tmp_read3 = deJitter(analogRead(NOTE_INPUT3), quant3); 
    uint16_t  tmp_read4 = deJitter(analogRead(NOTE_INPUT4), quant4); 
    uint8_t   tmp_scale = ScaleSelect(analogRead(SCALE_SELECTOR)); 
    
    quant1 = tmp_read1; 
    quant2 = tmp_read2; 
    quant3 = tmp_read3; 
    quant4 = tmp_read4; 
              
  if (clkState == LOW) { 
      clkState = HIGH; 
      digitalWrite(ledPin, LOW); 
      digitalWrite(gatePin, LOW); 
      
  switch(tmp_scale){ 
     case  0: 
       tmp_midi_note1 = mapMaj(tmp_read1); 
       tmp_midi_note2 = mapMaj(tmp_read2); 
       tmp_midi_note3 = mapMaj(tmp_read3); 
       tmp_midi_note4 = mapMaj(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  1: 
       tmp_midi_note1 = mapMin(tmp_read1); 
       tmp_midi_note2 = mapMin(tmp_read2); 
       tmp_midi_note3 = mapMin(tmp_read3); 
       tmp_midi_note4 = mapMin(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  2: 
       tmp_midi_note1 = mapPenta(tmp_read1); 
       tmp_midi_note2 = mapPenta(tmp_read2); 
       tmp_midi_note3 = mapPenta(tmp_read3); 
       tmp_midi_note4 = mapPenta(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  3: 
       tmp_midi_note1 = mapDorian(tmp_read1); 
       tmp_midi_note2 = mapDorian(tmp_read2); 
       tmp_midi_note3 = mapDorian(tmp_read3); 
       tmp_midi_note4 = mapDorian(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  4: 
       tmp_midi_note1 = mapMaj3rd(tmp_read1); 
       tmp_midi_note2 = mapMaj3rd(tmp_read2); 
       tmp_midi_note3 = mapMaj3rd(tmp_read3); 
       tmp_midi_note4 = mapMaj3rd(tmp_read4); 
        
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  5: 
       tmp_midi_note1 = mapMin3rd(tmp_read1); 
       tmp_midi_note2 = mapMin3rd(tmp_read2); 
       tmp_midi_note3 = mapMin3rd(tmp_read3); 
       tmp_midi_note4 = mapMin3rd(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  6: 
       tmp_midi_note1 = mapWh(tmp_read1); 
       tmp_midi_note2 = mapWh(tmp_read2); 
       tmp_midi_note3 = mapWh(tmp_read3); 
       tmp_midi_note4 = mapWh(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
       break; 
        
     case  7: 
       tmp_midi_note1 = mapChromatic(tmp_read1); 
       tmp_midi_note2 = mapChromatic(tmp_read2); 
       tmp_midi_note3 = mapChromatic(tmp_read3); 
       tmp_midi_note4 = mapChromatic(tmp_read4); 
        
       sendNote1(tmp_midi_note1); 
       sendNote2(tmp_midi_note2); 
       sendNote3(tmp_midi_note3); 
       sendNote4(tmp_midi_note4); 
     default: 
     break; 
    } 
    } else { 
     digitalWrite(ledPin, HIGH); 
     digitalWrite(gatePin, HIGH); 
  } 
} 

