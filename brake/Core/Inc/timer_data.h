#pragma once

#include "stm32g0xx_hal.h"
#include <stdint.h>

// Used to store the data of a PWM timer
typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel;
	uint32_t *ccr_channel;
} PWMTimer;

// Used to store the data of a quadrature timer
typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel;
	uint32_t *cnt_channel;
} QuadTimer;

// REQUIRES: _timer corresponds to timer,
// _channel corresponds to timer channel,
// and _ccr_channel is a pointer to the ccr channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created PWMTimer object
PWMTimer *new_pwm_timer(
	TIM_HandleTypeDef *_timer,
	uint32_t _channel,
	uint32_t *_ccr_channel
);

// REQUIRES: _timer corresponds to timer,
// _channel corresponds to timer channel,
// and _cnt_channel is a pointer to the cnt channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created QuadTimer object
QuadTimer *new_quad_timer(
	TIM_HandleTypeDef *_timer,
	uint32_t _channel,
	uint32_t *_cnt_channel
);


void start_pwm_timer(PWMTimer *pwm_timer);

void start_quad_timer(QuadTimer *quad_timer);
