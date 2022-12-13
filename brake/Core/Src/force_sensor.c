#include "force_sensor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ForceSensor object
ForceSensor *new_force_sensor(ADCSensor *_adc_sensor, uint8_t _rank) {
    ForceSensor *force_sensor = (ForceSensor*) malloc(sizeof(ForceSensor));
	force_sensor->adc_sensor = _adc_sensor;
    force_sensor->rank = _rank;
	return force_sensor;
}

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value force sensor voltage output.
uint16_t get_force_sensor_data(ForceSensor *force_sensor) {
    return get_adc_sensor_value(force_sensor->adc_sensor, force_sensor->rank);
}
