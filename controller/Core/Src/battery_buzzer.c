#include "battery_buzzer.h"

// REQUIRES: _buzzer_pin is the buzzer pin
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created BatteryBuzzer object
BatteryBuzzer *new_battery_buzzer(PinData *_buzzer_pin, uint8_t *_battery_data) {
	BatteryBuzzer *battery_buzzer = (BatteryBuzzer*) malloc(sizeof(BatteryBuzzer));
	battery_buzzer->buzzer_pin = _buzzer_pin;
	battery_buzzer->ms_since_period_cycle = 0;
	battery_buzzer->battery_data = _battery_data;
	return battery_buzzer;
}

// REQUIRES: _buzzer_pin is the buzzer pin
// MODIFIES: nothing
// EFFECTS: Updates the logic of the battery buzzer.
// It will buzz for 1 second every 3 seconds if no battery.
// It will buzz for 1 second every 5 seconds if extremely low.
// It will buzz for 1 second every 15 seconds if low.
// This function is expected to be called every 2 ms.
void update_battery_buzzer_logic(BatteryBuzzer *battery_buzzer) {
	switch (*battery_buzzer->battery_data) {
	case NO_BATTERY_DATA:
		if (battery_buzzer->ms_since_period_cycle == 0) {
			change_battery_buzzer_noise_val(battery_buzzer, true);
		}
		else if (battery_buzzer->ms_since_period_cycle == BATTERY_BUZZ_TIME_MS) {
			change_battery_buzzer_noise_val(battery_buzzer, false);
		}
		battery_buzzer->ms_since_period_cycle =
				battery_buzzer->ms_since_period_cycle == NO_BATTERY_PERIOD_MS ?
						0 : battery_buzzer->ms_since_period_cycle + 2;
		break;
	case CRITICALLY_LOW_BATTERY_DATA:
		if (battery_buzzer->ms_since_period_cycle == 0) {
			change_battery_buzzer_noise_val(battery_buzzer, true);
		}
		else if (battery_buzzer->ms_since_period_cycle == BATTERY_BUZZ_TIME_MS) {
			change_battery_buzzer_noise_val(battery_buzzer, false);
		}
		battery_buzzer->ms_since_period_cycle =
				battery_buzzer->ms_since_period_cycle == CRITICALLY_LOW_BATTERY_BUZZ_PERIOD_MS ?
						0 : battery_buzzer->ms_since_period_cycle + 2;
		break;
	case LOW_BATTERY_DATA:
		if (battery_buzzer->ms_since_period_cycle == 0) {
			change_battery_buzzer_noise_val(battery_buzzer, true);
		}
		else if (battery_buzzer->ms_since_period_cycle == BATTERY_BUZZ_TIME_MS) {
			change_battery_buzzer_noise_val(battery_buzzer, false);
		}
		battery_buzzer->ms_since_period_cycle =
				battery_buzzer->ms_since_period_cycle == LOW_BATTERY_BUZZ_PERIOD_MS ?
						0 : battery_buzzer->ms_since_period_cycle + 2;
		break;
	default:
		battery_buzzer->ms_since_period_cycle = 0;
		break;
	}
}

// REQUIRES: battery_buzzer is an object and data is the new battery data.
// Data should be 0 for no battery, 1 for critically low battery,
// 2 for low battery, and 3/4/5 for others values.
// MODIFIES: nothing
// EFFECTS: Updates the battery buzzer data
void change_battery_buzzer_data(BatteryBuzzer *battery_buzzer, uint8_t data) {
	*battery_buzzer->battery_data = data;
}

// REQUIRES: battery_buzzer is an object and val is if it should be on or off.
// MODIFIES: nothing
// EFFECTS: Changes the output noise of the battery buzzer.
void change_battery_buzzer_noise_val(BatteryBuzzer *battery_buzzer, bool val) {
	set_pin_value(battery_buzzer->buzzer_pin, val);
}
