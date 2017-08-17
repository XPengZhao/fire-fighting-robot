#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
//ALIENTEK Mini STM32开发板范例代码7
//定时器中断实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms  
   	while(1)
	{
		//LED0=!LED0;
		TIM3->CNT=0;
		delay_ms(1000);		   
	}
}
