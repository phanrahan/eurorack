#define STEPS 8
const int notes[] = { 4, 5, 6, 7, 8, 10, 11, 12 };
const int clock = 2;
const int note = 3;
const int gate = 13;
const int duration = A0;
//const int cv = 9;

unsigned clockstate = 0;
int step = 0;
unsigned long lastmillis = 0;

void clockisr()
{
    clockstate = 1;
}

void pulse(unsigned i)
{
    digitalWrite(gate,1);
    delay(i);
    digitalWrite(gate,0);
    //delay(n-i);
}

void setup() 
{
    Serial.begin(115200);

    for( int i = 0; i < STEPS; i++ ) {
        pinMode(notes[i], OUTPUT);
    }
    pinMode(duration, INPUT);
    pinMode(clock, INPUT);
    pinMode(note, INPUT);
    pinMode(gate, OUTPUT);
    //pinMode(cv, OUTPUT);

    attachInterrupt(0, clockisr, RISING);
}

void loop() 
{
    if( clockstate ) {
        clockstate = 0;

        unsigned long m = millis();
        unsigned long length = m - lastmillis;
        lastmillis = m;

        Serial.print("bpm: ");
        Serial.println(60000UL/length);

        unsigned d =  (length*analogRead(duration))/1023;

        digitalWrite(notes[step], 1);

        if( digitalRead(note) )
            pulse(d);
    
        digitalWrite(notes[step], 0);

        step = (step + 1) % STEPS;
    }
}
