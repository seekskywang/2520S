#ifndef _lcm_H
#define _lcm_H
#define Bank1_LCD_C        ((u32)0x6C000002)
#define Bank1_LCD_D        ((u32)0x6C000000)

#define LCD_REG            *(__IO uint8_t *)(Bank1_LCD_D)
#define LCD_RAM            *(__IO uint8_t *)(Bank1_LCD_C)

//==========================================================
//LCD��������
#define LCD_CMD_CURSOR_POS	(u8)(0x21)	//���λ�üĴ���(AddrX(0-4F),AddrY(0-0F))
#define LCD_CMD_OFFSET		(u8)(0x22)	//External CGRAMƫ�ƼĴ���(AddrL,AddrH)
										//D4-D0:A15-A11
										//00000-Extern CGRAM Addr (0000-07FFH)
										//00001-Extern CGRAM Addr (0800-0FFFH)
										//00010-Extern CGRAM Addr (1000-17FFH)
										//11100-Extern CGRAM Addr (E000-E7FFH)
										//11101-Extern CGRAM Addr (E800-EFFFH)
										//11110-Extern CGRAM Addr (F000-F7FFH)
										//11111-Extern CGRAM Addr (F800-FFFFH)
#define LCD_CMD_ADDR		(u8)(0x24)	//��д��ַ�Ĵ���(AddrL,AddrH)

#define LCD_CMD_TXT_ADDR	(u8)(0x40)	//�ı��׵�ַ(AddrL,AddrH)
#define LCD_CMD_TXT_WIDTH	(u8)(0x41)	//�ı�����(Columns,0)
#define LCD_CMD_GRH_ADDR	(u8)(0x42)	//ͼ���׵�ַ(AddrL,AddrH)
#define LCD_CMD_GRH_WIDTH	(u8)(0x43)	//ͼ�ο���(Columns,0)

#define LCD_CMD_MODE_INTERNAL_CGROM	(u8)(0x80)	//�ڲ�CGROM��D2-D0:ģʽ����
#define LCD_CMD_MODE_EXTERNAL_CGRAM	(u8)(0x88)	//�ⲿCGRAM��D2-D0:ģʽ����
#define LCD_CMD_MODE_OR		(u8)(0x00)	//��ģʽ
#define LCD_CMD_MODE_XOR	(u8)(0x02)	//���ģʽ
#define LCD_CMD_MODE_AND	(u8)(0x03)	//��ģʽ
#define LCD_CMD_MODE_TXT	(u8)(0x04)	//�ı�����

#define LCD_CMD_DISP_OFF	(u8)(0x90)	//��ʾ�أ�D3-D0:��ʾ����
#define LCD_CMD_DISP_BLINK	(u8)(SetD0)	//D0=1/0:1=�����˸��
#define LCD_CMD_DISP_CURSOR	(u8)(SetD1)	//D1=1/0:1=�����ʾ��
#define LCD_CMD_DISP_TXT	(u8)(SetD2)	//D2=1/0:1=�ı���ʾ��
#define LCD_CMD_DISP_GRH	(u8)(SetD3)	//D3=1/0:1=ͼ����ʾ��

#define LCD_CMD_CURSOR_1LINE (u8)(0xA0)	//1�й��
#define LCD_CMD_CURSOR_2LINE (u8)(0xA1)	//2�й��
#define LCD_CMD_CURSOR_3LINE (u8)(0xA2)	//3�й��
#define LCD_CMD_CURSOR_4LINE (u8)(0xA3)	//4�й��
#define LCD_CMD_CURSOR_5LINE (u8)(0xA4)	//5�й��
#define LCD_CMD_CURSOR_6LINE (u8)(0xA5)	//6�й��
#define LCD_CMD_CURSOR_7LINE (u8)(0xA6)	//7�й��

#define LCD_CMD_AUTO_WRITE	(u8)(0xB0)	//�����Զ�д
#define LCD_CMD_AUTO_READ	(u8)(0xB1)	//�����Զ���
#define LCD_CMD_AUTO_RESET	(u8)(0xB2)	//�Զ���д��λ

