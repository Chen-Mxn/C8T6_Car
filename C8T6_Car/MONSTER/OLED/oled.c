#include "oled.h"
#include "oled_table.h"

//OLED���Դ�
//��Ÿ�ʽ����.
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
/*��������: GPIOģ��SPI�˿ڳ�ʼ��                                        */
/*************************************************************************/
void OLED_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);//ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //�˿�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);//�����趨������ʼ��GPIOA
	/*
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|
	RCC_APB2Periph_SPI1, ENABLE ); //��GPIO,SPI ʱ��ʹ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7); //�ٳ�ʼ�� GPIO
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;//�˿�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);//�����趨������ʼ��GPIOA
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //���� SPI ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //���� SPI ����ģʽ:����Ϊ�� SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // 8 λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS �ź���Ӳ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; //Ԥ��Ƶ 256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //���ݴ���� MSB λ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC ֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure); //�ڸ���ָ���Ĳ�����ʼ������ SPIx �Ĵ���
	SPI_Cmd(SPI1, ENABLE); //��ʹ�� SPI ����
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
/*��������: ͨ��SPIO���ģ��SPIͨ��Э��,��ģ��(SSD1306)д��һ���ֽ�         */
/*��ڲ�����															     */	
/*						data��Ҫд�������/����							 */				
/*						cmd ������/�����־ 0,��ʾ����;1,��ʾ����;         */
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
		if(data&0x80)OLED_MOSI=1; //�Ӹ�λ����λ
		else OLED_MOSI=0;
		OLED_CLK=1;
		data<<=1;
	}
	OLED_CLK=1;
	OLED_DC=1;
}
/*************************************************************************/
/*��������: д����                                                        */
/*************************************************************************/
void WriteCmd(unsigned char cmd)
{
	SPI_WriteByte(cmd,OLED_CMD);
}
/*************************************************************************/
/*��������: д����                                                        */
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
/*��������: ����ʱ                                                        */
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
/*��������: ��ʼ��OLEDģ��                                                */
/*************************************************************************/
void OLED_Init(void)
{
	OLED_SPI_Init();
	OLED_CLK = 1;
	OLED_RST = 0;
	OLED_DLY_ms(100);
	OLED_RST = 1;

	//���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���
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

	OLED_Clear();  //��ʼ����	
}
/*************************************************************************/
/*��������: ��OLED�������л���                                         	 */
/*************************************************************************/
void OLED_ON(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X14);  //������ɱ�
	WriteCmd(0XAF);  //OLED����
}
/*************************************************************************/
/*��������: ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA                      */
/*************************************************************************/
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X10);  //�رյ�ɱ�
	WriteCmd(0XAE);  //OLED����
}

/*************************************************************************/
/*��������: �����Դ浽OLED                                              	 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		WriteCmd(0xb0+i);   //����ҳ��ַ��0~7��
		WriteCmd(0x00);      //������ʾλ�á��е͵�ַ
		WriteCmd(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)WriteData(OLED_GRAM[n][i]); 
	}   
}
/*************************************************************************/
/*��������: ����                                                			 */
/*************************************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//������ʾ
}
/*************************************************************************/
/*��������: ����                                                          */
/*��ڲ����� 															 */
/*						x��������       0~127              			     */
/*						y��������	 	 		0~63                     */
/*						dot:0,���;1,���	  							 */				
/*************************************************************************/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
/*************************************************************************/
/*��������: ���                                                          */
/*��ڲ����� 															 */
/*						x1,y1,x2,y2 �������ĶԽ�����                  	 */
/*						ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 	 */
/*						dot:0,���;1,���	  						     */				
/*************************************************************************/
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//������ʾ
}

/*************************************************************************/
/*��������: ��ָ��λ����ʾһ���ַ�,���������ַ�                             */
/*��ڲ����� 															 */
/*						x:0~12                                           */
/*						y:0~63                                	 	 	 */
/*						mode:0,������ʾ;1,������ʾ	  					 */	
/*            size:ѡ������ 16/12                                     	 */
/*************************************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ		 
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[chr][t];	//����1608����
		else if(size==24)temp=asc2_2412[chr][t];	//����2412����
		else return;								//û�е��ֿ�
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
//m^n����
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
/*************************************************************************/
/*��������: ��ʾ2������                                               	 */
/*��ڲ����� 															 */
/*						x,y :�������                                   	 */
/*						len :���ֵ�λ��                              	 */
/*						size:�����С	  								 */	
/*            num:��ֵ(0~4294967295)                                  	 */
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
/*��������: ��ʾ�ַ���												     */
/*��ڲ����� 															 */
/*						x,y:�������                                    	 */
/*						size:�����С                                	 */
/*						*p:�ַ�����ʼ��ַ	  							 */	
/*************************************************************************/
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size)
{	
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>(128-(size/2))){x=0;y+=size;}
        if(y>(64-size)){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,size,1);	 
        x+=size/2;
        p++;
    }  
	
}	
/*************************************************************************/
/*�������ܣ���ʾһ���ֿ��еĺ���               							 */
/*��ڲ�����	                       										 */
/*    			x,y:�������												 */
/*     			num :�ֿ��еڼ�������									 */
/*     			size:�����С											 */
/*   			mode��ģʽ��0,������ʾ;1,������ʾ							 */
/* 																		 */
/*************************************************************************/
void OLED_ShowChinese(u8 x, u8 y,  u8 num, u8 size,u8 mode)
{
    u8 temp,t,t1;
    u8 y0=y;
    u8 csize=(size/8 + ((size%8)?1:0)) * size;     //�õ�����һ���ַ���Ӧ������ռ���ֽ���
              
    for(t=0;t<csize;t++)
    {  
		  //ֻ������16��12������   û��������������
        if(size==12)      temp = chinese_1212[num][t];    //����1212����
        else if(size==16) temp = chinese_1616[num][t];    //����1616����
        else return;                                //û�е��ֿ�
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




