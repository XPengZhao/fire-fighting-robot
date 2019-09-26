#ifndef ACTION_H
#define ACTION_H

#include "main.h"

#define TURNLEFT 1
#define TURNRIGHT 2

extern u8 __turn_direction;

void Turn(void);

void turn_left45(void);           //use delay_ms()
void turn_left45_return(void);
void turn_right45(void);
void turn_right45_return(void);
void turn_right_withdelay(void);  //use delay_ms()
void turn_left_withdelay(void);

#endif
