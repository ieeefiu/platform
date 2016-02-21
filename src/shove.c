/*********************************************************************
 * Functions for shoving
 ********************************************************************/

#include <avr/io.h>

#include "i2c_master.h"
#include "USART.h"
#include "shove.h"

uint8_t shove_all_with_color
(ColorSensor **sensors, Pin **pins, enum colors shovecolor)
{
    return 0;
}

uint8_t shove_range_with_color
(ColorSensor **sensors, Pin **pins,
 uint8_t lower, uint8_t upper, enum colors shovecolor)
{
    return 0;
}

uint8_t shove_one(ColorSensor *sensor, Pin *pin)
{
    return 0;
}

uint8_t shove_all(ColorSensor **sensors, Pin **pins)
{
    return 0;
}
