// * command_and_control_center_test_model_01 (3c)
// * test_01

int pause = 2000;
int device_mode = 2001;
int counter = 0;
int command_number = 0;

#include <SoftwareSerial.h>         // * Include software serial library
#define RX 8                        // * Define TX pin for software serial port
#define TX 9                        // * Define RX pin for software serial port
                                    //
SoftwareSerial Serial4(RX,TX);      // * Create software serial port
byte data_transmit[5];                       // Declare array for receiving and storing data 
int randomNumber = 0;
byte data[5];  

//#include <OneWire.h>              // include library for working with OneWire interface
//OneWire  ds(6);                   // Create object named ds, with pin specification to which the sensor is connected
//OneWire  ds_2(7);                 // Create object named ds, with pin specification to which the sensor is connected

#include <Wire.h>                   // Include library for working with hardware I2C bus.
  
void setup(void) {
  pinMode(4,1);
  pinMode(12,1);
  pinMode(5,1);
  pinMode(10,1);
  pinMode(LED_BUILTIN, OUTPUT);     // IMPORTANT: Set LED pin as output
  
  Serial.begin(9600);
  Serial4.begin(9600);              // Initialize serial port at 9600 baud
  randomSeed(millis());  
  delay(500);                       // Wait for completion of transient processes related to power supply.     
  }
  
void loop(void) {
    //****************
  if (Serial.available() > 0) {                             // Check if data is available for reading
    String inputString = Serial.readStringUntil('\n');      // Read string from serial port
    inputString.trim();                                     // Remove extra spaces and newline characters
    
    if (inputString.length() > 0) {                         // Check if string is not empty
      float inputValue = inputString.toFloat();             // Try to convert string to number
      float result = inputValue * 2;                        // Multiply by 2
      command_number = (int) inputValue;

       //..radio logic
//  int trans_data = random(5);
  Serial.print(", trans_data: ");
//  int trans_data_2 = 13; 
  Serial.println(command_number);
  function_transmit(command_number, 2);
  delay(1000);
    }
  }
  
  Serial.println("command_and_control_center_test_model_01");
  Serial.println("device_mode");
  Serial.println(device_mode);
   // If there is data in buffer and read byte equals packet header
  if (Serial4.available() && Serial4.read() == 0xAA) {
    // Read string from serial port and convert to byte array data
    String receivedString = Serial4.readStringUntil('\n');
    receivedString.toCharArray((char*)data, sizeof(data));
    
    // Debug output
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println("device_mode:");
    Serial.println(data[2]);
    Serial.println(data[3]);
    Serial.println(data[4]);
    // Serial.println(sizeof(data));
    device_mode = data[2];
    Serial.println("---++---");
    
    // Turn built-in LED on/off based on received data
    digitalWrite(LED_BUILTIN, data[0]);
    
    delay(1000);
  }
//  //..radio logic
//  int trans_data = random(5);
//  Serial.print(", trans_data: ");
//  int trans_data_2 = 13; 
//  Serial.println(trans_data_2);
////  function_transmit(trans_data_2, 2);
  delay(1000);

}

void function_transmit(int x, int module) {
  byte data[5];                       // Declare array for receiving and storing data 
  int randomNumber = 0;
  Serial.println("function_transmit++");
  Serial.println(x);

  digitalWrite(11,1);//pin on
  randomNumber = random(101);
  
  delay(1000);                       // Wait half a second
  digitalWrite(11,0);//pin off
  data[0] = 1;                      // Write one (ON) to the first byte of the array
  data[1] = byte(module);
  data[2] = byte(x);
  Serial4.write(0xAA);              // Send packet header
  Serial4.write(data, sizeof(data));// Send data array
  Serial4.write('\n');              // Send newline character
          
  delay(1000);                       // Wait half a second
  }
