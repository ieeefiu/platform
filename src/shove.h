#pragma once

/*********************************************************************
 * Functions for shoving
 ********************************************************************/

#include "colorsensors.h"
#include "pins.h"

/* shove all based on color */
uint8_t shove_all_with_color
(ColorSensor **sensors, Pin **pins, enum colors shovecolor);

/* shove a range of blocks based on color */
uint8_t shove_range_with_color
(ColorSensor **sensors, Pin **pins,
 uint8_t lower, uint8_t upper, enum colors shovecolor);

/* shove a single rail */
uint8_t shove_one(ColorSensor *sensor, Pin *pin);

/* shove everything */
uint8_t shove_all(ColorSensor **sensors, Pin **pins);
