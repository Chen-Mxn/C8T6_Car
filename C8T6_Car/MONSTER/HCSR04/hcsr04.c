#include "hcsr04.h"
#include "sys.h"
#include "delay.h"
//经过定时器溢出时间计算Tout= ((arr+1)*(psc+1))/Tclk
// arr=0xffff,psc=71
//APB1时钟频率为36M，由于psc≠0，所以TIM2的计数频率是APB1时钟频率的2倍 72M 
//计算溢出时间为 Tout= (65536*72)/72000000 = 0.065536s = 65.536ms
//超声波速度340m/s，计算得出 (340/2)*0.065536 = 11.14112m >> HCSR04的最大测距4.5m
//故不需要考虑定时器溢出中断。

u16 overcount=0;
//arr:自动重装值 psc:时钟预分频数
//定时器溢出时间计算：Tout=((arr+1)*(psc+1))/Ft   us
//Ft = 定时器工作频率，单位Mhz
//TIM2在APB1上，为HCLK/2 == 36Mhz

void HCSR_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能TIM2,GPIOA,GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	
	//GPIO初始化
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;		//下拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;			// PA0. echo0
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3 ;		// PA3.trig0
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//TIM2初始化
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		// 时钟不分频，TDTS = Tck_tim 
	TIM_TimeBaseInitStructure.TIM_CounterMode= TIM_CounterMode_Up;  //TIM 向上计数模式 
	TIM_TimeBaseInitStructure.TIM_Period= arr;		 	//设定计数器自动重装值 
	TIM_TimeBaseInitStructure.TIM_Prescaler= psc;		//设置预分频值 
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig( TIM2, TIM_IT_Update,ENABLE);//允许中断 
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,DISABLE );  //使能定时器2 
}

float Senor_Using(void)	//距离计算函数，取5次平均值
{
	float length=0,sum=0;
	u16 tim;
	u8 i=0;
	/*测5次数据计算一次平均值*/
	while(i!=5)
	{
		PAout(3)=1; //拉高信号，作为触发信号
		delay_us(20); //高电平信号超过10us
		PAout(3)=0;
		/*等待回响信号*/
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==RESET);
		TIM_Cmd(TIM2,ENABLE);//回响信号到来，开启定时器计数

		i+=1; //每收到一次回响信号+1，收到5次就计算均值
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET);//回响信号消失
		TIM_Cmd(TIM2,DISABLE);//关闭定时器

		tim=TIM_GetCounter(TIM2);//获取计TIM4数寄存器中的计数值，一边计算回响信号时间

		length=(tim+overcount*1000)/58.0;//通过回响信号计算距离

		sum=length+sum;
		TIM2->CNT=0; //将TIM4计数寄存器的计数值清零
		overcount=0; //中断溢出次数清零
		delay_ms(10);
	}
	length=sum/5;
	return length;//距离作为函数返回值
}

//中断服务函数
void TIM2_IRQHandler(void)
{            
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)	//如果定时器溢出
	 {
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志
	overcount++;
	 }	
}

