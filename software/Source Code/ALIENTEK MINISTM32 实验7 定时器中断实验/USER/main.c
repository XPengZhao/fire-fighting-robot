#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
//ALIENTEK Mini STM32�����巶������7
//��ʱ���ж�ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
{
	u16 count;
	float length;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	LED_Init();
	printf("ss\t");
	TIM3_Int_Init(49999,719); 
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	while (1)
		{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_us(20);//����20us,���䳬����
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		printf("����ǰ��%d\r\n",TIM3->CNT);
		TIM3->CNT=0;//��ʱ������
		printf("a\t");
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);//�ȴ�ECHO�ߵ�ƽ
		printf("b\t");
		TIM_Cmd(TIM3, ENABLE);// TIM3 enable counter [??tim3����]
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
		
