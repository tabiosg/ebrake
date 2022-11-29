#include "warning_led.h"

// REQUIRES: _warning_led_pin is the warning LED pin, _battery_buzzer is the battery buzzer object,
// and _wireless is the wireless object
// MODIFIES: nothing
// EFFECTS: Returns a pointer to a created WarningLed object
WarningLed *new_warning_led(PinData *_warning_led_pin, BatteryBuzzer* _battery_buzzer, Wireless* _wireless) {
	WarningLed *warning_led = (WarningLed*) malloc(sizeof(WarningLed));
	warning_led->battery_buzzer = _battery_buzzer;
	warning_led->warning_led_pin = _warning_led_pin;
	warning_led->ms_since_period_cycle = 0;
	warning_led->battery_buzzer = _battery_buzzer;
	warning_led->wireless = _wireless;
	return warning_led;
}

// REQUIRES: warning_led is the warning LED
// MODIFIES: nothing
// EFFECTS: Updates the logic of the warning LED.
// It will blink for 1 second every 2 second if lost communication.
// It will stay on if the battery is low on battery.
// This function is expected to be called every 2 ms.
void update_warning_led_logic(WarningLed *warning_led) {
	if (is_wireless_comms_lost(warning_led->wireless)) {
		// Blink the LED
		if (warning_led->ms_since_period_cycle == 0) {
			set_pin_value(warning_led->warning_led_pin, true);
		}
		else if (warning_led->ms_since_period_cycle == WARNING_LED_TIME_MS) {
			set_pin_value(warning_led->warning_led_pin, false);
		}
		warning_led->ms_since_period_cycle =
				warning_led->ms_since_period_cycle == WARNING_LED_PERIOD_MS ?
								0 : warning_led->ms_since_period_cycle + 2;
	}
	else if (warning_led->battery_buzzer->battery_data <= LOW_BATTERY_DATA) {
		// Keep the LED on
		if (warning_led->ms_since_period_cycle == 0) {
			set_pin_value(warning_led->warning_led_pin, true);
		}
		warning_led->ms_since_period_cycle =
						warning_led->ms_since_period_cycle == WARNING_LED_PERIOD_MS ?
										0 : warning_led->ms_since_period_cycle + 2;
	}
	else {
		set_pin_value(warning_led->warning_led_pin, false);
		warning_led->ms_since_period_cycle = 0;
	}
}
