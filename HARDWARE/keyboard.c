#include "pbdata.h"

//==========================================================
//全局变量
Key_TypeDef Keyboard;//键码结构体

static u8 LastKeyVal;//上次键值
static u8 LastKeyTicks;//按键节拍
static u8 ContinueKeyTicks;//持续按键节拍
const u8 Scan_Value[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void Key_Delay(u32 num)
{
    while(num)
    {
        num--;
    }
    

}
void Keyboard_Init(void)
{
	
    
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOI|RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
    GPIO_SetBits(GPIOC,GPIO_Pin_9);
    
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(GPIOI,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	///GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	Keyboard.value=KEY_NONE;//键值为空
	Keyboard.state=FALSE;	//按键无效
	Keyboard.continuance=FALSE;//持续按键无效
	
	LastKeyVal=KEY_NONE;//上次键值
	LastKeyTicks=0;//按键节拍
	ContinueKeyTicks=0;//持续按键节拍
}

void _164Delaay(void)
{
	u16 i;
	for(i=0;i<10;i--)
	;

};
void HW_Sendvalueto164(u8 value)
{
	uint8_t i;
	_Hc164CpL;
	for(i=0;i<8;i++)
	{
		if((value&0x80)==0x80)
			_Hc164DH;
		else
			_Hc164DL;
		_Hc164CpH;
		_164Delaay();
		_Hc164CpL;
		value<<=1;
        //_164Delaay();
	}

}

//==========================================================
//函数名称：Key_Identiry
//函数功能：按键识别
//入口参数：无
//出口参数：U8 键值
//创建日期：2014.09.25 
//修改日期：2014.09.29 14:45
//备注说明：按键输入信号，0有效
//==========================================================
//u8 Key_Identiry(void)
//{
//	u16 key1;
//	u8 key;
//	
//	key1=GPIO_ReadInputData(GPIOG);//GPIOG->ODR;//
//	key1|=0x01ff;
//	if(key1!=0xFFFF)//按键输入信号有效
//	{
//		switch(key1)
//		{
//			case HW_KEY_SET:
//				key=KEY_SET;
//				break;
//			case HW_KEY_UP:
//				key=KEY_UP;
//				break;
//			case HW_KEY_DOWN:
//				key=KEY_DOWN;
//				break;
////			case HW_KEY_LEFT:
////				key=KEY_LEFT;
////				break;
////			case HW_KEY_RIGHT:
////				key=KEY_RIGHT;
////				break;
//			case HW_KEY_ENTER:
//				key=KEY_ENTER;
//				break;
//			case HW_KEY_RESET:
//				key=KEY_RESET;
//				break;
//			case HW_KEY_START:
//				key=KEY_START;
//				break;
//			default:
//				key=KEY_NONE;
//				break;
//		}
//	}
//	else
//	{
//		key=KEY_NONE;
//	}
////	if(key==KEY_NONE)
////	{
////		key2=GPIO_ReadInputData(GPIOC);
////		key2|=0XFFCF;
////		if(key2!=0xFFFF)//按键输入信号有效
////		{
////			switch(key2)
////			{
//////				case HW_KEY_SET:
//////					key=KEY_SET;
//////					break;
//////				case HW_KEY_UP:
//////					key=KEY_UP;
//////					break;
////				case HW_KEY_DOWN:
////					key=KEY_DOWN;
////					break;
//////				case HW_KEY_LEFT:
//////					key=KEY_LEFT;
//////					break;
//////				case HW_KEY_RIGHT:
//////					key=KEY_RIGHT;
//////					break;
//////				case HW_KEY_ENTER:
//////					key=KEY_ENTER;
//////					break;
////				case HW_KEY_RESET:
////					key=KEY_RESET;
////					break;
//////				case HW_KEY_START:
//////					key=KEY_START;
//////					break;
////				default:
////					key=KEY_NONE;
////					break;
////			}
////		}
////		else
////		{
////			key=KEY_NONE;
////		}
////	}
//	return (key);
//}
//==========================================================
//函数名称：Key_Init
//函数功能：按键结构体初始化
//入口参数：无
//出口参数：无
//创建日期：2014.09.29
//修改日期：2014.09.29 10:49
//备注说明：无
//==========================================================
//void Key_Init(void)
//{
//    Keyboard_Init();//按键端口初始化
//	Keyboard.value=KEY_NONE;//键值为空
//	Keyboard.state=FALSE;	//按键无效
//	Keyboard.continuance=FALSE;//持续按键无效
//	
//	LastKeyVal=KEY_NONE;//上次键值
//	LastKeyTicks=0;//按键节拍
//	ContinueKeyTicks=0;//持续按键节拍
//}

//==========================================================
//函数名称：Key_Read
//函数功能：读取按键
//入口参数：无
//出口参数：无
//创建日期：2014.09.29
//修改日期：2014.09.29 10:50
//备注说明：无
//==========================================================
u8 Key_Read(void)
{
	if (Keyboard.state)	//有键按下
	{
		Keyboard.state=FALSE;
		//Beep_One();	//蜂鸣器响一声
        Key_beep();
        
		return (Keyboard.value);
	}
	//可直接处理电源等通用按键
	return (KEY_NONE);	
}

//==========================================================
//函数名称：Key_Read_WithTimeOut
//函数功能：阻塞式读取按键
//入口参数：ticks:等待节拍数(50ms周期)
//出口参数：按键值
//创建日期：2014.09.29
//修改日期：2014.09.29 10:56
//备注说明：直到按键响应或限时到
//==========================================================
u8 Key_Read_WithTimeOut(u8 ticks)
{
   // u8 i=1;
//	if (ticks)//定时等待按键
//		{
			SetSoftTimer(KEYBOARD_SOFTTIMER,ticks);//设置按键延时周期(即软定时器设置,50ms周期)
				
			while ((!GetSoftTimerOut(KEYBOARD_SOFTTIMER))&&(!Keyboard.state)) //计时未到并且无按键按下
				{
//					RunOnKeyFree();//在按键等待过程中处理其他业务
                    //i=GetSoftTimerOut(KEYBOARD_SOFTTIMER);
				}
//		}
//	else//无限等待按键
//		{
//			while (!Keyboard.state) 
//				{
//					RunOnKeyFree();//在按键等待过程中处理其他业务
//				}			
//		}
	return Key_Read();//按键更新
}
//==========================================================
//函数名称：Key_Scan
//函数功能：按键扫描
//入口参数：无
//出口参数：无
//创建日期：2014.09.28 
//修改日期：2014.09.28 11:01
//备注说明：由10mS中断调用
//==========================================================
 u8 Key_Identiry(void)
{
    u8 row,i;
//	u8 scanvalue=0;
	u8 key_value=0xff;
	u8 value=0xff;
	HW_Sendvalueto164(0);
	if(GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_11)==0)
		row=0;
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)==0)
		row=1;
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)==0)
		row=2;
	else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)==0)
		row=3;
	else 
        row=4;
    if(row<4)
	{
		
		for(i=0;i<8;i++)
		{
			HW_Sendvalueto164(Scan_Value[i]);
            _164Delaay();
			switch(row)
			{
				case 0:
						
						if(GPIO_ReadInputDataBit(GPIOI, GPIO_Pin_11)==0)
						{
							
							value=i;
						}
						
					break;
				case 1:
					if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)==0)
						value=i;
					break;
				case 2:
					if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)==0)
						value=i;
					break;
				case 3:
					if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)==0)
						value=i;
					break;
				default:
					break;
			}
            if(value!=0xff)
			break;
		}
        if(value==0xff)
            return  KEY_NONE;
		key_value=row*8+value;
        return key_value;
	
	
	}
    else
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)==0)
        {
            return Key_TRIG;
        
        
        }
    return  KEY_NONE;
    
	
    
}

