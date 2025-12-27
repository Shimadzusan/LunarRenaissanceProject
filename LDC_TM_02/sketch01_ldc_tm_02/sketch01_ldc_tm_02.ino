// * lunar_data_center_test_model_02
// * test_01

void setup() {
  Serial.begin(9600);                                       // Serial port initialization at 9600 baud rate
}

void loop() {
  if (Serial.available() > 0) {                             // Check if data is available for reading
    String inputString = Serial.readStringUntil('\n');      // Read string from serial port
    inputString.trim();                                     // Remove extra spaces and newline characters
    
    if (inputString.length() > 0) {                         // Check if string is not empty
      float inputValue = inputString.toFloat();             // Try to convert string to number
      float result = inputValue * 2;                        // Multiply by 2
      
      Serial.print("Input: ");                              // Send result back
      Serial.print(inputValue);
      Serial.print(" | Multiplication result by 2: ");
      Serial.println(result);
    }
  }
}
