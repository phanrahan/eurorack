const int key = 2;
const int pot = A0;
const int gate = 3;
const int cv = 9;
int voltage = 0;

void setup() 
{
   //pinMode(key, INPUT_PULLUP);
   //pinMode(pot, INPUT);

   pinMode(gate, OUTPUT);
   pinMode(cv, OUTPUT);
}

void loop() 
{
    //while( digitalRead(key) ) ;
    //analogWrite(cv, analogRead(pot) >> 2);
    //digitalWrite(gate, 1);
    //while( !digitalRead(key) ) ;
    //digitalWrite(gate, 0);

    analogWrite(cv, voltage);
    voltage = (voltage + 4) % 48;
    digitalWrite(gate, 1);
    delay(30);
    digitalWrite(gate, 0);
    delay(220);
}
