#include "i2c_mux.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a new I2C mux
I2CMux *new_i2c_mux(I2C_HandleTypeDef *hi2c) {
	I2CMux *i2c_mux = (I2CMux*) malloc(sizeof(I2CMux));
	i2c_mux->i2c = hi2c;
	for (size_t i = 0; i < 8; ++i) {
		i2c_mux->channels_register_data[i] = 0b1 << i;
	}
	for (size_t i = 0; i < 10; ++i) {
		i2c_mux->buffer[i] = 0;
	}
	return i2c_mux;
}

// REQUIRES: i2c_mux is the mux and channel is an integer [0, 7]
// MODIFIES: nothing
// EFFECTS: Activates an i2c mux channel
void activate_i2c_mux_channel(I2CMux *i2c_mux, uint8_t channel) {
	i2c_mux->buffer[0] = I2C_MUX_SELECT_CMD;
	i2c_mux->buffer[1] = i2c_mux->channels_register_data[channel];
	HAL_I2C_Master_Transmit(
		i2c_mux->i2c,
		I2C_MUX_ADDRESS << 1,
		i2c_mux->buffer,
		2,
		5);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
