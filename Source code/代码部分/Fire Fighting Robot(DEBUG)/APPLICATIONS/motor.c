#include "main.h"

/**
  * @brief 调节右电机PWM波
  * @param speed，范围从-100~+100
  * @retval None
  * details -100反转最大速度，0停转，+100正转最大速度
  *         PWM占空比由TIM4配置得出
  */
void MotorRight(int16_t speed)
{
  if(speed>100)  speed=100;
  if(speed<-100) speed=-100;
  __Motordata.motor_right=speed;
  speed=750-speed;
  TIM_SetCompare1(TIM4,speed);
}

/**
  * @brief 调节右电机PWM波
  * @param speed，范围从-100~+100
  * @retval None
  * details -100反转最大速度，0停转，+100正转最大速度
  *         PWM占空比由TIM4配置得出
  */
void MotorLeft(int16_t speed)
{
  if(speed>100)  speed=100;
  if(speed<-100) speed=-100;
  __Motordata.motor_left=speed;
  speed=750+speed;
  TIM_SetCompare2(TIM4,speed);
}

void FanMotor_Init()
{
  GPIO_InitTypeDef GPIO_InitStrue;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_15;
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOD,&GPIO_InitStrue);
}

void FanMotor_Open()
{
  GPIO_SetBits(GPIOD,GPIO_Pin_15);
}

void FanMotor_Close()
{
  GPIO_ResetBits(GPIOD,GPIO_Pin_15);
}
