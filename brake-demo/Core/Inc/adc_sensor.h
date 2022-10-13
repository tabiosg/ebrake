#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	ADC_HandleTypeDef *adc;
	uint8_t total_ranks;
	uint16_t values[10];
} ADCSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc and _total_ranks are the total ranks.
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created ADCSensor object
ADCSensor *new_adc_sensor(ADC_HandleTypeDef *hadc, uint8_t _total_ranks);

// REQUIRES: adc_sensor is an ADCSensor object and rank is the index
// MODIFIES: nothing
// EFFECTS: Returns the currently stored value of trigger.
// Expect an integer between 0 and 4096.
uint16_t get_adc_sensor_value(ADCSensor *adc_sensor, uint8_t rank);

// REQUIRES: adc_sensor is an ADCSensor object
// MODIFIES: values
// EFFECTS: Updates the stored value of value.
void update_adc_sensor_values(ADCSensor *adc_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
