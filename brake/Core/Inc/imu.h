#pragma once

#include "stm32g0xx_hal.h"
#include <stdlib.h>

// TODO - find actual address
#define ADDRESS_BOTH_GROUND 0x00
#define ADDRESS_BOTH_HIGH 0x00

typedef struct {
	I2C_HandleTypeDef *i2c;
	uint8_t addr;
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

// REQUIRES: IMU is an object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
float get_imu_accel_in_axis(IMU *imu, axis axis);

// REQUIRES: IMU is an object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu rotation in the axis in degrees/s
float get_imu_rotation_in_axis(IMU *imu, axis axis);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
