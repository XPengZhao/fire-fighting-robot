#include "led.h"
//左超声波 PE.6-->trig    PE.5-->echo
//初始化PE.6&PE.5并使能这两个口的时钟		    
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能GPIOE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //trig-->PE.6端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化PE.6
 GPIO_ResetBits(GPIOE,GPIO_Pin_6);						 //trig 输出低

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //echo-->PE.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出低
}
 
