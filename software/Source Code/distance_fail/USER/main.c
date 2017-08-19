#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"


 int main(void)
{
	u16 count;
	float length;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	LED_Init();
	printf("ss\t");
	TIM3_Int_Init(49999,71); 
	while (1)
		{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_us(20);						//拉高20us,发射超声波
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		printf("清零前：%d\r\n",TIM3->CNT);
		TIM3->CNT=0;						//计时器清零
		printf("a\t");
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);//等待ECHO高电平
		printf("b\t");
		TIM_Cmd(TIM3, ENABLE);// TIM3 enable counter [??tim3计数]
			printf("%d\t",TIM3->CNT);
		 
		while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)&&(TIM3->CNT<TIM3->ARR-10));
			printf("%d\t",TIM3->CNT);

		 
		TIM_Cmd(TIM3, DISABLE);

		 
		count=TIM3->CNT;
		length=count/58.0;
		printf("%f\r\n",length);
		delay_ms(200);
		}
}
		
