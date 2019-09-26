#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"

void MotorRight(int16_t speed);
void MotorLeft(int16_t speed);
void FanMotor_Init(void);
void FanMotor_Open(void);
void FanMotor_Close(void);

#endif

