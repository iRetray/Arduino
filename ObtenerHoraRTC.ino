#include <Wire.h>

uint8_t second, minute, hour, wday, day, month, year, ctrl;

void setup() {
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  Serial.begin(9600);
  Wire.begin();
}

void loop() {

  delay(1000);
  if (relojConectado()) {
    imprimirHora();
  } else {
    Serial.println("No se detecta el DS1307, revisar conexiones");
  }
}
 
bool relojConectado()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  if (Wire.endTransmission() != 0)
    return false;
  Wire.requestFrom(0x68, 8);
  second = bcd2bin(Wire.read());
  minute = bcd2bin(Wire.read());
  hour = bcd2bin(Wire.read());
  wday = bcd2bin(Wire.read());
  day = bcd2bin(Wire.read());
  month = bcd2bin(Wire.read());
  year = bcd2bin(Wire.read());
  ctrl = Wire.read();
  return true;
}
 
uint8_t bcd2bin(uint8_t bcd)
{
  return (bcd / 16 * 10) + (bcd % 16);
}

void imprimirHora()
{
  Serial.print("Fecha: ");
  Serial.print(day);
  Serial.print('/');
  Serial.print(month);
  Serial.print('/');
  Serial.print(year);
 
  Serial.print("  Hora: ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.print(second);
 
  Serial.println();
}
