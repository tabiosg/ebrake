#pragma once

#include "stm32g0xx_hal.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define I2C_MUX_ADDRESS 0x70
#define I2C_MUX_SELECT_CMD 0xCC

// TCA9548A
typedef struct {
	I2C_HandleTypeDef *i2c;
	int channels_register_data[8];
	uint8_t buffer[10];
} I2CMux;

/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a new i2c mux
I2CMux *new_i2c_mux(I2C_HandleTypeDef *hi2c);

// REQUIRES: i2c_mux is the mux and channel is an integer [0, 7]
// MODIFIES: nothing
// EFFECTS: Activates an i2c mux channel
void activate_i2c_mux_channel(I2CMux *i2c_mux, uint8_t channel);
