#include "tones.h"
#include "lineSensor.h"


#define DEBUG 0

//cria objeto do sensor de linha
LineSensor ls;


//define se o robo deve continuar andando ou parar até proximo reset de energia
boolean continuar = true;

//Variáveis de controle dos motores e ponte H 298
#define FRENTE 1
#define TRAS 0

//pinagem da controladora dianteira
#define ENA 2 //(output pwm)
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENB 7 //(output pwm)


//Variáveis de controle de som
int beeper = 9; //definição do pino do beeper
boolean tocouMusica = false;
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4 };

//define a velocidade máxima de movimento do robô
int velo = 750;
//int velo = 1020;

/***************************************************************************************
SETUP
***************************************************************************************/
void setup()
{
  pinMode(beeper, OUTPUT);
  
  //**********************
  //CONTROLADORA 
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  
  //liga os pinos do sensor de linha e leds
  ls.attach();
  ls.calibrateSensors();

  //beep de carga completa
  beep();

  if(DEBUG==1)
  {
    //define frequencia da serial
    Serial.begin(9600);  
  }
  
  //musicola();
  
  
}

/***************************************************************************************
LOOP
***************************************************************************************/
void loop()
{
  ls.readSensors();
  ls.processReadings();
  if(DEBUG==1)
  {
    serialDebug();
  }
  
  //TUDO TRUE - Todos os sensores foram acionados juntos, ou seja, o robô estã longe do chão 
  if ((ls.getDigitalReading('A') == true) && (ls.getDigitalReading('B') == true) && (ls.getDigitalReading('C') == true) && (ls.getDigitalReading('D') == true) && (ls.getDigitalReading('E') == true) && (ls.getDigitalReading('F') == true) && (ls.getDigitalReading('G') == true) )
  {
    pare();
    continuar = false;
    if (tocouMusica == false)
    {
      //musicola();
      tocouMusica = true;      
    }
  } 
  else
  {
    
    
    //uma vez parado, não volta a correr
    if (continuar == true)    
    {
      /*
      SE NENHUM SENSOR ESTIVER ATIVO, ENTÃO ESTOU FORA DA LINHA
      SOLUÇÃO: ANDE DEVEGAR ATÉ ACHAR A LINHA.
      */
      if ((ls.getDigitalReading('C') == false) &&(ls.getDigitalReading('D') == false) && (ls.getDigitalReading('E') == false))
      {
        frente(velo);
        delay(25); 
        pare();
        delay(15);
      }
      
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      /*
      ACIONEI SENSOR DA DIREITA E AINDA TENHO LEITURA DO SENSOR CENTRAL.
      SIGNIFICADO: ESTOU SAINDO PARA A BORDA DIREITA, ENTÃO PRECISO VIRAR PRA DIREITA
      SOLUÇÃO: SIGA PARA FRENTE, MAS DIMINUA A VELOCIDADE DO MOTOR A (DIREITO)
      */
      if ((ls.getDigitalReading('C') == true) && (ls.getDigitalReading('E') == false))
      {
        direita(velo);
        delay(15);
        pare();
        delay(50); 
      }
    
      //DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
      if ((ls.getDigitalReading('C') == false) &&(ls.getDigitalReading('D') == true) && (ls.getDigitalReading('E') == false))
      {
        frente(velo);
        delay(15);
        pare();
        delay(50);        
      }
      
      //EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
      if ((ls.getDigitalReading('C') == false) && (ls.getDigitalReading('E') == true))
      {
        esquerda(velo);
        delay(15);
        pare();
        delay(50);
      }
      
    }//fim continuar
  }//fim else
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
  MotorA(FRENTE, 0);
  MotorB(FRENTE, 0);
}

/***************************************************************************************
FRENTE
***************************************************************************************/
void frente (int vel)
{
  MotorA(FRENTE, vel);
  MotorB(FRENTE, vel);
}


/***************************************************************************************
FRENTE
***************************************************************************************/
void frente (int velA, int velB)
{
  MotorA(FRENTE, velA);
  MotorB(FRENTE, velB);
}

/***************************************************************************************
TRAS
***************************************************************************************/
void tras (int vel)
{
  MotorA(TRAS, vel);
  MotorB(TRAS, vel);
}

/***************************************************************************************
DIREITA
***************************************************************************************/
void direita (int vel)
{
  MotorA(TRAS, vel/2);
  MotorB(FRENTE, vel); 
}


/***************************************************************************************
ESQUERDA
***************************************************************************************/
void esquerda (int vel)
{
  MotorA(FRENTE, vel);
  MotorB(TRAS, vel/2);
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
void MotorA(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    MotorAFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    MotorARe(velocidade);
  }
}

/***************************************************************************************
DMOTORAFRENTE
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void MotorAFrente(int velocidade)
{
  digitalWrite(ENA, 0);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(ENA, velocidade);
}

/***************************************************************************************
DMOTORARE
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void MotorARe(int velocidade)
{
  digitalWrite(ENA, 1);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(ENA, velocidade);
}


/***************************************************************************************
DMOTORB
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void MotorB(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    MotorBFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    MotorBRe(velocidade);
  }
}

/***************************************************************************************
MOTORBFRENTE
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void MotorBFrente(int velocidade)
{
  digitalWrite(ENB, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENB, velocidade);
}

/***************************************************************************************
DMOTORBRE
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void MotorBRe(int velocidade)
{
  digitalWrite(ENB, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENB, velocidade);
}


void serialDebug()
{
  Serial.print("\nA-DIGITAL: ");
  Serial.println(ls.getDigitalReading('A'));
  Serial.print("A-ANALOG: ");
  Serial.println(ls.getAnalogReading('A'));
  Serial.print("Compensacao A: ");
  Serial.println(ls.getCompensateVar('A'));  
  
  Serial.print("B-DIGITAL: ");
  Serial.println(ls.getDigitalReading('B'));
  Serial.print("B-ANALOG: ");
  Serial.println(ls.getAnalogReading('B'));
  Serial.print("Compensacao B: ");
  Serial.println(ls.getCompensateVar('B'));
   
  Serial.print("C-DIGITAL: ");
  Serial.println(ls.getDigitalReading('C'));
  Serial.print("C-ANALOG: ");
  Serial.println(ls.getAnalogReading('C'));
  Serial.print("Compensacao C: ");
  Serial.println(ls.getCompensateVar('C'));
  
  Serial.print("D-DIGITAL: ");
  Serial.println(ls.getDigitalReading('D'));
  Serial.print("D-ANALOG: ");
  Serial.println(ls.getAnalogReading('D'));
  Serial.print("Compensacao D: ");
  Serial.println(ls.getCompensateVar('D'));

  Serial.print("E-DIGITAL: ");
  Serial.println(ls.getDigitalReading('E'));
  Serial.print("E-ANALOG: ");
  Serial.println(ls.getAnalogReading('E'));
  Serial.print("Compensacao E: ");
  Serial.println(ls.getCompensateVar('E'));
  
  Serial.print("F-DIGITAL: ");
  Serial.println(ls.getDigitalReading('F'));
  Serial.print("F-ANALOG: ");
  Serial.println(ls.getAnalogReading('F'));
  Serial.print("Compensacao F: ");
  Serial.println(ls.getCompensateVar('F'));
  
  Serial.print("G-DIGITAL: ");
  Serial.println(ls.getDigitalReading('G'));
  Serial.print("G-ANALOG: ");
  Serial.println(ls.getAnalogReading('G'));
  Serial.print("Compensacao G: ");
  Serial.println(ls.getCompensateVar('G'));
  Serial.println("---------------------------------------------------");
}
