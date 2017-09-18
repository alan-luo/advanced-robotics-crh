/* Adapted from:
 *  http://fabacademy.org/archives/content/tutorials/12_Interface_and_Application_Programming/PD_to_Arduino_Over_Serial.html
 *  
 *  Use this code to test reading serial data. 
 *  
 *  The patch in this folder will play a tone corresponding with
 *  the value written to serial output, thus producing a constantly
 *  increasing tone.
 *  
 */


void setup() {
 Serial.begin(9600);
}

void loop() {
 for (int i=0; i<255; i++) {
 Serial.write(i);
 delay(100);
 }
 for (int i=255; i>0; i--) {
 Serial.write(i);
 delay(100);
 }
}
