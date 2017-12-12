#include "stdint.h"
#include "stdbool.h"

#define Modbus_Address_Device     0x64
#define Modbus_Function_Write     0x10
#define Modbus_Function_Read      0x03
#define Modbus_Data_OFFSET        0x00
//------------------------------------
//00 Reset_Hardware
//01 Reset_Software -NOK
//02 Shoutdown      -NOK
//03 SPI_Enable

//10 SetValueBinary
//11 SetValueDecimal_Hi  -NOK
//12 SetValueDecimal_Lo  -NOK
//13 GetValueBinary      -NOK
//14 GetValueDecimal_Hi  -NOK
//15 GetValueDecimal_Lo  -NOK
//16 PK_ON_A/PK_ON_B
//17 SetValueTest
//18 ADC_Channel_Hi (float)
//19 ADC_Channel_Lo (float)
//20 ADC_+10V_Hi    (float)
//21 ADC_+10V_Lo    (float)
//22 Temp_Hi        (float)
//23 Temp_Lo        (float)


uint16_t Modbus_Register1[100];

void Modbus_Main(void);
bool Modbus_Flaga_DMA_Rx;
//uint8_t Modbus_Counter_DMA_Tx;
uint8_t Modbus_Counter_DMA_Tx_index;

uint8_t Modbus_Buffor_Temp;
uint8_t Modbus_Buffor_Tab[20];
uint8_t Modbus_index;

uint16_t CRC16 (const uint8_t *nData, uint16_t wLength);
void     ModbusWrite(uint8_t* SendBuffor,uint8_t len);
