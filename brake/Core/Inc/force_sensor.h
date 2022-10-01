#pragma once

#include "pin_data.h"

// The force sensor being used is the SEN-10245.
// The load cell amp is the HX711.
typedef struct {
	PinData sck_pin;
	PinData data_pin;
} ForceSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: sck and data have the corresponding PinData for sck and data
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ForceSensor object
ForceSensor *new_force_sensor(PinData sck, PinData data);

// REQUIRES: ForceSensor is an object
// MODIFIES: nothing
// EFFECTS: Returns a force detected in Newtons
double get_force_sensor_data(ForceSensor *force_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
