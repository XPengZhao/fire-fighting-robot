#ifndef __WAVE_MEASURE_H
#define __WAVE_MEASURE_H

#define ARR 49999
#define PSC 71
#define COUNT 6

#include "sys.h"

typedef struct
 {
     int front;
     int right;
     int left;
 }Distance;
 
void Wave_Init(void);
void Get_Distance(void);

#endif
