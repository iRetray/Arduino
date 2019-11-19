#include <Keypad.h>
#include  <Wire.h>
#include <LCD.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7);

uint8_t second, minute, hour, wday, day, month, year, ctrl;
 
const byte rowsCount = 4;
const byte columsCount = 4;

int ledVerde = 9;
int ledBlanco = 10;
int ledAzul = 11;
int buzzer = 12;

int lecturaDeMovimiento = 13;
int PIR = 0;

int sensor;  
float temperatura;  
float suma;   
double temperaturaT;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3'},
   { '4','5','6'},
   { '7','8','9'},
   { '#','0','*'}
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
 
const byte rowPins[rowsCount] = { 8, 2, 3, 4 };
const byte columnPins[columsCount] = { 5, 6, 7};
char clave[4];
char key;
int indice=0;
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 
void setup() {
  pinMode(lecturaDeMovimiento,INPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  Wire.begin();
  lcd.createChar(1,a);
  lcd.createChar(2,b);
  lcd.createChar(3,c);
  lcd.createChar(4,d);
  lcd.createChar(5,e);
  lcd.createChar(6,exclama);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledAzul, OUTPUT);
  pinMode (ledBlanco, OUTPUT);
  pinMode (buzzer, OUTPUT);
  Serial.begin(9600);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
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
 
void loop() {
   lcd.setCursor(0,1);
   key = keypad.getKey();
   if(key){
      clave[indice] = key;
      lcd.setCursor(indice+6,1);
      digitalWrite(buzzer,HIGH);
      digitalWrite(ledBlanco,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      digitalWrite(ledBlanco,LOW);
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
          digitalWrite(ledVerde,HIGH);
          delay(50);
          digitalWrite(ledVerde,LOW);
          lcd.print(" correcta");
          delay(1000);
          Serial.println("La clave es correcta");
          limpiarInferior();
          iniciarSistema();
          }
          else{
            lcd.print(" incorrecta");
          Serial.println("La clave es incorrecta");
          digitalWrite(ledAzul,HIGH);
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
          digitalWrite(ledAzul,LOW);
          delay(1000);
          limpiarInferior();
          indice = 0;
          }
        }
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
  digitalWrite(ledBlanco, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arrancando");
  lcd.setCursor(0,1);
  lcd.print("sistema");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Cargando...");
  llenarCuadro();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(6);
  digitalWrite(ledBlanco, LOW);
  digitalWrite(ledVerde, HIGH);
  lcd.write("Bienvenido!");
  lcd.setCursor(0,1);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Todo seguro");
  while(true){
    temperaturaT = darTemperatura();
    imprimirTemperatura(temperaturaT); 
    }
   
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
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(temperatura);
  lcd.print(" C");
  estaSeguro();

bool estaSeguro(){
  PIR = digitalRead(lecturaDeMovimiento);
  if (PIR == HIGH){
      lcd.clear();
      lcd.setCursor(0,1);
      Serial.println("Modo emergencia activado");
      lcd.setCursor(0,1);
      lcd.print("Ingrese la clave para desactivar");
      while(){
        lcd.setCursor(0,1);
   key = keypad.getKey();
   if(key){
      clave[indice] = key;
      lcd.setCursor(indice+6,1);
      digitalWrite(buzzer,HIGH);
      digitalWrite(ledBlanco,HIGH);
      delay(50);
      digitalWrite(buzzer,LOW);
      digitalWrite(ledBlanco,LOW);
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
          digitalWrite(ledVerde,HIGH);
          delay(50);
          digitalWrite(ledVerde,LOW);
          lcd.print(" correcta");
          delay(1000);
          Serial.println("La clave es correcta");
          limpiarInferior();
          iniciarSistema();
          }
          else{
            lcd.print(" incorrecta");
          Serial.println("La clave es incorrecta");
          digitalWrite(ledAzul,HIGH);
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
          digitalWrite(ledAzul,LOW);
          delay(1000);
          limpiarInferior();
          indice = 0;
          }
        }
    }
        }
      }
      
    }
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


void limpiarInferior(){
  for(int i=0; i<=15;i++){
    lcd.setCursor(i,1);
    lcd.print(" ");
    }
  }
