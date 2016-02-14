/*********************************************************************
 * Functions for reading and switching between color sensors
 ********************************************************************/

#include <avr/io.h>
#include <stdlib.h>

#include "i2c_master.h"
#include "USART.h"
#include "colorsensors.h"

void selector_init(void)
{
	i2c_start(CHANNEL_WRITE);
	i2c_write(0x08);
	i2c_stop();
	printString("PCA9547 Initialized\n\n");
}

void select_channel(uint8_t channel)
{
	i2c_start(CHANNEL_WRITE);
	i2c_write(CHANNEL_OFFSET | channel);
	i2c_stop();
}

uint8_t selector_get_channel(void)
{
	uint8_t retval = 0;
	i2c_start(CHANNEL_READ);
	retval = i2c_read_nack();
	i2c_stop();
	return retval - CHANNEL_OFFSET;
}

ColorSensor *sensor_new(uint8_t channel)
{
	ColorSensor *sensor;
	uint8_t i = 0;
	sensor = (ColorSensor *)malloc(sizeof(ColorSensor));
	
	sensor->channel = channel;
	sensor->color = NONE;
	for (i = 0; i < SENSOR_VALUES; i++) {
		sensor->values[i] = 0;
	}
	
	return sensor;
}

void sensor_init(ColorSensor *sensor)
{
	select_channel(sensor->channel);
	i2c_start(SENSOR_WRITE);
	i2c_write(0x80 | 0x00);
	i2c_stop();
	i2c_start(SENSOR_WRITE);
	i2c_write(0x01 | 0x02);
	i2c_stop();
	i2c_start(SENSOR_WRITE);
	i2c_write(0x80 | 0x14);
	i2c_stop();
}

void sensor_print(ColorSensor *sensor)
{
	printString("Channel: ");
	printByte(sensor->channel);
	printString("\nC: ");
	printWord(sensor->values[0]);
	printString("    ");
	printString("R: ");
	printWord(sensor->values[1]);
	printString("    ");
	printString("G: ");
	printWord(sensor->values[2]);
	printString("    ");
	printString("B: ");
	printWord(sensor->values[3]);
	printString("\nColor: ");
	
	switch (sensor->color) {
	case NONE:
		printString("NONE\n");
		break;
	case RED:
		printString("RED\n");
		break;
	case GREEN:
		printString("GREEN\n");
		break;
	case YELLOW:
		printString("YELLOW\n");
		break;
	case BLUE:
		printString("BLUE\n");
		break;
	default:
		break;
	}
}

enum colors sensor_get(ColorSensor *sensor)
{
	uint8_t i = 0;
	select_channel(sensor->channel);
	i2c_start(SENSOR_READ);
	for (i = 0; i < SENSOR_VALUES; i++) {
		sensor->values[i] = i2c_read_ack();
		sensor->values[i] |= (i2c_read_ack() << 8);
	}
	i2c_stop();

	if (sensor->values[0] > YELLOW_CLEAR_LOWER) {
		sensor->color = YELLOW;
	}
	else if (sensor->values[0] > RGB_CLEAR_LOWER) {
		if (sensor->values[1] > RED_LOWER) {
			sensor->color = RED;
		}
		else if (sensor->values[3] < sensor->values[1]) {
			sensor->color = GREEN;
		}
		else {
			sensor->color = BLUE;
		}
	}
	else {
		sensor->color = NONE;
	}
	
	return sensor->color;
}
