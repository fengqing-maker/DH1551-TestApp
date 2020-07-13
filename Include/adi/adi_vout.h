
#ifndef _ADI_VOUT_H_
#define _ADI_VOUT_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*VOUT�������ֵ*/
enum
{
	ADIVOUT_ERROR_BAD_PARAMETER = ADI_VOUT_ERROR_BASE,
	ADIVOUT_ERROR_INVALID_DEVICE_ID,
	ADIVOUT_ERROR_FEATURE_NOT_SUPPORTED
};

/*��Ƶ����豸����*/
typedef enum
{
	EM_ADIVOUT_CVBS,	// CSBVS��Ƶ����ӿ�
	EM_ADIVOUT_YC,	    // S-Video ��Ƶ����ӿ�
	EM_ADIVOUT_YUV,     // ������Ƶ����ӿ� 
	EM_ADIVOUT_RF,      // ��Ƶ�ź���Ƶ����ӿ� 
	EM_ADIVOUT_SCART,   // SCART��Ƶ����ӿ�
	EM_ADIVOUT_HDMI,    // HDMI��Ƶ����ӿ�
	EM_ADIVOUT_DVO,     // ������Ƶ���
	EM_ADIVOUT_NUM      // ��Ƶ�ӿڸ���
}ADIVOUTDevices_E;

/*��Ƶ����˿ڵ���ɫ���� */
typedef enum
{
	EM_ADIVOUT_OUTPUT_TYPE_YUV, // YUVģʽ 
	EM_ADIVOUT_OUTPUT_TYPE_RGB, // RGBģʽ 
	EM_ADIVOUT_OUTPUT_TYPE_NUM	// ģʽ���� 
}ADIVOUTOutputType_E;

ADI_Error_Code ADIVOUTEnable(ADIVOUTDevices_E eVoutDevice);

ADI_Error_Code ADIVOUTDisable(ADIVOUTDevices_E eVoutDevice);

ADI_Error_Code ADIVOUTSetOutputType(ADIVOUTDevices_E eVoutDevice, ADIVOUTOutputType_E eType);

#ifdef  __cplusplus
}
#endif

#endif

