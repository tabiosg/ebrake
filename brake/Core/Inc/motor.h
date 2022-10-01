#pragma once

#include "pin_data.h"
#include "timer_data.h"
#include <stdint.h>

// The motor is a DC Gear motor with two-channel Hall effect encoder
// The H-Bridge being used is a standard H-Bridge
typedef struct {
	PinData fwd_pin;
	PinData bwd_pin;
	PWMTimerData timer;
} Motor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: Ports and pins correspond to H-Bridge.
// Timer is associated with PWM connected to H-Bridge
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Motor object
Motor *new_motor(
	PinData fwd,
	PinData bwd,
	PWMTimerData *timer
);

// REQUIRES: Speed to be between -1.0 and 1.0
// MODIFIES: H-Bridge digital outputs and timer PWM
// EFFECTS: The H-Bridge PWM and direction will change
void set_motor_speed(Motor *motor, double speed_1);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
