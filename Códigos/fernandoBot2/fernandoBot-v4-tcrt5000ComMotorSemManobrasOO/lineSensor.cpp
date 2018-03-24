#include "lineSensor.h"

LineSensor::LineSensor(){
	//1. Define pinagem
	//attach();
	
	//2. Desliga os leds por precaução
	//turnLedsOff();

	//3. Zera as variáveis
	//resetVars();

	//4. Considerando que o robô foi ligado sobre uma superfície branca, realiza a calibragem
	//calibrateSensors(); //PROBLEMA AQUI...NÃO PODE RODAR ANTES DA SETUP() NO ARDUINO!
}

LineSensor::~LineSensor(){
	//1. Desliga os leds por precaução
	turnLedsOff();

	//2. Zera as variáveis
	resetVars();
}

//liga sensores e leds aos seus respectivos pinos
void LineSensor::attach(){
	//Define a pinagem
	pinMode(ledA, OUTPUT);
	pinMode(ledB, OUTPUT);
	pinMode(ledC, OUTPUT);
	pinMode(ledD, OUTPUT);
	pinMode(ledE, OUTPUT);
	pinMode(analogPinA, INPUT);
	pinMode(analogPinB, INPUT);
	pinMode(analogPinC, INPUT);
	pinMode(analogPinD, INPUT);
	pinMode(analogPinE, INPUT);	
}

//liga os sensores da placa aos seus respectivos pinos de saída no arduino
void LineSensor::setSensorsPins(int a, int b, int c, int d, int e){
	analogPinA = a;
	analogPinB = b;
	analogPinC = c;
	analogPinD = d;
	analogPinE = e;
}

//liga os leds da placa aos seus respectivos pinos de saída no arduino
void LineSensor::setLedsPins(int a, int b, int c, int d, int e){
	ledA = a;
	ledB = b;
	ledC = c;
	ledD = d;
	ledE = e;
}

//define o valor limiar
void LineSensor::setThreshold(int threshold){
	this->threshold  = threshold ;
}

//zera as variáveis de leitura analógica dos leds
void LineSensor::resetVars(){
	aSensors.A = 0;
	aSensors.B = 0;
	aSensors.C = 0;
	aSensors.D = 0;
	aSensors.E = 0;
	
	dSensors.A = false;
	dSensors.B = false;
	dSensors.C = false;
	dSensors.D = false;
	dSensors.E = false;
}

//testa se o sensor informado está ativo
bool LineSensor::isActive(char sensor){
	
	//IMPLEMENTAR
	
}

//retorna struct das leituras analógicas
digitalReadings * LineSensor::getDigitalReadings(){
	readSensors();
	return &dSensors;	
}

//retorna estrutura das leituras digitalizadas
analogReadings * LineSensor::getAnalogReadings(){
	readSensors();
	return &aSensors;
}

//retorna as variáveis de compensação de leituras do sensor de linha
compensateVars* getCompensateVars(){
	return &compensateVars;
}

int getCompensateVar(char s){
	switch (s)
	{
		case 'A':
	    {
	      return compensateVars.A;
	    } break;
		case 'B':
		{
	      return compensateVars.B;
	    } break;
	    case 'C':
	    {
	      return compensateVars.C;
	    } break;
	    case 'D':
	    {
	      return compensateVars.D;
	    } break;
	    case 'E':
	    {
	      return compensateVars.E;
	    } break;
	    case DEFAULT:
	    {
	      return -1;
	    } break;
	}
}

//retorna o valor analogico de leitura de um sensor
/*
PREMISSAS
1. VALORES FORAM LIDOS
2. VALORES FORAM PROCESSADOS
3. VALORES ESTÃO PRONTOS PARA SEREM ENTREGUES.
*/
int LineSensor::getAnalogReading(char s){
	switch (s)
	{
		case 'A':
	    {
	      return analogReadings.A;
	    } break;
		case 'B':
		{
	      return analogReadings.B;
	    } break;
	    case 'C':
	    {
	      return analogReadings.C;
	    } break;
	    case 'D':
	    {
	      return analogReadings.D;
	    } break;
	    case 'E':
	    {
	      return analogReadings.E;
	    } break;
	    case default:
	    {
	      return -1;
	    } break;
	}
}

