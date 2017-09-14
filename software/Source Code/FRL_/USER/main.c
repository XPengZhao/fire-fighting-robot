#include "wave_left.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"



int FRL[3]={0};

 int main(void)
 {	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 		//延时函数初始化	
	uart_init(9600);	 			//9600	 
	WAVE_Left_Init();		  		//初始化与LED连接的硬件接口
 	TIM2_Cap_Init(49999,71);		//以1Mhz的频率计数 
	TIM3_Cap_Init(49999,71);		//以1Mhz的频率计数 
	TIM5_Cap_Init(49999,71);		//以1Mhz的频率计数 
   
		
 	while(1){	
		
	     Get_Distance();
		
			printf("F  %d  R  %d  L  %d\n",FRL[0],FRL[1],FRL[2]);
	
			delay_ms(500);
	
		
	
		
		}	
 		
	}

