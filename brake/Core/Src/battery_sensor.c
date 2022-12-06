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

// REQUIRES: battery_sensor is a BatterySensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value battery sensor data.
uint8_t get_battery_sensor_data(BatterySensor *battery_sensor) {
    uint32_t raw_value = get_adc_sensor_value(battery_sensor->adc_sensor, battery_sensor->rank);
    float voltage = raw_value * 3.3f / 64.0;
    if (voltage > BATTERY_SENSOR_FIVE_BATTERY) {
    	return 5;
    }
    else if (voltage > BATTERY_SENSOR_THREE_BATTERY) {
//    	return 3;
    	return 2; // This is done temporarily to make noise for the controller. (It only makes noise at 2 or less).
    }
    else if (voltage > BATTERY_SENSOR_TWO_BATTERY) {
//    	return 2;
    	return 1; // This is done temporarily to make noise for the controller. (It only makes noise at 2 or less).
    }
    return 0;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
