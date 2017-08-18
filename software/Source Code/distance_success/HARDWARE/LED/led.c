#include "led.h"

//初始化PC13和PA0为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //trig-->PC13 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.13
 GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //trig 输出低

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PA.0 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
}
 
