#include "oled.h"
#include "oled_table.h"

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 		   
u8 OLED_GRAM[128][8];	


/*************************************************************************/
/*函数功能: GPIO模拟SPI端口初始化                                        */
/*************************************************************************/
void OLED_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);//使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //端口配置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO口速度为50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);//根据设定参数初始化GPIOA
	/*
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|
	RCC_APB2Periph_SPI1, ENABLE ); //①GPIO,SPI 时钟使能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7); //①初始化 GPIO
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;//端口配置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO口速度为50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);//根据设定参数初始化GPIOA
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //设置 SPI 全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //设置 SPI 工作模式:设置为主 SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // 8 位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS 信号由硬件管理
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; //预分频 256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从 MSB 位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC 值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure); //②根据指定的参数初始化外设 SPIx 寄存器
	SPI_Cmd(SPI1, ENABLE); //③使能 SPI 外设
	*/
}
/*
void OLED_WB(uint8_t data)
{
    //Loop while DR register in not emplty 
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    // Send byte through the SPI2 peripheral 
    SPI_I2S_SendData(SPI1, data);
}
*/
/*************************************************************************/
/*函数功能: 通过SPIO软件模拟SPI通信协议,向模块(SSD1306)写入一个字节         */
/*入口参数：															     */	
/*						data：要写入的数据/命令							 */				
/*						cmd ：数据/命令标志 0,表示命令;1,表示数据;         */
/*************************************************************************/
void SPI_WriteByte(unsigned char data,unsigned char cmd)
{
	unsigned char i=0;
	OLED_DC =cmd;
	//OLED_WB(data);
	OLED_CLK=0;
	for(i=0;i<8;i++)
	{
		OLED_CLK=0;
		if(data&0x80)OLED_MOSI=1; //从高位到低位
		else OLED_MOSI=0;
		OLED_CLK=1;
		data<<=1;
	}
	OLED_CLK=1;
	OLED_DC=1;
}
/*************************************************************************/
/*函数功能: 写命令                                                        */
/*************************************************************************/
void WriteCmd(unsigned char cmd)
{
	SPI_WriteByte(cmd,OLED_CMD);
}
/*************************************************************************/
/*函数功能: 写数据                                                        */
/*************************************************************************/
void WriteData(unsigned char data)
{
	SPI_WriteByte(data,OLED_DATA);
}


/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/




/*************************************************************************/
/*函数功能: 软延时                                                        */
/*************************************************************************/
void OLED_DLY_ms(unsigned int ms)
{                         
  unsigned int a;
  while(ms)
  {
    a=1335;
    while(a--);
    ms--;
  }
}
/*************************************************************************/
/*函数功能: 初始化OLED模块                                                */
/*************************************************************************/
void OLED_Init(void)
{
	OLED_SPI_Init();
	OLED_CLK = 1;
	OLED_RST = 0;
	OLED_DLY_ms(100);
	OLED_RST = 1;

	//从上电到下面开始初始化要有足够的时间，即等待RC复位完毕
	WriteCmd(0xAE);	 		// Display Off (0x00)
	WriteCmd(0xD5);
	WriteCmd(0x80);		    // Set Clock as 100 Frames/Sec
	WriteCmd(0xA8);
	WriteCmd(0x3F);	        // 1/64 Duty (0x0F~0x3F)
	WriteCmd(0xD3);
	WriteCmd(0x00);		    // Shift Mapping RAM Counter (0x00~0x3F)
	WriteCmd(0x40 | 0x00);  // Set Mapping RAM Display Start Line (0x00~0x3F)
	WriteCmd(0x8D);
	WriteCmd(0x10 | 0x04);	// Enable Embedded DC/DC Converter (0x00/0x04)
	WriteCmd(0x20);
	WriteCmd(0x02);		    // Set Page Addressing Mode (0x00/0x01/0x02)
	WriteCmd(0xA0 | 0x01);  // Set SEG/Column Mapping    
	WriteCmd(0xC0);  // Set COM/x Scan Direction   
	WriteCmd(0xDA);
	WriteCmd(0x02 | 0x10);  // Set Sequential Configuration (0x00/0x10)
	WriteCmd(0x81);
	WriteCmd(0xCF);	        // Set SEG Output Current
	WriteCmd(0xD9);
	WriteCmd(0xF1);         // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	WriteCmd(0xDB);
	WriteCmd(0x40);	        // Set VCOM Deselect Level
	WriteCmd(0xA4 | 0x00);	// Disable Entire Display On (0x00/0x01)
	WriteCmd(0xA6 | 0x00);	// Disable Inverse Display On (0x00/0x01)
	WriteCmd(0xAE | 0x01);  // Display On (0x01)

	OLED_Clear();  //初始清屏	
}
/*************************************************************************/
/*函数功能: 将OLED从休眠中唤醒                                         	 */
/*************************************************************************/
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}
/*************************************************************************/
/*函数功能: 将OLED休眠 -- 休眠模式下,OLED功耗不到10uA                      */
/*************************************************************************/
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

