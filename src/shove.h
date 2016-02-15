#pragma once

/*********************************************************************
 * Functions for shoving
 ********************************************************************/

#include <avr/io.h>

#include "i2c_master.h"
#include "USART.h"
#include "colorsensors.h"
#include "pins.h"

/* shove whatever needs shoving and report status */
uint8_t shove_all(ColorSensor **sensors, Pin **pins, enum colors shovecolor);

/* shove a single rail */
uint8_t shove_one(ColorSensor *sensor, Pin *pin, enum colors shovecolor);

