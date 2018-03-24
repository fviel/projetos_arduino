
#define trigPin 8
#define echoPin 9
/*#define blockedLedPin 13
#define cleanLedPin 12
*/

#include <LiquidCrystal.h>

//declare variables/
float tempLM35;
int sensorAPin = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  Serial.begin (9600);
  
  lcd.begin(20, 4);
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //inicializa os leds
//  pinMode(blockedLedPin, OUTPUT);
//  pinMode(cleanLedPin, OUTPUT); 
}

void loop() 
{
  lcd.clear();
  tempLM35 = leTemperatura();
  lcd.setCursor(0, 2);
  lcd.print("Temperatura: ");
  lcd.print(tempLM35);  
  
  int distancia = leDistancia();
  if ((distancia >= 100) || (distancia <= 0))
  {
    lcd.setCursor(0, 3); 
    lcd.print("Livre");     
  }
  else 
  { 
    lcd.setCursor(0, 3); 
    lcd.print("Dist: ");
    lcd.print(distancia);
    lcd.print(" cm");
  }
  delay(200);
}


float leTemperatura() 
{
  float tempC;
  tempC = analogRead(sensorAPin);
  tempC = (5.0 * tempC * 100.0)/1024.0; //converte em celsius
  return(tempC);
} 

/*
void leds(boolean estado)
{
  if(estado == true)
  {
    //LIVRE
    digitalWrite(blockedLedPin,LOW);
    digitalWrite(cleanLedPin,HIGH);
  }
  else
  {
    //OBSTRUÍDO
    digitalWrite(blockedLedPin,HIGH);
    digitalWrite(cleanLedPin,LOW);
  }
}
*/
int leDistancia()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}



