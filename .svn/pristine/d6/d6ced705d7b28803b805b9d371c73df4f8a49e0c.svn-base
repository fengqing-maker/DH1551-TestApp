#include "RequestPSISITable.h"
#include <string.h>
#include "adi_section.h"
#include "adi_os.h"
#include <stdio.h>

#define REQUEST_PAT_TIMEOUT (10*1000)

RequestPSISITable::RequestPSISITable(unsigned int unPID, unsigned int unTunerID, RequestTableNotify *pRequestTableNotify):
APSafeThread(5 * 17, 16 * 1024, "RequestPSISITable", strlen("RequestPSISITable")),
m_unPID(unPID), m_unTunerID(unTunerID),m_pRequestTableNotify(pRequestTableNotify)
{
	m_hFilterHandle = NULL;

	m_hFilterSignal = NULL;
	
	ADIFILTERAllocateSignal(&m_hFilterSignal);

	SectionReceive(m_unPID, 4 * 1024);

	m_unLockStatus = 0;

	memset(&m_curLockDelivery, 0, sizeof(m_curLockDelivery));

	StartRun();
}

RequestPSISITable::~RequestPSISITable()
{
	Exit();

	if(m_hFilterHandle != NULL)
	{
		ADIFILTERStop(m_hFilterHandle);
		ADIFILTERFree(m_hFilterHandle);
	}
}

void RequestPSISITable::OnceProcess()
{
	m_APLock.Lock();
	
	if(m_unLockStatus > 0)
	{
		ListenSectionData(m_hFilterSignal);
	}

	m_APLock.UnLock();

	ADIOSThreadSleep(1000);
}

unsigned int RequestPSISITable::StartLock(ADITunerSRCDeliver_U* pDelivery)
{
	unsigned int unRe = 0;

	m_APLock.Lock();

	if(memcmp(&m_curLockDelivery, pDelivery, sizeof(m_curLockDelivery)) != 0)
	{
		if(ADITunerConnect(m_unTunerID, pDelivery) == 0)
		{
			memcpy(&m_curLockDelivery, pDelivery, sizeof(m_curLockDelivery));
			
			m_unLockStatus = 0;
			
			unRe = 1;
		}
		else
		{
			m_pRequestTableNotify->LockDeliveryErrorNotify(m_unTunerID);
		}
	}
	else
	{
		unRe = 1;
	}

	m_APLock.UnLock();

	return unRe;
}

unsigned int RequestPSISITable::SectionReceive(unsigned int nPid, unsigned int unBufSize)
{
	ADI_BOOL bRet = ADI_FALSE;
    ADI_Error_Code eErrCode = ADI_FAILURE;
    ADISECTIONRequestInfo_S   sRequestInfo;
	ADIFILTERMatchMask_S sMMFilter;
	
	char u8Mask[16] =  {0xff ,0x0 ,0x0, 0xff ,0xff  ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00};
	char u8Match[16] = {0x00 ,0x0 ,0x0 ,0x60 ,0x00 , 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00};		
	char u8NMask[16] = {0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00};

    sRequestInfo.m_nPID             = nPid;
    sRequestInfo.m_bCRCCheck        = ADI_FALSE;
    sRequestInfo.m_eReqType         = EM_ADI_REQ_SECTION_DATA;
    sRequestInfo.m_nDemuxID         = m_unTunerID;
	sRequestInfo.m_unBufSize = unBufSize;
	sRequestInfo.m_hSignal = m_hFilterSignal;

    memcpy(sMMFilter.mask, u8Mask, 16);
    memcpy(sMMFilter.match, u8Match, 16);
	memcpy(sMMFilter.negate, u8NMask, 16);

	do
	{
	    eErrCode = ADIFILTERAllocate(&sRequestInfo, NULL, &m_hFilterHandle);
	    if (eErrCode != ADI_SUCCESS)
	    {
	        printf("Error (%d) failed to execute ADIFILTERAllocate()!!!\n", eErrCode);
	        break;
	    }

		eErrCode = ADIFILTERSet(m_hFilterHandle,&sMMFilter);
		if (eErrCode != ADI_SUCCESS)
	    {
	        printf("Error (%d) failed to execute ADIFILTERSet()!!!\n", eErrCode);
	        break;
	    }

		printf("Swayer Pat handle=0x%x\n", (unsigned int)m_hFilterHandle);
	   	ADIFILTERStart(m_hFilterHandle);
	   	bRet = ADI_TRUE;
	}while(0);

    if( bRet == ADI_FALSE )
	{
	    if ( m_hFilterHandle )
	    {
	        ADIFILTERFree(m_hFilterHandle);
	        m_hFilterHandle = NULL;
	    }
	}

    return bRet;
}

unsigned int RequestPSISITable::ListenSectionData(ADI_HANDLE hFilterSignal)
{
	unsigned int unRe = 0;
	ADI_Error_Code errCode = ADI_FAILURE;
	ADIFILTERData_S stFilterData[1];
	unsigned int nFilterDataCnt = 1;
	unsigned char pucSection[4096];
	unsigned int unSectionLen = 4096;
	unsigned int unTimeout = 0;

	stFilterData[0].m_pucSection = pucSection;
	stFilterData[0].m_unSectionLen = unSectionLen;
	
	do
	{
		errCode = ADIFILTERWaitDataArrived(hFilterSignal, 1000);
		if(errCode == ADI_SUCCESS)
		{
			errCode = ADIFILTERReadData(hFilterSignal, stFilterData, 1, &nFilterDataCnt);

			if ( errCode == ADI_SUCCESS )
			{
				printf("hFilterSignal =%d SectionTest nFilterDataCnt=%d\n", (unsigned int)hFilterSignal, nFilterDataCnt);

				if ( nFilterDataCnt > 0 && stFilterData[0].m_unSectActualLen > 0 && stFilterData[0].m_pucSection[0] == 0x0 )
				{
					unsigned short usTSPid = (unsigned short)((stFilterData[0].m_pucSection[3] << 8) | stFilterData[0].m_pucSection[4]);
					if ( usTSPid == 0x6000 )
					{				
						unRe = 1;
						m_unLockStatus = 0;
						m_pRequestTableNotify->RequestTableSuccessNotify(m_unTunerID);						
						printf("==========>>>Get PAT=============>usTSPid:0x%x\n", usTSPid);						
						break;
					}
				}
			}
			else
			{
				printf("ADIFILTERReadData Error !!\n");
			}
		}

		unTimeout += 1000;
	}while(unTimeout < REQUEST_PAT_TIMEOUT && m_unLockStatus > 0);

	if(unRe == 0 && m_unLockStatus > 0)
	{
		m_pRequestTableNotify->RequestTableTimeoutNotify(m_unTunerID);
	}

	return unRe;
}

unsigned int RequestPSISITable::StopListen(void)
{
	m_unLockStatus = 0;
	
	m_APLock.Lock();
	if ( m_hFilterHandle != NULL )
	{
		ADIFILTERStop(m_hFilterHandle);
	}
	m_APLock.UnLock();

	return 1;
}

unsigned int RequestPSISITable::StartFilter(void)
{
	unsigned int unRe = 0;

	m_APLock.Lock();	
	if(m_hFilterHandle != NULL)
	{
		if(ADIFILTERStart(m_hFilterHandle) == ADI_SUCCESS)
		{
			m_unLockStatus = 1;		
			unRe = 1;
		}
	}
	m_APLock.UnLock();

	return unRe;
}
