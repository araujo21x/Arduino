#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);  // set the LCD address to 0x38

void setup(){
  lcd.begin(16,2);
}

void loop(){
  int i = 0;
  lcd.setCursor(0,0);
  lcd.print("Final d semestre");

  delay(2000);
 
  lcd.setCursor(0,1);
  lcd.print("Estamos fudidos!");

  for (i =0; i <10; i++){     
    lcd.scrollDisplayRight();     
    delay(20); //Aguarda 1 segundo   
  } 
}
