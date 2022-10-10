#pragma once

#include "pin_data.h"

#define FORCE_SENSOR_NEWTONS_PER_COUNT_RATIO 1.0f

// The load cell amp is the HX711.
typedef struct {
	ADC_HandleTypeDef *adc;
	uint32_t value;
} ForceSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of the force sensor in Newtons.
float get_force_sensor_input(ForceSensor *force_sensor);

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: value
// EFFECTS: Updates the stored value of value
float update_force_sensor_value(ForceSensor *force_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
