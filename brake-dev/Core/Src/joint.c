#include "joint.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object and
// _potentiometer is a Potentiometer object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, Potentiometer* _potentiometer) {
	Joint *joint = (Joint*) malloc(sizeof(Joint));
	joint->motor = _motor;
    joint->potentiometer = _potentiometer;
    joint->potentiometer_value_at_rest_offset = 0;
    joint->current_angle_degrees = 0.0f;
    joint->desired_angle_degrees = 0.0f;
	joint->is_calibrated = false;
	return joint;
}

// REQUIRES: joint is a Joint object
// and target is a float
// MODIFIES: Nothing
// EFFECTS: Moves the motor based on current angle and desired angle
void move_joint_to_target(Joint *joint) {

	if (joint->current_angle_degrees > (joint->desired_angle_degrees + DESIRED_ANGLE_LAX_PER_SIDE_DEGREES)) {
		set_motor_speed(joint->motor, IS_MOTOR_SAME_DIRECTION_AS_POTENTIOMETER ? -1.0f : 1.0f);
	}
	else if (joint->current_angle_degrees < (joint->desired_angle_degrees - DESIRED_ANGLE_LAX_PER_SIDE_DEGREES)) {
		set_motor_speed(joint->motor, IS_MOTOR_SAME_DIRECTION_AS_POTENTIOMETER ? 1.0f : -1.0f);
	}
	else {
		set_motor_speed(joint->motor, 0.0f);
	}
}

// REQUIRES: joint is a Joint object
// MODIFIES: current_angle_degrees
// EFFECTS: Updates current_angle_degrees based on potentiometer
// reading and potentiometer offset
void refresh_joint_angle(Joint *joint) {
    uint32_t raw_data = get_potentiometer_input(joint->potentiometer);
	int32_t adjusted_data = raw_data - joint->potentiometer_value_at_rest_offset;
	joint->current_angle_degrees = adjusted_data / RATIO_OF_RAW_POTENT_DATA_PER_JOINT_DEGREE;
}

// REQUIRES: joint is a Joint object
// and target is a float
// MODIFIES: desired_angle_degrees
// EFFECTS: Changes the desired_angle_degrees
void set_joint_target(Joint *joint, float target) {
	joint->desired_angle_degrees = target;
}

// REQUIRES: joint is a Joint object
// MODIFIES: potentiometer_error
// EFFECTS: Updates the potentiometer_error so that
// current potentiometer readings are mapped to zero
void zero_joint(Joint *joint) {
	joint->potentiometer_value_at_rest_offset = get_potentiometer_input(joint->potentiometer);
}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
