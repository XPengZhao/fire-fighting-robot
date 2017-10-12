#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"

void parameter_init(void)
{
	turn_flag=0;
	room_flag=0;
    forward();
    Get_Distance();
    delay_ms(100);
    last_distance.right=distance.right;
    last_distance.left=distance.left;
    Get_Distance();
    angle.right=distance.right-last_distance.right;
	angle.left=distance.left-last_distance.left;
	C_distance_front=distance.front;
}

void forward_left(void)
{
	angle.left=distance.left-last_distance.left;
	/*------------------根据 angle.left 进行控制--------------*/
	if(angle.left>0)
	{
		left();
	}
	else if(angle.left<0)
	{
		right();
	}
	
	//-------------------位置环控制 way1-------------------------
	else if(distance.left-LEFT_DIS<-5)
	{
		printf("abc---------------\r\n");
		right();
	}
	else if(distance.left-LEFT_DIS>5)
	{
		printf("abc---------------\r\n");
		left();
	}
	else
	{
		forward();
	}
	
	/*
	//-------------------位置环控制 way2-------------------
	else 
	{
		forward();
	}
	if((angle.left<2&&angle.left>-2)||distance.left<10)
	{
		printf("weizhihuan!!!\r\n");
		if((distance.left-LEFT_DIS)>2)
		{
			left();
			delay_ms(100);
			right();
			delay_ms(100);
			forward();
		}
		else if((distance.left-LEFT)<-2)
		{
			right();
			delay_ms(100);
			left();
			delay_ms(100);
			forward();
		}
		else
			forward();
		Get_Distance_Left();
	}
	*/	
	last_distance.left=distance.left;
}

void forward_right(void)
{
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
	
	//-------------------位置环控制 way1-------------------------
	else if(distance.right-RIGHT_DIS<-5)
	{
		printf("位置环！！！\r\n");
		left();
	}
	else if(distance.right-RIGHT_DIS>5)
	{
		printf("位置环！！！\r\n");
		right();
	}
	else
	{
		forward();
	}
	
	/*
	//-------------------位置环控制 way2-------------------
	else 
	{
		forward();
	}
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
	*/	
	last_distance.right=distance.right;
}

void left(void)
{
    MotorRight(TIM4,704);
    MotorLeft(TIM4,780);
	printf("left\r\n");
}

void right(void)
{
    MotorRight(TIM4,724);
    MotorLeft(TIM4,800);
	printf("right\r\n");
}

void turn_left(void)
{
  MotorRight(TIM4,700);
  MotorLeft(TIM4,700);
	delay_ms(620);
	stop();
	delay_ms(200);
	Get_Distance_Right();
	last_distance.right=distance.right;
}	

void turn_right(void)
{
  MotorRight(TIM4,800);
  MotorLeft(TIM4,800);
	delay_ms(620);
	stop();
	delay_ms(200);
	Get_Distance_Left();
	last_distance.left=distance.left;
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
    
