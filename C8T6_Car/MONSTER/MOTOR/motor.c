#include "motor.h"
#include "stm32f10x.h"


void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);				// PB0. PB1. PB3. PB4
	//让四个IO都先输出低电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_10 | GPIO_Pin_11);

}

//电机A——正转、反转、停转函数
void MotorA_Forward(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_1); 	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);		
}

void MotorA_Backward(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
	GPIO_SetBits(GPIOB,GPIO_Pin_1);	
}

void MotorA_Stop(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0); 	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1); 	
}

//电机B——正转、反转、停转函数
void MotorB_Forward(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_11); 
	GPIO_SetBits(GPIOB,GPIO_Pin_10);	
}


void MotorB_Backward(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_10); 
	GPIO_SetBits(GPIOB,GPIO_Pin_11);	
}

void MotorB_Stop(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_10); 
	GPIO_ResetBits(GPIOB,GPIO_Pin_11); 
}



//小车运动状态函数
void Car_Forward(u16 speed)
{
	MotorA_Forward();
	MotorB_Forward();
	TIM_SetCompare1(TIM3,speed);
	TIM_SetCompare1(TIM4,speed);

}

void Car_Backward(u16 speed)
{
	MotorA_Backward();
	MotorB_Backward();
	TIM_SetCompare1(TIM3,speed);
	TIM_SetCompare1(TIM4,speed);
	
}

void Car_TurnLeft(u16 speed)
{
	MotorB_Backward();
	MotorA_Forward();
	TIM_SetCompare1(TIM3,speed);
	TIM_SetCompare1(TIM4,speed);
}

void Car_TurnRight(u16 speed)
{
	MotorB_Forward();
	MotorA_Backward();
	TIM_SetCompare1(TIM3,speed);
	TIM_SetCompare1(TIM4,speed);
}

void Car_Stop(void)
{
	MotorA_Stop();
	MotorB_Stop();
	//TIM_SetCompare1(TIM3,speed);
	//TIM_SetCompare1(TIM4,speed);
}

