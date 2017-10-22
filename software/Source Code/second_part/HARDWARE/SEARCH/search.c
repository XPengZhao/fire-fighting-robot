#include "search.h"
#include "Move.h"
#include "usart.h"
#include "delay.h"
#include "wave_measure.h"
#include "sensor.h"

void judge(int n)
{
	printf("turn flag: %d\r\n",turn_flag);
	if(turn_flag==0)
		forward_flag=1; 
	else if(turn_flag==1)
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
	//printf("%d\t%d\t%d\t%d\r\n",n,distance.front,distance.left,distance.right);
	switch(n){
		case 0:
			if(distance.left<30) turn_right();
			else turn_left();
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
