
#ifndef _ADI_SCREEN_H_
#define _ADI_SCREEN_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif
 
#define ADI_HDCPKEY_MAX_SIZE	(1152)
/*视频播放相关错误代码值*/
enum
{
	ADISCREEN_ERROR_BAD_PARAMETER = ADI_SCREEN_ERROR_BASE,  // 错误参数类型
	ADISCREEN_ERROR_FEATURE_NOT_SUPPORTED,      			// 不支持此操作
	ADISCREEN_ERROR_ALREADY_ADDED							// 该回调已经注册
};

/*视频输出通道类型*/
typedef enum
{
	EM_ADI_VOUT_DEVICE_SD	= 1,			//标清输出通道
	EM_ADI_VOUT_DEVICE_HD	= 1 << 1		//高清输出通道
}ADISCREENType_E;

/*视频输出分辨率*/
typedef enum 
{
	EM_ADISCREEN_RESOLUTION_INVALID,
	EM_ADISCREEN_RESOLUTION_NTSC,  			//  SD: EM_ADICTL_MIX_ENCODING_MODE_NTSCM 
	EM_ADISCREEN_RESOLUTION_NTSC_443,		//  NTSC M mode but with 4.43361875MHz color subcarrier frequency. 
	EM_ADISCREEN_RESOLUTION_NTSC_JAPAN,	    //  Japan NTSC, no pedestal level 
	EM_ADISCREEN_RESOLUTION_PAL, 		    //  SD: EM_ADICTL_MIX_ENCODING_MODE_PALBDGHI 
	EM_ADISCREEN_RESOLUTION_PAL_M,        	//  PAL Brazil 
	EM_ADISCREEN_RESOLUTION_PAL_N,        	// PAL_N 
	EM_ADISCREEN_RESOLUTION_PAL_NC,      	//  PAL_N, Argentina (PAL N mode but with 3.58205625 MHz color subcarrier frequency and no pedestal (= 0 IRE blanking setup)) 
	EM_ADISCREEN_RESOLUTION_PAL_B,			// Australia 
	EM_ADISCREEN_RESOLUTION_PAL_B1,		    // Hungary 
	EM_ADISCREEN_RESOLUTION_PAL_D,			//  China ==EM_ADISCREEN_RESOLUTION_PAL 
	EM_ADISCREEN_RESOLUTION_PAL_D1,		    //  Poland 
	EM_ADISCREEN_RESOLUTION_PAL_G,			// Europe. Same as EM_ADISCREEN_RESOLUTION_PAL. 
	EM_ADISCREEN_RESOLUTION_PAL_H,			//  Europe 
	EM_ADISCREEN_RESOLUTION_PAL_K,	      	// Europe 
	EM_ADISCREEN_RESOLUTION_PAL_I,			//  U.K. 
	EM_ADISCREEN_RESOLUTION_SECAM,      	// SECAM III B6 
	
	EM_ADISCREEN_RESOLUTION_480P,           // NTSC Progressive (27Mhz) 	
	EM_ADISCREEN_RESOLUTION_576P, 		    //  Australian mode 	
	EM_ADISCREEN_RESOLUTION_720P,  		    // HD: EIA770.3 #1 P60 = SMPTE 296M #1 P60 //19
	EM_ADISCREEN_RESOLUTION_720P_24HZ,      //  HD 720p 24Hz 	
	EM_ADISCREEN_RESOLUTION_720P_50HZ,	    // HD 720p 50Hz
	
	EM_ADISCREEN_RESOLUTION_1080I,  	    // HD: EIA770.3 #3 I60 = SMPTE274M #4 I60 		
	EM_ADISCREEN_RESOLUTION_1080I_50HZ,     //  HD:  SMPTE 274M   I50  //23
	
	EM_ADISCREEN_RESOLUTION_1080P,          //  HD 1080 Progressive, 60Hz 
	EM_ADISCREEN_RESOLUTION_1080P_24HZ,     //  HD 1080 Progressive, 24Hz 
	EM_ADISCREEN_RESOLUTION_1080P_25HZ,	    //  HD 1080 Progressive, 25Hz 
	EM_ADISCREEN_RESOLUTION_1080P_30HZ,	    //  HD 1080 Progressive, 30Hz 
	EM_ADISCREEN_RESOLUTION_1080P_50HZ,     //  HD 1080 Progressive, 50Hz 	
	EM_ADISCREEN_RESOLUTION_1250I_50HZ,     //  HD 1250 Interlaced, 50Hz 
	
	EM_ADISCREEN_RESOLUTION_VESA,			//  PC monitor. Requires width, height and refresh rate parameters 
	EM_ADISCREEN_RESOLUTION_480I,
	EM_ADISCREEN_RESOLUTION_576I,

	EM_ADISCREEN_RESOLUTION_4K_3840x2160_24P,  	    // HD: 4K 3840x2160 Progressive, 24Hz
	EM_ADISCREEN_RESOLUTION_4K_3840x2160_25P,  	    // HD: 4K 3840x2160 Progressive, 25Hz
	EM_ADISCREEN_RESOLUTION_4K_3840x2160_30P,  	    // HD: 4K 3840x2160 Progressive, 30Hz 	
	EM_ADISCREEN_RESOLUTION_4K_3840x2160_50P,  	    // HD: 4K 3840x2160 Progressive, 50Hz 	
	EM_ADISCREEN_RESOLUTION_4K_3840x2160_60P,  	    // HD: 4K 3840x2160 Progressive, 60Hz	

	EM_ADISCREEN_RESOLUTION_4K_4096x2160_24P,  	    // HD: 4K 4096x2160 Progressive, 24Hz	
	EM_ADISCREEN_RESOLUTION_4K_4096x2160_25P,  	    // HD: 4K 4096x2160 Progressive, 25Hz
	EM_ADISCREEN_RESOLUTION_4K_4096x2160_30P,  	    // HD: 4K 4096x2160 Progressive, 30Hz	
	EM_ADISCREEN_RESOLUTION_4K_4096x2160_50P,  	    // HD: 4K 4096x2160 Progressive, 50Hz	
	EM_ADISCREEN_RESOLUTION_4K_4096x2160_60P,  	    // HD: 4K 4096x2160 Progressive, 60Hz
	
	EM_ADISCREEN_RESOLUTION_NUM
} ADISCREENResolution_E;

