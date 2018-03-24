#ifndef lineSensor_h
	#lineSensor_h

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
	
	//representa a analise das leituras com base no limiar
	typedef struct{
		bool A = false;
		bool B = false;
		bool C = false;
		bool D = false;
		bool E = false;
	}digitalReadings;
	
	//representa a analise das leituras com base no limiar
	typedef struct{
		unsigned int A = 0;
		unsigned int B = 0;
		unsigned int C = 0;
		unsigned int D = 0;
		unsigned int E = 0;
	}compensateVars;
			
			
	/***************************************************************************************
	----------------------------- class LineSensor -----------------------------------------
	@Author: Fernando Viel
	@Date: 01/06/2015
		
	Atenção para seu ciclo de funcionamento:
	1. Leia o sensor (ex.: readSensors() );
	2. Processe a leitura para saber quais sensores estão ativos (exe.: processReadings() );
	3. Retorne os valores lidos (exe.: getReadings() );
	***************************************************************************************/
	class LineSensor
	{	
		private: 

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

		//array de sensores IR com suas leituras analogicas
		analogReadings aSensors;
		
		//array de sensores IR com suas leituras digitais
		digitalReadings dSensors; 

		//struct das compensadoras dos sensores
		compensateVars compensate;
		
		int activatedSensorsCounter = 0;

		//limiar de deteccao digital
		int threshold = 500;
		
		public:
		LineSensor();
		
		~LineSensor();	
		
//A--
		
		//OK faz o pinmode da setup
		void attach();
		
//C--
		
		//OK calibra os sensores
		void calibrateSensors();
		
//F--
		
		//FALTA SUAS SUBFUNCOES - pisca rapidamente todos os leds
		void flashLeds(unsigned int qtd, unsigned int time);
		
//G--
		
		//OK obtem o valor de contagem dos sensores
		int getActivatedSensorsCounter();
		
		//ok obtem as 	variaveis de compensaÃ§Ã£o
		compensateVars* getCompensateVars();
		
		//ok retorna uma variavel de compensacao
		int getCompensateVar(char s);
		
		//ok retorna struct das leituras analogicas
		digitalReadings* getDigitalReadings();

		//ok retorna estrutura das leituras digitalizadas
		analogReadings* getAnalogReadings();

		//ok retorna o valor analogico de leitura de um sensor
		int getAnalogReading(char s);

		//ok retorna o valor digital de leitura de um sensor
		bool getDigitalReading(char s);	
		
//P--

		//digitalizacao e o acionamento dos leds com base nas leituras e limiar
		void processReadings();
		
		//digitalizacao e o acionamento dos leds com base nas leituras e limiar
		void processReading(char s);

//R--
		//le os sensores e publica os dados na forma digital e analÃ³gica
		void readSensors();	

		//le o sensor informado e publica os dados na forma digital e analÃ³gica
		int readSensor(char s);	
		
		//zera as variaveis de leitura analÃ³gica dos leds
		void resetVars();
		
//S--

		//define o valor limiar
		void setThreshold(int newThreshold);	
		
		//liga os sensores a um pino de entrada analÃ³gica no arduino
		void setSensorsPins(int a, int b, int c, int d, int e);

		//liga os leds da placa aos seus respectivos pinos de saÃ­da no arduino
		void setLedsPins(int a, int b, int c, int d, int e);
				
//T--
		
		//desliga todos os leds
		void turnLedsOff();

		//desliga um unico led
		void turnLedOff(char s);

		//liga todos os leds
		void turnLedsOn();

		//liga um unico led
		void turnLedOn(char s);			
		
		//acende leds na ordem da esquerda pra direita
		void turnLedsOnInARow(unsigned int qtd, unsigned int time);
		
	};

#endif