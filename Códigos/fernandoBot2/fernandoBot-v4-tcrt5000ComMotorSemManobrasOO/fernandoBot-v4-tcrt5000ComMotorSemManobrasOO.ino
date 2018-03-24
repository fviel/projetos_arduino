#include "tones.h"
//#include "lineSensor.h"

/**************/
#define lCarcaca 6
boolean lCarc=false;

boolean tocouMusica = false;
boolean continuar = true;

/************************************************************************
Variáveis de controle dos motores e ponte H 298
************************************************************************/

#define FRENTE 1
#define TRAS 0

//pinagem da controladora dianteira
#define DENA 12 //(output pwm)
#define DIN1 41
#define DIN2 43
#define DIN3 45
#define DIN4 47
#define DENB 11 //(output pwm)

//pinagem da controladora traseira
#define TENA 10 //(output pwm)
#define TIN1 31
#define TIN2 33
#define TIN3 35
#define TIN4 37
#define TENB 9 //(output pwm)

boolean Sentido = HIGH;

/************************************************************************
Variáveis de controle de som
************************************************************************/
int beeper = 8;
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4 };

/************************************************************************
Variáveis de controle dos sensores de linha
************************************************************************/
//LineSensor ls;

int velo = 750;



/***************************************************************************************
SETUP
***************************************************************************************/
void setup()
{
  pinMode(beeper, OUTPUT);
  
  pinMode(lCarcaca, OUTPUT);

  //**********************
  //CONTROLADORA DIANTEIRA
  //define pinos como de output
  pinMode(DENA, OUTPUT);
  pinMode(DENB, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);
  pinMode(DIN3, OUTPUT);
  pinMode(DIN4, OUTPUT);

  //inicializa variáveis do motor A
  digitalWrite(DENA, LOW);
  digitalWrite(DIN1, LOW);
  digitalWrite(DIN2, HIGH);

  //inicializa variáveis do motor B
  digitalWrite(DENB, LOW);
  digitalWrite(DIN3, LOW);
  digitalWrite(DIN4, HIGH);

  //**********************
  //CONTROLADORA TRASEIRA
  //define pinos como de output
  pinMode(TENA, OUTPUT);
  pinMode(TENB, OUTPUT);
  pinMode(TIN1, OUTPUT);
  pinMode(TIN2, OUTPUT);
  pinMode(TIN3, OUTPUT);
  pinMode(TIN4, OUTPUT);

  //inicializa variáveis do motor A
  digitalWrite(TENA, LOW);
  digitalWrite(TIN1, LOW);
  digitalWrite(TIN2, HIGH);

  //inicializa variáveis do motor B
  digitalWrite(TENB, LOW);
  digitalWrite(TIN3, LOW);
  digitalWrite(TIN4, HIGH);

 
  //liga os pinos do sensor de linha e leds
  //ls.attach();
  //ls.calibrateSensors();

  //beep de carga completa
  beep();

  //Serial.begin(9600);  //define frequencia da serial
}

