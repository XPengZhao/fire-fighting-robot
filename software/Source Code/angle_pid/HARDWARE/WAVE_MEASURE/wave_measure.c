#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"

/**
  * ----------------------------------------------------------------------------
  * 前超声波 echo-->PA.1    trig-->PC.11    TIM2_CH2
  * 右超声波 echo-->PB.0    trig-->PC.12    TIM3_CH3
  * 左超声波 echo-->PA.2    trig-->PC.13    TIM5_CH3
  * 主函数使用时先设置中断分组 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  * 接着调用 Wave_Init();
  * 最后调用 Get_front();即可得出距离
  */


 Distance distance;

 u8  TIM3CH3_CAPTURE_STA=0; //输入捕获状态
 u16 TIM3CH3_CAPTURE_VAL;   //输入捕获值
 u8  TIM2CH2_CAPTURE_STA=0; //输入捕获状态
 u16 TIM2CH2_CAPTURE_VAL;   //输入捕获值
 u8  TIM5CH3_CAPTURE_STA=0; //输入捕获状态
 u16 TIM5CH3_CAPTURE_VAL;   //输入捕获值



//定时器通道输入捕获配置
void Wave_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    //使能各个时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //使能TIM2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    //使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);    //使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //使能GPIOB时钟

    /*-------------------------初始化trig端口---------------------------------
     * PC.11-->front    PC.12-->right   PC.13-->left
     */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13);
    ////

    /*---------------------------初始化echo端口--------------------------------
     * PA.1 front   PA.2 left   PB.0 right
     */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //PA.1与PA.2 上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //根据设定值初始化PA.1与PA.2
    GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);      //PA.1与PA.2 下拉电位

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;              //PB.0 清除之前设置  
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  //根据设定值初始化PB.0
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);                       //PB.0 下拉电位
    ////

    /*---------------------------配置定时器时基参数-------------------------------
     * TIM2-->front   TIM3-->right    TIM5-->left
     */
    TIM_TimeBaseStructure.TIM_Period = ARR;                 //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler =PSC;               //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    ////

    /*--------------------------配置定时器捕获参数--------------------------------
     * TIM2-->front   TIM3-->right    TIM5-->left
     */
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //直接映射
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //配置输入分频,不分频 
    TIM_ICInitStructure.TIM_ICFilter = 0x3; //IC1F=0011 配置输入滤波器进行滤波
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    ////

    /*---------------------------设置中断分组------------------------------------
     * TIM2-->front   TIM3-->right    TIM5-->left
     */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
    NVIC_Init(&NVIC_InitStructure);
    ////

    /*---------------------------使能中断与定时器---------------------------------
     * TIM2_CH2-->front   TIM3_CH3-->right    TIM5_CH3-->left
     */
    TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
    TIM_Cmd(TIM2,ENABLE);    //使能定时器2
    TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
    TIM_Cmd(TIM3,ENABLE);    //使能定时器3
    TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
    TIM_Cmd(TIM5,ENABLE);    //使能定时器5
}

