#pragma once

#include "stm32g0xx_hal.h"
#include <stdint.h>

// Used to store the data of a PWM timer
typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel;
	uint32_t *ccr_channel;
} PWMTimerData;

// Used to store the data of a quadrature timer
typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel;
	uint32_t *cnt_channel;
} QuadTimerData;

