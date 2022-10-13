#include "imu.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu_sensor(I2C_HandleTypeDef *hi2c) {
    IMU *imu = (IMU*) malloc(sizeof(IMU));
	imu->i2c = hi2c;
	return imu;
}

// REQUIRES: IMU is an object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
float get_imu_accel_in_axis(IMU *imu, axis axis) {
    return -1;
}

// REQUIRES: IMU is an object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu rotation in the axis in degrees/s
float get_imu_rotation_in_axis(IMU *imu, axis axis) {
    return -1;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
