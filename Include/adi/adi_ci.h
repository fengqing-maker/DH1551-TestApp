
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
*    ��ģ���ж�ȡ����
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    ���ݳ���
*     pcData[out];   ��ȡ���ݵ�Buffer 

*
*Return Values
*       0 : SUCCESS ��ȡ���ݳɹ�
*       -1: FAILURE ����������ȡ����ʧ��
**************************************************************************/
ADI_Error_Code ADICIReadData(ADI_HANDLE hHandleCI, int* pnLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICIWrite
*    ��ģ���ж�д������
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    ���ݳ���
*     pcData[in];   Ҫд�������

*
*Return Values
*       0 : SUCCESS д�����ݳɹ�
*       -1: FAILURE ���������д������ʧ��
**************************************************************************/
ADI_Error_Code ADICIWriteData(ADI_HANDLE hHandleCI, int nLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICICISRead
*    ��ģ�������ڴ��ж�ȡCIS ����
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    ���ݳ���
*     pcData[out];   ��ȡ���ݵ�Buffer 

*
*Return Values
*       0 : SUCCESS ��ȡ���ݳɹ�
*       -1: FAILURE ����������ȡ����ʧ��
**************************************************************************/
ADI_Error_Code ADICICISReadData(ADI_HANDLE hHandleCI, int nLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICICISWrite
*    ��ģ�������ڴ��ж�д������
*
*Parameters	
*     hHandleCI [in]:
*     nLen[in];    ���ݳ���
*     pcData[in];   Ҫд�������
*
*Return Values
*       0 : SUCCESS д�����ݳɹ�
*       -1: FAILURE ���������д������ʧ��
**************************************************************************/
ADI_Error_Code ADICICISWriteData(ADI_HANDLE hHandleCI, unsigned long dwOffset, int nLen, unsigned char *pcData);


/**************************************************************************
*Function Name: ADICIRegRead
*    ��ȡģ��Ĵ���������
*
*Parameters	
*     hHandleCI [in]:
*     eReg[in];    �Ĵ���
*
		�Ĵ�������:
*	CI_MODULE_CONTROL,
*	CI_MODULE_STATUS,
*	CI_MODULE_SIZE_L,
*	CI_MODULE_SIZE_H
*
*    	pcByte[out];   �Ĵ�����ֵ
*
*Return Values
*       0 : SUCCESS ��ȡ���ݳɹ�
*       -1: FAILURE ����������ȡ����ʧ��
**************************************************************************/
ADI_Error_Code ADICIRegRead(ADI_HANDLE hHandleCI, E_CI_Register eReg, unsigned char *pcByte);


/**************************************************************************
*Function Name: ADICIRegWrite
*    ��ģ��Ĵ�����д������
*
*Parameters	
*     hHandleCI [in]:
*     eReg[in];    �Ĵ���
*
		�Ĵ�������:
*	CI_MODULE_CONTROL,
*	CI_MODULE_STATUS,
*	CI_MODULE_SIZE_L,
*	CI_MODULE_SIZE_H
*     pcByte[in];   �Ĵ�����ֵ
*
*Return Values
*       0 : SUCCESS д�����ݳɹ�
*       -1: FAILURE ���������д������ʧ��
**************************************************************************/
ADI_Error_Code ADICIRegWrite(ADI_HANDLE hHandleCI, E_CI_Register eReg, unsigned char *pcByte);


/**************************************************************************
*Function Name: ADICICardDetect
*    ����Ƿ���ģ�����
*
*Parameters	
*      hHandleCI [in]:
*
*Return Values
*       1 : TRUE ��⵽CAM ��
*       0: FALSE û�м�⵽CAM ��
**************************************************************************/
ADI_BOOL ADICICamDetected(ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICIPowerOn
*    ��ģ���ϵ�
*
*Parameters	
*      hHandleCI [in]:
*
*Return Values
*       0 : SUCCESS �ɹ�
*       -1: FAILURE ʧ��
**************************************************************************/
ADI_Error_Code ADICIPowerOnOff(ADI_HANDLE hHandleCI, ADI_BOOL bPowerOnOff);




/**************************************************************************
*Function Name: ADICIModuleReset
*    ��ģ����и�λ
*
*Parameters	
*      hHandleCI [in]:
*
*Return Values
*       0 : SUCCESS �ɹ�
*       -1: FAILURE ʧ��
**************************************************************************/
ADI_Error_Code ADICIModuleReset(ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICITSFlowConnect
*    ѡ��TS �������ĸ�ģ��
*
*Parameters	
*      hTuner [in]:
*      hHandleCI [in]:
*	   hCpuChnl [in]:
*
*Return Values
*       0 : SUCCESS �ɹ�
*       -1: FAILURE ʧ��
**************************************************************************/
//int ADICITunerSlotConnect(ADI_HANDLE hHandleCI, ADI_HANDLE hTuner);
ADI_Error_Code ADICITSFlowConnect(ADI_HANDLE hHandleCI, ADI_HANDLE hTuner,ADI_HANDLE hCpuChnl);


/**************************************************************************
*Function Name: ADICITSSelect
*    ѡ����һ·��������оƬ
*
*Parameters	
*      hHandleCI [in]:
*      hCpuChannel [in]:CPU ͨ����
*
*Return Values
*       0 : SUCCESS �ɹ�
*       -1: FAILURE ʧ��
**************************************************************************/
ADI_Error_Code ADICITSSelect(ADI_HANDLE hHandleCI, ADI_HANDLE hCpuChnl);


/**************************************************************************
*Function Name: ADICIConfigAccessMode
*    ѡ��I/O��дģʽ
*
*Parameters	
*      hHandleCI [in]:
*      eAccMode [in]:ģʽѡ�񣬼�ö�ٶ���E_CI_IOAcessMode
*
*Return Values
*       0 : SUCCESS �ɹ�
*       -1: FAILURE ʧ��
**************************************************************************/
ADI_Error_Code ADICIConfigAccessMode(E_CI_IOAcessMode eAccMode, ADI_HANDLE hHandleCI);


/**************************************************************************
*Function Name: ADICITSEnableCntrl
*    ����ģ���TSʹ������
*
*Parameters	
*      hHandleCI [in]:
*      bTSInCntrl [in]:����ģ���TSʹ������
*      bTSOutCntrl [in]:����ģ���TSʹ������
*
*Return Values
*       0 : SUCCESS �ɹ�
*       -1: FAILURE ʧ��
**************************************************************************/
ADI_Error_Code ADICITSEnableCntrl(ADI_HANDLE hHandleCI, ADI_BOOL bTSInCntrl,ADI_BOOL bTSOutCntrl );

ADI_BOOL ADICICheckDataAvailable(ADI_HANDLE hHandleCI);

ADI_Error_Code ADICIGetDeviceBufferSize(ADI_HANDLE hHandleCI, unsigned short *pusDevBufferSize);

#ifdef  __cplusplus
}
#endif

#endif

