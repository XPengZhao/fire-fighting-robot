/*
 * OpenMultiServo.h
 *
 *  Created on: 2012-8-31
 *      Author: Administrator
 */

#include <Arduino.h>
#include <./MsTimer2.h>

#ifndef OPEN_MULTISERVO_H_
#define OPEN_MULTISERVO_H_

namespace MultiServo
{
	extern uint16_t counter2;//计数器2
	extern uint16_t servotime;//每隔servotime转一度
	extern uint16_t servoLastAngle[8];
	extern uint16_t servoDstAngle[8];//存储舵机目标位置
	extern volatile long low_width;//剩下低电平时间
	extern volatile uint16_t servoNowAngle[8];//存储舵机当前位置
	extern uint16_t Parallel_HighWidSum;//并联电机正脉宽之和
	extern volatile uint16_t servoId;//舵机编号
	extern volatile long high_widthsum;//多路舵机脉宽总和
	extern volatile bool done;//完成一次目标角度标志

	void InitOpenMultiChannelServo(void);
	bool SetJointsAngle(uint16_t *joint);
	void UpdateMotion(int time);
	void InitHc595port(void);
	void InitTimer1(void);
	void InitServo(void);
	void SetServo(uint8_t servonum,uint16_t Angle);
	void CommandSet(void);//命令执行函数
}
#endif /* OPEN_MULTISERVO_H_ */
