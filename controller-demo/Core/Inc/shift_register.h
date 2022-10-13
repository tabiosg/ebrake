#pragma once

#include "pin_data.h"
#include <stdint.h>

// The shift register is SN74HC595
typedef struct {
	PinData* ser_pin;
	PinData* srclk_pin;
	PinData* not_srclk_pin;
	PinData* rclk_pin;
	PinData* not_oe_pin;
} ShiftRegister;

/** PUBLIC FUNCTIONS **/

// REQUIRES: The pins correspond to the pins of the shift register
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ShiftRegister object
ShiftRegister *new_shift_register(
		PinData *_ser_pin,
		PinData *_srclk_pin,
		PinData *_not_srclk_pin,
		PinData *_rclk_pin,
		PinData *_not_oe_pin);

// REQUIRES: shift_register is a ShiftRegister object and value is either 0 or 1
// MODIFIES: outputs of ports and pins
// EFFECTS: shift value into register
void shift_shift_register(ShiftRegister *shift_register, uint8_t value);

// REQUIRES: shift_register is a ShiftRegister object and value is either 0 or 1
// MODIFIES: outputs of ports and pins
// EFFECTS: clears the shift register
void reset_shift_register(ShiftRegister *shift_register);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
