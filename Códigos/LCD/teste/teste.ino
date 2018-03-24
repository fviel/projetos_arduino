#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8,7,6,5,4,3);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.home();
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("111111111111111");
  lcd.setCursor(0,1);
  lcd.print("222222222222222");
  /*lcd.setCursor(0,2);
  lcd.print("33333333333333333333");
  lcd.setCursor(0,3);
  lcd.print("44444444444444444444");*/
  delay(500);
}

