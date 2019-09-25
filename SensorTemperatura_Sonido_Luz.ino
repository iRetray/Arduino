#include  <Wire.h>
#include <LCD.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7);
int ledAzul = 8;
int ledVerde = 9;
int ledRojo = 10;
int buzzer = 11;
int sensor;  
float temperatura;  
float suma;   
double temperaturaT;
 
void setup()
{
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear ();
  Serial.begin(9600);
  pinMode (ledAzul, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledRojo, OUTPUT);
  pinMode (buzzer, OUTPUT);
}
 
void loop()
{
  temperaturaT = darTemperatura();
  encenderLed(temperaturaT);
  imprimirTemperatura(temperaturaT);
}

void imprimirTemperatura(double temperatura){
  lcd.setCursor(0,0);
  lcd.print("La temperatura es:");
  lcd.setCursor(0,1);
  lcd.print(temperatura);
  lcd.print(" grados Cº");
  }

double darTemperatura(){
  suma = 0;         
  for (int i=0; i < 5; i++){      
  sensor = analogRead(A0);        
  temperatura = ((sensor * 5000.0) / 1023) / 10;
  suma = temperatura + suma;     
  delay(100);        
  }
  Serial.println(suma/5.0, 1);
  temperaturaT = suma/5.0;
  return temperaturaT;
  }

void encenderLed(double temperaturaT){
  if(temperaturaT<=22.0){
      encenderLedAzul();
    }else{
      if(temperaturaT>=22.1 && temperaturaT<=24.0){
          encenderLedVerde();
        }else{
          if(temperaturaT>=24.1){
            encenderLedRojo();
            }
          }
      }
  }

void apagarTodo(){
  digitalWrite(ledAzul,LOW);
  digitalWrite(ledRojo,LOW);
  digitalWrite(ledVerde,LOW);
  digitalWrite(buzzer, LOW);
  }

void encenderLedAzul(){
  apagarTodo();
  digitalWrite(ledAzul, HIGH);
  }

void encenderLedVerde(){
  apagarTodo();
  digitalWrite(ledVerde, HIGH);
  }

void encenderLedRojo(){
  apagarTodo();
  digitalWrite(ledRojo, HIGH);
  timbrarBuzzer();
  }

void timbrarBuzzer(){
  digitalWrite(buzzer,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(50);
  digitalWrite(buzzer,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(50);
  digitalWrite(buzzer,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(50);
  }
