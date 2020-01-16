#include "pbdata.h"
#include "cpld.h"
//#define BEEP GPIO_SetBits()
void SM_RelayGPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD,ENABLE);
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;    
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_4;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_4;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
    GPIO_Init(GPIOD,&GPIO_InitStructure);


}
void PLC_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|
    RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOG,ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;     //pro
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_Init(GPIOH,&GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;     //fail
    GPIO_Init(GPIOA,&GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;     //pass
    GPIO_Init(GPIOC,&GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;     //START
    GPIO_Init(GPIOD,&GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;     //STOP
    GPIO_Init(GPIOG,&GPIO_InitStructure); 

}
void Led_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|
    RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOH,ENABLE);//
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;     //2  PASS
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_Init(GPIOE,&GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14;//10 FAIL  11  LOCK  12 TRIP  14 ON
    GPIO_Init(GPIOH,&GPIO_InitStructure); 
   // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//OFF
    GPIO_Init(GPIOD,&GPIO_InitStructure); 


}
void V_I_Select_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOG,ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_Init(GPIOG,&GPIO_InitStructure);
    


}
void Open_flag_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    
    


}
void Select_V_I(u8 ch)//1  电流  0  电压
{
    if(ch)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_13);
        GPIO_ResetBits(GPIOB,GPIO_Pin_6);
    
    }
    else
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_13);
        GPIO_SetBits(GPIOB,GPIO_Pin_6);
    
    }



}
void GPIO_Configuration(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;	
	//串口 用于调试
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD/
    RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOI,ENABLE);//
    
    /* 使能 USART 时钟 */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//|GPIO_Pin_2;//TX
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//|GPIO_Pin_3;//RX
//	GPIO_Init(GPIOB,&GPIO_InitStructure);

////  
//    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);

//  /*  连接 PXx 到 USARTx__Rx*/
//  GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
//  
  
    //RS485_1
    
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//|GPIO_Pin_2;//TX
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//|GPIO_Pin_3;//RX
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//    
//    
//    //RS485_2
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//|GPIO_Pin_2;//TX
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//    
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//|GPIO_Pin_3;//RX
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOD,&GPIO_InitStructure);
    
//    //485方向控制
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOD,&GPIO_InitStructure); 

	
    //4094控制端口
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//PC5是开机继电器
    
    
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
    
    GPIO_SetBits(GPIOC,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_1);
    
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_Init(GPIOH,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOH,GPIO_Pin_5);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_Init(GPIOI,&GPIO_InitStructure);
    
    
    //74HC595控制端口
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //ADS1216控制端口
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_11;
//	GPIO_Init(GPIOB,&GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init(GPIOI,&GPIO_InitStructure); 
    GPIO_ResetBits(GPIOI,GPIO_Pin_5);


    
//    //档位控制
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3\
//    |GPIO_Pin_4|GPIO_Pin_6;
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOE,&GPIO_InitStructure); 
//	
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
//    
////	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
    
     //ADS1216控制端口输入
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
 //   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_InitStructure); 
    
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOI,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure); 
	
	
    Led_GPIO_Configuration();//LED
    CPLD_GPIO_Configuration( );//CPLD端口配置
    V_I_Select_Configuration();//电流电压选择信号
    Open_flag_Configuration();//开路信号
    PLC_GPIO_Configuration();//PLC控制信号
    SM_RelayGPIO_Configuration();

	
	
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   	
}

void CH1COMP(u8 status)
{
	if(status == 1)
	{
		GPIO_SetBits(GPIOI,GPIO_Pin_3);
	}else if(status == 0){
		GPIO_ResetBits(GPIOI,GPIO_Pin_3);
	}
}

void CH2COMP(u8 status)
{
	if(status == 1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_6);
	}else if(status == 0){
		GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	}
}


void CH3COMP(u8 status)
{
	if(status == 1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
	}else if(status == 0){
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	}
}


void CH4COMP(u8 status)
{
	if(status == 1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_5);
	}else if(status == 0){
		GPIO_ResetBits(GPIOD,GPIO_Pin_5);
	}
}

u8 Read_Openflag(void)
{
    return GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_6);

}

u8 Read_ExtTrig(void)
{
    return GPIO_ReadInputDataBit( GPIOD,  GPIO_Pin_13);

}

