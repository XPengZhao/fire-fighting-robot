#include "led.h"
//左超声波 PC.13-->trig    PA.0-->echo
//初始化PC.13&PA.0并使能这两个口的时钟		    
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOA与GPIOC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //trig-->PC.13端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PC.13
 GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //trig 输出低

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PA.0 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOA,GPIO_Pin_0); 						 //PE.5 输出高低
}
 
