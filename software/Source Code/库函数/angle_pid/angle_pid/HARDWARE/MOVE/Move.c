#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"

void parameter_init(void)
{
    Get_Distance();
    delay_ms(300);
    angle.left=Get_Distance_Left()-distance.left;
    angle.right=Get_Distance_Right()-distance.right;
    last_angle=angle;
}

void forward_left(void)
{
    int Ut,diff;
    distance.left=Get_Distance_Left();
    diff=distance.left-last_distance.left;
    Ut=Kp*diff;
    if(Ut>THRESHOLD)
        left();
    else if(Ut<-THRESHOLD)
        right();
    else if((distance.left-LEFT_DIS)>2)
        left();
    else if((distance.left-LEFT_DIS)<-2)
        right();
    else
        forward();
    last_distance.left=distance.left;
}

void forward_right(void)
{
    int Ut,diff;
    distance.right=Get_Distance_Right();
    diff=distance.right-last_distance.right;
    Ut=Kp*diff;
    printf("%d\r\n",Ut);
    if(Ut>0)
    {
        right();
        delay_ms(10);
    }
    else if(Ut<0)
    {
        left();
        delay_ms(10);
    }
    if(Ut<2&&Ut>-2)
    {
        if((distance.right-RIGHT_DIS)>2)
        {
            right();
            delay_ms(30);
			left();
			delay_ms(30);
			forward();
        }
        else if((distance.right-RIGHT_DIS)<-2)
        {
            left();
            delay_ms(30);
			right();
			delay_ms(30);
			forward();
        }
        else
            forward();
    }
    last_distance.right=distance.right;
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
}	

void turn_right(void)
{
    MotorRight(TIM4,800);
    MotorLeft(TIM4,800);
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
    
