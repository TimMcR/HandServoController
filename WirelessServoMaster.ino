#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 12
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

int mins[] = {104, 67, 115, 125, 90};
int maxes[] = {180, 0, 178, 175, 180};
boolean buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MAX);
}

int values[] = {1023, 1023, 1023, 1023, 1023};
int angles[] = {maxes[0], maxes[1], maxes[2], maxes[3], maxes[4]};

const int flexMin = 760, flexMax = 900;

int myMap(int x, int inMin, int inMax, int outMin, int outMax)
{
  return map(constrain(x, inMin, inMax), inMin, inMax, outMin, outMax);
}

void readSensors()
{
  values[0] = analogRead(A0);
  values[1] = analogRead(A1);
  values[2] = analogRead(A2);
  values[3] = analogRead(A3);
  values[4] = analogRead(A4);
  for(int i = 0; i < 5; i++)
  {
    angles[i] = myMap(values[i], flexMin, flexMax, maxes[i], mins[i]);
  }
}

void loop() { 
  delay(5);
  radio.startListening();
  while(!radio.available());
  readSensors();
  int f = 0;
  radio.read(&f, sizeof(f));
  radio.stopListening();
  radio.write(&angles[f], sizeof(angles[f]));
}
