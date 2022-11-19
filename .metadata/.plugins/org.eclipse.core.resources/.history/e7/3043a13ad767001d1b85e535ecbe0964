#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

// Used to store the data of a timer used to spawn interrupts
typedef struct {
	TIM_HandleTypeDef *timer;
} InterruptTimer;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _timer corresponds to timer
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created InterruptTimer object
InterruptTimer *new_interrupt_timer(TIM_HandleTypeDef *_timer);

// REQUIRES: interrupt_timer is an InterruptTimer object
// MODIFIES: nothing
// EFFECTS: Enables interrupts for the interrupt timer
void start_interrupt_timer(InterruptTimer *interrupt_timer);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
