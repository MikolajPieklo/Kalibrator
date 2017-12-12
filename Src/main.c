/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "stdint.h"
#include "Modbus.h"
#include "AD5293.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

uint8_t SPI1_Data_Received;
uint8_t spi_message[2] ={0x04,0xAA} ;
uint8_t AD5293_SPI_Enable[2]= {0x18,0xFF};
uint8_t AD5293_SPI_Reset[2]={0x10,0xFB};
uint8_t Flaga_ADC = 0;
volatile uint8_t licznik_TIM=0;
volatile bool Flaga_TIM=false;
uint16_t PomiarADC[4];
float NapiecieADC[4];
float RealADC[4];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
 if(htim->Instance == TIM10){ // Je¿eli przerwanie pochodzi od timera 10
 HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_0);
 if(Flaga_TIM==true)
 {
	if(licznik_TIM==20){
		Flaga_TIM=false;licznik_TIM=0;MX_TIM10_Init();}

	else
		licznik_TIM++;
 }
 }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {


	HAL_SPI_Receive_IT(&hspi1, &SPI1_Data_Received, 8); // Ponowne wlaczenie nasluchiwania
}

/*
			if(UART1_Data_Received[3]==4)//Modbus_Register_Reset_Software)
			{
				spi_message[0]=0x10;
				spi_message[1]=0x00;

			}

			if(UART1_Data_Received[3]==6)//Modbus_Register_SetValue_Decimal)
			{

				//Set_Value=Set_Value + (Set_Value_f/100);
				//Result = (uint16_t)(1024*Set_Value-50.176)/9.951;
				/*if(Result>0xFF)
				{
					spi_message[0]=(Result>>8);
					spi_message[0]&=0x03;
					spi_message[0]|=0x04;
					spi_message[1]=(Result&0xFF);
				}
				else
				{
					spi_message[0]=0x00;
					spi_message[0]|=0x04;
					spi_message[1]=(Result&0xFF);
				}
			/*}

			if(UART1_Data_Received[3]==12)//Modbus_Register_GetValue)
			{
				spi_message[0]=0x08;
				spi_message[1]=0xFF;

			}
		}
	}
}*/

void HAL_GPIO_EXTI_Callback(uint16_t PIN)
{
	if(PIN==GPIO_PIN_10)
	{
		Flaga_ADC=1;
	}
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM10_Init();
  MX_ADC_Init();

  /* USER CODE BEGIN 2 */
  	HAL_UART_Receive_DMA(&huart1,&Modbus_Buffor_Temp,1);
	HAL_TIM_Base_Start_IT(&htim10);
	HAL_ADC_Start_DMA(&hadc, PomiarADC, 3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	//AD5293_Init();

	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	  HAL_Delay(50);
	  HAL_SPI_Transmit(&hspi1, AD5293_SPI_Enable, 2, 0);
	  HAL_Delay(50);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
	  HAL_Delay(50);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
	  HAL_Delay(50);
	  spi_message[0]=0x04;spi_message[1]=0x00;
	  HAL_SPI_Transmit(&hspi1, spi_message, 2, 0);
	  HAL_Delay(50);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOE,POT_RES_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);


	  while (1)
	  {

		Modbus_Main();
		Kalibrator_zadanie();

		PomiarADC[0];
		volatile uint8_t Data[2];
		Data[0]=0x07;
		Data[1]=0xEF;

		/*HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //CS
		HAL_Delay(50);
		HAL_SPI_Transmit(&hspi1,Data,2,100);
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);*/
		uint16_t* p1;

		NapiecieADC[1] = PomiarADC[1]*0.00080566;//(3.3 * PomiarADC[1]) / 4096; //Ref10V
		RealADC[1] = NapiecieADC[1] * 3.4271844;//(NapiecieADC[1] * 141.2) / 41.2;
		p1=&RealADC[1];
		Modbus_Register1[18]=*p1;
		Modbus_Register1[19]=*(p1+1);
		NapiecieADC[2] = PomiarADC[2]*0.00080566;
		RealADC[2] = NapiecieADC[2] * 3.4271844;
		p1=&RealADC[2];
		Modbus_Register1[20]=*p1;
		Modbus_Register1[21]=*(p1+1);


  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enables the Clock Security System 
    */
  HAL_RCC_EnableCSS();

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
