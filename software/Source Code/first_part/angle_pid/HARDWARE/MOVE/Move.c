#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"

void parameter_init(void)
{
    forward();
    Get_Distance();
    delay_ms(100);
    last_distance.right=distance.right;
    last_distance.left=distance.left;
    Get_Distance();
    angle.right=distance.right-last_distance.right;
    angle.left=distance.left-last_distance.left;
}

void forward_left(void)
{
    while(1){turn_right();}
}

void forward_right(void)
{
	Get_Distance_Right();
	angle.right=distance.right-last_distance.right;
	/*------------------根据 angle.right 进行控制--------------*/
	if(angle.right>0)
	{
		right();
	}
	else if(angle.right<0)
	{
		left();
	}
	else
	{
		forward();
	}
	last_distance.right=distance.right;
	
	/*-------------------判断是否进入位置环控制-------------------*/
	if((angle.right<2&&angle.right>-2)||distance.right<10)
	{
		printf("weizhihuan!!!\r\n");
		if((distance.right-RIGHT_DIS)>2)
		{
			right();
			delay_ms(100);
			left();
			delay_ms(100);
			forward();
		}
		else if((distance.right-RIGHT_DIS)<-2)
		{
			left();
			delay_ms(100);
			right();
			delay_ms(100);
			forward();
		}
		else
			forward();
		Get_Distance_Right();
	}
}

void left(void)
{
    MotorRight(TIM4,704);
    MotorLeft(TIM4,780);
}

void right(void)
{
    MotorRight(TIM4,724);
    MotorLeft(TIM4,800);
}

void turn_left(void)
{
    MotorRight(TIM4,700);
    MotorLeft(TIM4,700);
	delay_ms(640);
}	

void turn_right(void)
{
    MotorRight(TIM4,800);
    MotorLeft(TIM4,800);
	delay_ms(640);
}	

void forward(void)
{
    MotorLeft(TIM4,800);
    MotorRight(TIM4,704);
}

void stop(void)
{
    MotorLeft(TIM4,750);
    MotorRight(TIM4,750);
}

void up(void)
{
	if(distance.right<30) forward_right();
	else if(distance.left<30) forward_left();
	else forward();
}
    
