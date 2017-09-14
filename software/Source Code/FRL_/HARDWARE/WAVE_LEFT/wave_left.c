#include "wave_left.h"

//超声波引脚
//前：trig:PC11   echo:PA1-TIM2CH2
//右：trig:Pc12   echo:PB0-TIM3CH3
//左：trig:PC13   echo:PA2-TIM5CH3

extern u8  TIM2CH2_CAPTURE_STA;		//输入捕获状态
extern u16	TIM2CH2_CAPTURE_VAL;	//输入捕获值
extern u8  TIM3CH3_CAPTURE_STA;		//输入捕获状态
extern u16	TIM3CH3_CAPTURE_VAL;	//输入捕获值
extern u8  TIM5CH3_CAPTURE_STA;		//输入捕获状态
extern u16	TIM5CH3_CAPTURE_VAL;	//输入捕获值

void WAVE_Left_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOA，B，C端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //trig-->PC.11端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PC11
 GPIO_ResetBits(GPIOC,GPIO_Pin_11);						 //trig 下拉电位

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //trig-->PC.12端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PC12
 GPIO_ResetBits(GPIOC,GPIO_Pin_12);						 //trig 下拉电位
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //trig-->PC.13端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PE.0
 GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //trig 下拉电位

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //echo-->PA1端口配置
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;           //上拉输入
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOA,GPIO_Pin_1); 						 //echo 下拉电位
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PB.0端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_0); 						 //echo 下拉电位
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //echo-->PB.0端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //IO口速度为50MHz
 GPIO_ResetBits(GPIOA,GPIO_Pin_2); 						 //echo 下拉电位
}
 



void Get_Distance(void)  //返回超声波测得距离
	{
	u32 temp1=0,temp2=0,temp3=0; 
   int front=0,right=0,left=0;
		GPIO_SetBits(GPIOC,GPIO_Pin_11);     //trig 拉高电平 
		GPIO_SetBits(GPIOC,GPIO_Pin_12);     
		GPIO_SetBits(GPIOC,GPIO_Pin_13); 
		delay_us(20);
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);  //trig 拉低电平
  	GPIO_ResetBits(GPIOC,GPIO_Pin_12);  
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
		if(TIM2CH2_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
			temp1=TIM2CH2_CAPTURE_STA&0X3F;
			temp1*=50000;					//溢出时间总和
			temp1+=TIM2CH2_CAPTURE_VAL;		//得到总的高电平时间
			front=temp1 *170;
			front /= 1000;
			FRL[0]=front;
			//printf("hanshu:%d mm  ",distance);	//打印距离
 			TIM2CH2_CAPTURE_STA=0;			//开启下一次捕获
		}  
  
 	if(TIM3CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
			temp2=TIM3CH3_CAPTURE_STA&0X3F;
			temp2*=50000;					//溢出时间总和
			temp2+=TIM3CH3_CAPTURE_VAL;		//得到总的高电平时间
			right=temp2 *170;
			right /= 1000;
			FRL[1]=right;
			//printf("hanshu:%d mm  ",distance);	//打印距离
 			TIM3CH3_CAPTURE_STA=0;			//开启下一次捕获
		}  
		if(TIM5CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
			temp3=TIM5CH3_CAPTURE_STA&0X3F;
			temp3*=50000;					//溢出时间总和
			temp3+=TIM5CH3_CAPTURE_VAL;		//得到总的高电平时间
			left=temp3 *170;
			left /= 1000;
			FRL[2]=left;
			//printf("hanshu:%d mm  ",distance);	//打印距离
 			TIM5CH3_CAPTURE_STA=0;			//开启下一次捕获
		}  
		
 
 
		
	}


	 