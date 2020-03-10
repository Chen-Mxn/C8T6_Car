#include "usart1.h"
#include "led.h"
#include "sys.h"
#include <stdio.h>

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void MY_USART_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA, USART1
	
	USART_DeInit(USART1); 		//USART1复位
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		//推挽复用输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);				// PA9. USART1_TX 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);				// PA10. USART1_RX 
	
	USART_InitStructure.USART_BaudRate=bound;							//设置波特率
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;		//收发模式
	USART_InitStructure.USART_Parity=USART_Parity_No;					//无奇偶检验位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;			//字长 8
	USART_InitStructure.USART_StopBits=USART_StopBits_1;				//停止位 1
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;		//无硬件流控制
	USART_Init(USART1,&USART_InitStructure);			//初始化USART1
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);						//中断优先级分组
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		//开启接收中断
			
	USART_Cmd(USART1,ENABLE);		//使能串口1

}

u8 i;
u8 flag;		//定义一个命令标志位
u8 MODE = 0xF;	//切换模式（蓝牙/避障）
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除 USART1 的中断标志位
		
		GPIO_SetBits(GPIOB,GPIO_Pin_10);						//设置LED亮作为中断发生的指示灯
		
		i = USART_ReceiveData(USART1);                    //返回 USART1 最近接收到的数据
		
		//if语句的内容部分可以保证蓝牙接收到的flag数据是正确的，如果不加的话会导致接收不到正确的数据
	    if(i=='0') flag=0; 	//停止
		if(i=='1') flag=1;	//前进
		if(i=='2') flag=2;	//后退
		if(i=='3') flag=3;	//左转
		if(i=='4') flag=4;	//右转
		if(i=='5') flag=5;	//速度600,占空比600/900
		if(i=='6') flag=6;	//速度350，占空比350/900
		if(i=='7') flag=7;	//速度450，占空比450/900=50%
		if(i=='8') flag=8;	//速度800，占空比800/900
		if(i=='9') MODE=~MODE;	//定义一个模式转化按键
//		if(i==0x00) MODE=!MODE;	//定义一个模式转化按键
	}
}


#endif

