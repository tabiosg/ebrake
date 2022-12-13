#pragma once

#include "adc_sensor.h"

// We read in from a battery sensor.
typedef struct {
	ADCSensor *adc_sensor;
	uint8_t rank;
} BatterySensor;

#define BATTERY_SENSOR_FIVE_BATTERY 1.35f
#define BATTERY_SENSOR_THREE_BATTERY 1.1f
#define BATTERY_SENSOR_TWO_BATTERY 0.7f

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created BatterySensor object
BatterySensor *new_battery_sensor(ADCSensor *_adc_sensor, uint8_t _rank);

// REQUIRES: battery_sensor is a BatterySensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value battery sensor data.
uint8_t get_battery_sensor_data(BatterySensor *battery_sensor);
