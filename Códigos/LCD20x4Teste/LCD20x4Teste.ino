/*
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
#include <LiquidCrystal.h>

//declare variables/
int sensorAPin = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  lcd.begin(20, 4);
  lcd.clear();
}

void loop() {
  lcd.clear();
  //testa20x4();
  testaLinha1();
  delay(200);  
}  

void testa20x4()
{
  lcd.setCursor(0, 0);
  lcd.print("11111111111111111111");
  lcd.setCursor(0, 1);
  lcd.print("22222222222222222222");
  lcd.setCursor(0, 2);
  lcd.print("33333333333333333333");
  lcd.setCursor(0, 3);
  lcd.print("44444444444444444444"); 
}

void testaLinha1()
{
  lcd.setCursor(0, 0);
  lcd.print("abcdefghijklmnopqrst");
}
  






