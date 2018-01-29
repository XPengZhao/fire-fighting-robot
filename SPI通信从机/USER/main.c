#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "flash.h"

//ALIENTEK Mini STM32开发板范例代码20
//SPI实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
//要写入到W25Q64的字符串数组
const u8 TEXT_Buffer[]={"successful!"};
#define SIZE sizeof(TEXT_Buffer)	 
 int main(void)
 { 
	u8 key;
	u16 i=0,j=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	KEY_Init();				//按键初始化		 	
	SPI_Flash_Init();  		//SPI FLASH 初始化 	 
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"SPI TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/9");	

	FLASH_SIZE=8*1024*1024;	//FLASH 大小为8M字节
  	POINT_COLOR=BLUE;		//设置字体为蓝色	  
	while(1)
	{
		if(j==SIZE)
		{
			LCD_ShowString(60,190,200,16,16,"complete!");//传输完成
			break;
		}
		else
			datatemp[j++]=SPI_I2S_ReceiveData(SPI1);
		LCD_ShowString(60,190,200,16,16,datatemp);
	}
}

