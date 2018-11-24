# USART通信基本测试

## 1. 源码

main.c

```c
#include "stm32f10x.h"

void Usart1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStrue;
  USART_InitTypeDef USART_InitStrue;
  NVIC_InitTypeDef NVIC_InitStrue;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
  
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
  
  USART_InitStrue.USART_BaudRate=115200;
  USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
  USART_InitStrue.USART_Parity=USART_Parity_No;
  USART_InitStrue.USART_StopBits=USART_StopBits_1;
  USART_InitStrue.USART_WordLength=USART_WordLength_8b;
  
  USART_Init(USART1,&USART_InitStrue);
  
  USART_Cmd(USART1,ENABLE);//使能串口1
  
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启接收中断
  
  NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
  NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
  NVIC_Init(&NVIC_InitStrue);
  
}

void USART1_IRQHandler(void)
{
  u8 buff;
  if(USART_GetITStatus(USART1,USART_IT_RXNE))
  {
    buff= USART_ReceiveData(USART1);
    USART_SendData(USART1,buff);
  }
}
 
 int main(void)
 {	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Usart1_Init();
   while(1);
 }
```

## 2. GPIO口速度选择

I/O口输出模式下有三种输出速度可选（2MHz，10MHz，50MHz），这个速度是指I/O口驱动电路的响应速度；I/O管脚内部有多个响应不同的驱动电路，用户可以根据自己的需要选择合适的驱动电路。

高低频比较  
高频驱动电路：输出频率高，噪音大，功耗高，电磁干扰强；  
低频驱动电路：输出频率低，噪音小，功耗低，电磁干扰弱；提高系统EMI（电磁干扰）性能；

总结：通过选择速度来选择不同的输出驱动模块，达到最佳的噪音控制和降低功耗的目的如果需要选择较高频率信号，但是却选择了低频驱动模块，很有可能会失真的输出信号；所以GPIO的引脚速度应与应用匹配。

举几个栗子：

1. 对于串口来说，加入最大波特率为115200，这样只需要用2M的GPIO的引脚速度就可以了，省电噪音又小；
2. 对于I2C接口，假如使用400 000波特率，若想把余量留大一些，2M的GPIO引脚速度或许是不够，这时可以选用10M的GPIO引脚速度；
3. 对于SPI接口，假如使用18M或9M的波特率，用10M的GPIO口也不够用了，需要选择呢50M的GPIO引脚速度

## 端口复用

![端口复用]

![引脚配置]

[端口复用]: <./img/9.png>
[引脚配置]: <./img/10.png>