#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

AltSoftSerial Herbie; // permanently pins 8,9
int HR1 = 11; // 3
int EQ = 3; // 6
int DB = 6;// 5
int PP = 5; // 11
int HR2 = 10;  // 10
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

  // while (Serial.available() > 0) {
  //   char c = Serial.read();
  //   incomingMsg = atoi(c);
  //   Serial.println(incomingMsg);
  //   delay(1);
  //   break;
  // }
  //
  // while(incomingMsg >= 0 && incomingMsg < 256){
  //   int j = incomingMsg;
  //   analogWrite(DB, j);
  //   delay(1);
  //   j = 0;
  //   break;
  // }
  //
  // while(incomingMsg >= 300 && incomingMsg < 556){
  //   incomingMsg = incomingMsg - 300;
  //   int j = incomingMsg;
  //   analogWrite(EQ, j);
  //   delay(1);
  //   j = 0;
  //   break;
  // }
  //
  while (readbuffer[0] == 170) { // Hyper Red
    Serial.print(readbuffer[0]);
    Serial.print(", ");
    Serial.println(readbuffer[1]);
    i = readbuffer[1];
    for (int j = 0; j < 2; j++) {
      readbuffer[j] = 0;
      delay(1);
    }
    analogWrite(HR1, i);
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
    analogWrite(DB, i);
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
    analogWrite(EQ, i);
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
    analogWrite(HR2, i);
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
    analogWrite(PP, i);
    i = 0;
    break;
  }
}


void Off() {
  j = 255;
  while (j >= 0) {
    if ( HR1indicator == 1) {
      analogWrite(HR1, j);
    }
    if ( HR2indicator == 1) {
      analogWrite(HR2, j);
    }
    if ( DBindicator == 1) {
      analogWrite(DB, j);
    }
    if ( EQindicator == 1) {
      analogWrite(EQ, j);
    }
    j--;
    delay(10);
    if (j == 0) {
      HR1indicator = 0;
      EQindicator = 0;
      HR2indicator = 0;
      DBindicator = 0;
      break;
    }
  }
}

// bool Brighten(int _color, int _z, int _max, int _speed){ // LED string, start, end, speed
//   for(_z; _z <= _max; _z++){
//     if(_z < 0){_z = 0;}
//     if(_z > 255){_z = 255;}
//     analogWrite(_color, _z);
//     delay(_speed);
//   }
//   return status = true;
// }
//
// bool Dim(int _color, int _z, int _min, int _speed){ // LED string, start, end, speed
//   for(_z; _z >= _min; _z--){
//     if(_z < 0){_z = 0;}
//     if(_z > 255){_z = 255;}
//     analogWrite(_color, _z);
//     delay(_speed);
//   }
//   return status = false;
// }
