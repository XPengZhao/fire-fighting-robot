#define DIS 200
#define KP1 24
#define KP2 40

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"

extern Distance distance;

int main(void)
{ 
    float Kp1=KP1,Kp2=KP2,Ut=0;
    int difference=0;
    int last_dis=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init();
    uart_init(9600);
    Wheel_Init();
    Wave_Init();
    delay_ms(1000);
    
    MotorLeft(TIM4,800);
    MotorRight(TIM4,700);

	Get_Distance();
    difference=distance.right-DIS;

    while(1)
    {
        if(difference>40)
        {
			printf("1\r\n");
            difference-=20;
            Ut=Kp1*difference;
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
            Ut=Kp1*difference;
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

        last_dis=distance.right;
		Get_Distance();
        difference=distance.right-DIS;
        printf("%f\r\n",Ut);
    }

}
