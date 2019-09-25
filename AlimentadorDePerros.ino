#include <Servo.h>
#include <Wire.h>

uint8_t second, minute, hour, wday, day, month, year, ctrl;
Servo servoMotor;

void setup() {
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  Serial.begin(9600);
  Wire.begin();
  servoMotor.attach(8);
  Serial.println("----------------------------------------------------");
  Serial.println("             ALIMENTADOR DE MASCOTAS                ");
  Serial.println("----------------------------------------------------");
}


 
void loop() {
  delay(1000);
  read_ds1307();
  print_time();
  if(hour==9 && minute==0 && second==0){
    darComida();
    }
  if(hour==12 && minute==30 && second==0){
    darComida();
    }
   if(hour==18 && minute==0 && second==0){
    darComida();
    }
   if(hour==14 && minute==43 && second==0){
    darComida();
    }
  

}


void darComida(){
  for(int i=0;i<=4;i++){
  servoMotor.write(210);
  delay(1000);
  servoMotor.write(90);
  delay(1000);
  }
  Serial.print("La comida se ha servido");
  }

bool read_ds1307()
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
 
void print_time()
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
