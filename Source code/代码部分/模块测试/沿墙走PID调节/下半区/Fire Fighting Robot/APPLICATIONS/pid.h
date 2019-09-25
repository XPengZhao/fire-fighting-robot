#ifndef PID_H
#define PID_H
#include "main.h"


typedef struct{
  int16_t Target,Error_r,Error_l,MaxError;
}PIDParams;

typedef struct{
  int8_t ne_min;
  int8_t ne_two;
  int8_t ne_one;
  int8_t zero;
  int8_t one;
  int8_t two;
  int8_t max;
}FuzzyParam;

typedef struct{
  int8_t ne_min;
  int8_t ne_two;
  int8_t ne_one;
  int8_t zero;
  int8_t one;
  int8_t two;
  int8_t max;
}FuzzyD;


void Pos_ControlRight(void);
void Pos_ControlLeft(void);
void FlushPIDparam(void);
void GoStraight(void);
#endif