/*************************************************************************/
/*函数功能: 更新显存到OLED                                              	 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		WriteCmd(0xb0+i);   //设置页地址（0~7）
		WriteCmd(0x00);      //设置显示位置—列低地址
		WriteCmd(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)WriteData(OLED_GRAM[n][i]); 
	}   
}
/*************************************************************************/
/*函数功能: 清屏                                                			 */
/*************************************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显示
}
/*************************************************************************/
/*函数功能: 画点                                                          */
/*入口参数： 															 */
/*						x：横坐标       0~127              			     */
/*						y：纵坐标	 	 		0~63                     */
/*						dot:0,清空;1,填充	  							 */				
/*************************************************************************/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
/*************************************************************************/
/*函数功能: 填充                                                          */
/*入口参数： 															 */
/*						x1,y1,x2,y2 填充区域的对角坐标                  	 */
/*						确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 	 */
/*						dot:0,清空;1,填充	  						     */				
/*************************************************************************/
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//更新显示
}

/*************************************************************************/
/*函数功能: 在指定位置显示一个字符,包括部分字符                             */
/*入口参数： 															 */
/*						x:0~12                                           */
/*						y:0~63                                	 	 	 */
/*						mode:0,反白显示;1,正常显示	  					 */	
/*            size:选择字体 16/12                                     	 */
/*************************************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
	chr=chr-' ';//得到偏移后的值		 
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[chr][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[chr][t];	//调用2412字体
		else return;								//没有的字库
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}
//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
/*************************************************************************/
/*函数功能: 显示2个数字                                               	 */
/*入口参数： 															 */
/*						x,y :起点坐标                                   	 */
/*						len :数字的位数                              	 */
/*						size:字体大小	  								 */	
/*            num:数值(0~4294967295)                                  	 */
/*************************************************************************/		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 
/*************************************************************************/
/*函数功能: 显示字符串												     */
/*入口参数： 															 */
/*						x,y:起点坐标                                    	 */
/*						size:字体大小                                	 */
/*						*p:字符串起始地址	  							 */	
/*************************************************************************/
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size)
{	
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>(128-(size/2))){x=0;y+=size;}
        if(y>(64-size)){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,size,1);	 
        x+=size/2;
        p++;
    }  
	
}	
/*************************************************************************/
/*函数功能：显示一个字库中的汉字               							 */
/*入口参数：	                       										 */
/*    			x,y:起点坐标												 */
/*     			num :字库中第几个汉字									 */
/*     			size:字体大小											 */
/*   			mode：模式。0,反白显示;1,正常显示							 */
/* 																		 */
/*************************************************************************/
void OLED_ShowChinese(u8 x, u8 y,  u8 num, u8 size,u8 mode)
{
    u8 temp,t,t1;
    u8 y0=y;
    u8 csize=(size/8 + ((size%8)?1:0)) * size;     //得到字体一个字符对应点阵集所占的字节数
              
    for(t=0;t<csize;t++)
    {  
		  //只定义了16，12号字体   没有声明其他字体
        if(size==12)      temp = chinese_1212[num][t];    //调用1212字体
        else if(size==16) temp = chinese_1616[num][t];    //调用1616字体
        else return;                                //没有的字库
		for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)OLED_DrawPoint(x,y,mode);
            else OLED_DrawPoint(x,y,!mode);
            temp<<=1;
            y++;
            if((y-y0)==size)
            {
                y=y0;
                x++;
                break;
            }
        }    
    } 	
}




