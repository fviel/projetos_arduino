
#include <Stepper.h>

#define trigPin 13
#define echoPin 12
#define blockedLedPin 5
#define cleanLedPin 6

//define a quantidade de passos por volta
const int passosPorVolta = 200; 
//inicializa o motor e seus pinos
Stepper motor(passosPorVolta, 8,9,10,11);
//inicializa o contador de voltas
int contaGiro = 0;         

void setup() {
  Serial.begin (9600);
  //define a velocidade do motor
  motor.setSpeed(70);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //inicializa os leds
  pinMode(blockedLedPin, OUTPUT);
  pinMode(cleanLedPin, OUTPUT); 
}

void loop() {
  //LÊ o sensor de ultrasom 
  int distance=leDistancia();
  
  if ((distance >= 200) || (distance <= 0))
  {
    //Acende o led de livre  
    leds(true);
    
    Serial.println("Livre");
    //dá giro no motor
    //volta 360 graus = 2040 passos.
    giraMotor(20);    
  }
  else {
    //Acende o led de bloqueio    
    leds(false);
    
    Serial.print("Obstruido - Distancia medida: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
}

void giraMotor(int passos)
{
    int i = 0;
    for(i=0;i<=passos;i++)
    {
      motor.step(1);
    }
    Serial.print("Passos: " );
    Serial.println(contaGiro);
    contaGiro = contaGiro + (i-1);   
}

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



