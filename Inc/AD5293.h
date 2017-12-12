#include "stdint.h"

uint16_t AD5293_Value;

void AD5293_Reset_Hardware(void);
void AD5293_Reset_Software(void);
void AD5293_Shoutdown();


void AD5293_Set_Value(uint8_t value);
uint8_t AD5293_Get_Value();
void AD5293_Init(void);
