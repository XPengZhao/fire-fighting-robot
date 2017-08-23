#include "wave_left.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"



extern u8  TIM3CH3_CAPTURE_STA;		//输入捕获状态
extern u16	TIM3CH3_CAPTURE_VAL;	//输入捕获值
 int main(void)
 {	
	 
	u32 temp=0; 
	int distance=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 		//延时函数初始化	
	uart_init(9600);	 			//9600	 
	WAVE_Left_Init();		  		//初始化与LED连接的硬件接口
 	TIM3_Cap_Init(49999,71);		//以1Mhz的频率计数 
   	while(1)
	{	
 		GPIO_SetBits(GPIOE,GPIO_Pin_0);     //PE.0-->trig 拉低电平
		delay_us(20);
		GPIO_ResetBits(GPIOE,GPIO_Pin_0);	//PE.0-->trig 拉高电平
		if(TIM3CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
			temp=TIM3CH3_CAPTURE_STA&0X3F;
			temp*=50000;					//溢出时间总和
			temp+=TIM3CH3_CAPTURE_VAL;		//得到总的高电平时间
			distance=temp *170;
			distance /= 10000;
			printf("HIGH:%d cm\r\n",distance);	//打印总的高点平时间
 			TIM3CH3_CAPTURE_STA=0;			//开启下一次捕获
			delay_ms(50);
 		}
	}
}
