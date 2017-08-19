#include "wave_left.h"
//左超声波 PA.2-->trig    PA.1-->echo
//初始化PA.1&PA.2并使能这两个口的时钟		    
void WAVE_Left_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能GPIOA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //trig-->PA.2端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化PA.2
 GPIO_ResetBits(GPIOA,GPIO_Pin_2);						 //trig 输出低

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //echo-->PA.1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOA,GPIO_Pin_1); 						 //PA.1 输出低
}
 
