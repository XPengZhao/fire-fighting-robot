#define DIS 200

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
    difference=distance-last_distance;
    while(1)
    {
        if(difference!=0)
        {
            if(difference>0)		//左偏
            {
                while(difference>20)
                {
                    MotorRight(TIM4,740);
                    MotorLeft(TIM4,800);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                    printf("1:%d\r\n",distance);
                }
                while(((distance-DIS)>20||(DIS-distance)<=20)&&difference>0)
                {
                    MotorRight(TIM4,730);
                    MotorLeft(TIM4,800);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                    printf("2:%d\r\n",distance);
                }
                while(((distance-DIS)<=20||(DIS-distance)>20)&&difference>0)
                {
                    MotorRight(TIM4,720);
                    MotorLeft(TIM4,800);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                    printf("3:%d\r\n",distance);
                }
            }
            else
            {
                while(difference<-20)
                {
                    MotorRight(TIM4,700);
                    MotorLeft(TIM4,760);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                    printf("4:%d\r\n",distance);
                }
                while(((distance-DIS)<-20||(DIS-distance)>=-20)&&difference<0)
                {
                    MotorRight(TIM4,700);
                    MotorLeft(TIM4,770);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                    printf("5:%d\r\n",distance);
                }
                while(((distance-DIS)>=-20||(DIS-distance)<-20)&&difference<0)
                {
                    MotorRight(TIM4,700);
                    MotorLeft(TIM4,780);
                    last_distance=distance;
                    distance=Get_Distance();
                    difference=distance-last_distance;
                   printf("6:%d\r\n",distance);
                }
            }
        }
        else
        {
            MotorRight(TIM4,700);
            MotorLeft(TIM4,800);
            last_distance=distance;
            distance=Get_Distance();
            difference=distance-last_distance;
            printf("7:%d\r\n",distance);
        }
    }
}
