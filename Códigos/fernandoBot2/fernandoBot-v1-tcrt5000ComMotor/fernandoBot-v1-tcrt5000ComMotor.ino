#include <Servo.h>

#define CENTRO 90
#define ESQUERDA 115
#define DIREITA 65

Servo motor;

/*************************************************
* Public Constants
*************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

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
int DENA = 12; //(output pwm)
int DIN1 = 41;
int DIN2 = 43;
int DIN3 = 45;
int DIN4 = 47;
int DENB = 11; //(output pwm)

//pinagem da controladora traseira
int TENA = 10; //(output pwm)
int TIN1 = 31;
int TIN2 = 33;
int TIN3 = 35;
int TIN4 = 37;
int TENB = 9; //(output pwm)

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
int limiar = 600;

int cCounter = 150;

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
 
  motor.attach(28);
  
  servoCentro();

  //beep de carga completa
  beep();

  Serial.begin(9600);  //define frequencia da serial
}

/***************************************************************************************
LOOP
***************************************************************************************/
void loop()
{  
  
  Serial.println(" - INICIO LOOP - ");
  leSensoresLinha();

  /*******************************************************************************************
  OBSERVAÇÃO
  QUANDO ACENDO UM LED, QUER DIZER QUE ENCONTREI A LINHA PRETA. TECNICAMENTE, ISTO QUER DIZER
  QUE O SENSOR FOI DESATIVADO. O LED ACESO DÁ O ENTENDIMENTO CONTRÁRIO, POIS É O MAIS
  FÁCIL DE SER ENTENDIDO PARA O HUMANO.
  PORTANTO, ESTOU TRABALHANDO COM UMA LÓGICA INVERSA, CUIDADO.
  ********************************************************************************************/

  //4. TOMA AÇÃO NOS MOTORES
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
    delay(50);    
  }

  //uma vez parado, não volta a correr
  if (continuar == true)
  {
    //AVALIA SE HÁ OBSTÁCULO
    //int distance = leDistancia();
    int distance = 30;
    
    Serial.println(distance);
    if ((distance >= 10) || (distance <= 0))
    {
      Serial.println("Livre");      
      //4. TOMA AÇÃO NOS MOTORES
      //OK - nenhum sensor está ativo, o robô perdeu a linha, então ande de vagar para frente
      if ((A == false) && (B == false) && (C == false) && (D == false) && (E == false))
      {
        frente(500);
        delay(10);
        //pare();
      }

      //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
      if ((A == true) && (B == false) && (C == false) && (D == false) && (E == false))
      {
        cCounter = 150;
        Serial.print(" - A - \n");
        /*while (leSensorLinha('C') == false)
        {
          tras(1023);
          delay(25);
          direita(1023);
          delay(150);
          pare();
        }*/
      }

      //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
      if ((A == false) && (B == true) && (C == false) && (D == false) && (E == false))
      {
        cCounter = 150;
        Serial.print(" - B - \n");
        /*while (leSensorLinha('D') == false && leSensorLinha('C') == false)
        {
          tras(1023);
          delay(25);
          direita(1023);
          delay(150);
          pare();
        }*/
      }

      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      if (C == true)
      {
        cCounter = cCounter+50;//cria uma aceleração para a direção C
        if(cCounter >= 1000)
        {
          cCounter = 1023;
        }
        Serial.print(" - C - \n");
        frente(cCounter);
        delay(5);       
      }

      //DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
      if ((A == false) && (B == false) && (C == false) && (D == true) && (E == false))
      {
        cCounter = 150;
        Serial.print(" - D - \n");
        /*while (leSensorLinha('B') == false && leSensorLinha('C') == false)
        {
          tras(1023);
          delay(25);
          esquerda(1023);
          delay(150);
          pare();
        }*/
      }

      //EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
      if ((A == false) && (B == false) && (C == false) && (D == false) && (E == true))
      {
        cCounter = 150;
        Serial.print(" - E - \n");
        /*while (leSensorLinha('E') == false)
        {
          tras(1023);
          delay(25);
          esquerda(1023);
          delay(150);
          pare();
        }*/
      }
    }
    else
    {
      beep();
      pare();
  
      //coloca o servo no centro 
      servoCentro();
      delay(50);  

      //vira à esquerda
      servoEsquerda();
      delay(50);
 
      servoCentro();
      delay(50);  
 
      //vira à direita
      servoDireita();
      delay(50); 
  
      delay(50);
    }//fim if distância
  }//fim if continuar
  debugSensor();
  zeraVals();
  Serial.println(" - FIM LOOP - ");
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
  /*
  dMotorA(TRAS,   vel);
  dMotorB(FRENTE, vel);
  tMotorA(TRAS,   vel);
  tMotorB(FRENTE, vel);
  */
  
  dMotorA(FRENTE, vel/3);
  dMotorB(FRENTE, vel);
  tMotorA(FRENTE, vel/3);
  tMotorB(FRENTE, vel);
}


/***************************************************************************************
ESQUERDA
***************************************************************************************/
void esquerda (int vel)
{
  /*
  dMotorA(FRENTE, vel);
  dMotorB(TRAS,   vel);
  tMotorA(FRENTE, vel);
  tMotorB(TRAS,   vel);
  */
  dMotorA(FRENTE, vel);
  dMotorB(FRENTE, vel/3);
  tMotorA(FRENTE, vel);
  tMotorB(FRENTE, vel/3);
}

/***************************************************************************************
LESENSORESLINHA
***************************************************************************************/
void leSensoresLinha()
{
  //1. LÊ OS SENSORES
  valA = analogRead(analogPinA);
  valB = analogRead(analogPinB);
  valC = analogRead(analogPinC);
  valD = analogRead(analogPinD);
  valE = analogRead(analogPinE) - 250;

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
}

/***************************************************************************************
LESENSORLINHA
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
  return (resp);
}

/***************************************************************************************
DEBUGSENSOR
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
***************************************************************************************/
void beep()
{
  tone(beeper, NOTE_G3, 100);
  delay(100);
  tone(beeper, NOTE_F4, 100);
  delay(100);
  noTone(beeper);
  delay(50);
}

/***************************************************************************************
ZERAVALS
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
TROCASENTIDO
***************************************************************************************/
boolean trocaSentido(boolean Sentido)
{
  if (Sentido == HIGH)
  {
    Sentido = LOW;
  }
  else
  {
    Sentido = HIGH;
  }
  return (Sentido);
}

/***************************************************************************************
DMOTORA
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
***************************************************************************************/
int leDistancia()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

/***************************************************************************************
Posiociona servo no centro
***************************************************************************************/
void servoCentro()
{
  motor.write(CENTRO);
}

void servoEsquerda()
{
  /*  
  for(int i=CENTRO;i<ESQUERDA;i++){
    motor.write(i);
  }
  */
  motor.write(ESQUERDA);  
}

void servoDireita()
{
  motor.write(DIREITA);
}