//retorna o valor digital de leitura de um sensor
/*
PREMISSAS
1. VALORES FORAM LIDOS
2. VALORES FORAM PROCESSADOS
3. VALORES ESTÃO PRONTOS PARA SEREM ENTREGUES.
*/
bool LineSensor::getDigitalReading(char s){
	if(getAnalogReading(s)>threshold)	{
		return true;
	}
	else{
		return false;
	}

}

//retorna a leitura tratada de um único sensor
/*TODO: FAZER UMA FUNÇÃO DE ANÁLISE DA LEITURA QUE SEJA SEPARADA! UMA COISA É LER, 
OUTRA COISA É TRATAR A LEITURA E POR FIM PROCESSÁ-LA. SÃO FINALIDADES DISTINTAS
 E DEIXEI TUDO JUNTO NO MESMO MÉTODO...
 READ
 PROCESS
 GET
 */
int LineSensor::readSensor(char s){
	switch (s)
	{
		case 'A':
	    {
			aSensors.A = analogRead(analogPinA);
			//faz a compensação de calibragem
			if (compensateVars.A > aSensors.A < 0)
			{
				compensateVars.A = compensateVars.A - aSensors.A;
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
			if (compensateVars.B > aSensors.B < 0)
			{
				//precisa compensar
				compensateVars.B = compensateVars.B - aSensors.B;
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
			if (compensateVars.C > aSensors.C < 0)
			{
				compensateVars.C = compensateVars.C - aSensors.C;
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
			if (compensateVars.D > aSensors.D < 0)
			{
				compensateVars.D = compensateVars.D - aSensors.D;
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
			if (compensateVars.E > aSensors.E < 0)
			{
				compensateVars.E = compensateVars.E - aSensors.E;
				aSensors.E = 0;		
			} 
			else
			{
				aSensors.E = 0;	
			}			
			return aSensors.E;
	    } break;
	    case default:
	    {
			return -1;
	    } break;
	}
	return -1;
}
		
//lê os sensores e publica os dados na forma digital e analógica
/*
  OPTEI POR NÃO FAZER UMA SÉRIE DE LEITURAS INDIVIDUAIS, POIS CONSIDERANDO A VELOCIDADE DE PROCESSAMENTO DO ROBÔ, 
  AS COISAS PODEM TER MUDADO ENTRE A LEITURA DE A E B, LOGO EU TERIA LEITURA DE MOMENTOS DIFERENTES E ISTO É 
  CONTRÁRIO À LÓGICA DELE. POSSO ATÉ TER LEITURAS ATRASADAS, MAS DO MESMO MOMENTO.
*/
void LineSensor::readSensors(){
	
	//BUG - POR ALGUM MOTIVO ESTOU PEGANDO LEITURAS NEGATIVAS E AINDA POR CIMA ISTO ACENDE O LED!!!
	//PORRA, SE FIZ AS VARS UNSIGNED INT, COMO QUE PODEM ESTAR NEGATIVAS??????:
	
	
	//zera o contador
    activatedSensorsCounter = 0;
    //zera as leituras de sensores 
    resetVars();	
	
	//1. Lê os sensores já com a compensação obtida na calibragem
	aSensors.A = analogRead(analogPinA);
	aSensors.B = analogRead(analogPinB);
	aSensors.C = analogRead(analogPinC);
	aSensors.D = analogRead(analogPinD);
	aSensors.E = analogRead(analogPinE);
	
	//2. Ajusta valores de calibração e as aplica
	if (compensateVars.A > aSensors.A < 0)
	{
		//precisa compensar
		compensateVars.A = compensateVars.A - aSensors.A;
		aSensors.A = 0;		
	} 
	else
	{
		aSensors.A = 0;	
	}
	
	if (compensateVars.B > aSensors.B < 0)
	{
		//precisa compensar
		compensateVars.B = compensateVars.B - aSensors.B;
		aSensors.B = 0;		
	} 
	else
	{
		aSensors.B = 0;	
	}
	
	if (compensateVars.C > aSensors.C < 0)
	{
		//precisa compensar
		compensateVars.C = compensateVars.C - aSensors.C;
		aSensors.C = 0;		
	} 
	else
	{
		aSensors.C = 0;	
	}
	
	if (compensateVars.D > aSensors.D < 0)
	{
		//precisa compensar
		compensateVars.D = compensateVars.D - aSensors.D;
		aSensors.D = 0;		
	} 
	else
	{
		aSensors.D = 0;	
	}
	
	if (compensateVars.E > aSensors.E < 0)
	{
		//precisa compensar
		compensateVars.E = compensateVars.E - aSensors.E;
		aSensors.E = 0;		
	} 
	else
	{
		aSensors.E = 0;	
	}	
}

/*
Process é a digitalização e o acionamento dos leds com base
nas leituras e limiar
*/
void LineSensor::processReadings(){
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
}

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
	}
	return;
}

//calibra os sensores
void LineSensor::calibrateSensors(){
	cA  = analogRead(analogPinA);
	cB  = analogRead(analogPinB);
	cC  = analogRead(analogPinC);
	cD  = analogRead(analogPinD);
	cE  = analogRead(analogPinE); 

	for(int i = 0; i < 5; i++)
	{
		turnLedsOn();
		delay(40);
		turnLedsOff();
		delay(40);
	}  
}

//desliga todos os leds
void LineSensor::turnLedsOff(){
	digitalWrite(ledA, LOW);
	digitalWrite(ledB, LOW);
	digitalWrite(ledC, LOW);
	digitalWrite(ledD, LOW);
	digitalWrite(ledE, LOW);
}

//desliga um único led
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

	}

}

