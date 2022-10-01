#pragma once

#include "pin_data.h"
#include "timer_data.h"
#include <stdint.h>

// The motor is a NEMA17 stepper motor
// The motor driver being used is a DRV8825
typedef struct {
	PinData stp_pin;
	PinData dir_pin;
	PWMTimerData timer;
} Motor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: Ports and pins correspond to DRV8825 pins.
// Timer is associated with PWM connected to DRV8825 step pin.
// position is an integer that is the assumed position
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Motor object
Motor *new_motor(
	PinData stp_pin,
	PinData dir_pin,
	PWMTimerData *timer
);

// REQUIRES: motor is a Motor object
// and speed to be between -1.0 and 1.0
// MODIFIES: timer settings
// EFFECTS: Changes the speed of the motor
void set_motor_speed(Motor *motor, float speed_1);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
