#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setup() {
  lcd.begin(16,2);  

}

void loop() {
  lcd.clear();
  lcd.print("Humphrey's LCD"); 
  delay(3000); 
}
