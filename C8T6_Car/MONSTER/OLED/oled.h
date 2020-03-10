#ifndef __OLED_H
#define __OLED_H
#include "sys.h"

#define OLED_CMD 0   //命令声明
#define OLED_DATA 1 //数据声明

#define OLED_CLK 	PBout(12)	// CLK时钟 	 D0/SCK
#define OLED_MOSI 	PBout(13)	// MOSI		 D1/SDA
#define OLED_RST 	PBout(14)	// RET复位	 RES
#define OLED_DC  	PBout(15)	// 命令|数据	 DC	（0表传输命令1表传输数据）

u8 SPI1_ReadWriteByte(u8 TxData);

void OLED_SPI_Init(void); //配置MCU的SPI
void SPI_WriteByte(unsigned char addr,unsigned char data); //向寄存器地址写一个byte的数据
void WriteCmd(unsigned char cmd); //写命令
void WriteData(unsigned char data); //写数据




void OLED_Init(void);//初始化OLED
void OLED_ON(void);//唤醒OLED
void OLED_OFF(void);//OLED休眠
void OLED_Refresh_Gram(void);//更新显存到OLED
void OLED_Clear(void);//清屏
void OLED_DrawPoint(u8 x,u8 y,u8 t);//画点
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//填充
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//显示字符
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//显示2个数字
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//显示字符串
void OLED_ShowChinese(u8 x, u8 y,  u8 num, u8 size,u8 mode);//显示中文汉字
#endif









