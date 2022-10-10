# Electronic Braking System for Longboards

For EECS 473, our group decided on making an electronic braking system for longboards. Developed by Austin, Iman, Wendy, Nathan, and Guthrie. Original idea was created by Nathan.

---

## Description

The basics is that the user can brake their own longboard via a controller.

The main goals are reliability and cost.

---

## Developing

First clone the repository and get accustomed to developing in the STM32CubeIDE.

When setting up the IDE, make sure to enable printf for floats.
To do this, click Project -> Properties -> C/C++ Build -> Settings -> MCU Settings.
Then check the box that says "Use float with printf from newlib-nano (-u_printf_float).

Also, make sure to add the libraries folder in the path directory for both STM32 projects.
To do this, click Project -> Properties -> C/C++ General -> Paths and Symbols -> Includes -> Add.
Then select the libraries directory and click apply. Make sure to do the same for the other STM32 project.

---

## Attaching the System

This section explains how to attach the system to your longboard.

TBD.

---

## Braking System Explained

TBD. 

---

## Controller Features

The user should be able to control braking using the controller through the use of a trigger.
The trigger will correspond to the desired angle of the motor.

Also, the user should be able to monitor speed on the controller.
The speed will be displayed in miles per hour.

---

## Braking System Features

The braking system is able to detect if the user has lost control of the skateboard.
A force sensor is used to detect the presence of the user.
If the user is not detected for over a second, then
the braking arm will automatically move to the braking position.

---

## Bluetooth Settings

The STM32 connects to the Bluetooth module via USART.

The following explains how to configure the Bluetooth module.

---

## Authors

- Austin
- Iman
- Wendy
- Nathan
- Guthrie