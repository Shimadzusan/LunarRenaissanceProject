void setup() {
 pinMode(13,1);
 Serial.begin(9600);
}

void loop() {
  Serial.println("system_out ++");
 
  // Check for incoming data
  while (Serial.available() > 0) {
    char buffer[10]; // Buffer of storage for characters
    int index = 0;
    
    // Read available characters
    while (Serial.available() > 0 && index < 9) {
      char incomingByte = Serial.read();
      buffer[index++] = incomingByte;
      delay(2);
    }
    buffer[index] = '\0'; // null terminator for the string
    
    Serial.print("received: ");
    Serial.println(buffer);
    
    // convert string to number
    int number = atoi(buffer);
    Serial.print("as integer: ");
    Serial.println(number);
  }

  digitalWrite(13,1);
  delay(1000);
  digitalWrite(13,0);
  delay(1000);
}
