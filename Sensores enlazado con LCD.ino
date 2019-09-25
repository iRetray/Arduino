//Incluir libreria para el lcd
#include <LiquidCrystal.h>

//Crear los objetos a usar como variables
int ledAzul = 8;
int ledVerde = 9;
int ledRojo = 10;
int funcion;
int sensor;  
float temperatura;  
float suma;   
float temperaturaT;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int inicio=0;

void setup(){
  Serial.begin(9600);
  pinMode (ledAzul, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledRojo, OUTPUT);
  lcd.begin(16, 2);
}

void loop(){
  while(inicio=0){
      iniciarPrograma();
      inicio++;
    }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:"); 
  suma = 0;         
  for (int i=0; i < 5; i++){      
  sensor = analogRead(A0);        
  temperatura = ((sensor * 5000.0) / 1023) / 10;
  suma = temperatura + suma;     
  delay(100);        
  }
  Serial.println(suma/5.0, 1);
  temperaturaT = suma/5.0;
  lcd.setCursor(0,1);
  lcd.print(temperaturaT);
  apagarTodo();
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
  lcd.setCursor(0, 0);      // ubica cursor en columna 0, linea 0
  lcd.print("Hola, han pasado");  // escribe el texto en pantalla
  lcd.setCursor(0, 1);      // ubica cursor en columna 0, linea 1
  lcd.print(millis() / 1000);   // escribe valor en segundos devuelto por funcion millis()
  lcd.print(" seg."); 
}

void iniciarPrograma(){
  lcd.setCursor(0,0);
  lcd.print("Iniciando programa");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("0%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("10%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("20%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("30%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("40%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("50%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("60%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("70%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("80%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("90%");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("100%");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Progama iniciado!");
  delay(1000);
}

void apagarTodo(){
  digitalWrite(ledAzul,LOW);
  digitalWrite(ledRojo,LOW);
  digitalWrite(ledVerde,LOW);
  }

void encenderLedAzul(){
  digitalWrite(ledAzul, HIGH);
  }

void encenderLedVerde(){
  digitalWrite(ledVerde, HIGH);
  }

void encenderLedRojo(){
  digitalWrite(ledRojo, HIGH);
  }
