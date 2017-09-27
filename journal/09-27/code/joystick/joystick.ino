/*
Adafruit Arduino - Lesson 16. Stepper
*/

#include <Stepper.h>

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

int joyPinX = 1;
int joyPinY = 0;
int joyPinC = 2;

// shift setup
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

byte leds = 0;  // byte that the shift shows

int posX = 0;
int posY = 0;
int sinceLast = 0;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

void setup()
{
  //set up stepper
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  //set up joystick
  pinMode(joyPinC, INPUT_PULLUP);

  // set up shift
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int joyX = analogRead(joyPinX);
  int joyY = analogRead(joyPinY);
  int joyC = digitalRead(joyPinC);
  
  //when the button is pressed, step
//  Serial.println(digitalRead(joyPinC) == HIGH);
//  Serial.println(analogRead(joyPinY));
  if(joyX > 800) {
    posX+=3;
  } else if(joyX < 200) {
    posX+=1;
  }

  if(joyY > 800) {
    posY+=3;
  } else if(joyY < 200) {
    posY+=1;
  }
  
  posX = posX % 4;
  posY = posY % 4;

  leds = 0;
  bitSet(leds, posX);
  bitSet(leds, posY+4);
  updateShiftRegister();

  Serial.println(joyC);
  if(digitalRead(joyPinC) == LOW && sinceLast > 10) {
    motor.setSpeed((16*(posY)+4*posX)+10);
//    motor.setSpeed(20);
    motor.step(500);
    sinceLast = 0;
  }
  
   
  sinceLast++;
  delay(100);
}

void updateShiftRegister() {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
