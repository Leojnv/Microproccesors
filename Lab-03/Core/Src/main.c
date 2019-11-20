/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ST_INICIO 0
#define ST_RESET 1
#define ST_START 2
#define ST_RANDOM_TIME 3
#define ST_WAIT_STOP 4
#define ST_DISPLAY 5
#define ST_TIMEOUT 6
#define ST_CHEAT 7
#define DELAY 20
#define GET_MILISECONDS HAL_GetTick()

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim11;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct {
	int delay;              // Delay in order to debounce
	int counter;            // Counter that will help to determine stable state

	bool state;             // Stable state
	bool state_raw;         // Raw input
	bool edge_rise;         // For Pull-Up
	bool edge_fall;         // For Pull-Down
} Button;
int SegmentTable[21] = {
		0x3F, /* 0 */
		0x06, /* 1 */
		0x5B, /* 2 */
		0x4F, /* 3 */
		0x66, /* 4 */
		0x6D, /* 5 */
		0x7D, /* 6 */
		0x07, /* 7 */
		0x7F, /* 8 */
		0x6F, /* 9 */
		0x77, /* A */
		0x7C, /* B */
		0x39, /* C */
		0x5E, /* D */
		0x79, /* E */
		0x71, /* F */
		0x76, /* H */
		0x00, /* OFF */
		0x38, /* L */
		0x37, /* n */
		0x73  /* P */
};
Button b_start;
Button b_clear;
void debounce(Button *button, _Bool entry)
{
	button->edge_rise = false;
	button->edge_fall = false;
	button->state_raw = entry;

	button->counter++;

	if(button->state == button->state_raw)
		button->counter = 0;

	if(button->counter >= button->delay) {
		button->counter = 0;
		if(button->state_raw) {
			button->state = button->state_raw;
			button->edge_rise = true;
		} else {
			button->state = button->state_raw;
			button->edge_fall = true;
		}
	}
}
int getRiseEdge(Button *btn)
{
	return btn->edge_rise;
}
void write_number(int n, uint8_t *current_display, uint16_t *st)
{
	uint16_t ct = GET_MILISECONDS;
	if (ct >= (*st + 1))
	{
		int aux = 0;

		// Selecting the corresponding display
		uint8_t T0 = (*current_display == 0);
		uint8_t T1 = (*current_display == 1);
		uint8_t T2 = (*current_display == 2);
		uint8_t T3 = (*current_display == 3);

		GPIOE->ODR &= ~(0xFF << 8);								// Clearing 7 Segment Display
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, T0);				// Enable / Disable TRANS_DIG_0
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, T1);				// Enable / Disable TRANS_DIG_1
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, T2);				// Enable / Disable TRANS_DIG_2
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, T3);				// Enable / Disable TRANS_DIG_3

		switch (*current_display) {
		case 0:
			aux = (n/1) % 10;									// Taking unit of number
			GPIOE->ODR |= (SegmentTable[aux] << 8);				// Writing output to segments
			break;
		case 1:
			aux = (n/10) % 10;									// Taking dozen of number
			GPIOE->ODR |= (SegmentTable[aux] << 8);				// Writing output to segments
			break;
		case 2:
			aux = (n/100) % 10;									// Taking hundred of number
			GPIOE->ODR |= (SegmentTable[aux] << 8);				// Writing output to segments
			break;
		case 3:
			aux = (n/1000) % 10;								// Taking thousandth of number
			GPIOE->ODR |= (SegmentTable[aux] << 8) + (1<<15);	// Writing output to segments with a point
			break;
		default:
			break;
		}
		*st = ct;
		*current_display >= 3 ? *current_display = 0 : (*current_display)++;
	}

}
void write_hi(uint8_t *current_display, uint16_t *st)
{
	uint16_t ct = GET_MILISECONDS;
	if (ct >= (*st + 1))
	{
		// Selecting the corresponding display
		uint8_t T0 = (*current_display == 0);
		uint8_t T1 = (*current_display == 1);
		uint8_t T2 = (*current_display == 2);
		uint8_t T3 = (*current_display == 3);

		GPIOE->ODR &= ~(0xFF << 8);								// Clearing 7 Segment Display
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, T0);				// Enable / Disable TRANS_DIG_0
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, T1);				// Enable / Disable TRANS_DIG_1
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, T2);				// Enable / Disable TRANS_DIG_2
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, T3);				// Enable / Disable TRANS_DIG_3

		switch (*current_display) {
		case 0:
			GPIOE->ODR |= (SegmentTable[17] << 8);			// Writing output blank
			break;
		case 1:
			GPIOE->ODR |= (SegmentTable[1] << 8);			// Writing output I
			break;
		case 2:
			GPIOE->ODR |= (SegmentTable[16] << 8);			// Writing output H
			break;
		case 3:
			GPIOE->ODR |= (SegmentTable[17] << 8);			// Writing output blank
			break;
		default:
			break;
		}
		*st = ct;
		*current_display >= 3 ? *current_display = 0 : (*current_display)++;
	}

}
void write_blank(uint8_t *current_display, uint16_t *st)
{
	uint16_t ct = GET_MILISECONDS;
	if (ct >= (*st + 1))
	{
		// Selecting the corresponding display
		uint8_t T0 = (*current_display == 0);
		uint8_t T1 = (*current_display == 1);
		uint8_t T2 = (*current_display == 2);
		uint8_t T3 = (*current_display == 3);

		GPIOE->ODR &= ~(0xFF << 8);								// Clearing 7 Segment Display
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, T0);				// Enable / Disable TRANS_DIG_0
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, T1);				// Enable / Disable TRANS_DIG_1
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, T2);				// Enable / Disable TRANS_DIG_2
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, T3);				// Enable / Disable TRANS_DIG_3

		switch (*current_display) {
		case 0:
			GPIOE->ODR |= (SegmentTable[17] << 8);			// Writing output
			break;
		case 1:
			GPIOE->ODR |= (SegmentTable[17] << 8);			// Writing output
			break;
		case 2:
			GPIOE->ODR |= (SegmentTable[17] << 8);			// Writing output
			break;
		case 3:
			GPIOE->ODR |= (SegmentTable[17] << 8);			// Writing output
			break;
		default:
			break;
		}
		*st = ct;
		*current_display >= 3 ? *current_display = 0 : (*current_display)++;
	}

}
void write_timeout(uint8_t *current_display, uint16_t *st)
{
	uint16_t ct = GET_MILISECONDS;
	if (ct >= (*st + 1))
	{
		// Selecting the corresponding display
		uint8_t T0 = (*current_display == 0);
		uint8_t T1 = (*current_display == 1);
		uint8_t T2 = (*current_display == 2);
		uint8_t T3 = (*current_display == 3);

		GPIOE->ODR &= ~(0xFF << 8);								// Clearing 7 Segment Display
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, T0);				// Enable / Disable TRANS_DIG_0
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, T1);				// Enable / Disable TRANS_DIG_1
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, T2);				// Enable / Disable TRANS_DIG_2
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, T3);				// Enable / Disable TRANS_DIG_3

		switch (*current_display) {
		case 0:
			GPIOE->ODR |= (SegmentTable[18] << 8);			// Writing output L
			break;
		case 1:
			GPIOE->ODR |= (SegmentTable[1] << 8);			// Writing output I
			break;
		case 2:
			GPIOE->ODR |= (SegmentTable[10] << 8);			// Writing output A
			break;
		case 3:
			GPIOE->ODR |= (SegmentTable[15] << 8);			// Writing output F
			break;
		default:
			break;
		}
		*st = ct;
		*current_display >= 3 ? *current_display = 0 : (*current_display)++;
	}

}
void write_nope(uint8_t *current_display, uint16_t *st)
{
	uint16_t ct = GET_MILISECONDS;
	if (ct >= (*st + 1))
	{
		// Selecting the corresponding display
		uint8_t T0 = (*current_display == 0);
		uint8_t T1 = (*current_display == 1);
		uint8_t T2 = (*current_display == 2);
		uint8_t T3 = (*current_display == 3);

		GPIOE->ODR &= ~(0xFF << 8);								// Clearing 7 Segment Display
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, T0);				// Enable / Disable TRANS_DIG_0
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, T1);				// Enable / Disable TRANS_DIG_1
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, T2);				// Enable / Disable TRANS_DIG_2
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, T3);				// Enable / Disable TRANS_DIG_3

		switch (*current_display) {
		case 0:
			GPIOE->ODR |= (SegmentTable[14] << 8);			// Writing output E
			break;
		case 1:
			GPIOE->ODR |= (SegmentTable[20] << 8);			// Writing output P
			break;
		case 2:
			GPIOE->ODR |= (SegmentTable[0] << 8);			// Writing output O
			break;
		case 3:
			GPIOE->ODR |= (SegmentTable[19] << 8);			// Writing output N
			break;
		default:
			break;
		}
		*st = ct;
		*current_display >= 3 ? *current_display = 0 : (*current_display)++;
	}

}
void turn_off_LED()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
}
void turn_on_LED()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
}
_Bool read_LED()
{
	return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
}
_Bool read_start()
{
	return getRiseEdge(&b_start);
}
_Bool read_clear()
{
	return getRiseEdge(&b_clear);
}
_Bool read_stop()
{
	return HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5);
}
void reset_count()
{
	// Resetting counter of TIM11
	HAL_TIM_IC_Stop(&htim11, TIM_CHANNEL_1);
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	HAL_TIM_IC_Start(&htim11, TIM_CHANNEL_1);
}
void initButton(Button *button, _Bool initialState)
{
	button->delay = DELAY;
	button->counter = 0;
	button->state = initialState;
	button->state_raw = initialState;
	button->edge_rise = false;
	button->edge_fall = false;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_IC_Start(&htim11, TIM_CHANNEL_1);
	srand(time(NULL));


	uint8_t current_display = 0;
	uint8_t state = ST_INICIO;
	uint16_t start_time = GET_MILISECONDS;
	uint16_t random_time = 0;
	uint16_t current_time = 0;
	uint16_t start_wait_time = 0;
	uint16_t led_time_on = 0;
	uint16_t led_time_off = 0;

	// Start and clear button
	initButton(&b_start, 0);
	initButton(&b_clear, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		debounce(&b_start, HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6));
		debounce(&b_clear, HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7));

		if(read_clear())
		{
			state = ST_RESET;
			led_time_on = 0;
		}

		switch (state) {

		case ST_INICIO:

			write_hi(&current_display, &start_time);
			turn_off_LED();
			state = ST_RESET;
			break;

		case ST_RESET:

			write_hi(&current_display, &start_time);
			turn_off_LED();
			if(read_start() != 0)
			{
				state = ST_START;
			}
			break;

		case ST_START:

			write_blank(&current_display, &start_time);
			state = ST_RANDOM_TIME;
			start_time = GET_MILISECONDS;
			break;

		case ST_RANDOM_TIME:

			state = ST_WAIT_STOP;
			// Generating random number
			random_time = (1 + ( (float)(rand() ) / ( (float)(RAND_MAX/2) ) ))*1000;
			start_wait_time = GET_MILISECONDS;
			break;

		case ST_WAIT_STOP:

			// While the LED is off, turn off screen
			if(!read_LED())
				write_blank(&current_display, &start_time);

			current_time = GET_MILISECONDS;
			// If the random time between 1 and 3 seconds have passed, turn on LED,
			// reset TIM counter and the time where the LED got turned on
			if (current_time >= (start_wait_time + random_time))
			{
				turn_on_LED();
				if(led_time_on == 0)
				{
					led_time_on = GET_MILISECONDS;
					reset_count();
				}
			}
			if (read_LED())
			{	// While the LED is on, show counter value in seconds
				// 0.25 milliseconds = 4khz
				write_number( (TIM11->CNT)*0.25, &current_display, &start_time);
			}
			if(read_stop() && read_LED())
			{
				led_time_off = GET_MILISECONDS;
				state = ST_DISPLAY;
			}
			if (GET_MILISECONDS >= (led_time_on + 2000) && read_LED())
			{
				// If 2 seconds have passed since LED turned on, go to TIMEOUT state
				state = ST_TIMEOUT;
			}
			if (read_LED() == 0 && read_stop()) {
				// If the button was pressed before the LED being turned on, go to CHEAT state
				state = ST_CHEAT;
			}
			break;

		case ST_DISPLAY:

			turn_off_LED();
			// Write the measured time
			write_number( (led_time_off - led_time_on), &current_display, &start_time);
			break;

		case ST_TIMEOUT:

			turn_off_LED();
			// Write FAIL on screen
			write_timeout(&current_display, &start_time);
			break;

		case ST_CHEAT:

			turn_off_LED();
			// Write NOPE on screen
			write_nope(&current_display, &start_time);
			break;

		default:
			break;
		}

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
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 54000-1;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 20000;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim11, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PF3 PF5 PF10 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PE8 PE9 PE10 PE11 
                           PE12 PE13 PE14 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
