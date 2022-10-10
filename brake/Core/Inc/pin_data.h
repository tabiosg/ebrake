#pragma once

#include "stm32g0xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

// Used to store the data of a pin
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} PinData;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _port and _pin corresponds to
// the port and pin.
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created PinData object
PinData *new_pin_data(GPIO_TypeDef *_port, uint16_t _pin);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/