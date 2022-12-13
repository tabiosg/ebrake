#include "display.h"

/** PUBLIC FUNCTIONS **/

/** PUBLIC FUNCTIONS **/

// REQUIRES: _shift_register is a ShiftRegister object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(ShiftRegister *_shift_register) {
	Display *display = (Display*) malloc(sizeof(Display));
	display->shift_register = _shift_register;

	// These numbers are like this because our actual schematic and pins were off,
	// so this is a software fix.
	display->left_display_numbers[0] = 0b0000000001000000;
	display->left_display_numbers[1] = 0b0000011101110000;
	display->left_display_numbers[2] = 0b0000100000100000;
	display->left_display_numbers[3] = 0b0000001000100000;
	display->left_display_numbers[4] = 0b0000011000010000;
	display->left_display_numbers[5] = 0b0000001000001000;
	display->left_display_numbers[6] = 0b0000000000001000;
	display->left_display_numbers[7] = 0b0000011001100000;
	display->left_display_numbers[8] = 0b0000000000000000;
	display->left_display_numbers[9] = 0b0000001000000000;

	display->right_display_numbers[0] = 0b0000000000000100;
	display->right_display_numbers[1] = 0b0011000000000111;
	display->right_display_numbers[2] = 0b0100000000000010;
	display->right_display_numbers[3] = 0b0001000000000010;
	display->right_display_numbers[4] = 0b0011000000000001;
	display->right_display_numbers[5] = 0b0001000010000000;
	display->right_display_numbers[6] = 0b0000000010000000;
	display->right_display_numbers[7] = 0b0011000000000110;
	display->right_display_numbers[8] = 0b0000000000000000;
	display->right_display_numbers[9] = 0b0001000000000000;

	return display;
}

// REQUIRES: Display is a Display object and number is an integer 0 to 99
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void update_display_number(Display *display, uint16_t number) {
	uint16_t numbers_to_insert = display->left_display_numbers[(number / 10) % 10];
	numbers_to_insert |= display->right_display_numbers[number % 10];

	for (uint8_t j = 0; j < 16; ++j) {
		uint8_t shift_val = (numbers_to_insert & (0b1 << (j))) >> (j);
		shift_shift_register(display->shift_register, shift_val);
	}
}
