#ifndef BreadLed_h
#define BreadLed_h

#include "Arduino.h"

class BreadLed
{
public:
	BreadLed(uint8_t pin);
	void send(uint8_t green, uint8_t red, uint8_t blue);

private:
	uint8_t pin;
};

#endif