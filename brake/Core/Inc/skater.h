#pragma once

#include "force_sensor.h"
#include <stdlib.h>
#include <stdbool.h>

#define RAW_FORCE_SENSOR_VALUE_INDICATING_SKATER_PRESENCE 43
#define TIME_INDICATING_SKATER_ABSENCE_MS 250
#define TIME_TO_RELEASE_BRAKE_AFTER_SKATER_NOT_DETECTED 4000

// A Skater keeps track of the state of
// the skater on the board
typedef struct {
	ForceSensor *force_sensor;
    uint32_t ms_since_skater_detected;
} Skater;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _force_sensor is a ForceSensor object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Skater object
Skater *new_skater(ForceSensor *_force_sensor);

// REQUIRES: skater is a Skater object
// MODIFIES: nothing
// EFFECTS: Returns whether skater has recently left board
bool has_skater_recently_left_board(Skater *skater);

// REQUIRES: skater is a Skater object
// MODIFIES: ms_since_skater_detected
// EFFECTS: Updates the value of ms_since_skater_detected
void refresh_skater_status(Skater *skater);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
