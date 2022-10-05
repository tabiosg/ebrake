#pragma once

#include <stdint.h>
#include "stm32g0xx_hal.h"

// Used to store the data of a pin
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} PinData;
