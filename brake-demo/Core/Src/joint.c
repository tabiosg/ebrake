#include "joint.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object,
// _potentiometer is a Potentiometer object,
// and _limit_switch_pin is a PinData object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, Potentiometer* _potentiometer, PinData* _limit_switch_pin) {
	Joint *joint = (Joint*) malloc(sizeof(Joint));
	joint->motor = _motor;
    joint->potentiometer = _potentiometer;
    joint->limit_switch_pin = _limit_switch_pin;
    joint->potentiometer_value_at_rest_offset = 0;
    joint->current_angle_degrees = 0.0f;
    joint->desired_angle_degrees = 0.0f;
	joint->is_calibrated = false;
	joint->is_limit_switch_activated = true;
	return joint;
}

// REQUIRES: joint is a Joint object
// and target is a float
// MODIFIES: Nothing
// EFFECTS: Moves the motor based on current angle and desired angle
void move_joint_to_target(Joint *joint) {
	float difference_degrees = joint->desired_angle_degrees - joint->current_angle_degrees;
	if (fabs(difference_degrees) > DESIRED_ANGLE_LAX_DEGREES) {
		bool direction = !((difference_degrees > 0) ^ IS_MOTOR_SAME_DIRECTION_AS_POTENTIOMETER);
		step_motor_direction(joint->motor, direction);
		float steps = difference_degrees > 0 ? 1 : -1;
		float changed_degrees = steps / MOTOR_STEPS_PER_JOINT_DEGREE;
		joint->current_angle_degrees += changed_degrees;
	}

	if (USE_LIMIT_SWITCH) {
		bool motor_thinks_is_at_rest = fabs(joint->current_angle_degrees - AUTOMATIC_RELAX_ANGLE_DEGREES) < DESIRED_ANGLE_LAX_DEGREES;
		if (motor_thinks_is_at_rest && !joint->is_limit_switch_activated) {
			// Increase its current angle by an arbitrary number in order to make it head in the direction of the desired.
			joint->current_angle_degrees += 10;
		}
	}
}

// REQUIRES: joint is a Joint object
// MODIFIES: is_limit_switch_activated
// EFFECTS: Updates joint limit switch value
void refresh_joint_limit_switch(Joint *joint) {
	if (USE_LIMIT_SWITCH) {
		bool raw_pin_value = get_pin_value(joint->limit_switch_pin);
		joint->is_limit_switch_activated = !raw_pin_value;
		if (joint->is_limit_switch_activated) {
			zero_joint(joint);
		}
	}
}

// REQUIRES: joint is a Joint object
// MODIFIES: current_angle_degrees
// EFFECTS: Updates current_angle_degrees based on potentiometer
// reading and potentiometer offset
void refresh_joint_angle(Joint *joint) {
	if (USE_LIMIT_SWITCH && joint->is_limit_switch_activated) {
		// TODO - this is technically redundant, but it does not hurt I think.
		zero_joint(joint);
	}
	else {
		uint32_t raw_data = get_potentiometer_input(joint->potentiometer);
		int32_t adjusted_data = raw_data - joint->potentiometer_value_at_rest_offset;
		joint->current_angle_degrees = adjusted_data / RATIO_OF_RAW_POTENT_DATA_PER_JOINT_DEGREE;
	}
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
	joint->current_angle_degrees = 0;
}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
