#pragma once

#include "pin_data.h"
#include "adc_sensor.h"

// We read in from a battery sensor.
typedef struct {
	ADCSensor *adc_sensor;
	uint8_t rank;
} BatterySensor;

#define BATTERY_SENSOR_FIVE_BATTERY 1.7f
#define BATTERY_SENSOR_THREE_BATTERY 1.4f
#define BATTERY_SENSOR_ONE_BATTERY 0.9

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created BatterySensor object
BatterySensor *new_battery_sensor(ADCSensor *_adc_sensor, uint8_t _rank);

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value battery sensor data.
float get_battery_sensor_data(BatterySensor *battery_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/