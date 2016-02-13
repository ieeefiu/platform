/*********************************************************************
 * FIU 2016 IEEE Southeastcon Hardware Competition
 *
 * Platform 5000
 * By William Oberndorfer
 * 
 * Eats, reads, and shoves out blocks.
 *
 * For the generic platform, eats all blocks and shoves them all out
 * onto the corkboard region.
 *
 * For the top platform, eats all the blocks and shoves them out by
 * color, determined by whichever bucket the robot is in front of.
 *
 * For the last platform, eats all the blocks and shoves the blue ones
 * onto the corkboard and the rest into the truck.
 *
 ********************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "i2c_master.h"
#include "USART.h"
#include "colorsensors.h"

volatile enum colors shovecolor = NONE;
