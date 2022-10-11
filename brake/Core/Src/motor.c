#include "motor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _dir_pin correspond to DRV8825 dir pin.
// Timer is associated with PWM connected to DRV8825 step pin.
// position is an integer that is the assumed position
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Motor object
Motor *new_motor(
	PinData *_dir_pin,
	PWMTimer *_timer
) {
    Motor *motor = (Motor*) malloc(sizeof(Motor));
    motor->dir_pin = _dir_pin;
    motor->timer = _timer;
    start_pwm_timer(motor->timer);
	return motor;
}

// REQUIRES: motor is a Motor object
// and speed to be between -1.0 and 1.0
// MODIFIES: timer settings
// EFFECTS: Changes the speed of the motor
void set_motor_speed(Motor *motor, float speed_1) {

    // This code only supports three speeds:
    // Backwards, stop, or forwards.
    // The speed can not be adjusted with this code.
    // The speed actually depends on the amount of rising edges, not the duty cycle.
    // TODO - Change frequency based on speed_1.
    int32_t pwm = speed_1 * 100.0f;
    pwm = pwm > 100 ? 100 : (pwm < -100 ? -100 : pwm);
    *(motor->timer->ccr_channel) = 0;
    set_pin_value(motor->dir_pin, speed_1 >= 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    *(motor->timer->ccr_channel) = 50;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
