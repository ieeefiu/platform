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
#define SENSOR_NUMBER 2

/* Number of values returned by a sensor read */
#define SENSOR_VALUES 4

/* Constants for color values read from sensor */
#define YELLOW_CLEAR_LOWER 25000
#define RGB_CLEAR_LOWER 4000
#define RED_LOWER 4000

enum colors { NONE, RED, GREEN, YELLOW, BLUE };

typedef struct {
	uint8_t channel;
	enum colors color;
	uint16_t values[SENSOR_VALUES];
} ColorSensor;


/* Initialize channel selector */
void selector_init(void);

/* Select the sensor to read from */
void select_channel(uint8_t channel);

/* Return current channel */
uint8_t selector_get_channel(void);

/* Initialize a single color sensor in memory */
ColorSensor *sensor_new(uint8_t channel);

/* Initialize color sensor on i2c */
void sensor_init(ColorSensor *sensor);

/* Output sensor value over USART */
void sensor_print(ColorSensor *sensor);

/* Obtains data from a color sensor */
enum colors sensor_get(ColorSensor *sensor);
