#pragma once

#include "stm32g0xx_hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "display.h"
#include "warning_led.h"
#include "battery_buzzer.h"

#define TIME_INDICATING_WIRELESS_COMMS_LOST_MS 10000

// UART is used for wireless
// communication with other devices.
typedef struct {
	UART_HandleTypeDef *uart;
	uint8_t uart_buffer[10];
	int message_contents;
	uint32_t ms_since_comms;
	Display* display;
	BatteryBuzzer* battery_buzzer;
	WarningLed* warning_led;
} Wireless;

/** PUBLIC FUNCTIONS **/

// REQUIRES: huart is a UART channel
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Wireless object
Wireless *new_wireless(UART_HandleTypeDef *huart, Display* _display, BatteryBuzzer* _battery_buzzer, WarningLed* _warning_led);

// REQUIRES: wireless is a Wireless object
// and trigger_input is an int from 0 to 64
// MODIFIES: Nothing
// EFFECTS: Sends trigger input command over wireless
void send_wireless_trigger_input(Wireless *wireless, int trigger_input);

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Sends calibration command over wireless
void send_wireless_calib(Wireless *wireless);

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Attempts to parse data based on wireless buffer and returns true if success
bool parse_wireless_message(Wireless *wireless, char start_char);

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Receives the wireless message and updates program based on it
void receive_wireless(Wireless *wireless);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 10 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_10(Wireless *wireless, char string[10]);

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Increases ms_since_comms.
// Assumes function is called every 2 ms
void refresh_wireless_status(Wireless *wireless);

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Returns whether or not wireless comms were lost
bool is_wireless_comms_lost(Wireless *wireless);
