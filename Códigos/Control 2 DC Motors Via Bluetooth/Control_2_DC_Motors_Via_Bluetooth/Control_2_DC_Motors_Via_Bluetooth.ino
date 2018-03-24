#include <SoftwareSerial.h>
 
const int TX_BT = 10;
const int RX_BT = 11;
 
SoftwareSerial btSerial(TX_BT, RX_BT);
 
//Frequency to send periodic messages to Windows Phone, in milliseconds.
//Core code.
const unsigned long periodicMessageFrequency = 5000;
unsigned long time = 0;
 
//Process the incoming command from Windows Phone.
//It should be changed according to what you want to do.
void processCommand(char* command) {
}
 
//Send a message back to the Windows Phone.
//Is can't be changed.
void sendMessage(char* message) {
  int messageLen = strlen(message);
  if(messageLen < 256) {  
    btSerial.write(messageLen);
    btSerial.print(message);
  }
}
 
//Send a set of periodic messages to the Windows Phone.
//It should be changed according to what you want to do.
//This message could be a sensor data, like a thermometer data.
void sendPeriodicMessages() {
}
 
//Setup Arduino function
void setup() {
  Serial.begin(9600);
  Serial.println("USB Connected");
  btSerial.begin(9600);
}
 
//Loop Arduino function
//It can't be changed
void loop() {
  if(btSerial.available()) {
      int commandSize = (int)btSerial.read();
      Serial.print(commandSize);
  /*    char command[commandSize];
      int commandPos = 0;
      while(commandPos < commandSize) {
        if(btSerial.available()) {
          command[commandPos] = (char)btSerial.read();
          commandPos++;
        }
      }
      command[commandPos] = 0;
      processCommand(command);
  }
  unsigned long currentTime = millis();
  if((currentTime - time) > periodicMessageFrequency) {
    sendPeriodicMessages();
    time = currentTime;*/
  }
}
