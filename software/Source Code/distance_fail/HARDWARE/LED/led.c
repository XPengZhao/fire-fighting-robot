#include "led.h"


//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
 		//USART1_TX   GPIOE.1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //PE1
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //trig   PC13
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE.1
   
  //USART1_RX	  GPIOE.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PE2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//   echo   PA0
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE.2
}
 
