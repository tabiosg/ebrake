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
// and desired_angle is the desired angle
// of the arm in degrees
// MODIFIES: Nothing
// EFFECTS: Sends desired angle degrees command over wireless
void send_wireless_desired_angle(Wireless *wireless, int desired_angle) {
	char string[10];
	sprintf((char *)string, "T%iET%iE", desired_angle, desired_angle);
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
void receive_wireless(Wireless *wireless, Display* display) {
	HAL_UART_Receive(wireless->uart, wireless->uart_buffer, sizeof(wireless->uart_buffer), 500);

	bool speed_success =  parse_wireless_message(wireless, display, 'S');
	if (speed_success) {
		update_display_number(display, wireless->message_contents);
		return;
	}

	bool battery_data_success = parse_wireless_message(wireless, display, 'B');
	if (battery_data_success) {
		// TODO - SOMETHING WILL HAVE TO HAPPEN
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
