/*
 * Kalibrator.h
 *
 *  Created on: 14.07.2017
 *      Author: mikolajp
 */
#include "stdbool.h"
#include "stdint.h"

void Init_Kalibrator(void);
void Kalibrator_zadanie(void);
void PK_ON_A(void);
void PK_ON_B(void);

uint8_t SPI_Data[2];

struct ADC_struct{
 bool Flaga_ADC;
 uint16_t Pomiar_ADC;
};
