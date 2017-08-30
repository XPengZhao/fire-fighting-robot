#include "stm32f10x.h"
#include "wave_measure.h"
#include "usart.h"
#include "delay.h"

int main(void)
{	
	int distance;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
    uart_init(9600);
	Wave_Init();
	distance=Get_Distance();
	printf("%d\r\n",distance);
	delay_ms(3000);
}
