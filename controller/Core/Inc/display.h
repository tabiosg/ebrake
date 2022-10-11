#pragma once

#include "shift_register.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	ShiftRegister *shift_register;
	uint8_t display_numbers[10];
} Display;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _shift_register is a ShiftRegister object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(ShiftRegister *_shift_register);

// REQUIRES: Display is a Display object and number is an integer 0 to 9
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void update_display_number(Display *display, uint8_t number);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
