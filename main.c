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

static inline void testmenu(void)
{
	printString("Make a selection: \n"
				"1. Red\n"
				"2. Green\n"
				"3. Yellow\n"
				"4. Blue\n\n");
}

volatile enum colors shovecolor = NONE;
volatile uint8_t received;

int main(void)
{
	uint8_t i;

	ColorSensor *colorsensors[SENSOR_NUMBER];
	for (i = 0; i < SENSOR_NUMBER; i++) {
		colorsensors[i] = sensor_new(i);
	}
	
	initUSART();
	sei();
	set_sleep_mode(SLEEP_MODE_IDLE);
	i2c_init();

	printString("FIU IEEE Block Shoving Robot Platform Module\n"
				"--------------------------------------------\n\n");

	selector_init();

	printString("Initializing sensors...\n");
	
	for (i = 0; i < SENSOR_NUMBER; i++) {
		sensor_init(colorsensors[i]);
		printString("Sensor initialized at channel ");
		printByte(colorsensors[i]->channel);
	}

	printString("~ All sensors initialized ~\n\n");

	while(1) {
		testmenu();
		shovecolor = NONE;
		sleep_mode();
		for (i = 0; i < SENSOR_NUMBER; i++) {
			sensor_get(colorsensors[i]);
			sensor_print(colorsensors[i]);
		}
	}
	
	return 0;
}

ISR(USART_RX_vect)
{
	cli();
	received = UDR0;

	switch (received) {
	case '1':
		shovecolor = RED;
		break;
	case '2':
		shovecolor = GREEN;
		break;
	case '3':
		shovecolor = YELLOW;
		break;
	case '4':
		shovecolor = BLUE;
		break;
	default:
		shovecolor = NONE;
		break;
	}
	sei();
}
