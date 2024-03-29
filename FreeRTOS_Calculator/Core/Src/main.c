/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"
#include "stdint.h"
#include "KEYPAD_Interface.h"
#include "LCD1602.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DWT_CTRL		*((volatile uint32_t*)0xE0001000 )
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
TaskHandle_t KPTaskHandle, LCDTaskHandle, CalculationTaskHandle;
int32_t G_i32ArrNumbers[10];
uint8_t G_u8ArrOperations[9];

QueueHandle_t xQueueInputNumbers;
QueueHandle_t xQueueInputOperations;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

void KPTaskHandler(void * Parameters);
void LCDTaskHandler(void * Parameters);
void CalculationTaskHandler(void * Parameters);
void UserButtonTaskHandler(void );

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

	BaseType_t Local_Status;

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

  /* Enable Cycle counter feature of the processor */
  DWT_CTRL |= 1;

  SEGGER_UART_init(500000);

  /* Configure Sysview target source files and start recording */
  SEGGER_SYSVIEW_Conf();
//  SEGGER_SYSVIEW_Start();

  lcd_init();
  lcd_clear();
  lcd_send_string("Advanced Calculator");
  HAL_Delay(1000);
  lcd_clear();


  xQueueInputNumbers = xQueueCreate(10, sizeof(int32_t));
  xQueueInputOperations = xQueueCreate(10, sizeof(uint8_t));

  Local_Status = xTaskCreate(KPTaskHandler, "KEYPAD", 300, NULL, 3, &KPTaskHandle);

  configASSERT(Local_Status  == pdPASS);

  Local_Status = xTaskCreate(LCDTaskHandler, "LCD", 400, NULL, 1, &LCDTaskHandle);

  configASSERT(Local_Status  == pdPASS);

  Local_Status = xTaskCreate(CalculationTaskHandler, "Calculation", 300, NULL, 2, &CalculationTaskHandle);

  configASSERT(Local_Status  == pdPASS);

//  Local_Status = xTaskCreate(UserButtonTaskHandler, "User-Button", 200, NULL, 3, &TasksHandle[3]);

  configASSERT(Local_Status  == pdPASS);

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|LCD_EN_Pin
                          |LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|LCD_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA4 LCD_EN_Pin
                           LCD_RS_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|LCD_EN_Pin
                          |LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D6_Pin LCD_D5_Pin LCD_D4_Pin */
  GPIO_InitStruct.Pin = LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 LCD_D7_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|LCD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void KPTaskHandler(void * Parameters)
{
	char L_pu8String[50];
	uint8_t  L_u8KeyPadReadValue = 0 , L_u8KeyPadLastValue = 0  ;
	static uint8_t L_u8CountPress = 0;
	TickType_t xLastWakeTime= xTaskGetTickCount();

	while(1)
	{

		L_u8KeyPadReadValue = KEYPAD_read();

		if(L_u8KeyPadReadValue )
		{
			snprintf(L_pu8String, 50, "KP Value is %c\n", L_u8KeyPadReadValue);
			SEGGER_SYSVIEW_PrintfTarget(L_pu8String);

			if(L_u8KeyPadReadValue == 'c' && (L_u8KeyPadLastValue != L_u8KeyPadReadValue) )
			{
				/* clear everything */
				xQueueReset(xQueueInputOperations);
				xQueueReset(xQueueInputNumbers);
				lcd_clear();
				lcd_put_cur(0, 0);

			}/* For Long press Button */
			else if( (L_u8KeyPadLastValue == L_u8KeyPadReadValue) && L_u8KeyPadReadValue >= '0' && L_u8KeyPadReadValue <= '9')
			{
				L_u8CountPress ++;
				if(L_u8CountPress >= 20)
				{
					L_u8CountPress -=4;

					/* read this num Notify */
					xTaskNotify(LCDTaskHandle,L_u8KeyPadReadValue,eSetValueWithOverwrite);
				}

			}
			else if(L_u8KeyPadLastValue != L_u8KeyPadReadValue)
			{
				L_u8KeyPadLastValue  = L_u8KeyPadReadValue;
				L_u8CountPress = 0;
				xTaskNotify(LCDTaskHandle,(uint32_t)L_u8KeyPadReadValue,eSetValueWithOverwrite);
			}
		}
		else
		{
			L_u8CountPress = 0;
			L_u8KeyPadLastValue  = L_u8KeyPadReadValue;
		}

		vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(20) );

	}
}

