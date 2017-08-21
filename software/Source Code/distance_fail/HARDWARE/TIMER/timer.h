#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"


void TIM2_Int_Init(u16 arr,u16 psc); 
uint8_t Level_Judge(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
