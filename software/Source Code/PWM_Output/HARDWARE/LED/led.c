#include "led.h"
	    
//LED IO初始化
void GPIO_Cfg(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_TIM1,ENABLE);

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);

    //设置PE.9,PE.11为复用输出，输出2路PWM
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_Init(GPIOE,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
}

 
