#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int azul = A5;
//int branco = 10;
int pinoSensor = 0;
int valorLido = 0;
float temperatura = 0;

void setup() { 
  lcd.begin(16, 2);
  lcd.print("Temperat.: ");
  pinMode(azul, OUTPUT);
  //pinMode(branco, OUTPUT);
}

void loop() {
  digitalWrite(azul, HIGH);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(11, 0);
  //lcd.print(millis()/1000);
  lcd.print(getTemperatura());
  lcd.setCursor(0, 1);
  lcd.print("By Karpinski");
  delay(1000);
  digitalWrite(azul, LOW);
  delay(1000);
}

float getTemperatura() {
  valorLido = analogRead(pinoSensor);
  temperatura = (valorLido * 0.00488);
  temperatura = temperatura * 100;
  return temperatura;
}