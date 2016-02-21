/*********************************************************************
 * Functions for pins
 ********************************************************************/
#include <avr/io.h>
#include <stdlib.h>

#include "i2c_master.h"
#include "USART.h"
#include "colorsensors.h"
#include "pins.h"

Pin *pin_new(uint8_t channel, uint8_t zero_pin)
{
    Pin *pin;
    pin = malloc(sizeof(Pin));

    pin->channel = channel;
    pin->zero = zero_pin;
    
    return pin;
}

void pin_init(Pin *pin)
{
    
}

uint8_t pins_return_to_zero(Pin **pin)
{
    uint8_t stop_status = 0;
    int i;
    while (stop_status < SENSOR_NUMBER) {
        stop_status = 0;
        for (i = 0; i < SENSOR_NUMBER; i++) {
            if (pin_check_zero(pin[i])) {
                pin_halt(pin[i]);
                stop_status++;
            }
            else {
                pin_move_backwards(pin[i]);
            }
        }
    } 
    return 0;
}

uint8_t pin_move_forward(Pin *pin)
{
    /* tell motor to move forward */
    return 0;
}

uint8_t pin_move_backwards(Pin *pin)
{
    if (pin_check_zero(pin)) {
        pin_halt(pin);
        return 1;
    }
    else {
        /* tell motor to move backwards */
    }
    return 0;
}

uint8_t pin_check_zero(Pin *pin)
{
    if (bit_is_clear(PINB, pin->zero)) {
        return 1;
    }
    else {
        return 0;
    }
}

uint8_t pin_halt(Pin *pin)
{
    /* tell motor to stop */
    return 0;
}
