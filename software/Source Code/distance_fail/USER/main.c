#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"


 int main(void)
{
	u16 count;
	uint8_t SaveStatus = 0;
	int length;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	LED_Init();
	printf("ss\t");
	TIM2_Int_Init(49999,71); 
	while (1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_us(20);						//拉高20us,发射超声波
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		SaveStatus=Level_Judge(GPIOA,GPIO_Pin_0);          //接收echo的电平	
		while(SaveStatus==0){
			printf("nothing\r\n");
			SaveStatus=Level_Judge(GPIOA,GPIO_Pin_0);
		}
		TIM2->CNT=0;					//计时器清零
		TIM_Cmd(TIM2, ENABLE);			// TIM3 enable counter
		while(Level_Judge(GPIOA,GPIO_Pin_0)&&(TIM2->CNT<TIM2->ARR-10));
		count=TIM2->CNT;
		TIM_Cmd(TIM2, DISABLE);
		TIM2->CNT=0;
		length=count/58;
		printf("%d\r\n",length);
		delay_ms(50);
	}
}
		
