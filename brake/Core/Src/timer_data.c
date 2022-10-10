#include "timer_data.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _timer corresponds to timer,
// _channel corresponds to timer channel,
// and _ccr_channel is a pointer to the ccr channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created PWMTimer object
PWMTimer *new_pwm_timer(
	TIM_HandleTypeDef *_timer,
	uint32_t _channel,
	uint32_t *_ccr_channel
) {
    PWMTimer *pwm_timer = (PWMTimer*) malloc(sizeof(PWMTimer));
	pwm_timer->timer = _timer;
    pwm_timer->channel = _channel;
    pwm_timer->ccr_channel = _ccr_channel;
	return pwm_timer;
}

void start_pwm_timer(PWMTimer *pwm_timer) {
    return;
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
