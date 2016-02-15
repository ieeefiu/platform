#pragma once

/*********************************************************************
 * Functions for pins
 ********************************************************************/

#include <avr/io.h>

#include "i2c_master.h"
#include "USART.h"
#include "colorsensors.h"

#define TEST_SENSOR PB0

typedef struct {
	/* placeholder for motor */
	uint8_t channel;
} Pin;

/* make new pin */
Pin *pin_new(uint8_t channel);

/* initialize pin */
void pin_init(Pin *pin);

/* reset rail to zero position */
uint8_t pin_return_to_zero(Pin *pin);

/* tell pin to move forward */
uint8_t pin_move_forward(Pin *pin);

/* tell pin to move backwards */
uint8_t pin_move_backwards(Pin *pin);

/* halt pin */
uint8_t pin_halt(Pin *pin);
