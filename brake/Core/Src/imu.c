#include "imu.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel and _addr is the address
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu_sensor(I2C_HandleTypeDef *hi2c, uint8_t _addr) {
    IMU *imu = (IMU*) malloc(sizeof(IMU));
	imu->i2c = hi2c;
	imu->addr = _addr;
	imu->accel_values[0] = 0.0f;
	imu->accel_values[1] = 0.0f;
	imu->accel_values[2] = IMU_Z_ACCEL_GRAVITY;
	return imu;
}

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Updates the imu acceleration in the axis in m/s^2
void refresh_imu_accel_in_axis(IMU *imu, axis axis) {
	// TODO;
	return;
}

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
float get_imu_accel_in_axis(IMU *imu, axis axis) {
    return imu->accel_values[axis];
}

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Returns if IMU z accel is equal to gravity
bool is_imu_z_accel_equal_to_gravity(IMU *imu) {
    return fabs(get_imu_accel_in_axis(imu, Z_Axis) - IMU_Z_ACCEL_GRAVITY) < IMU_ACCEL_NOISE;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
