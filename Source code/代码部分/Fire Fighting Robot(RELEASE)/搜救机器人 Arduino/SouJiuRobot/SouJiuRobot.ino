/*
 * main.cpp
 *
 *  Created on: 2017-05-17
 *  Author: wucp@szopen.cn
 *  QQ:     992601104
 * 思路：有串口数据来  》读取全部数据  》解析数据 》反馈信息
 * */
#include <OpenMultiServo.h>
#include <MsTimer2.h>

#define servoleft  6
#define servoright 7

#define Uint 27
uint16_t Init_servoangle[7]={2897,2782,3205,3000,3000,3000,3000};//存放用户设置的舵机角度，servoangle[0]存放并联舵机角度，单位增量为27
uint16_t servoangle[7]={3000,3000,3000,3000,3000,3000,3000};//存放用户设置的舵机角度，servoangle[0]存放并联舵机角度

char RevByte=0;
String RevStr;
bool RevStart = false;
char charnums;

String action;
String type;
String style;
String value;
uint16_t intvalue;
uint16_t i=0;
uint16_t runid=0;

unsigned int initSVO2pulse=2784;//SVO2 pulses

/*
 * 初始化函数
 */
void setup(void){
	Serial.begin(9600);
	InitContinMotorPin(servoleft);
	InitContinMotorPin(servoright);
        MultiServo::servoLastAngle[0]=initSVO2pulse;
        MultiServo::servoDstAngle[0]=initSVO2pulse;
        MultiServo::servoNowAngle[0]=initSVO2pulse;
	MultiServo::InitOpenMultiChannelServo();
	InitialHand();
	delay(2000);
	HandInitStates();
}
/*
 * main函数
 */
void loop(void)
{
	ReceviceSerialData();
	MoveProcess();
}

/*
 * 调速，前进
 */
void GoForward(uint16_t speeds){
	PulseOut(servoleft,1500+speeds*5);
	PulseOut(servoright,1500-speeds*5);
	delay(10);
}
/*
 * 调速，后退
 */
void GoBack(uint16_t speeds){
	PulseOut(servoleft,1500-speeds*5);
	PulseOut(servoright,1500+speeds*5);
	delay(10);
}
/*
 * 调速，左转
 */
void SpinLeft(uint16_t speeds){
	PulseOut(servoleft,1500-speeds*5);
	PulseOut(servoright,1500-speeds*5);
	delay(10);
}
/*
 * 调速，右转
 */
void SpinRight(uint16_t speeds){
	PulseOut(servoleft,1500+speeds*5);
	PulseOut(servoright,1500+speeds*5);
	delay(10);
}
/*
 * 停止
 */
void Stop(uint16_t speedsorstep)
{
	PulseOut(servoleft,1500);
	PulseOut(servoright,1500);
	delay(20);
}
/*
 * 定步，前进
 */
void Forward(uint16_t steps){
	for(i=0;i<steps;i++)
	{
		PulseOut(servoleft,1520);
		PulseOut(servoright,1480);
		delay(10);
	}
}
/*
 * 定步，后退
 */
void Back(uint16_t steps){
	for(i=0;i<steps;i++)
	{
		PulseOut(servoleft,1485);
		PulseOut(servoright,1515);
		delay(10);
	}
}
/*
 * 定步，左转
 */
void Left(uint16_t steps){
	for(i=0;i<steps;i++)
	{
		PulseOut(servoleft,1480);
		PulseOut(servoright,1480);
		delay(10);
	}
}
/*
 * 定步，右转
 */
void Right(uint16_t steps){
	for(i=0;i<steps;i++)
	{
		PulseOut(servoleft,1520);
		PulseOut(servoright,1520);
		delay(10);
	}
}
/*
 * 机械手与底座成90度
 */
void InitialHand(void)
{
	MultiServo::SetJointsAngle(Init_servoangle);
	MultiServo::UpdateMotion(20);
}
/*
 * 机械手初始状态 1682(-45)  4723(+70)  1990(-45)  1920(-40)
 */
void HandInitStates(void)
{
	servoangle[3]=Init_servoangle[3]-Uint*40;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[0]=Init_servoangle[0]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[1]=Init_servoangle[1]+Uint*70;
	servoangle[2]=Init_servoangle[2]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);//1
	MultiServo::UpdateMotion(20);
}
/*
 * 机械手准备抓起动作  1243 1459 1405 3000
 */
void HandINTEND(void)//准备抓起
{
	servoangle[1]=Init_servoangle[1]+Uint*0;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[1]=Init_servoangle[1]-Uint*67-24;
	servoangle[2]=Init_servoangle[2]-Uint*49;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[0]=Init_servoangle[0]-Uint*48;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
}
/*
 * 机械手抓起对象
 */
void HandTAKEUP(void)//抓起对象
{
	servoangle[0]=Init_servoangle[0]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[1]=Init_servoangle[1]+Uint*70;
	servoangle[2]=Init_servoangle[2]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);//1
	MultiServo::UpdateMotion(20);
}
/*
 * 机械手放下对象
 */
void HandDOWNIT(void)//放下对象
{
	servoangle[1]=Init_servoangle[1]+Uint*0;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[1]=Init_servoangle[1]-Uint*55;
	servoangle[2]=Init_servoangle[2]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[0]=Init_servoangle[0]-Uint*67;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[3]=Init_servoangle[3]-Uint*40;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[0]=Init_servoangle[0]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);
	MultiServo::UpdateMotion(20);
	servoangle[1]=Init_servoangle[1]+Uint*70;
	servoangle[2]=Init_servoangle[2]-Uint*45;
	MultiServo::SetJointsAngle(servoangle);//1
	MultiServo::UpdateMotion(20);
}
/*
 * String转int
 */
