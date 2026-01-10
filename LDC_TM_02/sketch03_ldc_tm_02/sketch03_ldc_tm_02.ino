// * lunar_data_center_test_model_02
// * test_03

int command_number = -1;
int pause = 50;

const int averageValue = 500;       // Variable to store the number of reading cycles
long int sensorValue = 0;           // Variable to store the value from the current sensor
long int voltageSensorValue = 0;    // Variable to store the value from the voltage sensor
 
float voltage = 0;                  // Variable to store the voltage value
float current = 0;                  // Variable to store the current value
float input_voltage = 0;            // Variable to store the measured voltage

void setup() {
pinMode(4, OUTPUT); // declare pin 4 as output
pinMode(5, OUTPUT); // declare pin 5 as output
pinMode(6, OUTPUT); // declare pin 5 as output
pinMode(7, OUTPUT); // declare pin 5 as output
  Serial.begin(9600);                                       // Serial port initialization at 9600 baud rate
}

void loop() {
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
  Serial.println(input_voltage);                  // Send input voltage

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
