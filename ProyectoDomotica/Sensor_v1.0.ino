#include  <Wire.h>
#include <LCD.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7);
int ledAzul = 8;
int ledVerde = 9;
int ledRojo = 10;
int cargando = 12;
int inicio = 13;
int buzzer = 11;
int sensor;  
float temperatura;  
float suma;   
double temperaturaT;
int carga;

//Caracteres especiales
//bolita para grados
byte grado[8] = {
        B00000,
        B01110,
        B01010,
        B01110,
        B00000,
        B00000,
        B00000,
        B00000
};

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
  Serial.begin(9600);
  pinMode (ledAzul, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledRojo, OUTPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (cargando, OUTPUT);
  pinMode (inicio, OUTPUT);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.createChar(7, grado);
  lcd.createChar(1,a);
  lcd.createChar(2,b);
  lcd.createChar(3,c);
  lcd.createChar(4,d);
  lcd.createChar(5,e);
  lcd.createChar(6,exclama);
  lcd.clear ();
  lcd.setCursor(0,0);
  lcd.write("Cargando...");
  digitalWrite(cargando, HIGH);
  llenarCuadro();
  digitalWrite(cargando, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  digitalWrite(inicio, HIGH);
  lcd.write("Programa para");
  lcd.setCursor(0,1);
  lcd.write("ver temperatura");
  delay(1000);
}
 
void loop()
{
  temperaturaT = darTemperatura();
  encenderLed(temperaturaT);
  imprimirTemperatura(temperaturaT);
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

void imprimirTemperatura(double temperatura){
  lcd.setCursor(0,0);
  lcd.print("Temperatura:   ");
  lcd.setCursor(0,1);
  lcd.print(temperatura);
  lcd.print(" grados C");
  lcd.write(7);
  
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
