#define DIS 10

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"

int main(void)
{ 
    int distance=0;
    int last_distance=DIS;
    int difference=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
    delay_init();                   //延时函数初始化
    uart_init(9600);                //9600
    Wheel_Init();
    Wave_Init();
    MotorRight(TIM4,700);
    MotorLeft(TIM4,800);
    distance=Get_Distance();
	printf("%d\r\n",distance);
    difference=distance-last_distance;
    while(1)
    {
        if(difference!=0)
        {
            if(difference>0)
            {
                while(difference>5)
                {
                    MotorRight(TIM4,750);
                    MotorLeft(TIM4,800);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
					printf("%d\r\n",distance);
                }
                while(((distance-DIS)>3||(DIS-distance)<=3)&&difference>0)
                {
                    MotorRight(TIM4,700);
                    MotorLeft(TIM4,850);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                }
                while(((distance-DIS)<=3||(DIS-distance)>3)&&difference>0)
                {
                    MotorRight(TIM4,670);
                    MotorLeft(TIM4,850);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                }
            }
        }
    }
}
