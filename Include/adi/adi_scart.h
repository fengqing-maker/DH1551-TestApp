#ifndef _ADI_SCART_H_
#define _ADI_SCART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "adi_typedef.h"
#include "adi_error.h"

typedef enum
{
	EM_ADISCART_TYPE_IC,
	EM_ADISCART_TYPE_HW
}ADIScartType_E;


typedef struct
{
	int	m_nGPIO16_9;			/**<设置16:9或4:3*/
	int	m_nGPIOTV_AV;			/**<设置tv av输出*/
	int	m_nGPIOSlow_SW;			/**<是否连接了VCR*/
	int	m_nGPIOFastBlank;		/**<输出为RGB或s缎子*/
	int	m_nGPIOVCR_SW;			/**<TV scart 信号来源, STB信号或VCR信号*/
	int   m_nGPIOTV_SW;                      /**<VCR scart 信号来源, STB信号或TV信号*/
	unsigned int   m_dwReserved1;                         /**<保留位*/
	unsigned int   m_dwReserved2;				/**<保留位*/
}ADIScartGPIOCfg_S;


typedef enum
{
	EM_ADISCART_INDEX_TV, 	
	EM_ADISCART_INDEX_VCR
}ADIScartIndex_E;


typedef enum
{
	EM_ADISCART_SOURCE_VCR,
	EM_ADISCART_SOURCE_ENCODER,	
	EM_ADISCART_SOURCE_AUX,
	EM_ADISCART_SOURCE_TV
}ADIScartSignalSource_E;


typedef enum
{
	EM_ADISCART_DISPLAY_1_1,				//1:1
	EM_ADISCART_DISPLAY_4_3,				/**<4:3模式*/
	EM_ADISCART_DISPLAY_16_9				/**<16:9模式*/
}ADIScartDisplayMod_E;

typedef enum  
{
	EM_ADISCART_MOD_AV,						/**<AV模式*/
	EM_ADISCART_MOD_TV						/**<TV模式*/
}ADIScartAVTVMod_E;


typedef enum
{
	EM_ADISCART_COLOR_RGB,					/**<RGB模式模式*/
	EM_ADISCART_COLOR_CVBS					/**<CVBS模式*/
}ADIScartColorMod_E;


typedef enum
{
	EM_ADISCART_MSG_VCR_ON,
	EM_ADISCART_MSG_VCR_OFF,
	EM_ADISCART_MSG_TV_ON,
	EM_ADISCART_MSG_TV_OFF
}ADIScartPowerStatusMsg_E;

typedef enum
{
	EM_ADISCART_VCR_OFF_TV_OFF,	
	EM_ADISCART_VCR_OFF_TV_ON,
	EM_ADISCART_VCR_ON_TV_OFF,
	EM_ADISCART_VCR_ON_TV_ON
}ADIScartPowerStatus_E;


typedef enum
{
	EM_ADISCART_H_FOR_VCR_ON,
	EM_ADISCART_L_FOR_VCR_ON
}ADIScartVCRStatus_E;


typedef  void ( *ADIScartCallback )(  void * );

ADI_Error_Code ADIScartConfigI2CIndex(int I2CIndex);


ADI_Error_Code ADIScartInitialize( ADIScartType_E type, ADIScartGPIOCfg_S* pPIOCfg );


ADI_Error_Code ADIScartSetVCRStatus( ADIScartType_E type, ADIScartVCRStatus_E enmVCRStatus );


ADI_Error_Code ADIScartSignalSourceSwitch( ADIScartSignalSource_E SignalSource );

ADI_Error_Code ADIScartExtSignalSourceSwitch(  ADIScartIndex_E Scart, ADIScartSignalSource_E SignalSource );


ADI_Error_Code ADIScartSetAspectRatio( ADIScartIndex_E Scart,  ADIScartDisplayMod_E DisplayMode);


ADI_Error_Code ADIScartSetTVAVMod( ADIScartIndex_E Scart, ADIScartAVTVMod_E TVWorkMode);


ADI_Error_Code ADIScartColorModeSwitch( ADIScartIndex_E Scart, ADIScartColorMod_E ColorMode);


ADI_Error_Code ADIScartRegistCallBack( ADIScartCallback function);



#ifdef __cplusplus
}
#endif

#endif

