class Led{
private:

  int pin;
  boolean state;

public:
  Led(unsigned int pin)
  {
    state = 0;
    pin = this->pin;    
  }

  ~Led()
  {
  }

  boolean getState()
  {
    if(state == 1)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void setState(boolean state)
  {
    state = this->state;
    digitalWrite(state,pin);
  }

  int getPin()
  {
    return pin;
  }

  void setPin(int pin)
  {
    pin = this->pin;    
  }
};

Led *l;
void setup()
{
  l = new Led(8);
}

void loop()
{
  l->setState(true);
  delay(500);
  l->setState(false);
  delay(500);
}





