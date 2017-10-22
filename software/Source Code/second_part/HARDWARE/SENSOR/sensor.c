#include "sensor.h"
#include "wave_measure.h"
#include "usart.h"
#include "move.h"

//通过修改 ARR_SENSOR 与 PSC_SENSOR 改变采样时间，暂定为100ms

void Sensor_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

    TIM_TimeBaseStructure.TIM_Period = ARR_SENSOR;    //自动装载值
    TIM_TimeBaseStructure.TIM_Prescaler = PSC_SENSOR; //预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级3级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设
}

void TIM6_IRQHandler(void)   //TIM6中断
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			Count++;
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx的中断待处理位
    }
}
