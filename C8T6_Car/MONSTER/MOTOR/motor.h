#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"


void Motor_Init(void);

void MotorA_Forward(void);
void MotorA_Backward(void);
void MotorB_Forward(void);
void MotorB_Backward(void);

void Car_Forward(u16 speed);
void Car_Backward(u16 speed);
void Car_TurnLeft(u16 speed);
void Car_TurnRight(u16 speed);
void Car_Stop(void);


#endif


