#include "interrupt_timer.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: _timer corresponds to timer
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created InterruptTimer object
InterruptTimer *new_interrupt_timer(TIM_HandleTypeDef *_timer) {
	InterruptTimer *interrupt_timer = (InterruptTimer*) malloc(sizeof(InterruptTimer));
	interrupt_timer->timer = _timer;
	return interrupt_timer;
}

// REQUIRES: interrupt_timer is an InterruptTimer object
// MODIFIES: nothing
// EFFECTS: Enables interrupts for the interrupt timer
void start_interrupt_timer(InterruptTimer *interrupt_timer) {
	HAL_TIM_Base_Start_IT(interrupt_timer->timer);
}
