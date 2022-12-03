#pragma once

#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


// TODO - find actual address
#define ADDRESS_BOTH_GROUND 0x19
#define ADDRESS_BOTH_HIGH 0x19

#define IMU_ACCEL_NOISE 1.0f
#define IMU_Z_ACCEL_GRAVITY -9.81f

// This link is useful
// https://blog.robertelder.org/gy-511-lsm303dlhc/
typedef struct {
	I2C_HandleTypeDef *i2c;
	uint8_t addr;
	int16_t accel_values[3];
	uint8_t buffer[10];
} IMU;

typedef enum
{
	X_Axis, Y_Axis, Z_Axis
} axis;


/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel and _addr is the address
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu(I2C_HandleTypeDef *hi2c, uint8_t _addr);

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Initializes the IMU
void init_imu(IMU* imu);

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Updates the imu acceleration in the axis in m/s^2
void refresh_imu_accel_in_axis(IMU *imu, axis axis);

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
int16_t get_imu_accel_in_axis(IMU *imu, axis axis);

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Returns if IMU z accel is equal to gravity
bool is_imu_z_accel_equal_to_gravity(IMU *imu);

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Writes data to a particular register
void write_imu_register(IMU* imu, uint8_t reg, uint8_t data);

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Reads IMU from a register
uint8_t read_imu_register(IMU* imu, uint8_t reg);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
