int pause = 2000;
int device_mode = 2000;
int counter = 0;
  
void setup() {
  pinMode(13,1);
  pinMode(12,1);
  pinMode(11,1);
  pinMode(10,1);
  Serial.begin(9600);
}

void loop() {
  Serial.print("system_out++ counter: ");
  Serial.println(counter);
  counter++;
 
  // check for incoming data
  while (Serial.available() > 0) {
    char buffer[10]; // buffer of storage for characters
    int index = 0;
    
    // read available characters
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
    device_mode = number;
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
      digitalWrite(11, 1);
      delay(pause);
      break;
      
    case 4:
      digitalWrite(11, 0);
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
      digitalWrite(13, 1);
      delay(pause);
      break;
      
    case 8:
      digitalWrite(13, 0);
      delay(pause);
      break;
  }
  delay(1000);  
}
