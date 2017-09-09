#include "delay.h"
#include "Motor_Turn.h"

/**
  * ----------------------------------------------------------------------------
  * 通过一轮前进，一轮后退的方式转弯
  * 通过调整 "Motor_Turn.h" 中的时间来调整转动角度
  */
  
void Turn_Left(void)
{
    delay_init();
    Wheel_Init();
    MotorRight(TIM4,700);
    MotorLeft(TIM4,700);
    delay_ms(Left_Time);
}

void Turn_Left(void)
{
    delay_init();
    Wheel_Init();
    MotorRight(TIM4,800);
    MotorLeft(TIM4,800);
    delay_ms(Right_Time);
}

