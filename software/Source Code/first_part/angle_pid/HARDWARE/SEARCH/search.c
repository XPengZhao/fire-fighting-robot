#include "search.h"
#include "move.h"
#include "usart.h"
#include "wave_measure.h"

void judge(int n)
{
	printf("%d\t%d\t%d\t%d\r\n",n,distance.front,distance.left,distance.right);
	//Get_Distance();
	Get_Distance_Left();
	Get_Distance_Right();
	switch(n){
		case 0:
			if(distance.left<30) turn_right();
			else turn_left();
			break;
		case 1:
			if(distance.left<=30 && distance.right<=30) up();
			else if(distance.left>30) turn_left();
			else if(distance.right>30) turn_right();
			else while(1){turn_left();}
			break;
		case 2:
			up();
			break;
		default:
			while(1){turn_left();}
		}
}
