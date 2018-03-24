
#define trigPin 8
#define echoPin 9
#define blockedLedPin 13
#define cleanLedPin 12


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //inicializa os leds
  pinMode(blockedLedPin, OUTPUT);
  pinMode(cleanLedPin, OUTPUT); 
}

void loop() 
{
  int distancia = leDistancia();
  if ((distancia >= 100) || (distancia <= 0))
  {
    
    //Acende o led de livre  
    leds(true);
    
    Serial.println("Livre");   
    
  }
  else {
    //Acende o led de bloqueio    
    leds(false);
    
    Serial.print("Obstruido - Distancia medida: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }
}

void leds(boolean estado)
{
  if(estado == true)
  {
    //LIVRE
    digitalWrite(blockedLedPin,LOW);
    digitalWrite(cleanLedPin,HIGH);
  }
  else
  {
    //OBSTRUÍDO
    digitalWrite(blockedLedPin,HIGH);
    digitalWrite(cleanLedPin,LOW);
  }
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



