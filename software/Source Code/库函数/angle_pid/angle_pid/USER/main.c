#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wave_measure.h"
#include "Motor_Pwm.h"
#include "Move.h"

Distance distance={0,0,0},last_distance={0,0,0};
Angle angle={0,0};
Angle last_angle={0,0};

int main(void)
{ 
    int i,time=0;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
    delay_init();                                  // 延时函数初始化
    uart_init(9600);
    Wheel_Init();
    Wave_Init();
    parameter_init();

    while(1)
    {
        forward_right();
        distance.front=Get_Distance_Front();
        if(distance.front<15)
        {
            turn_left();
            delay_ms(640);
        }
    }
}
