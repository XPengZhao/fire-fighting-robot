#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"
#include "usart.h"

void parameter_init(void)
{
	turn_flag=0;
	room_flag=0;
	forward_flag=0;
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
	else if(distance.left-LEFT_DIS<-THRESHOLD)
	{
		right();
	}
	else if(distance.left-LEFT_DIS>THRESHOLD)
	{
		left();
	}
	else
	{
		forward();
	}	
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
	else if(distance.right-RIGHT_DIS<-THRESHOLD)
	{
		left();
	}
	else if(distance.right-RIGHT_DIS>THRESHOLD)
	{
		right();
	}
	else
	{
		forward();
	}
	last_distance.right=distance.right;
}

void left(void)
{
    MotorRight(TIM4,704);
    MotorLeft(TIM4,780);}

void right(void)
{
    MotorRight(TIM4,724);
    MotorLeft(TIM4,800);
}

void turn_left(void)
{
  MotorRight(TIM4,700);
  MotorLeft(TIM4,700);
	delay_ms(600);
	stop();
	Get_Distance();
	last_distance=distance;
	delay_ms(200);
	turn_flag++;
}	

void turn_right(void)
{
    MotorRight(TIM4,800);
    MotorLeft(TIM4,800);
	delay_ms(600);
	stop();
	Get_Distance();
	last_distance=distance;
	delay_ms(200);
	turn_flag++;
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
	if(forward_flag==0)
	{
		if(distance.right<30) forward_right();
	else if(distance.left<30) forward_left();
	else forward();
	}
	else {
		if(distance.left<30) forward_left();
	else if(distance.right<30) forward_right();
	else forward();
	}
}
    
