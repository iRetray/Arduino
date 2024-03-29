#include <Keypad.h>
#include  <Wire.h>
#include <LCD.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7);
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3'},
   { '4','5','6'},
   { '7','8','9'},
   { '#','0','*'}
};

byte ene[8] = {
  B00000,
  B01110,
  B00000,
  B11110,
  B10001,
  B10001,
  B10001,
  B10001
};
 
const byte rowPins[rowsCount] = { 8, 2, 3, 4 };
const byte columnPins[columsCount] = { 5, 6, 7};
char clave[4];
char key;
int indice=0;
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 
void setup() {
   Serial.begin(9600);
   lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.createChar(1, ene);
  lcd.begin(16, 2);
  lcd.clear ();
  lcd.setCursor(0,0);
  lcd.print("Sistema de");
  lcd.setCursor(0,1);
  lcd.print("Seguridad");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ingrese la clave");
}

bool verificarClave(char claveIngresada[]){
    if(claveIngresada[0]=='1' && claveIngresada[1]=='2' && claveIngresada[2]=='3' && claveIngresada[3]=='4'){
        return true;
      }
      else{
        return false;
        }
  }

void iniciarSistema(){
  Serial.print("Sistema iniciado");
  }

void limpiarInferior(){
  for(int i=0; i<=15;i++){
    lcd.setCursor(i,1);
    lcd.print(" ");
    }
  }
 
void loop() {
    lcd.setCursor(0,1);
   key = keypad.getKey();
   if(key){
      clave[indice] = key;
      lcd.setCursor(indice+6,1);
      lcd.print("*");
      indice++;
      Serial.println(key);
      if(indice==4){
        limpiarInferior();
        lcd.setCursor(0,1);
        lcd.print(clave[0]);
        lcd.print(clave[1]);
        lcd.print(clave[2]);
        lcd.print(clave[3]);
        Serial.print("La clave ingresada fue: ");
        Serial.print(clave[0]);
        Serial.print(clave[1]);
        Serial.print(clave[2]);
        Serial.print(clave[3]);
        Serial.println("");
        if(verificarClave(clave)){
          lcd.print(" correcta");
          delay(1000);
          Serial.println("La clave es correcta");
          limpiarInferior();
          iniciarSistema();
          }
          else{
            lcd.print(" incorrecta");
          Serial.println("La clave es incorrecta");
          delay(1000);
          limpiarInferior();
          indice = 0;
          }
        }
    }
    
}
