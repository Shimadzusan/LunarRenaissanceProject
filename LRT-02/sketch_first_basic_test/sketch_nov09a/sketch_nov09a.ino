void setup() {
  // Инициализируем последовательный порт
  Serial.begin(9600);
   pinMode(4,1);
  
  // Опционально: устанавливаем опорное напряжение (по умолчанию 5В или 3.3В)
  // analogReference(DEFAULT); // DEFAULT = 5V на 5V-платах, 3.3V на 3.3V-платах
}

void loop() {
  digitalWrite(4,1);
  function_one();
  delay(20000);
  digitalWrite(4,0);
  delay(5000);
  function_one();
  // Считываем значение с аналогового пина A0
//  int sensorValue = analogRead(A0);
//  
//  // Преобразуем аналоговое значение в напряжение
//  // Формула: напряжение = (показание АЦП * опорное напряжение) / 1024
//  float voltage = sensorValue * (5.0 / 1024.0); // Для плат с 5V питанием (Arduino Uno/Nano)
//  // float voltage = sensorValue * (3.3 / 1024.0); // Для плат с 3.3V питанием (Arduino Pro Mini 3.3V)
//  
//  // Выводим значение в монитор порта
//  Serial.print("Напряжение: ");
//  Serial.print(voltage, 2); // 2 знака после запятой
//  Serial.println(" V");
//  
//  // Ждем 500 мс перед следующим измерением
//  delay(5000);
}

void function_one() {
   // Считываем значение с аналогового пина A0
  int sensorValue = analogRead(A0);
  
  // Преобразуем аналоговое значение в напряжение
  // Формула: напряжение = (показание АЦП * опорное напряжение) / 1024
  float voltage = sensorValue * (5.0 / 1024.0); // Для плат с 5V питанием (Arduino Uno/Nano)
  // float voltage = sensorValue * (3.3 / 1024.0); // Для плат с 3.3V питанием (Arduino Pro Mini 3.3V)
  
  // Выводим значение в монитор порта
  Serial.print("Напряжение: ");
  Serial.print(voltage, 2); // 2 знака после запятой
  Serial.println(" V");
  
  // Ждем 500 мс перед следующим измерением
  delay(5000);}
