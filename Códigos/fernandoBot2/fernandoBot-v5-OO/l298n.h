#ifndef l298n_h
	#define l298n_h
	
	#include <Arduino.h>
	#include <inttypes.h>
	
	//Variáveis de controle dos motores e ponte H 298
#define FRENTE 1
#define TRAS 0

	//representa os pinos da placa
	typedef struct{
		unsigned int ENA = 12 //(output pwm)
		unsigned int IN1 = 41
		unsigned int IN2 = 43
		unsigned int IN3 = 45
		unsigned int IN4 = 47
		unsigned int ENB = 11 //(output pwm)
	}boardPins;
		
	class l298n{
		
		private:
		
		//representa os pinos de uma controladora l298n
		boardPins pins;
		
		unsigned int speed;
		
		
		public:
		
		l298n();
		
		~l298n();
		
		setPins(unsigned int ENA, unsigned int IN1, unsigned int IN2, unsigned int IN3, unsigned int IN4, unsigned int ENB);		
		boardPins* getBoardPins();		
		void attach();		
		void pare();
		void frente (int vel);
		void tras (int vel);
		void direita (int vel);
		void esquerda (int vel);
		void dMotorA(boolean sentido, int velocidade);
		void dMotorAFrente(int velocidade);
		void dMotorARe(int velocidade);
		void dMotorB(boolean sentido, int velocidade);
		void dMotorBFrente(int velocidade);
		void dMotorBRe(int velocidade);
		void tMotorA(boolean sentido, int velocidade);
		void tMotorAFrente(int velocidade);
		void tMotorARe(int velocidade);
		void tMotorB(boolean sentido, int velocidade);
		void tMotorBFrente(int velocidade);
		void tMotorBRe(int velocidade);
	};	
#endif