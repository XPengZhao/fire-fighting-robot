#include "main.h"

void taskloop(void)
{
  static u32 system_25ms=0;
  system_25ms++;

  Duty_25ms();
  if(system_25ms%2==0)
    Duty_50ms();
  if(system_25ms%4==0)
    Duty_100ms();
  if(system_25ms%20==0)
    Duty_500ms();
}

void Duty_25ms(void)
{


	delay_ms(1000);
	FanMotor_Open();
	turn_left45();
	delay_ms(2000);
	turn_left45_return();
	FanMotor_Close();
	delay_ms(1000);
}

void Duty_50ms(void)
{

}

void Duty_100ms(void)
{

}

void Duty_500ms(void)
{
}
