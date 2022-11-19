#pragma once

#include "shift_register.h"
#include <stdbool.h>
#include <stdint.h>

// Display should be connected to the shift register as follows:
// Display g f e d c b a should be connected to
// shift register QG, QF, QE, QD, QC, QB, QA.
// Assumes that display is in common anode configuration (0 is on).
typedef struct {
	ShiftRegister *shift_register;
	uint16_t left_display_numbers[10];
	uint16_t right_display_numbers[10];
} Display;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _shift_register is a ShiftRegister object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(ShiftRegister *_shift_register);

// REQUIRES: Display is a Display object and number is an integer 0 to 99
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void update_display_number(Display *display, uint16_t number);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
