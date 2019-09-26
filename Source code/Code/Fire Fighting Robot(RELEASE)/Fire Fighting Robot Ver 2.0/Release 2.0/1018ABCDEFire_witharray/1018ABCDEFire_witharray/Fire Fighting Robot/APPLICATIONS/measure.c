#include "main.h"

//全局结构__distance用于保存超声波探测到的距离，有三个成员。
Distance __distance={0,0,0};

/**
  * @brief 测量左墙的距离
  * @param None
  * @retval None
  * @details trig-->PC.13  echo-->PA.2  TIM5_CH3
  *          毫米级测距，采用限幅滤波与卡尔曼滤波
  */
void Get_Distance_Left(void)
{
  u16 dis=0,temp=0;
  u32 time_old=0,time_now=0,time_cnt=0;
  u32 reload=SysTick->LOAD;

  TIM5CH3_CAPTURE_STA=0;
  time_old=SysTick->VAL;

  TIM_Cmd(TIM5,ENABLE);
  GPIO_SetBits(GPIOC,GPIO_Pin_13);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);

  while(time_cnt<45000){                    //5ms
    if(TIM5CH3_CAPTURE_STA&0X80)
      break;

    time_now=SysTick->VAL;
    if(time_now<=time_old)
      time_cnt+=time_old-time_now;
    else
      time_cnt+=reload-time_now+time_old;
    time_old=time_now;
  }

  if(TIM5CH3_CAPTURE_STA&0X80){
    temp = TIM5CH3_CAPTURE_VAL;            //得到总的高电平时间
    dis = temp * 170 / 1000;
    __Sensordata.wheel_left=dis;
    kalmanfilter_l(&dis);
    dis=dis/10;
    __distance.left=dis;
  }
  else{
    __distance.left=100;
    TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising);       //设置为上升沿捕获
  }

  TIM_Cmd(TIM5,DISABLE);                   //失能定时器3
  TIM5CH3_CAPTURE_STA|=0X80;               //标记完成
  __Sensordata.dis_left=__distance.left;
}

/**
  * @brief 测量右墙的距离
  * @param None
  * @retval None
  * @details trig-->PC.12  echo-->PB.0  TIM3_CH3
  *          毫米级测距，采用限幅滤波与卡尔曼滤波
  */
void Get_Distance_Right(void)
{
  u16 dis=0,temp=0;
  u32 time_old=0,time_now=0,time_cnt=0;
  u32 reload=SysTick->LOAD;

  TIM3CH3_CAPTURE_STA=0;
  time_old=SysTick->VAL;

  TIM_Cmd(TIM3,ENABLE);
  GPIO_SetBits(GPIOC,GPIO_Pin_12);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_12);


  while(time_cnt<45000){                    //5ms
    if(TIM3CH3_CAPTURE_STA&0X80)
      break;

    time_now=SysTick->VAL;
    if(time_now<=time_old)
      time_cnt+=time_old-time_now;
    else
      time_cnt+=reload-time_now+time_old;
    time_old=time_now;
  }

  if(TIM3CH3_CAPTURE_STA&0X80)
  {
    temp = TIM3CH3_CAPTURE_VAL;             //得到总的高电平时间
    dis = temp * 170 / 1000;
    __Sensordata.fire_sensor=dis;
    kalmanfilter_r(&dis);
    dis/=10;
    __distance.right=dis;
  }
  else
  {
    __distance.right=100;
    TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);       //设置为上升沿捕获
  }
  TIM_Cmd(TIM3,DISABLE);                   //失能定时器3
  TIM3CH3_CAPTURE_STA|=0X80;               //标记完成
  __Sensordata.dis_right=__distance.right;
}


void Get_Distance_Front(void)
{
  u16 dis=0,temp=0;
  u32 time_old=0,time_now=0,time_cnt=0;
  u32 reload=SysTick->LOAD;

  TIM2CH2_CAPTURE_STA=0;
  time_old=SysTick->VAL;

  TIM_Cmd(TIM2,ENABLE);                     //使能定时器2
  GPIO_SetBits(GPIOC,GPIO_Pin_11);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_11);

  while(time_cnt<45000){                    //5ms
    if(TIM2CH2_CAPTURE_STA&0X80)
      break;

    time_now=SysTick->VAL;
    if(time_now<=time_old)
      time_cnt+=time_old-time_now;
    else
      time_cnt+=reload-time_now+time_old;
    time_old=time_now;
  }

  if(TIM2CH2_CAPTURE_STA&0X80){
    temp = TIM2CH2_CAPTURE_VAL;             //得到总的高电平时间
    dis = temp * 170 / 1000;
    dis/=10;
    __distance.front=dis;
  }
  else{
    __distance.front=100;
    TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);       //设置为上升沿捕获
  }

  TIM_Cmd(TIM2,DISABLE);                   //失能定时器2
  TIM2CH2_CAPTURE_STA|=0X80;               //标记完成
  __Sensordata.dis_front=__distance.front;
}

/**
  * @brief 测量前右左三测的距离
  * @param None
  * @retval None
  * @details 
  */
void Get_Distance(void)
{
  Get_Distance_Right();
  Get_Distance_Left();
  Get_Distance_Front();
}
