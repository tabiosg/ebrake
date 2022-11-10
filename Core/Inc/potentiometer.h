#pragma once

#include "adc_sensor.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	ADCSensor *adc_sensor;
	uint8_t rank;
} Potentiometer;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Potentiometer object
Potentiometer *new_potentiometer(ADCSensor *_adc_sensor, uint8_t _rank);

// REQUIRES: potentiometer is a Potentiometer object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of trigger.
// Expect an integer between 0 and 4096.
uint32_t get_potentiometer_input(Potentiometer *potentiometer);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
