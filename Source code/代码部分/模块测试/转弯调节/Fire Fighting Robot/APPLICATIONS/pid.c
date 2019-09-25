#include "main.h"

//  float P,I,D,FF,MaxError
static PIDParams pos_pidparam={0,0,0,0,80};

//  float Error,Target;
static PIDState  pos_pidstate={0,15};

//  int8_t ne_min,ne_two,ne_one,zero,one,two,max;比例参数
//static FuzzyParam fuzzyparam={-35,-20,-15,0,15,20,35};
static FuzzyParam fuzzyparam={-33,-20,-13,0,29,36,48};

//  int8_t ne_min,ne_two,ne_one,zero,one,two,max;微分参数
//static FuzzyD fuzzyd={28,15,15,40,15,15,28};
static FuzzyD fuzzyd={29,20,15,5,15,20,29};

/*
now_dis 本次测量的距离    last_dis 上次测量的距离
now_diff 本次误差信号量    last_diff 上次误差信号量
*/
void Pos_ControlRight(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Right();
    e = pos_pidstate.Target - __distance.right;
    de = e - pos_pidstate.Error;
    pos_pidstate.Error = e;

    //模糊规则
    if(e>2)
    {
      ctrl_signal=fuzzyparam.max+fuzzyd.max*de;
    }
    else if(e==2)
    {
      ctrl_signal=fuzzyparam.two+fuzzyd.two*de;
    }
    else if(e==1)
    {
      ctrl_signal=fuzzyparam.one+fuzzyd.one*de;
    }
    else if(e==0)
    {
      ctrl_signal=fuzzyparam.zero+fuzzyd.zero*de;
    }
    else if(e==-1)
    {
      ctrl_signal=fuzzyparam.ne_one+fuzzyd.ne_one*de;
    }
    else if(e==-2)
    {
      ctrl_signal=fuzzyparam.ne_two+fuzzyd.ne_two*de;
    }
    else if(e<-2)
    {
      ctrl_signal=fuzzyparam.ne_min+fuzzyd.ne_min*de;
    }

    if(ctrl_signal>pos_pidparam.MaxError)
    {
      ctrl_signal=pos_pidparam.MaxError;
    }
    else if(ctrl_signal<-pos_pidparam.MaxError)
    {
      ctrl_signal=-pos_pidparam.MaxError;
    }

    if(e>0)                  //右偏
    {
      MotorLeft(86-ctrl_signal);
      MotorRight(100);
    }
    else if(e<0)             //左偏
    {
      MotorLeft(86);
      MotorRight(100+ctrl_signal+de*16);
    }
    else if(de>0)       //左边回来
    {
      MotorLeft(86-ctrl_signal);
      MotorRight(100);
    }
    else                //右边回来
    {
      MotorLeft(86);
      MotorRight(100+ctrl_signal+de*16);
    }

}

void Pos_ControlLeft(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Left();
    e = pos_pidstate.Target - __distance.left;
    de = e - pos_pidstate.Error;
    pos_pidstate.Error = e;

    //模糊规则
    if(e>2)
    {
      ctrl_signal=fuzzyparam.max+fuzzyd.max*de;
    }
    else if(e==2)
    {
      ctrl_signal=fuzzyparam.two+fuzzyd.two*de;
    }
    else if(e==1)
    {
      ctrl_signal=fuzzyparam.one+fuzzyd.one*de;
    }
    else if(e==0)
    {
      ctrl_signal=fuzzyparam.zero+fuzzyd.zero*de;
    }
    else if(e==-1)
    {
      ctrl_signal=fuzzyparam.ne_one+fuzzyd.ne_one*de;
    }
    else if(e==-2)
    {
      ctrl_signal=fuzzyparam.ne_two+fuzzyd.ne_two*de;
    }
    else if(e<-2)
    {
      ctrl_signal=fuzzyparam.ne_min+fuzzyd.ne_min*de;
    }

    if(ctrl_signal>pos_pidparam.MaxError)
    {
      ctrl_signal=pos_pidparam.MaxError;
    }
    else if(ctrl_signal<-pos_pidparam.MaxError)
    {
      ctrl_signal=-pos_pidparam.MaxError;
    }

    if(e>0)                  //左偏
    {
      MotorLeft(86);
      MotorRight(100-ctrl_signal-de*16);
    }
    else if(e<0)             //右偏
    {
      MotorLeft(86+ctrl_signal);
      MotorRight(100);
    }
    else if(de>0)       //右边回来
    {
      MotorLeft(86);
      MotorRight(100-ctrl_signal-de*16);
    }
    else                //左边回来
    {
      MotorLeft(86+ctrl_signal);
      MotorRight(100);
    }

}



void pid_left(void)
{
  static int8_t adjust_flag=0,count=0,e=0;
  int kp=5;
  if(adjust_flag==0)                                //不在调节过程中
  {
    Get_Distance_Left();
    e=__distance.left-14;
    if(e>3)
      e=4;
    else if(e<-4)
      e=-4;
    if(e>2)
        adjust_flag=1;
    else if(e<-2)
        adjust_flag=2;
  }
  else                                             //在调节过程中
  {
    switch(adjust_flag)
    {
      case 1:
          if(count<e*kp){
          MotorLeft(50);
          MotorRight(100);
          count++;
          }
          else if(count<2*e*kp){
            MotorLeft(86);
            MotorRight(49);
            count++;
          }
          else{
            MotorLeft(86);
            MotorRight(100);
            adjust_flag=0;
            count=0;
          }
          break;
      
      case 2:                               //左偏
          if(count<-e*kp){
          MotorLeft(86);
          MotorRight(49);
          count++;
          }
          else if(count<-2*e*kp){
            MotorLeft(50);
            MotorRight(100);
            count++;
          }
          else{
            MotorLeft(86);
            MotorRight(100);
            adjust_flag=0;
            count=0;
          }
          break;
    }
  }
}

void AngleAdjust_L(void)
{
  int8_t last_dis=__distance.left,e=0;
  Get_Distance_Left();
  if(last_dis==0 || last_dis==100)
    return;
  e=__distance.left-last_dis;

  if(__distance.left>18 || __distance.left<12){
    if(e>0){                 //向右偏
      MotorLeft(0);
      MotorRight(100);
    }
    else if(e<0){
      MotorLeft(100);
      MotorRight(0);
    }
  }
  else{
    MotorLeft(86);
    MotorRight(100);
  }
  
  MotorLeft(86);
  MotorRight(100);
}


/**
  * @brief 通过编码器走直线
  *
  */
void GoStraight(void)
{
  int e;
  float kp=16,u=0;
  e=__left_encoder_count-__right_encoder_count;    //>0 左轮快；<0 右轮慢
  if(e>2)
    e=3;
  else if(e<-2)
    e=-3;

  u=kp*e;
  MotorLeft(86-u);
  MotorRight(100+u-16);
}
