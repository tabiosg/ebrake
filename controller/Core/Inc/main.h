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
#define BLUETOOTH_UART_RX_Pin GPIO_PIN_7
#define BLUETOOTH_UART_RX_GPIO_Port GPIOB
#define DEBUG_LED_Pin GPIO_PIN_2
#define DEBUG_LED_GPIO_Port GPIOF
#define TRIGGER_POTENTIOMETER_ADC_Pin GPIO_PIN_0
#define TRIGGER_POTENTIOMETER_ADC_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOA
#define BATTERY_STATUS_BUTTON_Pin GPIO_PIN_2
#define BATTERY_STATUS_BUTTON_GPIO_Port GPIOA
#define BATTERY_OUTPUT_Pin GPIO_PIN_3
#define BATTERY_OUTPUT_GPIO_Port GPIOA
#define DISPLAY_0_Pin GPIO_PIN_4
#define DISPLAY_0_GPIO_Port GPIOA
#define DISPLAY_1_Pin GPIO_PIN_5
#define DISPLAY_1_GPIO_Port GPIOA
#define DISPLAY_2_Pin GPIO_PIN_6
#define DISPLAY_2_GPIO_Port GPIOA
#define DISPLAY_3_Pin GPIO_PIN_7
#define DISPLAY_3_GPIO_Port GPIOA
#define DISPLAY_4_Pin GPIO_PIN_0
#define DISPLAY_4_GPIO_Port GPIOB
#define DISPLAY_5_Pin GPIO_PIN_11
#define DISPLAY_5_GPIO_Port GPIOA
#define DISPLAY_6_Pin GPIO_PIN_12
#define DISPLAY_6_GPIO_Port GPIOA
#define BLUETOOTH_UART_TX_Pin GPIO_PIN_6
#define BLUETOOTH_UART_TX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