void LCDTaskHandler(void * Parameters)
{
	uint8_t ulNotifiedValue ;
	static uint8_t L_u8OpFlag=0 , L_u8Negative=0;
	char L_pu8String[50];

	int32_t L_i32NUM = 0;
	while(1)
	{
		xTaskNotifyWait(0,0,(uint32_t*)&ulNotifiedValue,portMAX_DELAY);

		snprintf(L_pu8String, 50, "LCD Print %c\n", ulNotifiedValue);
		SEGGER_SYSVIEW_PrintfTarget(L_pu8String);

		lcd_send_data(ulNotifiedValue);

		if( ulNotifiedValue >= '0' && ulNotifiedValue <= '9')
		{
			L_i32NUM = (L_i32NUM*10) + (ulNotifiedValue-'0');
		}
		else
		{
			if (L_u8Negative)
			{
				L_i32NUM*=(-1);
				L_u8Negative = 0;
			}
			xQueueSendToFront(xQueueInputNumbers, &L_i32NUM, 0);

			L_i32NUM = 0;

			/* send Notification to calculate Mul or Div first */
			if( L_u8OpFlag  || ( (uxQueueMessagesWaiting(xQueueInputOperations) > 0) && ( ulNotifiedValue == '+' || ulNotifiedValue == '-' ) )  )
			{
				/**/
				xTaskNotify(CalculationTaskHandle,0,eSetValueWithOverwrite);
				L_u8OpFlag = 0 ;
			}

			if( ulNotifiedValue == '*' || ulNotifiedValue == '/')
			{
				L_u8OpFlag = 1;
			}
			else if( ulNotifiedValue == '-')
			{
				ulNotifiedValue = '+';
				L_u8Negative = 1;
			}
			else if (ulNotifiedValue == '=')
			{
				/* stop and start calculations over all Queue */
				xTaskNotify(CalculationTaskHandle,1,eSetValueWithOverwrite);
				ulNotifiedValue=0;

			}

			xQueueSendToFront(xQueueInputOperations, &ulNotifiedValue, 0);

		}
	}
}

void CalculationTaskHandler(void * Parameters)
{
	uint8_t ulNotifiedValue , Operation;
	int32_t N1,N2;

	char Lcd_string[10];

	while(1)
	{
		xTaskNotifyWait(0,0,(uint32_t*)&ulNotifiedValue,portMAX_DELAY);

		/* check notification Value */
		if(ulNotifiedValue == 0 )
		{
			/* Do one operation */
			xQueueReceive(xQueueInputNumbers, &N2,0);
			xQueueReceive(xQueueInputNumbers, &N1,0);
			xQueueReceive(xQueueInputOperations, &Operation,0);

			switch(Operation)
			{
			case '*': N1 *= N2; break;
			case '/': N1 /= N2; break;
			case '+': N1 += N2; break;
			case '-': N1 -= N2; break;
			default: break;
			}
			xQueueSendToFront(xQueueInputNumbers, &N1, 0);

		}
		else
		{
			while(uxQueueMessagesWaiting(xQueueInputOperations) > 0)
			{
				/* Do one operation */
				xQueueReceive(xQueueInputNumbers, &N2,0);
				xQueueReceive(xQueueInputNumbers, &N1,0);
				xQueueReceive(xQueueInputOperations, &Operation,0);

				switch(Operation)
				{
				case '*': N1 *= N2; break;
				case '/': N1 /= N2; break;
				case '+': N1 += N2; break;
				case '-': N1 -= N2; break;
				default: break;
				}
				xQueueSendToFront(xQueueInputNumbers, &N1, 0);

			}
			xQueueReset(xQueueInputOperations);
			xQueueReset(xQueueInputNumbers);
			/* receive Last Item in Queue and display it on LCD */
			itoa(N1,Lcd_string,10);
			SEGGER_SYSVIEW_PrintfTarget("result is");
			SEGGER_SYSVIEW_PrintfTarget(Lcd_string);
			lcd_put_cur(1,8);
			lcd_send_data('=');
			lcd_send_string(Lcd_string);

		}

	}
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