//定时器2中断服务程序	 
void TIM2_IRQHandler(void)
{
    
    if((TIM2CH2_CAPTURE_STA&0X80)==0)
        if((TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET))  //判断是否发生更新中断
            if(TIM2CH2_CAPTURE_STA&0X40)
            {
                if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
                {
                    TIM2CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
                    TIM2CH2_CAPTURE_VAL=0XFFFF;
                }
                else 
                    TIM2CH2_CAPTURE_STA++;
            }
    if(TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//通道2发生捕获事件
    {
        if(TIM2CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
        { 			
            TIM2CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一个完整脉冲
            TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);
            TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC3P=0 设置为上升沿捕获
        }
        else                            //还未开始,第一次捕获上升沿
        {
            TIM2CH2_CAPTURE_STA=0;      //清空
            TIM2CH2_CAPTURE_VAL=0;
            TIM_SetCounter(TIM2,0);
            TIM2CH2_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
            TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC3P=1 设置为下降沿捕获
        }    
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
}

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{
    
    if((TIM3CH3_CAPTURE_STA&0X80)==0)
        if((TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET))  //判断是否发生更新中断
            if(TIM3CH3_CAPTURE_STA&0X40)
            {
                if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
                {
                    TIM3CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
                    TIM3CH3_CAPTURE_VAL=0XFFFF;
                }
                else
                    TIM3CH3_CAPTURE_STA++;
            }
    if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//通道3发生捕获事件
    {
        if(TIM3CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
        {
            TIM3CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一个完整脉冲
            TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);
            TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC3P=0 设置为上升沿捕获
        }
        else                            //还未开始,第一次捕获上升沿
        {
            TIM3CH3_CAPTURE_STA=0;      //清空
            TIM3CH3_CAPTURE_VAL=0;
            TIM_SetCounter(TIM3,0);
            TIM3CH3_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
            TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC3P=1 设置为下降沿捕获
        }    
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位
}

//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{
    if((TIM5CH3_CAPTURE_STA&0X80)==0)
        if((TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET))  //判断是否发生更新中断
            if(TIM5CH3_CAPTURE_STA&0X40)
            {
                if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
                {
                    TIM5CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
                    TIM5CH3_CAPTURE_VAL=0XFFFF;
                }
                else 
                    TIM5CH3_CAPTURE_STA++;
            }
    if(TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//通道3发生捕获事件
    {
        if(TIM5CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
        { 			
            TIM5CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一个完整脉冲
            TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);
            TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC3P=0 设置为上升沿捕获
        }
        else                            //还未开始,第一次捕获上升沿
        {
            TIM5CH3_CAPTURE_STA=0;      //清空
            TIM5CH3_CAPTURE_VAL=0;
            TIM_SetCounter(TIM5,0);
            TIM5CH3_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
            TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC3P=1 设置为下降沿捕获
        }    
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位
}

void Get_Distance(void)    //返回超声波测得距离
{
	
    u32 temp1=0,temp2=0,temp3=0; 
    int front=0,right=0,left=0;
    int i=0,j=0,k=0;
    int l=0,m=0,n=0;
    int total0=0,total1=0,total2=0;
    int average0[COUNT]={0},average1[COUNT]={0},average2[COUNT]={0};
	uart_init(9600);
	
    for(i=0;i<COUNT;i++)
    {
        while((TIM3CH3_CAPTURE_STA&0X80)==0||(TIM2CH2_CAPTURE_STA&0X80)==0||(TIM5CH3_CAPTURE_STA&0X80)==0)
        {
            GPIO_SetBits(GPIOC,GPIO_Pin_11);     //trig 拉高电平 
            GPIO_SetBits(GPIOC,GPIO_Pin_12);     
            GPIO_SetBits(GPIOC,GPIO_Pin_13); 
            delay_us(20);
            GPIO_ResetBits(GPIOC,GPIO_Pin_11);  //trig 拉低电平
            GPIO_ResetBits(GPIOC,GPIO_Pin_12);  
            GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			delay_ms(20);
		}
        if(TIM2CH2_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
        {
            temp1=TIM2CH2_CAPTURE_STA&0X3F;
            temp1*=50000;                   //溢出时间总和
            temp1+=TIM2CH2_CAPTURE_VAL;     //得到总的高电平时间
            front=temp1 *170;
            front /= 1000;

            /*------------------------------滤波部分---------------------------*/
            if(front>=2&&front<3000)
            {
            //升序排序
                if(m==0)
                    average0[m++]=front;
                else
                {
                    if(front>=average0[m-1])
                        average0[m++]=front;
                    else
                    {
                        for(j=m;j>0;j--)
                            average0[j]=average0[j-1];
                        average0[0]=front;
                        m++;
                    }
                }
            ////
            }
            /*----------------------------滤波部分----------------------------*/
            TIM2CH2_CAPTURE_STA=0;          //开启下一次捕获
        }

        if(TIM3CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
        {
            temp2=TIM3CH3_CAPTURE_STA&0X3F;
            temp2*=50000;                   //溢出时间总和
            temp2+=TIM3CH3_CAPTURE_VAL;     //得到总的高电平时间
            right=temp2 *170;
            right /= 1000;
            /*------------------------------滤波部分---------------------------*/
            if(right>=2&&right<3000)
            {
            //升序排序
                if(n==0)
                    average1[n++]=right;
                else
                {
                    if(right>=average1[n-1])
                        average1[n++]=right;
                    else
                    {
                        for(j=n;j>0;j--)
                            average1[j]=average1[j-1];
                        average1[0]=right;
                        n++;
                    }
                }
            ////
            }
            /*----------------------------滤波部分----------------------------*/ 
            TIM3CH3_CAPTURE_STA=0;          //开启下一次捕获
        }

        if(TIM5CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
        {
            temp3=TIM5CH3_CAPTURE_STA&0X3F;
            temp3*=50000;                   //溢出时间总和
            temp3+=TIM5CH3_CAPTURE_VAL;     //得到总的高电平时间
            left=temp3 *170;
            left /= 1000;
            /*------------------------------滤波部分---------------------------*/
            if(left>=2&&left<3000)
            {
            //升序排序
                if(l==0)
                    average2[l++]=left;
                else
                {
                    if(left>=average2[l-1])
                        average2[l++]=left;
                    else
                    {
                        for(j=l;j>0;j--)
                            average2[j]=average2[j-1];
                        average2[0]=left;
                        l++;
                    }
                }
            ////
            }
            /*----------------------------滤波部分----------------------------*/ 
            TIM5CH3_CAPTURE_STA=0;          //开启下一次捕获
        }
    }
    for(k=1;k<m-1;k++)
        total0+=average0[k];
    front=total0/(m-2);
    for(k=1;k<n-1;k++)
        total1+=average1[k];
    right=total1/(n-2);
    for(k=1;k<l-1;k++)
        total2+=average2[k];
    left=total2/(l-2);
    distance.front=front;
	distance.right=right;
	distance.left=left;
}
