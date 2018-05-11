#include <SoftwareSerial.h>
// #include <AltSoftSerial.h>

SoftwareSerial Herbie(8,9); // permanently pins 8,9
int HR1 = 10; // 3
int EQ = 11; // 6
int DB = 3;// 5
int PP = 5; // 11
int HR2 = 6;  // 10
int rb = 0;
int i = 0, j = 255, k = 0;
char incomingByte = 0;
int HR1indicator = 0;
int EQindicator = 0;
int HR2indicator = 0;
int DBindicator = 0;
int PPindicator = 0;
int readbuffer[] = {0,0};
int incomingMsg;
bool status = false;
int fadeSpeed = 5;
int previousDB = 0, previousEQ = 0, previousHR1 = 0, previousHR2 = 0, previousP = 0;

void setup(){
  Serial.begin(9600);
  Herbie.begin(9600);
  pinMode(HR1, OUTPUT);
  pinMode(HR2, OUTPUT);
  pinMode(DB, OUTPUT);
  pinMode(EQ, OUTPUT);
  pinMode(PP, OUTPUT);
  analogWrite(HR1, 0);
  analogWrite(HR2, 0);
  analogWrite(DB, 0);
  analogWrite(EQ, 0);
  analogWrite(PP, 0);
}

void loop(){
  while (Herbie.available() > 0) {
    int sb = Herbie.read();
    delay(10);
    readbuffer[rb] = sb;
    rb++;
    if (rb == 2) {
      rb = 0;
      break;
    }
  }

  while (readbuffer[0] == 170) { // Hyper Red
    Serial.print(readbuffer[0]);
    Serial.print(", ");
    Serial.println(readbuffer[1]);
    i = readbuffer[1];
    for (int j = 0; j < 2; j++) {
      readbuffer[j] = 0;
      delay(1);
    }
    setColor(HR1, i, previousHR1);
    previousHR1 = i;
    i = 0;
    break;
  }

  while (readbuffer[0] == 187) { // Deep Blue
    Serial.print(readbuffer[0]);
    Serial.print(", ");
    Serial.println(readbuffer[1]);
    i = readbuffer[1];
    for (int j = 0; j < 2; j++) {
      readbuffer[j] = 0;
      delay(1);
    }
    setColor(DB, i, previousDB);
    previousDB = i;
    i = 0;
    break;
  }

  while (readbuffer[0] == 204) { // EQ
    Serial.print(readbuffer[0]);
    Serial.print(", ");
    Serial.println(readbuffer[1]);
    i = readbuffer[1];
    for (int j = 0; j < 2; j++) {
      readbuffer[j] = 0;
      delay(1);
    }
    setColor(EQ, i, previousEQ);
    previousEQ = i;
    i = 0;
    break;
  }

  while (readbuffer[0] == 221) { // Far Red
    Serial.print(readbuffer[0]);
    Serial.print(", ");
    Serial.println(readbuffer[1]);
    i = readbuffer[1];
    for (int j = 0; j < 2; j++) {
      readbuffer[j] = 0;
      delay(1);
    }
    setColor(HR2, i, previousHR2);
    previousHR2 = i;
    i = 0;
    break;
  }

  while (readbuffer[0] == 238) { // Purple
    Serial.print(readbuffer[0]);
    Serial.print(", ");
    Serial.println(readbuffer[1]);
    i = readbuffer[1];
    for (int j = 0; j < 2; j++) {
      readbuffer[j] = 0;
      delay(1);
    }
    setColor(PP, i, previousP);
    previousP = i;
        i = 0;
    break;
  }
}

void Off() {
  analogWrite(HR1, 0);
  analogWrite(HR2, 0);
  analogWrite(DB, 0);
  analogWrite(EQ, 0);
  analogWrite(PP, 0);
  previousDB = 0;
  previousP = 0;
  previousEQ = 0;
  previousHR1 = 0;
  previousHR2 = 0;
}

void setColor(int _Color, int _value, int _previousValue){
  if (_value < 0){
    _value = 0;
  }
  if (_value > 255){
    _value = 255;
  }
  if(_value > _previousValue){
    for(int c = _previousValue; c <= _value; c++){
      analogWrite(_Color, c);
      delay(fadeSpeed);
    }
  }
  else if(_value < _previousValue){
    for(int c = _previousValue; c >= _value; c--){
      analogWrite(_Color, c);
      delay(fadeSpeed);
    }
  }
}
