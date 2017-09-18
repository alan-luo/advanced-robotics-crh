#include "IRLibAll.h"
 

// IR setup here
IRrecvPCI myReceiver(2); //Create a receiver object to listen on pin 2
IRdecode myDecoder; //Create a decoder object 

// shift setup
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

// IR constants
long SLOW = 16720605;
long PAUSE = 16712445;
long FAST = 16761405;

byte leds = 0;  // byte that the shift shows
byte count = 0; // current count

int delayAmount = 500; // interval length in ms

void setup() {
  // set up shift
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  // initialize count
  count = 0;

  // set up IR stuff
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}


void loop()  {
  // update shift with new value
  updateShiftRegister();
  delay(delayAmount);
  leds = count;
  updateShiftRegister();
  
  // increment and prevent overflow
  count += 1;
  count = count % 256;

  // IR code
  if (myReceiver.getResults()) {
    myDecoder.decode();
    // set one of three speeds depending on what was pressed
    if(myDecoder.value == FAST) {
     delayAmount = 250;
    } else if(myDecoder.value == SLOW) {
      delayAmount = 1000;
    } else if(myDecoder.value == PAUSE) {
      delayAmount = 500;
    }

    myReceiver.enableIRIn(); //Restart receiver
  }
}

// shift helper function
void updateShiftRegister() {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
