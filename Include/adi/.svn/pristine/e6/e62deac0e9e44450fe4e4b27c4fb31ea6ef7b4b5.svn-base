
#ifndef _ADI_CI_H_
#define _ADI_CI_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif 


typedef enum _CI_Register
{
	CI_MODULE_DATA,
	CI_MODULE_CONTROL = 1,
	CI_MODULE_STATUS = 1,
	CI_MODULE_SIZE_L = 2,
	CI_MODULE_SIZE_H = 3
		
}E_CI_Register;

typedef enum _CI_Slot
{
	SLOTA,
	SLOTB,
	SLOTMAX
		
}E_CI_Slot;

typedef enum _CI_IOAcessMode
{
	NOTUSE,
	ATTRIBUTE,
	IOACCESS
		
}E_CI_IOAcessMode;

typedef enum
{
	EM_ADICI_IN = 0,
	EM_ADICI_OUT = 1,
}ADICIStatus_E;

typedef void (*ADICIFnCallBack)(ADI_HANDLE hHandleCI, ADICIStatus_E eStatus);


ADI_Error_Code ADICIStart(ADI_HANDLE *pHandleCI, ADICIFnCallBack fnCAMCallback);


ADI_Error_Code ADICIStop(ADI_HANDLE hHandleCI, ADI_BOOL bTerminate);	


ADI_Error_Code ADICIGetInfo(ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICIRead
*    从模块中读取数据
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    数据长度
*     pcData[out];   读取数据的Buffer 

*
*Return Values
*       0 : SUCCESS 读取数据成功
*       -1: FAILURE 参数错误或读取数据失败
**************************************************************************/
ADI_Error_Code ADICIReadData(ADI_HANDLE hHandleCI, int* pnLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICIWrite
*    往模块中读写入数据
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    数据长度
*     pcData[in];   要写入的数据

*
*Return Values
*       0 : SUCCESS 写入数据成功
*       -1: FAILURE 参数错误或写入数据失败
**************************************************************************/
ADI_Error_Code ADICIWriteData(ADI_HANDLE hHandleCI, int nLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICICISRead
*    从模块属性内存中读取CIS 数据
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    数据长度
*     pcData[out];   读取数据的Buffer 

*
*Return Values
*       0 : SUCCESS 读取数据成功
*       -1: FAILURE 参数错误或读取数据失败
**************************************************************************/
ADI_Error_Code ADICICISReadData(ADI_HANDLE hHandleCI, int nLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICICISWrite
*    往模块属性内存中读写入数据
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    数据长度
*     pcData[in];   要写入的数据
*
*Return Values
*       0 : SUCCESS 写入数据成功
*       -1: FAILURE 参数错误或写入数据失败
**************************************************************************/
ADI_Error_Code ADICICISWriteData(ADI_HANDLE hHandleCI, unsigned long dwOffset, int nLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICIRegRead
*    读取模块寄存器的数据
*
*Parameters	
*     hHandleCI [in]:
*     eReg[in];    寄存器
*
		寄存器类型:
*	CI_MODULE_CONTROL,
*	CI_MODULE_STATUS,
*	CI_MODULE_SIZE_L,
*	CI_MODULE_SIZE_H
*
*    	pcByte[out];   寄存器的值
*
*Return Values
*       0 : SUCCESS 读取数据成功
*       -1: FAILURE 参数错误或读取数据失败
**************************************************************************/
ADI_Error_Code ADICIRegRead(ADI_HANDLE hHandleCI, E_CI_Register eReg, unsigned char *pcByte);


/**************************************************************************
*Function Name: ADICIRegWrite
*    往模块寄存器中写入数据
*
*Parameters	
*     hHandleCI [in]:
*     eReg[in];    寄存器
*
		寄存器类型:
*	CI_MODULE_CONTROL,
*	CI_MODULE_STATUS,
*	CI_MODULE_SIZE_L,
*	CI_MODULE_SIZE_H
*     pcByte[in];   寄存器的值
*
*Return Values
*       0 : SUCCESS 写入数据成功
*       -1: FAILURE 参数错误或写入数据失败
**************************************************************************/
ADI_Error_Code ADICIRegWrite(ADI_HANDLE hHandleCI, E_CI_Register eReg, unsigned char *pcByte);


/**************************************************************************
*Function Name: ADICICardDetect
*    检测是否有模块插入
*
*Parameters	
*      hHandleCI [in]:
*
*Return Values
*       1 : TRUE 检测到CAM 卡
*       0: FALSE 没有检测到CAM 卡
**************************************************************************/
ADI_BOOL ADICICamDetected(ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICIPowerOn
*    给模块上电
*
*Parameters	
*      hHandleCI [in]:
*
*Return Values
*       0 : SUCCESS 成功
*       -1: FAILURE 失败
**************************************************************************/
ADI_Error_Code ADICIPowerOnOff(ADI_HANDLE hHandleCI, ADI_BOOL bPowerOnOff);




/**************************************************************************
*Function Name: ADICIModuleReset
*    对模块进行复位
*
*Parameters	
*      hHandleCI [in]:
*
*Return Values
*       0 : SUCCESS 成功
*       -1: FAILURE 失败
**************************************************************************/
ADI_Error_Code ADICIModuleReset(ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICITSFlowConnect
*    选择TS 流流过哪个模块
*
*Parameters	
*      hTuner [in]:
*      hHandleCI [in]:
*	   hCpuChnl [in]:
*
*Return Values
*       0 : SUCCESS 成功
*       -1: FAILURE 失败
**************************************************************************/
//int ADICITunerSlotConnect(ADI_HANDLE hHandleCI, ADI_HANDLE hTuner);
ADI_Error_Code ADICITSFlowConnect(ADI_HANDLE hHandleCI, ADI_HANDLE hTuner,ADI_HANDLE hCpuChnl);


/**************************************************************************
*Function Name: ADICITSSelect
*    选择哪一路流进入主芯片
*
*Parameters	
*      hHandleCI [in]:
*      hCpuChannel [in]:CPU 通道号
*
*Return Values
*       0 : SUCCESS 成功
*       -1: FAILURE 失败
**************************************************************************/
ADI_Error_Code ADICITSSelect(ADI_HANDLE hHandleCI, ADI_HANDLE hCpuChnl);


/**************************************************************************
*Function Name: ADICIConfigAccessMode
*    选择I/O读写模式
*
*Parameters	
*      hHandleCI [in]:
*      eAccMode [in]:模式选择，见枚举定义E_CI_IOAcessMode
*
*Return Values
*       0 : SUCCESS 成功
*       -1: FAILURE 失败
**************************************************************************/
ADI_Error_Code ADICIConfigAccessMode(E_CI_IOAcessMode eAccMode, ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICITSEnableCntrl
*    经过模块的TS使能配置
*
*Parameters	
*      hHandleCI [in]:
*      bTSInCntrl [in]:流入模块的TS使能配置
*      bTSOutCntrl [in]:流出模块的TS使能配置
*
*Return Values
*       0 : SUCCESS 成功
*       -1: FAILURE 失败
**************************************************************************/
ADI_Error_Code ADICITSEnableCntrl(ADI_HANDLE hHandleCI, ADI_BOOL bTSInCntrl,ADI_BOOL bTSOutCntrl );

ADI_BOOL ADICICheckDataAvailable(ADI_HANDLE hHandleCI);

ADI_Error_Code ADICIGetDeviceBufferSize(ADI_HANDLE hHandleCI, unsigned short *pusDevBufferSize);

#ifdef  __cplusplus
}
#endif

#endif

