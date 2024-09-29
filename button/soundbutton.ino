const int buttonPin = 2;
const int potPin = A0;

const int gatePin = 3;
const int cvPin = 9;

void setup() 
{
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(potPin, INPUT);

    pinMode(gatePin, OUTPUT);
    pinMode(cvPin, OUTPUT);
}

void loop() 
{
    // 1 Octave
    analogWrite(cvPin, analogRead(potPin) / 20); 

    // 2 Octave
    // analogWrite(cvPin, analogRead(potPin) / 10); 

    // 3 Octave
    // analogWrite(cvPin, analogRead(potPin) / 5); 

    digitalWrite(gatePin, digitalRead(buttonPin));
}
