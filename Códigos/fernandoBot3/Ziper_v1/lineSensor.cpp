#include "lineSensor.h"

/***************************************************************************************
LineSensor()
***************************************************************************************/
LineSensor::LineSensor(){
	//1. Define pinagem
	//attach();
	
	//2. Desliga os leds por precaução
	////turnLedsOff();

	//3. Zera as variáveis
	//resetVars();

	//4. Considerando que o robô foi ligado sobre uma superfície branca, realiza a calibragem
	//calibrateSensors(); //PROBLEMA AQUI...NÃO PODE RODAR ANTES DA SETUP() NO ARDUINO!
}

/***************************************************************************************
~LineSensor()
***************************************************************************************/
LineSensor::~LineSensor(){
	//1. Desliga os leds por precaução
	////turnLedsOff();

	//2. Zera as variáveis
	//resetVars();
}

/***************************************************************************************
attach()
Liga sensores e leds aos seus respectivos pinos no arduino
***************************************************************************************/
void LineSensor::attach(){
	pinMode(ledA, OUTPUT);
	pinMode(ledB, OUTPUT);
	pinMode(ledC, OUTPUT);
	pinMode(ledD, OUTPUT);
	pinMode(ledE, OUTPUT);
	pinMode(ledF, OUTPUT);
	pinMode(ledG, OUTPUT);
	pinMode(analogPinA, INPUT);
	pinMode(analogPinB, INPUT);
	pinMode(analogPinC, INPUT);
	pinMode(analogPinD, INPUT);
	pinMode(analogPinE, INPUT);
	pinMode(analogPinF, INPUT);
	pinMode(analogPinG, INPUT);	
}


/***************************************************************************************
calibrateSensors()
Obtém os valores a serem utilizados nas calibragens dos sensores
***************************************************************************************/
void LineSensor::calibrateSensors(){
	compensate.A  = analogRead(analogPinA);
	compensate.B  = analogRead(analogPinB);
	compensate.C  = analogRead(analogPinC);
	compensate.D  = analogRead(analogPinD);
	compensate.E  = analogRead(analogPinE); 
	compensate.F  = analogRead(analogPinF);
	compensate.G  = analogRead(analogPinG); 

	flashLeds(4, 50);
}


/***************************************************************************************
flashLeds(int qtd)
Pisca rapidamente todos os leds da placa na quantidade informada
***************************************************************************************/
void LineSensor::flashLeds(unsigned int qtd, unsigned int time){
	for (unsigned int i = 0; i<qtd;i++){
		turnLedsOn();
		delay(time);    
		turnLedsOff();
		delay(time);
	}
}


/***************************************************************************************
getActivatedSensorsCounter()
Retorna a contagem de sensores ativos.
Sempre utilizar um readSensors() antes, senão lerá 0.
***************************************************************************************/
int LineSensor::getActivatedSensorsCounter(){
	return activatedSensorsCounter;
}


/***************************************************************************************
getDigitalReading(char s)
Retorna a leitura do sensor informado em s [A,B,C,D,E]
***************************************************************************************/
bool LineSensor::getDigitalReading(char s){
	if(getAnalogReading(s)>threshold)	{
		return true;
	}
	else{
		return false;
	}
}


/***************************************************************************************
getDigitalReadings()
Retorna struct das leituras digitais
Sempre utilizar um readSensors() com a processReadings() antes, senão lerá 0.
***************************************************************************************/
digitalReadings * LineSensor::getDigitalReadings(){
	return &dSensors;	
}

/***************************************************************************************
getDigitalReadings()
Retorna struct das leituras analogicas
Sempre utilizar um readSensors() antes, senão lerá 0.
***************************************************************************************/
analogReadings * LineSensor::getAnalogReadings(){	
	return &aSensors;
}


/***************************************************************************************
getCompensateVars()
Retorna as variaveis de compensação de leituras do sensor de linha
***************************************************************************************/
compensateVars* LineSensor::getCompensateVars(){
	return &compensate;
}


