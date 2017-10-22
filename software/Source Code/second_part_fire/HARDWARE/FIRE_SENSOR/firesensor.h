#ifndef __firesensor_H
#define __firesensor_H	
#include "sys.h"

#define N 50
#define M 2

typedef struct{
    u16  left;
	  u16 right;
}Fire;


extern vu16 AD_Value[N][M]; //用来存放ADC转换结果，也是DMA的目标地址
extern vu16 After_filter[M]; //用来存放求平均值之后的结果
extern Fire sig;       //存放最终电压值



void FAN_Init(void);    //风扇初始化接口 
void fan_off(void);
void fan_on(void);
void ADC1_Configuration(void);//adc1配置
void DMA_Configuration(void);   //DMA配置
 u16 GetVolt(u16 advalue);  //将数字信号转换成模拟信号
 void filter(void);   //把SIG1和SIG2转换后的数字信号，采样N次后求平均值，让数据更加稳定
 void Get_Fire(void);
 void PutOff_LeftFire(void);
 void PutOff_RightFire(void);
 
#endif 
