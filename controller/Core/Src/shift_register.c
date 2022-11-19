#include "shift_register.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: The pins correspond to the pins of the shift register
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ShiftRegister object
ShiftRegister *new_shift_register(
		PinData *_ser_pin,
		PinData *_srclk_pin,
		PinData *_not_srclk_pin,
		PinData *_rclk_pin,
		PinData *_not_oe_pin) {
	ShiftRegister *shift_register = (ShiftRegister*) malloc(sizeof(ShiftRegister));
	shift_register->ser_pin = _ser_pin;
	shift_register->srclk_pin = _srclk_pin;
	shift_register->not_srclk_pin = _not_srclk_pin;
	shift_register->rclk_pin = _rclk_pin;
	shift_register->not_oe_pin = _not_oe_pin;
	return shift_register;
}

// REQUIRES: shift_register is a ShiftRegister object and value is either 0 or 1
// MODIFIES: outputs of ports and pins
// EFFECTS: shift value into register
void shift_shift_register(ShiftRegister *shift_register, uint8_t value) {
	set_pin_value(shift_register->ser_pin, 1);
	set_pin_value(shift_register->ser_pin, value);
	set_pin_value(shift_register->not_srclk_pin, 1);
	set_pin_value(shift_register->srclk_pin, 1);
	set_pin_value(shift_register->srclk_pin, 0);
	set_pin_value(shift_register->rclk_pin, 1);
	set_pin_value(shift_register->rclk_pin, 0);
	set_pin_value(shift_register->ser_pin, 0);
}

// REQUIRES: shift_register is a ShiftRegister object and value is either 0 or 1
// MODIFIES: outputs of ports and pins
// EFFECTS: clears the shift register
void reset_shift_register(ShiftRegister *shift_register) {
	set_pin_value(shift_register->rclk_pin, 1);
	set_pin_value(shift_register->rclk_pin, 0);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
