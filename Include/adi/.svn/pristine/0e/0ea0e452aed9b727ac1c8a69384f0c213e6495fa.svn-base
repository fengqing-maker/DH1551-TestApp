#ifndef _ADI_PANEL_INIT_H_
#define _ADI_PANEL_INIT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "adi_typedef.h"


#define	ADIPANEL_LED_MAX_COM_PIN 6

/*Panel模块Panel类型枚举定义*/
typedef enum
{
	EM_PANEL_TYPE_COMMON_LED = 0, //普通LED面板
	EM_PANEL_TYPE_SPI_LED,        //面板使用pt6964,其具有锁存功能，采用SPI协议
	EM_PANEL_TYPE_COMMON_NO_LED,  //普通面板使用74HC164，无LED
	EM_PANEL_TYPE_GPIO_LED,       //普通面板，全部gpio控制，没有74H164，有LED
	EM_PANEL_TYPE_GPIO_NO_LED,    //普通面板，gpio控制按键，没有led不使用164。
	EM_PANEL_TYPE_MAX
}ADIPanelType_E;


/*Panel模块普通LED面板硬件配置结构体(引脚复用)*/
typedef struct
{
	unsigned char m_aucGpioComPin[ADIPANEL_LED_MAX_COM_PIN]; 	// LED面板位选线的GPIO口，参考硬件设计
	                             //pt6964面板  0: m_nGPIOSTB, 1: 中断引脚1, 2: 中断引脚2
	                             //其余备用
	                             //注意:不使用的pin配置请赋值为0xFF
	unsigned char m_ucGpioData;	 // 连接面板164芯片的Data引脚的GPIO
	                             //pt6964面板  m_nGPIOData
	                             //注意:不使用的pin配置请赋值为0xFF
	unsigned char m_ucGpioClk;	 // 连接面板164芯片的clock引脚的GPIO
	                             //pt6964面板  m_nGPIOCLK
	                             //注意:不使用的pin配置请赋值为0xFF
	unsigned char m_ucGpioKey; 	 // 面板扫描按键的 GPIO
	                             //pt6964面板  备用
	                             //注意:不使用的pin配置请赋值为0xFF
	unsigned char m_aucReserved[3];//pt6964面板  备用
								   //注意:不使用的pin配置请赋值为0xFF
	                            
}ADIPanelCommonLedCfg_S;


/*Panel模块，普通面板，由gpio控制的面板使用此数据结构*/
typedef struct
{
	unsigned char m_ucLedSegPinGroup[8];    // 数码管seg管脚，不使用时一定设为0xff
	unsigned char m_ucLedComPinGroup[7];    // 数码管com管脚,不使用时一定设为0xff
	unsigned char m_ucLedStandby;           // 数码管standby管脚，不使用时一定设为0xff
	unsigned int  m_ulKeyNum;               // 按键数量，不使用时一定设为0xff
	unsigned char m_ucKeyPinGroup[8];       // 按键gpio配置，不使用时一定设为0xff
}ADIPanelGpioCfg_S;


ADI_Error_Code ADIPanelInit(int nIndex,ADIPanelType_E ePanelType,void *pParms);




#ifdef __cplusplus
}
#endif

#endif

