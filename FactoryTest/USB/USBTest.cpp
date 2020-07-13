/*
 * PlayServiceTest.cpp
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#include "APAssert.h"
#include "USBTest.h"
#include "adi_fs.h"
#include "string.h"
#include "FactoryTestInit.h"

static void USBDviceCallBack(ADIFSEvent_E eType, int nDeviceId, const void * pvEventData, void * pvUserData);

USBTest::USBTest(USBNotify* pNotify) : m_pNotify(pNotify)
{
	m_unCheckStatus = NONE_USB;
}

USBTest::~USBTest()
{
	ADIFSRemoveCallback(USBDviceCallBack, this);
}

void USBTest::Init(USBConfig csUSBConfig)
{
	memcpy(&m_USBConfig, &csUSBConfig, sizeof(USBConfig));
	
	ADIFSAddCallback(USBDviceCallBack, this);
}

unsigned int USBTest::Start()
{
	unsigned int unRet = 0;
	int anDevCnt[8] = { 0 };
	int nActualCnt = 0;

	if (ADI_SUCCESS == ADIFSGetAllDeviceId(anDevCnt, 8, &nActualCnt))
	{
		if(nActualCnt > 0)
		{
			for (int ii = 0; ii < nActualCnt; ii++)
			{
				ADIFSDeviceInfo_S stDevInfo = { 0 };
				if (ADI_SUCCESS == ADIFSGetDeviceInfo((unsigned int)anDevCnt[ii], &stDevInfo))
				{
					if(stDevInfo.m_eDeviceType == EM_ADIFS_DEVTYPE_VOLUME && IsCheckUSBSuccess(stDevInfo.m_nMountPort))
					{
						m_pNotify->USBReady((unsigned int)anDevCnt[ii], &stDevInfo);
						unRet = 1;
						break;
					}
				}
			}
		}
		if( unRet != 1 )
		{
			m_pNotify->NoUSBNotify(m_unCheckStatus);
		}
	}
	else
	{		
		m_pNotify->NoUSBNotify(m_unCheckStatus);
	}
	printf("-[%s][%d]-nActualUSBCount:%d---\n", __FUNCTION__, __LINE__, nActualCnt);
	
	return unRet;
}

unsigned int USBTest::Stop()
{
	unsigned int unRet = 1;

	return unRet;
}

void USBTest::USBMediaReady(unsigned int unDevice, ADIFSDeviceInfo_S* psDeviceInfo)
{
	if(IsCheckUSBSuccess(psDeviceInfo->m_nMountPort))
	{
		m_pNotify->USBReady(unDevice, psDeviceInfo);
	}
	else if( m_USBConfig.m_nCount > 1  && m_unCheckStatus > 0 )
	{
		FactoryTestInterface *pFactoryTestInterface = GetFactoryTestInterface();
		if(pFactoryTestInterface != NULL)
		{
			TestResult_S stTestResult = {0};
			if(pFactoryTestInterface->GetTestResult(&stTestResult))
			{
				if(stTestResult.nUSBResult != 1)
				{
					Start();
				}
			}
		}
	}
}

void USBTest::USBMediaPlugOut(unsigned int unDevice)
{
	m_pNotify->USBPlugOut(unDevice);

	m_unCheckStatus = NONE_USB;
}

BOOL USBTest::IsCheckUSBSuccess(unsigned int unDeviceID)
{
	BOOL bSuccess = FALSE;

	unDeviceID = unDeviceID % 2;
	
	m_unCheckStatus |= (unDeviceID + 1);
	
	if( m_USBConfig.m_nCount > 1)
	{
		if( (m_unCheckStatus & DOUBLE_USB) == DOUBLE_USB )
		{
			bSuccess = TRUE;
		}
	}
	else if( m_USBConfig.m_nCount == 1 && m_unCheckStatus != NONE_USB )
	{
		bSuccess = TRUE;
	}

	return bSuccess;
}

static void USBDviceCallBack(ADIFSEvent_E eType, int nDeviceId, const void * pvEventData, void * pvUserData)
{
	APAssert(pvUserData != NULL);

	USBTest *pUSBTest = (USBTest*)pvUserData;

	if (pUSBTest != NULL)
	{
		if (eType == EM_ADIFS_EVENT_READY)
		{
			ADIFSDeviceInfo_S stDevInfo = { 0 };
			if (ADI_SUCCESS == ADIFSGetDeviceInfo((unsigned int)nDeviceId, &stDevInfo))
			{
				if(stDevInfo.m_eDeviceType == EM_ADIFS_DEVTYPE_VOLUME)
				{
					pUSBTest->USBMediaReady((unsigned int)nDeviceId, &stDevInfo);
				}
			}
		}
		else if (eType == EM_ADIFS_EVENT_PLUGOUT)
		{
			pUSBTest->USBMediaPlugOut((unsigned int)nDeviceId);
		}
		else if(eType == EM_ADIFS_EVENT_ERROR || eType == EM_ADIFS_EVENT_DEVICE_NO_PARTITION)
		{
			ADIFSDeviceInfo_S stDevInfo = { 0 };
			stDevInfo.m_nMountPort = 0;
			pUSBTest->USBMediaReady((unsigned int)nDeviceId, &stDevInfo);
			printf("--[%s][%d]--eType:%d---\n", __FUNCTION__, __LINE__, eType);
		}
	}
}

