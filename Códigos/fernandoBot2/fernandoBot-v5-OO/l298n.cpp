setPins(unsigned int ENA, unsigned int IN1, unsigned int IN2, unsigned int IN3, unsigned int IN4, unsigned int ENB){
			pins.ENA=ENA;
			pins.IN1=IN1;
			pins.IN2=IN2;
			pins.IN3=IN3;
			pins.IN4=IN4;
			pins.ENB=ENB;
		}
		
		boardPins* getBoardPins(){
			return &pins;
		}






void attach(){
	pinMode(pins.ENA, OUTPUT);
	pinMode(pins.ENB, OUTPUT);
	pinMode(pins.IN1, OUTPUT);
	pinMode(pins.IN2, OUTPUT);
	pinMode(pins.IN3, OUTPUT);
	pinMode(pins.IN4, OUTPUT);
}

/***************************************************************************************
PARE
***************************************************************************************/
void pare()
{
  dMotorA(FRENTE, 0);
  dMotorB(FRENTE, 0);
  tMotorA(FRENTE, 0);
  tMotorB(FRENTE, 0);
}

/***************************************************************************************
FRENTE
***************************************************************************************/
void frente (int vel)
{
  dMotorA(FRENTE, vel);
  dMotorB(FRENTE, vel);
  tMotorA(FRENTE, vel);
  tMotorB(FRENTE, vel);
}

/***************************************************************************************
TRAS
***************************************************************************************/
void tras (int vel)
{
  dMotorA(TRAS, vel);
  dMotorB(TRAS, vel);
  tMotorA(TRAS, vel);
  tMotorB(TRAS, vel);
}

/***************************************************************************************
DIREITA
***************************************************************************************/
void direita (int vel)
{
  dMotorA(TRAS, vel);
  dMotorB(FRENTE, vel);
  tMotorA(TRAS, vel);
  tMotorB(FRENTE, vel);  
}


/***************************************************************************************
ESQUERDA
***************************************************************************************/
void esquerda (int vel)
{
  dMotorA(FRENTE, vel);
  dMotorB(TRAS, vel);
  tMotorA(FRENTE, vel);
  tMotorB(TRAS, vel);
}


/***************************************************************************************
DMOTORA
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void dMotorA(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    dMotorAFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    dMotorARe(velocidade);
  }
}

/***************************************************************************************
DMOTORAFRENTE
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void dMotorAFrente(int velocidade)
{
  digitalWrite(DENA, 0);
  digitalWrite(DIN1, 0);
  digitalWrite(DIN2, 1);
  analogWrite(DENA, velocidade);
}

/***************************************************************************************
DMOTORARE
Quando: funções de locomoção
O quê: controla motor dianteiro A
***************************************************************************************/
void dMotorARe(int velocidade)
{
  digitalWrite(DENA, 1);
  digitalWrite(DIN1, 1);
  digitalWrite(DIN2, 0);
  analogWrite(DENA, velocidade);
}

/***************************************************************************************
DMOTORB
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void dMotorB(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    dMotorBFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    dMotorBRe(velocidade);
  }
}

/***************************************************************************************
MOTORBFRENTE
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void dMotorBFrente(int velocidade)
{
  digitalWrite(DENB, 0);
  digitalWrite(DIN3, 0);
  digitalWrite(DIN4, 1);
  analogWrite(DENB, velocidade);
}

/***************************************************************************************
DMOTORBRE
Quando: funções de locomoção
O quê: controla motor dianteiro B
***************************************************************************************/
void dMotorBRe(int velocidade)
{
  digitalWrite(DENB, 1);
  digitalWrite(DIN3, 1);
  digitalWrite(DIN4, 0);
  analogWrite(DENB, velocidade);
}

/*****************************************************************************************************************************************

/***************************************************************************************
TMOTORA
Quando: funções de locomoção
O quê: controla motor traseiro A
***************************************************************************************/
void tMotorA(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    tMotorAFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    tMotorARe(velocidade);
  }
}

/***************************************************************************************
TMOTORAFRENTE
Quando: funções de locomoção
O quê: controla motor traseiro A
***************************************************************************************/
void tMotorAFrente(int velocidade)
{
  digitalWrite(TENA, 0);
  digitalWrite(TIN1, 0);
  digitalWrite(TIN2, 1);
  analogWrite(TENA, velocidade);
}

/***************************************************************************************
DMOTORARE
Quando: funções de locomoção
O quê: controla motor traseiro A
***************************************************************************************/
void tMotorARe(int velocidade)
{
  digitalWrite(TENA, 1);
  digitalWrite(TIN1, 1);
  digitalWrite(TIN2, 0);
  analogWrite(TENA, velocidade);
}

/***************************************************************************************
TMOTORB
Quando: funções de locomoção
O quê: controla motor traseiro B
***************************************************************************************/
void tMotorB(boolean sentido, int velocidade)
{
  if (sentido == FRENTE)
  {
    tMotorBFrente(velocidade);
  }
  else if (sentido == TRAS)
  {
    tMotorBRe(velocidade);
  }
}

/***************************************************************************************
TMOTORBFRENTE
Quando: funções de locomoção
O quê: controla motor traseiro B
***************************************************************************************/
void tMotorBFrente(int velocidade)
{
  digitalWrite(TENB, 0);
  digitalWrite(TIN3, 0);
  digitalWrite(TIN4, 1);
  analogWrite(TENB, velocidade);
}

/***************************************************************************************
TMOTORBRE
Quando: funções de locomoção
O quê: controla motor traseiro B
***************************************************************************************/
void tMotorBRe(int velocidade)
{
  digitalWrite(TENB, 1);
  digitalWrite(TIN3, 1);
  digitalWrite(TIN4, 0);
  analogWrite(TENB, velocidade);
}
