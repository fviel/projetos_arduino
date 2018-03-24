

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
#include <AcceleroMMA7361.h>

//Inicializa pinos
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//Inicializa o acelerômetro
AcceleroMMA7361 accelero;  
int x;  
int y;  
int z;  

void inicializaAcelerometro()  
{  
  accelero.begin(13, 12, 11, 10, A0, A1, A2);  
  accelero.setARefVoltage(3.3);          //Seta a voltagem de referencia AREF como 3.3V  
  accelero.setSensitivity(LOW);          //Seta a sensibilidade (Pino GS) para +/-6G  
  accelero.calibrate();  
}  

void setup() {
  //Ativa a serial
  Serial.begin(9600);  

  //Inicializa o Acelero
  inicializaAcelerometro();

    // Define 20 colunas por 4 linhas - LCD Hitachi j204a
    lcd.begin(20, 4);
  }


void loop() {
  //lcd.noBlink();
  x = accelero.getXAccel(); //Obtem o valor do eixo X  
  y = accelero.getYAccel(); //Obtem o valor do eixo Y  
  z = accelero.getZAccel(); //Obtem o valor do eixo Z  
  lcd.setCursor(0,0);
  lcd.print("Teste do acelerometro.");
  lcd.setCursor(0,1);
  lcd.print("X:");   //Mostra os valores no serial monitor  
  lcd.print(x);  
  
  lcd.setCursor(0,2);
  lcd.print("Y:");   //Mostra os valores no serial monitor  
  lcd.print(y);
  
  lcd.setCursor(0,3);
  lcd.print("Z:");   //Mostra os valores no serial monitor  
  lcd.print(z);
  
    Serial.print("\nx: ");   //Mostra os valores no serial monitor  
  Serial.print(x);  
  Serial.print(" \ty: ");  
  Serial.print(y);  
  Serial.print(" \tz: ");  
  Serial.print(z);  
  Serial.print("\tG*10^-2");  
  
  //lcd.print("\tG*10^-2");  
  delay(500);                     
}
