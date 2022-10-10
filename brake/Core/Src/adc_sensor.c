#include "adc_sensor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc and _total_ranks are the total ranks.
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ADCSensor object
ADCSensor *new_adc_sensor(ADC_HandleTypeDef *hadc, uint8_t _total_ranks) {
    ADCSensor *adc_sensor = (ADCSensor*) malloc(sizeof(ADCSensor));
    adc_sensor->adc = hadc;
    adc_sensor->total_ranks = _total_ranks;
    for (uint8_t i = 0; i < _total_ranks; ++i) {
        adc_sensor->values[i] = 0;
    }
    return adc_sensor;
}

// REQUIRES: adc_sensor is an ADCSensor object and rank is the index
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of trigger.
// Expect an integer between 0 and 4096.
uint32_t get_adc_sensor_value(ADCSensor *adc_sensor, uint8_t rank) {
    return adc_sensor->values[rank];
}

// REQUIRES: adc_sensor is an ADCSensor object
// MODIFIES: values
// EFFECTS: Updates the stored value of value.
void update_adc_sensor_values(ADCSensor *adc_sensor) {
    HAL_ADC_Start_DMA(adc_sensor->adc, adc_sensor->values, adc_sensor->total_ranks);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
