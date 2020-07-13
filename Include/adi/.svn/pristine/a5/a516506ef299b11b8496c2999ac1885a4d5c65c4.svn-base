
#ifndef _ADI_AOUT_H_
#define _ADI_AOUT_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif


enum
{
	ADIAOUT_ERROR_BAD_PARAMETER = ADI_AOUT_ERROR_BASE,
	ADIAOUT_ERROR_INVALID_DEVICE_ID,
	ADIAOUT_ERROR_FEATURE_NOT_SUPPORTED	
};


typedef enum
{
	EM_ADIAOUT_RCA		= 1,			//“Ù∆µ◊Û”“…˘µ¿ ‰≥ˆ
	EM_ADIAOUT_SPDIF	= 1 << 1,
	EM_ADIAOUT_HDMI 	= 1 << 2
}ADIAOUTDevices_E;



typedef enum
{
	EM_ADIAOUT_DECODE,	
	EM_ADIAOUT_BYPASS	
}ADIAOUTMode_E;


ADI_Error_Code ADIAOUTMute(ADIAOUTDevices_E eAudioDevice);


ADI_Error_Code ADIAOUTUnmute(ADIAOUTDevices_E eAudioDevice);


ADI_Error_Code ADIAOUTSetOPMode(ADIAOUTDevices_E eAudioDevice,ADIAOUTMode_E eMode);

#ifdef  __cplusplus
}
#endif

#endif

