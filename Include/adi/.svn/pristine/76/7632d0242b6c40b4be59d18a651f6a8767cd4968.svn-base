
#ifndef _ADI_VOUT_H_
#define _ADI_VOUT_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*VOUT错误代码值*/
enum
{
	ADIVOUT_ERROR_BAD_PARAMETER = ADI_VOUT_ERROR_BASE,
	ADIVOUT_ERROR_INVALID_DEVICE_ID,
	ADIVOUT_ERROR_FEATURE_NOT_SUPPORTED
};

/*视频输出设备类型*/
typedef enum
{
	EM_ADIVOUT_CVBS,	// CSBVS视频输出接口
	EM_ADIVOUT_YC,	    // S-Video 视频输出接口
	EM_ADIVOUT_YUV,     // 分量视频输出接口 
	EM_ADIVOUT_RF,      // 射频信号视频输出接口 
	EM_ADIVOUT_SCART,   // SCART视频输出接口
	EM_ADIVOUT_HDMI,    // HDMI视频输出接口
	EM_ADIVOUT_DVO,     // 数字视频输出
	EM_ADIVOUT_NUM      // 视频接口个数
}ADIVOUTDevices_E;

/*视频输出端口的颜色类型 */
typedef enum
{
	EM_ADIVOUT_OUTPUT_TYPE_YUV, // YUV模式 
	EM_ADIVOUT_OUTPUT_TYPE_RGB, // RGB模式 
	EM_ADIVOUT_OUTPUT_TYPE_NUM	// 模式计数 
}ADIVOUTOutputType_E;

ADI_Error_Code ADIVOUTEnable(ADIVOUTDevices_E eVoutDevice);

ADI_Error_Code ADIVOUTDisable(ADIVOUTDevices_E eVoutDevice);

ADI_Error_Code ADIVOUTSetOutputType(ADIVOUTDevices_E eVoutDevice, ADIVOUTOutputType_E eType);

#ifdef  __cplusplus
}
#endif

#endif

