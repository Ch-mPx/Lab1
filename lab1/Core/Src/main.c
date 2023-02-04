/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include<stdio.h>
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
struct Portpin
{
	GPIO_TypeDef* PORT ;
	uint16_t PIN ;
};

struct Portpin R[4] = {
		{GPIOA,GPIO_PIN_10},
		{GPIOB,GPIO_PIN_3},
		{GPIOB,GPIO_PIN_5},
		{GPIOB,GPIO_PIN_4}
};
struct Portpin L[4] = {
		{GPIOA,GPIO_PIN_9},
		{GPIOC,GPIO_PIN_7},
		{GPIOB,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_7}
};

uint16_t ButtonMatrix = 0 ;
uint16_t position = 0 ;
uint16_t data = 0 ;
uint16_t check = 0 ;
char TrueID [11] = {6,4,3,4,0,5,0,0,0,0,9};
char ID [11] = {0} ;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void ReadMatrixButton_1Row();
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
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  static uint32_t timestamp = 0;
	  static uint32_t delay = 20;
	  if(HAL_GetTick() >= timestamp)
	  	  	{
	  	  		timestamp = HAL_GetTick() + delay ;
	  	  		ReadMatrixButton_1Row();
	  	  		if (ButtonMatrix == 8 && data == 0)
	  	  		{
	  	  			ID[position] = 0 ;
	  	  			position += 1 ;
	  	  			data = 1 ;
	  	  		}
	  	  		else if (ButtonMatrix == 4 && data == 0)
	  	  		{
	  	  			ID[position] = 1 ;
	  	  			position += 1 ;
	  	  			data = 1 ;
	  	  		}
	  	  	    else if (ButtonMatrix == 64 && data == 0)
	   	  		{
	  	  		  	ID[position] = 2 ;
	  	  		  	position += 1 ;
	  	  		  	data = 1 ;
	   	  		}
	  	  	    else if (ButtonMatrix == 1024 && data == 0)
	  	  		{
	  	   		  	ID[position] = 3 ;
	  	  		  	position += 1 ;
  	  		  	    data = 1 ;
	  	  		}
	  	  	    else if (ButtonMatrix == 2 && data == 0)
	  	  		{
	  	  		   	ID[position] = 4 ;
	  	  		  	position += 1 ;
	  		  	    data = 1 ;
	  	  		}
	  	  	    else if (ButtonMatrix == 32 && data == 0)
	  	  		{
	  	  		  	ID[position] = 5 ;
	  	  		  	position += 1 ;
	  	  	  	    data = 1 ;
	  	  		}
	  	  	    else if (ButtonMatrix == 512 && data == 0)
	  	   		{
	  	  	  	    ID[position] = 6 ;
	  	  	  	    position += 1 ;
	  	    	    data = 1 ;
 	  	  		}
	  	  	    else if (ButtonMatrix == 1 && data == 0)
	  		  	{
	  		  	    ID[position] = 7 ;
	  		  	  	position += 1 ;
	  	  	  		data = 1 ;
	  		  	}
	  	  	    else if (ButtonMatrix == 16 && data == 0)
	  		  	{
	  		  	    ID[position] = 8 ;
	  		  	  	position += 1 ;
	  	  	  		data = 1 ;
	  		  	}
	  	  	    else if (ButtonMatrix == 256 && data == 0)
	  		  	{
	  		  	    ID[position] = 9 ;
	  		  	    position += 1 ;
	  	  	  		data = 1 ;
	  		  	}
	  	  	    else if (ButtonMatrix == 4096 && data == 0)
	  	  		{
	  	  		  register int j  ;
	  	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  	  		  data = 1 ;
	  	  		  position = 0 ;
	  	  		  for(j = 0;j<11;j++)
	  	  		  {
	  	  			  ID [j] = 0 ;
	  	  		  }
	  	  		}
	  	  	    else if (ButtonMatrix == 8192 && data == 0)
	  	  		{
	  	  	    	 data = 1 ;
	  	  	    	 if(position == 0)
	  	  		  	 {
	  	  	    			ID[10] = 0 ;
	  	  		  	   		position = 10 ;

	  	  		  	 }
	  	  		  	 else if(position > 0)
	  	  		  	 {
	  	  		  		 ID[position-1] = 0 ;
	  	  		  		 position -=1 ;
	  	  		  	 }
	  	  		}
	  	  	    else if (ButtonMatrix == 32768 && data == 0)
	  	  		{
	  	  	    	data = 1 ;
	  	  	    	register i ;
	  	  	    	for(i = 0;i<11;i++)
	  	  	    	{
	  	  	    	  if(ID [i] == TrueID[i])
	  	  	    	  {
	  	  	    	  	  check = 1 ;
	  	  	    	  }
	  	  	    	  else
	  	  	    	  {
	  	  	    	  	  check = 0 ;
	  	  	    	  }
	  	  	    	  	  		}
	  	  	    	if(check == 1)
	  	  	    	{
	  	  	    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  	  	    	}
	  	  	    	else {
	  	  	    		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  	  	    	}
	  	  		}
	  	  		if(ButtonMatrix == 0 && data == 1)
	  	  		{
	  	  			data = 0 ;
	  	  		}
	  	  		if(position == 11)
	  	  		{
	  	  			position = 0;
	  	  		}
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
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|R1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, R2_Pin|R4_Pin|R3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : L4_Pin L1_Pin */
  GPIO_InitStruct.Pin = L4_Pin|L1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : L2_Pin */
  GPIO_InitStruct.Pin = L2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(L2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : R1_Pin */
  GPIO_InitStruct.Pin = R1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(R1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : R2_Pin R4_Pin R3_Pin */
  GPIO_InitStruct.Pin = R2_Pin|R4_Pin|R3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : L3_Pin */
  GPIO_InitStruct.Pin = L3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(L3_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void ReadMatrixButton_1Row(){
	static uint8_t x = 0 ;
	register int i ;
	for(i=0;i<4;i++)
	{
		if(HAL_GPIO_ReadPin(L[i].PORT, L[i].PIN))
		{
			ButtonMatrix &= ~(1<<x*4+i);
		}
		else
		{
			ButtonMatrix |= 1<<(x*4+i);
		}

	}
	//set RX
	HAL_GPIO_WritePin(R[x].PORT, R[x].PIN, 1);
	//Reset RX+1%4
	HAL_GPIO_WritePin(R[(x+1)%4].PORT, R[(x+1)%4].PIN, 0);
	x++;
	x%=4;
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
