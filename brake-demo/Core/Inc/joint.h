#pragma once

#include "motor.h"
#include "potentiometer.h"
#include "pin_data.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define AUTOMATIC_BRAKING_ANGLE_DEGREES 90.0f
#define AUTOMATIC_RELAX_ANGLE_DEGREES 0.0f
#define RATIO_OF_RAW_POTENT_DATA_PER_JOINT_DEGREE (4096.0f / 180.0f);
#define MOTOR_STEPS_PER_JOINT_DEGREE (3000.0f * 32.0f / 90.0f)
#define DESIRED_ANGLE_LAX_DEGREES 5.0f
#define IS_MOTOR_SAME_DIRECTION_AS_POTENTIOMETER false
#define USE_LIMIT_SWITCH false

// A Joint composes of a motor, a device to measure angle,
// an angle, and a desired angle.
typedef struct {
	Motor *motor;
    Potentiometer *potentiometer;
    PinData *limit_switch_pin;
    uint32_t potentiometer_value_at_rest_offset;
    float current_angle_degrees;
    float desired_angle_degrees;
    bool is_calibrated;
    bool is_limit_switch_activated;
} Joint;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object,
// _potentiometer is a Potentiometer object,
// and _limit_switch_pin is a PinData object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, Potentiometer* _potentiometer, PinData* _limit_switch_pin);

// REQUIRES: joint is a Joint object
// and target is a float
// MODIFIES: Nothing
// EFFECTS: Moves the motor based on current angle and desired angle
void move_joint_to_target(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: is_limit_switch_activated
// EFFECTS: Updates joint limit switch value
void refresh_joint_limit_switch(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: current_angle_degrees
// EFFECTS: Updates current_angle_degrees based on potentiometer
// reading and potentiometer offset
void refresh_joint_angle(Joint *joint);

// REQUIRES: joint is a Joint object
// and target is a float
// MODIFIES: desired_angle_degrees
// EFFECTS: Changes the desired_angle_degrees
void set_joint_target(Joint *joint, float target);

// REQUIRES: joint is a Joint object
// MODIFIES: potentiometer_error
// EFFECTS: Updates the potentiometer_error so that
// current potentiometer readings are mapped to zero
void zero_joint(Joint *joint);


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
