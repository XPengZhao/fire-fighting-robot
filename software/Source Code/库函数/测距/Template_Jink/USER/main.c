#include "stm32f10x.h"
#include "wave_measure.h"
#include "usart.h"
#include "delay.h"


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
    uart_init(9600);
	Wave_Init();
	while(1){
	printf("%d",Get_Distance());
	delay_ms(100);
	}
}
