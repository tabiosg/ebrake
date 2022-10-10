#pragma once

#include "trigger.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _potentiometer is a Potentiometer object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Trigger object
Trigger *new_trigger(Potentiometer *_potentiometer) {
	Trigger *trigger = (Trigger*) malloc(sizeof(Trigger));
	trigger->potentiometer = _potentiometer;
	return trigger;
}

// REQUIRES: trigger is a Trigger object
// MODIFIES: nothing
// EFFECTS: Returns the currently desired angle being commanded
// by user based on trigger
float get_trigger_input(Trigger *trigger) {
	uint32_t raw_counts = get_potentiometer_input(trigger->potentiometer);
	float degrees = raw_counts * TRIGGER_DEGREES_PER_POTENTIOMETER_COUNTS;
	float degrees_corrected = degrees - TRIGGER_OFFSET_DEGREES;
	return degrees_corrected;
}

// REQUIRES: trigger is a Trigger object
// MODIFIES: value
// EFFECTS: Updates the desired angle being commanded
// by user based on trigger
void update_trigger_value(Trigger *trigger) {
	update_potentiometer_value(trigger->potentiometer);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
