/*
 * Sketch for transmitter, module hc-12
 */
#include <SoftwareSerial.h>         // * Include software serial library
#define RX 8                        // * Define TX pin for software serial
#define TX 9                        // * Define RX pin for software serial
                                    //
SoftwareSerial Serial4(RX,TX);      // * Create software serial port
#include <OneWire.h>                          // include library for working with OneWire interface
#include <Wire.h>                             // Include library for working with hardware I2C bus.
  
void setup(void) {
  Serial.begin(9600);
  Serial4.begin(9600);                        // Initialize serial port at 9600 baud
  randomSeed(millis());  
  delay(500);                                 // Wait for completion of power-on transient processes     
  }
  
void loop(void) {
  int trans_data = random(101);
  Serial.println(trans_data);
  function_transmit(trans_data);
  delay(1000);
}

void function_transmit(int x) {
  byte data[5];                       // Declare array for receiving and storing data
  Serial.println("function_transmit++");
  Serial.println(x);
  
  delay(10000);                       // Wait half a second
  data[0] = 1;                      // Write one (ON) to the first byte of array
  data[1] = byte(2);
  data[2] = byte(x);
  Serial4.write(0xAA);              // Send packet header
  Serial4.write(data, sizeof(data));// Send data array
  Serial4.write('\n');              // Send new line character
          
  delay(10000);                       // Wait 10 second
  }
