int ledAzul = 8;
int ledVerde = 9;
int ledRojo = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode (ledAzul, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledRojo, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledAzul,HIGH);
  digitalWrite(ledVerde,HIGH);
  digitalWrite(ledRojo,HIGH);
  delay(200);
  digitalWrite(ledAzul,LOW);
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledRojo,LOW);
  delay(200);
}
