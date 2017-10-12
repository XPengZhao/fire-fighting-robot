#include "search.h"
#include "Move.h"
#include "usart.h"
#include "delay.h"
#include "wave_measure.h"

void judge(int n)
{
	if(n==0)
	{
		delay_ms(50);
		Get_Distance_Front();
		n=distance.front<25?0:2;
	}
	else if(n==1)
	{
		delay_ms(50);
		Get_Distance_Front();
		n=(distance.front<80&&distance.front>70)?1:2;
	}
	printf("%d\t%d\t%d\t%d\r\n",n,distance.front,distance.left,distance.right);
	switch(n){
		case 0:
			if(distance.left<30) turn_right();
			else turn_left();
			turn_flag=1;
			if(room_flag==1) room_flag+=1;
			else if(room_flag==2)
			{
				while(distance.right<30)
				{
					forward_right();
					Get_Distance_Right();
					delay_ms(50);
				}
				forward();
				delay_ms(100);
				turn_right();
			}
			break;
		case 1:
			if(distance.left>30&&distance.right<=30&&!turn_flag) turn_left();
			else if(distance.left<=30&&distance.right>30) room_flag=1;
			else up();
			break;
		case 2:
			up();
			turn_flag=0;
			break;
		default:
			while(1){turn_left();}
		}
}
void Get_position(void)
{
    if(C_distance_front-distance.front>42)
    {
        switch(Direction)
        {
            case(0):
                CY+=1;
				break;
            case(1):
                CX+=1;
				break;
            case(2):
                CY-=1;
				break;
            case(3):
                CX-=1;
			break;
        }
        C_distance_front=distance.front;
    }
}