/***************************************************************************************
LOOP
***************************************************************************************/
void loop()
{  
  //pisca o led por loop de leitura
  digitalWrite(lCarcaca, !digitalRead(lCarcaca));
  
    
  //se isto não funcionar, precisarei fazer uma função mapeamento DE PARA  
  /*ls.readSensors();	
  Serial.print("\nA-DIGITAL: ");
  Serial.println(ls.getDigitalReadings('A'));
  Serial.print("A-ANALOG: ");
  Serial.println(ls.getAnalogReadings('A'));
  Serial.print("Compensacao A: ");
  Serial.println(ls.cA);
  
  Serial.print("B-DIGITAL: ");
  Serial.println(ls.getDigitalReadings('B'));
  Serial.print("B-ANALOG: ");
  Serial.println(ls.getAnalogReadings('B'));
  Serial.print("Compensacao B: ");
  Serial.println(ls.cB);
   
  Serial.print("C-DIGITAL: ");
  Serial.println(ls.getDigitalReadings('C'));
  Serial.print("C-ANALOG: ");
  Serial.println(ls.getAnalogReadings('C'));
  Serial.print("Compensacao C: ");
  Serial.println(ls.cC);
  
  Serial.print("D-DIGITAL: ");
  Serial.println(ls.getDigitalReadings('D'));
  Serial.print("D-ANALOG: ");
  Serial.println(ls.getAnalogReadings('D'));
  Serial.print("Compensacao D: ");
  Serial.println(ls.cD);

  Serial.print("E-DIGITAL: ");
  Serial.println(ls.getDigitalReadings('E'));
  Serial.print("E-ANALOG: ");
  Serial.println(ls.getAnalogReadings('E'));
  Serial.print("Compensacao E: ");
  Serial.println(ls.cE);
  Serial.println("---------------------------------------------------");


  //TUDO TRUE - Todos os sensores foram acionados juntos, ou seja, o robô estã longe do chão 
  if ((ls.getdigitalReadings('A') == true) && (ls.getdigitalReadings('B') == true) && (ls.getdigitalReadings('C') == true) && (ls.getdigitalReadings('D') == true) && (ls.getdigitalReadings('E') == true))
  {
    pare();
    continuar = false;
    if (tocouMusica == false)
    {
      musicola();
      tocouMusica = true;
    }
  }  

  //uma vez parado, não volta a correr
  if (continuar == true)
  {
    distance = 30;
    //AVALIA SE HÁ OBSTÁCULO
    //distance = leDistancia();    

    if (distance <= distanciaLimite)  
    {        
      tras(velo);
      delay(150);
      pare();  
      usScan();    
    }
    else //if distância
    {
      if(paradaPorContagem()==false)
      {           
          
        //4. TOMA AÇÃO NOS MOTORES
        //TODOS FALSE - Nenhum sensor está ativo, o robô perdeu a linha, então ande de vagar para frente
        if ((ls.getdigitalReadings('A') == false) && (ls.getdigitalReadings('B') == false) && (ls.getdigitalReadings('C') == false) && (ls.getdigitalReadings('D') == false) && (ls.getdigitalReadings('E') == false))
        {
          frente(velo);
          delay(75);
          pare();         
        }
    
        //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        if ((ls.getdigitalReadings('A') == true) && (ls.getdigitalReadings('B') == false) && (ls.getdigitalReadings('C') == false) && (ls.getdigitalReadings('D') == false) && (ls.getdigitalReadings('E') == false))
        {
            direita(velo);
        }

        //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
        if ((ls.getdigitalReadings('A') == false) && (ls.getdigitalReadings('B') == true) && (ls.getdigitalReadings('C') == false) && (ls.getdigitalReadings('D') == false) && (ls.getdigitalReadings('E') == false))
        {
            direita(velo);
        }

        //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        if ((ls.getdigitalReadings('A') == false) && (ls.getdigitalReadings('B') == false) && (ls.getdigitalReadings('C') == true) && (ls.getdigitalReadings('D') == false) && (ls.getdigitalReadings('E') == false))
        {
          frente(velo);          
        }

        //DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        if ((ls.getdigitalReadings('A') == false) && (ls.getdigitalReadings('B') == false) && (ls.getdigitalReadings('C') == false) && (ls.getdigitalReadings('D') == true) && (ls.getdigitalReadings('E') == false))
        {
            esquerda(velo);          
        }

        //EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        if ((ls.getdigitalReadings('A') == false) && (ls.getdigitalReadings('B') == false) && (ls.getdigitalReadings('C') == false) && (ls.getdigitalReadings('D') == false) && (ls.getdigitalReadings('E') == true))
        {
            esquerda(velo);          
        }     
      }//if do contador de sensor
      else
      {
        /*beep();
        delay(30);
      }//fim if contador de sensores  
    }//fim if distancia    
  }//fim if continuar  
  */
}

