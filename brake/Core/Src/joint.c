#include "joint.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object,
// and _rest_limit_switch_pin and _brake_limit_switch_pin is a PinData object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, PinData* _rest_limit_switch_pin, PinData* _brake_limit_switch_pin) {
	Joint *joint = (Joint*) malloc(sizeof(Joint));
	joint->motor = _motor;
    joint->rest_limit_switch_pin = _rest_limit_switch_pin;
    joint->brake_limit_switch_pin = _brake_limit_switch_pin;
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
		step_motor_direction(joint->motor, is_difference_steps_positive);
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
// EFFECTS: Zeros the joint
void zero_joint(Joint *joint) {
	joint->current_angle_steps = 0;
}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
