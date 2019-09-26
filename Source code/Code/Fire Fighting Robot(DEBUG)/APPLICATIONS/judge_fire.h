#ifndef JUDGE_FIRE_H
#define JUDGE_FIRE_H
#include "main.h"

#define NO_FIRE       0
#define FIRE_ON_LEFT  1
#define FIRE_ON_RIGHT 2

extern u8 __judge_result;

void judge_fire(void);

#endif
