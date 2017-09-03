#define DIS 200
#define TIME 0.01
#define TD 0
#define TI 10000
#define KP1 24
#define KP2 40

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"

int main(void)
{ 
    float Kp1=KP1,Kp2=KP2,Ti=TI,Td=TD,Ut=0;
    int difference=0,d_difference=0,i_difference=0;
    int distance=0,last_dis=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
    delay_init();                   //延时函数初始化
    uart_init(9600);                //9600
    Wheel_Init();
    Wave_Init();
	delay_ms(1000);
    MotorLeft(TIM4,800);
    MotorRight(TIM4,700);

    distance=Get_Distance();
    difference=distance-DIS;

    while(1)
    {
        if(difference>40)
        {
			printf("1\r\n");
            difference-=20;
            Ut=Kp1*difference+Kp1*TIME*i_difference/Ti+Kp1*Td*d_difference/TIME;
            MotorRight(TIM4,730);
            MotorLeft(TIM4,800);
            delay_ms(500);
            MotorRight(TIM4,700);
            MotorLeft(TIM4,800);
            delay_ms((int)Ut);
            MotorRight(TIM4,700);
            MotorLeft(TIM4,770);
            delay_ms(500);
        }
		else if(difference<-40)
        {
			printf("2\r\n");
            difference+=20;
            Ut=Kp1*difference+Kp1*TIME*i_difference/Ti+Kp1*Td*d_difference/TIME;
            MotorRight(TIM4,700);
            MotorLeft(TIM4,770);
            delay_ms(500);
            MotorRight(TIM4,700);
            MotorLeft(TIM4,800);
            delay_ms((int)-Ut);
            MotorRight(TIM4,730);
            MotorLeft(TIM4,800);
            delay_ms(500);
        }
        else if(10<difference&&difference<40)
        {
			printf("3\r\n");
            difference-=10;
            Ut=Kp2*difference;
            MotorRight(TIM4,720);
            MotorLeft(TIM4,800);
            delay_ms(500);
            MotorRight(TIM4,700);
            MotorLeft(TIM4,800);
            delay_ms((int)Ut);
            MotorRight(TIM4,700);
            MotorLeft(TIM4,780);
            delay_ms(500);
        }
        else if(difference>-40&&difference<-10)
        {
			printf("4\r\n");
            difference+=10;
            Ut=Kp2*difference;
            MotorRight(TIM4,700);
            MotorLeft(TIM4,780);
            delay_ms(500);
            MotorRight(TIM4,700);
            MotorLeft(TIM4,800);
            delay_ms((int)-Ut);
            MotorRight(TIM4,720);
            MotorLeft(TIM4,800);
            delay_ms(500);
        }
		else
		{
			printf("5\r\n");
			MotorRight(TIM4,700);
            MotorLeft(TIM4,800);
		}

        last_dis=distance;
        i_difference+=distance;
        distance=Get_Distance();
        printf("%d\t",distance);
        difference=distance-DIS;
        d_difference=distance-last_dis;
        printf("%f\r\n",Ut);
        if(i_difference>100)
            i_difference=0;
    }

}
