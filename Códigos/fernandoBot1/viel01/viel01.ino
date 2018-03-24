

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

boolean DEBUG = true;

//struct que armazena as leituras de distÃ¢ncias dos sensores us
struct dst
{
  long dstA;
  long dstB;
};
struct dst dist;

// notas musicais da melodia
int melody[] = { 
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// duraÃ§Ã£o das notas musicais: 4 = quarto de nota, 8 = oitava de nota, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

long mila=0;
long milb=0;

//Controle beeper
const int BEEPER=13;

//Define a distancia de mediÃ§Ã£o de perigo
const int DSTPERIGO = 40;

//Controle dos motores
const int ENA=32;
const int IN1=30;
const int IN2=28;
const int IN3=26;
const int IN4=24;
const int ENB=22;

//Sensores de distÃ¢ncia
const int Aecho=9;
const int Atrig=10;
const int Becho=2;
const int Btrig=4;

//INFELIZES VARIAVEIS GLOBAIS
//flag de sentigo para curvas
boolean Sentido = HIGH;

//Vars do bluetooth
char val;
int incomingByte = 0;   // for incoming serial data
//======================================================================

void setup()
{
  //inicializa a serial, inclusive o bluetooth
  Serial.begin(38400); 



  //define pinos como de output
  pinMode(ENA,OUTPUT); // define a velicidade do motor A
  pinMode(ENB,OUTPUT); // define a velicidade do motor B
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(BEEPER, OUTPUT);

  //inicializa variÃ¡veis do motor A
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);

  //inicializa variÃ¡veis do motor B 
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  //inicializa porta dos sensores
  pinMode(Atrig, OUTPUT);
  pinMode(Aecho, INPUT);
  pinMode(Btrig, OUTPUT);
  pinMode(Becho, INPUT);

  //toca a musicola  
  //beepAlive();  
}


void loop()
{
  /*
  mila=millis();
   dist.dstA=0;
   dist.dstB=0;
   
   if(DEBUG)
   {
   Serial.print("millis: ");
   Serial.println(milb-mila);
   Serial.print("ANTES distancia A: ");
   Serial.println(dist.dstA);
   Serial.print("ANTES distancia B: ");
   Serial.println(dist.dstB);
   }
   
   //LÃª os sensores
   leDist(&dist);
   
   if(DEBUG)
   {
   Serial.print("DEPOIS - distancia A: ");
   Serial.print(dist.dstA);
   Serial.println("cm;");
   Serial.print("DEPOIS - distancia B: ");
   Serial.print(dist.dstB);
   Serial.println("cm;");
   Serial.println("---------------------------");
   }
   
   //FunÃ§Ãµes de beep
   if (((dist.dstA <= DSTPERIGO) && (dist.dstA >= 0)))
   {
   beep((dist.dstA*10)+1200);
   }
   
   if (((dist.dstB <= DSTPERIGO) && (dist.dstB >= 0)))
   {
   beep((dist.dstB*10)+100);
   }
   
   //encurralado
   if ((((dist.dstA <= DSTPERIGO) && (dist.dstA >= 0))) && (((dist.dstB <= DSTPERIGO) && (dist.dstB >= 0))))
   {
   Sentido = LOW;
   int i = 0;
   //acelera suavemente pra frente
   direita(Sentido, 255 - dist.dstA);
   
   //por 250 milis anda pra frente
   //delay(250);
   
   //desacelera os motores atÃ© parar
   desaceleraMotores(Sentido);
   }
   */

  /*
  //funÃ§Ãµes de motores 
   if (((dist.dstA <= DSTPERIGO) && (dist.dstA >= 0)))
   {    
   Sentido = LOW;
   int i = 0;
   //acelera suavemente pra frente
   aceleraMotores(Sentido, 255 - dist.dstA);
   
   //por 250 milis anda pra frente
   delay(250);
   
   //desacelera os motores atÃ© parar
   desaceleraMotores(Sentido);
   
   }  
   
   if (((dist.dstB <= DSTPERIGO) && (dist.dstB >= 0)))
   {
   Sentido = HIGH;
   int i = 0;
   //acelera suavente pra frente
   aceleraMotores(Sentido, 255 - dist.dstB);
   
   //por 250 milis anda pra frente
   delay(250);
   
   //para os motores
   desaceleraMotores(Sentido); 
   }  
   
   
   milb=millis();*/

  /*aceleraMotores(1, 255);
   delay(100);
   desaceleraMotores(1);*/











}

void serialEvent(){
  int comando=0;
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    //Serial.print("Recebi: ");
    //Serial.println(incomingByte, DEC);
    comando = incomingByte;
    incomingByte=0;
  }

  switch(comando){
  case 49:
    {
      Serial.println("Frente.");  
      aceleraMotores(1,255);
    }
    break;
  case 50:
    {
      Serial.println("Esquerda.");  
      esquerda(255);  
    }
    break;
  case 51:
    {
      Serial.println("Parar.");    
      motorA(1,0);
      motorB(1,0);
    }
    break;
  case 52:
    {
      Serial.println("Direita.");  
      direita(255);
    }
    break;
  case 53:
    {
      Serial.println("Tras.");   
      aceleraMotores(0,255); 
    }
    break;
  default: 
    {
      Serial.println("Comando não reconhecido.");    
    }
    break;
  }

}

