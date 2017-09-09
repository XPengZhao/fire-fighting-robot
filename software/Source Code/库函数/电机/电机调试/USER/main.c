#include "stm32f10x.h"
#include "Motor_Pwm.h"
#include "delay.h"
int main(void){
	delay_init();
	Wheel_Init();
	delay_ms(1000);
	while(1)
	{
		/*MotorRight(TIM4,700);
		MotorLeft(TIM4,800);
		delay_ms(500);*/
		MotorRight(TIM4,700);
		MotorLeft(TIM4,700);
		delay_ms(610);
		MotorRight(TIM4,750);
		MotorLeft(TIM4,750);
		delay_ms(500);
	}
}
