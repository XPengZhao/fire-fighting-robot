#include "motor.h"
#include "delay.h"


//PC.0-->右电机 1300us向前		PC.1-->左电机 1700向前

void Motor_Init(void){
    GPIO_InitTypeDef GPIO_Initstructure;                  //定义结构类型变量
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //使能PC端口时钟

    GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;               //左电机接PC0
    GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽输出
    GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_Initstructure);
    GPIO_SetBits(GPIOC,GPIO_Pin_0);

    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_1;             //右电机接PC1
    GPIO_Init(GPIOC,&GPIO_Initstructure);
    GPIO_SetBits(GPIOC,GPIO_Pin_1);  
}

void Direction_Adjust(int distance){
	
}
