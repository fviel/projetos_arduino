int ENA=8;//connected to Arduino's port 5(output pwm)
int IN1=9;//connected to Arduino's port 2
int IN2=10;//connected to Arduino's port 3
int IN3=11;//connected to Arduino's port 4
int IN4=12;//connected to Arduino's port 7
int ENB=13;//connected to Arduino's port 6(output pwm)


boolean Sentido = HIGH;

void setup()
{
  
 Serial.begin(9600); 
 Serial.print("Serial inicializada...");
 
 //define pinos como de output
  pinMode(ENA,OUTPUT);//output
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  //inicializa variáveis do motor A
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  
  //inicializa variáveis do motor B 
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void loop()
{
  Serial.print("Começou");
  
  Sentido = trocaSentido(Sentido);
  
  for(int i = 255; i >0; i--)
  {
   // motorA(Sentido,i);
   // motorB(Sentido,i);
    Serial.print("F" + i);
    delay(10000);
  }
}

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

/*
*Função principal para controle de sentido do motor A
*
*/
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

void motorAFrente(int velocidade)
{
  digitalWrite(ENA,0);
  digitalWrite(IN1,0); 
  digitalWrite(IN2,1);
  analogWrite(ENA,velocidade);
}

void motorARe(int velocidade)
{
  digitalWrite(ENA,1);
  digitalWrite(IN1,1); 
  digitalWrite(IN2,0);
  analogWrite(ENA,velocidade);
}

/*
*Função principal para controle de sentido do motor B
*
*/
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

void motorBFrente(int velocidade)
{
  digitalWrite(ENB,0);
  digitalWrite(IN3,0); 
  digitalWrite(IN4,1);
  analogWrite(ENB,velocidade);
}

void motorBRe(int velocidade)
{
  digitalWrite(ENB,1);
  digitalWrite(IN3,1); 
  digitalWrite(IN4,0);
  analogWrite(ENB,velocidade);
}