boolean paradaPorContagem()
{
  Serial.print("Contagem de sensores ativos: ");
  Serial.println(ls.getActivatedSensorsCounter());
  byte sCounter = ls.getActivatedSensorsCounter();
  
  if(sCounter > 2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/***************************************************************************************
PARE
***************************************************************************************/
void pare()
{
  dMotorA(FRENTE, 0);
  dMotorB(FRENTE, 0);
  tMotorA(FRENTE, 0);
  tMotorB(FRENTE, 0);
}

/***************************************************************************************
FRENTE
***************************************************************************************/
void frente (int vel)
{
  dMotorA(FRENTE, vel);
  dMotorB(FRENTE, vel);
  tMotorA(FRENTE, vel);
  tMotorB(FRENTE, vel);
}

/***************************************************************************************
TRAS
***************************************************************************************/
void tras (int vel)
{
  dMotorA(TRAS, vel);
  dMotorB(TRAS, vel);
  tMotorA(TRAS, vel);
  tMotorB(TRAS, vel);
}

/***************************************************************************************
DIREITA
***************************************************************************************/
void direita (int vel)
{
  dMotorA(TRAS, vel);
  dMotorB(FRENTE, vel);
  tMotorA(TRAS, vel);
  tMotorB(FRENTE, vel);  
}


/***************************************************************************************
ESQUERDA
***************************************************************************************/
void esquerda (int vel)
{
  dMotorA(FRENTE, vel);
  dMotorB(TRAS, vel);
  tMotorA(FRENTE, vel);
  tMotorB(TRAS, vel);
}

/***************************************************************************************
musicola
Quando: loop()
O quê: toca uma música chata no beeper
***************************************************************************************/
void musicola()
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++)
  {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(beeper, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(beeper);
  }
}

/***************************************************************************************
BEEP
Quando:
O quê: beepa
***************************************************************************************/
void beep()
{
  tone(beeper, NOTE_G3, 100);
  delay(50);
  tone(beeper, NOTE_F4, 100);
  delay(50);
  noTone(beeper);
  delay(50);
}

/***************************************************************************************
DMOTORA
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void dMotorA(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    dMotorAFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    dMotorARe(velocidade);
  }
}

/***************************************************************************************
DMOTORAFRENTE
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void dMotorAFrente(int velocidade)
{
  digitalWrite(DENA, 0);
  digitalWrite(DIN1, 0);
  digitalWrite(DIN2, 1);
  analogWrite(DENA, velocidade);
}

/***************************************************************************************
DMOTORARE
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void dMotorARe(int velocidade)
{
  digitalWrite(DENA, 1);
  digitalWrite(DIN1, 1);
  digitalWrite(DIN2, 0);
  analogWrite(DENA, velocidade);
}

/***************************************************************************************
DMOTORB
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void dMotorB(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    dMotorBFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    dMotorBRe(velocidade);
  }
}

/***************************************************************************************
MOTORBFRENTE
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void dMotorBFrente(int velocidade)
{
  digitalWrite(DENB, 0);
  digitalWrite(DIN3, 0);
  digitalWrite(DIN4, 1);
  analogWrite(DENB, velocidade);
}

/***************************************************************************************
DMOTORBRE
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void dMotorBRe(int velocidade)
{
  digitalWrite(DENB, 1);
  digitalWrite(DIN3, 1);
  digitalWrite(DIN4, 0);
  analogWrite(DENB, velocidade);
}

/*****************************************************************************************************************************************

/***************************************************************************************
TMOTORA
Quando: funções de locomoção
O quê: controla motor traseiro A
***************************************************************************************/
void tMotorA(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    tMotorAFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    tMotorARe(velocidade);
  }
}

