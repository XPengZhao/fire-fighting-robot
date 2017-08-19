#include "motor.h"
#include "delay.h"


//PC.0-->右电机    PC.1-->左电机

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

void Motor_Run(int distance){
	delay_init();
    if(distance>13){
		Motor0=1;
		Motor1=1;
		
		delay_us(1500);
		Motor0=0;
		delay_us(200);
		Motor1=0;                                         //右电机1700us向前
		delay_us(18300);
		Motor_Run(10);
        
    }
    else if(distance<7){
        Motor0=1;
		Motor1=1;
		
		delay_us(1300);                                   //左电机1700us向前
		Motor0=0;
		delay_us(200);
		Motor1=0;
		delay_us(18500);
		Motor_Run(10);
    }
    else {
        Motor0=1;
		Motor1=1;
		
		delay_us(1300);
		Motor0=0;
		delay_us(400);
		Motor1=0;
        delay_us(18300);
		
    }

}
