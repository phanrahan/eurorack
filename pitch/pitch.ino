const int potPin = A0;
const int cvPin = 9;

void setup() 
{
    pinMode(potPin, INPUT);
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
}
