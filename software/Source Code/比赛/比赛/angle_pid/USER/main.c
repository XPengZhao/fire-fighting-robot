#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"
#include "sensor.h"
#include "search.h"


Distance distance={0,0,0},last_distance={0,0,0};
Angle angle={0,0};
Angle last_angle={0,0};
int turn_flag=0;
int forward_flag=0;
int control_flag=0;
int first_room=0;

int main(void)
{ 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
    delay_init();                                  
    uart_init(9600);
    Wheel_Init();
    Wave_Init();
	FAN_Init();
	parameter_init();
    while(1)
    {
		printf("********************************\r\n");
		Get_Distance();
		if(distance.front<30)
			judge(0);
		else if(distance.front>65 && distance.front<85&&turn_flag!=18)
			judge(1);
		else if(distance.front>45 && distance.front<60&&turn_flag==18)
			while(1){stop();delay_ms(50);}
		else judge(2);
		delay_ms(100);
		printf("********************************\r\n");
    }
	/*while(1)
	{
		MotorRight(TIM4,800);
		MotorLeft(TIM4,800);
		delay_ms(150);
		forward();
		delay_ms(300);
		MotorRight(TIM4,704);
		MotorLeft(TIM4,700);
		delay_ms(150);
		stop();
		Get_Distance();
		last_distance=distance;
		forward();	
	}
	*/
}
