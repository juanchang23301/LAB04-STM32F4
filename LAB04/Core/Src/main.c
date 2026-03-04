/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stdint.h"
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t Player_1 = 0;
uint8_t Player_2 = 0;

uint32_t timer_5s = 0;
uint32_t timer_count = 0;
uint8_t timer_init= 0;
uint8_t timer_disp = 0;
uint8_t Block_Push_Player = 0;

uint8_t hex_table[16] = {
    0x3F, // 0 → 0b00111111 → a,b,c,d,e,f
    0x06, // 1 → 0b00000110 → b,c
    0x5B, // 2 → 0b01011011 → a,b,d,e,g
    0x4F, // 3 → 0b01001111 → a,b,c,d,g
    0x66, // 4 → 0b01100110 → b,c,f,g
    0x6D, // 5 → 0b01101101 → a,c,d,f,g
    0x7D, // 6 → 0b01111101 → a,c,d,e,f,g
    0x07, // 7 → 0b00000111 → a,b,c
    0x7F, // 8 → 0b01111111 → a,b,c,d,e,f,g
    0x6F, // 9 → 0b01101111 → a,b,c,d,f,g
    0x77, // A → 0b01110111 → a,b,c,e,f,g
    0x7C, // B → 0b01111100 → c,d,e,f,g
    0x39, // C → 0b00111001 → a,d,e,f
    0x5E, // D → 0b01011110 → b,c,d,e,g
    0x79, // E → 0b01111001 → a,d,e,f,g
    0x71  // F → 0b01110001 → a,e,f,g
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void Display_Show(uint8_t valor) {

    uint8_t seg = hex_table[valor];

    HAL_GPIO_WritePin(GPIOC, Disp_A_Pin, (seg >> 0) & 1);
    HAL_GPIO_WritePin(GPIOC, Disp_B_Pin, (seg >> 1) & 1);
    HAL_GPIO_WritePin(GPIOA, Disp_C_Pin, (seg >> 2) & 1);
    HAL_GPIO_WritePin(GPIOB, Disp_D_Pin, (seg >> 3) & 1);
    HAL_GPIO_WritePin(GPIOB, Disp_E_Pin, (seg >> 4) & 1);
    HAL_GPIO_WritePin(GPIOB, Disp_F_Pin, (seg >> 5) & 1);
    HAL_GPIO_WritePin(GPIOA, Disp_G_Pin, (seg >> 6) & 1);
}
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (timer_init == 1) {
		  timer_5s = HAL_GetTick() - timer_count;
		  timer_disp = 5 - (timer_5s/1000);
		  Display_Show(timer_disp);

		  if (timer_5s >= 5000) {
			  timer_init = 0;
			  timer_disp = 0;
			  Block_Push_Player = 1;
		}

	}

	  if (Player_2 < 5){
		  switch (Player_1) {
	      case 1:
	          HAL_GPIO_WritePin(GPIOA, P1_Led1_Pin, GPIO_PIN_SET);
	          break;
	      case 2:
	          HAL_GPIO_WritePin(GPIOA, P1_Led2_Pin, GPIO_PIN_SET);
	          break;
	      case 3:
	          HAL_GPIO_WritePin(GPIOB, P1_Led4_Pin, GPIO_PIN_SET);
	          break;
	      case 4:
	          HAL_GPIO_WritePin(GPIOB, P1_Led3_Pin, GPIO_PIN_SET);
	          break;
	      default:
	          break;
		  }
	  }else if(Player_2 >= 5 && Player_1 < 5){

          HAL_GPIO_WritePin(GPIOA, P1_Led1_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOA, P1_Led2_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOB, P1_Led3_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOB, P1_Led4_Pin, GPIO_PIN_RESET);
          Display_Show(2);
	  }


	  if (Player_1 < 5){
		  switch (Player_2) {
		 	      case 1:
		 	          HAL_GPIO_WritePin(GPIOA, P2_Led1_Pin, GPIO_PIN_SET);
		 	          break;
		 	      case 2:
		 	    	  HAL_GPIO_WritePin(P2_Led2_GPIO_Port, P2_Led2_Pin, GPIO_PIN_SET);
		 	          break;
		 	      case 3:
		 	          HAL_GPIO_WritePin(GPIOB, P2_Led3_Pin, GPIO_PIN_SET);
		 	          break;
		 	      case 4:
		 	          HAL_GPIO_WritePin(GPIOA, P2_Led4_Pin, GPIO_PIN_SET);

		 	          break;
		 	      default:
		 	          break;
		 	  }
	 	  }else if(Player_1 >= 5 && Player_2 < 5){

	 		    HAL_GPIO_WritePin(GPIOA, P2_Led1_Pin, GPIO_PIN_RESET);
	 		    HAL_GPIO_WritePin(P2_Led2_GPIO_Port, P2_Led2_Pin, GPIO_PIN_RESET);
	 		    HAL_GPIO_WritePin(GPIOB, P2_Led3_Pin, GPIO_PIN_RESET);
	 		    HAL_GPIO_WritePin(GPIOA, P2_Led4_Pin, GPIO_PIN_RESET);
	 		    Display_Show(1);
	 	  }





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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOC, Disp_A_Pin|Disp_B_Pin|P2_Led2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, P1_Led2_Pin|P1_Led1_Pin|P2_Led4_Pin|Disp_G_Pin
                          |P2_Led1_Pin|Disp_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Disp_F_Pin|Disp_E_Pin|Disp_D_Pin|P2_Led3_Pin
                          |P1_Led3_Pin|P1_Led4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Disp_A_Pin Disp_B_Pin P2_Led2_Pin */
  GPIO_InitStruct.Pin = Disp_A_Pin|Disp_B_Pin|P2_Led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Push_P1_Pin */
  GPIO_InitStruct.Pin = Push_P1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Push_P1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Push_P2_Pin */
  GPIO_InitStruct.Pin = Push_P2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Push_P2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Push_Timer_Pin */
  GPIO_InitStruct.Pin = Push_Timer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Push_Timer_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : P1_Led2_Pin P1_Led1_Pin P2_Led4_Pin Disp_G_Pin
                           P2_Led1_Pin Disp_C_Pin */
  GPIO_InitStruct.Pin = P1_Led2_Pin|P1_Led1_Pin|P2_Led4_Pin|Disp_G_Pin
                          |P2_Led1_Pin|Disp_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Disp_F_Pin Disp_E_Pin Disp_D_Pin P2_Led3_Pin
                           P1_Led3_Pin P1_Led4_Pin */
  GPIO_InitStruct.Pin = Disp_F_Pin|Disp_E_Pin|Disp_D_Pin|P2_Led3_Pin
                          |P1_Led3_Pin|P1_Led4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if(GPIO_Pin == Push_Timer_Pin){
		timer_count = HAL_GetTick();
		timer_init = 1;
		timer_disp = 5;
		Player_1 = 0;
		Player_2 = 0;
        HAL_GPIO_WritePin(GPIOA, P1_Led1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, P1_Led2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, P1_Led3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, P1_Led4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, P2_Led1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(P2_Led2_GPIO_Port, P2_Led2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, P2_Led3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, P2_Led4_Pin, GPIO_PIN_RESET);

	}if(Block_Push_Player == 1){
		if (GPIO_Pin == Push_P1_Pin) {
			Player_1++;
		} else if (GPIO_Pin == Push_P2_Pin) {
			Player_2++;
		}
	}
}

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
#ifdef USE_FULL_ASSERT
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
