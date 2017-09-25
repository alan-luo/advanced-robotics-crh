/*
Adafruit Arduino - Lesson 14. Knob
*/

#include <Servo.h> 

int potPin = 1;  
int servoPin = 3;
Servo servo; 
 
void setup() 
{ 
  servo.attach(servoPin);  
  Serial.begin(9600);
} 
 
void loop() 
{ 
  int reading = analogRead(potPin);     // 0 to 1023
  Serial.println(reading);
  int angle = reading / 6;              // 0 to 180-ish
  servo.write(angle);  
} 
