#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo pinkyFinger;
//Servo thumb;

Servo fingers[] = {indexFinger, middleFinger, ringFinger, pinkyFinger};

//RF24 radio(7, 8);
//const byte addresses[][6] = {"00001", "00002"};

int indexMin = 104, indexMax = 180;
int middleMin = 0, middleMax = 67;
int ringMin = 115, ringMax = 178;
int pinkyMin = 125, pinkyMax = 175;
int thumbMin = 90, thumbMax = 180;

//Limits for fingers:

//Index finger 180-104
//Middle finger 0-67
//Ring finger 115-178
//Pinky finger 125-175
//Thumb 90-180

boolean indexClosed = true, middleClosed = true, ringClosed = true, pinkyClosed = true;

int moveDelay = 4;

void indexOpen()
{
  indexFinger.write(indexMax);
  delay(moveDelay * 3);
}

void indexClose()
{
  indexFinger.write(indexMin);
  delay(moveDelay * 3);
}

void middleClose()
{
  middleFinger.write(middleMax);
  delay(moveDelay * 3);
}

void middleOpen()
{
  middleFinger.write(middleMin);
  delay(moveDelay * 3);
}

void ringOpen()
{
  ringFinger.write(ringMax);
  delay(moveDelay * 3);
}

void ringClose()
{
  ringFinger.write(ringMin);
  delay(moveDelay * 3);
}

void pinkyOpen()
{
  pinkyFinger.write(pinkyMax);
  delay(moveDelay * 3);
}

void pinkyClose()
{
  pinkyFinger.write(pinkyMin);
  delay(moveDelay * 3);
}
/*
void thumbOpen()
{
  thumb.write(thumbMax);
  delay(moveDelay * 3);
}

void thumbClose()
{
  thumb.write(thumbMax);
  delay(moveDelay * 3);
}
*/
void closeHand()
{
  //thumbClose();
  pinkyClose();
  ringClose();
  middleClose();
  indexClose();
}

void openHand()
{
  pinkyOpen();
  ringOpen();
  middleOpen();
  indexOpen();
  //thumbOpen();
}

void gotEm()
{
  openHand();
  indexClose();
}

void rockOn()
{
  closeHand();
  pinkyOpen();
  indexOpen();
}

void wave()
{
  pinkyClose();
  ringClose();
  middleClose();
  pinkyOpen();
  indexClose();
  ringOpen();
  middleOpen();
  indexOpen();
}

void setOpen()
{
  openHand();
  delay(moveDelay * 4);
}

void trial()
{
  openHand();
  delay(1000);
  closeHand();
  delay(1000);
  gotEm();
  delay(1000);
  indexOpen();
  rockOn();
  delay(1000);
  openHand();
  delay(1000);
  indexClose();
  delay(500);
  indexOpen();
  delay(500);
  ringClose();
  delay(500);
  ringOpen();
  delay(500);
  middleClose();
  delay(500);
  middleOpen();
  delay(500);
  pinkyClose();
  delay(500);
  pinkyOpen();
  delay(500);
}

int i = 0;
int maxFinger = 4;

void setup() 
{
  indexFinger.attach(2);
  middleFinger.attach(3);
  ringFinger.attach(4);
  pinkyFinger.attach(5);
  //thumb.attach(6);

  /*
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MAX);
  */
  
  setOpen();
}

void loop()
{
  trial();
}
