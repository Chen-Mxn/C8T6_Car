#include "hcsr04.h"
#include "sys.h"
#include "delay.h"
//������ʱ�����ʱ�����Tout= ((arr+1)*(psc+1))/Tclk
// arr=0xffff,psc=71
//APB1ʱ��Ƶ��Ϊ36M������psc��0������TIM2�ļ���Ƶ����APB1ʱ��Ƶ�ʵ�2�� 72M 
//�������ʱ��Ϊ Tout= (65536*72)/72000000 = 0.065536s = 65.536ms
//�������ٶ�340m/s������ó� (340/2)*0.065536 = 11.14112m >> HCSR04�������4.5m
//�ʲ���Ҫ���Ƕ�ʱ������жϡ�

u16 overcount=0;
//arr:�Զ���װֵ psc:ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㣺Tout=((arr+1)*(psc+1))/Ft   us
//Ft = ��ʱ������Ƶ�ʣ���λMhz
//TIM2��APB1�ϣ�ΪHCLK/2 == 36Mhz

void HCSR_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//ʹ��TIM2,GPIOA,GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	
	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;		//��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;			// PA0. echo0
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	//�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3 ;		// PA3.trig0
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//TIM2��ʼ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		// ʱ�Ӳ���Ƶ��TDTS = Tck_tim 
	TIM_TimeBaseInitStructure.TIM_CounterMode= TIM_CounterMode_Up;  //TIM ���ϼ���ģʽ 
	TIM_TimeBaseInitStructure.TIM_Period= arr;		 	//�趨�������Զ���װֵ 
	TIM_TimeBaseInitStructure.TIM_Prescaler= psc;		//����Ԥ��Ƶֵ 
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig( TIM2, TIM_IT_Update,ENABLE);//�����ж� 
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,DISABLE );  //ʹ�ܶ�ʱ��2 
}

float Senor_Using(void)	//������㺯����ȡ5��ƽ��ֵ
{
	float length=0,sum=0;
	u16 tim;
	u8 i=0;
	/*��5�����ݼ���һ��ƽ��ֵ*/
	while(i!=5)
	{
		PAout(3)=1; //�����źţ���Ϊ�����ź�
		delay_us(20); //�ߵ�ƽ�źų���10us
		PAout(3)=0;
		/*�ȴ������ź�*/
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==RESET);
		TIM_Cmd(TIM2,ENABLE);//�����źŵ�����������ʱ������

		i+=1; //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET);//�����ź���ʧ
		TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��

		tim=TIM_GetCounter(TIM2);//��ȡ��TIM4���Ĵ����еļ���ֵ��һ�߼�������ź�ʱ��

		length=(tim+overcount*1000)/58.0;//ͨ�������źż������

		sum=length+sum;
		TIM2->CNT=0; //��TIM4�����Ĵ����ļ���ֵ����
		overcount=0; //�ж������������
		delay_ms(10);
	}
	length=sum/5;
	return length;//������Ϊ��������ֵ
}

//�жϷ�����
void TIM2_IRQHandler(void)
{            
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)	//�����ʱ�����
	 {
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־
	overcount++;
	 }	
}

