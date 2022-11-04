#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "skater.h"
#include "joint.h"

// UART is used for wireless
// communication with other devices.
typedef struct {
	UART_HandleTypeDef *uart;
	uint8_t uart_buffer[30];
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
void send_wireless_speed(Wireless *wireless, float speed);

// REQUIRES: wireless is a Wireless object
// and desired_angle is the desired angle
// of the arm in degrees
// MODIFIES: Nothing
// EFFECTS: Sends desired angle degrees command over wireless
void send_wireless_desired_angle(Wireless *wireless, float desired_angle);

// REQUIRES: wireless, skater, and joint are objects
// MODIFIES: Nothing
// EFFECTS: Receives the wireless angle and changes the joint angle if skater is on the board
void receive_wireless_angle(Wireless *wireless, Skater* skater, Joint* joint);

/** PRIVATE FUNCTIONS MAY BE IN SOURCE FILE ONLY **/

// REQUIRES: wireless is a Wireless object
// and string is an array of 30 characters.
// MODIFIES: Nothing
// EFFECTS: Sends the character array over wireless
void send_wireless_string_30(Wireless *wireless, char string[30]);
