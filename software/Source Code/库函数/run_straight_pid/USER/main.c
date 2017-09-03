#define DIS 200
#define TIME 0.01
#define TD 0
#define TI 10000
#define KP 0.2

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"

int main(void)
{ 
	float Kp=KP,Ti=TI,Td=TD,Ut=0;
	int difference=0,d_difference=0,i_difference=0;
	int distance=0,last_dis=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();                   //延时函数初始化
	uart_init(9600);                //9600
	Wheel_Init();
	Wave_Init();
	MotorLeft(TIM4,800);
	MotorRight(TIM4,700);

	distance=Get_Distance();
	difference=distance-DIS;
	while(1)
	{
		Ut=Kp*difference+Kp*TIME*i_difference/Ti+Kp*Td*d_difference/TIME;
		if(Ut>=0&&Ut<25)
		{
			MotorRight(TIM4,700+Ut);
			MotorLeft(TIM4,800);
		}
		else if(Ut<0&&Ut>-25)
		{
			MotorLeft(TIM4,800+Ut);
			MotorRight(TIM4,700);
		}
		else if(Ut>=25)
		{
			MotorRight(TIM4,725);
			MotorLeft(TIM4,800);
			delay_ms(300);
			MotorRight(TIM4,700);
			MotorLeft(TIM4,775);
			delay_ms(300);
		}
		else
		{
			MotorRight(TIM4,700);
			MotorLeft(TIM4,775);
			delay_ms(300);
			MotorRight(TIM4,725);
			MotorLeft(TIM4,800);
			delay_ms(300);
		}

		last_dis=distance;
		i_difference+=distance;
		distance=Get_Distance();
		printf("%d\t",distance);
		difference=distance-DIS;
		d_difference=distance-last_dis;
		printf("%f\r\n",Ut);
		if(i_difference>100)
			i_difference=0;
	}

}
