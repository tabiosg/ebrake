#pragma once

#include "stm32g0xx_hal.h"
#include "pin_data.h"
#include <stdint.h>
#include <stdlib.h>

#define MOTOR_DEGREES_PER_STEP 1.8f

// The motor is a NEMA17 stepper motor
// The motor driver being used is a DRV8825
typedef struct {
	PinData *dir_pin;
	PinData *stp_pin;
} Motor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _dir_pin corresponds to DRV8825 dir pin.
// and _stp_pin corresponds to DRV8825 step pin
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Motor object
Motor *new_motor(
	PinData *_dir_pin,
	PinData *_stp_pin
);

// REQUIRES: motor is a Motor object
// and steps is the amount of steps to turn
// MODIFIES: nothing
// EFFECTS: Moves the motor a certain by a certain amount of steps
void change_motor_steps(Motor *motor, int steps);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