uint16_t stringToint(String str)
{
	char strlen=0;
	unsigned int i=0;
	char buf[10];
	uint16_t val=0;
	strlen = str.length();
	for(i=0;i<strlen;i++)
	{
		buf[i] = str.charAt(i);
	}
	val = atoi(buf);
	return val;
}
/*
 * 解析接收的数据帧
 */
void AnalyseData(String ValidData)//// Analysis serial port input data
{   //机械手点动和联动帧数据格式
	//点动 $ HAND 1 12 2769 @
	//联动 $ HAND 0 RESETS @
	//移动速度和定步帧数据格式
	//设置速度 $ MOVE 1 QIAN 1 @
	//设置定步 $ MOVE 0 BACK 20 @
	//握手帧数据格式
	//握手 $ LINK OPEN @

	action = ValidData.substring(0,4);
	type = ValidData.substring(4,5);
	if(!action.compareTo("HAND"))
	{
		if(!type.compareTo("1"))
		{
			style = ValidData.substring(5,7);
			value = ValidData.substring(7,10)+ValidData.substring(10);
			intvalue=stringToint(value);
			if(!style.compareTo("12"))
			{
				servoangle[0]=intvalue;
			}
			else if(!style.compareTo("03"))
			{
				servoangle[1]=intvalue;
			}
			else if(!style.compareTo("04"))
			{
				servoangle[2]=intvalue;
			}
			else if(!style.compareTo("05"))
			{
				servoangle[3]=intvalue;
			}
			else if(!style.compareTo("06"))
			{
				servoangle[4]=intvalue;
			}
			else if(!style.compareTo("07"))
			{
				servoangle[5]=intvalue;
			}
			else if(!style.compareTo("08"))
			{
				servoangle[6]=intvalue;
			}
			MultiServo::SetJointsAngle(servoangle);
			MultiServo::UpdateMotion(20);
		}
		else if(!type.compareTo("0"))
		{
			style = ValidData.substring(5,10)+ValidData.substring(10);
			if(!style.compareTo("RESETS"))
			{
				HandInitStates();
			}
			else if(!style.compareTo("INTEND"))
			{
				HandINTEND();
			}
			else if(!style.compareTo("TAKEUP"))
			{
				HandTAKEUP();
			}
			else if(!style.compareTo("DOWNIT"))
			{
				HandDOWNIT();
			}
		}
		runid=0;
	}
	else if(!action.compareTo("MOVE"))
	{
		style = ValidData.substring(5,9);
		value = ValidData.substring(9,charnums)+ValidData.substring(charnums);
		intvalue=stringToint(value);
		if(!type.compareTo("1"))
		{
			if(!style.compareTo("QIAN"))
			{
				runid=1;
			}
			else if(!style.compareTo("BACK"))
			{
				runid=2;
			}
			else if(!style.compareTo("LEFT"))
			{
				runid=3;
			}
			else if(!style.compareTo("RIGH"))
			{
				runid=4;
			}
			else if(!style.compareTo("STOP"))
			{
				runid=0;
			}
		}
		else if(!type.compareTo("0"))
		{
			if(!style.compareTo("QIAN"))
			{
				Forward(intvalue);
			}
			else if(!style.compareTo("BACK"))
			{
				Back(intvalue);
			}
			else if(!style.compareTo("LEFT"))
			{
				Left(intvalue);
			}
			else if(!style.compareTo("RIGH"))
			{
				Right(intvalue);
			}
			else if(!style.compareTo("STOP"))
			{
				//Stop(intvalue);
			}
			runid=0;
		}

	}
	else if(!action.compareTo("LINK"))
	{
		style = ValidData.substring(4,7)+ValidData.substring(7);
		if(!style.compareTo("OPEN"))
		{
			Serial.print("$atmega328p*");
		}
		runid=0;
	}
}
/*
 * 接收串口数据
 */
void ReceviceSerialData(void)
{
	RevByte =  0;//清空接收缓存变量
	if(Serial.available()>0)//有串口数据来
	{
		RevByte = Serial.read();//读取串口数据
		if(RevByte > 0)//是有效数据
		{
			if((RevByte == '$')&&(!RevStart))//读到协议里的起始字符
			{
				RevStart = true;
				RevStr = "";
				charnums=0;
			}
			else if(RevStart)
			{
				if((RevByte >= 48) && (RevByte <= 122)&&(RevByte!='@'))
				{
					charnums++;
					RevStr = RevStr + (char)(RevByte);
				}
				else if(RevByte == '@')//读到结束字符
				{
					RevStart = false;
					AnalyseData(RevStr);//从字符串中提取信息
				}
			}
		}
	}
}
/*
 * 调速，移动函数
 */
void MoveProcess(void)
{
	switch(runid)
	{
	case 1:GoForward(intvalue);
		break;
	case 2:GoBack(intvalue);
		break;
	case 3:SpinLeft(intvalue);
		break;
	case 4:SpinRight(intvalue);
		break;
	default:
		break;
	}
}

void InitContinMotorPin(uint8_t pin)
{
  pinMode(pin,OUTPUT);
}
void PulseOut(uint8_t pin,int speeds)
{
	digitalWrite(pin,HIGH);
	delayMicroseconds(speeds);
	digitalWrite(pin,LOW);
}


