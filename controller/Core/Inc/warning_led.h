#pragma once

#include "stm32g0xx_hal.h"
#include "pin_data.h"
#include "battery_buzzer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define WARNING_LED_TIME_MS 1000
#define WARNING_LED_PERIOD_MS 2000

#define WARNING_LED_SKATER_NOT_DETECTED_FELL_OFF_TIME_MS 500
#define WARNING_LED_SKATER_NOT_DETECTED_PERIOD_MS 1000

// This manages the battery led
typedef struct {
	PinData *warning_led_pin;
	uint32_t ms_since_period_cycle;
	uint8_t* battery_data;
	bool is_skater_detected_on_board;
} WarningLed;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _warning_led_pin is the warning LED pin,
// and _wireless is the wireless object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created WarningLed object
WarningLed *new_warning_led(PinData *_warning_led_pin, uint8_t* _battery_data);

// REQUIRES: warning_led is the warning LED
// MODIFIES: nothing
// EFFECTS: Updates the logic of the warning LED.
// It will blink for 1 second every 2 second if lost communication.
// It will stay on if the battery is low on battery.
// This function is expected to be called every 2 ms.
void update_warning_led_logic(WarningLed *warning_led, bool is_comms_lost);
