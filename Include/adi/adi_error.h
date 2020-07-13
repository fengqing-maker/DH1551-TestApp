
#ifndef _ADI_ERROR_H_
#define _ADI_ERROR_H_

#include "adi_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADI_SUCCESS   (0)     		       // 通用成功代码,所有一般成功均用该值表示
#define ADI_TIMEOUT   (-1)
#define ADI_FAILURE   (0xFFFFFFFF)         // 一般失败代码,未定义的出错代码可使用该值，但建议返回实际的错误代码值，而不应该使用该值

typedef unsigned int    ADI_Error_Code;  // 平台公共返回值类型


enum
{
   EM_ERROR_START_ADI	   = 0, 	   // ADI模块错误代码高位起始值
   EM_ERROR_START_MAX
};

enum
{
	ADI_AOUT_ERROR_BASE				= (EM_ERROR_START_ADI + 1) << 16,
	ADI_AUDIO_ERROR_BASE			= (EM_ERROR_START_ADI + 2) << 16,
	ADI_VIDEO_ERROR_BASE			= (EM_ERROR_START_ADI + 3) << 16,
	ADI_SCREEN_ERROR_BASE			= (EM_ERROR_START_ADI + 4) << 16,
	ADI_DESCRAMBLE_ERROR_BASE		= (EM_ERROR_START_ADI + 5) << 16,
	ADI_INJECT_ERROR_BASE			= (EM_ERROR_START_ADI + 6) << 16,
	ADI_RECORD_ERROR_BASE			= (EM_ERROR_START_ADI + 7) << 16,
	ADI_OSG_ERROR_BASE			    = (EM_ERROR_START_ADI + 8) << 16,
	ADI_SECTION_ERROR_BASE		    = (EM_ERROR_START_ADI + 9) << 16,
	ADI_SMC_ERROR_BASE			    = (EM_ERROR_START_ADI + 10) << 16,
	ADI_OS_ERROR_BASE				= (EM_ERROR_START_ADI + 11) << 16,
	ADI_FS_ERROR_BASE				= (EM_ERROR_START_ADI + 12) << 16,
	ADI_PLAYER_ERROR_BASE			= (EM_ERROR_START_ADI + 13) << 16,
	ADI_TUNER_ERROR_BASE			= (EM_ERROR_START_ADI + 14) << 16,
	ADI_FLASH_ERROR_BASE			= (EM_ERROR_START_ADI + 15) << 16,
	ADI_DEMUX_ERROR_BASE			= (EM_ERROR_START_ADI + 16) << 16,
	ADI_TOOLSET_ERROR_BASE		    = (EM_ERROR_START_ADI + 17) << 16,
	ADI_PANEL_ERROR_BASE			= (EM_ERROR_START_ADI + 18) << 16,
	ADI_IR_ERROR_BASE			    = (EM_ERROR_START_ADI + 19) << 16,
	ADI_HDMI_ERROR_BASE			    = (EM_ERROR_START_ADI + 20) << 16,
	ADI_VOUT_ERROR_BASE       	    = (EM_ERROR_START_ADI + 21) << 16,
	ADI_UART_ERROR_BASE       	    = (EM_ERROR_START_ADI + 22) << 16,
	ADI_DEBUG_ERROR_BASE            = (EM_ERROR_START_ADI + 23) << 16,
	ADI_NET_ERROR_BASE           	= (EM_ERROR_START_ADI + 24) << 16,
	ADI_MAX_ERROR_BASE
};


#ifdef __cplusplus
}
#endif


#endif  

