/*
 * Sketch for receiver, module hc-12
 */
#include <SoftwareSerial.h>                      // * Include software serial library
#define RX 8                                     // * Define TX pin for software serial
#define TX 9                                     // * Define RX pin for software serial
                                                 //
SoftwareSerial Serial4(RX, TX);                  // * Create software serial port
byte data[5];                                    // Array for receiving and storing data

void setup() {
  Serial4.begin(9600);                           // Initialize software serial at 9600 baud
  Serial.begin(9600);                            // Initialize hardware serial for debugging
  pinMode(LED_BUILTIN, OUTPUT);                  // IMPORTANT: Set LED pin as output
}                                                //
                                                 
void loop() {                                    
  // If there is data in buffer and read byte equals packet header
  if (Serial4.available() && Serial4.read() == 0xAA) {
    // Read string from serial port and convert to byte array data
    String receivedString = Serial4.readStringUntil('\n');
    receivedString.toCharArray((char*)data, sizeof(data));
    
    // Debug output
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(data[2]);
    Serial.println(data[3]);
    Serial.println(data[4]);
    // Serial.println(sizeof(data));
    Serial.println("---++---");
    
    // Turn built-in LED on/off based on received data
    digitalWrite(LED_BUILTIN, data[0]);
  }
}
