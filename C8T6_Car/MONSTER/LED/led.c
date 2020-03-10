#include "led.h"
#include "stm32f10x.h"


void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);				// PB12
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);		//都输出低电平  LED亮
}
