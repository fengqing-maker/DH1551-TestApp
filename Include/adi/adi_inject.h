
#ifndef _ADI_INJECTER_H_
#define _ADI_INJECTER_H_

#include "adi_public.h"
#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif 

/*����ע����ش������ֵ*/
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

/*Injecterö�����͵Ķ���*/
typedef enum 
{
	EM_INJECTER_PCM, 	      //  PCMע�벥���� 
	EM_INJECTER_ES,		      //  ESע�벥���� 
	EM_INJECTER_PES,	      //  PESע�벥���� 
	EM_INJECTER_TS,		      //  TSע�벥���� 
	EM_INJECTER_MAX
}ADIINJECTERType_E;


/*Injecter ע���ý�����ݵ�ö�ٶ���*/
typedef enum 
{
	EM_ADIINJECTER_CONTENT_DEFAULT,		//  Injecterע������ݣ�defaultΪȱʡ���� ��ָTS�Ȳ���Ҫ��û�а취�ֱ������Ƶ����Ƶ����ͼ����Ļ��Ϣ
	EM_ADIINJECTER_CONTENT_AUDIO,		//  Injecterע�������Ϊ��Ƶ����
	EM_ADIINJECTER_CONTENT_VIDEO,		//  Injecterע�������Ϊ��Ƶ���� 
	EM_ADIINJECTER_CONTENT_IFRAME,		//  Injecterע�������Ϊ��ƵIFrame���� 
	EM_ADIINJECTER_CONTENT_MAX
}ADIINJECTERContentType_E;

/**@brief Injecter ���Բ������͵�ö�ٶ���*/
typedef enum
{
	EM_ADIINJECTER_STATUS,		   ///< ��ȡINJECTER����״̬��Ϣ ,��ֵΪֻ��
	EM_ADIINJECTER_BUFFER,    	   ///< Injecter������buffer��Ϣ����ֵΪֻ��
	EM_ADIINJECTER_CALLBACK,	   ///< ����Injecter�ص��������ݲ���ʵ��
	EM_ADIINJECTER_PES_SYNC,	   ///< ���ע����֮���ͬ����Ϣ����ֵ�ɶ�д	
	EM_ADIINJECTER_PCM_PARAMS,     ///< PCMע�벥����������������ֵ�ɶ�д
	EM_ADIINJECTER_PCM_ENDIAN,     ///< PCM����ע�����ݵĴ�С���趨����Ĭ��ֵΪƽ̨�Ƽ�ֵ����ֵ�ɶ�д
	EM_ADIINJECTER_IFRAME_PARAMS   ///< IFrame���ݲ�������ֵ�ɶ�д
}ADIINJECTERAttributeType_E;


/*Injecter Buffer״̬��Ϣ�ṹ����*/
typedef struct
{
	int 	  m_nAvailableDataSize;			// Injecter�Ѿ�ע�뵽Ŀ�껺������������������У�����δ�����ĵ������ݳ���(��λ�ֽ�)��������ݳ�ʼֵΪ0���ܹ���ע�롢��������б���ѯ
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
	EM_ADIINJECTER_LITTLE_ENDIAN,		///< С���ֽ��� 
	EM_ADIINJECTER_BIG_ENDIAN			///< ����ֽ��� 
	
}ADIINJECTERPcmEndian_E;



/*Injecter ע��ͨ�����ͽṹ����*/
typedef struct 
{
 	ADIINJECTERType_E 			m_eInjecterType;  // Injecterʵ�����ͣ����ADIINJECTERType_E
	ADIINJECTERContentType_E 	m_eContentType;   // Injecter ע���ý����������
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
