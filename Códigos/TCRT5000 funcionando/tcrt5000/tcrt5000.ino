//http://blog.fazedores.com/sensor-optico-reflexivo-tcrt5000-com-arduino/


int analogPinA = 0; 
int analogPinB = 1; 
int analogPinC = 2; 
int analogPinD = 3; 
int analogPinE = 4; 

int valA = 0;
int valB = 0;
int valC = 0;
int valD = 0;
int valE = 0;

int ledA = 7;
int ledB = 6;
int ledC = 5;
int ledD = 8;
int ledE = 9        ;

//limiar de detecção
int limiar = 650;
   /************************/
   
//configurando os pinos (executado apenas uma vez)
void setup(){
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
  
  Serial.begin(9600);  //define frequencia da serial
}
 
//laço principal (executado infinitamente)
void loop() 
{
  valA = analogRead(analogPinA);   
  valB = analogRead(analogPinB);   
  valC = analogRead(analogPinC);    
  valD = analogRead(analogPinD);    
  valE = analogRead(analogPinE);    

  Serial.print("A: "); 
  Serial.print(valA);
  Serial.print("| B: "); 
  Serial.print(valB);
  Serial.print("| C: "); 
  Serial.print(valC);
  Serial.print("| D: "); 
  Serial.print(valD);
  Serial.print("| E: "); 
  Serial.print(valE);
  Serial.print("\n**********************************\n");

  if (valA < limiar){
    digitalWrite(ledA,LOW);
  }else{  
    digitalWrite(ledA,HIGH);
  }
  
  if (valB < limiar){
    digitalWrite(ledB,LOW);
  }else{  
    digitalWrite(ledB,HIGH);
  }
  
  if (valC < limiar){
    digitalWrite(ledC,LOW);
  }else{  
    digitalWrite(ledC,HIGH);
  }
  
  if (valD < limiar){
    digitalWrite(ledD,LOW);
  }else{  
    digitalWrite(ledD,HIGH);
  }
  
  if (valE < limiar){
    digitalWrite(ledE,LOW);
  }else{  
    digitalWrite(ledE,HIGH);
  }
  
  zeraVals();

}

void zeraVals()
{
  valA = 0;
  valB = 0;
  valC = 0;
  valD = 0;
  valE = 0;
}
