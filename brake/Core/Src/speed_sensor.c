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
	speed_sensor->ms_since_front_imu_spiked = 0xFFFFFFFF;
	return speed_sensor;
}

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: speed
// EFFECTS: Returns the currently stored speed value of the speed sensor
// Assumes this function is called every 2ms.
void refresh_speed_sensor_logic(SpeedSensor *speed_sensor) {
	speed_sensor->ms_since_front_imu_spiked += 2;
	if (speed_sensor->ms_since_front_imu_spiked > SPEED_SENSOR_TOO_LONG_SO_SET_SPEED_TO_0) {
		speed_sensor->speed = 0;
	}
}

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: speed
// EFFECTS: Updates the speed logic depending on if the front imu or back imu triggered
// this interrupt. This function should ONLY be called if an interrupt is triggered.
void trigger_speed_sensor_interrupt(SpeedSensor* speed_sensor, bool is_front) {
	if (is_front) {
		speed_sensor->ms_since_front_imu_spiked = 0;
	}
	else {
		float meters_per_second = LENGTH_OF_BOARD_M * 1000.0f / speed_sensor->ms_since_front_imu_spiked;
		float mph = meters_per_second * MPH_TO_MPS_RATIO;
		if (mph > 15.0f) {
			return;
		}
		speed_sensor->speed = mph;
	}
}

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored speed value of the speed sensor
uint8_t get_speed_sensor_data(SpeedSensor *speed_sensor) {
	return speed_sensor->speed;
}
