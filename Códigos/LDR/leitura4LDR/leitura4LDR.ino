
int L0=0;
int L1=0;
int L2=0;
int L3=0;
int L4=0;

void setup()
{
Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
}
 
void loop()
{

L0 = analogRead(A0);
L1 = analogRead(A1);
L2 = analogRead(A2);
L3 = analogRead(A3);
L4 = analogRead(A4);


Serial.print(L0);
Serial.print("|");
Serial.print(L1);
Serial.print("|");
Serial.print(L2);
Serial.print("|");
Serial.print(L3);
Serial.print("|");
Serial.print(L4);
Serial.println("|");

delay(500); 
}
