#include "battery_sensor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created BatterySensor object
BatterySensor *new_battery_sensor(ADCSensor *_adc_sensor, uint8_t _rank) {
	BatterySensor *battery_sensor = (BatterySensor*) malloc(sizeof(BatterySensor));
	battery_sensor->adc_sensor = _adc_sensor;
	battery_sensor->rank = _rank;
	return battery_sensor;
}

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value battery sensor data.
float get_battery_sensor_data(BatterySensor *battery_sensor) {
    uint32_t raw_value = get_adc_sensor_value(battery_sensor->adc_sensor, battery_sensor->rank);
    float voltage = raw_value * 3.3f / 64.0;
    if (voltage > BATTERY_SENSOR_FIVE_BATTERY) {
    	return 5;
    }
    else if (voltage > BATTERY_SENSOR_THREE_BATTERY) {
    	return 3;
    }
    else if (voltage > BATTERY_SENSOR_ONE_BATTERY) {
    	return 1;
    }
    return 0;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
