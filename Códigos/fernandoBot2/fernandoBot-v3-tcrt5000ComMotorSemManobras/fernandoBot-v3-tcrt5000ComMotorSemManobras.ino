#include "tones.h"
#include <Servo.h>

#define CENTRO 72
#define ESQUERDA 112
#define DIREITA 12

Servo motor;

/**************/
#define lCarcaca 6
boolean lCarc=false;
int distance = 0;
int distanciaLimite = 15;


/************************************************************************
Variáveis do sensor ultrasom dianteiro
************************************************************************/
int trigPin = 53;
int echoPin = 51;

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
int analogPinA = 8;
int analogPinB = 9;
int analogPinC = 10;
int analogPinD = 11;
int analogPinE = 12;

int valA = 0;
int valB = 0;
int valC = 0;
int valD = 0;
int valE = 0;

int ledA = 44;
int ledB = 46;
int ledC = 48;
int ledD = 50;
int ledE = 52;

boolean A = false;
boolean B = false;
boolean C = false;
boolean D = false;
boolean E = false;

//limiar de detecção
int limiar = 450;
int velo = 750;

//cariáveis de compensação de leitores ultrasom
int corretorA=0;
int corretorB=0;
int corretorC=0;
int corretorD=0;
int corretorE=0;

/***************************************************************************************
SETUP
***************************************************************************************/
void setup()
{

  pinMode(beeper, OUTPUT);

  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(ledE, OUTPUT);

  pinMode(analogPinA, INPUT);
  pinMode(analogPinB, INPUT);
  pinMode(analogPinC, INPUT);
  pinMode(analogPinD, INPUT);
  pinMode(analogPinE, INPUT);

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

  //setup dos pinos do sensor ultrasom
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  //liga o servo do sensor ao pino 28;
  motor.attach(28);
  
  //vira o servo na posiçãop central --AINDA PRECISA DE REVISÃO
  servoCentro();
  //usScan();
  
  //compensa a diferença de leitura dos sensores
  calibrarSensores();

  //beep de carga completa
  beep();

  //Serial.begin(9600);  //define frequencia da serial
}

/***************************************************************************************
LOOP
***************************************************************************************/
void loop()
{  
  if(lCarc==false)
  {
    digitalWrite(lCarcaca, HIGH);
    lCarc=true;
  }
  else
  {
    digitalWrite(lCarcaca, LOW);
    lCarc=false;
  }
   
  
  //Serial.println(" - INICIO LOOP - ");
  leSensoresLinha();


  //OK - todos os sensores foram acionados juntos, ou seja, o robô estã longe do chão 
  if ((A == true) && (B == true) && (C == true) && (D == true) && (E == true))
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
    /*Serial.print("Distancia medida pelo US: ");   
    Serial.print(distance);      
    Serial.println("cm.");  */
    if (distance <= distanciaLimite)  
    {
      for(int i = 0; i<3;i++)
      {
        digitalWrite(ledC, HIGH);
        delay(30);
        digitalWrite(ledC, LOW);
        delay(30);
      }      
      tras(velo);
      delay(150);
      pare();  
      usScan();    
    }
    else //if distância
    {
      if(paradaPorContagem()==false)
      {
        //Serial.print("Caminho livre - ");      
          
        //4. TOMA AÇÃO NOS MOTORES
        //OK - nenhum sensor está ativo, o robô perdeu a linha, então ande de vagar para frente
        if ((A == false) && (B == false) && (C == false) && (D == false) && (E == false))
        {
          frente(velo);
          delay(75);
          pare();         
        }
    
        //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        if ((A == true) && (B == false) && (C == false) && (D == false) && (E == false))
        {
            direita(velo);
        }

        //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
        if ((A == false) && (B == true) && (C == false) && (D == false) && (E == false))
        {
            direita(velo);
        }

        //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
        if ((A == false) && (B == false) && (C == true) && (D == false) && (E == false))
        {
          frente(velo);          
        }

        //DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
        if ((A == false) && (B == false) && (C == false) && (D == true) && (E == false))
        {
            esquerda(velo);          
        }

        //EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        if ((A == false) && (B == false) && (C == false) && (D == false) && (E == true))
        {
            esquerda(velo);          
        }     
      }//if do contador de sensor
      else
      {
        beep();
        delay(30);
      }//fim if contador de sensores  
    }//fim if distancia    
  }//fim if continuar
  //debugSensor();
  zeraVals();
  //Serial.println(" - FIM LOOP - ");
}

boolean paradaPorContagem()
{
  byte sCounter = 0;
  if(A==true)
  {
    sCounter++;
  }
  if(B==true)
  {
    sCounter++;
  }
  if(C==true)
  {
    sCounter++;
  }
  if(D==true)
  {
    sCounter++;
  }
  if(E==true)
  {
    sCounter++;
  }
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
LESENSORESLINHA
Quando: Executada na setup(), fora do loop.
O quê: aplica valores de compensação às leituras, compensando erros da placa.
***************************************************************************************/
void calibrarSensores()
{
  corretorA  = analogRead(analogPinA);
  corretorB  = analogRead(analogPinB);
  corretorC  = analogRead(analogPinC);
  corretorD  = analogRead(analogPinD);
  corretorE  = analogRead(analogPinE);  
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, LOW);
  digitalWrite(ledE, LOW);
  for(int i = 0; i < 2; i++)
  {
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, HIGH);
    digitalWrite(ledC, HIGH);
    digitalWrite(ledD, HIGH);
    digitalWrite(ledE, HIGH);
    delay(30);
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, LOW);
    digitalWrite(ledE, LOW);
    delay(30);
  }
  
}