//liga todos os leds
void LineSensor::turnLedsOn(){
	digitalWrite(ledA, HIGH);
	digitalWrite(ledB, HIGH);
	digitalWrite(ledC, HIGH);
	digitalWrite(ledD, HIGH);
	digitalWrite(ledE, HIGH);
}

//liga um único led
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
	}
}

//obtém o valor de contagem dos sensores
int LineSensor::getActivatedSensorsCounter(){
	return activatedSensorsCounter;
}

//pisca rapidamente todos os leds
void LineSensor::flashLeds(){
	for (unsigned int i = 0; i<4;i++){
		turnLedsOn();
		delay(50);    //HUUUUUM, DEPOIS TROCAR DELAYS POR MILLIS()
		turnLedsOff();
		delay(50);
	}
}
		
//acende leds na ordem da esquerda pra direita
void LineSensor::turnLedsOnInARow(){
	
	for(unsigned int i = 0; i <4;i++){
		
		//A
		digitalWrite(ledA, HIGH);
		delay(30);
		digitalWrite(ledA, LOW);
		//B
		digitalWrite(ledB, HIGH);
		delay(30);
		digitalWrite(ledB, LOW);
		//C
		digitalWrite(ledC, HIGH);
		delay(30);
		digitalWrite(ledC, LOW);
		//D
		digitalWrite(ledD, HIGH);
		delay(30);
		digitalWrite(ledD, LOW);
		//E
		digitalWrite(ledE, HIGH);
		delay(30);
		digitalWrite(ledE, LOW);
		
		
		
		//E
		digitalWrite(ledE, HIGH);
		delay(30);
		digitalWrite(ledE, LOW);
		//D
		digitalWrite(ledD, HIGH);
		delay(30);
		digitalWrite(ledD, LOW);
		//C
		digitalWrite(ledC, HIGH);
		delay(30);
		digitalWrite(ledC, LOW);
		//B
		digitalWrite(ledB, HIGH);
		delay(30);
		digitalWrite(ledB, LOW);
		//A
		digitalWrite(ledA, HIGH);
		delay(30);
		digitalWrite(ledA, LOW);
	}
}