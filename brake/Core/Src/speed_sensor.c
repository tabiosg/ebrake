#include "speed_sensor.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _front_imu and _back_imu are IMU objects
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created SpeedSensor object
SpeedSensor *new_speed_sensor(IMU *_front_imu, IMU *_back_imu) {
	SpeedSensor *speed_sensor = (SpeedSensor*) malloc(sizeof(SpeedSensor));
	speed_sensor->front_imu = _front_imu;
	speed_sensor->back_imu = _back_imu;
	speed_sensor->speed = 0;
	return speed_sensor;
}

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored speed value of the speed sensor
uint8_t get_speed_sensor_data(SpeedSensor *speed_sensor) {
	return -1;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
