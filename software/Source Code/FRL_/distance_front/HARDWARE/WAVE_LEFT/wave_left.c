#include "wave_left.h"
//左超声波 PC.13-->trig    PB.0-->echo
//初始化PB.0&PE.0并使能这两个口的时钟		    
void WAVE_Left_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOB，C端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //trig-->PC.13端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PE.0
 GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //trig 下拉电位

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PB.0端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_0); 						 //echo 下拉电位
}
 

extern u8  TIM3CH3_CAPTURE_STA;		//输入捕获状态
extern u16	TIM3CH3_CAPTURE_VAL;	//输入捕获值

int Distance(void)  //返回超声波测得距离
	{
	u32 temp=0; 
  int distance=0;
	
		GPIO_SetBits(GPIOC,GPIO_Pin_13);     //PC13-->trig 拉高电平 
		delay_us(20);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);  //PC13-->trig 拉低电平
  
		if(TIM3CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
			temp=TIM3CH3_CAPTURE_STA&0X3F;
			temp*=50000;					//溢出时间总和
			temp+=TIM3CH3_CAPTURE_VAL;		//得到总的高电平时间
			distance=temp *170;
			distance /= 1000;
			//printf("hanshu:%d mm  ",distance);	//打印距离
 			TIM3CH3_CAPTURE_STA=0;			//开启下一次捕获
				return distance;
	}  
  
 
		
 
 
		
	}


	 