void Beep_On(void)
{
    GPIO_SetBits(GPIOH,GPIO_Pin_5);
   // GPIO_ResetBits(GPIOH,GPIO_Pin_10);

}
void Beep_Off(void)
{
    GPIO_ResetBits(GPIOH,GPIO_Pin_5);

}
void Key_beep(void)
{
    Beep_On();
    delay_ms(10);
    Beep_Off();
}
void Power_Relay_on(void)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_5);

}
void Power_Relay_OFF(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);

}
void Power_On_led(void)//开关红灯亮
{
    Turnoff_Led();
    Power_Relay_OFF();


}
void Power_Off_led(void)//开关绿灯亮
{
    Turnon_Led();
    Power_Relay_on();

}
void All_LedOff(void )//关所有的灯 除了开关按键灯
{
    GPIO_ResetBits(GPIOE,GPIO_Pin_2);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
    GPIO_ResetBits(GPIOH,GPIO_Pin_10);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    Lock_Off();
    Trip_Off();
    
    


}
void Led_Pass_On(void)//不合格
{
	GPIO_SetBits(GPIOE,GPIO_Pin_2);
    GPIO_SetBits(GPIOA,GPIO_Pin_0);
    GPIO_ResetBits(GPIOH,GPIO_Pin_10);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);

}
void Led_Fail_On(void)//合格灯
{
    GPIO_SetBits(GPIOH,GPIO_Pin_10);
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);

}
void Close_Compled(void)
{
//	GPIO_SetBits(GPIOH,GPIO_Pin_10);
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
//	GPIO_SetBits(GPIOE,GPIO_Pin_2);
    GPIO_SetBits(GPIOA,GPIO_Pin_0);
    GPIO_ResetBits(GPIOH,GPIO_Pin_10);
//    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
//    GPIO_ResetBits(GPIOA,GPIO_Pin_0);


}
void Turnon_Led(void)
{
    GPIO_SetBits(GPIOH,GPIO_Pin_14);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);

}
void Turnoff_Led(void)
{
    GPIO_SetBits(GPIOD,GPIO_Pin_3);
	GPIO_ResetBits(GPIOH,GPIO_Pin_14);

}
void Lock_On(void)
{
    GPIO_SetBits(GPIOH,GPIO_Pin_11);
}
void Lock_Off(void)
{
    GPIO_ResetBits(GPIOH,GPIO_Pin_11);
}

void Trip_On(void)
{
    GPIO_SetBits(GPIOH,GPIO_Pin_12);
}
void Trip_Off(void)
{
    GPIO_ResetBits(GPIOH,GPIO_Pin_12);
}
void PGA_20mR(void)//200m
{
    cpld_buff[1]=0x10;
//   _4094_databuff[0]=0x48;
//   ADS1216_Set_IO(0x02,3);

}
void PGA_200mR(void)//2R
{
    _4094_databuff[0]=0x48;
    ADS1216_Set_IO(0x02,3);

}
void PGA_2R(void)//20R
{
    _4094_databuff[0]=0x48;
    ADS1216_Set_IO(0x01,1);//5倍
}  

void PGA_20R(void)//200R
{
    _4094_databuff[0]=0x88;
    ADS1216_Set_IO(0x01,1);//放大5倍

} 
void PGA_200R(void)//2K
{
    _4094_databuff[0]=0x9;
    ADS1216_Set_IO(0x01,1);//放大5倍
   


} 

void PGA_2kR(void)//20K
{
    _4094_databuff[0]=0x8;
    ADS1216_Set_IO(0,0);//不放大

}
void PGA_20kR(void)//20K
{

    _4094_databuff[0]=0x02;
    ADS1216_Set_IO(0,0);//不放大


}
void PGA_200kR(void)//200K
{
    
//    GPIO_SetBits(GPIOE,GPIO_Pin_6);
//   GPIO_SetBits(GPIOE,GPIO_Pin_0);
//   GPIO_SetBits(GPIOE,GPIO_Pin_1);
//   GPIO_ResetBits(GPIOE,GPIO_Pin_2);
//   GPIO_SetBits(GPIOE,GPIO_Pin_3);
//   GPIO_ResetBits(GPIOE,GPIO_Pin_4);
//   GPIO_ResetBits(GPIOB,GPIO_Pin_11);
    _4094_databuff[0]=0x04;
    
   ADS1216_Set_IO(0,0);//不放大
   //ADS_1216_PGA(0);//不放大

}