/***************************************************************************************
TMOTORAFRENTE
Quando: funções de locomoção
O quê: controla motor traseiro A
***************************************************************************************/
void tMotorAFrente(int velocidade)
{
  digitalWrite(TENA, 0);
  digitalWrite(TIN1, 0);
  digitalWrite(TIN2, 1);
  analogWrite(TENA, velocidade);
}

/***************************************************************************************
DMOTORARE
Quando: funções de locomoção
O quê: controla motor traseiro A
***************************************************************************************/
void tMotorARe(int velocidade)
{
  digitalWrite(TENA, 1);
  digitalWrite(TIN1, 1);
  digitalWrite(TIN2, 0);
  analogWrite(TENA, velocidade);
}

/***************************************************************************************
TMOTORB
Quando: funções de locomoção
O quê: controla motor traseiro B
***************************************************************************************/
void tMotorB(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    tMotorBFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    tMotorBRe(velocidade);
  }
}

/***************************************************************************************
TMOTORBFRENTE
Quando: funções de locomoção
O quê: controla motor traseiro B
***************************************************************************************/
void tMotorBFrente(int velocidade)
{
  digitalWrite(TENB, 0);
  digitalWrite(TIN3, 0);
  digitalWrite(TIN4, 1);
  analogWrite(TENB, velocidade);
}

/***************************************************************************************
TMOTORBRE
Quando: funções de locomoção
O quê: controla motor traseiro B
***************************************************************************************/
void tMotorBRe(int velocidade)
{
  digitalWrite(TENB, 1);
  digitalWrite(TIN3, 1);
  digitalWrite(TIN4, 0);
  analogWrite(TENB, velocidade);
}

/***************************************************************************************
LEDISTANCIA 
Quando: loop()
O quê: lê a distância em cm do sensor ultrasom
***************************************************************************************/
int leDistancia()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  //delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

/***************************************************************************************
USSCAN
Quando: na loop(), quando há obstáculo
O quê: lê a distância em cm do sensor ultrasom na direita e esquerda
***************************************************************************************/
void usScan()
{
  distance = 0; 
  servoEsquerda();
  delay(150);
  distance = leDistancia();    
 /* Serial.print("Distancia medida pelo US ESQUERDA: ");   
  Serial.print(distance);      
  Serial.println("cm.");  */
  if (distance <= distanciaLimite)
  {
    /*
    for(int i = 0; i<3;i++)
    {
      digitalWrite(ledE, HIGH);
      delay(30);
      digitalWrite(ledE, LOW);
      delay(30);
    }
    */
    direita(velo);
    delay(150);
    pare();
  }   
  
  distance = 0;
  servoDireita();
  delay(150);
  distance = leDistancia(); 
 /* Serial.print("Distancia medida pelo US DIREITA: ");   
  Serial.print(distance);      
  Serial.println("cm.");*/    
  if (distance <= distanciaLimite) 
  {
    /*
    for(int i = 0; i<3;i++)
    {
      digitalWrite(ledA, HIGH);
      delay(30);
      digitalWrite(ledA, LOW);
      delay(30);
    }
    */
    esquerda(velo);
    delay(150);
    pare();
  }
  
  servoCentro();  
}

/***************************************************************************************
SERVOCENTRO
Quando: loop() e setup();
O quê: Posiociona servo no centro
***************************************************************************************/
void servoCentro()
{
  motor.write(CENTRO);
}
/***************************************************************************************
SERVOESQUERDA
Quando: loop() e setup();
O quê: Posiociona servo à esquerda
***************************************************************************************/
void servoEsquerda()
{
  /*  
  for(int i=CENTRO;i<ESQUERDA;i++){
    motor.write(i);
  }
  */
  motor.write(ESQUERDA);  
}
/***************************************************************************************
SERVODIREITA
Quando: loop() e setup();
O quê: Posiociona servo À direita
***************************************************************************************/
void servoDireita()
{
  motor.write(DIREITA);
}