/*****************************************
 * Leitura da distancia dos sensores
 *****************************************/
void leDist(struct dst *A)
{
  long durA=15000;
  //while(durA > 12000)
  {
    //leitura do sensor A
    durA=0;
    digitalWrite(Atrig, LOW);
    digitalWrite(Atrig, HIGH);
    delayMicroseconds(10); 
    digitalWrite(Atrig, LOW);
    durA = pulseIn(Aecho, HIGH);
  }


  long durB = 15000;
  //while(durB > 12000)
  {
    //leitura do sensor B
    durB=0;
    digitalWrite(Btrig, LOW);
    digitalWrite(Btrig, HIGH);
    delayMicroseconds(10); 
    digitalWrite(Btrig, LOW);
    durB = pulseIn(Becho, HIGH);
  }

  if(DEBUG)
  {
    Serial.println("leDist(struct dst *A)");
    Serial.print("durA: ");
    Serial.print(durA);
    Serial.println("ms;");
    Serial.print(durB);
    Serial.println("ms;");
  }



  //calcula distancia e joga no ponteiro
  A->dstA = (durA/2) / 29.1;
  A->dstB = (durB/2) / 29.1;
}

/***************************************
 * emite um beep conforme o tom solicitado
 ***************************************/
void beep(int tom)
{
  tone(BEEPER, tom, 50);
  //Adiciona 20% de tempo da duraÃ§Ã£o da nota
  //delay(20);
  // para o toque
  noTone(BEEPER);
  // delay(20);   
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


void direita(int velocidade)
{
  for (int i = 0; i < velocidade; i = i + 25)
  {
    motorA(1,i);
    motorB(1,i);      
    delay(60);
  }
  motorA(1,0);  
  motorB(1,0);  
}

void esquerda(int velocidade)
{
  for (int i = 0; i < velocidade; i = i + 25)
  {
    motorA(0,i);
    motorB(0,i);      
    delay(60);
  }
  motorB(0,255);      
   delay(20);  
  motorA(1,0);  
  motorB(1,0); 
}


void direita(boolean Sentido, int velocidade)
{
  for (int i = 0; i < velocidade; i = i + 25)
  {
    motorA(Sentido,i);
    motorB(Sentido,i);      
    delay(25);
  }   
}

void esquerda(boolean Sentido, int velocidade)
{
  for (int i = 0; i < velocidade; i = i + 25)
  {
    motorA(trocaSentido(Sentido),i);
    motorB(trocaSentido(Sentido),i);      
    delay(25);
  }   
}

void aceleraMotores(boolean Sentido, int velocidade)
{
  for (int i = 0; i < velocidade; i = i + 25)
  {
    motorA(Sentido,i);
    motorB(trocaSentido(Sentido),i);      
    delay(25);
  }   
}

void desaceleraMotores(boolean Sentido)
{
  for (int j = 200; j > 0 ; j = j - 10)
  {
    motorA(Sentido,j);
    motorB(trocaSentido(Sentido),j);      
    delay(25);
  }  
}

/***************************************
 * Inverte a variÃ¡vel sentido
 ***************************************/
boolean trocaSentido(boolean Sentido)
{
  if(Sentido==HIGH)
  {
    Sentido=LOW;
  }
  else
  {
    Sentido=HIGH;
  }
  return(Sentido);
}


/***************************************
 * Gira o motor conforme o sentido solicitado
 ***************************************/
void motorA(boolean sentido, int velocidade)
{
  if(sentido==1)
  {
    motorAFrente(velocidade);
  }
  else
  {
    motorARe(velocidade);
  }
}

/***************************************
 * Aciona a pinagem do motor A pra frente
 ***************************************/
void motorAFrente(int velocidade)
{
  //para o motor
  digitalWrite(ENA,0);

  digitalWrite(IN1,0); 
  digitalWrite(IN2,1);
  analogWrite(ENA,velocidade);
}

/***************************************
 * Aciona a pinagem do motor A pra trÃ¡s
 ***************************************/
void motorARe(int velocidade)
{
  //para o motor
  digitalWrite(ENA,0);

  digitalWrite(IN1,1); 
  digitalWrite(IN2,0);
  analogWrite(ENA,velocidade);
}

/***************************************
 * Inverte sentidos do motor B
 ***************************************/
void motorB(boolean sentido, int velocidade)
{
  if(sentido==1)
  {
    motorBFrente(velocidade);
  }
  else
  {
    motorBRe(velocidade);
  }
}

/***************************************
 * Aciona a pinagem do motor B pra frente
 ***************************************/
void motorBFrente(int velocidade)
{
  //pÃ¡ra o motor
  digitalWrite(ENB,0);

  digitalWrite(IN3,0); 
  digitalWrite(IN4,1);
  analogWrite(ENB,velocidade);
}

/***************************************
 * Aciona a pinagem do motor B pra trÃ¡s
 ***************************************/
void motorBRe(int velocidade)
{
  //pÃ¡ra o motor
  digitalWrite(ENB,0);
  digitalWrite(IN3,1); 
  digitalWrite(IN4,0);
  analogWrite(ENB,velocidade);
}






