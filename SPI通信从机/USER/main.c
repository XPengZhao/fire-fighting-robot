#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "flash.h"

//ALIENTEK Mini STM32�����巶������20
//SPIʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
//Ҫд�뵽W25Q64���ַ�������
const u8 TEXT_Buffer[]={"successful!"};
#define SIZE sizeof(TEXT_Buffer)	 
 int main(void)
 { 
	u8 key;
	u16 i=0,j=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
	KEY_Init();				//������ʼ��		 	
	SPI_Flash_Init();  		//SPI FLASH ��ʼ�� 	 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"SPI TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	

	FLASH_SIZE=8*1024*1024;	//FLASH ��СΪ8M�ֽ�
  	POINT_COLOR=BLUE;		//��������Ϊ��ɫ	  
	while(1)
	{
		if(j==SIZE)
		{
			LCD_ShowString(60,190,200,16,16,"complete!");//�������
			break;
		}
		else
			datatemp[j++]=SPI_I2S_ReceiveData(SPI1);
		LCD_ShowString(60,190,200,16,16,datatemp);
	}
}

