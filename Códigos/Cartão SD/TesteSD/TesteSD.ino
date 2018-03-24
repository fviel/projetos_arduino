/*
 PINAGEM DO CARTÃO PARA ARDUINO UNO, PRO MEGA ´R DIFERENTE
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 */
#include <SD.h>

boolean debug = true;
File myFile;

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("## Inicializacao do SD falhou.");
    return;
  }
  Serial.println("Cartao inicializado com sucesso.");
  Serial.println("Procurando o arquivo log.txt na raíz do cartao.");

  boolean arqEncontrado = arquivoExiste("log.txt");

  Serial.println("Criando o arquivo Viel.txt.");
  myFile = SD.open("Viel.txt", FILE_WRITE);
  myFile.close();




  /*
  // delete the file:
   Serial.println("Removing example.txt...");
   SD.remove("example.txt");
   
   if (SD.exists("example.txt")){ 
   Serial.println("example.txt exists.");
   }
   else {
   Serial.println("example.txt doesn't exist.");  
   }
   */
}

void loop()
{
  // nothing happens after setup finishes.
}

boolean arquivoExiste(char *arquivo){
  if(debug){
    Serial.print("Procurando o arquivo ");
    Serial.print(arquivo);
    Serial.println(".");
  }
  
  Serial.print("ARQUIVO:");
Serial.println(arquivo);
  
  if (SD.exists(arquivo)) {

    if(debug){
      Serial.print(arquivo);
      Serial.println(" encontrado.");
    }

    return true;
  }
  else {

    if(debug){
      Serial.print(arquivo);
      Serial.println(" nao encontrado.");
    }

    return false;
  }
}




