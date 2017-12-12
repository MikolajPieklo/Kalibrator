/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define UR_OUT_Pin GPIO_PIN_1
#define UR_OUT_GPIO_Port GPIOA
#define REF_10V_Pin GPIO_PIN_2
#define REF_10V_GPIO_Port GPIOA
#define POT_RES_Pin GPIO_PIN_9
#define POT_RES_GPIO_Port GPIOE
#define POT_RDY_Pin GPIO_PIN_10
#define POT_RDY_GPIO_Port GPIOE
#define POT_RDY_EXTI_IRQn EXTI15_10_IRQn
#define SPI_CS_Pin GPIO_PIN_12
#define SPI_CS_GPIO_Port GPIOE
#define Z3_Pin GPIO_PIN_8
#define Z3_GPIO_Port GPIOD
#define Z4_Pin GPIO_PIN_9
#define Z4_GPIO_Port GPIOD
#define Z5_Pin GPIO_PIN_10
#define Z5_GPIO_Port GPIOD
#define Z6_Pin GPIO_PIN_11
#define Z6_GPIO_Port GPIOD
#define Z7_Pin GPIO_PIN_12
#define Z7_GPIO_Port GPIOD
#define PK_ON_A_Pin GPIO_PIN_14
#define PK_ON_A_GPIO_Port GPIOD
#define PK_ON_B_Pin GPIO_PIN_15
#define PK_ON_B_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
