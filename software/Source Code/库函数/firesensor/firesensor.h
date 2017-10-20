#ifndef __firesensor_H
#define __firesensor_H	
#include "sys.h"

#define N 50
#define M 2

extern vu16 AD_Value[N][M]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
extern vu16 After_filter[M]; //���������ƽ��ֵ֮��Ľ��

void ADC1_Configuration(void);//adc1����
void DMA_Configuration();   //DMA����
 u16 GetVolt(u16 advalue);  //�������ź�ת����ģ���ź�
 void filter(void);   //��SIG1��SIG2ת����������źţ�����N�κ���ƽ��ֵ�������ݸ����ȶ�
 
 
#endif 
