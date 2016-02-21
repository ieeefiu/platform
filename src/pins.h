#pragma once

/*********************************************************************
 * Functions for pins
 ********************************************************************/

#include <avr/io.h>
#include <stdlib.h>

#include "i2c_master.h"
#include "USART.h"

#define TEST_SENSOR PB0

typedef struct {
    /* placeholder for motor */
    uint8_t channel;
    uint8_t zero;
} Pin;

/* make new pin */
Pin *pin_new(uint8_t channel, uint8_t zero_pin);

/* initialize pin */
void pin_init(Pin *pin);

/* reset rail to zero position */
uint8_t pins_return_to_zero(Pin **pin);

/* tell pin to move forward */
uint8_t pin_move_forward(Pin *pin);

/* tell pin to move backwards */
uint8_t pin_move_backwards(Pin *pin);

/* checks to see if pin is at zero position */
uint8_t pin_check_zero(Pin *pin);

/* halt pin */
uint8_t pin_halt(Pin *pin);
