#include "skater.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _force_sensor is a ForceSensor object and _thermistor is a Thermistor object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Skater object
Skater *new_skater(ForceSensor *_force_sensor, Thermistor *_thermistor) {
	Skater *skater = (Skater*) malloc(sizeof(Skater));
	skater->force_sensor = _force_sensor;
	skater->ms_since_skater_detected = 0;
	skater->raw_value_indicating_skater_presence = ROOM_TEMP_SKATER_PRESENCE_VALUE;
	skater->thermistor = _thermistor;
	skater->use_temperature_to_adjust_force_sensor = true;
	return skater;
}

// REQUIRES: skater is a Skater object
// MODIFIES: nothing
// EFFECTS: Returns whether skater has recently left board
bool has_skater_recently_left_board(Skater *skater) {
	return 1000 <= skater->ms_since_skater_detected && skater->ms_since_skater_detected <= TIME_TO_RELEASE_BRAKE_AFTER_SKATER_NOT_DETECTED;
}

// REQUIRES: skater is a Skater object
// MODIFIES: nothing
// EFFECTS: Returns whether skater is gone or not
bool is_skater_gone(Skater *skater) {
	return 1000 < skater->ms_since_skater_detected;
}

// REQUIRES: skater is a Skater object
// MODIFIES: ms_since_skater_detected
// EFFECTS: Updates the value of ms_since_skater_detected
// This function is expected to be called every 2 ms.
void refresh_skater_status(Skater *skater) {

	if (skater->use_temperature_to_adjust_force_sensor) {
		uint8_t raw_temp_value = get_thermistor_data(skater->thermistor);
		if (raw_temp_value > ROOM_TEMP_RAW_THERM_VALUE_INDICATING_SKATER) {
			// ROOM TEMP
			skater->raw_value_indicating_skater_presence = ROOM_TEMP_SKATER_PRESENCE_VALUE;
		}
		else {
	//	else if (raw_temp_value > COLD_TEMP_RAW_THERM_VALUE_INDICATING_SKATER) {
			// COLD
			skater->raw_value_indicating_skater_presence = COLD_TEMP_SKATER_PRESENCE_VALUE;
		}
	}

	uint16_t raw_force_value = get_force_sensor_data(skater->force_sensor);
	bool is_skater_detected = raw_force_value < skater->raw_value_indicating_skater_presence;

	// If skater is detected, reset value to 0.
	// If skater is not detected, then keep incrementing ms_since_skater_detected.
	if (is_skater_detected) {
		skater->ms_since_skater_detected = 0;
	}
	else {
		skater->ms_since_skater_detected += 2;
	}
}

// REQUIRES: skater is a Skater object
// MODIFIES: raw_value_indicating_skater_presence
// EFFECTS: Calibrates skater threshold value, assuming current value means no skater
void calibrate_skater_threshold(Skater *skater) {
	skater->use_temperature_to_adjust_force_sensor = false;
	uint16_t current_raw_force_value = get_force_sensor_data(skater->force_sensor);
	if (current_raw_force_value > 2) {
		skater->raw_value_indicating_skater_presence = skater->raw_value_indicating_skater_presence - 2;
	}
}
