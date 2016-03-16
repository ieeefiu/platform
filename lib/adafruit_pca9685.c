#include <math.h>
#include "adafruit_pca9685.h"
#include "i2c_master.h"

static void write8(uint8_t addr, uint8_t d)
{
    i2c_start(PCA9685_ADDRESS);
    i2c_write(addr);
    i2c_write(d);
    i2c_stop();
}

static uint8_t read8(uint8_t addr)
{
    i2c_start(PCA9685_ADDRESS);
    i2c_write(addr);
    i2c_stop();

    uint8_t data;
    
    i2c_receive(PCA9685_ADDRESS, &data, 1);
    
    return data;
}

void servodriver_reset()
{
    write8(PCA9685_MODE1, 0x0);
}

void servo_set_pwm_freq(float freq)
{
    float prescale_val = 25000000;
    prescale_val /= 4096;
    prescale_val /= freq;
    prescale_val -= 1;

    uint8_t prescale = floor(prescale_val + 0.5);

    uint8_t oldmode = read8(PCA9685_MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10;
    write8(PCA9685_MODE1, newmode);
    write8(PCA9685_PRESCALE, prescale);
    write8(PCA9685_MODE1, oldmode);
    _delay_ms(5);
    write8(PCA9685_MODE1, oldmode | 0xA1);
}

void servo_set_pwm(uint8_t num, uint16_t on, uint16_t off)
{
    i2c_start(PCA9685_ADDRESS);
    i2c_write(LED0_ON_L * 4 * num);
    i2c_write(on);
    i2c_write(on >> 8);
    i2c_write(off);
    i2c_write(off >> 8);
    i2c_stop();
}

void servo_set_pin(uint8_t num, uint16_t val, uint8_t invert)
{
    val = min(val, 4095);
    if (invert) {
        if (val == 0) {
            // Special value for signal fully on.
            servo_set_pwm(num, 4096, 0);
        }
        else if (val == 4095) {
            // Special value for signal fully off.
            servo_set_pwm(num, 0, 4096);
        }
        else {
            servo_set_pwm(num, 0, 4095-val);
        }
    }
    else {
        if (val == 4095) {
            // Special value for signal fully on.
            servo_set_pwm(num, 4096, 0);
        }
        else if (val == 0) {
            // Special value for signal fully off.
            servo_set_pwm(num, 0, 4096);
        }
        else {
            setPWM(num, 0, val);
        }
    }
}