/***************************************************************************************
getCompensateVar(char s)
Retorna uma variavel de compensação de leituras do sensor de linha
***************************************************************************************/
int LineSensor::getCompensateVar(char s){
	switch (s)
	{
		case 'A':
	    {
	      return compensate.A;
	    } break;
	    case 'B':
	    {
	      return compensate.B;
	    } break;
	    case 'C':
	    {
	      return compensate.C;
	    } break;
	    case 'D':
	    {
	      return compensate.D;
	    } break;
	    case 'E':
	    {
	      return compensate.E;
	    } break;
            case 'F':
	    {
	      return compensate.F;
	    } break;
	    case 'G':
	    {
	      return compensate.G;
	    } break;
	    default:
	    {
	      return -1;
	    } break;
	}
}


/***************************************************************************************
getAnalogReading(char s)
Retorna o valor analogico de leitura de um sensor
***************************************************************************************/
int LineSensor::getAnalogReading(char s){
	switch (s)
	{
		case 'A':
	    {
	      return aSensors.A;
	    } break;
		case 'B':
		{
	      return aSensors.B;
	    } break;
	    case 'C':
	    {
	      return aSensors.C;
	    } break;
	    case 'D':
	    {
	      return aSensors.D;
	    } break;
	    case 'E':
	    {
	      return aSensors.E;
	    } break;
            case 'F':
	    {
	      return aSensors.F;
	    } break;
	    case 'G':
	    {
	      return aSensors.G;
	    } break;
	    default:
	    {
	      return -1;
	    } break;
	}
} 


/***************************************************************************************
processReadings()
Digitaliza as leituras analogicas, atualizando as bool privadas
***************************************************************************************/
void LineSensor::processReadings(){
	//zera o contador
    activatedSensorsCounter = 0;
	
	// Digitaliza leitura
	if (aSensors.A < threshold)
	{
		dSensors.A = false;
		turnLedOff('A');
	} else
	{
		dSensors.A = true;
		activatedSensorsCounter++;
		turnLedOn('A');
	}

	if (aSensors.B < threshold)
	{
		dSensors.B = false;
                turnLedOff('B');
	} else
	{
		dSensors.B = true;
		activatedSensorsCounter++;
		turnLedOn('B');
	}
	
	if (aSensors.C < threshold)
	{
		dSensors.C = false;
                turnLedOff('C');
	} else
	{
		dSensors.C = true;
		activatedSensorsCounter++;
		turnLedOn('C');
	}
	
	if (aSensors.D < threshold)
	{
		dSensors.D = false;
                turnLedOff('D');
	} else
	{
		dSensors.D = true;
		activatedSensorsCounter++;
		turnLedOn('D');
	}
	
	if (aSensors.E < threshold)
	{
		dSensors.E = false;
                turnLedOff('E');
	} else
	{
		dSensors.E = true;
		activatedSensorsCounter++;
		turnLedOn('E');
	}
        
        if (aSensors.F < threshold)
	{
		dSensors.F = false;
		turnLedOff('F');
	} else
	{
		dSensors.F = true;
		activatedSensorsCounter++;
		turnLedOn('F');
	}
	
	if (aSensors.G < threshold)
	{
		dSensors.G = false;
		turnLedOff('G');
	} else
	{
		dSensors.G = true;
		activatedSensorsCounter++;
		turnLedOn('G');
	}
}


