#include "joint.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object,
// _potentiometer is a Potentiometer object,
// and _rest_limit_switch_pin and _brake_limit_switch_pin is a PinData object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, Potentiometer* _potentiometer, PinData* _rest_limit_switch_pin, PinData* _brake_limit_switch_pin) {
	Joint *joint = (Joint*) malloc(sizeof(Joint));
	joint->motor = _motor;
    joint->potentiometer = _potentiometer;
    joint->rest_limit_switch_pin = _rest_limit_switch_pin;
    joint->brake_limit_switch_pin = _brake_limit_switch_pin;
    joint->potentiometer_value_at_rest_offset = 0;
    joint->current_angle_steps = CALIBRATION_POINT_REST_STEPS;
    joint->desired_angle_steps = CALIBRATION_POINT_REST_STEPS;
	joint->is_calibrated = false;
	joint->is_rest_limit_switch_activated = true;
	joint->is_brake_limit_switch_activated = false;
	return joint;
}

// REQUIRES: joint is a Joint object
// MODIFIES: Nothing
// EFFECTS: Returns whether or not current joint angle is close enough to desired angle
bool is_joint_close_enough_to_target(Joint *joint) {
	return joint->desired_angle_steps == joint->current_angle_steps;
}

// REQUIRES: joint is a Joint object
// MODIFIES: Nothing
// EFFECTS: Moves the motor based on current steps and desired steps
void move_joint_to_target(Joint *joint) {
	if (!is_joint_close_enough_to_target(joint)) {
		bool is_difference_steps_positive = joint->desired_angle_steps > joint->current_angle_steps;
		bool direction = !((is_difference_steps_positive) ^ IS_MOTOR_SAME_DIRECTION_AS_POTENTIOMETER);
		step_motor_direction(joint->motor, direction);
		int8_t steps = is_difference_steps_positive ? 1 : -1;
		joint->current_angle_steps += steps;
	}
}

// REQUIRES: joint is a Joint object
// MODIFIES: is_rest_limit_switch_activated and is_brake_limit_switch_activated
// EFFECTS: Updates joint limit switch value
void refresh_joint_limit_switch(Joint *joint) {
	bool raw_rest_pin_value = get_pin_value(joint->rest_limit_switch_pin);
	joint->is_rest_limit_switch_activated = raw_rest_pin_value;
	if (joint->is_rest_limit_switch_activated) {
		joint->is_calibrated = true;
		zero_joint(joint);
	}
	else {
		bool raw_brake_pin_value = get_pin_value(joint->brake_limit_switch_pin);
		joint->is_brake_limit_switch_activated = raw_brake_pin_value;
		if (joint->is_brake_limit_switch_activated) {
			// TODO - currently does not support potentiometer offset
			joint->current_angle_steps = MAX_BRAKING_STEPS;
		}
	}

}

// REQUIRES: joint is a Joint object
// MODIFIES: current_angle_steps
// EFFECTS: Updates current_angle_steps based on potentiometer
// reading and potentiometer offset
void refresh_joint_angle_with_potentiometer(Joint *joint) {
	// TODO - We do not use a potentiometer for our project so right now, it does nothing.
//	if (joint->is_rest_limit_switch_activated) {
//		zero_joint(joint);
//	}
//	else {
//		uint32_t raw_data = get_potentiometer_input(joint->potentiometer);
//		int32_t adjusted_data = raw_data - joint->potentiometer_value_at_rest_offset;
//		joint->current_angle_steps = adjusted_data / RATIO_OF_RAW_POTENT_DATA_PER_JOINT_STEP;
//	}
}

// REQUIRES: joint is a Joint object
// and target is an integer
// MODIFIES: desired_angle_steps
// EFFECTS: Changes the desired_angle_steps
void set_joint_target(Joint *joint, int32_t target) {
	if (joint->is_calibrated) {
		joint->desired_angle_steps = target;
	}
	else {
		joint->desired_angle_steps = CALIBRATION_POINT_REST_STEPS;
	}
}

// REQUIRES: joint is a Joint object
// MODIFIES: potentiometer_error
// EFFECTS: Updates the potentiometer_error so that
// current potentiometer readings are mapped to zero
void zero_joint(Joint *joint) {
	joint->potentiometer_value_at_rest_offset = get_potentiometer_input(joint->potentiometer);
	joint->current_angle_steps = 0;
}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
