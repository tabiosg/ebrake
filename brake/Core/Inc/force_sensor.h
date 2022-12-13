#pragma once

#include "pin_data.h"
#include "adc_sensor.h"

// The load cell amp is the HX711.
typedef struct {
	ADCSensor *adc_sensor;
	uint8_t rank;
} ForceSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ForceSensor object
ForceSensor *new_force_sensor(ADCSensor *_adc_sensor, uint8_t _rank);

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value force sensor voltage output.
uint16_t get_force_sensor_data(ForceSensor *force_sensor);
