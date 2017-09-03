#define DIS 200
#define TIME 0.01
#define TD 0
#define TI 10000
#define KP 30

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
	delay_ms(1000);
	MotorLeft(TIM4,800);
	MotorRight(TIM4,700);

	while(1)
	{
		distance=Get_Distance();
		delay_ms(200);
		d_difference=Get_Distance()-distance;
		printf("%d\r\n",d_difference);
		if(d_difference>20)
			d_difference=20;
		else if(d_difference<-20)
			d_difference=-20;
		Ut=Kp*d_difference;
		if(Ut>30&&Ut<Kp*10)
		{
			MotorRight(TIM4,720);
			MotorLeft(TIM4,800);
			delay_ms((int)Ut);
		}
		else if(Ut<-30&&Ut>(-Kp*10))
		{
			MotorRight(TIM4,700);
			MotorLeft(TIM4,780);
			Ut=-Ut;
			delay_ms((int)Ut);
		}
		else if(Ut>Kp*10)
		{
			MotorRight(TIM4,725);
			MotorLeft(TIM4,800);
			delay_ms((int)Ut);
		}
		else if(Ut<(-Kp*10))
		{
			{
			MotorRight(TIM4,700);
			MotorLeft(TIM4,775);
			Ut=-Ut;
			delay_ms((int)Ut);
		}
		}
		else
		{
			MotorRight(TIM4,700);
			MotorLeft(TIM4,800);
		}
		MotorLeft(TIM4,800);
		MotorRight(TIM4,700);
	}
}
