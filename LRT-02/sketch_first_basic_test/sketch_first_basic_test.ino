void setup() {
 pinMode(4,1);
 pinMode(12,1);
 pinMode(5,1);
 pinMode(10,1);
}

void loop() {
digitalWrite(4,1);
digitalWrite(12,1);
digitalWrite(5,1);
digitalWrite(10,1);
delay(20000);
digitalWrite(4,0);

delay(1000);
digitalWrite(12,1);
delay(1000);
digitalWrite(12,0);
delay(1000);

digitalWrite(5,1);
delay(1000);
digitalWrite(5,0);
delay(1000);

digitalWrite(10,1);
delay(1000);
digitalWrite(10,0);
delay(1000);
}
