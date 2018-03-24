/*
  TCRT5000 IR Sensor Test Analog
 Reads a analog input on pin A0, prints the result to the serial monitor 
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(0);
  Serial.println(sensorValue);
  delay(100);
}
