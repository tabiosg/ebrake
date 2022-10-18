#include "motor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _dir_pin corresponds to DRV8825 dir pin.
// and _stp_pin corresponds to DRV8825 step pin
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Motor object
Motor *new_motor(
	PinData *_dir_pin,
	PinData *_stp_pin
) {
    Motor *motor = (Motor*) malloc(sizeof(Motor));
    motor->dir_pin = _dir_pin;
    motor->stp_pin = _stp_pin;
	return motor;
}

// REQUIRES: motor is a Motor object
// and steps is the amount of steps to turn
// MODIFIES: nothing
// EFFECTS: Moves the motor a certain by a certain amount of steps
void change_motor_steps(Motor *motor, int steps) {
    set_pin_value(motor->dir_pin, steps >= 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    steps = abs(steps);
    float delay = 700;
    for (int i = 0; i < steps; ++i) {
    	if (delay > 250) {
    		delay -= 0.5;
    	}
    	set_pin_value(motor->stp_pin, GPIO_PIN_SET);
		for (int j = 0; j < delay; ++j);
		set_pin_value(motor->stp_pin, GPIO_PIN_RESET);
		for (int j = 0; j < delay; ++j);
    }
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
