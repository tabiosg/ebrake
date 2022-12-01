/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SLOW_PERIOD 2000
#define FAST_PERIOD 50
#define IMU_PERIOD 50000
#define BLUETOOTH_UART_RX_Pin GPIO_PIN_7
#define BLUETOOTH_UART_RX_GPIO_Port GPIOB
#define LIMIT_SWITCH_1_Pin GPIO_PIN_9
#define LIMIT_SWITCH_1_GPIO_Port GPIOB
#define DEBUG_LED_Pin GPIO_PIN_2
#define DEBUG_LED_GPIO_Port GPIOF
#define FORCE_SENSOR_Pin GPIO_PIN_0
#define FORCE_SENSOR_GPIO_Port GPIOA
#define LIMIT_SWITCH_2_Pin GPIO_PIN_1
#define LIMIT_SWITCH_2_GPIO_Port GPIOA
#define POTENTIOMETER_Pin GPIO_PIN_2
#define POTENTIOMETER_GPIO_Port GPIOA
#define BATTERYDATA_Pin GPIO_PIN_3
#define BATTERYDATA_GPIO_Port GPIOA
#define DEBUG_PIN_0_Pin GPIO_PIN_5
#define DEBUG_PIN_0_GPIO_Port GPIOA
#define DRV8825_STP_Pin GPIO_PIN_6
#define DRV8825_STP_GPIO_Port GPIOA
#define DRV8825_DIR_Pin GPIO_PIN_7
#define DRV8825_DIR_GPIO_Port GPIOA
#define DEBUG_PIN_1_Pin GPIO_PIN_0
#define DEBUG_PIN_1_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_11
#define IMU_SCL_GPIO_Port GPIOA
#define IMU_SDA_Pin GPIO_PIN_12
#define IMU_SDA_GPIO_Port GPIOA
#define BLUETOOTH_UART_TX_Pin GPIO_PIN_6
#define BLUETOOTH_UART_TX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
