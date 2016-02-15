#pragma once

/*********************************************************************
 * Functions for shoving blocks
 ********************************************************************/

#define TEST_SENSOR PB0

typedef struct {
	/* placeholder for motor */
	uint8_t channel;
} Pin;

/* make new pin */
Pin *pin_new(uint8_t channel);

/* initialize pin */
void pin_init(Pin *pin);

/* shove whatever needs shoving and report status */
uint8_t shove(ColorSensor **sensors, Pin **pins, enum colors shovecolor);

/* reset rail to zero position */
uint8_t pin_return_to_zero(Pin *pin);

/* tell pin to move forward */
uint8_t pin_move_forward(Pin *pin);

/* tell pin to move backwards */
uint8_t pin_move_backwards(Pin *pin);

/* halt pin */
uint8_t pin_halt(Pin *pin);
