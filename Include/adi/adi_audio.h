

#ifndef _ADI_AUDIO_H_
#define _ADI_AUDIO_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"
#include "adi_aout.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_MAX_VOLUME		(31)  // �������ֵ


enum
{
	ADIAUDIO_ERROR_BAD_PARAMETER = ADI_AUDIO_ERROR_BASE,
	ADIAUDIO_ERROR_INVALID_DEVICE_ID,
	ADIAUDIO_ERROR_FEATURE_NOT_SUPPORTED
};

/*��Ƶ����*/
typedef enum 
{
  	EM_ADIAUDIO_CHANNEL_STEREO,			// ������ 
  	EM_ADIAUDIO_CHANNEL_LEFT,			// ������ 
  	EM_ADIAUDIO_CHANNEL_RIGHT,			// ������ 
  	EM_ADIAUDIO_CHANNEL_MIXED_MONO		// ����� 
}ADIAUDIOChannelType_E;	


ADI_Error_Code ADIAUDIOGetCount(int * pnAudioDecCount);

ADI_Error_Code ADIAUDIOSetChannel(int nAudioIndex,ADIAUDIOChannelType_E eChannelType);


ADI_Error_Code ADIAUDIOMute(int nAudioIndex);


ADI_Error_Code ADIAUDIOUnmute(int nAudioIndex);


ADI_Error_Code ADIAUDIOSetVolume(int nAudioIndex,int nVolume);


ADI_Error_Code ADIAUDIOSetDeviceVolume(int nAudioIndex, ADIAOUTDevices_E eAudioDevice, int nVolume);

//Audio Description
ADI_Error_Code ADIAUDIOSetADVolume(int nAudioIndex,int nVolume);


ADI_Error_Code ADIAUDIOADEnable(int nAudioIndex,ADI_BOOL bEnable);



#ifdef  __cplusplus
}
#endif

#endif

