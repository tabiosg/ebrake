# E-Brake

For EECS 473, our group's project is a wireless, electric-powered, friction-braking system for longboards. We call this product the E-Brake. Developed by Austin, Iman, Wendy, Nathan, and Guthrie. Original idea was created by Nathan.


<img src="https://user-images.githubusercontent.com/71603173/207442646-54b3ac62-dc44-4758-bba6-f2065956eb31.jpg" height=400> <img src="https://user-images.githubusercontent.com/71603173/207442217-9204c7b7-5db6-45a2-9c42-62ef7f43d7bd.jpg" height=400>

---

## Description

This system is employed by the user to have direct control over reducing their speed to reduce the likelihood of a collision. In the case of an event where the user becomes separated from their board, the brake automatically applies to prevent the longboard from hitting someone or going into the road.

---

## Developing

First clone the repository and get accustomed to developing in the STM32CubeIDE.

When setting up the IDE, make sure to enable printf for floats.
To do this, click Project -> Properties -> C/C++ Build -> Settings -> MCU Settings.
Then check the box that says "Use float with printf from newlib-nano (-u_printf_float).

---

## Attaching the System

The brake system bolts onto the back of the board.

---

## Braking System Explained

The brake system deploys downward based on a screw and socket pushing up.

---

## Controller Features

The user should be able to control braking using the controller through the use of a trigger.
The trigger will correspond to the desired angle of the motor.

The controller communicated data regarding a request to calibrate the force sensor and requests for desired braking position based on the trigger position.

The MCU is STM32G031F8P6.
The Bluetooth module is HC05.
The display is LDD-SMHTA304RISITR.
The shift registers are SN74HC595.

---

## Braking System Features

The braking system is able to detect if the user has lost control of the skateboard.
A force sensor is used to detect the presence of the user.
If the user is not detected for over a second, then
the braking arm will automatically move to the braking position.

The MCU is STM32G031F8P6.
The Bluetooth module is HC05.
The motor driver is DRV8825.
The force sensor is SEN-10245.
The IMU is GY-511.
The I2C Mux is TCA9548A.

---

## PCBs

Here are the images of the PCBs

<img src="https://user-images.githubusercontent.com/71603173/207443429-519d50be-1805-4ec5-8f76-28f360d139ac.jpg" height=400> <img src="https://user-images.githubusercontent.com/71603173/207443319-33cc7007-e130-4bd6-8e62-696fbaec6c54.jpg" height=400>

---

## Authors

- Austin
- Iman
- Wendy
- Nathan
- Guthrie
