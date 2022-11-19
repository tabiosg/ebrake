#include "display.h"

/** PUBLIC FUNCTIONS **/

/** PUBLIC FUNCTIONS **/

// REQUIRES: _shift_register is a ShiftRegister object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(ShiftRegister *_shift_register) {
	Display *display = (Display*) malloc(sizeof(Display));
	display->shift_register = _shift_register;
	display->display_numbers[0] = 0xC0;
	display->display_numbers[1] = 0xF9;
	display->display_numbers[2] = 0xA4;
	display->display_numbers[3] = 0xB0;
	display->display_numbers[4] = 0x99;
	display->display_numbers[5] = 0x92;
	display->display_numbers[6] = 0x82;
	display->display_numbers[7] = 0xF8;
	display->display_numbers[8] = 0x80;
	display->display_numbers[9] = 0x90;
	return display;
}

// REQUIRES: Display is a Display object and number is an integer 0 to 99
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void update_display_number(Display *display, uint16_t number) {
	uint8_t display_numbers[2];
	display_numbers[0] = display->display_numbers[(number / 10) % 10];
	display_numbers[1] = display->display_numbers[number % 10];
	for (uint8_t i = 0; i < 2; ++i) {
		uint8_t display_number = display_numbers[i];
		for (uint8_t j = 0; j < 8; ++j) {
			// Load in g, then f, e, d, c, b, then a.
			uint8_t shift_val = (display_number & (0b1 << (7 - j))) >> (7 - j);
			shift_shift_register(display->shift_register, shift_val);
		}

	}
}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
