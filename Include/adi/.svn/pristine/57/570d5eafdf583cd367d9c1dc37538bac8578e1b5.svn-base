
#ifndef _ADI_SMC_H_
#define _ADI_SMC_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif


/*智能卡相关错误代码值*/
enum
{
	ADISMC_ERROR_BAD_PARAMETER = ADI_SMC_ERROR_BASE,
	ADISMC_ERROR_ERROR_PARITY,
	ADISMC_ERROR_ERROR_ANSWER,
	ADISMC_ERROR_TIMEOUT,
	
	ADISMC_ERROR_OUT , 
	ADISMC_ERROR_IN,
	ADISMC_ERROR_CARD_BUSY,
	ADISMC_ERROR_NOT_LOCK_OWNER,
	ADISMC_ERROR_READY,

	ADISMC_ERROR_MUTE,
	ADISMC_ERROR_ERROR_CARD,
	ADISMC_ERROR_INVALID_PROTOCOL,
	ADISMC_ERROR_NOT_RESET,
	ADISMC_ERROR_FAILURE,
	ADISMC_ERROR_NOT_SUPPORT
};

/*智能卡协议*/
typedef enum 
{
    EM_ADISMC_PROTOCOL_UNKNOWN,		    // 未知协议 
	EM_ADISMC_PROTOCOL_T0,				 
	EM_ADISMC_PROTOCOL_T1,				 
	EM_ADISMC_PROTOCOL_T14,			    
	EM_ADISMC_PROTOCOL_MAX
}ADISMCProtocol_E;

/*智能卡标准*/
typedef enum 
{
	EM_ADISMC_STANDARD_ISO,			// ISO标准，支持T0，T1协议
	EM_ADISMC_STANDARD_EMV2000,		// EMV2000标准 
	EM_ADISMC_STANDARD_IRDETO,		// 爱迪德标准 
	EM_ADISMC_STANDARD_MAX 
}ADISMCStandard_E;

/*智能卡校验位信息*/
typedef enum
{
	EM_ADISMC_8BITS_NO_PARITY,     // 8位无奇偶校验
	EM_ADISMC_8BITS_ODD_PARITY,    // 8位奇校验
	EM_ADISMC_8BITS_EVEN_PARITY,   // 8位偶校验
	EM_ADISMC_PARITY_MAX 
}ADISMCDataBits_E;

/*停止位类型枚举定义*/
typedef enum
{
	EM_ADISMC_STOP_0,    // 无停止位
	EM_ADISMC_STOP_1,    // 1个bit的停止位
	EM_ADISMC_STOP_2,    // 2个bit的停止位
	EM_ADISMC_STOP_3,    // 3个bit的停止位
	EM_ADISMC_STOP_MAX
}ADISMCStopBits_E;


/*智能卡属性信息*/
typedef struct
{
	int    m_nETU;                      // ETU:372,625...
	int    m_nBaudRate;                 // 波特率，例如：9600,115200
	int    m_nFrequency;                // 时钟频率:3570KHZ/4500KHZ
	ADISMCStandard_E  m_eStandard;      // 智能卡标准，初始化设置完后，后面的操作通过get获取此字段
	ADISMCProtocol_E  m_eProtocol;      // 智能卡传输协议:T0/T1/T14
	ADISMCStopBits_E  m_eStopBit;       // 停止位
	ADISMCDataBits_E  m_eCheckBit;      // 校验位:奇校验/偶校验/无校验	
}ADISMCParam_S;


typedef void (*ADISMCCallback)(int nCardIndex, ADI_Error_Code eStatus);

ADI_Error_Code ADISMCGetCount(int * pnSMCCount);

ADI_Error_Code ADISMCOpen(int nCardIndex, ADISMCCallback fnSMCCallback);

ADI_Error_Code ADISMCClose(int nCardIndex);

ADI_Error_Code ADISMCReset(int nCardIndex, unsigned char * pucAtr, int * pnAtrLength, ADI_BOOL bColdRst);

ADI_Error_Code ADISMCSetParams(int nCardIndex,const ADISMCParam_S * psSMCParams);

ADI_Error_Code ADISMCDataExchange(
									int             nCardIndex, 
									unsigned char  *pucWriteData,
	                                int             nNumberToWrite,
	                                unsigned char  *pcResponseData,
	                                int            *pnNumberRead,
	                                unsigned char  *pucStatusWord);


ADI_Error_Code ADISMCSetPPS(
						 int             nCardIndex,
	                     unsigned char  *pucWriteData,
                         int             nNumberToWriteLen,
	                     unsigned char  *pucResponseData,
                         int            *pnResponseDataLen);


unsigned int ADISMCDetectCardStatus( int nCardIndex );


#ifdef __cplusplus
}
#endif

#endif