/***************************************************************************************
LESENSORESLINHA
Quando: na loop()
O quê: diz se um sensor está ligado ou não com base em um valor limiar definido na setup
***************************************************************************************/
void leSensoresLinha()
{
  //1. LÊ OS SENSORES
  valA = analogRead(analogPinA)- corretorA;
  valB = analogRead(analogPinB)- corretorB;
  valC = analogRead(analogPinC)- corretorC;
  valD = analogRead(analogPinD)- corretorD;
  valE = analogRead(analogPinE)- corretorE;  
  
  //2. DIGITALIZA A LEITURA
  if (valA < limiar)
  {
    A = false;
  } else
  {
    A = true;
  }

  if (valB < limiar)
  {
    B = false;
  } else
  {
    B = true;
  }

  if (valC < limiar)
  {
    C = false;
  } else
  {
    C = true;
  }

  if (valD < limiar)
  {
    D = false;
  } else
  {
    D = true;
  }

  if (valE < limiar)
  {
    E = false;
  } else
  {
    E = true;
  }

  //3. ACIONA LEDS PLACA
  if (A) {
    digitalWrite(ledA, HIGH);
  } else {
    digitalWrite(ledA, LOW);
  }

  if (B) {
    digitalWrite(ledB, HIGH);
  } else {
    digitalWrite(ledB, LOW);
  }

  if (C) {
    digitalWrite(ledC, HIGH);
  } else {
    digitalWrite(ledC, LOW);
  }

  if (D) {
    digitalWrite(ledD, HIGH);
  } else {
    digitalWrite(ledD, LOW);
  }

  if (E) {
    digitalWrite(ledE, HIGH);
  } else {
    digitalWrite(ledE, LOW);
  }
  zeraVals();
}

/***************************************************************************************
LESENSORLINHA
Quando: -
O quê: lê somente um sensor
***************************************************************************************/
boolean leSensorLinha(char sensor)
{
  int val = 0;
  boolean resp = false;

  switch (sensor)
  {
    case 'A':
      {
        val = analogRead(analogPinA);
      } break;
    case 'B':
      {
        val = analogRead(analogPinB);
      } break;
    case 'C':
      {
        val = analogRead(analogPinC);
      } break;
    case 'D':
      {
        val = analogRead(analogPinD);
      } break;
    case 'E':
      {
        val = analogRead(analogPinE);
      } break;
    case DEFAULT:
      {
        val = -1;
      } break;
  }

  //2. DIGITALIZA A LEITURA
  if (val < limiar)
  {
    resp = false;
  } else
  {
    resp = true;
  }

  switch (sensor)
  {
    case 'A':
      {
        if (val==true)
        {
          digitalWrite(ledA, HIGH);
        } else {
          digitalWrite(ledA, LOW);
        }
      } break;
    case 'B':
      {
        if (val==true)
        {
          digitalWrite(ledB, HIGH);
        } else {
          digitalWrite(ledB, LOW);
        }
      } break;
    case 'C':
      {
        if (val==true)
        {
          digitalWrite(ledC, HIGH);
        } else {
          digitalWrite(ledC, LOW);
        }
      } break;
    case 'D':
      {
        if (val==true)
        {
          digitalWrite(ledD, HIGH);
        } else {
          digitalWrite(ledD, LOW);
        }
      } break;
    case 'E':
      {
        if (val==true)
        {
          digitalWrite(ledE, HIGH);
        } else {
          digitalWrite(ledE, LOW);
        }
      } break;
  }
  zeraVals();
  return (resp);
}

/***************************************************************************************
DEBUGSENSOR
Quando: loop()
O quê: printa no terminal os valores lidos para fins de debug
***************************************************************************************/
void debugSensor()
{
  Serial.print("******************************************************************************\n");
  Serial.print("* limiar: ");
  Serial.println(limiar);
  Serial.print("| A: ");
  Serial.print(valA);
  Serial.print(" - ");
  Serial.print(A);
  Serial.print("| B: ");
  Serial.print(valB);
  Serial.print(" - ");
  Serial.print(B);
  Serial.print("| C: ");
  Serial.print(valC);
  Serial.print(" - ");
  Serial.print(C);
  Serial.print("| D: ");
  Serial.print(valD);
  Serial.print(" - ");
  Serial.print(D);
  Serial.print("| E: ");
  Serial.print(valE);
  Serial.print(" - ");
  Serial.print(E);
  Serial.print("*\n******************************************************************************\n");
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
ZERAVALS
Quando: leSensores() e leSensor()
O quê: zera as variáveis para a próxima leitura
***************************************************************************************/
void zeraVals()
{
  valA = 0;
  valB = 0;
  valC = 0;
  valD = 0;
  valE = 0;
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
    for(int i = 0; i<3;i++)
    {
      digitalWrite(ledE, HIGH);
      delay(30);
      digitalWrite(ledE, LOW);
      delay(30);
    }
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
    for(int i = 0; i<3;i++)
    {
      digitalWrite(ledA, HIGH);
      delay(30);
      digitalWrite(ledA, LOW);
      delay(30);
    }
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
