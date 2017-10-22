#include "search.h"
#include "Move.h"
#include "usart.h"
#include "delay.h"
#include "wave_measure.h"
#include "sensor.h"
#include "firesensor.h"

void judge(int n)
{
    if(turn_flag==1)
        forward_flag=0;
    else if(turn_flag==2)
        forward_flag=1;
    else if(turn_flag==12)
        forward_flag=0;
    else if(turn_flag==13)
    {
        forward_flag=1;
        if(distance.right>30)
        {
            if(Count==0)
                Sensor_Init();
            else if(Count>=3)
            {
                TIM_Cmd(TIM6, DISABLE);
                turn_right();
                forward_flag=0;
            }	
        }
    }
    if(n==0)
    {
        Get_Distance_Front();
        n=distance.front<25?0:2;
        if(n==2)
        {
            printf("n error\r\n");
        }
    }
    else if(n==1)
    {
        if(turn_flag==3)
        {
            right();
            delay_ms(50);
        }
        if(turn_flag==14)
            while(1){stop();}
        Get_Distance_Front();
        n=(distance.front<80&&distance.front>65)?1:2;
        if(n==2)
        {
            printf("n error\r\n");
        }
    }
    switch(n){
        case 0:
            if(distance.left<30)
            {
                Get_Fire();
				printf("sig:%d\r\n",sig.left);
                if(sig.left<200)
                {
                    stop();
                    PutOff_LeftFire();
                    turn_right();
                }
                else
                    turn_right();
            }
            else
            {
                Get_Fire();
				printf("sig:%d\r\n",sig.right);
                if(sig.right<200)
                {
                    stop();
                    PutOff_RightFire();
                    turn_left();
                }
                else
                    turn_left();
            }
            break;
        case 1:
            if(distance.left>45&&distance.right<=30&&turn_flag!=6&&turn_flag!=7&&turn_flag!=12) turn_left();
            else up();
            break;
        case 2:
            up();
            break;
        default:
            while(1){turn_left();}
        }
}