/***************************************************************************************
processReading(char s)
Digitaliza a leituras analogica de um sensor, atualizando a bool privada
***************************************************************************************/
void LineSensor::processReading(char s){
	switch (s)
	{
		case 'A':
	    {
			if (aSensors.A < threshold)
			{
				dSensors.A = false;
				turnLedOff('A');
			} else
			{
				dSensors.A = true;
				turnLedOn('A');
			}
	    } break;
		case 'B':
		{
			if (aSensors.B < threshold)
			{
				dSensors.B = false;
				turnLedOff('B');
			} else
			{
				dSensors.B = true;
				turnLedOn('B');
			}
	    } break;
	    case 'C':
	    {
			if (aSensors.C < threshold)
			{
				dSensors.C = false;
				turnLedOff('C');
			} else
			{
				dSensors.C = true;
				turnLedOn('C');
			}
	    } break;
	    case 'D':
	    {
			if (aSensors.D < threshold)
			{
				dSensors.D = false;
				turnLedOff('D');
			} else
			{
				dSensors.D = true;
				turnLedOn('D');
			}
	    } break;
	    case 'E':
	    {
			if (aSensors.E < threshold)
			{
				dSensors.E = false;
				turnLedOff('E');
			} else
			{
				dSensors.E = true;
				turnLedOn('E');
			}
	    } break;
            case 'F':
	    {
			if (aSensors.F < threshold)
			{
				dSensors.F = false;
				turnLedOff('F');
			} else
			{
				dSensors.F = true;
				turnLedOn('F');
			}
	    } break;
            case 'G':
	    {
			if (aSensors.G < threshold)
			{
				dSensors.G = false;
				turnLedOff('G');
			} else
			{
				dSensors.G = true;
				turnLedOn('G');
			}
	    } break;
	}
	return;
}


/***************************************************************************************
readSensor(char s)
Lê o sensor informado
***************************************************************************************/
int LineSensor::readSensor(char s){
	switch (s)
	{
		case 'A':
	    {
			aSensors.A = analogRead(analogPinA);
			//faz a compensação de calibragem
			if (compensate.A > aSensors.A < 0)
			{
				compensate.A = aSensors.A;
				aSensors.A = 0;		
			} 
			else
			{
				aSensors.A = 0;	
			}			
			return aSensors.A;
	    } break;
		case 'B':
		{
			aSensors.B = analogRead(analogPinB);
			if (compensate.B > aSensors.B < 0)
			{
				//precisa compensar
				compensate.B = aSensors.B;
				aSensors.B = 0;		
			} 
			else
			{
				aSensors.B = 0;	
			}
			aSensors.B;
	    } break;
	    case 'C':
	    {
			aSensors.C = analogRead(analogPinC);
			//faz a compensação de calibragem
			if (compensate.C > aSensors.C < 0)
			{
				compensate.C = aSensors.C;
				aSensors.C = 0;		
			} 
			else
			{
				aSensors.C = 0;	
			}			
			return aSensors.C;
	    } break;
	    case 'D':
	    {
			aSensors.D = analogRead(analogPinD);
			//faz a compensação de calibragem
			if (compensate.D > aSensors.D < 0)
			{
				compensate.D = aSensors.D;
				aSensors.D = 0;		
			} 
			else
			{
				aSensors.D = 0;	
			}			
			return aSensors.D;
	    } break;
	    case 'E':
	    {
			aSensors.E = analogRead(analogPinE);
			//faz a compensação de calibragem
			if (compensate.E > aSensors.E < 0)
			{
				compensate.E = aSensors.E;
				aSensors.E = 0;		
			} 
			else
			{
				aSensors.E = 0;	
			}			
			return aSensors.E;
	    } break;
            case 'F':
	    {
			aSensors.F = analogRead(analogPinF);
			//faz a compensação de calibragem
			if (compensate.F > aSensors.F < 0)
			{
				compensate.F = aSensors.F;
				aSensors.F = 0;		
			} 
			else
			{
				aSensors.F = 0;	
			}			
			return aSensors.F;
	    } break;
            case 'G':
	    {
			aSensors.G = analogRead(analogPinG);
			//faz a compensação de calibragem
			if (compensate.G > aSensors.G < 0)
			{
				compensate.G = aSensors.G;
				aSensors.G = 0;		
			} 
			else
			{
				aSensors.G = 0;	
			}			
			return aSensors.G;
	    } break;
	    default:
	    {
			return -1;
	    } break;
	}
	return -1;
}
		
		
/***************************************************************************************
readSensors()
Lê todos os sensores.
***************************************************************************************/
void LineSensor::readSensors(){	
	
    //zera as leituras de sensores 
    resetVars();	
	
	//1. Lê os sensores já com a compensação obtida na calibragem
	aSensors.A = analogRead(analogPinA);
	aSensors.B = analogRead(analogPinB);
	aSensors.C = analogRead(analogPinC);
	aSensors.D = analogRead(analogPinD);
	aSensors.E = analogRead(analogPinE);
	aSensors.F = analogRead(analogPinF);
	aSensors.G = analogRead(analogPinG);
	
	//2. Ajusta valores de calibração e as aplica
	/*if (compensate.A > aSensors.A < 0)
	{
		//precisa compensar
		compensate.A = aSensors.A;
		aSensors.A = 0;		
	} 
	else
	{
		aSensors.A = 0;	
	}
	
	if (compensate.B > aSensors.B < 0)
	{
		//precisa compensar
		compensate.B = aSensors.B;
		aSensors.B = 0;		
	} 
	else
	{
		aSensors.B = 0;	
	}
	
	if (compensate.C > aSensors.C < 0)
	{
		//precisa compensar
		compensate.C = aSensors.C;
		aSensors.C = 0;		
	} 
	else
	{
		aSensors.C = 0;	
	}
	
	if (compensate.D > aSensors.D < 0)
	{
		//precisa compensar
		compensate.D = aSensors.D;
		aSensors.D = 0;		
	} 
	else
	{
		aSensors.D = 0;	
	}
	
	if (compensate.E > aSensors.E < 0)
	{
		//precisa compensar
		compensate.E = aSensors.E;
		aSensors.E = 0;		
	} 
	else
	{
		aSensors.E = 0;	
	}*/	
}


