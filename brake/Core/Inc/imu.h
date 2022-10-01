#pragma once

typedef struct {
	I2C_HandleTypeDef *i2c;
} IMU;

typedef enum
{
	X_Axis, Y_Axis, Z_Axis
} axis;


/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu_sensor(I2C_HandleTypeDef *hi2c);

// REQUIRES: IMU is an object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
double get_imu_accel_in_axis(IMU *imu, axis axis);

// REQUIRES: IMU is an object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu rotation in the axis in degrees/s
double get_imu_rotation_in_axis(IMU *imu, axis axis);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
