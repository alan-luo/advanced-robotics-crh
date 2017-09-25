#include <Servo.h> 
#include "IRLibAll.h"

// IR setup here
IRrecvPCI myReceiver(2); //Create a receiver object to listen on pin 2
IRdecode myDecoder; //Create a decoder object 

const long ZERO = 16738455;
const long ONE  = 16724175;
const long TWO  = 16718055;
const long THREE= 16743045;
const long FOUR = 16716015;
const long FIVE = 16726215;
const long SIX  = 16734885;
const long SEVEN= 16728765;
const long EIGHT= 16730805;
const long NINE = 16732845;


// shift setup
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

byte leds = 0;  // byte that the shift shows

//servo pins
int potPin = 1;  
int servoPin = 3;
Servo servo;
int angle = 0;

//running number stream
const int combo_length = 4;
int combo[combo_length] = {};
int trueCombo[4] = {1, 2, 3, 4};
 
void setup() {
  // set up shift
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  // set up IR stuff
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));

  //set up combination
  for(int i=0; i<combo_length; i++) {
    combo[i] = 0;
  }
  
  //servo 
  servo.attach(servoPin);

  Serial.begin(9600);
}
boolean checkCombo() {
  for(int i=0; i<combo_length; i++) {
    if(combo[i]!=trueCombo[i]) {
      return false;
    }
  }
  return true;
}

void registerValue(int number) {
  leds = 0;
  updateShiftRegister();
  delay(100);
  
  leds = number; // write to shift

  //write number to stream
  for(int i=0; i<combo_length-1; i++) {
    combo[i] = combo[i+1];
  }
  combo[combo_length-1] = number;

  // log a 4-digit combination
//  Serial.print(combo[0]);
//  Serial.print(combo[1]);
//  Serial.print(combo[2]);
//  Serial.print(combo[3]);
//  Serial.println();
  if(checkCombo()) {
    angle = 0;
  } else {
     angle = 170;
  }
}
void loop() { 
  servo.write(angle); // set servo

  
  // IR code
  
  if (myReceiver.getResults()) {
    myDecoder.decode();
    
    //for dumping IR values
//    Serial.println(myDecoder.value);

    //this can be done with an array to be much more elegant, but I was kind of lazy
    //    - this also makes testing individual IR values a lot easier
    if(myDecoder.value==ZERO) { registerValue(0); } 
    else if (myDecoder.value==ONE) {   registerValue(1); }
    else if (myDecoder.value==TWO) {   registerValue(2); }
    else if (myDecoder.value==THREE) { registerValue(3); }
    else if (myDecoder.value==FOUR) {  registerValue(4); }
    else if (myDecoder.value==FIVE) {  registerValue(5); }
    else if (myDecoder.value==SIX) {   registerValue(6); }
    else if (myDecoder.value==SEVEN) { registerValue(7); }
    else if (myDecoder.value==EIGHT) { registerValue(8); }
    else if (myDecoder.value==NINE) {  registerValue(9); }

    myReceiver.enableIRIn(); //Restart receiver
  }

  updateShiftRegister();
} 

// shift helper function
void updateShiftRegister() {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
