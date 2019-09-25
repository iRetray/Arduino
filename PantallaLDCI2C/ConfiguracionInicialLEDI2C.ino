#include  <Wire.h>
#include <LCD.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7);
 
void setup()
{
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear ();
}
 
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("Hola, han pasado");
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  lcd.print(" segs.");
}
