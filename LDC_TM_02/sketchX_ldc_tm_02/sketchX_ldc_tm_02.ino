// * lunar_data_center_test_model_02

const int averageValue = 500;       // Переменная для хранения значения количества считывания циклов 
long int sensorValue = 0;           // Переменная для хранения значения с датчика тока
long int voltageSensorValue = 0;    // Переменная для хранения значения с датчика напряжения
float voltage = 0;                  // Переменная для хранения значения напряжения
float current = 0;                  // Переменная для хранения значения тока
float input_voltage = 0;            // Переменная для хранения измеренного напряжения
//========
int pause = 2000;
int device_mode = 2001;
int counter = 0;

#include <SoftwareSerial.h>         // * Include software serial library
#define RX 8                        // * Define TX pin for software serial port
#define TX 9                        // * Define RX pin for software serial port
                                    //
SoftwareSerial Serial5(RX,TX);      // * Create software serial port
byte data_transmit[5];              // Declare array for receiving and storing data 
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
  Serial5.begin(9600);              // Initialize serial port at 9600 baud
  randomSeed(millis());  
  delay(500);                       // Wait for completion of transient processes related to power supply.     
  }
  
void loop(void) {
  Serial.println("ldc_tm_02");
  Serial.println("device_mode");
  Serial.println(device_mode);
  
   // If there is data in buffer and read byte equals packet header
  if (Serial5.available() && Serial5.read() == 0xAA) {
    // Read string from serial port and convert to byte array data
    String receivedString = Serial5.readStringUntil('\n');
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

  

   switch(device_mode) {
    case 1:
      digitalWrite(10, 1);
      delay(pause);
      break;
      
    case 2:
      digitalWrite(10, 0);
      delay(pause);
      break;
      
    case 3:
      digitalWrite(5, 1);
      delay(pause);
      break;
      
    case 4:
      digitalWrite(5, 0);
      delay(pause);
      break;
      
    case 5:
      digitalWrite(12, 1);
      delay(pause);
      break;
      
    case 6:
      digitalWrite(12, 0);
      delay(pause);
      break;
      
    case 7:
      digitalWrite(4, 1);
      delay(pause);
      break;
      
    case 8:
      digitalWrite(4, 0);
      delay(pause);
      break;
  }
  delay(1000);
  
//  module_1();
//  module_2();    
  delay(3000);
}

void function_transmit(int x, int module) {
  byte data[5];                       // Declare array for receiving and storing data 
  int randomNumber = 0;
  Serial.println("function_transmit++");
  Serial.println(x);

  digitalWrite(11,1);//pin on
  randomNumber = random(101);
  
  delay(5000);                       // Wait half a second
  digitalWrite(11,0);//pin off
  data[0] = 1;                      // Write one (ON) to the first byte of the array
  data[1] = byte(module);
  data[2] = byte(x);
  Serial5.write(0xAA);              // Send packet header
  Serial5.write(data, sizeof(data));// Send data array
  Serial5.write('\n');              // Send newline character
          
  delay(5000);                       // Wait half a second
  }


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
