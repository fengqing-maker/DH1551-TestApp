
#ifndef _ADI_ERROR_H_
#define _ADI_ERROR_H_

#include "adi_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADI_SUCCESS   (0)     		       // ͨ�óɹ�����,����һ��ɹ����ø�ֵ��ʾ
#define ADI_TIMEOUT   (-1)
#define ADI_FAILURE   (0xFFFFFFFF)         // һ��ʧ�ܴ���,δ����ĳ�������ʹ�ø�ֵ�������鷵��ʵ�ʵĴ������ֵ������Ӧ��ʹ�ø�ֵ

typedef unsigned int    ADI_Error_Code;  // ƽ̨��������ֵ����


enum
{
   EM_ERROR_START_ADI	   = 0, 	   // ADIģ���������λ��ʼֵ
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

