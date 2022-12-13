#pragma once

#include "stm32g0xx_hal.h"
#include "pin_data.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO_BATTERY_DATA 0
#define CRITICALLY_LOW_BATTERY_DATA 1
#define LOW_BATTERY_DATA 2
#define MEDIUM_BATTERY_DATA 3
#define HIGH_BATTERY 4
#define FULLY_BATTERY 5

#define BATTERY_BUZZ_TIME_MS 1000
#define NO_BATTERY_PERIOD_MS 15000
#define CRITICALLY_LOW_BATTERY_BUZZ_PERIOD_MS 30000
#define LOW_BATTERY_BUZZ_PERIOD_MS 60000

// This manages the battery buzzer
typedef struct {
	PinData *buzzer_pin;
	uint16_t ms_since_period_cycle;
	uint8_t* battery_data;
} BatteryBuzzer;

/** PUBLIC FUNCTIONS **/

// REQUIRES: _buzzer_pin is the buzzer pin
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created BatteryBuzzer object
BatteryBuzzer *new_battery_buzzer(PinData *_buzzer_pin, uint8_t *_battery_data);

// REQUIRES: _buzzer_pin is the buzzer pin
// MODIFIES: nothing
// EFFECTS: Updates the logic of the battery buzzer.
// It will buzz for 1 second every 15 seconds if low.
// It will buzz for 1 second every 5 seconds if extremely low.
// This function is expected to be called every 2 ms.
void update_battery_buzzer_logic(BatteryBuzzer *battery_buzzer);

// REQUIRES: battery_buzzer is an object and data is the new battery data.
// Data should be 0 for no battery, 1 for critically low battery,
// 2 for low battery, and 3/4/5 for others values.
// MODIFIES: nothing
// EFFECTS: Updates the battery buzzer data
void change_battery_buzzer_data(BatteryBuzzer *battery_buzzer, uint8_t data);

// REQUIRES: battery_buzzer is an object and val is if it should be on or off.
// MODIFIES: nothing
// EFFECTS: Changes the output noise of the battery buzzer.
void change_battery_buzzer_noise_val(BatteryBuzzer *battery_buzzer, bool val);

// REQUIRES: battery_buzzer is an object and val is if it should be on or off.
// MODIFIES: nothing
// EFFECTS: Turns the battery led on or off.
void change_battery_led(BatteryBuzzer *battery_buzzer, bool val);
