#pragma once

#include "motor.h"
#include "potentiometer.h"
#include "pin_data.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// 35968 = 1124 steps * 32 pulses per step
#define AUTOMATIC_BRAKING_ANGLE_STEPS 35968


//#define RATIO_OF_RAW_POTENT_DATA_PER_JOINT_STEP (64.0f / (AUTOMATIC_BRAKING_ANGLE_STEPS))
#define RATIO_OF_RAW_POTENT_DATA_PER_JOINT_STEP 0.00177936f;

//#define RATIO_OF_JOINT_STEP_PER_TRIGGER_INPUT (AUTOMATIC_BRAKING_ANGLE_STEPS / 64.0f)
#define RATIO_OF_JOINT_STEP_PER_TRIGGER_INPUT 562

#define AUTOMATIC_RELAX_ANGLE_STEPS 0

// The best resolution we have with 6 bit is 562 steps. 562 * 3 = 1686
#define DESIRED_ANGLE_LAX_STEPS 1686

//#define AUTOMATIC_BRAKING_ANGLE_STEPS_LOW (AUTOMATIC_BRAKING_ANGLE_STEPS - DESIRED_ANGLE_LAX_STEPS)
//#define AUTOMATIC_BRAKING_ANGLE_STEPS_HIGH (AUTOMATIC_BRAKING_ANGLE_STEPS + DESIRED_ANGLE_LAX_STEPS)
#define AUTOMATIC_BRAKING_ANGLE_STEPS_LOW 34282
#define AUTOMATIC_BRAKING_ANGLE_STEPS_HIGH 37654

// This is what we use for addition. DESIRED_ANGLE_LAX_STEPS * 2
#define ARBITRARY_ADD_ANGLE_FOR_LIMIT_SWITCH_STEPS 3372

#define IS_MOTOR_SAME_DIRECTION_AS_POTENTIOMETER false

// A Joint composes of a motor, a device to measure angle,
// an angle, and a desired angle.
typedef struct {
	Motor *motor;
    Potentiometer *potentiometer;
    PinData *rest_limit_switch_pin;
    PinData *brake_limit_switch_pin;
    uint32_t potentiometer_value_at_rest_offset;
    int32_t current_angle_steps;
    int32_t desired_angle_steps;
    bool is_calibrated;
    bool is_rest_limit_switch_activated;
    bool is_brake_limit_switch_activated;
} Joint;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _motor is a Motor object,
// _potentiometer is a Potentiometer object,
// and _rest_limit_switch_pin and _brake_limit_switch_pin is a PinData object
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Joint object
Joint *new_joint(Motor* _motor, Potentiometer* _potentiometer, PinData* _rest_limit_switch_pin, PinData* _brake_limit_switch_pin);

// REQUIRES: joint is a Joint object
// MODIFIES: Nothing
// EFFECTS: Returns whether or not current joint angle is close enough to desired angle
bool is_joint_close_enough_to_target(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: Nothing
// EFFECTS: Moves the motor based on current angle and desired angle
void move_joint_to_target(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: is_limit_switch_activated
// EFFECTS: Updates joint limit switch value
void refresh_joint_limit_switch(Joint *joint);

// REQUIRES: joint is a Joint object
// MODIFIES: current_angle_steps
// EFFECTS: Updates current_angle_steps based on potentiometer
// reading and potentiometer offset
void refresh_joint_angle(Joint *joint);

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


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
