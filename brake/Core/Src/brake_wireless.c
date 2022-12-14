#include "brake_wireless.h"

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
// MODIFIES: Nothing
// EFFECTS: Increases ms_since_comms.
// Assumes function is called every 2 ms
void refresh_wireless_status(Wireless *wireless) {
	wireless->ms_since_comms += 2;
}

// REQUIRES: wireless is a Wireless object
// MODIFIES: Nothing
// EFFECTS: Returns whether or not wireless comms were lost
bool is_wireless_comms_lost(Wireless *wireless) {
	return wireless->ms_since_comms >= TIME_INDICATING_WIRELESS_COMMS_LOST_MS;
}

// REQUIRES: wireless is a Wireless object
// and speed is the speed data
// MODIFIES: Nothing
// EFFECTS: Sends speed data over wireless
void send_wireless_speed(Wireless *wireless, int speed) {
	char string[sizeof(wireless->uart_buffer)];
	sprintf((char *)string, "S%iES%iE", speed, speed);
	send_wireless_string_10(wireless, string);
}

// REQUIRES: wireless is a Wireless object
// and skater_status is 0 if board does not detect skater
// MODIFIES: Nothing
// EFFECTS: Send wireless skater status
void send_wireless_detect_skater_status(Wireless *wireless, uint8_t skater_status) {
	char string[sizeof(wireless->uart_buffer)];
	sprintf((char *)string, "D%iED%iE", skater_status, skater_status);
	send_wireless_string_10(wireless, string);
}

// REQUIRES: wireless is a Wireless object
// and battery_data is the battery data
// MODIFIES: Nothing
// EFFECTS: Sends battery data over wireless
void send_wireless_battery_data(Wireless *wireless, int battery_data) {
	char string[sizeof(wireless->uart_buffer)];
	sprintf((char *)string, "B%iEB%iE", battery_data, battery_data);
	send_wireless_string_10(wireless, string);
}

// REQUIRES: wireless and display are objects
// MODIFIES: Nothing
// EFFECTS: Attempts to parse data based on wireless buffer and returns true if success
bool parse_wireless_message(Wireless *wireless, char start_char) {
	int start_of_transmit = -1;
	int end_of_transmit = -1;
	for (int i = 0; i < sizeof(wireless->uart_buffer) - 1; ++i) {
		if (wireless->uart_buffer[i] == start_char && isdigit((unsigned char)wireless->uart_buffer[i + 1])) {
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

// REQUIRES: wireless, skater, and joint are objects
// MODIFIES: Nothing
// EFFECTS: Receives the wireless angle and changes the joint angle if skater is on the board
void receive_wireless(Wireless *wireless, Skater* skater, Joint* joint) {
//	for (int i = 0; i < 10; ++i) {
//		wireless->uart_buffer[i] = 0;
//	}
//	HAL_Delay(10);
	HAL_UART_Receive_DMA(wireless->uart, (uint8_t *)wireless->uart_buffer, sizeof(wireless->uart_buffer));
//	HAL_Delay(10);
	bool target_success = parse_wireless_message(wireless, 'T');
	if (target_success) {
		wireless->ms_since_comms = 0;
		bool is_skater_here = !has_skater_recently_left_board(skater);
		if (is_skater_here) {
			int trigger_val = wireless->message_contents;
			int32_t desired_steps = RIGHT_BEFORE_BRAKING_STEPS;
			if (0 <= trigger_val && trigger_val < 10) {
				desired_steps = RIGHT_BEFORE_BRAKING_STEPS;
			}
			else if (trigger_val < 32) {
				desired_steps = RIGHT_BEFORE_BRAKING_STEPS;
			}
			else if (trigger_val < 63) {
				desired_steps = (trigger_val - 32) * (MAX_BRAKING_STEPS - RIGHT_BEFORE_BRAKING_STEPS) / 32 + RIGHT_BEFORE_BRAKING_STEPS;
			}
			else if (trigger_val < 64){
				desired_steps = MAX_BRAKING_STEPS;
			}
			set_joint_target(joint, desired_steps);
		}
		return;
	}
	bool calib_success = parse_wireless_message(wireless, 'C');
	if (calib_success) {
		calibrate_skater_threshold(skater);
	}
}

/** PRIVATE FUNCTIONS **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 10 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_10(Wireless *wireless, char string[10]) {
	HAL_Delay(50);
	HAL_UART_Transmit(wireless->uart, (uint8_t *)string, sizeof(wireless->uart_buffer), 200);
	HAL_Delay(50);
}
