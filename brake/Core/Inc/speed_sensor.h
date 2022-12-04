#pragma once

#include "imu.h"

#define LENGTH_OF_BOARD_M 0.762
#define IMU_ACCEL_INDICATING_SPIKE 15.0f
#define MPH_TO_MPS_RATIO 2.23694f

// This uses an IMU to measure speed
typedef struct {
	IMU *front_imu;
	IMU *back_imu;
	uint8_t speed;
	uint32_t ms_since_front_imu_spiked;
} SpeedSensor;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _front_imu and _back_imu are IMU objects
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created SpeedSensor object
SpeedSensor *new_speed_sensor(IMU *_front_imu, IMU *_back_imu);

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: speed
// EFFECTS: Returns the currently stored speed value of the speed sensor
// Assumes this function is called every 2ms.
void refresh_speed_sensor_logic(SpeedSensor *speed_sensor);

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored speed value of the speed sensor
uint8_t get_speed_sensor_data(SpeedSensor *speed_sensor);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
