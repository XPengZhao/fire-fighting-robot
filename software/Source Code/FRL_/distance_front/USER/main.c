#include "wave_left.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "pwm.h"

#define DistanceSet 200
#define motor_right TIM_SetCompare3
#define motor_left TIM_SetCompare4


 int main(void)
 {	
	 int difference;
	int distance;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 		//延时函数初始化	
	uart_init(9600);	 			//9600	 
	WAVE_Left_Init();		  		//初始化与LED连接的硬件接口
 	TIM3_Cap_Init(49999,71);		//以1Mhz的频率计数 
	 //pwm波初始化
	TIM2_PWM_Init(9999,143);//不分频。PWM 频率=72*10^6/(9999+1)/(143+1)=50Hz 
	 
	distance=Distance();
		
 	while(1){	
	
		difference=DistanceSet-distance;
		if(difference<0)
		{if(difference<-30)
				{
				motor_right(TIM2,750);
				motor_left(TIM2,800);
					printf("1 %d mm \n",distance);
						distance=Distance();
				}
			else {
			   	motor_right(TIM2,720);
			   	motor_left(TIM2,800);
					printf("2 %d mm \n",distance);
						distance=Distance();
			     }
		}
		else {
			if(distance>0)
			{  if(difference>30)
						{
				motor_right(TIM2,700);
				motor_left(TIM2,750);	
            printf("3 %d mm \n",distance);
						distance=Distance();					
						}
		    	  else {
				motor_right(TIM2,700);
			  motor_left(TIM2,780);
							printf("4 %d mm \n",distance);
						distance=Distance();
					}
				}
					else  {
				motor_right(TIM2,700);
				motor_left(TIM2,800);
						printf("5 %d mm \n",distance);
						distance=Distance();
					}
				}
			delay_us(500);
	
		
	
		
		}	
 		
	}

