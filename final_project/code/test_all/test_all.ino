/*********************************************************************
Taken directly from bleuart_cmdmode from the Bluefruit library
*********************************************************************/
/* set up bluetooth stuff */

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#include "DHT.h" // for temp

#include <Servo.h> // for servo

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/* set up DHT stuff */
#define DHTPIN 9     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

int lightPin = A0; // light sensor

int servoPin = 5;
Servo servo;  

int pumpPin = 3;


int angle = 0;   // servo position in degrees

void setup(void) {
  // ------ bluetooth stuff ---------
  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE ) {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter characters to send to Bluefruit"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }
  
  dht.begin(); // set up dht
  analogReference(EXTERNAL); // set up light sensor
  servo.attach(servoPin); // servo
  pinMode(pumpPin, OUTPUT); // set up transistor switch
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/

int count = 0;
void loop(void) {
  // ----- get sensor inputs
  // dht
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // light
  int rawValue = analogRead(lightPin);
  float l = RawToLux(rawValue);

  String data = String(h)+","+String(t)+","+String(l);

  // Send characters to Bluefruit
  Serial.print("[Send] ");
  Serial.println(data);

  ble.print("AT+BLEUARTTX=");
  ble.println(data);

  /*
  // check response stastus
  if (! ble.waitForOK() ) {
    Serial.println(F("Failed to send?"));
  }

  // Check for incoming characters from Bluefruit
  ble.println("AT+BLEUARTRX");
  ble.readline();
  if (strcmp(ble.buffer, "OK") == 0) {
    // no data
    return;
  }
  // Some data was found, its in the buffer
  Serial.print(F("[Recv] ")); Serial.println(ble.buffer);
  ble.waitForOK();

  */
  if(count % 2 == 0) {
    for(angle = 0; angle < 180; angle++) {                                  
      servo.write(angle);               
      delay(15);                   
    }
  } else {
    for(angle = 180; angle > 0; angle--) {                              
      servo.write(angle);           
      delay(15);       
    }
  }
  count++;
 
}

float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux
float RawToLux(int raw) {
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}
