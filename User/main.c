#include "pbdata.h"
#include "bsp_exti.h"


int main(void)
{  	
	//SetSystemStatus(SYS_STATUS_POWER);//开机上电状态
    EXTI_Key_Config();
    g_LcdDirection=1;
    softswitch=0;
    Int_Pe3flag=0;
    SetSystemStatus(SYS_STATUS_TOOL);
    GPIO_Configuration();//端口初始化

	while(1)
	{
		switch(GetSystemStatus())
		{
			case SYS_STATUS_POWER:
				Power_Process();//开机上电处理
				break;
			case SYS_STATUS_SETUP:
				Setup_Process();//设置处理
				break;

			case SYS_STATUS_TEST:
				Test_Process();//测试处理
				break;

            case SYS_STATUS_SYSSET : //系统设置
                
                Use_SysSetProcess();
                break;
			case SYS_STATUS_DEBUG:
				Use_DebugProcess();//调试处理
				break;	

			case SYS_STATUS_RESET:
				//Reset_Process();//软件复位处理
				break;
            
            case SYS_STATUS_SYS://系统信息显示
				
				Sys_Process();
				break;
            case SYS_STATUS_CLEAR:
                Clear_Process();
                break;
            case SYS_STATUS_TOOL://工具
				Soft_Turnon();
			break;
            case SYS_STATUS_R_COMP://电阻比较设置ak;
                Setup_R_Comp_Process();
                
            break;
             case SYS_STATUS_V_COMP://电压比较设置ak;
                 Setup_V_Comp_Process();
                
            break;
             case SYS_STATUS_C_LECT://通道选择设置
                 Setup_Channel_Process();
                 break;
			default:
//				Disp_Clr( );//清屏
				//Error_Process();//错误处理
				break;
		}
		

	}	
}









