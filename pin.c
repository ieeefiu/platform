/*********************************************************************
 * Functions for pins
 ********************************************************************/

#include "pin.h"

Pin *pin_new(uint8_t channel)
{
	Pin *pin;
	pin = malloc(sizeof(Pin));

	pin->channel = channel;
	
	return pin;
}

void pin_init(Pin *pin)
{
	
}

uint8_t shove(ColorSensor **sensors, Pin **pins, enum colors shovecolor)
{
	
}

uint8_t pin_return_to_zero(Pin *pin)
{
	
}

uint8_t pin_move_forward(Pin *pin)
{
	
}

uint8_t pin_move_backwards(Pin *pin)
{
	
}

uint8_t pin_halt(Pin *pin)
{
	
}
