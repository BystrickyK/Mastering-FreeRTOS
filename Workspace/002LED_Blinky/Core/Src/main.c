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
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "SEGGER_SYSVIEW.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define DWT_CTRL (*(volatile uint32_t*) 0xE0001000)
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
BaseType_t NotifyAndSuspend(TaskHandle_t handle);
static void handler_LED_red(void* parameters);
static void handler_LED_green(void* parameters);
static void handler_LED_blue(void* parameters);
static void handler_button(void* parameters);
TaskHandle_t task_to_delete;
TaskHandle_t handle_LED_green;
TaskHandle_t handle_LED_red;
TaskHandle_t handle_LED_blue;
TaskHandle_t handle_button;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	  BaseType_t status;

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
  /* USER CODE BEGIN 2 */
  DWT_CTRL |= (1 << 0);

  SEGGER_SYSVIEW_Conf();
  SEGGER_SYSVIEW_Start();
//  SEGGER_UART_Init(500000);

  status = xTaskCreate(handler_LED_green, "Task-Green", 200, NULL,
              2, &handle_LED_green);
  configASSERT(status == pdPASS);


  status = xTaskCreate(handler_LED_red, "Task-Red", 200, NULL,
              2, &handle_LED_red);
  configASSERT(status == pdPASS);


  status = xTaskCreate(handler_LED_blue, "Task-Blue", 200, NULL,
              2, &handle_LED_blue);
  configASSERT(status == pdPASS);


  status = xTaskCreate(handler_button, "Task-Button", 200, NULL,
              3, &handle_button);
  configASSERT(status == pdPASS);

  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB14 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
static void handler_LED_red(void* parameters)
{
	const TickType_t xPeriod = pdMS_TO_TICKS(250);
	TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1)
  {
	  vTaskDelayUntil(&xLastWakeTime, xPeriod);
//    SEGGER_SYSVIEW_PrintfTarget("Toggling RED");
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		if (xTaskNotifyWait(0, 0, NULL, 0))
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
			xTaskNotify(handle_button, 0, eNoAction);
		}
  }
}

static void handler_LED_blue(void* parameters)
{
  const TickType_t xPeriod = pdMS_TO_TICKS(250);
  vTaskDelay(pdMS_TO_TICKS(50));
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1)
  {
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		if (xTaskNotifyWait(0, 0, NULL, 0))
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
			xTaskNotify(handle_button, 0, eNoAction);
		}
  }
}


static void handler_LED_green(void* parameters)
{
  const TickType_t xPeriod = pdMS_TO_TICKS(250);
  vTaskDelay(pdMS_TO_TICKS(100));
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1)
  {
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
		if (xTaskNotifyWait(0, 0, NULL, 0))
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			xTaskNotify(handle_button, 0, eNoAction);
		}
  }
}

static void handler_button(void* parameters)
{
	GPIO_PinState button_state = GPIO_PIN_RESET; //off
	GPIO_PinState button_state_prev = GPIO_PIN_RESET;

	const TickType_t xPeriod = pdMS_TO_TICKS(25);
	TickType_t xLastWakeTime = xTaskGetTickCount();

	uint8_t state = 0;

	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, xPeriod);

		button_state_prev = button_state;
		button_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

		if (button_state==GPIO_PIN_SET && button_state_prev==GPIO_PIN_RESET)
		{
			SEGGER_SYSVIEW_PrintfTarget("Button pressed");

			switch(state)
			{
				case 0:
					if(NotifyAndSuspend(handle_LED_red))
						++state;
					break;
				case 1:
					if(NotifyAndSuspend(handle_LED_blue))
						++state;
					break;
				case 2:
					if(NotifyAndSuspend(handle_LED_green))
						++state;
					break;
				case 3:
					vTaskResume(handle_LED_red);
					vTaskResume(handle_LED_blue);
					vTaskResume(handle_LED_green);
					state = 0;
					break;
			}
		}
	}
}

BaseType_t NotifyAndSuspend(TaskHandle_t handle)
{
	BaseType_t status;
	xTaskNotify(handle, 0, eNoAction);
	status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(1000));
	if (status)
		vTaskSuspend(handle);
	return status;
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

