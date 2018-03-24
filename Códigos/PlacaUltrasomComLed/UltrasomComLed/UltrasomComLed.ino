#define echoPin 9
#define trigPin 8
#define beepPin 4

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //LÊ o sensor de ultrasom 
  int distance=leDistancia();
  
  if ((distance >= 200) || (distance <= 0))
  {
    Serial.println("Livre");
    digitalWrite(beepPin, 0);
  }
  else {
    Serial.print("Obstruido - Distancia medida: ");
    Serial.print(distance);
    Serial.println(" cm");
    int led=255-(10*distance);
    if(led >255)
    {
      led=255;
    }
    if(led <0)
    {
      led=0;
    }
    analogWrite(beepPin, led);
    delay(10);   
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



