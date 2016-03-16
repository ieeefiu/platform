#pragma once

#define PCA9685_ADDRESS 0x60
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

void servodriver_reset();

void servo_set_pwm_freq(float freq);
void servo_set_pwm(uint8_t num, uint16_t on, uint16_t off);
void servo_set_pin(uint8_t num, uint16_t val, uint8_t invert);
