#ifndef __OLED_H
#define __OLED_H
#include "sys.h"

#define OLED_CMD 0   //��������
#define OLED_DATA 1 //��������

#define OLED_CLK 	PBout(12)	// CLKʱ�� 	 D0/SCK
#define OLED_MOSI 	PBout(13)	// MOSI		 D1/SDA
#define OLED_RST 	PBout(14)	// RET��λ	 RES
#define OLED_DC  	PBout(15)	// ����|����	 DC	��0��������1�������ݣ�

u8 SPI1_ReadWriteByte(u8 TxData);

void OLED_SPI_Init(void); //����MCU��SPI
void SPI_WriteByte(unsigned char addr,unsigned char data); //��Ĵ�����ַдһ��byte������
void WriteCmd(unsigned char cmd); //д����
void WriteData(unsigned char data); //д����




void OLED_Init(void);//��ʼ��OLED
void OLED_ON(void);//����OLED
void OLED_OFF(void);//OLED����
void OLED_Refresh_Gram(void);//�����Դ浽OLED
void OLED_Clear(void);//����
void OLED_DrawPoint(u8 x,u8 y,u8 t);//����
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//���
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//��ʾ�ַ�
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//��ʾ2������
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//��ʾ�ַ���
void OLED_ShowChinese(u8 x, u8 y,  u8 num, u8 size,u8 mode);//��ʾ���ĺ���
#endif









