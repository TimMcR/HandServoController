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
  for(int i = 0; i < 5; i++)
  {
    angles[i] = myMap(values[0], flexMin, flexMax, maxes[i], mins[i]);
  }
}

void loop() { 
  delay(5);
  radio.stopListening();
  readSensors();
  for(int i = 0; i < 4; i++)
  {
    radio.write(&angles[i], sizeof(angles[i]));
    Serial.println(angles[i]);
  }  
}
