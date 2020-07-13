
#ifndef _ADI_RECORD_H_
#define _ADI_RECORD_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"

#ifdef __cplusplus
extern "C"
{
#endif 

#define ADI_REC_MAX_PID_COUNT 32

#define ADI_MAX_SECURITYKEY_LEN (128)  // ������볤�� ��λ:BYTES,����ָ��AED,DES������Կ����


/*¼����ش������ֵ*/
enum
{
	ADIREC_ERROR_BAD_PARAMETER = ADI_RECORD_ERROR_BASE,
	ADIREC_ERROR_FEATURE_NOT_SUPPORTED,
	ADIREC_ERROR_UNKNOWN_ERROR,
	ADIREC_ERROR_NO_MEMORY,
	ADIREC_ERROR_INVALID_DEVICE_ID,
	ADIREC_ERROR_INVALID_HANDLE,
	ADIREC_ERROR_RECORD_FULL,
	ADIREC_ERROR_ALREADY_STARTED,
	ADIREC_ERROR_ALREADY_STOPPED,
	ADIREC_ERROR_NOT_STARTED,
	ADIREC_ERROR_INVALID_PIDS,
	ADIREC_ERROR_TIME_FAILED,
	ADIREC_ERROR_NO_CALLBACK,
	ADIREC_ERROR_ALREADY_ADDED
};

/*¼������*/
typedef enum
{
	EM_ADIRECORD_TYPE_CHNL = 0,           // ¼��һ·��Ŀ��������ļ���ʽΪ�����ļ�
	EM_ADIRECORD_TYPE_TSHIFT,             // ʱ��¼��,������ļ���ʽΪѭ���ļ����ط�ʱ���Խ���trickmode����
	EM_ADIRECORD_TYPE_TS                  // ts��¼�ƣ�ts���а�����·��Ŀ��
}ADIRecType_E;

/*¼�ƻص���Ϣ*/
typedef enum
{
	EM_ADIRECORD_EVT_DISKFULL,      //   �洢�豸û�пռ���Ϣ
	EM_ADIRECORD_EVT_WRITEFAIL,     //   ¼��д�ļ�ʧ��
	EM_ADIRECORD_EVT_UNKNOWN,       //   δ֪��Ϣ����
	EM_ADIRECORD_EVT_MAX_NUM        //   ��Ч�߽�ֵ
}ADIRecEvent_E;

/*¼��ͨ���豸��Դ���ݽṹ����*/
typedef struct
{
	int m_nDemux;		// Demux�豸��Index��-1��������Demux�豸
}ADIRecChnl_S;

/*¼��ʱ����Ϣ*/
typedef struct {
	int       m_nStartTime;   		//  ¼�ƿ�ʼ�ľ���ʱ�䣬���ڷ�ʱ��¼����ʱ����ʱ��ʼ��Ϊ0
	int       m_nValidDuration;   	//  ¼����Чʱ�䣬��¼�ƿɲ��ŵ�ʱ��
} ADIRecTimeInfo_S;

/*�����������ͣ�һ������PVR*/
typedef enum
{
	EM_ADI_ENCRYPT_TYPE_FREE = 0,		// ������������
	EM_ADI_ENCRYPT_TYPE_CA,			    // ¼��ca������
	EM_ADI_ENCRYPT_TYPE_REENCRYPT,	    // ���μ�����(��ca���Ƴ���������ƽ̨����Ӳ����)
	EM_ADI_ENCRYPT_TYPE_SOFT_REENCRYPT, // ���μ�����(��ca���Ƴ���������ƽ̨���������)
	EM_ADI_ENCRYPT_TYPE_CA_REENCRYPT    // ���μ�����(��ca���Ƴ���������ƽ̨���μ��ܣ���ԿCA�ṩ)
}ADIStreamEncryptType_E;

/*¼��stream�������ݽṹ����*/
typedef struct
{
	ADIStreamEncryptType_E m_eEncryptType;				    //���ܷ�ʽ�����ADIRecEncryptType_E˵��
	unsigned char  m_ucEncryptKey[ADI_MAX_SECURITYKEY_LEN]; //���ܽ���Key,�����¼�ƾ��Ǽ���Key;����ǲ��ž��ǽ���Key
	int                    m_nEncryptKeyLength; 			//��Կ����
} ADIStreamEncryptParam_S;

/*����¼����Ϣ*/
typedef struct {
	ADIRecType_E		m_eRecType;								// ��·¼�Ƶ����ͣ����ADIRecType_E˵��
	char                m_szFileName[ADI_MAX_FILE_NAME_LEN];  	// ����¼�ƽ�����ļ�����ֻ֧��ASCII�����ʽ
	int					m_nCount;								// ¼�Ƶ�pid����
	ADIStreamInfo_S	    m_psPids[ADI_REC_MAX_PID_COUNT];    	// ��Ҫ¼�ƵĽ�Ŀpids ���ADIStreamInfo_S˵��
	ADI_BOOL			    m_bAppend;								// ׷��¼�ƣ�m_bAppend=falseʱ�����¼��Ŀ���ļ�����ʱ�����Ƚ�Ŀ���ļ�������ٴ�ͷд�ļ�
																// m_bAppend=trueʱ�����¼��Ŀ���ļ�����ʱ����ɾ�������ļ����������ļ�ĩβ׷��д
	unsigned int		m_nMaxSize;								// ¼����󳤶�(��λΪMB)������m_eRecType==EM_ADIRECORD_TYPE_TSHIFTʱ��Ч
    ADIStreamEncryptParam_S m_stEncryptParam; 					//�μ�ADIStreamEncryptParam_S
} ADIRecStartParam_S;

typedef int (*ADIRECCallback_F)(ADI_HANDLE hRecHandle,const ADIRecEvent_E eEvent, void* pvEventData,void * pvUserData);

ADI_Error_Code ADIRECAddCallback(ADI_HANDLE hRecHandle,ADIRECCallback_F fnRecordCallback, void * pvUserData);

ADI_Error_Code ADIRECDelCallback(ADI_HANDLE hRecHandle,ADIRECCallback_F fnRecordCallback,void * pvUserData);

ADI_Error_Code ADIRECOpen(const ADIRecChnl_S * psChnl, ADI_HANDLE * phRecHandle);

ADI_Error_Code ADIRECClose(ADI_HANDLE hRecHandle);

ADI_Error_Code ADIRECStart(ADI_HANDLE  hRecHandle,const ADIRecStartParam_S * psStartParam);

ADI_Error_Code ADIRECStop(ADI_HANDLE  hRecHandle);

ADI_Error_Code ADIRECStopTshift(ADI_HANDLE  hRecHandle,ADI_BOOL bSwitchToFile);

ADI_Error_Code ADIRECGetRecTime(ADI_HANDLE  hRecHandle, ADIRecTimeInfo_S * psTimeInfo);


#ifdef __cplusplus
}
#endif

#endif
