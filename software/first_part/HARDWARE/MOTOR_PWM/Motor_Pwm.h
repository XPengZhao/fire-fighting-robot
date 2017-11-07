#ifndef __MOTOR_PWM_H
#define __MOTOR_PWM_H

#define ARR_PWM 9999
#define PSC_PWM 143

#define MotorRight TIM_SetCompare1
#define MotorLeft TIM_SetCompare2

#include "sys.h"

void Wheel_Init(void);

#endif
