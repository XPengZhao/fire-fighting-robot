#include "main.h"

/**/
void fire_fighting()
{

    if(__judge_result==FIRE_ON_LEFT){         //检测到左边有火
      FanMotor_Open();                      //开风扇
      turn_left45();                        //左转45
      delay_ms(1000);                       //对着目的点吹1000ms
      turn_left45_return();                 //回正
      FanMotor_Close();                     //关风扇
    }

    if(__judge_result==FIRE_ON_RIGHT){
      FanMotor_Open();
      turn_right45();
      delay_ms(1000);
      turn_right45_return();
      FanMotor_Close();
    }
    
    if(__judge_result==NO_FIRE){
      FanMotor_Close();
      return;
    }

  return ;
}
