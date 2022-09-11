#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>

typedef struct {
	GPIO_TypeDef port;
	uint16_t pin;
} Buzzer;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _port and _pin correspond to MOSFET connected
// to the buzzer
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created Buzzer object
Buzzer *new_buzzer(
    GPIO_TypeDef *_port,
	uint16_t _pin
);

// REQUIRES: Buzzer is an object
// MODIFIES: sets digital output to 1
// EFFECTS: turns buzzer on
void set_buzzer_on(Buzzer *buzzer);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

#endif /* INC_BUZZER_H_ */