#ifndef __WAVE_MEASURE_H
#define __WAVE_MEASURE_H

#define ARR_WAVE 49999
#define PSC_WAVE 71
#include "sys.h"

u8  TIM3CH3_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM3CH3_CAPTURE_VAL;	//输入捕获值

int Wave_Init(void);