#define LCD_CMD_WR_INC_ADDR	(u8)(0xC0)	//дһ���ݣ�ADP��ַ��һ
#define LCD_CMD_RD_INC_ADDR	(u8)(0xC1)	//��һ���ݣ�ADP��ַ��һ
#define LCD_CMD_WR_DCC_ADDR	(u8)(0xC2)	//дһ���ݣ�ADP��ַ��һ
#define LCD_CMD_RD_DEC_ADDR	(u8)(0xC3)	//��һ���ݣ�ADP��ַ��һ
#define LCD_CMD_WR_NOC_ADDR	(u8)(0xC4)	//дһ���ݣ�ADP��ַ����
#define LCD_CMD_RD_NOC_ADDR	(u8)(0xC5)	//��һ���ݣ�ADP��ַ����

#define LCD_CMD_SCREEN_PEEK	(u8)(0xE0)	//�ӵ�ǰ��ַ��ȡһ�ֽ�����
#define LCD_CMD_SCREEN_COPY	(u8)(0xE8)	//��������

#define LCD_CMD_BIT			(u8)(0xF0)	//�Ե�ǰ��ַ�����ݽ���λ����
#define LCD_CMD_BIT_RESET	(u8)(ClrD3)	//D3=0��Bit Reset
#define LCD_CMD_BIT_SET		(u8)(SetD3)	//D3=1��Bit Set
										//D2-D0λѡ��7-0��ӦD7-D0λ

//==========================================================
//LCD��������
#define LCD_ADDR_X_MAX ((u8)(30)) //X�������ֵ(30*8=240)
#define LCD_ADDR_Y_MAX ((u8)(128))//Y�������ֵ(128)

#define LCD_GRH_ADDR_START ((u16)(0))//ͼ����ʼ��ַ
#define LCD_GRH_ADDR_WIDTH ((u8)(LCD_ADDR_X_MAX))//ͼ�ο���

#define LCD_TXT_ADDR_START ((u16)((LCD_ADDR_X_MAX)*(LCD_ADDR_Y_MAX)))  //�ı���ʼ��ַ
#define LCD_TXT_ADDR_WIDTH ((u8)(LCD_ADDR_X_MAX))//�ı�����

#define LCD_CGRAM_ADDR_OFFSET ((u8)(2))//��Ӧ�ⲿCGRAM�ĸ�5λ��ַ(A15-A11)
//�ı��ַ�80H���ⲿCGRAM���׵�ַΪ1400H
//Offset(A15-A11=00010)+Code(A10-A3=10000000)+Vertical counter(A2-A0=000) = 1400H
#define LCD_CGRAM_ADDR_START (((u16)(LCD_CGRAM_ADDR_OFFSET<<11)+(u16)(0x80<<3))+0)//�ַ�80H��Ӧ���ⲿCGRAM����ʼ��ַ

#define LCD_1608_CODE_START	((u8)(' '))//16*8�ı��ַ��ֿ����ʼ�ַ�
//LCD����ṹ�嶨��
typedef struct 
{
	u8 x;	//X����
	u8 y;	//Y����
}LcdAddr_TypeDef;

extern LcdAddr_TypeDef LcdAddr;//LCD��ַ�ṹ��

//==========================================================
//�����б�
//void Lcd_ReadBF(void);//��ȡҺ����״̬λֱ��BF��־��Ч(��200�κ��Զ��˳�)
void Lcd_WriteCmd(u8);//д����
void Lcd_WriteData(u8);//д����
void Lcd_AutoWriteData(u8);//�Զ�ģʽ��д����
void Lcd_Set_Grh_Addr(void);//LCDͼ������LcdAdr����
void Lcd_Set_Txt_Addr(void);//LCD�ı�����LcdAdr����
void Lcd_Clr(void);//ȫ������
void Lcd_Init(void);//Һ����ʼ��
void Lcd_Wr_Txt1608(u8 ch);//д�ı�ģʽ��8*16�ַ�
void Lcd_Wr_1608(u8 ch, u8 highlight);//д8*16�ַ�
void Lcd_Wr_1616(u8 *pt, u8 highlight);//д16*16�ַ�
//void Lcd_Wr_1212A(u8 *pt, u8 highlight);//д12*12�ַ�
//void Lcd_Wr_1212B(u8 *pt, u8 highlight);//д12*12�ַ�
//void Lcd_WR_CGRAM(void);//д�ַ����ݵ��ⲿCGRAM(code:80H-FFH)
void Lcd_Draw_Line(u8 x, u8 y, u8 len);//X=0:�����ߣ��������ߣ�len:���Ȼ�߶�

#endif 