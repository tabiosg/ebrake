#pragma once

#include "force_sensor.h"
#include "thermistor.h"
#include <stdlib.h>
#include <stdbool.h>

#define ROOM_TEMP_SKATER_PRESENCE_VALUE 43
#define ROOM_TEMP_RAW_THERM_VALUE_INDICATING_SKATER 30

#define COLD_TEMP_SKATER_PRESENCE_VALUE 41
#define COLD_TEMP_RAW_THERM_VALUE_INDICATING_SKATER 0

#define COLDEST_TEMP_RAW_THERM_VALUE_INDICATING_SKATER 0

#define TIME_INDICATING_SKATER_ABSENCE_MS 250
#define TIME_TO_RELEASE_BRAKE_AFTER_SKATER_NOT_DETECTED 4000

// A Skater keeps track of the state of
// the skater on the board
typedef struct {
	ForceSensor *force_sensor;
    uint32_t ms_since_skater_detected;
    uint16_t raw_value_indicating_skater_presence;
    Thermistor *thermistor;
} Skater;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _force_sensor is a ForceSensor object and _thermistor is a Thermistor object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Skater object
Skater *new_skater(ForceSensor *_force_sensor, Thermistor *_thermistor);

// REQUIRES: skater is a Skater object
// MODIFIES: nothing
// EFFECTS: Returns whether skater has recently left board
bool has_skater_recently_left_board(Skater *skater);

// REQUIRES: skater is a Skater object
// MODIFIES: nothing
// EFFECTS: Returns whether skater is gone or not
bool is_skater_gone(Skater *skater);

// REQUIRES: skater is a Skater object
// MODIFIES: ms_since_skater_detected
// EFFECTS: Updates the value of ms_since_skater_detected
void refresh_skater_status(Skater *skater);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
