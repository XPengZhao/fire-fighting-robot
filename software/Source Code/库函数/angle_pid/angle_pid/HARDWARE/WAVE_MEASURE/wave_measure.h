#ifndef __WAVE_MEASURE_H
#define __WAVE_MEASURE_H

#define ARR_WAVE 4999
#define PSC_WAVE 7199
#define COUNT 5
#include "sys.h"


void Wave_Init(void);
int Get_Distance_Left(void);
int Get_Distance_Right(void);
int Get_Distance_Front(void);
void Get_Distance(void);

#endif
