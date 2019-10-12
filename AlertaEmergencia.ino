#include  <Wire.h>
#include <LCD.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7);
int lecturaDeMovimiento = 7;
int ledVerde = 8;
int ledRojo = 9;
int buzzer = 10;

int PIR = 0;

byte a[8] = {
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000
};

byte b[8] = {
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000
};

byte c[8] = {
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100,
        B11100
};

byte d[8] = {
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110
};

byte e[8] = {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
};


byte exclama[8] = {
        B00000,
        B00100,
        B00000,
        B00000,
        B00100,
        B00100,
        B00100,
        B00100
};

void setup()
{
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear ();
  
  pinMode(lecturaDeMovimiento,INPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledRojo,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  lcd.createChar(1,a);
  lcd.createChar(2,b);
  lcd.createChar(3,c);
  lcd.createChar(4,d);
  lcd.createChar(5,e);
  lcd.createChar(6,exclama);
  lcd.setCursor(0,0);
  lcd.write("Cargando...");
  llenarCuadro();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Estado:");
}

void llenarCuadro(){
  for(int cubo=0;cubo<=15;cubo++){
    for(int i=1;i<=5;i++){
      lcd.setCursor(cubo,1);
      lcd.write(i);
      delay(80);
    }
   }  
  }

void loop()
{
  
  PIR = digitalRead(lecturaDeMovimiento);
  if (PIR == HIGH){
      Serial.println("Modo emergencia activado");
      digitalWrite(ledVerde,LOW);
      digitalWrite(ledRojo,HIGH);
      digitalWrite(buzzer,HIGH);
      lcd.setCursor(0,1);
      lcd.print("Peligro!    ");
    }
  else {
    Serial.println("Todo seguro");
    digitalWrite(ledRojo,LOW);
    digitalWrite(buzzer,LOW);
    digitalWrite(ledVerde,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Todo Seguro");
    delay(1000);
}
}


/*

  lcd.setCursor(0,0);
  lcd.print("Hola, han pasado");
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  lcd.print(" segs.");

  */
  
