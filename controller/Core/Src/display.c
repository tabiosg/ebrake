#include "display.h"

/** PUBLIC FUNCTIONS **/

/** PUBLIC FUNCTIONS **/

// REQUIRES: _shift_register is a ShiftRegister object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(ShiftRegister *_shift_register) {
	Display *display = (Display*) malloc(sizeof(Display));
	display->shift_register = _shift_register;
	display->display_numbers[0] = 0;
	display->display_numbers[1] = 0;
	display->display_numbers[2] = 0;
	display->display_numbers[3] = 0;
	display->display_numbers[4] = 0;
	display->display_numbers[5] = 0;
	display->display_numbers[6] = 0;
	display->display_numbers[7] = 0;
	display->display_numbers[8] = 0;
	display->display_numbers[9] = 0;
	return display;
}

// REQUIRES: Display is a Display object and number is an integer 0 to 9
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void update_display_number(Display *display, uint8_t number) {
	uint8_t display_number = display->display_numbers[number];
	for (uint8_t i = 0; i < 8; ++i) {
		uint8_t shift_val = display_number & 0b1;
		shift_shift_register(display->shift_register, shift_val);
		display_number = display_number >> 1;
	}
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
