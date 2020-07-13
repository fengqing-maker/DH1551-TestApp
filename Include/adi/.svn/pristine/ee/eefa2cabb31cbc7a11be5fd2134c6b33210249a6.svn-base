
#ifndef _ADI_INJECTER_H_
#define _ADI_INJECTER_H_

#include "adi_public.h"
#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif 

/*数据注入相关错误代码值*/
enum
{
	ADIINJECTER_ERROR_BAD_PARAMETER = ADI_INJECT_ERROR_BASE,
	ADIINJECTER_ERROR_FEATURE_NOT_SUPPORTED,
	ADIINJECTER_ERROR_UNKNOWN_ERROR,
	ADIINJECTER_ERROR_NO_MEMORY,
	ADIINJECTER_ERROR_INVALID_DEVICE_ID,
	ADIINJECTER_ERROR_INVALID_HANDLE,
	ADIINJECTER_ERROR_INVALID_STATUS,
	ADIINJECTER_ERROR_DEVICE_BUSY,
	ADIINJECTER_ERROR_DEVICE_DISORDER,
	ADIINJECTER_ERROR_STREAMTYPE_NOT_MATCH_INJECTERTYPE,
	ADIINJECTER_ERROR_ALREADY_STARTED,
	ADIINJECTER_ERROR_ALREADY_STOPPED,
	ADIINJECTER_ERROR_NOT_STARTED

};

/*Injecter枚举类型的定义*/
typedef enum 
{
	EM_INJECTER_PCM, 	      //  PCM注入播放器 
	EM_INJECTER_ES,		      //  ES注入播放器 
	EM_INJECTER_PES,	      //  PES注入播放器 
	EM_INJECTER_TS,		      //  TS注入播放器 
	EM_INJECTER_MAX
}ADIINJECTERType_E;


/*Injecter 注入的媒体内容的枚举定义*/
typedef enum 
{
	EM_ADIINJECTER_CONTENT_DEFAULT,		//  Injecter注入的内容，default为缺省类型 ，指TS等不需要或没有办法分辨出是音频、视频还是图文字幕信息
	EM_ADIINJECTER_CONTENT_AUDIO,		//  Injecter注入的内容为音频数据
	EM_ADIINJECTER_CONTENT_VIDEO,		//  Injecter注入的内容为视频数据 
	EM_ADIINJECTER_CONTENT_IFRAME,		//  Injecter注入的内容为视频IFrame数据 
	EM_ADIINJECTER_CONTENT_MAX
}ADIINJECTERContentType_E;

/**@brief Injecter 属性参数类型的枚举定义*/
typedef enum
{
	EM_ADIINJECTER_STATUS,		   ///< 获取INJECTER缓冲状态信息 ,该值为只读
	EM_ADIINJECTER_BUFFER,    	   ///< Injecter启动的buffer信息，该值为只读
	EM_ADIINJECTER_CALLBACK,	   ///< 设置Injecter回调函数，暂不用实现
	EM_ADIINJECTER_PES_SYNC,	   ///< 多个注入器之间的同步信息，该值可读写	
	EM_ADIINJECTER_PCM_PARAMS,     ///< PCM注入播放器启动参数，该值可读写
	EM_ADIINJECTER_PCM_ENDIAN,     ///< PCM数据注入数据的大小端设定，其默认值为平台推荐值，该值可读写
	EM_ADIINJECTER_IFRAME_PARAMS   ///< IFrame数据参数，该值可读写
}ADIINJECTERAttributeType_E;


/*Injecter Buffer状态信息结构定义*/
typedef struct
{
	int 	  m_nAvailableDataSize;			// Injecter已经注入到目标缓冲区或解码器缓冲区中，但尚未被消耗掉的数据长度(单位字节)。这个数据初始值为0，能够在注入、解码过程中被查询
}ADIINJECTERStatus_S;


typedef struct
{
	unsigned int m_uBitsSample;
	unsigned int m_uSampleRate;
	unsigned int m_uChannels;
}ADIINJECTERPcmStartParam_S;

typedef struct 
{
	unsigned int m_unQueuedByte;        
	unsigned int m_unFifoSize;         
}ADIINJECTERPcmStatusParam_S;


typedef enum 
{
	EM_ADIINJECTER_LITTLE_ENDIAN,		///< 小端字节序 
	EM_ADIINJECTER_BIG_ENDIAN			///< 大端字节序 
	
}ADIINJECTERPcmEndian_E;



/*Injecter 注入通道类型结构定义*/
typedef struct 
{
 	ADIINJECTERType_E 			m_eInjecterType;  // Injecter实例类型，详见ADIINJECTERType_E
	ADIINJECTERContentType_E 	m_eContentType;   // Injecter 注入的媒体内容类型
}ADIINJECTEROpenParam_S;


ADI_Error_Code  ADIINJECTEROpen(const ADIINJECTEROpenParam_S * psOpenParams, ADI_HANDLE * phINJECTER);

ADI_Error_Code  ADIINJECTERClose(ADI_HANDLE hINJECTER);

ADI_Error_Code ADIINJECTERStart(ADI_HANDLE hINJECTER);

ADI_Error_Code ADIINJECTERSetAttribute(ADI_HANDLE hINJECTER,ADIINJECTERAttributeType_E eAttrType, const void * pvData);

ADI_Error_Code ADIINJECTERGetAttribute(ADI_HANDLE hINJECTER,ADIINJECTERAttributeType_E eAttrType, void * pvData);

ADI_Error_Code ADIINJECTERStop(ADI_HANDLE hINJECTER);

ADI_Error_Code ADIINJECTERFlush(ADI_HANDLE hINJECTER);

ADI_Error_Code ADIINJECTERClear(ADI_HANDLE hINJECTER);

ADI_Error_Code ADIINJECTERGetFreeBuffer(ADI_HANDLE hINJECTER, void ** ppvBuffer, unsigned  long * puLength );

ADI_Error_Code ADIINJECTERWriteComplete(ADI_HANDLE hINJECTER, void ** ppvBuffer, unsigned long uWrittenSize);


#ifdef  __cplusplus
}
#endif

#endif
