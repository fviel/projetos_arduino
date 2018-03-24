#include <Servo.h>

#define CENTRO 90
#define ESQUERDA 135
#define DIREITA 45

Servo motor;

void setup()
{

   motor.attach(28);

}

void loop ()
{   
  /*centro();
  delay(2000); 
  
  
  */
  
  //coloca o motor no centro 
  centro();
  delay(250);  

  //vira à esquerda
  esquerda();
  delay(250);
  

  //vira à direita
  direita();
  delay(250); 
  
}

void centro()
{
  motor.write(CENTRO);
}

void esquerda()
{
  /*  
  for(int i=CENTRO;i<ESQUERDA;i++){
    motor.write(i);
  }
  */
  motor.write(ESQUERDA);  
}

void direita()
{
  motor.write(DIREITA);
}
