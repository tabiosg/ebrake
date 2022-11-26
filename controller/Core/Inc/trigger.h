#pragma once

#include "potentiometer.h"
#include <stdlib.h>
#include <stdbool.h>

// A Skater keeps track of the state of
// the skater on the board
typedef struct {
	Potentiometer *potentiometer;
} Trigger;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _potentiometer is a Potentiometer object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Trigger object
Trigger *new_trigger(Potentiometer *_potentiometer);

// REQUIRES: trigger is a Trigger object
// MODIFIES: nothing
// EFFECTS: Returns the currently desired steps being commanded
// by user based on trigger
int16_t get_trigger_input(Trigger *trigger);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
