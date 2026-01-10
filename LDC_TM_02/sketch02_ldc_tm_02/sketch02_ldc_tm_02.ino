// * lunar_data_center_test_model_02
// * test_02

int command_number = -1;
int pause = 50;

void setup() {
pinMode(4, OUTPUT); // declare pin 4 as output
pinMode(5, OUTPUT); // declare pin 5 as output
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
      
      Serial.print("Input: ");                              // Send result back
      Serial.print(inputValue);
      Serial.print(" | Multiplication result by 2: ");
      Serial.println(result);
    }
  }

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
  }
}
