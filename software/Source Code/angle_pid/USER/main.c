#define KP 30

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"

int main(void)
{ 
	int Kp=KP;
	int angle=0,last_angle=0;
    int distance=0,i=0,Ut=0;
    int count=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();                                  //延时函数初始化
	uart_init(9600);
	Wheel_Init();
	Wave_Init();
	for(i=0;i<3;i++)
	{
		delay_ms(1000);
	}
	MotorLeft(TIM4,800);
	MotorRight(TIM4,700);
	
	distance=Get_Distance();
	delay_ms(250);
	angle=Get_Distance()-distance;
	printf("%d\r\n",angle);
	last_angle=angle;

	while(1)
	{
		/*----------对angle进行滤波---------*/
		if(angle>15)                                //限幅
			angle=15;
		else if(angle<-15)
			angle=-15;
		
		if(last_angle<2&&last_angle>-3)				 //滞后滤波
		{
			if(angle<=0)
				angle=angle/3+last_angle;  
			else
				angle=angle/3+last_angle;
		}
		/*----------------------------------*/
		Ut=Kp*angle;
		printf("%d\t",angle);
		
		if(Ut>Kp)
		{
			MotorRight(TIM4,724);
			MotorLeft(TIM4,800);
			delay_ms((int)Ut);
		}
		else if(Ut<-Kp)
		{
			MotorRight(TIM4,704);
			MotorLeft(TIM4,780);
			Ut=-Ut;
			delay_ms((int)Ut);
		}
		else
		{
			MotorRight(TIM4,704);
			MotorLeft(TIM4,800);
		}
		MotorLeft(TIM4,800);
		MotorRight(TIM4,704);
		
		last_angle=angle;
		distance=Get_Distance();
		delay_ms(250);
		angle=Get_Distance()-distance;
		printf("%d\r\n",angle);
		
	}
}
