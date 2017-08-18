#include "led.h"
//左超声波 PE.0-->trig    PA.0-->echo
//初始化PE.0&PA.0并使能这两个口的时钟		    
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);	 //使能GPIOE&GPIOA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //trig-->PE.0端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化PE.0
 GPIO_ResetBits(GPIOE,GPIO_Pin_0);						 //trig 输出低

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PA.0 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOA,GPIO_Pin_0); 						 //PA.0 输出低
}
 
