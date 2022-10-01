#pragma once

#include "pin_data.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	PinData pins[7];
	uint8_t current_number;
	bool is_on;
} Display;

/** PUBLIC FUNCTIONS **/

// REQUIRES: display_pins corresponding to pins of display,
// number is an integer 0 to 9,
// and _is_on is a boolean for if display begins on or off
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object,
Display *new_display(PinData *display_pins[7], uint8_t display_number, bool _is_on);

// REQUIRES: Display is an object, and on is a boolean
// MODIFIES: outputs of ports and pins
// EFFECTS: turns display on number to particular display
void change_display_state(Display *display, bool on);

// REQUIRES: Display is an object, number is an integer 0 to 9
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void update_display_number(Display *display, uint8_t number);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