//定义COPYCONTROL模式
typedef enum
{
	EM_ADISCREEN_COPYCONTROL_COPY_FREELY,	//免费拷贝
	EM_ADISCREEN_COPYCONTROL_COPY_NO_MORE,	//预留
	EM_ADISCREEN_COPYCONTROL_COPY_ONCE,		//只允许拷贝一次
	EM_ADISCREEN_COPYCONTROL_COPY_NEVER,	//不允许拷贝
	EM_ADISCREEN_COPYCONTROL_COPY_MAX	
}ADISCREENCopyControlMode_E;


typedef enum 
{   
    EM_ADISCREEN_COPYCONTROL_INVALID,      
    EM_ADISCREEN_COPYCONTROL_HDCP, //HDCP
    EM_ADISCREEN_COPYCONTROL_CGMS,  // CGMS
    EM_ADISCREEN_COPYCONTROL_MACROVISION, // MACROVISION
    EM_ADISCREEN_COPYCONTROL_NUM
}ADISCREENCopyControlType_E;


/*定义HDCP配置*/
typedef struct
{
	ADI_BOOL 	m_bHDCPFlag;//HDCP打开标志
	unsigned char m_aucHDCPKey[ADI_HDCPKEY_MAX_SIZE];//HDCP KEY
	int			m_nHDCPKeySize;//HDCP KEY 长度
}ADISYSHDCPCfg_S;

ADI_Error_Code ADISCREENInitExt(ADISCREENType_E * peScreenDevice, ADISCREENResolution_E * peResolution, int nCount);

ADI_Error_Code ADISCREENSetResolution(ADISCREENType_E* peScreenDevice, ADISCREENResolution_E* peResolution,int nCount);
ADI_Error_Code ADISCREENSetResolutionExt(ADISCREENType_E* peScreenDevice, ADISCREENResolution_E* peResolution,int nCount, ADI_BOOL bForce);

ADI_Error_Code ADISCREENGetResolution(ADISCREENType_E eScreenDevice,ADISCREENResolution_E * peResolution);

ADI_Error_Code  ADISCREENSetOSDTransparency(int nTransparency);

ADI_Error_Code ADISCREENSetBrightness(int nBrightness);

ADI_Error_Code ADISCREENSetContrast( int nContrast);

ADI_Error_Code ADISCREENSetSaturation( int nSaturation);

ADI_Error_Code ADISCREENSetCopyControlMode(ADISCREENCopyControlType_E eCopyControlType, unsigned int unValue1, void* unValue2 );



#ifdef  __cplusplus
}
#endif

#endif

