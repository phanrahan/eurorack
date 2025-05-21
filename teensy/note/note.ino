#include <USBHost_t36.h>

const int LED = 13;
const int in_1 = 15;
const int in_2 = 16;
const int gate_1 = 2;
const int gate_2 = 3;
const int gate_3 = 4;
const int gate_4 = 5;
const int cv_out_2 = A21;
const int cv_out_1 = A22;

USBHost myusb;
//USBHub hub1(myusb);
//USBHub hub2(myusb);
MIDIDevice midi1(myusb);

void setup() {
  analogWriteResolution(8);
  analogReadResolution(3);
  pinMode(in_2, INPUT);
  pinMode(gate_1, OUTPUT);
  pinMode(gate_2, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWriteFast(LED, HIGH);
  Serial.begin(57600);
  delay(1500);
  myusb.begin();
  //midi1.setHandleControlChange(myControlChange);
  midi1.setHandleNoteOn(myNoteOn);
  midi1.setHandleNoteOff(myNoteOff);
}

void loop() {
  myusb.Task();
  midi1.read();

  /*
  current_reading = analogRead(A1);

  data = digitalReadFast(in_2);


  if (data != clock_tick) {
    clock_tick = data;
    if (clock_tick == 1) {
      digitalWriteFast(LED, HIGH);
      doClock();
    }
    else if (clock_tick == 0) {
      digitalWriteFast(LED, LOW);
      doClockOff();
    }
  }
  */
}
/*
void myControlChange(byte channel, byte control, byte value) {
  if (channel == 1) {
    if (control >= 70 && control <= 77) {
      Serial.print(control); 
      Serial.print(" ");
      Serial.println(value); 
      control = control - 70; 
      knobs[control] = value;
    }
  }
}
*/

void myNoteOn(byte channel, byte note, byte velocity) {
  if (channel == 10) {
    if (note >= 36 && note <= 43) {
      Serial.print(note); 
      Serial.print(" ");
      Serial.println(velocity); 
      note = note - 36; 
      int value = note * 255.0/(12*3.3); // map octave to 0 .. 1 V output
      analogWrite(cv_out_1, value);
      analogWrite(cv_out_2, value);
      digitalWriteFast(gate_1, HIGH);
      digitalWriteFast(gate_2, HIGH);
      digitalWriteFast(LED, HIGH);
    }
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  if (channel == 10) {
    if (note >= 36 && note <= 43) {
      Serial.print(note); 
      Serial.print(" ");
      Serial.println(velocity); 
      digitalWriteFast(gate_1, LOW);
      digitalWriteFast(gate_2, LOW);
      digitalWriteFast(LED, LOW);
    }
  }
}

