#include <Servo.h>
/*
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
*/

Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo pinkyFinger;
//Servo thumb;

//RF24 radio(7, 8); // CE, CSN
//const byte addresses[][6] = {"00001", "00002"};

int indexMin = 104, indexMax = 180;
int middleMin = 0, middleMax = 67;
int ringMin = 115, ringMax = 178;
int pinkyMin = 125, pinkyMax = 175;
int thumbMin = 90, thumbMax = 180;

//Index finger 180-104
//Middle finger 0-67
//Ring finger 115-178
//Pinky finger 125-175
//Thumb 90-180

boolean indexClosed = true, middleClosed = true, ringClosed = true, pinkyClosed = true;

int moveDelay = 4;

void indexOpen()
{
  if(indexClosed)
  {
    for(int i = indexMin; i <= indexMax; i++)
    {
      indexFinger.write(i);
      delay(moveDelay);
    }
    indexClosed = false;
  }
}

void indexClose()
{
  if(!indexClosed)
  {
    for(int i = indexMax; i >= indexMin; i--)
    {
      indexFinger.write(i);
      delay(moveDelay);
    }
    indexClosed = true;
  }
}

void middleClose()
{
  if(!middleClosed)
  {
    for(int i = middleMin; i <= middleMax; i++)
    {
      middleFinger.write(i);
      delay(moveDelay);
    }
    middleClosed = true;
  }
}

void middleOpen()
{
  if(middleClosed)
  {
    for(int i = middleMax; i >= middleMin; i--)
    {
      middleFinger.write(i);
      delay(moveDelay);
    }
    middleClosed = false;
  }
}

void ringOpen()
{
  if(ringClosed)
  {
    for(int i = ringMin; i <= ringMax; i++)
    {
      ringFinger.write(i);
      delay(moveDelay);
    }
    ringClosed = false;
  }
}

void ringClose()
{
  if(!ringClosed)
  {
    for(int i = ringMax; i >= ringMin; i--)
    {
      ringFinger.write(i);
      delay(moveDelay);
    }
    ringClosed = true;
  }
}

void pinkyOpen()
{
  if(pinkyClosed)
  {
    for(int i = pinkyMin; i <= pinkyMax; i++)
    {
      pinkyFinger.write(i);
      delay(moveDelay);
    }
    pinkyClosed = false;
  }
}

void pinkyClose()
{
  if(!pinkyClosed)
  {
    for(int i = pinkyMax; i >= pinkyMin; i--)
    {
      pinkyFinger.write(i);
      delay(moveDelay);
    }
    pinkyClosed = true;
  }
}
/*
void thumbOpen()
{
  thumb.write(thumbMax);
  delay(moveDelay * 4);
}

void thumbClose()
{
  thumb.write(thumbMax);
  delay(moveDelay * 4);
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

void bigBird()
{
  closeHand();
  middleOpen();
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
  indexFinger.write(indexMax);
  middleFinger.write(middleMin);
  ringFinger.write(ringMax);
  pinkyFinger.write(pinkyMax);
  delay(moveDelay * 4);
}

int potpin = 0;
int val;

boolean buttonState = 0;
int button = 9;

int angles[] = {0, 0, 0, 0, 0};
Servo fingers[] = {indexFinger, middleFinger, ringFinger, pinkyFinger};

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
/*
void sendFinger(int f)
{
  radio.stopListening();
  radio.write(&f, sizeof(f));
}

void writeFinger(int f, int a)
{
  fingers[f].write(a);
}
*/

int i = 0;
int maxFinger = 4;

void setup() {
  indexFinger.attach(2);
  middleFinger.attach(3);
  ringFinger.attach(4);
  pinkyFinger.attach(5);
  //thumb.attach(6);
  //Serial.begin(9600);
  /*
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MAX);
  */
  setOpen();
  //setClose();
}

void loop() 
{ 
  /*
  delay(5);
  sendFinger(i);
  radio.startListening();
  while(!radio.available());
  int angle = 0;
  radio.read(&angle, sizeof(angle));
  writeFinger(i, angle);
  i = (i > maxFinger ? 0 : i + 1);
  */

  trial();
}
