#include "pwm_timer_data.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _timer corresponds to timer,
// _channel corresponds to timer channel,
// and _ccr_channel is a pointer to the ccr channel
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created PWMTimer object
PWMTimer *new_pwm_timer(
	TIM_HandleTypeDef *_timer,
	uint32_t _channel,
	volatile uint32_t *_ccr_channel
) {
    PWMTimer *pwm_timer = (PWMTimer*) malloc(sizeof(PWMTimer));
	pwm_timer->timer = _timer;
    pwm_timer->channel = _channel;
    pwm_timer->ccr_channel = _ccr_channel;
	return pwm_timer;
}

// REQUIRES: pwm_timer is a PWMTimer object
// MODIFIES: nothing
// EFFECTS: Enables PWM for the timer
void start_pwm_timer(PWMTimer *pwm_timer) {
	HAL_TIM_PWM_Start(pwm_timer->timer, pwm_timer ->channel);
}

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/
