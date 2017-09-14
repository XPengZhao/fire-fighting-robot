#include "pwm.h"


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	 GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// ʹ�ܶ�ʱ��ʱ��TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIOA����ʱ��ʹ��  
                                                                              
  
   //���ø�����Ϊ�����������,���TIM2 CH3(PA2�������)��TIM2 CH4(PA3�������)��PWM���岨��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //TIM2_CH3(PA2�������)��TIM2 CH4(PA3�������)  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
      
 
      
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ    50HZ  
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ  
      
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ  
    
   
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��  
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�  
  
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx   
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��     
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx   
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��  
 
      
      
    TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���  
    TIM_CtrlPWMOutputs(TIM2,ENABLE);    //MOE �����ʹ��  
    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2  
   
   
}


void forward(void)
{  
  //1.5ms->90��    749Ϊֵֹͣ 
	u16 pwmright=700;//���ֽ�PA2
	u16 pwmleft=800;  //���ֽ�PA3
while(1)
  {
     //����ռ�ձ�pwmval1/(9999+1)
     TIM_SetCompare3(TIM2,pwmright);
     TIM_SetCompare4(TIM2,pwmleft);
   }
}

void turnright(void)
{
	  u16 pwmright=749;//���ֽ�PA2
	  u16 pwmleft=800;  //���ֽ�PA3
	while(1){
		TIM_SetCompare3(TIM2,pwmright);
     TIM_SetCompare4(TIM2,pwmleft);
	}
}

void turnleft(void)
{
	  u16 pwmright=700;//���ֽ�PA2
	  u16 pwmleft=749;  //���ֽ�PA3
	while(1){
		TIM_SetCompare3(TIM2,pwmright);
     TIM_SetCompare4(TIM2,pwmleft);
	}
}

