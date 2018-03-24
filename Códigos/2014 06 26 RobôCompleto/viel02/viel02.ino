#include <LiquidCrystal.h>

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

//======================================================================
//PINAGEM DO MEGA
//======================================================================

//Controle beeper
#define BEEPER 12

//Controle dos motores
#define ENA 53
#define IN1 51
#define IN2 49
#define IN3 47
#define IN4 45
#define ENB 43

#define echoPin 50
#define trigPin 48

#define obstaclePin 52
//======================================================================


//======================================================================
//VARIAVEIS GLOBAIS DE CONFIGURAÇÃO
//======================================================================

/*
 * LCD RS     - digital pin 32
 * LCD Enable - digital pin 30
 * LCD D4     - digital pin 28
 * LCD D5     - digital pin 26
 * LCD D6     - digital pin 24
 * LCD D7     - digital pin 22
 * LCD R/W    - ground
 */

//Inicializa pinos
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);

boolean obstruido = false;


// notas musicais da melodia
int melody[] = { 
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// duracao das notas musicais: 4 = quarto de nota, 8 = oitava de nota, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

//define se está em modo de DEBUG, exibindo mesg na serial
boolean DEBUG = true;

//matriz de média de valores
unsigned int sLDRs[5][100];

//controlador de insersao de valores
unsigned int ultimaPos = 0;


void setup()
{
  // Define 20 colunas por 4 linhas - LCD Hitachi j204a
  lcd.begin(20, 4);
  lcd.noBlink();

  //inicializa a serial, inclusive o bluetooth
  Serial.begin(38400);

  //define pinos como de output
  pinMode(ENA,OUTPUT); 
  pinMode(ENB,OUTPUT); 
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(obstaclePin,OUTPUT);

  pinMode(BEEPER, OUTPUT);

  //inicializa variaveis do motor A
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,LOW);

  //inicializa variaveis do motor B 
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  //pinagem do sensor de distancia
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //toca a musicola de inicio
  beepAlive();

  lcdTest(); 

  lcd.setCursor(0,3);
  lcd.print("Distancia (cm):     ");

}

/***************************************************************
 *loooooooop
 ***************************************************************/
void loop()
{
  digitalWrite(obstaclePin,LOW);
  int distance=leDistancia();

  lcd.setCursor(15,3);
  lcd.print("     "); 
  lcd.setCursor(15,3); 
  lcd.print(distance);  

  //LIVRE
  if ((distance >= 20) || (distance <= 0))
  { 
    obstruido=false;   
  }
  else //OBSTRUIDO
  {
    obstruido=true;
  }
  
  while(obstruido == true)
  {   
    digitalWrite(obstaclePin,HIGH); 
    if(DEBUG)
    {
       Serial.print("Obstruido: ");
       Serial.println(distance);
    }
    
    tras(200);
    delay(10);
    parar();
    distance=leDistancia();
    if (distance > 10)
    {
      obstruido = false;
    }
  } 
  
}

/***************************************************************
 *Método que é chamado sempre que um evento na serial 0 ocorre.
 ***************************************************************/
void serialEvent()
{
  /*
  int comando=0;
   CODIGO REMOVIDO PARA MELHORAR RESPONSIVIDADE
   if (Serial.available() > 0) 
   {
   comando = Serial.read();
   }*/

  unsigned int comando = Serial.read();
  int vel =200; 
  switch(comando)
  {
  case 49:
    {
      if(!obstruido)
      {        
        if(DEBUG)
        {
          Serial.println("Frente.");  
        }
        //lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Frente");
        frente(vel);   
      }
    }
    break;
  case 50:
    { 
      if(DEBUG)
      {     
        Serial.println("Direita.");  
      }
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Direita");
      direita(vel); 
    }
    break;
  case 51:
    {
      if(DEBUG)
      {
        Serial.println("Parar.");    
      }
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pare");
      parar();  
    }
    break;
  case 52:
    {
      if(DEBUG)
      {
        Serial.println("Esquerda.");
      }
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Esquerda");
      esquerda(vel -50 );
    }
    break;
  case 53:
    {
      if(DEBUG)
      {
        Serial.println("Tras.");  
      }
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tras");
      tras(vel -50);
    }
    break;
  case 54:
    {
      if(DEBUG)
      {
        Serial.println("Beeep!");  
      }
      lcd.setCursor(0,0);
      lcd.print("Beeeeeeeeep!");
      beep(150);
    }
    break; 
  default: 
    {
      if(DEBUG)
      {
        beep(10);
        beep(10);
        beep(10);
        Serial.println("Comando não reconhecido.");    
      }
    }
    break;
  }
}

