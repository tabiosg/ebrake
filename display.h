#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdint.h>

typedef struct {
	GPIO_TypeDef *ports[7];
	uint16_t pins[7];
} Display;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _ports and _pins corresponding to ports and pins
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Display object
Display *new_display(
    GPIO_TypeDef *_ports[7],
	uint16_t _pins[7]
);

// REQUIRES: Display is an object, number is int 0 to 9
// MODIFIES: outputs of ports and pins
// EFFECTS: displays number to particular display
void set_display_number(Display *display, uint8_t number);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

#endif /* INC_DISPLAY_H_ */