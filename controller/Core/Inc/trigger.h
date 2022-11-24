#pragma once

#include "potentiometer.h"
#include <stdlib.h>
#include <stdbool.h>

// 96000 = 3000 steps * 32 pulses per step
#define MAX_STEPS 96000

//#define TRIGGER_STEPS_PER_POTENTIOMETER_COUNTS (MAX_STEPS / 64f)
#define TRIGGER_STEPS_PER_POTENTIOMETER_COUNTS 1500
#define TRIGGER_OFFSET_STEPS 0

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
