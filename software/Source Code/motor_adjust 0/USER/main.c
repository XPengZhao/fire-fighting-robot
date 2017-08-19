#include "stm32f10x.h"
#include "motor.h"
#include "sys.h"
#include "delay.h"
int main(void)
{
  delay_init();
  Motor_Init();
  while(1)
	{
		Motor0=1;
		Motor1=1;
		
		delay_us(1500);
		Motor0=0;
		Motor1=0;
		delay_us(18500);
	}
}
