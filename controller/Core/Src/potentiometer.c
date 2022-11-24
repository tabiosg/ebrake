#include "potentiometer.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _adc_sensor is an ADCSensor object and _rank is the adc rank
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Potentiometer object
Potentiometer *new_potentiometer(ADCSensor *_adc_sensor, uint8_t _rank) {
    Potentiometer *potentiometer = (Potentiometer*) malloc(sizeof(Potentiometer));
    potentiometer->adc_sensor = _adc_sensor;
    potentiometer->rank = _rank;
    return potentiometer;
}

// REQUIRES: potentiometer is a Potentiometer object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of trigger.
// Expect an integer between 0 and 64.
uint16_t get_potentiometer_input(Potentiometer *potentiometer) {
    return get_adc_sensor_value(potentiometer->adc_sensor, potentiometer->rank);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
