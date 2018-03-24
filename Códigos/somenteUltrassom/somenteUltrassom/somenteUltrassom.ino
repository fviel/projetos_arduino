#define echoPin 46
#define trigPin 47
#define beepPin 13

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
  }
  else {
    Serial.print("Obstruido - Distancia medida: ");
    Serial.print(distance);
    Serial.println(" cm");
    analogWrite(beepPin, 10*distance);
    delay(10);
    analogWrite(beepPin, 0);
    delay(10*distance);
    
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



