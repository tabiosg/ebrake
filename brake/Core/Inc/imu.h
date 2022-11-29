#pragma once

#include "stm32g0xx_hal.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO - find actual address
#define ADDRESS_BOTH_GROUND 0x00
#define ADDRESS_BOTH_HIGH 0x00

#define IMU_ACCEL_NOISE 1.0f
#define IMU_Z_ACCEL_GRAVITY -9.81f

typedef struct {
	I2C_HandleTypeDef *i2c;
	uint8_t addr;
	float accel_values[3];
} IMU;

typedef enum
{
	X_Axis, Y_Axis, Z_Axis
} axis;


/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel and _addr is the address
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu_sensor(I2C_HandleTypeDef *hi2c, uint8_t _addr);

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Updates the imu acceleration in the axis in m/s^2
void refresh_imu_accel_in_axis(IMU *imu, axis axis);

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
float get_imu_accel_in_axis(IMU *imu, axis axis);

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Returns if IMU z accel is equal to gravity
bool is_imu_z_accel_equal_to_gravity(IMU *imu);


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
