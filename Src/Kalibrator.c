/*
 * Kalibrator.c
 *
 *  Created on: 14.07.2017
 *      Author: mikolajp
 */

#include "Kalibrator.h"
#include "stm32l151xc.h"
#include "Modbus.h"
#include "spi.h"
#include "gpio.h"
//#include "stm32l1xx_hal_gpio.h"

void PK_ON_A(void)
{
	MX_GPIO_Init();
	HAL_GPIO_WritePin(PK_ON_A_GPIO_Port,PK_ON_A_Pin,1); //PD14
	HAL_GPIO_WritePin(PK_ON_B_GPIO_Port,PK_ON_B_Pin,0); //PD15
	HAL_Delay(10);
	HAL_GPIO_DeInit(PK_ON_A_GPIO_Port,PK_ON_A_Pin);
	HAL_GPIO_DeInit(PK_ON_B_GPIO_Port,PK_ON_B_Pin);
}
void PK_ON_B(void)
{
	MX_GPIO_Init();
	HAL_GPIO_WritePin(PK_ON_A_GPIO_Port,PK_ON_A_Pin,0); //PD14
	HAL_GPIO_WritePin(PK_ON_B_GPIO_Port,PK_ON_B_Pin,1); //PD15
	HAL_Delay(10);
	HAL_GPIO_DeInit(PK_ON_A_GPIO_Port,PK_ON_A_Pin);
	HAL_GPIO_DeInit(PK_ON_B_GPIO_Port,PK_ON_B_Pin);
}

void Init_Kalibrator(void)
{

}

void Kalibrator_zadanie(void)
{
	if(Modbus_Register1[0]!=0)
	{
		HAL_GPIO_WritePin(GPIOE,POT_RES_Pin,GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(GPIOE,POT_RES_Pin,GPIO_PIN_RESET);
		Modbus_Register1[0]=0;

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(50);
		uint8_t Data[2];
		Data[0]=0x18;
		Data[1]=0xFF;
		HAL_SPI_Transmit(&hspi1, Data, 2, 0);
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
	}

	if(Modbus_Register1[3]!=0) //Enable SPI_Enable
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(50);
		uint8_t Data[2];
		Data[0]=0x18;
		Data[1]=0xFF;
		HAL_SPI_Transmit(&hspi1, Data, 2, 0);
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
		Modbus_Register1[3]=0;
	}

	if(Modbus_Register1[10]!=Modbus_Register1[30])//SetValueBinary  10
	{
		SPI_Data[0]=((Modbus_Register1[10])>>8)|0x04;
		SPI_Data[1]=((Modbus_Register1[10])&0xFF);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //CS
		HAL_Delay(50);
		HAL_SPI_Transmit(&hspi1,SPI_Data,2,100);
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
		Modbus_Register1[30]=Modbus_Register1[10];
	}

	if(Modbus_Register1[11]!=Modbus_Register1[31])//SetValueDecimal  11,12
	{
		SPI_Data[0]=((Modbus_Register1[10])>>8)|0x04;
		SPI_Data[1]=((Modbus_Register1[10])&0xFF);

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //CS
		HAL_Delay(50);
		HAL_SPI_Transmit(&hspi1,SPI_Data,2,100);
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
		Modbus_Register1[31]=Modbus_Register1[11];
		Modbus_Register1[32]=Modbus_Register1[12];
	}

	//GetValueBinary 13
	//GetValueDecimal 14 15

	if(Modbus_Register1[16]!=Modbus_Register1[36]){
		if(Modbus_Register1[16]==0)PK_ON_A();
		if(Modbus_Register1[16]!=0)PK_ON_B();
		Modbus_Register1[36]=Modbus_Register1[16];
	}

	if(Modbus_Register1[17]!=Modbus_Register1[37])
	{
		uint8_t Data[2];

		switch(Modbus_Register1[17])
		{
		case 00:   Data[0]=0x04; Data[1]=0x00;break;
		case 250:  Data[0]=0x04; Data[1]=0x15;break;
		case 500:  Data[0]=0x04; Data[1]=0x2F;break;
		case 750:  Data[0]=0x04; Data[1]=0x49;break;
		case 1000: Data[0]=0x04; Data[1]=0x64;break;
		case 1250: Data[0]=0x04; Data[1]=0x7E;break;
		case 1500: Data[0]=0x04; Data[1]=0x99;break;
		case 1750: Data[0]=0x04; Data[1]=0xB4;break;
		case 2000: Data[0]=0x04; Data[1]=0xCF;break;
		case 2250: Data[0]=0x04; Data[1]=0xEA;break;
		case 2500: Data[0]=0x05; Data[1]=0x05;break;
		case 2750: Data[0]=0x05; Data[1]=0x20;break;
		case 3000: Data[0]=0x05; Data[1]=0x3C;break;
		case 3250: Data[0]=0x05; Data[1]=0x56;break;
		case 3500: Data[0]=0x05; Data[1]=0x71;break;
		case 3750: Data[0]=0x05; Data[1]=0x8C;break;
		case 4000: Data[0]=0x05; Data[1]=0xA9;break;
		case 4250: Data[0]=0x05; Data[1]=0xC3;break;
		case 4500: Data[0]=0x05; Data[1]=0xDE;break;
		case 4750: Data[0]=0x05; Data[1]=0xF9;break;
		case 5000: Data[0]=0x06; Data[1]=0x14;break;
		case 5250: Data[0]=0x06; Data[1]=0x2E;break;
		case 5500: Data[0]=0x06; Data[1]=0x49;break;
		case 5750: Data[0]=0x06; Data[1]=0x63;break;
		case 6000: Data[0]=0x06; Data[1]=0x7E;break;
		case 6250: Data[0]=0x06; Data[1]=0x98;break;
		case 6500: Data[0]=0x06; Data[1]=0xB2;break;
		case 6750: Data[0]=0x06; Data[1]=0xCB;break;
		case 7000: Data[0]=0x06; Data[1]=0xE5;break;
		case 7250: Data[0]=0x06; Data[1]=0xFE;break;
		case 7500: Data[0]=0x07; Data[1]=0x17;break;
		case 7750: Data[0]=0x07; Data[1]=0x30;break;
		case 8000: Data[0]=0x07; Data[1]=0x49;break;
		case 8250: Data[0]=0x07; Data[1]=0x62;break;
		case 8500: Data[0]=0x07; Data[1]=0x7A;break;
		case 8750: Data[0]=0x07; Data[1]=0x92;break;
		case 9000: Data[0]=0x07; Data[1]=0xAA;break;
		case 9250: Data[0]=0x07; Data[1]=0xC1;break;
		case 9500: Data[0]=0x07; Data[1]=0xD8;break;
		case 9750: Data[0]=0x07; Data[1]=0xEF;break;
		default:  Data[0]=0x04; Data[1]=0x00;break;
		}

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //CS
		HAL_Delay(50);
		HAL_SPI_Transmit(&hspi1,Data,2,100);
		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
		Modbus_Register1[37]=Modbus_Register1[17];

	}
}


