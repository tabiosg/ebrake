#include "potentiometer.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Potentiometer object
Potentiometer *new_potentiometer(ADC_HandleTypeDef *hadc) {
    Potentiometer *potentiometer = (Potentiometer*) malloc(sizeof(Potentiometer));
    potentiometer->adc = hadc;
    potentiometer->value = 0;
    return potentiometer;
}

// REQUIRES: potentiometer is a Potentiometer object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of trigger.
// Expect an integer between 0 and 4096.
uint32_t get_potentiometer_input(Potentiometer *potentiometer) {
    return potentiometer->value;
}

// REQUIRES: potentiometer is a Potentiometer object
// MODIFIES: value
// EFFECTS: Updates the stored value of value.
void update_potentiometer_value(Potentiometer *potentiometer) {
    // TODO - read this https://community.st.com/s/article/using-timers-to-trigger-adc-conversions-periodically
    // This will use interrupts instead of polling for conversion. MUCH BETTER.
    HAL_ADC_Start(potentiometer->adc);
    HAL_ADC_PollForConversion(potentiometer->adc, HAL_MAX_DELAY);
    potentiometer->value = HAL_ADC_GetValue(potentiometer->adc);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
