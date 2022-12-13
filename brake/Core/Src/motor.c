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
// and direction is a bool that dictates direction
// MODIFIES: nothing
// EFFECTS: Moves the motor a certain by a certain amount of steps
void step_motor_direction(Motor *motor, bool dir) {
	set_pin_value(motor->dir_pin, dir);
	set_pin_value(motor->stp_pin, GPIO_PIN_SET);
	set_pin_value(motor->stp_pin, GPIO_PIN_RESET);
}
