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
// EFFECTS: Returns the currently desired steps being commanded
// by user based on trigger
int16_t get_trigger_input(Trigger *trigger) {
	uint32_t raw_counts = get_potentiometer_input(trigger->potentiometer);
	return 63 - raw_counts;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
