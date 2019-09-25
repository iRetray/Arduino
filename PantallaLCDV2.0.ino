    #include <LiquidCrystal.h>
    LiquidCrystal lcd(12, 11, 4, 5, 6, 7);
    
    void setup() { 
     lcd.begin(16,2);
    }
    void loop() {
      lcd.print("Hola");
      delay(3000);
       
     //lcd.setCursor(1,1);
     //lcd.print("Arduino"); 
    }
