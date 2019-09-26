#include "main.h"

static u8  fac_us=0;              //us延时倍乘数

/**
  * @brief 初始化SysTick嘀嗒定时器
  * @param None
  * @retval None
  * @details 使能SysTick定时器中断，每25ms中断一次，中断优先级最低
  *          SysTick定时器1us计数9下
  */
void SysTick_Init(void)
{
  u32 reload=0;
  fac_us=SystemCoreClock/8000000;                          //每个us需要的systick时钟数=9
  reload=SystemCoreClock/8000*25;                          //reload值为25ms需要的systick时钟数=225000
  SysTick->LOAD  = (reload & SysTick_LOAD_RELOAD_Msk) - 1; //每25ms中断一次
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
  SysTick->VAL   = 0;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);    //选择外部时钟  HCLK/8
  SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                 //开始SYSTICK中断
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                  //开始SYSTICK计数
}

/**
  * @brief 微秒延时函数
  * @param 所需延时微秒数
  * @retval None
  * @details 1、延时期间掩蔽所有中断
  *          2、可以延时的最大微秒数为(2^32)/9=477218588us
  *          3、掩蔽期间中断被悬起，结束掩蔽后这些中断将被执行
  */
void delay_us(u32 nus)
{
  NVIC_SETPRIMASK();
  u32 tick=nus*fac_us;
  u32 time_old,time_now,time_cnt=0;
  u32 reload=SysTick->LOAD;
  time_old=SysTick->VAL;

  while(1)
  {
    time_now=SysTick->VAL;
    if(time_now<=time_old)
      time_cnt+=time_old-time_now;
    else
      time_cnt+=reload-time_now+time_old;
    time_old=time_now;
    if(time_cnt>=tick)
      break;
  }
  NVIC_RESETPRIMASK();
}

/**
  * @brief 毫秒延时函数
  * @param 所需延时毫秒数
  * @retval None
  * @details 1、延时期间掩蔽所有中断
  *          2、可以延时的最大毫秒数为 2^16-1=65535ms
  *          3、掩蔽期间中断被悬起，结束掩蔽后这些中断将被执行
  */
void delay_ms(u16 nms)
{
  delay_us((u32)(1000*nms));
}


//注释掉了位于stm32f10x_it.c 136行的SysTick_Handler(),避免重定义。
void SysTick_Handler(void)
{
  taskloop();
}
