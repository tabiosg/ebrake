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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLUETOOTH_UART_RX_Pin GPIO_PIN_7
#define BLUETOOTH_UART_RX_GPIO_Port GPIOB
#define LIMIT_SWITCH_Pin GPIO_PIN_14
#define LIMIT_SWITCH_GPIO_Port GPIOC
#define QUAD_A_Pin GPIO_PIN_0
#define QUAD_A_GPIO_Port GPIOA
#define QUAD_B_Pin GPIO_PIN_1
#define QUAD_B_GPIO_Port GPIOA
#define POTENTIOMETER_Pin GPIO_PIN_2
#define POTENTIOMETER_GPIO_Port GPIOA
#define BATTERY_LED_Pin GPIO_PIN_3
#define BATTERY_LED_GPIO_Port GPIOA
#define HX711_DATA_Pin GPIO_PIN_4
#define HX711_DATA_GPIO_Port GPIOA
#define HX711_SCK_Pin GPIO_PIN_5
#define HX711_SCK_GPIO_Port GPIOA
#define HBRIDGE_PWM_Pin GPIO_PIN_6
#define HBRIDGE_PWM_GPIO_Port GPIOA
#define HBRIDGE_DIR_Pin GPIO_PIN_7
#define HBRIDGE_DIR_GPIO_Port GPIOA
#define HBRIDGE_NDIR_Pin GPIO_PIN_0
#define HBRIDGE_NDIR_GPIO_Port GPIOB
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
