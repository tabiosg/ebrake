#include "pin_data.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _port and _pin corresponds to
// the port and pin.
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created PinData object
PinData *new_pin_data(GPIO_TypeDef *_port, uint16_t _pin) {
    PinData *pin_data = (PinData*) malloc(sizeof(PinData));
	pin_data->port = _port;
    pin_data->pin = _pin;
	return pin_data;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/