/***************************************************************************************
setSensorsPins(int a, int b, int c, int d, int e)
Define a pinagem dos sensores na placa arduino
***************************************************************************************/
void LineSensor::setSensorsPins(int a, int b, int c, int d, int e, int f, int g){
	analogPinA = a;
	analogPinB = b;
	analogPinC = c;
	analogPinD = d;
	analogPinE = e;
        analogPinF = f;
	analogPinG = g;
}


/***************************************************************************************
setLedsPins(int a, int b, int c, int d, int e)
Define a pinagem dos leds na placa arduino
***************************************************************************************/
void LineSensor::setLedsPins(int a, int b, int c, int d, int e, int f, int g){
	ledA = a;
	ledB = b;
	ledC = c;
	ledD = d;
	ledE = e;
        ledF = f;
	ledG = g;
}


/***************************************************************************************
setThreshold(int newThreshold)
Define o valor limiar para considerar um sensor ativo ou não
***************************************************************************************/
void LineSensor::setThreshold(int newThreshold){
	threshold  = newThreshold ;
}


/***************************************************************************************
resetVars()
Reinicia as variaveis de valores lidos
***************************************************************************************/
void LineSensor::resetVars(){
	aSensors.A = 0;
	aSensors.B = 0;
	aSensors.C = 0;
	aSensors.D = 0;
	aSensors.E = 0;
        aSensors.F = 0;
        aSensors.G = 0;
	
	dSensors.A = false;
	dSensors.B = false;
	dSensors.C = false;
	dSensors.D = false;
	dSensors.E = false;
        dSensors.F = false;
	dSensors.G = false;
}


