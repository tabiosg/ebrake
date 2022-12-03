#include "warning_led.h"

// REQUIRES: _warning_led_pin is the warning LED pin,
// and _wireless is the wireless object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created WarningLed object
WarningLed *new_warning_led(PinData *_warning_led_pin, uint8_t* _battery_data) {
	WarningLed *warning_led = (WarningLed*) malloc(sizeof(WarningLed));
	warning_led->warning_led_pin = _warning_led_pin;
	warning_led->ms_since_period_cycle = 0;
	warning_led->battery_data = _battery_data;
	warning_led->is_skater_detected_on_board = true;
	return warning_led;
}

// REQUIRES: warning_led is the warning LED
// MODIFIES: nothing
// EFFECTS: Updates the logic of the warning LED.
// It will blink for 1 second every 2 second if lost communication.
// It will stay on if the battery is low on battery.
// This function is expected to be called every 2 ms.
void update_warning_led_logic(WarningLed *warning_led, bool is_comms_lost) {
	if (is_comms_lost) {
		// Blink the LED
		if (warning_led->ms_since_period_cycle % WARNING_LED_PERIOD_MS == 0) {
			set_pin_value(warning_led->warning_led_pin, true);
		}
		else if (warning_led->ms_since_period_cycle % WARNING_LED_PERIOD_MS == WARNING_LED_TIME_MS) {
			set_pin_value(warning_led->warning_led_pin, false);
		}
		warning_led->ms_since_period_cycle += 2;
	}
	else if (!warning_led->is_skater_detected_on_board) {
		if (warning_led->ms_since_period_cycle % WARNING_LED_SKATER_NOT_DETECTED_PERIOD_MS == 0) {
					set_pin_value(warning_led->warning_led_pin, true);
				}
		else if (warning_led->ms_since_period_cycle % WARNING_LED_SKATER_NOT_DETECTED_PERIOD_MS == WARNING_LED_SKATER_NOT_DETECTED_FELL_OFF_TIME_MS) {
			set_pin_value(warning_led->warning_led_pin, false);
		}
		warning_led->ms_since_period_cycle += 2;
	}
	else if (*warning_led->battery_data <= LOW_BATTERY_DATA) {
		// Keep the LED on
		if (warning_led->ms_since_period_cycle % WARNING_LED_PERIOD_MS == 0) {
			set_pin_value(warning_led->warning_led_pin, true);
		}
		warning_led->ms_since_period_cycle += 2;
	}
	else {
		set_pin_value(warning_led->warning_led_pin, false);
		warning_led->ms_since_period_cycle = 0;
	}
}
