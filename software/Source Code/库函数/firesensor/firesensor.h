#ifndef __firesensor_H
#define __firesensor_H	
#include "sys.h"

#define N 50
#define M 2

typedef struct{
    u16  left;
	  u16 right;
}Fire;


extern vu16 AD_Value[N][M]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
extern vu16 After_filter[M]; //���������ƽ��ֵ֮��Ľ��
extern Fire sig;       //������յ�ѹֵ



void FAN_Init(void);    //���ȳ�ʼ���ӿ� 
void fan_off();
void fan_on();
void ADC1_Configuration(void);//adc1����
void DMA_Configuration(void);   //DMA����
 u16 GetVolt(u16 advalue);  //�������ź�ת����ģ���ź�
 void filter(void);   //��SIG1��SIG2ת����������źţ�����N�κ���ƽ��ֵ�������ݸ����ȶ�
 void Get_Fire(void);
 
#endif 
