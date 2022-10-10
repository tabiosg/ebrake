#pragma once

#include "pin_data.h"

// A quadrature encoder is being used
typedef struct {
	QuadTimer a;
	QuadTimer b;
	int32_t current_value;
	uint16_t value_prev;
	uint16_t value_now;

} Quadrature;

/** PUBLIC FUNCTIONS **/

// REQUIRES: timer_a and timer_b have the timer data of the quadrature lines
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Quadrature object
Quadrature *new_quadrature_encoder(QuadTimer timer_a, QuadTimer timer_b);

// REQUIRES: Quadrature is an object
// MODIFIES: nothing
// EFFECTS: Returns updated angle data in revolutions of the motor.
double get_quadrature_data(Quadrature *quadrature);

// REQUIRES: Quadrature is an object
// MODIFIES: quadrature->current-value
// EFFECTS: Modifies current value
void zero_quadrature(Quadrature *quadrature);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
