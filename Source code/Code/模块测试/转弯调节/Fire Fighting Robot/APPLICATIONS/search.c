#include "main.h"

u8 turn_count=1;                          //×ªÍä¼ÆÊý

void action1(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.left>40){
      __turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }

  }
}

void action2(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.right>40){
      __turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action3(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.right>40){
      __turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action4(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.right>40){
      __turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action5(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.right>40){
      __turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}


void action6(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.left>40){
      __turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }
  }
}

void action7(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.left>40){
      __turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }
  }
}

void action8(void)
{
  Get_Distance();
  GoStraight();
  if(__distance.front<19){
    if(__distance.left>40){
      __turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }
  }
}