//static void NVIC_Configuration_Gpioint(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* 配置NVIC为优先级组1 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* 配置中断源：按键1 */
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//  /* 配置抢占优先级：1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//  /* 配置子优先级：1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//  /* 使能中断通道 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

//}
void Enable_Extiint(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    

  /* 选择 EXTI 中断源 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  /* 中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  /* 上升沿触发 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  /* 使能中断/事件线 */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

}
void Disable_Extiint(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    

  /* 选择 EXTI 中断源 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  /* 中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  /* 上升沿触发 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  /* 使能中断/事件线 */
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);

}

void EXTI_Ads1251_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
  
	/*开启按键GPIO口的时钟*/
//	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB,ENABLE);
  
  /* 使能 SYSCFG 时钟 ，使用GPIO外部中断时必须使能SYSCFG时钟*/
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* 配置 NVIC */
//  NVIC_Configuration_Gpioint();
  
	/* 选择按键1的引脚 */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  /* 设置引脚为输入模式 */ 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	    		
  /* 设置引脚不上拉也不下拉 */
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  /* 使用上面的结构体初始化按键 */
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* 连接 EXTI 中断源 到key1引脚 */
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource13);
   // Enable_Extiint();
 //  Enable_Extiint();
  


}
u8 read_cpld(void)
{
    u8 flag;
    if(Readfirst_cpld==1)//上次是开路
    {
        if(Read_Openflag()==0)//不再开路
        {
            Readfirst_cpld=0;
            //f_switch=TRUE;
            //Range=RANGE_MAX;
            open_flag=1;
            flag=0;
        
        }
        else
            open_flag=0;
            
    
    }
    else//上次不是开路
    {
        if(Read_Openflag()==1)//开路
        {
            Readfirst_cpld=1;//开路标志位
            //f_switch=TRUE;//继电器动作
            open_flag=0;
            flag=1;
            //Range=RANGE_MAX;
        
        }
        else
            open_flag=1;
        
    
    }
    return flag;

}
void sm_RYsel(u8 date)
{
	if(date==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
        GPIO_SetBits(GPIOC,GPIO_Pin_4);
	
	
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
        GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	
	}

}	


void Plc_Comp(u8 ch,u8 res)
{
	switch(ch)
	{
		case 0:
		{
			CH1COMP(res);
		}break;
		case 1:
		{
			CH2COMP(res);
		}break;
		case 2:
		{
			CH3COMP(res);
		}break;
		case 3:
		{
			CH4COMP(res);
		}break;
		default:break;
	}
}


void Relay_Select(u8 channel)
{
    switch(channel)
    {
        case 0:
            GPIO_ResetBits(GPIOA,GPIO_Pin_15);
            GPIO_ResetBits(GPIOD,GPIO_Pin_11);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
           
            break;
        case 1:
             GPIO_SetBits(GPIOA,GPIO_Pin_15);
            GPIO_ResetBits(GPIOD,GPIO_Pin_11);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
		case 2:
             GPIO_ResetBits(GPIOA,GPIO_Pin_15);
            GPIO_SetBits(GPIOD,GPIO_Pin_11);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
        case 3:
             GPIO_SetBits(GPIOA,GPIO_Pin_15);
            GPIO_SetBits(GPIOD,GPIO_Pin_11);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
        case 4:
             GPIO_ResetBits(GPIOA,GPIO_Pin_15);
            GPIO_ResetBits(GPIOD,GPIO_Pin_11);
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
        case 5:
             GPIO_SetBits(GPIOA,GPIO_Pin_15);
            GPIO_ResetBits(GPIOD,GPIO_Pin_11);
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
        case 6:
             GPIO_ResetBits(GPIOA,GPIO_Pin_15);
            GPIO_SetBits(GPIOD,GPIO_Pin_11);
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
        case 7:
             GPIO_SetBits(GPIOA,GPIO_Pin_15);
            GPIO_SetBits(GPIOD,GPIO_Pin_11);
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOC,GPIO_Pin_2);
            break;
        case 8:
             GPIO_ResetBits(GPIOA,GPIO_Pin_15);
            GPIO_ResetBits(GPIOD,GPIO_Pin_11);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_SetBits(GPIOC,GPIO_Pin_2);
            break;
        case 9:
             GPIO_SetBits(GPIOA,GPIO_Pin_15);
            GPIO_ResetBits(GPIOD,GPIO_Pin_11);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_SetBits(GPIOC,GPIO_Pin_2);
            break;
        
		default:
			break;
    
    
    
    }



}  
