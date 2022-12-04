#pragma once

#include "stm32g0xx_hal.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ADDRESS_511_ACCEL 0x19
#define ADDRESS_521_ACCEL_ADDR_HIGH 0x69

#define IMU_ACCEL_NOISE 1.0f
#define IMU_Z_ACCEL_GRAVITY -9.81f

// This link is useful for the 511
// https://blog.robertelder.org/gy-511-lsm303dlhc/
// This link is useful for the 521
// https://mschoeffler.com/2017/10/05/tutorial-how-to-use-the-gy-521-module-mpu-6050-breakout-board-with-the-arduino-uno/
typedef struct {
	I2C_HandleTypeDef *i2c;
	uint8_t addr;
	int16_t accel_values[3];
	uint8_t buffer[10];
	bool is_511;
} IMU;

typedef enum
{
	X_Axis, Y_Axis, Z_Axis
} axis;


/** PUBLIC FUNCTIONS **/
#include "imu.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu(I2C_HandleTypeDef *hi2c, bool _is_511);

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
float get_imu_accel_in_axis(IMU *imu, axis axis);

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
