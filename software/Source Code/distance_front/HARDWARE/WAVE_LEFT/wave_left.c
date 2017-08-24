#include "wave_left.h"
//左超声波 PC.13-->trig    PB.0-->echo
//初始化PB.0&PE.0并使能这两个口的时钟		    
void WAVE_Left_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //trig-->PE.0端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PE.0
 GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //trig 下拉电位

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PB.0 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_0); 						 //echo 下拉电位
}
 
