//declare variables/
float tempC;
float valLed;
int sensorAPin = 0;
int sensorBPin = 1;
int led = 5;
 
void setup()
{
Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
}
 
void loop()
{
//tempC = (analogRead(sensorAPin)+analogRead(sensorBPin))/2; //lê dois sensores e faz a média
//tempC = (5.0 * tempC * 100.0)/1024.0; //converte em celsius
valLed = analogRead(led);
Serial.println();
Serial.print(valLed); //send the data to the computer
delay(100); //wait one second before sending new data
}
