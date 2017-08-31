#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"

/**
  * ----------------------------------------------------------------------------
  * 右超声波接PB.0
  * 主函数使用时先设置中断分组 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  * 接着调用 Wave_Init();
  * 最后调用 Get_Distance();即可得出距离
  */

u8  TIM3CH3_CAPTURE_STA;            //保存捕获状态
u16	TIM3CH3_CAPTURE_VAL;            //保存捕获值

TIM_ICInitTypeDef  TIM3_ICInitStructure;

void Wave_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);   //使能GPIOB时钟

    /*------------------------------------------------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //trig-->PE.0端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化PE.0
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //trig 下拉电位
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //echo-->PB.0 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //IO口速度为50MHz
    GPIO_ResetBits(GPIOB,GPIO_Pin_0); 						 //echo 下拉电位

    /*------------------------------------------------------------------------*/
    //初始化定时器3 TIM3	 
    TIM_TimeBaseStructure.TIM_Period = ARR_WAVE; 				//设定计数器自动重装值 
    TIM_TimeBaseStructure.TIM_Prescaler =PSC_WAVE; 				//预分频器   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS= Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    /*------------------------------------------------------------------------*/
    //初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC2S=01 	选择输入端 IC2映射到TI2上
    TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
    TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
    TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
    TIM3_ICInitStructure.TIM_ICFilter = 0x3;//IC1F=0011 配置输入滤波器进行滤波
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);

    /*------------------------------------------------------------------------*/
    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM5中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
    
    TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
    TIM_Cmd(TIM3,ENABLE); 	//使能定时器5
}

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET))
		if((TIM3CH3_CAPTURE_STA&0X80)==0)
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

int Get_Distance(void)
{
    u32 temp=0; 
    int distance=0;
    int i,total=0,n=0;
    int average[10]={0};
    delay_init();
    for(i=0;i<COUNT;i++)
    {
        while((TIM3CH3_CAPTURE_STA&0X80)==0)
        {
            GPIO_SetBits(GPIOC,GPIO_Pin_13);     //PE.0-->trig 拉低电平 
            delay_us(20);
            GPIO_ResetBits(GPIOC,GPIO_Pin_13);	//PE.0-->trig 拉高电平
        }
        if(TIM3CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
        {
            temp=TIM3CH3_CAPTURE_STA&0X3F;
            temp*=50000;					//溢出时间总和
            temp+=TIM3CH3_CAPTURE_VAL;		//得到总的高电平时间
            distance=temp *170;
            distance /= 10000;
            if(distance!=0&&distance<200)
                average[n++]=distance;
            TIM3CH3_CAPTURE_STA=0;			//开启下一次捕获
        }
    }
    for(i=0;i<n;i++)
        total+=average[i];
    distance=total/n;
    return distance;
}
