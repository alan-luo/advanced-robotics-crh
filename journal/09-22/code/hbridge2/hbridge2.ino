//pins for hbridge
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int potPin = 0;

//pins for shift

int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

byte leds = 0;

void setup() {
  //set up hbridge pins
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  //set up shift pins
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);
}
void updateShiftRegister() {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void loop() {
  //hbridge
  //basically the whole 0-1023 range is output by the 10k pot
  int rawSpeed = analogRead(potPin);
  int speed = rawSpeed / 128;
  speed += 1; //make it from 1 - 8


  boolean reverse = speed > 4;
  int motorSpeed = 0;

  if(reverse) {
    motorSpeed = (rawSpeed - 512)/2;
  } else {
    motorSpeed = (512-rawSpeed) / 2;
  }

  setMotor(motorSpeed, reverse);

  //shift
  leds = 0;
  for(int i=0; i<speed; i++) {
    bitSet(leds, i);
  }
  
  updateShiftRegister();
}

void setMotor(int speed, boolean reverse) {
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}
