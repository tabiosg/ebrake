#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "skater.h"
#include "joint.h"

// UART is used for wireless
// communication with other devices.
typedef struct {
	UART_HandleTypeDef *uart;
	uint8_t uart_buffer[10];
	int message_contents;
} Wireless;

/** PUBLIC FUNCTIONS **/

// REQUIRES: huart is a UART channel
// MODIFIES: Nothing
// EFFECTS: Returns a pointer to a created Wireless object
Wireless *new_wireless(UART_HandleTypeDef *huart);

// REQUIRES: wireless is a Wireless object
// and speed is the speed data
// MODIFIES: Nothing
// EFFECTS: Sends speed data over wireless
void send_wireless_speed(Wireless *wireless, int speed);

// REQUIRES: wireless is a Wireless object
// and battery_data is the battery data
// MODIFIES: Nothing
// EFFECTS: Sends battery data over wireless
void send_wireless_battery_data(Wireless *wireless, int battery_data);

// REQUIRES: wireless, skater, and joint are objects
// MODIFIES: Nothing
// EFFECTS: Attempts to parse data based on wireless buffer and returns true if success
bool parse_wireless_message(Wireless *wireless, Skater* skater, Joint* joint, char start_char);

// REQUIRES: wireless, skater, and joint are objects
// MODIFIES: Nothing
// EFFECTS: Receives the wireless angle and changes the joint angle if skater is on the board
void receive_wireless(Wireless *wireless, Skater* skater, Joint* joint);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 10 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_10(Wireless *wireless, char string[10]);
