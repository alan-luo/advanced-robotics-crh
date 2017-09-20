int trigPin = 11;
int echoPin = 12;
long duration, cm, inches;

const int max_length = 10;
int values[max_length] = {};
int startup = max_length;

int average = 0;
 
void setup() {
  for(int i=0; i<max_length; i++) {
    values[i] = 0;
  }
  
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
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

  if(startup > 0) {
    values[startup-1] = cm;
    startup--;  
  } else {
    for(int i=0; i<max_length-1; i++) {
      values[i]=values[i+1];
    }
    values[max_length-1]=cm;
  }
  int sum = 0;
  for(int i=0; i<max_length; i++) {
    sum = sum + values[i];
  }
  average = sum / max_length;

//  Serial.println(average);
  Serial.write(average);
  
//  Serial.print(values[0]); Serial.print(", ");
//  Serial.print(values[1]); Serial.print(", ");
//  Serial.print(values[2]); Serial.print(", ");
//  Serial.print(values[3]); Serial.print(", ");
//  Serial.print(values[4]); Serial.print(", ");
//  Serial.println();
  
  
//  inches = (duration/2) / 74; 
  
//  Serial.write(cm);
//  Serial.print(cm);
//  Serial.println(cm);
 
  
  delay(10);
}