/***************************************************************************************
turnLedsOnInARow()
Acende leds na ordem da esquerda pra direita
***************************************************************************************/
void LineSensor::turnLedsOnInARow(unsigned int qtd, unsigned int time){
	
	for(unsigned int i = 0; i < qtd; i++){
		
		//A
		digitalWrite(ledA, HIGH);
		delay(time);
		digitalWrite(ledA, LOW);
		//B
		digitalWrite(ledB, HIGH);
		delay(time);
		digitalWrite(ledB, LOW);
		//C
		digitalWrite(ledC, HIGH);
		delay(time);
		digitalWrite(ledC, LOW);
		//D
		digitalWrite(ledD, HIGH);
		delay(time);
		digitalWrite(ledD, LOW);
		//E
		digitalWrite(ledE, HIGH);
		delay(time);
		digitalWrite(ledE, LOW);
                //F
		digitalWrite(ledF, HIGH);
		delay(time);
		digitalWrite(ledF, LOW);
                //G
		digitalWrite(ledG, HIGH);
		delay(time);
		digitalWrite(ledG, LOW);
		
		
		//G
		digitalWrite(ledG, HIGH);
		delay(time);
		digitalWrite(ledG, LOW);
		//F
		digitalWrite(ledF, HIGH);
		delay(time);
		digitalWrite(ledF, LOW);
		//E
		digitalWrite(ledE, HIGH);
		delay(time);
		digitalWrite(ledE, LOW);
		//D
		digitalWrite(ledD, HIGH);
		delay(time);
		digitalWrite(ledD, LOW);
		//C
		digitalWrite(ledC, HIGH);
		delay(time);
		digitalWrite(ledC, LOW);
		//B
		digitalWrite(ledB, HIGH);
		delay(time);
		digitalWrite(ledB, LOW);
		//A
		digitalWrite(ledA, HIGH);
		delay(time);
		digitalWrite(ledA, LOW);
	}
}


/***************************************************************************************
turnLedsOff()
Desliga todos os leds
***************************************************************************************/
void LineSensor::turnLedsOff(){
	digitalWrite(ledA, LOW);
	digitalWrite(ledB, LOW);
	digitalWrite(ledC, LOW);
	digitalWrite(ledD, LOW);
	digitalWrite(ledE, LOW);
	digitalWrite(ledF, LOW);
	digitalWrite(ledG, LOW);
}


/***************************************************************************************
turnLedOff(char s)
Desliga um único led
***************************************************************************************/
void LineSensor::turnLedOff(char s){
	switch (s)
	{
		case 'A':
	    {
	      digitalWrite(ledA, LOW);
	    } break;
		case 'B':
		{
	      digitalWrite(ledB, LOW);
	    } break;
	    case 'C':
	    {
	      digitalWrite(ledC, LOW);
	    } break;
	    case 'D':
	    {
	      digitalWrite(ledD, LOW);
	    } break;
	    case 'E':
	    {
	      digitalWrite(ledE, LOW);
	    } break;
	    case 'F':
	    {
	      digitalWrite(ledF, LOW);
	    } break;
	    case 'G':
	    {
	      digitalWrite(ledG, LOW);
	    } break;
	}
}


/***************************************************************************************
turnLedsOn()
Liga todos os leds
***************************************************************************************/
void LineSensor::turnLedsOn(){
	digitalWrite(ledA, HIGH);
	digitalWrite(ledB, HIGH);
	digitalWrite(ledC, HIGH);
	digitalWrite(ledD, HIGH);
	digitalWrite(ledE, HIGH);
	digitalWrite(ledF, HIGH);
	digitalWrite(ledG, HIGH);
}


/***************************************************************************************
turnLedOn(char s)
Liga um único led
***************************************************************************************/
void LineSensor::turnLedOn(char s){
	switch (s)
	{
	    case 'A':
	    {
	      digitalWrite(ledA, HIGH);
	    } break;
	    case 'B':
	    {
	      digitalWrite(ledB, HIGH);
	    } break;
	    case 'C':
	    {
	      digitalWrite(ledC, HIGH);
	    } break;
	    case 'D':
	    {
	      digitalWrite(ledD, HIGH);
	    } break;
	    case 'E':
	    {
	      digitalWrite(ledE, HIGH);
	    } break;
	    case 'F':
	    {
	      digitalWrite(ledF, HIGH);
	    } break;
	    case 'G':
	    {
	      digitalWrite(ledG, HIGH);
	    } break;
	}
}
