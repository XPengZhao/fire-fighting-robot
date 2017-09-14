#ifndef __PWM_H
#define __PWM_H
#include "sys.h"



void TIM2_PWM_Init(u16 arr,u16 psc);
void forward(void);
void turnright(void);
void turnleft(void);
#endif
