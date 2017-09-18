#include "IRLibAll.h"

// IR setup here
IRrecvPCI myReceiver(2); //Create a receiver object to listen on pin 2
IRdecode myDecoder; //Create a decoder object 

int trigPin = 11;    //Trig - green Jumper
int echoPin = 12;    //Echo - yellow Jumper
long duration, cm, inches;

const int MODE_ULTRA = 254;
const int MODE_IR = 253;

const long ZERO =   16753245;
const long ONE =    16720605;
const long TWO =    16769055;
const long THREE =  16738455;
const long FOUR =   16724175;
const long FIVE =   16716015;
const long SIX =    16728765;

 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  // set up IR stuff
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}
 
void loop() {
  // ------- set up ultrasonic -------
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;

  Serial.write(MODE_ULTRA);
  delay(50);
  Serial.write(cm);
  delay(50);

  // ---------- set up IR ---------
  byte irvalue = 0;

  if (myReceiver.getResults()) {
    myDecoder.decode();
    // set one of three speeds depending on what was pressed
    if(myDecoder.value == ONE) {
      irvalue = 10;
    } else if(myDecoder.value == TWO) {
      irvalue = 15;
    } else if(myDecoder.value == THREE) {
      irvalue = 20;
    } else if(myDecoder.value == FOUR) {
      irvalue = 25;
    } else if(myDecoder.value == FIVE) {
      irvalue = 30;
    } else if(myDecoder.value == SIX) {
      irvalue = 35;
    } else if(myDecoder.value == ZERO) {
      irvalue = 40;
    }
    Serial.write(MODE_IR);
    delay(50);
    Serial.write(irvalue);
    
    myReceiver.enableIRIn(); //Restart receiver
  }
  
  delay(30);
}
