#include "stm32f10x.h"
#include "Motor_Pwm.h"
#include "delay.h"
#include "Motor_Turn.h"
int main(void){
	delay_init();
	delay_ms(1000);
	while(1)
	{
		Turn_Right();
		MotorRight(TIM4,750);
		MotorLeft(TIM4,750);
		delay_ms(500);
	}
}
