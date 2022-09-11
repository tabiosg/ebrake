#ifndef INC_HBRIDGE_H_
#define INC_HBRIDGE_H_

#include <stdint.h>

typedef struct {
	GPIO_TypeDef *fwd_port;
	GPIO_TypeDef *bwd_port;
	TIM_HandleTypeDef *timer;
	uint16_t fwd_pin;
	uint16_t bwd_pin;
} HBridge;

/** PUBLIC FUNCTIONS **/

// REQUIRES: Ports and pins correspond to H-Bridge.
// Timer is associated with PWM connected to H-Bridge
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created HBridge object
HBridge *new_hbridge(
	GPIO_TypeDef *_fwd_port,
	uint16_t _fwd_pin,
	GPIO_TypeDef *_bwd_port,
	uint16_t _bwd_pin,
	TIM_HandleTypeDef *timer
);

// REQUIRES: Speed to be between -1.0 and 1.0
// MODIFIES: hbridge digital outputs and timer PWM
// EFFECTS: The HBridge PWM and direction will change
void set_hbridge_speed(HBridge *hbridge, double speed_1);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

#endif /* INC_HBRIDGE_H_ */