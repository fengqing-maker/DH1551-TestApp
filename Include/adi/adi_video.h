
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

/*��Ƶ�豸������ش������ֵ*/
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


/*��Ƶֹͣģʽ*/
typedef enum
{	
	EM_ADIVIDEO_STOPMODE_BLACK,	// ���� 
	EM_ADIVIDEO_STOPMODE_FREEZE	// ��֡ 
	
}ADIVIDEOStopMode_E;


/*��Ƶ��߱�*/
typedef enum 
{
	EM_ADIVIDEO_ASPECT_RATIO_UNKNOWN,  
	EM_ADIVIDEO_ASPECT_RATIO_4_3,	        // 4��3
	EM_ADIVIDEO_ASPECT_RATIO_16_9,	        // 16��9 
	EM_ADIVIDEO_ASPECT_RATIO_AUTO		    // �Զ�ѡ�� 
}ADIVIDEOAspectRatioType_E;


/*��Ƶ������Ϣ*/
typedef struct 
{
	ADIVIDStreamType_E 	  m_eVidStreamType;		// ��Ƶ������
	int 			      m_nSourceWidth;		// Դ��Ƶ�����
	int 			      m_nSourceHight;		// Դ��Ƶ���߶�
	int 			      m_nFrameRate;		    // Դ��Ƶ������
	ADI_BOOL	              m_bInterlaced;		// ADI_TRUE��ʾ����;ADI_FALSE��ʾ����
	int			          m_dwFrameCount;		// ��Ƶ�Ѳ��ŵ���֡��
	ADIVIDEOAspectRatioType_E m_eSourceAspectRatio; //��ƵԴ��߱�
}ADIVIDEOStreamStatus_S;

typedef enum 
{
	EM_ADIVIDEO_MATCH_METHOD_LETTER_BOX,	//  Letter Box 
	EM_ADIVIDEO_MATCH_METHOD_PAN_SCAN,	    //  Pan Scan 
	EM_ADIVIDEO_MATCH_METHOD_COMBINED,	    //  ComBined 
	EM_ADIVIDEO_MATCH_METHOD_IGNORE,	    // Ignore 
	EM_ADIVIDEO_MATCH_METHOD_LETTER_BOX_14_9, // Letter Box 14:9 
	EM_ADIVIDEO_MATCH_METHOD_PILLAR_BOX_14_9, // Pillar Box 14:9
	EM_ADIVIDEO_MATCH_METHOD_NUM            // ���ޡ�
}ADIVIDEOMatchMethod_E;

/*VBI ��������*/
typedef enum 
{   
    EM_ADIVIDEO_VBI_TELTEXT=(1<<0),      // teltext
    EM_ADIVIDEO_VBI_CLOSECAPTION=(1<<1), //VBI CLOSE CAPTION
    EM_ADIVIDEO_VBI_MACROVISION=(1<<2),  // Macrovision
    EM_ADIVIDEO_VBI_CGMS=(1<<3) 		 // CGMS
}ADIVIDEOVBIType_E;

/*��Ƶ�¼�ö�ٶ���*/
typedef enum 
{	
	EM_ADIVIDEO_USERDATA,		    	// ��Ƶ������user data�¼����ص���pvEventDataָ��ADIVIDEOUserData_S�ṹ��
	EM_ADIVIDEO_MAXEVENTTYPE		    // �߽�ֵ
}ADIVIDEOEventType_E; 

/*video�е�user data���ݽṹ����*/
typedef struct
{
	void *			    m_pVideoUserdata;				// UserData����Buffer��ַ
	unsigned int		m_uLength;						// UserData����
	ADI_UINT64 	        m_u64Pts;						// PTS 
	ADI_BOOL		        m_bIsRegistered;				// ��ʾ�Ƿ�Ϊ��ע���UserData��ΪTRUE��ṹ���Ա(m_ucCountryCode, m_ucCountryCodeExtensionByte & m_uProviderCode)��Ч
	unsigned char		m_ucCountryCode;				// Country code following ITU-T recommendation T.35
	unsigned char		m_ucCountryCodeExtensionByte;	// Country code extension byte. ע�⣺����m_ucCountryCodeΪ0xFF��Ч
	unsigned short	    m_uProviderCode;				// manufacturers code
	unsigned int		m_adwReserved[4];				// �����ֶ�
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
