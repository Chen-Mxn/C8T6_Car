#include "stm32f10x.h"
#include "sys.h"
#include "usart1.h"
#include "pwm.h"
#include "motor.h"
#include "led.h"
#include "hcsr04.h"
#include "oled.h"
#include "delay.h"


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif


extern u8 flag;		//����һ�������־λ
extern u8 MODE;	//�л�ģʽ������/���ϣ�
//������㺯��

int main(void)
{
	u16 spd;		//����Ƚ�ֵ==>�ٶȲ���
	float lenth0;
	//float lenth1;
	//float	lenth2;
	
	MY_USART_Init(9600);				//����1������9600
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�жϷ���2
	LED_GPIO_Init();			//��ʼ��LED
	delay_init();				//��ʼ����ʱ
	Motor_Init();
	TIM3_PWM_Init(899,0);		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
	TIM4_PWM_Init(899,0);		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
	HCSR_Init(999,72-1);  	//�� 1Mhz ��Ƶ�ʼ���  
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);		//������͵�ƽ  LED��
	OLED_SPI_Init();
	OLED_Init();
	OLED_ON();
	OLED_Clear();
	OLED_ShowString(24,16,":3119000880",12);
	OLED_ShowChinese(0,0,0,16,1);
	OLED_ShowChinese(16,0,1,16,1);
	OLED_ShowChinese(32,0,2,16,1);
	OLED_ShowChinese(48,0,3,16,1);
	OLED_ShowChinese(0,16,0,12,1);
	OLED_ShowChinese(12,16,1,12,1);
	OLED_ShowString(0,40,"Edit TIME: 2020/2/19",12);  
    OLED_ShowString(0,52,"Writer:",12);  
    OLED_ShowString(42,52,"Mr.Chen",12);  
	OLED_Refresh_Gram();
	while(1)
	{
		if(MODE==0XF) //��������ģʽ
		{
			switch(flag)
			{
				case 0:
					Car_Stop();break;
				case 1:		
					Car_Forward(spd);break;
				case 2:		
					Car_Backward(spd);break;
				case 3:		
					Car_TurnLeft(spd);break;
				case 4:		
					Car_TurnRight(spd);break;
				case 5:		
					spd = 600;break;
				case 6:		
					spd = 350;break;
				case 7:		
					spd = 450;break;
				case 8: 	
					spd = 800;break;
	//			case 9: 	
	//				break;			
				default:		
					Car_Stop();break;   
			} 
			
		}
		else	//����ģʽ
		{
			delay_ms(80);
			lenth0 = Senor_Using();	//������㺯����ȡ5��ƽ��ֵ
			delay_ms(80);
			if(lenth0 >30.00){       //���ǰ���������30cm  ǰ��
				Car_Forward(360);
			}	
			else{
				GPIO_SetBits(GPIOB,GPIO_Pin_12);	//LED��
				Car_TurnLeft(360);
			}
		}
		
	}
}



