#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
 * This is the code for controlling the animatronic hand
 * Right now it runs automatically with prewritten code, however there is some code that can allow you to control it with a seperate Arduino over radio
 */

//These are the servo objects, right now the thumb is commented out because it hasn't been working properly
Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo pinkyFinger;
//Servo thumb;

//This is the radio, which we use to communicate with another Arduino
RF24 radio(7, 8);
const byte addresses[][6] = {"00001", "00002"};

#define LED 9

//These are the limits for each servo, I found them out by using a potentiometer, however they may need to be updated
int indexMin = 104, indexMax = 180;
int middleMin = 0, middleMax = 67;
int ringMin = 115, ringMax = 178;
int pinkyMin = 125, pinkyMax = 175;
int thumbMin = 90, thumbMax = 180;

//This is the standard delay time between each finger movemend
int moveDelay = 20;

//These are the methods to open and close each finger
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

//These methods combine multiple other methods in order to form a specific hand position
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

//This is our standard procedure for events and for testing
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

void setup() 
{
  indexFinger.attach(2);
  middleFinger.attach(3);
  ringFinger.attach(4);
  pinkyFinger.attach(5);
  //thumb.attach(6);

  
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MAX);
  
  pinMode(LED, OUTPUT);
  
  setOpen();
}

void loop()
{
  if(radio.available())
  {
     digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
    
  trial();
}
