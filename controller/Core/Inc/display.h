#pragma once

#include "pin_data.h"
#include <stdint.h>

typedef struct {
	PinData pins[7];
} Display;

/** PUBLIC FUNCTIONS **/

// REQUIRES: pins corresponding to pins of display
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(
    PinData *_pins[7]
);

// REQUIRES: Display is an object, number is int 0 to 9
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void set_display_number(Display *display, uint8_t number);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
