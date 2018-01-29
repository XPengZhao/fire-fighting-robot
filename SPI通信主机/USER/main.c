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
	LCD_ShowString(60,130,200,16,16,"WK_UP:Write  KEY0:Read");	//显示提示信息		
	while(SPI_Flash_ReadID()!=W25Q64)							//检测不到W25Q64
	{
		LCD_ShowString(60,150,200,16,16,"25Q64 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
	LCD_ShowString(60,150,200,16,16,"25Q64 Ready!");

	FLASH_SIZE=8*1024*1024;	//FLASH 大小为8M字节
  	POINT_COLOR=BLUE;		//设置字体为蓝色
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)	//WK_UP按下,发送TEXT_Buffer中的字符串
		{
			LCD_Fill(0,170,239,319,WHITE);//清除半屏
 			LCD_ShowString(60,170,200,16,16,"Start Send！");
			for(j=0;j<SIZE;SPI_I2S_SendData(SPI1,TEXT_Buffer[j++]));
			LCD_ShowString(60,170,200,16,16,"W25Q64 Write Finished!");	//提示传送完成
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}

