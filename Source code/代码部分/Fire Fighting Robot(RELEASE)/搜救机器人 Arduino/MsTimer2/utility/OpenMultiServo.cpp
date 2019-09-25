/*
 * Open_MultiServo.cpp
 *
 *  Created on: 2012-8-31
 *      Author: Administrator
 */


#include <OpenMultiServo.h>


/*********************************************************************************************
 * 74HC595与ATmega328P引脚连接定义(Ver 3.0)
 *********************************************************************************************/
#define ClkPin     		1  //PB1    移位时钟比锁存时钟早一个脉冲
#define DataPin         3  //PB3  串行数据输入端

#define Clk_High   		PORTB |= (1<<ClkPin)
#define Clk_Low    		PORTB &= ~(1<<ClkPin)
#define Data_High       PORTB |= (1<<DataPin)
#define Data_Low        PORTB &= ~(1<<DataPin)

volatile const long PwmPro = 40000;
/*********************************************************************************************
 *变量定义
 *********************************************************************************************/
uint16_t MultiServo::counter2;//计数器2
uint16_t MultiServo::servotime;//每隔servotime转一度
uint16_t MultiServo::servoLastAngle[8]={3162,3000,3000,3000,3000,3000,3000,3000};//备份当前位置
uint16_t MultiServo::servoDstAngle[8]={3162,3000,3000,3000,3000,3000,3000,3000};//存储舵机目标位置
uint16_t MultiServo::Parallel_HighWidSum=0;//并联电机正脉宽之和

/* 中断服务函数中用到的变量 */
volatile long MultiServo::low_width;//总低电平时间
volatile uint16_t MultiServo::servoNowAngle[8]={3162,3000,3000,3000,3000,3000,3000,3000};//存储舵机当前位置
volatile uint16_t MultiServo::servoId;//舵机编号
volatile long MultiServo::high_widthsum;//多路舵机脉宽总和
volatile bool MultiServo::done=false;//完成一次目标角度标志

/*********************************************************************************************
 *函数功能：初始化多路舵机(构造函数)
 *输入参数：无
 *输出参数：无
 *********************************************************************************************/
void MultiServo::InitOpenMultiChannelServo(void)
{
	InitHc595port();//初始化595驱动端口
	InitTimer1();//初始化16位定时器1
    InitServo();//初始化舵机

	int i=0;
	for(i=0;i<8;i++)
	{
		SetServo(i,servoDstAngle[i]);
	}
	TIMSK1 |= (1<<OCIE1A);//使能比较器A匹配中断
}

/*********************************************************************************************
 *函数功能：74HC595驱动IO初始化函数
 *输入参数：无
 *输出参数：无
 *********************************************************************************************/
void MultiServo::InitHc595port(void)
{
	DDRB |= (1<<ClkPin)|(1<<DataPin);//配置PB1和PB3为输出
	PORTB &= ~((1<<ClkPin)|(1<<DataPin));//PB1和PB3输出低电平
}

/*********************************************************************************************
 *函数功能：定时器1初始化函数
 *输入参数：无
 *输出参数：无
 *********************************************************************************************/
void MultiServo::InitTimer1(void)
{
	TCCR1A=0;
	TCCR1B=(1<<CS11);//将晶振8分频后作为定时时钟
	TCNT1=0;//计数初值
	OCR1A=2000;//比较匹配初值,对16MHz晶振进行8分频后，定时时钟为0.5us，0.5*2000=1ms
	sei();//使能全局中断
}
/*********************************************************************************************
 *函数功能：初始化多路舵机函数
 *输入参数：无
 *输出参数：无
 *********************************************************************************************/
void MultiServo::InitServo(void)
{
	high_widthsum=0;
	servoId=0;
	Parallel_HighWidSum = servoNowAngle[0]+servoNowAngle[1];

	int i=0;
	for(i=0;i<8;i++)
	{
		high_widthsum += servoNowAngle[i];//多路舵机当前位置对应的正脉宽之和
	}
	for(i=0;i<8;i++)
	{
		servoLastAngle[i] = servoNowAngle[i];//保存各路舵机当前角度
	}
	low_width = PwmPro - high_widthsum;//舵机控制周期（20ms）- 正脉宽之和 == 总的低电平
}
/*********************************************************************************************
 *定时器1比较器匹配中断服务函数
 *********************************************************************************************/

SIGNAL (TIMER1_COMPA_vect)
{
	if(!MultiServo::servoId)
	{
		//servoId=0
		Data_High;//数据线置“1”
		Clk_High;//时钟线置“1”,上升沿，将“1”移入移位寄存器，在下一个上升沿时被锁存到锁存寄存器
		Clk_Low;//时钟线置“0”
		Data_Low;//数据线置低,在下一个时钟被移入移位寄存器
	}
		Clk_High;//时钟线置"1"
		Clk_Low;//时钟线置"0"
	if(MultiServo::servoId==8)
	{
		OCR1A += MultiServo::low_width;//剩下的低电平时间
		MultiServo::servoId=0;
	}
	else
	{
		OCR1A += MultiServo::servoNowAngle[MultiServo::servoId];
		MultiServo::servoId++;
	}
}
/*********************************************************************************************
 *函数功能：初始化多路舵机函数
 *输入参数：servonum - 舵机编号
 *输出参数：   Angle      - 脉冲宽度
 *********************************************************************************************/