void Key_Scan(void)
{
	u8 keyval;
	
	keyval = Key_Identiry();//按键识别，返回键值

	//按键长短识别
	if (keyval==KEY_NONE)//无键
	{
		if (LastKeyVal)	//上次有键，短按键判别
		{
			if ( (LastKeyTicks>SHORTKEYCOUNT) && (LastKeyTicks<LONGKEYCOUNT) )
			{
				Keyboard.value=LastKeyVal;	//键值
				Keyboard.state=TRUE;		//有按键
			}
		}
		LastKeyVal=KEY_NONE;
		LastKeyTicks=0;
		Keyboard.continuance=FALSE; //持续按键	
	}
	else	//有键
	{
		if (LastKeyVal==keyval)//上次按键和本次按键相同
		{
			if (LastKeyTicks<LONGKEYCOUNT+1)//长按键节拍数100x10mS
				LastKeyTicks++;
			
			if (LastKeyTicks==LONGKEYCOUNT)//等于长按键节拍数
			{
				ContinueKeyTicks=0;//持续按键节拍
				//keyval|=LONG_PRESS;	//长按键
				Keyboard.value=keyval;	//键值
				Keyboard.state=TRUE;	//有按键
//				Keyboard.continuance=FALSE; //持续按键
				Keyboard.continuance=TRUE; //持续按键
			}
			else if (LastKeyTicks>LONGKEYCOUNT)//大于长按键节拍数
			{
				if(HW_KEYBOARD_CONTINUE_SUPPORT)//持续按键有效判别
				{
					//keyval|=LONG_PRESS;	//长按键
					Keyboard.value=keyval;//键值
//					Keyboard.state=TRUE;//有按键
					Keyboard.continuance=TRUE; //持续按键
					ContinueKeyTicks++;
					if(ContinueKeyTicks>CONTINUEKEYCOUNT)//持续按键节拍数
					{
						ContinueKeyTicks=0;//持续按键节拍
						if(Keyboard.state==FALSE)//按键已读取
							Keyboard.state=TRUE;//有按键
					}
				}
			}					
		}
		else//上次按键和本次按键不同
		{
			LastKeyVal=keyval;
			LastKeyTicks=0;
		}
	}
}

