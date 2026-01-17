// * lunar_data_center_test_model_02
// * test_04

int command_number = -1;
int pause = 50;

const int averageValue = 500;       // Variable to store the number of reading cycles
long int sensorValue = 0;           // Variable to store the value from the current sensor
long int voltageSensorValue = 0;    // Variable to store the value from the voltage sensor
 
float voltage = 0;                  // Variable to store the voltage value
float current = 0;                  // Variable to store the current value
float input_voltage = 0;            // Variable to store the measured voltage

#include <SoftwareSerial.h>         // * Include software serial library
#define RX 8                        // * Define TX pin for software serial
#define TX 9                        // * Define RX pin for software serial
SoftwareSerial Serial4(RX,TX);      // * Create software serial port
#include <OneWire.h>                          // include library for working with OneWire interface
#include <Wire.h>                             // Include library for working with hardware I2C bus.

byte data[5];
int device_mode = 2001;  

void setup() {
  pinMode(4, OUTPUT); // declare pin 4 as output
  pinMode(5, OUTPUT); // declare pin 5 as output
  pinMode(6, OUTPUT); // declare pin 5 as output
  pinMode(7, OUTPUT); // declare pin 5 as output

  pinMode(12, OUTPUT); // declare pin 5 as output for TESTING
  
  Serial.begin(9600);                                       // Serial port initialization at 9600 baud rate

  Serial4.begin(9600);                        // Initialize serial port at 9600 baud for radio module HC-12
  randomSeed(millis());

   pinMode(LED_BUILTIN, OUTPUT);     // IMPORTANT: Set LED pin as output
}

void loop() {
   if (Serial4.available() && Serial4.read() == 0xAA) {
    // Read string from serial port and convert to byte array data
    String receivedString = Serial4.readStringUntil('\n');
    receivedString.toCharArray((char*)data, sizeof(data));
    
    // Debug output
//    Serial.println(data[0]);
//    Serial.println(data[1]);
//    Serial.println("device_mode:");
//    Serial.println(data[2]);
//    Serial.println(data[3]);
//    Serial.println(data[4]);
    // Serial.println(sizeof(data));
    device_mode = data[2];
    command_number = data[2];
//    Serial.println("---++---");
    
    // Turn built-in LED on/off based on received data
    digitalWrite(LED_BUILTIN, data[0]);
    
    delay(1000);
  }
  //****************
  if (Serial.available() > 0) {                             // Check if data is available for reading
    String inputString = Serial.readStringUntil('\n');      // Read string from serial port
    inputString.trim();                                     // Remove extra spaces and newline characters
    
    if (inputString.length() > 0) {                         // Check if string is not empty
      float inputValue = inputString.toFloat();             // Try to convert string to number
      float result = inputValue * 2;                        // Multiply by 2
      command_number = (int) inputValue;
    }
  }

   sensorValue = 0;
   voltageSensorValue = 0;
  
  for (int i = 0; i < averageValue; i++)    // Repeat the cycle
  {
    sensorValue += analogRead(A0);          // Read and record current readings
    voltageSensorValue += analogRead(A1);   // Read and record voltage readings
    delay(2);                               // Pause 2 µs
  }
 
  sensorValue = sensorValue / averageValue;               // Divide the obtained value
  voltageSensorValue = voltageSensorValue / averageValue; // Divide the obtained value
  
  voltage = sensorValue * 5.0 / 1024.0;                    // Voltage calculation
  current = (voltage - 2.49) / 0.185;                       // Current calculation
  input_voltage = voltageSensorValue * 5.0 / 1024.0;       // Input voltage calculation
  
  Serial.print("adc_value: ");                    // Send data to the serial port
  Serial.print(sensorValue);

  Serial.print(", ard_adc1_value: ");             // Send data to the serial port
  Serial.print(voltageSensorValue);
 
  Serial.print(", adc_voltage: ");                // Send data to the serial port
  Serial.print(voltage);                          // Send voltage
  
  Serial.print(", current: ");                    // Send data to the serial port
  Serial.print(current);                          // Send current

  Serial.print(", ard_voltage: ");                // Send data to the serial port
  Serial.print(input_voltage);                  // Send input voltage

  //..radio logic
  int trans_data = random(101);
  Serial.print(", trans_data: ");  
  Serial.print(trans_data);

  Serial.print(", device_mode: ");  
  Serial.println(device_mode);
  
  //function_transmit(trans_data);
  function_transmit_all();
  delay(1000);
  

  switch(command_number) {
    case 1:
      digitalWrite(4, 0);
      delay(pause);
      break;
      
    case 2:
      digitalWrite(4, 1);
      delay(pause);
      break;
      
    case 3:
      digitalWrite(5, 0);
      delay(pause);
      break;
      
    case 4:
      digitalWrite(5, 1);
      delay(pause);
      break;

    case 13:
      digitalWrite(12, 0);
      delay(pause);
      break;
      
    case 14:
      digitalWrite(12, 1);
      delay(pause);
      break;

    case 23:
      digitalWrite(6, 0);
      delay(pause);
      break;
      
    case 24:
      digitalWrite(6, 1);
      delay(pause);
      break;

    case 25:
      digitalWrite(7, 0);
      delay(pause);
      break;

    case 26:
      digitalWrite(7, 1);
      delay(pause);
      break;
  }
  delay(2000);
}

void function_transmit_all() {
  // create jsonString
  String json = "";
  json += "\"adc_value\":" + String(sensorValue) + ",";
  json += "\"ard_adc1_value\":" + String(voltageSensorValue) + ",";
  json += "\"adc_voltage\":" + String(voltage, 2) + ",";
  json += "\"current\":" + String(current, 2) + ",";
  json += "\"ard_voltage\":" + String(input_voltage, 2) + ",";
  json += "\"rand\":" + String(random(101)) + ",";
  json += "\"mode\":" + String(device_mode);
  json += "";

  Serial.println(json);
  
  // transmitting by radio
  Serial4.write(0xAA);
  Serial4.print(json);
  Serial4.write('\n');
  delay(2500);
}

void function_transmit(int x) {
  byte data[5];                       // Declare array for receiving and storing data
//  Serial.println("function_transmit++");
//  Serial.println(x);
  
  delay(10000);                       // Wait half a second
  data[0] = 1;                      // Write one (ON) to the first byte of array
  data[1] = byte(2);
  data[2] = byte(x);
  Serial4.write(0xAA);              // Send packet header
  Serial4.write(data, sizeof(data));// Send data array
  Serial4.write('\n');              // Send new line character
          
  delay(1000);                       // Wait 1 second
  }