void MultiServo::SetServo(uint8_t servonum,uint16_t Angle)
{
	high_widthsum -= servoLastAngle[servonum];//将舵机的旧脉宽从总脉宽中去掉
	high_widthsum += Angle;//将新的脉宽加入
	servoLastAngle[servonum]=Angle;//更新舵机的旧脉宽
}
/*********************************************************************************************
 *函数功能：更新舵机当前角度函数
 *输入参数：无
 *输出参数：无

 *********************************************************************************************/
void MultiServo::CommandSet(void)
{

	uint8_t j=0;
	if(servoNowAngle[0]>servoDstAngle[0])	servoNowAngle[0] -= 27;
	if(servoNowAngle[0]<servoDstAngle[0])	servoNowAngle[0] += 27;
	if(servoNowAngle[1]>servoDstAngle[1])	servoNowAngle[1] -= 27;
	if(servoNowAngle[1]<servoDstAngle[1])	servoNowAngle[1] += 27;
	if(servoNowAngle[2]>servoDstAngle[2])	servoNowAngle[2] -= 27;
	if(servoNowAngle[2]<servoDstAngle[2])	servoNowAngle[2] += 27;
	if(servoNowAngle[3]>servoDstAngle[3])	servoNowAngle[3] -= 27;
	if(servoNowAngle[3]<servoDstAngle[3])	servoNowAngle[3] += 27;
	if(servoNowAngle[4]>servoDstAngle[4])	servoNowAngle[4] -= 27;
	if(servoNowAngle[4]<servoDstAngle[4])	servoNowAngle[4] += 27;
	if(servoNowAngle[5]>servoDstAngle[5])	servoNowAngle[5] -= 27;
	if(servoNowAngle[5]<servoDstAngle[5])	servoNowAngle[5] += 27;
	if(servoNowAngle[6]>servoDstAngle[6])	servoNowAngle[6] -= 27;
	if(servoNowAngle[6]<servoDstAngle[6])	servoNowAngle[6] += 27;
	if(servoNowAngle[7]>servoDstAngle[7])	servoNowAngle[7] -= 27;
	if(servoNowAngle[7]<servoDstAngle[7])	servoNowAngle[7] += 27;

    if( (abs(servoNowAngle[0] - servoDstAngle[0])<27)&&
		(abs(servoNowAngle[1] - servoDstAngle[1])<27)&&
		(abs(servoNowAngle[2] - servoDstAngle[2])<27)&&
		(abs(servoNowAngle[3] - servoDstAngle[3])<27)&&
		(abs(servoNowAngle[4] - servoDstAngle[4])<27)&&
		(abs(servoNowAngle[5] - servoDstAngle[5])<27)&&
		(abs(servoNowAngle[6] - servoDstAngle[6])<27)&&
		(abs(servoNowAngle[7] - servoDstAngle[7])<27))
	{
		servoNowAngle[0]=servoDstAngle[0];
		servoNowAngle[1]=servoDstAngle[1];
		servoNowAngle[2]=servoDstAngle[2];
		servoNowAngle[3]=servoDstAngle[3];
		servoNowAngle[4]=servoDstAngle[4];
		servoNowAngle[5]=servoDstAngle[5];
		servoNowAngle[6]=servoDstAngle[6];
		servoNowAngle[7]=servoDstAngle[7];
		MsTimer2::stop();//关闭定时器2
		done = true;
	}
	for(j=0;j<8;j++)
	{
		SetServo(j,servoNowAngle[j]);
	}
	low_width = PwmPro-high_widthsum;
}
/*********************************************************************************************
 *函数功能：将输入的角度映射为脉宽函数
 *输入参数：*joint -  指向8路舵机角度的数组指针
 *输出参数： runtime   -  转到目标角度所用时间
 *假设1：0.5ms是0度，对应脉宽为1000，2.5ms是180度，对应脉宽为5000，则（5000-1000）/（180-0）=20
 *假设2：0.544ms是0度，对应脉宽为1088，2.4ms是180度，对应脉宽为4800，则（4800-1088）/（180-0）=20.6
 *********************************************************************************************/
bool MultiServo::SetJointsAngle(uint16_t *joint)
{
	int i;
	for(i=0;i<7;i++)
	{
		if(joint[i]<1000) joint[i]=1000;
		if(joint[i]>5000) joint[i]=5000;
	}
	if((joint[0]!=0)&&(joint[0]!=servoDstAngle[0]))
	{
		servoDstAngle[0] = joint[0];
		servoDstAngle[1] = Parallel_HighWidSum-joint[0];
	}
	for(i=1;i<7;i++)
	{
		if((joint[i]!=0)&&(joint[i]!=servoDstAngle[i+1]))
			servoDstAngle[i+1] = joint[i];
	}
	return true;
}
/*********************************************************************************************
 *函数功能：更新多路舵机位置函数
 *输入参数：无
 *输出参数：无
 *********************************************************************************************/
void MultiServo::UpdateMotion(int time)
{
	done = false;
	MsTimer2::set(time,MultiServo::CommandSet);
	MsTimer2::start();//启动定时器2
	while(!(done&0x1));//等待转到位
}

