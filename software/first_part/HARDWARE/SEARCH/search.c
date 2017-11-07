#include "search.h"
#include "Move.h"
#include "usart.h"
#include "delay.h"
#include "wave_measure.h"
#include "firesensor.h"

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
		if(turn_flag==18){
			
			while(1){stop();}
		}
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
			printf("case 0:\r\n");
			if(distance.left<30)
				{ if(fire_flag)
					{
						stop();
						PutOff_LeftFire();
					}
					turn_right();
				}
			else
         { 
					 if(fire_flag)
					{
						stop();
						PutOff_RightFire();
					}
					turn_left();
				}				
				
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
				delay_ms(700);
				turn_right();
				forward_flag=1;
				
				printf("forward_flag=1");
			}
			break;
		case 1:
			printf("case 1:\r\n");
			if(distance.left>45&&distance.right<=30&&turn_flag!=7&&turn_flag!=14&&turn_flag!=15) turn_left();
			else up();
			break;
		case 2:
			printf("case 2:\r\n");
			up();
			break;
		default:
			while(1){turn_left();}
		}
}
