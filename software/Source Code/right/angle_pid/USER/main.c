#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"
#include "search.h"
#include "timer.h"


Distance distance={0,0,0},last_distance={0,0,0};
Angle angle={0,0};
Angle last_angle={0,0};
int Map[6][6]={0};
int CX=5,CY=3,Direction=0,C_distance_front=105;
int Count=1;
int turn_flag=0;
int room_flag=0;

int main(void)
{ 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
    delay_init();                                  // 延时函数初始化
    uart_init(9600);
    Wheel_Init();
    Wave_Init();
    parameter_init();
	Timer_Init();

    while(1)
    {
        if(Count%2==0)
        {
            turn_left();
            Count=1;
            forward();
			printf("1:%d\n",Count);
        }
		printf("2:%d\n",Count);
    }
}
