#include "controller_wireless.h"

/** PUBLIC FUNCTIONS **/

// REQUIRES: huart is a UART channel
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Wireless object
Wireless *new_wireless(UART_HandleTypeDef *huart) {
	Wireless *wireless = (Wireless*) malloc(sizeof(Wireless));
	wireless->uart = huart;
	return wireless;
}

// REQUIRES: wireless is a Wireless object
// and trigger_input is an int from 0 to 64
// of the arm in degrees
// MODIFIES: Nothing
// EFFECTS: Sends trigger input command over wireless
void send_wireless_trigger_input(Wireless *wireless, int trigger_input) {
	char string[10];
	sprintf((char *)string, "T%iET%iE", trigger_input, trigger_input);
	send_wireless_string_10(wireless, string);
}

// REQUIRES: wireless and display are objects
// MODIFIES: Nothing
// EFFECTS: Attempts to parse data based on wireless buffer and returns true if success
bool parse_wireless_message(Wireless *wireless, Display* display, char start_char) {
	int start_of_transmit = -1;
	int end_of_transmit = -1;
	for (int i = 0; i < sizeof(wireless->uart_buffer) - 1; ++i) {
		if (wireless->uart_buffer[i] == start_char && isdigit(wireless->uart_buffer[i + 1])) {
			start_of_transmit = i + 1;
			break;
		}
	}
	if (start_of_transmit == -1) return false;
	for (int i = start_of_transmit; i < sizeof(wireless->uart_buffer); ++i) {
		if (wireless->uart_buffer[i] == 'E') {
			end_of_transmit = i;
			break;
		}
		else {
			if (!isdigit(wireless->uart_buffer[i])) return false;
		}
	}
	if (end_of_transmit == -1) return false;

	char contents_string[5];
	int length = end_of_transmit - start_of_transmit;
	memcpy(contents_string, wireless->uart_buffer + start_of_transmit, length);

	int content = atoi(contents_string);

	wireless->message_contents = content;

	return true;
}

// REQUIRES: wireless and display are objects
// MODIFIES: Nothing
// EFFECTS: Receives the wireless speed and changes the display based on it
void receive_wireless(Wireless *wireless, Display* display, BatteryBuzzer* battery) {
	HAL_UART_Receive_DMA(wireless->uart, wireless->uart_buffer, sizeof(wireless->uart_buffer));

	bool speed_success = parse_wireless_message(wireless, display, 'S');
	if (speed_success) {
		wireless->ms_since_comms = 0;
		update_display_number(display, wireless->message_contents);
		return;
	}

	bool battery_data_success = parse_wireless_message(wireless, display, 'B');
	if (battery_data_success) {
		wireless->ms_since_comms = 0;
		change_battery_buzzer_data(battery, wireless->message_contents);
		return;
	}

}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 10 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_10(Wireless *wireless, char string[10]) {
	HAL_Delay(50);
	HAL_UART_Transmit(wireless->uart, (uint8_t *)string, sizeof(wireless->uart_buffer), 200);
	HAL_Delay(50);
}

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Increases ms_since_comms.
// Assumes function is called every 2 ms
void refresh_wireless_status(Wireless *wireless) {
	wireless->ms_since_comms = wireless->ms_since_comms >= TIME_INDICATING_WIRELESS_COMMS_LOST_MS ?
			TIME_INDICATING_WIRELESS_COMMS_LOST_MS : wireless->ms_since_comms + 2;
}

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Returns whether or not wireless comms were lost
bool is_wireless_comms_lost(Wireless *wireless) {
	return wireless->ms_since_comms >= TIME_INDICATING_WIRELESS_COMMS_LOST_MS;
}

