
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

#define ADI_MAX_SECURITYKEY_LEN (128)  // 最大密码长度 单位:BYTES,用于指定AED,DES加密密钥长度


/*录制相关错误代码值*/
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

/*录制类型*/
typedef enum
{
	EM_ADIRECORD_TYPE_CHNL = 0,           // 录制一路节目，保存的文件形式为线性文件
	EM_ADIRECORD_TYPE_TSHIFT,             // 时移录制,保存的文件形式为循环文件，回放时可以进行trickmode操作
	EM_ADIRECORD_TYPE_TS                  // ts流录制（ts流中包含多路节目）
}ADIRecType_E;

/*录制回调信息*/
typedef enum
{
	EM_ADIRECORD_EVT_DISKFULL,      //   存储设备没有空间消息
	EM_ADIRECORD_EVT_WRITEFAIL,     //   录制写文件失败
	EM_ADIRECORD_EVT_UNKNOWN,       //   未知消息类型
	EM_ADIRECORD_EVT_MAX_NUM        //   无效边界值
}ADIRecEvent_E;

/*录制通道设备资源数据结构定义*/
typedef struct
{
	int m_nDemux;		// Demux设备的Index，-1代表不存在Demux设备
}ADIRecChnl_S;

/*录制时间信息*/
typedef struct {
	int       m_nStartTime;   		//  录制开始的绝对时间，对于非时移录类型时，该时间始终为0
	int       m_nValidDuration;   	//  录制有效时间，即录制可播放的时长
} ADIRecTimeInfo_S;

/*码流加密类型，一般用于PVR*/
typedef enum
{
	EM_ADI_ENCRYPT_TYPE_FREE = 0,		// 清流，不加密
	EM_ADI_ENCRYPT_TYPE_CA,			    // 录制ca加密流
	EM_ADI_ENCRYPT_TYPE_REENCRYPT,	    // 二次加密流(先ca解绕成清流，再平台二次硬加密)
	EM_ADI_ENCRYPT_TYPE_SOFT_REENCRYPT, // 二次加密流(先ca解绕成清流，再平台二次软加密)
	EM_ADI_ENCRYPT_TYPE_CA_REENCRYPT    // 二次加密流(先ca解绕成清流，再平台二次加密，密钥CA提供)
}ADIStreamEncryptType_E;

/*录制stream加密数据结构定义*/
typedef struct
{
	ADIStreamEncryptType_E m_eEncryptType;				    //加密方式，详见ADIRecEncryptType_E说明
	unsigned char  m_ucEncryptKey[ADI_MAX_SECURITYKEY_LEN]; //加密解密Key,如果是录制就是加密Key;如果是播放就是解密Key
	int                    m_nEncryptKeyLength; 			//密钥长度
} ADIStreamEncryptParam_S;

/*启动录制信息*/
typedef struct {
	ADIRecType_E		m_eRecType;								// 该路录制的类型，详见ADIRecType_E说明
	char                m_szFileName[ADI_MAX_FILE_NAME_LEN];  	// 保存录制结果的文件名，只支持ASCII编码格式
	int					m_nCount;								// 录制的pid个数
	ADIStreamInfo_S	    m_psPids[ADI_REC_MAX_PID_COUNT];    	// 需要录制的节目pids 详见ADIStreamInfo_S说明
	ADI_BOOL			    m_bAppend;								// 追加录制，m_bAppend=false时，如果录制目标文件存在时，会先将目标文件清除后，再从头写文件
																// m_bAppend=true时，如果录制目标文件存在时，不删除现有文件，在现有文件末尾追加写
	unsigned int		m_nMaxSize;								// 录制最大长度(单位为MB)，仅当m_eRecType==EM_ADIRECORD_TYPE_TSHIFT时有效
    ADIStreamEncryptParam_S m_stEncryptParam; 					//参见ADIStreamEncryptParam_S
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
