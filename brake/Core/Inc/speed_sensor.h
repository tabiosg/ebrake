#pragma once

#include "imu.h"

#define LENGTH_OF_BOARD_M 0.762

// This uses an IMU to measure speed
typedef struct {
	IMU *front_imu;
	IMU *back_imu;
	uint8_t speed;
} SpeedSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _front_imu and _back_imu are IMU objects
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created SpeedSensor object
SpeedSensor *new_speed_sensor(IMU *_front_imu, IMU *_back_imu);

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: speed
// EFFECTS: Returns the currently stored speed value of the speed sensor
// Assumes this function is called every 200ms.
void refresh_speed_sensor_logic(SpeedSensor *speed_sensor);

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored speed value of the speed sensor
uint8_t get_speed_sensor_data(SpeedSensor *speed_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
