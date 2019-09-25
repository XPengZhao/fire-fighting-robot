#include "main.h"

static u8 __FilterFlush_l=0;
static u8 __FilterFlush_r=0;
/*
Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
R:测量噪声，R增大，动态响应变慢，收敛稳定性变好
x_last=x(k-1|k-1)上一时刻的距离    p_last=p(k-1|k-1)上一时刻的协方差，上个时刻的迭代值
x_mid=x(k|k-1)，这一时刻的预测距离    p_mid=p(k|k-1)预测协方差
z_measure 测量值    R测量噪声，可理解为测量协方差
x_now计算得出的本时刻距离，p_now，计算出的本时刻协方差，供下一时刻迭代
*/
void kalmanfilter_r(u16 *z_measure)
{
  static float x_mid1,x_last1=0,p_mid1,p_last1=0,p_now1,x_now1=0;
  static float Q1=ProcessNiose_Q,kg1,R1=MeasureNoise_R;

  if(!__FilterFlush_r)
  {
    __FilterFlush_r=1;
    x_last1=*z_measure;
  }
  x_mid1=x_last1;                         //预测与上一时刻一致
  p_mid1=p_last1+Q1;                      //预测协方差为上一时刻协方差+Q_Noise
  kg1=p_mid1/(p_mid1+R1);                 //kg为kalman filter，R 为测量噪声
  x_now1=x_mid1+kg1*(*z_measure-x_mid1);  //计算出的最优值
  p_now1=(1-kg1)*p_mid1;                  //最优值对应的covariance
  p_last1=p_now1;                         //更新covariance 值
  x_last1=x_now1;                         //更新系统状态值
  *z_measure=(u16)x_now1;
}

void kalmanfilter_l(u16 *z_measure)
{
  static float x_mid2,x_last2=0,p_mid2,p_last2=0,p_now2,x_now2=0;
  static float Q2=ProcessNiose_Q,kg2,R2=MeasureNoise_R;

  if(!__FilterFlush_l)
  {
    __FilterFlush_l=1;
    x_last2=*z_measure;
  }
  x_mid2=x_last2;                       //预测与上一时刻一致
  p_mid2=p_last2+Q2;                     //预测协方差为上一时刻协方差+Q_Noise
  kg2=p_mid2/(p_mid2+R2);                 //kg为kalman filter，R 为测量噪声
  x_now2=x_mid2+kg2*(*z_measure-x_mid2);  //计算出的最优值
  p_now2=(1-kg2)*p_mid2;                   //最优值对应的covariance
  p_last2=p_now2;                         //更新covariance 值
  x_last2=x_now2;                            //更新系统状态值
  *z_measure=(u16)x_now2;
}

void FilterFlush(void)
{
  __FilterFlush_l=0;
  __FilterFlush_r=0;
}
