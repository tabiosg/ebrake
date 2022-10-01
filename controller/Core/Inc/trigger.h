#pragma once

typedef struct {
	ADC_HandleTypeDef *adc;
} Trigger;

/** PUBLIC FUNCTIONS **/

// REQUIRES: hadc is the adc channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Trigger object
Trigger *new_trigger(ADC_HandleTypeDef *hadc);

// REQUIRES: Trigger is an object
// MODIFIES: nothing
// EFFECTS: Returns a value between 0.0 to 1.0 representing
// how far the trigger is being pushed where 0.0 is not pushed.
double get_trigger_input(Trigger *trigger);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
