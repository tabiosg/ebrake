#include "thermistor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Thermistor object
Thermistor *new_thermistor(ADCSensor *_adc_sensor, uint8_t _rank) {
	Thermistor *thermistor = (Thermistor*) malloc(sizeof(Thermistor));
	thermistor->adc_sensor = _adc_sensor;
	thermistor->rank = _rank;
	return thermistor;
}

// REQUIRES: thermistor is a Thermistor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value thermistor data.
uint8_t get_thermistor_data(Thermistor *thermistor) {
    uint32_t raw_value = get_adc_sensor_value(thermistor->adc_sensor, thermistor->rank);
    return raw_value;
}
