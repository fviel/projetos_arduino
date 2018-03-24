#include <Stepper.h>

Stepper myStepper;

void setup(){
 Stepper myStepper(300, 8, 9, 10, 11);
}
 
void loop(){
 myStepper.setSpeed(60); // Ajusta a velocidade, este valor pode ser mudado
 myStepper.step(1500); // Numero de passos, sentido horário
 delay(500); // Delay de 0,5seg antes do próximo
 
myStepper.setSpeed(30); // Velocidade agora pela metade
 myStepper.step(-1500); // Numero de passos, agora sentido anti-horário
 delay(500); // Delay de 0,5seg
}
