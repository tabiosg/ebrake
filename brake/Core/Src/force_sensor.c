#include "force_sensor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ForceSensor object
ForceSensor *new_force_sensor(ADC_HandleTypeDef *hadc) {
    ForceSensor *force_sensor = (ForceSensor*) malloc(sizeof(ForceSensor));
	force_sensor->adc = hadc;
	return force_sensor;
}

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of the force sensor in Newtons.
float get_force_sensor_input(ForceSensor *force_sensor) {
    return force_sensor->value * FORCE_SENSOR_NEWTONS_PER_COUNT_RATIO;
}

// REQUIRES: ForceSensor is a force_sensor object
// MODIFIES: value
// EFFECTS: Updates the stored value of value
float update_force_sensor_value(ForceSensor *force_sensor) {
    // TODO - read this https://community.st.com/s/article/using-timers-to-trigger-adc-conversions-periodically
    // This will use interrupts instead of polling for conversion. MUCH BETTER.
    HAL_ADC_Start(force_sensor->adc);
    HAL_ADC_PollForConversion(force_sensor->adc, HAL_MAX_DELAY);
    force_sensor->value = HAL_ADC_GetValue(force_sensor->adc);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
