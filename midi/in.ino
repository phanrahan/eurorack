// midi_in_test.ino
// version 2015-06-01
// Arduino MIDI tutorial
// by Staffan Melin
// http://libremusicproduction.com/

// constants


#define PIN_LED 13

#define MIDI_NOTE_ON 144
byte midiByte;
byte midiChannel;
byte midiCommand;

void setup() {
    Serial.begin(31250);
    delay(100);

    pinMode(PIN_LED, OUTPUT);
}

void loop () {

    // Is there any MIDI waiting to be read?
    if (Serial.available() > 0) {

        // read MIDI byte
        midiByte = Serial.read();
    
        // remove channel info
        midiChannel = midiByte & B00001111;
        midiCommand = midiByte & B11110000;

        // if it is a MIDI note on commannd, blink the LED    
        if (midiCommand == MIDI_NOTE_ON)
        {
            digitalWrite(PIN_LED, HIGH);
            delay(100);
            digitalWrite(PIN_LED, LOW);
        }
    }

}
