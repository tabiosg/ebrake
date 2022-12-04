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
	float front_imu_accel = get_imu_accel_in_axis(speed_sensor->front_imu, Z_Axis);
	float back_imu_accel = get_imu_accel_in_axis(speed_sensor->back_imu, Z_Axis);
	// Start with the back imu, so we don't get a speed of 0.
	if (fabs(front_imu_accel) > IMU_ACCEL_INDICATING_SPIKE) {
		speed_sensor->ms_since_front_imu_spiked = 0;
	}
	else if (fabs(back_imu_accel) > IMU_ACCEL_INDICATING_SPIKE) {
		float meters_per_second = LENGTH_OF_BOARD_M * 1000.0f / speed_sensor->ms_since_front_imu_spiked;
		float mph = meters_per_second * MPH_TO_MPS_RATIO;
		if (mph > 99.0f) {
			mph = 99.0f;
		}
		speed_sensor->speed = mph;
	}
	speed_sensor->ms_since_front_imu_spiked += 2;
}

// REQUIRES: SpeedSensor is a speed_sensor object
// MODIFIES: nothing
// EFFECTS: Returns the currently stored speed value of the speed sensor
uint8_t get_speed_sensor_data(SpeedSensor *speed_sensor) {
	return -1;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
