/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 More info at: http://goo.gl/kJ8Gl
 */

#define trigPin 13
#define echoPin 12
#define blockedLedPin 11

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(blockedLedPin, LOW);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line

  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    Serial.println("Fora de alcance");
    //Apaga o led de bloqueio
    digitalWrite(blockedLedPin,LOW);
  }
  else {
    Serial.print("Distancia medida: ");
    Serial.print(distance);
    Serial.println(" cm");
    //Acende o led de bloqueio
    digitalWrite(blockedLedPin,HIGH);
  }
  delay(500);
}
