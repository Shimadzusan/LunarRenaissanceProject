
#include <SoftwareSerial.h>         // * Подключаем библиотеку программного последовательного порта
#define RX 8                        // * Определяем вывод TX программного последовательного порта
#define TX 9                        // * Определяем вывод RX программного последовательного порта
                                    //
SoftwareSerial Serial4(RX,TX);      // * Создаём программный последовательный порт
byte data[5];                      // Объявляем массив для приёма и хранения данных 
int randomNumber = 0;

#include <OneWire.h>                          // подключаем библиотеку для работы с интерфейсом OneWire
OneWire  ds(13);                              // Создаём объект с именем ds, и указанием пина, к которому подключен датчик
OneWire  ds_2(12);                            // Создаём объект с именем ds, и указанием пина, к которому подключен датчик

#include <Wire.h>                             // Подключаем библиотеку для работы с аппаратной шиной I2C.
  
void setup(void) {
  Serial.begin(9600);
  Serial4.begin(9600);              // Инициируем последовательный порт на скорости 9600 бод
  randomSeed(millis()); 
   pinMode(LED_BUILTIN, OUTPUT); 
  delay(500);                                 // Ждём завершение переходных процессов связанных с подачей питания.     
  }
  
void loop(void) {
   // If there is data in buffer and read byte equals packet header
  if (Serial4.available() && Serial4.read() == 0xAA) {
    // Read string from serial port and convert to byte array data
    String receivedString = Serial4.readStringUntil('\n');
    receivedString.toCharArray((char*)data, sizeof(data));
    
    // Debug output
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(data[2]);
    Serial.println(data[3]);
    Serial.println(data[4]);
    // Serial.println(sizeof(data));
    Serial.println("---++---");
    
    // Turn built-in LED on/off based on received data
    digitalWrite(LED_BUILTIN, data[0]);
    delay(5000);
    module_1();
  }
     
  delay(30000);
}

void module_1(void) {
  byte i;                                     // задаём переменную для счётчика
  byte present = 0;                           // Флаг сброса шины
  byte type_s;                                // Флаг модели датчика
  byte data[12];                              // массив под значения температуры, считанные с датчика
  byte addr[8];                               // массив под значение адреса датчика
  float celsius, fahrenheit;                  // переменные под значения температуры в градусах Цельсия и Фаренгейта
  
  if ( !ds.search(addr)) {                    // если функция принимает значение false, значит
    Serial.println("No more addresses.");     // больше устройств не найдено. Выводит в монитор порта сообщение об этом.
    Serial.println();                         // добавляем символ новой строки
    ds.reset_search();                        // функция начинает новый поиск устройства.
    delay(250);                               // задержка 250 мсек
    return;
  }
  Serial.print("ROM =");                      // выводим текст в монитор порта. "ROM" - это адрес устройства
  for ( i = 0; i < 8; i++) {                  // запускаем цикл
    Serial.write(' ');                        // между значениями добавляем пробел
    Serial.print(addr[i], HEX);               // в монитор порта побайтово выводим адрес устройства в 16-ричной кодировке
  }
  if (OneWire::crc8(addr, 7) != addr[7]) {    // выполяем проверка контрольной суммы CRC
    Serial.println("CRC is not valid!");      // если контрольная сумма не верна - отправляем в монитор порта сообщение об этом
    return;
  }
  Serial.println();                           // добавляем символ новой строки
  switch (addr[0]) {// Модель датчика температуры                                       Флаг типа модуля                В данном блоке проверяем значение старшего байта полученного адреса и по нему определяем модель модуля
    case 0x10:          Serial.println("  Chip = DS18S20");                             type_s = 1;        break;
    case 0x28:          Serial.println("  Chip = DS18B20");                             type_s = 0;        break;
    case 0x22:          Serial.println("  Chip = DS1822");                              type_s = 0;        break;
    default:            Serial.println("Device is not a DS18x20 family device.");                          return;
  }
  ds.reset();                                 // производим сброс шины перед началом работы с модулем
  ds.select(addr);                            // указываем устройство, с которым далее будет работать код
  ds.write(0x44, 0);                          // отправка команды выполнить конвертацию
  delay(1000);                                // задержка в 1 сек (для выполнения конвертации)
  present = ds.reset();                       // флаг сброса шины перед приёмом данных с модуля
  ds.select(addr);                            // указываем устройство, с которым далее будет работать код
  ds.write(0xBE);                             // считываем значение из scratchpad-памяти модуля
  Serial.print("  Data = ");                  // в монитор порта выводим текст "Значение"
  Serial.print(present, HEX);                 // выводим в монитор порта значение с модуля, в 16-ричной кодировке
  Serial.print(" ");                          // добавляем символ новой строки
  
  for ( i = 0; i < 9; i++) {                  // запускаем цикл считывания 9 байт информации с модуля
    data[i] = ds.read();                      // побайтовое чтение значений с модуля
    Serial.print(data[i], HEX);               // выводим в монитор порта значение байта, считанного с модуля
    Serial.print(" end 1");                        // между значениями добавляем пробел
  }

  Serial.print(" CRC=");                      // выводим в монитор порта текст CRC (контрольная сумма)
  Serial.print(OneWire::crc8(data, 8), HEX);  // выводим в монитор порта значение CRC
  Serial.println();                           // добавляем символ новой строки
  
  int16_t raw = (data[1] << 8) | data[0];     // конвертация значения температуры в 16-битный тип данных
  if (type_s) {                               // если подключена модель DS18S20
    raw = raw << 3;                           // тогда сдвигаем значение на 3 влево для получения 12-битного разрешения точности температуры
    if (data[7] == 0x10) {                    // если указанный бит совпадает с условием, то
      raw = (raw & 0xFFF0) + 12 - data[6];    // пересчитываем сырое значение
    }
  } else {                                    // для всех остальных моделей
    byte cfg = (data[4] & 0x60);              // для задания разрешения вводится переменная (по умолчанию установлено 12-битное разрешение)
    if (cfg == 0x00) raw = raw & ~7;          // если значение переменной и указанного бита совпадают, тогда устанавливается 9-битное разрешение точности
    else if (cfg == 0x20) raw = raw & ~3;     // если значение переменной и указанного бита совпадают, тогда устанавливается 10-битное разрешение точности
    else if (cfg == 0x40) raw = raw & ~1;     // если значение переменной и указанного бита совпадают, тогда устанавливается 11-битное разрешение точности
  }
  celsius = (float)raw / 16.0;                // переводим значения в градусы Цельсия
  fahrenheit = celsius * 1.8 + 32.0;          // переводим значения в градусы Фаренгейта
  Serial.println("  Temperature1 = ");         // выводим в монитор порта текста Температура
  Serial.print(celsius);  
  Serial.println("");
  
  int z = (int)celsius;
  Serial.println(z);
//  function_transmit(z, 1);
  delay(1000); 
  }
