//Crear los objetos a usar como variables
int ledAzul = 8;
int ledVerde = 9;
int ledRojo = 10;
int funcion;
int sensor;  
float temperatura;  
float suma;   
float temperaturaT;

void setup(){
  Serial.begin(9600);
  pinMode (ledAzul, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledRojo, OUTPUT);
}

void loop(){
  suma = 0;         
  for (int i=0; i < 5; i++){      
  sensor = analogRead(A0);        
  temperatura = ((sensor * 5000.0) / 1023) / 10;
  suma = temperatura + suma;     
  delay(100);        
  }
  Serial.println(suma/5.0, 1);
  temperaturaT = suma/5.0;
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
