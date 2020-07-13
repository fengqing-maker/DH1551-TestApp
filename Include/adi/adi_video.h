
#ifndef _ADI_VIDEO_H_
#define _ADI_VIDEO_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_screen.h"
#include "adi_osg.h"
#include "adi_error.h"
#include "adi_vout.h"


#ifdef  __cplusplus
extern "C" {
#endif

/*视频设备操作相关错误代码值*/
enum
{
	ADIVIDEO_ERROR_BAD_PARAMETER = ADI_VIDEO_ERROR_BASE,
	ADIVIDEO_ERROR_FEATURE_NOT_SUPPORTED,
	ADIVIDEO_ERROR_UNKNOWN_ERROR,
	ADIVIDEO_ERROR_NO_MEMORY,
	ADIVIDEO_ERROR_INVALID_DEVICE_ID,
	ADIVIDEO_ERROR_CALLBACK_EXIST,
	ADIVIDEO_ERROR_CALLBACK_NOT_EXIST
};


/*视频停止模式*/
typedef enum
{	
	EM_ADIVIDEO_STOPMODE_BLACK,	// 黑屏 
	EM_ADIVIDEO_STOPMODE_FREEZE	// 静帧 
	
}ADIVIDEOStopMode_E;


/*视频宽高比*/
typedef enum 
{
	EM_ADIVIDEO_ASPECT_RATIO_UNKNOWN,  
	EM_ADIVIDEO_ASPECT_RATIO_4_3,	        // 4：3
	EM_ADIVIDEO_ASPECT_RATIO_16_9,	        // 16：9 
	EM_ADIVIDEO_ASPECT_RATIO_AUTO		    // 自动选择 
}ADIVIDEOAspectRatioType_E;


/*视频解码信息*/
typedef struct 
{
	ADIVIDStreamType_E 	  m_eVidStreamType;		// 视频流类型
	int 			      m_nSourceWidth;		// 源视频流宽度
	int 			      m_nSourceHight;		// 源视频流高度
	int 			      m_nFrameRate;		    // 源视频流码率
	ADI_BOOL	              m_bInterlaced;		// ADI_TRUE表示隔行;ADI_FALSE表示逐行
	int			          m_dwFrameCount;		// 视频已播放的总帧数
	ADIVIDEOAspectRatioType_E m_eSourceAspectRatio; //视频源宽高比
}ADIVIDEOStreamStatus_S;

typedef enum 
{
	EM_ADIVIDEO_MATCH_METHOD_LETTER_BOX,	//  Letter Box 
	EM_ADIVIDEO_MATCH_METHOD_PAN_SCAN,	    //  Pan Scan 
	EM_ADIVIDEO_MATCH_METHOD_COMBINED,	    //  ComBined 
	EM_ADIVIDEO_MATCH_METHOD_IGNORE,	    // Ignore 
	EM_ADIVIDEO_MATCH_METHOD_LETTER_BOX_14_9, // Letter Box 14:9 
	EM_ADIVIDEO_MATCH_METHOD_PILLAR_BOX_14_9, // Pillar Box 14:9
	EM_ADIVIDEO_MATCH_METHOD_NUM            // 上限。
}ADIVIDEOMatchMethod_E;

/*VBI 功能类型*/
typedef enum 
{   
    EM_ADIVIDEO_VBI_TELTEXT=(1<<0),      // teltext
    EM_ADIVIDEO_VBI_CLOSECAPTION=(1<<1), //VBI CLOSE CAPTION
    EM_ADIVIDEO_VBI_MACROVISION=(1<<2),  // Macrovision
    EM_ADIVIDEO_VBI_CGMS=(1<<3) 		 // CGMS
}ADIVIDEOVBIType_E;

/*视频事件枚举定义*/
typedef enum 
{	
	EM_ADIVIDEO_USERDATA,		    	// 视频解码器user data事件，回调中pvEventData指向ADIVIDEOUserData_S结构体
	EM_ADIVIDEO_MAXEVENTTYPE		    // 边界值
}ADIVIDEOEventType_E; 

/*video中的user data数据结构定义*/
typedef struct
{
	void *			    m_pVideoUserdata;				// UserData数据Buffer地址
	unsigned int		m_uLength;						// UserData长度
	ADI_UINT64 	        m_u64Pts;						// PTS 
	ADI_BOOL		        m_bIsRegistered;				// 表示是否为已注册的UserData，为TRUE则结构体成员(m_ucCountryCode, m_ucCountryCodeExtensionByte & m_uProviderCode)有效
	unsigned char		m_ucCountryCode;				// Country code following ITU-T recommendation T.35
	unsigned char		m_ucCountryCodeExtensionByte;	// Country code extension byte. 注意：仅当m_ucCountryCode为0xFF有效
	unsigned short	    m_uProviderCode;				// manufacturers code
	unsigned int		m_adwReserved[4];				// 保留字段
} ADIVIDEOUserData_S;


typedef  void ( *ADIVIDEOCallback_F  )(int nVideoIndex, ADIVIDEOEventType_E eEvent, void * pvEventData, void * pvUserData);

ADI_Error_Code ADIVIDEOAddCallback(int nVideoIndex, ADIVIDEOCallback_F fnVideoCallback,ADIVIDEOEventType_E eEvent,void * pvUserData );

ADI_Error_Code ADIVIDEODelCallback(int nVideoIndex, ADIVIDEOCallback_F fnVideoCallback,ADIVIDEOEventType_E eEvent, void * pvUserData );
 
ADI_Error_Code ADIVIDEOSetVBIEnable(int nVideoIndex, ADIVIDEOVBIType_E eVideoVBIType, int nVbiPid, ADI_BOOL bEnable);

ADI_Error_Code ADIVIDEOGetCount(int * pnVideoDecCount);

ADI_Error_Code ADIVIDEOGetStreamStatus(int nVideoIndex,ADIVIDEOStreamStatus_S * psStreamStatus);

ADI_Error_Code ADIVIDEOShow(int nVideoIndex, ADI_BOOL bIsShow);

ADI_Error_Code ADIVIDEOSetAspectRatio(int nVideoIndex,ADISCREENType_E eScreenDevice, ADIVIDEOAspectRatioType_E eAspectRatio);

ADI_Error_Code ADIVIDEOSetMatchMethod(int nVideoIndex,ADISCREENType_E eScreenDevice, ADIVIDEOMatchMethod_E eMatchMethod);

ADI_Error_Code ADIVIDEOSetStopMode(int nVideoIndex, ADIVIDEOStopMode_E eStopMode);

ADI_Error_Code ADIVIDEOSetWindowSize(int nVideoIndex, ADISCREENType_E eScreenDevice, const ADIWinRect_S * pstRect );

ADI_Error_Code ADIVIDEOGetWindowSize(int nVideoIndex, ADISCREENType_E eScreenDevice, ADIWinRect_S * pstRect );

ADI_Error_Code ADIVIDEOFreezeDisp(int nVideoIndex, ADI_BOOL bIsShow);

ADI_Error_Code ADIVIDEODeviceShow(ADIVOUTDevices_E eVoutDevice, ADI_BOOL bIsShow);

ADI_Error_Code ADIVIDEOClear(int nVideoIndex);

ADI_Error_Code ADIVIDEOGetDispRect(int nVideoIndex, ADISCREENType_E eScreenDevice, ADIWinRect_S *pstVideoDispRect);


#ifdef  __cplusplus
}
#endif

#endif
