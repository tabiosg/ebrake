#pragma once

#include "stm32g0xx_hal.h"
#include "pin_data.h"
#include "pwm_timer_data.h"
#include <stdint.h>
#include <stdlib.h>

// The motor is a NEMA17 stepper motor.
// The stepper motor has 200 steps per revolution.
// The motor driver being used is a DRV8825
typedef struct {
	PinData *dir_pin;
	PWMTimer *timer;
} Motor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _dir_pin correspond to DRV8825 dir pin.
// Timer is associated with PWM connected to DRV8825 step pin.
// position is an integer that is the assumed position
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Motor object
Motor *new_motor(
	PinData *_dir_pin,
	PWMTimer *_timer
);

// REQUIRES: motor is a Motor object
// and speed to be between -1.0 and 1.0
// MODIFIES: timer settings
// EFFECTS: Changes the speed of the motor
void set_motor_speed(Motor *motor, float speed_1);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
