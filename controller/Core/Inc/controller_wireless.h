#pragma once

#include "stm32g0xx_hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "display.h"

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
// and trigger_input is an int from 0 to 64
// of the arm in degrees
// MODIFIES: Nothing
// EFFECTS: Sends trigger input command over wireless
void send_wireless_trigger_input(Wireless *wireless, int trigger_input);

// REQUIRES: wireless and display are objects
// MODIFIES: Nothing
// EFFECTS: Attempts to parse data based on wireless buffer and returns true if success
bool parse_wireless_message(Wireless *wireless, Display* display, char start_char);

// REQUIRES: wireless and display are objects
// MODIFIES: Nothing
// EFFECTS: Receives the wireless speed and changes the display based on it
void receive_wireless(Wireless *wireless, Display* display);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 10 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_10(Wireless *wireless, char string[10]);
