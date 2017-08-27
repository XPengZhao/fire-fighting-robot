#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"

 int main(void)
 {	
	u16 led0pwmval=15;    	
	delay_init();	    	 //延时函数初始化	  
	GPIO_Cfg();
	TIM1_PWM_Init(199,7199);    //不分频。PWM频率=72000000/(7200*200)=50HZ
   	while(1)
	{				 
		TIM_SetCompare1(TIM1,led0pwmval);	   
	} 
}

