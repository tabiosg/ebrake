#pragma once

#include "adc_sensor.h"

// We read in from a thermistor that went through a voltage divider.
typedef struct {
	ADCSensor *adc_sensor;
	uint8_t rank;
} Thermistor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Thermistor object
Thermistor *new_thermistor(ADCSensor *_adc_sensor, uint8_t _rank);

// REQUIRES: thermistor is a Thermistor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value thermistor data.
uint8_t get_thermistor_data(Thermistor *thermistor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
