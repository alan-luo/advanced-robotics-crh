const int buzzer = 3; //buzzer to arduino pin 9

// shift setup
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

byte leds = 0;  // byte that the shift shows

void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

  // set up shift
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);

}

int frameCount = 0;
void loop(){
  noTone(buzzer);

  leds = 0;
  for(int i=0; i<=frameCount; i++) {
    bitSet(leds, i);
  }
  updateShiftRegister();

  if(frameCount == 7) { //frameCount == 8
//    tone(buzzer, 1000); //enable this
  }
 
  frameCount++;
  frameCount = frameCount % 8;
  delay(1000);
}

void updateShiftRegister() {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
