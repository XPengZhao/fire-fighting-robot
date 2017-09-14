#include "pwm.h"


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	 GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// 使能定时器时钟TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIOA外设时钟使能  
                                                                              
  
   //设置该引脚为复用输出功能,输出TIM2 CH3(PA2复用输出)、TIM2 CH4(PA3复用输出)的PWM脉冲波形  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //TIM2_CH3(PA2复用输出)、TIM2 CH4(PA3复用输出)  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
      
 
      
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值    50HZ  
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式  
      
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位  
    
   
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能  
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高  
  
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx   
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3预装载使能     
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx   
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4预装载使能  
 
      
      
    TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器  
    TIM_CtrlPWMOutputs(TIM2,ENABLE);    //MOE 主输出使能  
    TIM_Cmd(TIM2, ENABLE);  //使能TIM2  
   
   
}


void forward(void)
{  
  //1.5ms->90度    749为停止值 
	u16 pwmright=700;//右轮接PA2
	u16 pwmleft=800;  //左轮接PA3
while(1)
  {
     //调节占空比pwmval1/(9999+1)
     TIM_SetCompare3(TIM2,pwmright);
     TIM_SetCompare4(TIM2,pwmleft);
   }
}

void turnright(void)
{
	  u16 pwmright=749;//右轮接PA2
	  u16 pwmleft=800;  //左轮接PA3
	while(1){
		TIM_SetCompare3(TIM2,pwmright);
     TIM_SetCompare4(TIM2,pwmleft);
	}
}

void turnleft(void)
{
	  u16 pwmright=700;//右轮接PA2
	  u16 pwmleft=749;  //左轮接PA3
	while(1){
		TIM_SetCompare3(TIM2,pwmright);
     TIM_SetCompare4(TIM2,pwmleft);
	}
}

