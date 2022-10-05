#pragma once

#include "stm32g0xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	ADC_HandleTypeDef *adc;
	uint32_t value;
} Potentiometer;

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Potentiometer object
Potentiometer *new_potentiometer(ADC_HandleTypeDef *hadc);

// REQUIRES: Potentiometer is an object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of trigger.
// Expect an integer between 0 and 4096.
uint32_t get_potentiometer_input(Potentiometer *potentiometer);

// REQUIRES: Potentiometer is an object
// MODIFIES: value
// EFFECTS: Updates the stored value of value.
void update_potentiometer_value(Potentiometer *potentiometer);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
