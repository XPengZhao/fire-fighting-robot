#include "delay.h"
#include "sys.h"
#include "pwm.h"

 int main(void)
 {	//1.5ms->90度    749为停止值 
	u16 pwmright=700;//右轮接PA2
	 u16 pwmleft=800;  //左轮接PA3
delay_init(); //延时函数初始化

TIM4_PWM_Init(9999,143);//不分频。PWM 频率=72*10^6/(9999+1)/(143+1)=50Hz

while(1)
{
//调节占空比pwmval1/(9999+1)
TIM_SetCompare1(TIM4,pwmright);
TIM_SetCompare2(TIM4,pwmleft);

}
	 
	 
}

