#pragma once

/*********************************************************************
 * Functions for reading and switching between color sensors
 *
 * Sensor used is TCS34725, 7-bit addresses fixed at 0x29.
 * Uses a PCA9547 to switch between them. 7-bit address is 0x70.
 ********************************************************************/

/* address constants for the channel switcher */
#define CHANNEL_WRITE 0xE0
#define CHANNEL_READ 0xE1

/* offset for channel value */
#define CHANNEL_OFFSET 0x08

/* address constants for color sensors */
#define SENSOR_WRITE 0x52
#define SENSOR_READ 0x53

/* Number of sensors attached. Supports up to eight */
#define SENSOR_NUMBER 8

/* Number of values returned by a sensor read */
#define SENSOR_VALUES 4

enum colors { NONE, RED, GREEN, YELLOW, BLUE };

typedef struct {
	uint8_t channel;
	enum colors color_value;
	uint16_t sensor_values[SENSOR_VALUES];
} ColorSensor;


/* Initialize channel selector */
void selector_init(void);

/* Select the sensor to read from */
void select_channel(uint8_t channel);

/* Return current channel */
uint8_t selector_get_channel(void);


/* Initialize color sensor */
ColorSensor *sensor_init(uint8_t channel);

/* Output sensor value over USART */
void sensor_printvalues(uint16_t *values);

/* Populates the values array with sensor data from a single sensor */
void sensor_get_and_set(ColorSensor *sensor);

/* Gets color value from a color sensor */
void sensor_get(uint16_t *values);