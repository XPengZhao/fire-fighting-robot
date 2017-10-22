#include "search.h"
#include "Move.h"
#include "usart.h"
#include "delay.h"
#include "wave_measure.h"

void judge(int n)
{
	printf("turn flag: %d\r\n",turn_flag);
	if(turn_flag==14)
		forward_flag=0;
	else if(turn_flag==16)
		forward_flag=1;
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
		if(turn_flag==18)
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
			if(turn_flag==8)
			{
				while(distance.right<30)
				{
					forward_right();
					Get_Distance();
					delay_ms(50);
				}
				left();
				delay_ms(150);
				forward();
				delay_ms(550);
				turn_right();
				forward_flag=1;
			}
			break;
		case 1:
			if(distance.left>45&&distance.right<=30&&turn_flag!=7&&turn_flag!=14) turn_left();
			else up();
			break;
		case 2:
			up();
			break;
		default:
			while(1){turn_left();}
		}
}
