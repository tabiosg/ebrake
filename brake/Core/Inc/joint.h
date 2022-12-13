#pragma once

#include "motor.h"
#include "pin_data.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BRAKING_STEPS 26000
#define FLOOR_BRAKING_STEPS_HARD 25000
#define FLOOR_BRAKING_STEPS_LIGHT 23800
#define RIGHT_BEFORE_BRAKING_STEPS 10000
#define MID_WAY_TO_BRAKING_STEPS 10000
#define ARBITRARY_ADD_ANGLE_FOR_LIMIT_SWITCH_STEPS 1500
#define CALIBRATION_POINT_REST_STEPS 0
#define MAX_REST_STEPS 0
#define IS_MOTOR_CORRECT_DIRECTION false

// A Joint composes of a motor, a device to measure angle,
// an angle, and a desired angle.
typedef struct {
	Motor *motor;
    PinData *rest_limit_switch_pin;
    PinData *brake_limit_switch_pin;
    int32_t current_angle_steps;
    int32_t desired_angle_steps;
    bool is_calibrated;
    bool is_rest_limit_switch_activated;
    bool is_brake_limit_switch_activated;
} Joint;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object,
// and _rest_limit_switch_pin and _brake_limit_switch_pin is a PinData object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, PinData* _rest_limit_switch_pin, PinData* _brake_limit_switch_pin);

// REQUIRES: joint is a Joint object
// MODIFIES: Nothing
// EFFECTS: Returns whether or not current joint angle is close enough to desired angle
bool is_joint_close_enough_to_target(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: Nothing
// EFFECTS: Moves the motor based on current angle and desired angle
// This function is expected to be called every 50 us
void move_joint_to_target(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: is_limit_switch_activated
// EFFECTS: Updates joint limit switch value
void refresh_joint_limit_switch(Joint *joint);

// REQUIRES: joint is a Joint object
// and target is an integer
// MODIFIES: desired_angle_steps
// EFFECTS: Changes the desired_angle_steps
void set_joint_target(Joint *joint, int32_t target);

// REQUIRES: joint is a Joint object
// MODIFIES: potentiometer_error
// EFFECTS: Updates the potentiometer_error so that
// current potentiometer readings are mapped to zero
void zero_joint(Joint *joint);
