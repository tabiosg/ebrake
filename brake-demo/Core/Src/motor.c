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
// and shifted_degrees is the amount to turn
// MODIFIES: nothing
// EFFECTS: Moves the motor a certain angle away in degrees
void change_motor_angle(Motor *motor, float angle) {
    set_pin_value(motor->dir_pin, angle >= 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    angle = angle > 0 ? angle : -angle;
    for (int i = 0; i < angle / MOTOR_DEGREES_PER_STEP; ++i) {
    	set_pin_value(motor->stp_pin, GPIO_PIN_SET);
		for (int j = 0; j < 1000; ++j);
		set_pin_value(motor->stp_pin, GPIO_PIN_RESET);
    }
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
