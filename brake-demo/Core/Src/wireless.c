#include "wireless.h"

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
// and speed is the speed data
// MODIFIES: Nothing
// EFFECTS: Sends speed data over wireless
void send_wireless_speed(Wireless *wireless, float speed) {
	char string[30];
	sprintf((char *)string, "$SPEED_DATA,%f,\n", speed);
	send_wireless_string_30(wireless, string);
}

// REQUIRES: wireless is a Wireless object
// and desired_angle is the desired angle
// of the arm in degrees
// MODIFIES: Nothing
// EFFECTS: Sends desired angle degrees command over wireless
void send_wireless_desired_angle(Wireless *wireless, float desired_angle) {
	char string[30];
	sprintf((char *)string, "$DESIRED_ANGLE_CMD,%f,\n", desired_angle);
	send_wireless_string_30(wireless, string);
}


/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 30 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_30(Wireless *wireless, char string[30]) {
	HAL_Delay(50);
	HAL_UART_Transmit_IT(wireless->uart, (uint8_t *)string, 30);
	HAL_Delay(50);
}
