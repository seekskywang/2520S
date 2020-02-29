#include "74LS595.h"
#include "pbdata.h"
#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */
char temp;

extern union 
{
   unsigned int _595A;
   struct 
   {
       unsigned char  O0:1;
       unsigned char  P1:1;
       unsigned char  F1:1;
       unsigned char  P2:1;
       unsigned char  F2:1;
       unsigned char  P3:1;
       unsigned char  F3:1;
       unsigned char  P4:1;
	   unsigned char  O1:1;
       unsigned char  F4:1;
       unsigned char  P5:1;
       unsigned char  F5:1;
       unsigned char  P6:1;
       unsigned char  F6:1;
       unsigned char  P7:1;
       unsigned char  F7:1;
   }BIT_FLAG;
}FLAG1;

static void delay595(u32 t)
{
	u32 i;
	while(t--)
		for (i = 0; i < 1; i++);
}

void In_595()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(SCK_595_GPIO_CLK | RCK_595_GPIO_CLK | SI_595_GPIO_CLK, ENABLE);
	//���74HC595����������ΪJTAG,��JTAG���Ž��ò�����Ϊͨ��GPIO����.
   //�����������Ϊͨ��GPIO����Ҫע�͵���������
//	GPIO_PinAFConfig

	
	GPIO_InitStructure.GPIO_Pin = SCK_595_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(SCK_595_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = RCK_595_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(RCK_595_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SI_595_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(SI_595_GPIO, &GPIO_InitStructure);
//	SCK_595_L();
//	RCK_595_L();
//	SI_595_L();
}


void LED595SendData(void)
{
    unsigned char i; //��������ʱ��ѭ��ʹ����ʱ����
	static unsigned int midd;
	
	midd = FLAG1._595A;
    for(i=0; i<16; i++) //��8λ���ݰ�λ����,�ȷ��͸��ֽں��͵��ֽ�
    {
        SCK_595_L();;//ʱ���ߵ͵�ƽ
		delay595(3);
        if( (midd & 0x8000) == 0x8000)//�ж����ݸߵ�λ
        {
            SI_595_H();                   //�����߸ߵ�ƽ
        }
        else
        {
            SI_595_L();          //�����ߵ͵�ƽ
        }
		delay595(3);
        midd = midd << 1;         //��������1λ
        SCK_595_H();                  //ʱ���߸ߵ�ƽ
		delay595(3);
    }
    //�������������
    RCK_595_L();
	delay595(3);
    RCK_595_H();
}


