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
#include "stm32f4xx_hal.h"

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
#define FAST_PERIOD 20
#define FORCE_SENSOR_Pin GPIO_PIN_0
#define FORCE_SENSOR_GPIO_Port GPIOA
#define POTENTIOMETER_Pin GPIO_PIN_1
#define POTENTIOMETER_GPIO_Port GPIOA
#define BATTERY_DATA_Pin GPIO_PIN_4
#define BATTERY_DATA_GPIO_Port GPIOA
#define LIMIT_SWITCH_Pin GPIO_PIN_5
#define LIMIT_SWITCH_GPIO_Port GPIOA
#define DRV8825_DIR_Pin GPIO_PIN_4
#define DRV8825_DIR_GPIO_Port GPIOC
#define DRV8825_STP_Pin GPIO_PIN_5
#define DRV8825_STP_GPIO_Port GPIOC
#define DEBUG_LED_Pin GPIO_PIN_1
#define DEBUG_LED_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_10
#define IMU_SCL_GPIO_Port GPIOB
#define BLUETOOTH_UART_TX_Pin GPIO_PIN_9
#define BLUETOOTH_UART_TX_GPIO_Port GPIOA
#define BLUETOOTH_UART_RX_Pin GPIO_PIN_10
#define BLUETOOTH_UART_RX_GPIO_Port GPIOA
#define IMU_SDA_Pin GPIO_PIN_3
#define IMU_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
