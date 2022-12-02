/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "adc_sensor.h"
#include "brake_wireless.h"
#include "battery_sensor.h"
#include "force_sensor.h"
#include "imu.h"
#include "interrupt_timer.h"
#include "joint.h"
#include "motor.h"
#include "potentiometer.h"
#include "skater.h"
#include "speed_sensor.h"
#include <stdbool.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define USE_POTENTIOMETER_FEEDBACK false
#define USE_FORCE_SENSOR true
#define USE_WIRELESS_COMMS_WATCHDOG true
#define USE_LIMIT_SWITCH true
#define USE_IMU false

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */

ADCSensor *adc_sensor = NULL;
BatterySensor *battery_sensor = NULL;
IMU *front_imu = NULL;
IMU *back_imu = NULL;
Motor *motor = NULL;
Potentiometer *potentiometer = NULL;
Joint *joint = NULL;
ForceSensor *force_sensor = NULL;
Skater *skater = NULL;
SpeedSensor *speed_sensor = NULL;
Wireless *wireless = NULL;
PinData* motor_direction_pin = NULL;
PinData* motor_step_pin = NULL;
PinData* rest_limit_switch_pin = NULL;
PinData* brake_limit_switch_pin = NULL;
PinData* debug_led = NULL;
PinData* debug_pin_0 = NULL;
PinData* debug_pin_1 = NULL;
InterruptTimer* slow_interrupt_timer = NULL;
InterruptTimer* fast_interrupt_timer = NULL;
InterruptTimer* imu_interrupt_timer = NULL;
bool send_message_flag = false;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM14_Init(void);
static void MX_TIM16_Init(void);
static void MX_TIM17_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	receive_wireless(wireless, skater, joint);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == fast_interrupt_timer->timer) {

		set_pin_value(debug_pin_1, 1);
		// 50 us
		move_joint_to_target(joint);
		set_pin_value(debug_pin_1, 0);

	}
	else if (htim == slow_interrupt_timer->timer) {

		// 2 ms
		update_adc_sensor_values(adc_sensor);
		if (USE_FORCE_SENSOR) {
			refresh_skater_status(skater);
		}

		if (USE_LIMIT_SWITCH) {
	//		bool motor_thinks_is_at_rest = abs(joint->current_angle_steps - AUTOMATIC_RELAX_ANGLE_STEPS) < DESIRED_ANGLE_LAX_STEPS;
			bool motor_thinks_is_at_rest = joint->current_angle_steps < DESIRED_ANGLE_LAX_STEPS;
			if (motor_thinks_is_at_rest && !joint->is_rest_limit_switch_activated) {
				// Increase its current angle by an arbitrary number in order to make it head in the direction of the desired.
				joint->current_angle_steps += ARBITRARY_ADD_ANGLE_FOR_LIMIT_SWITCH_STEPS;
			}
			else {
		//		bool motor_thinks_is_at_brake = abs(joint->current_angle_steps - AUTOMATIC_BRAKING_ANGLE_STEPS) < DESIRED_ANGLE_LAX_STEPS;
				bool motor_thinks_is_at_brake = joint->current_angle_steps > AUTOMATIC_BRAKING_ANGLE_STEPS_LOW && joint->current_angle_steps < AUTOMATIC_BRAKING_ANGLE_STEPS_HIGH;
				if (motor_thinks_is_at_brake && !joint->is_brake_limit_switch_activated) {
					// Increase its current angle by an arbitrary number in order to make it head in the direction of the desired.
					joint->current_angle_steps -= ARBITRARY_ADD_ANGLE_FOR_LIMIT_SWITCH_STEPS;
				}
			}
		}
		if (USE_LIMIT_SWITCH) {
			refresh_joint_limit_switch(joint);
		}
		if (USE_POTENTIOMETER_FEEDBACK) {
			refresh_joint_angle(joint);
		}

		if (is_skater_gone(skater)) {
			bool board_is_on_the_floor = is_imu_z_accel_equal_to_gravity(front_imu);
			if (board_is_on_the_floor) {
				set_joint_target(joint, AUTOMATIC_BRAKING_ANGLE_STEPS);
			}
		}
		else if (USE_WIRELESS_COMMS_WATCHDOG && is_wireless_comms_lost(wireless)) {
			set_joint_target(joint, AUTOMATIC_RELAX_ANGLE_STEPS);
		}

		refresh_wireless_status(wireless);
	}
	else if (htim == imu_interrupt_timer->timer) {
		// Called once every 200 ms
		refresh_imu_accel_in_axis(front_imu, Z_Axis);
		refresh_imu_accel_in_axis(back_imu, Z_Axis);
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	adc_sensor = new_adc_sensor(&hadc1, 3);
	// TODO - Implement actual code for the IMUs
	front_imu = new_imu_sensor(&hi2c2, ADDRESS_BOTH_GROUND);
	back_imu = new_imu_sensor(&hi2c2, ADDRESS_BOTH_HIGH);
	motor_direction_pin = new_pin_data(DRV8825_DIR_GPIO_Port, DRV8825_DIR_Pin, PIN_IS_OUTPUT);
	motor_step_pin = new_pin_data(DRV8825_STP_GPIO_Port, DRV8825_STP_Pin, PIN_IS_OUTPUT);
	rest_limit_switch_pin = new_pin_data(LIMIT_SWITCH_2_GPIO_Port, LIMIT_SWITCH_2_Pin, PIN_IS_INPUT);
	brake_limit_switch_pin = new_pin_data(LIMIT_SWITCH_1_GPIO_Port, LIMIT_SWITCH_1_Pin, PIN_IS_INPUT);
	debug_led = new_pin_data(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, PIN_IS_OUTPUT);
	debug_pin_0 = new_pin_data(DEBUG_PIN_0_GPIO_Port, DEBUG_PIN_0_Pin, PIN_IS_OUTPUT);
	debug_pin_1 = new_pin_data(DEBUG_PIN_1_GPIO_Port, DEBUG_PIN_1_Pin, PIN_IS_OUTPUT);
	motor = new_motor(motor_direction_pin, motor_step_pin);
	slow_interrupt_timer = new_interrupt_timer(&htim14);
	fast_interrupt_timer = new_interrupt_timer(&htim16);
	imu_interrupt_timer = new_interrupt_timer(&htim17);
	potentiometer = new_potentiometer(adc_sensor, 1);
	joint = new_joint(motor, potentiometer, rest_limit_switch_pin, brake_limit_switch_pin);
	force_sensor = new_force_sensor(adc_sensor, 0);
	battery_sensor = new_battery_sensor(adc_sensor, 2);
	skater = new_skater(force_sensor);
	wireless = new_wireless(&huart1);
	speed_sensor = new_speed_sensor(front_imu, back_imu);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM14_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  /* USER CODE BEGIN 2 */

  start_interrupt_timer(fast_interrupt_timer);
  start_interrupt_timer(slow_interrupt_timer);
  if (USE_IMU) {
	  start_interrupt_timer(imu_interrupt_timer);
  }

  receive_wireless(wireless, skater, joint);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  // TODO - this statement is in an if statement since we are afraid that it takes too much time
	  // and will decrease responsiveness. However, this may not actually be true
	  // It is worth testing to see if this is actually the case.
	  HAL_Delay(1000);
	  if (is_joint_close_enough_to_target(joint)) {
		  uint8_t current_speed = get_speed_sensor_data(speed_sensor);
		  send_wireless_speed(wireless, current_speed);

		  uint8_t battery_data = get_battery_sensor_data(battery_sensor);
		  send_wireless_battery_data(wireless, battery_data);

	  }
	  set_pin_value(debug_pin_0, 1);
	  set_pin_value(debug_pin_0, 0);


//	  for (int i = 0; i < 90; i = i + 5) {
//		  HAL_Delay(2000);
//		  set_joint_target(joint, i);
////		  move_joint_to_target(joint);
//	  }
//
//	  for (int i = 90; i >= 0; i = i - 5) {
//		  HAL_Delay(2000);
//		  set_joint_target(joint, i);
////		  move_joint_to_target(joint);
//	  }

//	set_pin_value(motor_direction_pin, 1);
//	set_pin_value(motor_direction_pin, 0);
//	set_pin_value(motor_step_pin, 1);
//	set_pin_value(motor_step_pin, 0);

//	set_pin_value(debug_led, 1);
//	set_pin_value(debug_led, 0);
//  	set_pin_value(debug_pin_0, 1);
//  	set_pin_value(debug_pin_0, 0);
//  	set_pin_value(debug_pin_1, 1);
//	set_pin_value(debug_pin_1, 0);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_6B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 3;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00303D5B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 15;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = SLOW_PERIOD;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 15;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = FAST_PERIOD;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 127;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = IMU_PERIOD;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LIMIT_SWITCH_1_Pin|DEBUG_PIN_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LIMIT_SWITCH_2_Pin|DEBUG_PIN_0_Pin|DRV8825_STP_Pin|DRV8825_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LIMIT_SWITCH_1_Pin */
  GPIO_InitStruct.Pin = LIMIT_SWITCH_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LIMIT_SWITCH_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DEBUG_LED_Pin */
  GPIO_InitStruct.Pin = DEBUG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DEBUG_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LIMIT_SWITCH_2_Pin */
  GPIO_InitStruct.Pin = LIMIT_SWITCH_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LIMIT_SWITCH_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DEBUG_PIN_0_Pin DRV8825_STP_Pin DRV8825_DIR_Pin */
  GPIO_InitStruct.Pin = DEBUG_PIN_0_Pin|DRV8825_STP_Pin|DRV8825_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DEBUG_PIN_1_Pin */
  GPIO_InitStruct.Pin = DEBUG_PIN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DEBUG_PIN_1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
