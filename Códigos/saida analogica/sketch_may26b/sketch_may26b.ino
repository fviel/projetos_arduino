//declare variables/
float tempC;
int sensorAPin = 0;
int sensorBPin = 0;
 
void setup()
{
Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
}
 
void loop()
{
tempC = (analogRead(sensorAPin)+analogRead(sensorAPin))/2; //lê dois sensores e faz a média
tempC = (5.0 * tempC * 100.0)/1024.0; //converte em celsius
Serial.println();
Serial.print(tempC); //send the data to the computer
delay(100); //wait one second before sending new data
}
