#include "IRLibAll.h"
 
//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);
 
//Create a decoder object 
IRdecode myDecoder;   

int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

long SLOW = 16720605;
long PAUSE = 16712445;
long FAST = 16761405;

byte leds = 0;
byte count = 0;

int delayAmount = 500;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  count = 0;

  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}


void loop() 
{
  updateShiftRegister();
  delay(delayAmount);
  leds = count;
  Serial.println(count);
  updateShiftRegister();
  
  count += 1;
  count = count % 128;

  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
//    Serial.println(myDecoder.value);
      if(myDecoder.value == FAST) {
       delayAmount = 250;
      } if(myDecoder.value == SLOW) {
        delayAmount = 1000;
      }
      if(myDecoder.value == PAUSE) {
        delayAmount = 500;
      }
      
    
    myReceiver.enableIRIn();      //Restart receiver
  }
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
