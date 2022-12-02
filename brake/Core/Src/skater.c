#include "skater.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _force_sensor is a ForceSensor object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Skater object
Skater *new_skater(ForceSensor *_force_sensor) {
	Skater *skater = (Skater*) malloc(sizeof(Skater));
	skater->force_sensor = _force_sensor;
	skater->ms_since_skater_detected = 0;
	return skater;
}

// REQUIRES: skater is a Skater object
// MODIFIES: nothing
// EFFECTS: Returns whether skater is gone or not
bool is_skater_gone(Skater *skater) {
	return skater->ms_since_skater_detected >= TIME_INDICATING_SKATER_ABSENCE_MS;
}

// REQUIRES: skater is a Skater object
// MODIFIES: ms_since_skater_detected
// EFFECTS: Updates the value of ms_since_skater_detected
// This function is expected to be called every 2 ms.
void refresh_skater_status(Skater *skater) {
	uint16_t raw_value = get_force_sensor_data(skater->force_sensor);
	bool is_skater_detected = raw_value < RAW_FORCE_SENSOR_VALUE_INDICATING_SKATER_PRESENCE;

	// If skater is detected, reset value to 0.
	// If skater is not detected, then keep incrementing ms_since_skater_detected
	// until it surpasses the expected maximum.
	// TODO - verify if 2 is the correct number to be adding.
	skater->ms_since_skater_detected = is_skater_detected ?
			0 : skater->ms_since_skater_detected > TIME_INDICATING_SKATER_ABSENCE_MS ?
					TIME_INDICATING_SKATER_ABSENCE_MS : skater->ms_since_skater_detected + 2;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
