#include "imu.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: hi2c is the i2c channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created IMU object
IMU *new_imu(I2C_HandleTypeDef *hi2c, bool _is_511) {
	IMU *imu = (IMU*) malloc(sizeof(IMU));
	imu->i2c = hi2c;
	imu->is_511 = _is_511;
	if (_is_511) {
		imu->addr = ADDRESS_511_ACCEL;
	}
	else {
		imu->addr = ADDRESS_521_ACCEL_ADDR_HIGH;
	}
	imu->accel_values[0] = 0.0;
	imu->accel_values[1] = 0.0;
	imu->accel_values[2] = IMU_Z_ACCEL_GRAVITY * 2048.0;
	for (size_t i = 0; i < 10; ++i) {
		imu->buffer[i] = 0;
	}
	return imu;
}

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Initializes the IMU
void init_imu(IMU* imu) {
	if (imu->is_511) {
		write_imu_register(imu, 0x20, 0x47); //set control reg 1a
		write_imu_register(imu, 0x23, 0x48); // set control reg 4a
	}
	else {
		write_imu_register(imu, 0x6B, 0x00);  // wakeup
	}
}

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Updates the imu acceleration in the axis in m/s^2
void refresh_imu_accel_in_axis(IMU *imu, axis axis) {
	if (imu->is_511) {
		if (axis == X_Axis) {
			uint8_t msb = read_imu_register(imu, 0x28);
			uint8_t lsb = read_imu_register(imu, 0x29);
			imu->accel_values[X_Axis] = (msb << 8) | lsb;
		}
		else if (axis == Y_Axis) {
			uint8_t msb = read_imu_register(imu, 0x2A);
			uint8_t lsb = read_imu_register(imu, 0x2B);
			imu->accel_values[Y_Axis] = (msb << 8) | lsb;
		}
		else if (axis == Z_Axis) {
			uint8_t msb = read_imu_register(imu, 0x2C);
			uint8_t lsb = read_imu_register(imu, 0x2D);
			imu->accel_values[Z_Axis] = (msb << 8) | lsb;
		}
	}
	else {
		if (axis == X_Axis) {
			uint8_t msb = read_imu_register(imu, 0x3B);
			uint8_t lsb = read_imu_register(imu, 0x3C);
			imu->accel_values[X_Axis] = (msb << 8) | lsb;
		}
		else if (axis == Y_Axis) {
			uint8_t msb = read_imu_register(imu, 0x3D);
			uint8_t lsb = read_imu_register(imu, 0x3E);
			imu->accel_values[Y_Axis] = (msb << 8) | lsb;
		}
		else if (axis == Z_Axis) {
			uint8_t msb = read_imu_register(imu, 0x3F);
			uint8_t lsb = read_imu_register(imu, 0x40);
			imu->accel_values[Z_Axis] = (msb << 8) | lsb;
		}
	}
}

// REQUIRES: IMU is an IMU object and axis is an axis
// MODIFIES: nothing
// EFFECTS: Returns the imu acceleration in the axis in m/s^2
float get_imu_accel_in_axis(IMU *imu, axis axis) {
	return ((int16_t) imu->accel_values[axis]) / 2048.0f;
}

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Returns if IMU z accel is equal to gravity
bool is_imu_z_accel_equal_to_gravity(IMU *imu) {
	float z_val = get_imu_accel_in_axis(imu, Z_Axis);
	float diff = fabs(z_val - IMU_Z_ACCEL_GRAVITY);
    return diff < IMU_ACCEL_NOISE;
}

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Writes data to a particular register
void write_imu_register(IMU* imu, uint8_t reg, uint8_t data) {
	imu->buffer[0] = reg;
	imu->buffer[1] = data;
	HAL_I2C_Master_Transmit(
		imu->i2c,
		imu->addr << 1,
		imu->buffer,
		2,
		5);
//	HAL_Delay(10);
}

// REQUIRES: IMU is an IMU object
// MODIFIES: nothing
// EFFECTS: Reads IMU from a register
uint8_t read_imu_register(IMU* imu, uint8_t reg) {
	imu->buffer[0] = reg;
	HAL_I2C_Master_Transmit(
		imu->i2c,
		imu->addr << 1,
		imu->buffer,
		1,
		50);
	HAL_I2C_Master_Receive(
		imu->i2c,
		(imu->addr << 1) | 1,
		imu->buffer,
		1,
		5);
//	HAL_Delay(10);
	return imu->buffer[0];
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
