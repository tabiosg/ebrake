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
#define FAST_PERIOD 1000
#define SLOW_PERIOD 2000
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define FORCE_SENSOR_Pin GPIO_PIN_0
#define FORCE_SENSOR_GPIO_Port GPIOA
#define POTENTIOMETER_Pin GPIO_PIN_1
#define POTENTIOMETER_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA
#define DRV8825_STP_Pin GPIO_PIN_6
#define DRV8825_STP_GPIO_Port GPIOA
#define BLUETOOTH_USART_RX_Pin GPIO_PIN_5
#define BLUETOOTH_USART_RX_GPIO_Port GPIOC
#define BLUETOOTH_USART_TX_Pin GPIO_PIN_9
#define BLUETOOTH_USART_TX_GPIO_Port GPIOA
#define LIMIT_SWITCH_Pin GPIO_PIN_6
#define LIMIT_SWITCH_GPIO_Port GPIOC
#define LIMIT_SWITCH_EXTI_IRQn EXTI4_15_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define DRV8825_DIR_Pin GPIO_PIN_5
#define DRV8825_DIR_GPIO_Port GPIOD
#define DEBUG_LED_Pin GPIO_PIN_3
#define DEBUG_LED_GPIO_Port GPIOB
#define BATTERY_LED_Pin GPIO_PIN_4
#define BATTERY_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
