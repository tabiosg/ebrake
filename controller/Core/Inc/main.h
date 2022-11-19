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
#define FAST_PERIOD 1000
#define BLUETOOTH_UART_RX_Pin GPIO_PIN_7
#define BLUETOOTH_UART_RX_GPIO_Port GPIOB
#define DEBUG_LED_Pin GPIO_PIN_2
#define DEBUG_LED_GPIO_Port GPIOF
#define TRIGGER_POTENTIOMETER_ADC_Pin GPIO_PIN_0
#define TRIGGER_POTENTIOMETER_ADC_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOA
#define BATTERY_OUTPUT_Pin GPIO_PIN_3
#define BATTERY_OUTPUT_GPIO_Port GPIOA
#define SHIFT_SER_Pin GPIO_PIN_4
#define SHIFT_SER_GPIO_Port GPIOA
#define SHIFT_SRCLK_Pin GPIO_PIN_5
#define SHIFT_SRCLK_GPIO_Port GPIOA
#define SHIFT_NOT_SRCLK_Pin GPIO_PIN_6
#define SHIFT_NOT_SRCLK_GPIO_Port GPIOA
#define SHIFT_RCLK_Pin GPIO_PIN_7
#define SHIFT_RCLK_GPIO_Port GPIOA
#define SHIFT_NOT_OE_Pin GPIO_PIN_0
#define SHIFT_NOT_OE_GPIO_Port GPIOB
#define BLUETOOTH_UART_TX_Pin GPIO_PIN_6
#define BLUETOOTH_UART_TX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
