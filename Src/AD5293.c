#include "AD5293.h"
#include "stm32l151xc.h"

void AD5293_Reset_Hardware(void)
{
	//PE9 low to high
	
}
void AD5293_Reset_Software(void)
{
	
}

void AD5293_Set_Value(uint8_t value)
{

}

void AD5293_Init(void)
{
	HAL_GPIO_WritePin(GPIOE,0x0200U,0); //PE9
	//HAL_GPIO_WritePin(GPIOE,0x0400U,1); //PE10
}