/***************************************
 * emite um beep conforme o tom solicitado
 ***************************************/
void beep(int duracao)
{
  analogWrite(BEEPER,100);
  delay(duracao); //recomendado 15
  analogWrite(BEEPER,0);
}

/***************************************
 * emite um beep conforme o tom solicitado
 ***************************************/
void beepTone(int tom)
{
  tone(BEEPER, tom, 250);
  // para o toque
  noTone(BEEPER);
}

/***************************************
 * Toca a musica de start!
 ***************************************/
void beepAlive()
{
  //toca a melodia
  for (int thisNote = 0; thisNote < 8; thisNote++) 
  {
    //para a calcular a duraÃ§Ã£o, divide 1 segundo pelo tempo da nota, exemplo 1000/4
    int noteDuration = 1000/noteDurations[thisNote];
    //toca a nota musical
    tone(BEEPER, melody[thisNote],noteDuration);
    //Adiciona 20% de tempo da duraÃ§Ã£o da nota
    delay(noteDuration * 1.20);
    // para o toque
    noTone(BEEPER);
  }
}

void frente(int vel)
{
  Serial.println("Frente.");  

  digitalWrite(ENA,1);
  digitalWrite(IN1,1); 
  digitalWrite(IN2,0);

  digitalWrite(ENB,1);
  digitalWrite(IN3,0); 
  digitalWrite(IN4,1);

  //anda para frente
  analogWrite(ENB,vel);   
  analogWrite(ENA,vel);   
}

void tras(int vel)
{
  Serial.println("Tras.");  

  digitalWrite(ENA,1);
  digitalWrite(IN1,0); 
  digitalWrite(IN2,1);

  digitalWrite(ENB,1);
  digitalWrite(IN3,1); 
  digitalWrite(IN4,0);

  //anda para frente
  analogWrite(ENB,vel);   
  analogWrite(ENA,vel);   
}

void parar()
{
  Serial.println("Parar.");    

  digitalWrite(ENA,1);
  digitalWrite(IN1,0); 
  digitalWrite(IN2,1);

  digitalWrite(ENB,1);
  digitalWrite(IN3,1); 
  digitalWrite(IN4,0);

  //para o robo
  analogWrite(ENB,0);   
  analogWrite(ENA,0);   
}

void direita(int vel)
{
  Serial.println("Direita.");  
  digitalWrite(ENA,1);
  digitalWrite(IN1,1); 
  digitalWrite(IN2,0);

  digitalWrite(ENB,1);
  digitalWrite(IN3,1); 
  digitalWrite(IN4,0);

  //anda para frente
  analogWrite(ENB,vel);   
  analogWrite(ENA,vel);   
}

void esquerda(int vel)
{
  Serial.println("Esquerda.");

  digitalWrite(ENA,1);
  digitalWrite(IN1,0); 
  digitalWrite(IN2,1);

  digitalWrite(ENB,1);
  digitalWrite(IN3,0); 
  digitalWrite(IN4,1);

  //anda para frente
  analogWrite(ENB,vel);   
  analogWrite(ENA,vel);   
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

void lcdTest()
{
  lcd.setCursor(0,0);
  lcd.print("Sistema inicializado.");
  lcd.setCursor(0,1);
  lcd.print("Compilacao 16/06/14");  
  lcd.setCursor(0,2);      
  lcd.print("--------------------");
  lcd.setCursor(0,3);      
  lcd.print("--------------------");

  delay(2000);
}

