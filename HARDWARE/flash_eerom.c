#include "pbdata.h"
u32 GROUP_ADD[]={STORE_M1,STORE_M2,STORE_M3,STORE_M4,STORE_M5};
void Store_set_flash(void)
{
//	u16 i;
//	u32 addr;
	Jk510_Set_Typedef *ptt;
    ptt=&Jk510_Set;
    SPI_FLASH_SectorErase(0);
    delay_ms(10);
    SPI_FLASH_BufferWrite((u8 *)ptt, 0, sizeof(Jk510_Set));
}
//void Read_compvalue(u8 data)
//{
//	u32 addr;
//	u16 i;
//	System_TypeDef *pt;
//	pt= &System;
//	Parameter_valuecomp();
//	addr=GROUP_ADD[data];
//	for(i=0;i<sizeof(SaveData);i++)
//	{
//		*((u8*)pt+i)=*(((u8*)(addr))+i);//FMC_Read(addr+i);
//			
//	}

//}
void Read_set_flash(void)
{
//	u16 i;
	u32 addr;
	Jk510_Set_Typedef *ptt;
	ptt=&Jk510_Set;
	addr=STORESETADDR;
    addr=0;

    SPI_FLASH_BufferRead((u8*)ptt, addr, sizeof(Jk510_Set));
	//
	

}

