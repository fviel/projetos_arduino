/*
 * LCD RS     - digital pin 7
 * LCD Enable - digital pin 6
 * LCD D4     - digital pin 5
 * LCD D5     - digital pin 4
 * LCD D6     - digital pin 3
 * LCD D7     - digital pin 2
 * LCD R/W    - ground
 */

#include <LiquidCrystal.h>

//Inicializa pinos
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
 // Define 20 colunas por 4 linhas - LCD Hitachi j204a
 lcd.begin(20, 4);

 lcd.setCursor(0,0);
 lcd.print("FernandoVielFernando");
 lcd.setCursor(0,1);
 lcd.print("1234567890123456789");  
 lcd.setCursor(0,2);      
 lcd.print("LCDazulEhMuitoLegal00");
 lcd.setCursor(0,3);      
 lcd.print("AgoraEhSohFazerCabo0");
}


void loop() {
  lcd.noBlink();
}



