#include "usart1.h"
#include "led.h"
#include "sys.h"
#include <stdio.h>

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void MY_USART_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOA, USART1
	
	USART_DeInit(USART1); 		//USART1��λ
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		//���츴�����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);				// PA9. USART1_TX 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);				// PA10. USART1_RX 
	
	USART_InitStructure.USART_BaudRate=bound;							//���ò�����
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;		//�շ�ģʽ
	USART_InitStructure.USART_Parity=USART_Parity_No;					//����ż����λ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;			//�ֳ� 8
	USART_InitStructure.USART_StopBits=USART_StopBits_1;				//ֹͣλ 1
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;		//��Ӳ��������
	USART_Init(USART1,&USART_InitStructure);			//��ʼ��USART1
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);						//�ж����ȼ�����
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		//���������ж�
			
	USART_Cmd(USART1,ENABLE);		//ʹ�ܴ���1

}

u8 i;
u8 flag;		//����һ�������־λ
u8 MODE = 0xF;	//�л�ģʽ������/���ϣ�
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//��� USART1 ���жϱ�־λ
		
		GPIO_SetBits(GPIOB,GPIO_Pin_10);						//����LED����Ϊ�жϷ�����ָʾ��
		
		i = USART_ReceiveData(USART1);                    //���� USART1 ������յ�������
		
		//if�������ݲ��ֿ��Ա�֤�������յ���flag��������ȷ�ģ�������ӵĻ��ᵼ�½��ղ�����ȷ������
	    if(i=='0') flag=0; 	//ֹͣ
		if(i=='1') flag=1;	//ǰ��
		if(i=='2') flag=2;	//����
		if(i=='3') flag=3;	//��ת
		if(i=='4') flag=4;	//��ת
		if(i=='5') flag=5;	//�ٶ�600,ռ�ձ�600/900
		if(i=='6') flag=6;	//�ٶ�350��ռ�ձ�350/900
		if(i=='7') flag=7;	//�ٶ�450��ռ�ձ�450/900=50%
		if(i=='8') flag=8;	//�ٶ�800��ռ�ձ�800/900
		if(i=='9') MODE=~MODE;	//����һ��ģʽת������
//		if(i==0x00) MODE=!MODE;	//����һ��ģʽת������
	}
}


#endif

