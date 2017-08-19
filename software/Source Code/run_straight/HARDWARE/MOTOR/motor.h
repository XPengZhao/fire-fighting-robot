#ifndef __Motor_H
#define __Motor_H	 
#include "sys.h"
#define Motor0 PCout(0)	// PC0
#define Motor1 PCout(1)	// PC1

void Motor_Init(void); //初始化
void Motor_Run(int distance);

		 				    

#endif
