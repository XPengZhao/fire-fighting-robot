#include "led.h"

//trig-->PC.13    echo-->PA.0
//初始化PA.0&PC.13.并使能这两个口的时钟
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PC端口时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;             //PC.13
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //trig   PC13
  GPIO_Init(GPIOC, &GPIO_InitStructure);                 //初始化GPIOC.1
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;              //PA.0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //echo   PA0
  GPIO_Init(GPIOA, &GPIO_InitStructure);                 //初始化PA.0
  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
 
