//#ifndef lineSensor_h
	//#define lineSensor_h
	#include <Arduino.h>
	#include <inttypes.h>
	
	//representa as leituras com valores de 0 a 1023 dos sensores
	typedef struct{
		unsigned int A = 0;
		unsigned int B = 0;
		unsigned int C = 0;
		unsigned int D = 0;
		unsigned int E = 0;
	}analogReadings;
	
	//representa a análise das leituras com base no limiar
	typedef struct{
		bool A = false;
		bool B = false;
		bool C = false;
		bool D = false;
		bool E = false;
	}digitalReadings;
	
	//representa a análise das leituras com base no limiar
	typedef struct{
		unsigned int A = 0;
		unsigned int B = 0;
		unsigned int C = 0;
		unsigned int D = 0;
		unsigned int E = 0;
	}compensateVars;
			
	class LineSensor
	{	
		private: 
		/************************************************************************
		Variáveis de controle dos sensores de linha
		************************************************************************/
		//pinagem dos sensores no arduino
		int analogPinA = 8;
		int analogPinB = 9;
		int analogPinC = 10;
		int analogPinD = 11;
		int analogPinE = 12;
		
		//pinagem dos leds no arduino
		int ledA = 44;
		int ledB = 46;
		int ledC = 48;
		int ledD = 50;
		int ledE = 52;

		//array de sensores IR com suas leituras analógicas
		analogReadings aSensors;
		//array de sensores IR com suas leituras digitais
		digitalReadings dSensors; 		
		
		int activatedSensorsCounter = 0;

		//limiar de detecção digital
		int threshold = 450;

		//variáveis de compensação de leitores ultrasom
		int cA=0;
		int cB=0;
		int cC=0;
		int cD=0;
		int cE=0;
		
		public:
		LineSensor();
		
		~LineSensor();	
		
		
		//faz o pinmode da setup
		void attach();

		//liga os sensores a um pino de entrada analógica no arduino
		void setSensorsPins(int a, int b, int c, int d, int e);

		//liga os leds da placa aos seus respectivos pinos de saída no arduino
		void setLedsPins(int a, int b, int c, int d, int e);

		//zera as variáveis de leitura analógica dos leds
		void resetVars();

		//testa se o sensor informado está ativo
		bool isActive(char sensor);

		//retorna struct das leituras analógicas
		digitalReadings* getDigitalReadings();

		//retorna estrutura das leituras digitalizadas
		analogReadings* getAnalogReadings();

		//retorna o valor analogico de leitura de um sensor
		int getAnalogReading(char s);

		//retorna o valor digital de leitura de um sensor
		bool getDigitalReading(char s);

		//lê os sensores e publica os dados na forma digital e analógica
		void readSensors();	

		//lê o sensor informado e publica os dados na forma digital e analógica
		int readSensor(char s);	
		
		//Process é a digitalização e o acionamento dos leds com base nas leituras e limiar
		void processReadings();
		
		//Process é a digitalização e o acionamento dos leds com base nas leituras e limiar
		void processReading(char s);

		//calibra os sensores
		void calibrateSensors();

		//define o valor limiar
		void setThreshold(int threshold);	
		
		//obtém o valor de contagem dos sensores
		int getActivatedSensorsCounter();
		
		//obtém as 	variáveis de compensação
		compensateVars* getCompensateVars();

		//desliga todos os leds
		void turnLedsOff();

		//desliga um único led
		void turnLedOff(char s);

		//liga todos os leds
		void turnLedsOn();

		//liga um único led
		void turnLedOn(char s);	
		
		
		//pisca rapidamente todos os leds
		void flashLeds();
		
		//acende leds na ordem da esquerda pra direita
		void turnLedsOnInARow();
	};
//#endif