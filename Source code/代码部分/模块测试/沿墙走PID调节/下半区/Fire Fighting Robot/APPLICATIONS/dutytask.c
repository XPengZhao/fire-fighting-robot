#include "main.h"

void taskloop(void)
{
  static u32 system_20ms=0;
  system_20ms++;

  Duty_20ms();
  if(system_20ms%2==0)
    Duty_40ms();
  if(system_20ms%4==0)
    Duty_80ms();
  if(system_20ms%20==0)
    Duty_400ms();
}

void Duty_20ms(void)
{
  Pos_ControlLeft();
}

void Duty_40ms(void)
{
  
}

void Duty_80ms(void)
{

}

void Duty_400ms(void)
{
}
