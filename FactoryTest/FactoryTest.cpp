/*
 * FactoryTest.cpp
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#include "APAssert.h"
#include "FactoryTest.h"
#include "adi_flash.h"
#include "string.h"
#include "UIViewInfo.h"
#include "TestAppVersion.h"
#include "STBDataInterface.h"
#include "stdio.h"

#define TEST_ITEM_ASSEMBLE			(0x100)

#define TEST_ITEM_PLAYSERVICE		(1)
#define TEST_ITEM_STOPSERVICE		(2)
#define TEST_ITEM_STARTFRONTPANEL	(3)
#define TEST_ITEM_STARTCARD			(4)
#define TEST_ITEM_STARTUSB			(5)
#define TEST_ITEM_STARTETHERNET 	(6)
#define TEST_ITEM_SWITCHSERVICE		(7)

FactoryTest::FactoryTest(ADISMCProtocol_E eProtocol, UpgradeNotify * pNotify) :
m_APMessageQ("FactoryTest", 1, sizeof(unsigned int)* 2, 0), APSafeThread(5 * 17 + 1, 64 * 1024, "FactoryTest", strlen("FactoryTest")),
m_pFactoryTestNotify(NULL), m_PlayServiceTest(this), m_FrontPanelTest(this),
m_SmartCardTest(0, eProtocol, this), m_EthernetTest(this) ,m_USBTest(this), m_SerialUpgrade(pNotify)
{
	memset(&m_stTestResult, 0, sizeof(TestResult_S));

	memset(&m_BaseTestItem, 0, sizeof(m_BaseTestItem));

	m_unFlashStatus = 0;

	StartRun();
}

FactoryTest::~FactoryTest()
{
	Exit();
}

unsigned int FactoryTest::GetFlashStatus(void)
{
	return m_unFlashStatus;
}

void FactoryTest::SetFactoryConfig(FactoryTestParamSet csFactoryTestParamSet)
{
	csFactoryTestParamSet.GetBaseConfig(&m_BaseTestItem);

	m_unFlashStatus = 1;
	
	LoadTestResult();

	if(m_BaseTestItem.m_nAV == 1)
	{
		csFactoryTestParamSet.GetAVConfig(&m_AVConfig);
		m_PlayServiceTest.Init(m_AVConfig);
	}
	else
	{
		m_stTestResult.nAVResult = 1;
	}
	
	if(m_BaseTestItem.m_nUSB == 1)
	{
		csFactoryTestParamSet.GetUSBConfig(&m_USBConfig);
		m_USBTest.Init(m_USBConfig);
	}
	else
	{
		m_stTestResult.nUSBResult = 1;
	}
	
	if(m_BaseTestItem.m_nNet == 1)
	{
		csFactoryTestParamSet.GetNETConfig(&m_NetConfig);
		m_EthernetTest.Init(m_NetConfig);
	}
	else
	{
		m_stTestResult.nEthernetResult = 1;
	}
	
	if(m_BaseTestItem.m_nSMC == 1)
	{
		csFactoryTestParamSet.GetSMCConfig(&m_SMCConfig);
		m_SmartCardTest.Init(m_SMCConfig);
	}
	else
	{
		m_stTestResult.nSMCResult = 1;
	}
	
	if(m_BaseTestItem.m_nFP == 1)
	{
		csFactoryTestParamSet.GetFPConfig(&m_FPConfig);
		m_FrontPanelTest.Init(m_FPConfig);
	}
	else
	{
		m_stTestResult.nFPResult = 1;
	}
	
	if(m_BaseTestItem.m_nSN == 1)
	{
		csFactoryTestParamSet.GetSNConfig(&m_SNConfig);
		m_SerialUpgrade.Init(m_SNConfig);
	}
	else
	{
		m_stTestResult.nSNResult = 1;
	}

	if(m_BaseTestItem.m_nOTA == 1)
	{
		csFactoryTestParamSet.GetOTAConfig(&m_OTAConfig);
		
		m_pOTASupport = GetOTASupport();
		
		m_pOTASupport->Init(m_OTAConfig);

		m_pOTASupport->SetOptAndMarketID();
	}
	else
	{
		m_stTestResult.nOTAResult = 1;
	}

	SaveTestResult();

	SetTestItem(m_BaseTestItem);
}

int FactoryTest::GetHLFlag()
{
	return m_OTAConfig.m_unHLType;
}

void FactoryTest::PrintLog(void)
{
	m_SerialUpgrade.PrintAllLogInfo();
}

unsigned int FactoryTest::StartPlayService()
{
	unsigned int aunMsg[2];
	unsigned int unRet = 0;

	//全部测完后OTA线程会去锁OTA频点并获取锁频状态
	//此处避免抢频点导致OTA想要获取的锁频状态不对
	if(IsReadyToOTA() == 0)
	{
		aunMsg[0] = TEST_ITEM_PLAYSERVICE;
		aunMsg[1] = 0;

		unRet = SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
	}

	return unRet;
}

unsigned int FactoryTest::SwitchService()
{
	unsigned int aunMsg[2];
	unsigned int unRet = 0;

	//全部测完后OTA线程会去锁OTA频点并获取锁频状态
	//此处避免抢频点导致OTA想要获取的锁频状态不对
	if (IsReadyToOTA() == 0)
	{
		aunMsg[0] = TEST_ITEM_SWITCHSERVICE;
		aunMsg[1] = 0;

		unRet = SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
	}

	return unRet;
}

unsigned int FactoryTest::StopPlay()
{
	unsigned int aunMsg[2];

	aunMsg[0] = TEST_ITEM_STOPSERVICE;
	aunMsg[1] = 0;

	return SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
}

unsigned int FactoryTest::StartPlayLowFrequencyService()
{
	unsigned int unRe = 0;

	if(IsReadyToOTA() == 0)
	{
		m_PlayServiceTest.Stop();
		
		unRe = m_PlayServiceTest.LockDelivery( m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0], 1 );
	}

	return unRe;
}

unsigned int FactoryTest::StartPlayMidFrequencyService()
{
	unsigned int unRe = 0;

	if(IsReadyToOTA() == 0)
	{
		m_PlayServiceTest.Stop();
		
		unRe = m_PlayServiceTest.LockDelivery( &m_OTAConfig.m_stOTADelivery, 3 );
	}

	return unRe;
}

unsigned int FactoryTest::StartPlayHighFrequencyService()
{
	unsigned int unRe = 0;

	if(IsReadyToOTA() == 0)
	{
		if(m_AVConfig.m_vTuner_List[0]->m_nDeliveryCount > 1)
		{
			m_PlayServiceTest.Stop();
		
			unRe = m_PlayServiceTest.LockDelivery(m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[1], 2);
		}
	}

	return unRe;
}

unsigned int FactoryTest::SetMaxVolume()
{
	m_PlayServiceTest.Unmute();
	m_PlayServiceTest.SetVolume(31);

	return 1;
}

unsigned int FactoryTest::SetMute()
{
	m_PlayServiceTest.Mute();

	return 1;
}

unsigned int FactoryTest::ShowVideo()
{
	m_PlayServiceTest.ShowVideo();

	return 1;
}

unsigned int FactoryTest::HideVideo()
{
	m_PlayServiceTest.HideVideo();

	return 1;
}

unsigned int FactoryTest::StartFrontPanelTest()
{
	unsigned int aunMsg[2];

	aunMsg[0] = TEST_ITEM_STARTFRONTPANEL;
	aunMsg[1] = 0;

	return SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
}

unsigned int FactoryTest::StopFrontPanelTest()
{
	return m_FrontPanelTest.Stop();
}

unsigned int FactoryTest::FrontPanelInputKey(unsigned int unKey)
{
	return m_FrontPanelTest.InputKey(unKey);
}

unsigned int FactoryTest::StartSmartCardTest()
{
	unsigned int aunMsg[2];

	aunMsg[0] = TEST_ITEM_STARTCARD;
	aunMsg[1] = 0;
    
	return SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
}

unsigned int FactoryTest::StopSmartCardTest()
{
	return m_SmartCardTest.Stop();
}

unsigned int FactoryTest::StartUSBTest()
{
	unsigned int aunMsg[2];

	aunMsg[0] = TEST_ITEM_STARTUSB;
	aunMsg[1] = 0;

	return SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
}

unsigned int FactoryTest::StopUSBTest()
{
	return m_USBTest.Stop();
}

unsigned int FactoryTest::StartEthernetTest()
{
	unsigned int aunMsg[2];

	aunMsg[0] = TEST_ITEM_STARTETHERNET;
	aunMsg[1] = 0;

	return SendFTMessage(aunMsg, sizeof(unsigned int)* 2, 100);
}

unsigned int FactoryTest::StopEthernetTest()
{
	return m_EthernetTest.Stop();
}

unsigned int FactoryTest::GetIPName(char *pcIP, int nLen)
{
	return m_EthernetTest.GetIPName( pcIP, nLen );
}

unsigned int FactoryTest::GetMacName(unsigned char *pucMacAddress, unsigned int unLen)
{
	return m_EthernetTest.GetMacName( pucMacAddress, unLen );
}

unsigned int FactoryTest::TriggerOTA()
{
	return 1;
}

unsigned int FactoryTest::GetTestResult(TestResult_S * pTestResult)
{
	unsigned int unRet = 0;

	m_ResultLock.Lock();
	
	if(pTestResult != NULL)
	{
		memcpy(pTestResult, &m_stTestResult, sizeof(TestResult_S));
		
		unRet = 1;
	}

	m_ResultLock.UnLock();

	return unRet;
}

void FactoryTest::SetSNUpgradeStatus(unsigned int unFinish)
{
	m_stTestResult.nSNResult = unFinish;
	
	SaveTestResult();
}

unsigned int FactoryTest::StartAssembleTest()
{
	unsigned int unRet = 1;

	unRet &= StartPlayService();

	SetMaxVolume();
	
	unRet &= StartUSBTest();
	
	unRet &= StartEthernetTest();

	unRet &= StartSmartCardTest();
	
	unRet &= StartFrontPanelTest();

	return unRet;
}

unsigned int FactoryTest::RegisterNotify(FactoryTestNotify* pNotify)
{
	unsigned int unRet = 0;

	if (pNotify != NULL)
	{
		m_pFactoryTestNotify = pNotify;
		unRet = 1;
	}

	return unRet;
}

void FactoryTest::ServicePlaySuccessNotify()
{
	m_stTestResult.nAVResult = 1;
	if (m_pFactoryTestNotify != NULL)
	{
		m_pFactoryTestNotify->LivePlayNotify(1);
	}
}

void FactoryTest::ServicePlayTimeoutNotify(unsigned int unStatus)
{
	if(m_stTestResult.nAVResult != 1)
	{
		if (m_pFactoryTestNotify != NULL)
		{
			m_stTestResult.nAVResult = unStatus;
			m_pFactoryTestNotify->LivePlayNotify(unStatus);
		}
	}
}

void FactoryTest::ServicePlayLockErrorNotify(unsigned int unStatus)
{
	if(m_stTestResult.nAVResult != 1)
	{
		if (m_pFactoryTestNotify != NULL)
		{
			m_stTestResult.nAVResult = unStatus;
			m_pFactoryTestNotify->LivePlayNotify(unStatus);
		}
	}
}

void FactoryTest::FrontPanelTestFinish(unsigned int unSuccess)
{
	m_stTestResult.nFPResult = 1;
	
	if (m_pFactoryTestNotify != NULL)
	{
		m_pFactoryTestNotify->FrontPanelTestNotify(unSuccess);
	}
}

void FactoryTest::SmartCardInNotify(unsigned int unIndex)
{
	/*m_PlayServiceTest.ShowVideo();
	m_PlayServiceTest.Unmute();
	m_PlayServiceTest.SetVolume(31);*/
}

void FactoryTest::SmartCardOutNotify(unsigned int unIndex)
{
	m_PlayServiceTest.HideVideo();
	m_PlayServiceTest.Mute();
}

void FactoryTest::SmartCardResetNotify(unsigned int unIndex, unsigned int unSuccess)
{
	if(unSuccess == 1)
	{
		m_PlayServiceTest.ShowVideo();
		m_PlayServiceTest.Unmute();
		m_PlayServiceTest.SetVolume(31);
	}

	if (m_pFactoryTestNotify != NULL)
	{
		m_stTestResult.nSMCResult = unSuccess;
		m_pFactoryTestNotify->SmartCardTestNotify(unSuccess);
	}
}

void FactoryTest::NoSmartCardNotify()
{
	if (m_pFactoryTestNotify != NULL)
	{
		m_stTestResult.nSMCResult = 2;
		m_pFactoryTestNotify->SmartCardTestNotify(2);
	}
}

void FactoryTest::USBReady(unsigned int unDeviceId, ADIFSDeviceInfo_S* psDeviceInfo)
{
	m_PlayServiceTest.ShowVideo();
	m_PlayServiceTest.Unmute();
	m_PlayServiceTest.SetVolume(31);

	if (m_pFactoryTestNotify != NULL)
	{
		m_stTestResult.nUSBResult = 1;
		m_pFactoryTestNotify->USBTestNotify(1);
	}
}

void FactoryTest::USBPlugOut(unsigned int unDeviceId)
{
	m_PlayServiceTest.HideVideo();
	m_PlayServiceTest.Mute();
}

void FactoryTest::NoUSBNotify(unsigned int unCheckStatus)
{
	m_stTestResult.nUSBResult = unCheckStatus+2;
	m_pFactoryTestNotify->USBTestNotify(unCheckStatus+2);
}

void FactoryTest::EthernetReadyNotify()
{
    m_stTestResult.nEthernetResult = 1;
    m_pFactoryTestNotify ->EthernetTestNotify(1);
}
void FactoryTest::EthernetNotReadyNotify()
{
    m_stTestResult.nEthernetResult = 2;
    m_pFactoryTestNotify ->EthernetTestNotify(2);
}


void FactoryTest::OnceProcess()
{
	unsigned int aunMsg[2];

	if (ReceiveFTMessage(aunMsg, sizeof(void*)* 2, 2000) == 1)
	{
		if(m_unFlashStatus ==0)
		{
			return;
		}
		
		switch (aunMsg[0])
		{
		case TEST_ITEM_PLAYSERVICE:
			//--test Stream: The_Hits_30Mins_Field.ts
			m_PlayServiceTest.Start();
			break;

		case TEST_ITEM_STOPSERVICE:
			m_PlayServiceTest.Stop();
			break;

		case TEST_ITEM_STARTFRONTPANEL:
			m_FrontPanelTest.Start();
			break;

		case TEST_ITEM_STARTCARD:
			m_SmartCardTest.Start();
			break;

		case TEST_ITEM_STARTUSB:
			m_USBTest.Start();
			break;
			
		case TEST_ITEM_STARTETHERNET:
			m_EthernetTest.Start();
			break;
		
		case TEST_ITEM_ASSEMBLE:
			break;

		case TEST_ITEM_SWITCHSERVICE:
			m_PlayServiceTest.SetServicePos();
			break;

		default:
			break;		
		}
	}
}

unsigned int FactoryTest::SendFTMessage(unsigned int aunMsg[], unsigned int unSize, unsigned int nTimeout)
{
	unsigned int unRet = 0;

	unsigned int aunTmp[2];

	while (m_APMessageQ.APReceiveMsgQueue(aunTmp, sizeof(unsigned int)* 2, 0) == 1);

	unRet = m_APMessageQ.APSendMsgQueue(aunMsg, unSize, nTimeout);

	return unRet;

}

unsigned int FactoryTest::ReceiveFTMessage(unsigned int aunMsg[], unsigned int unSize, unsigned int nTimeout)
{
	unsigned int unRet = 0;

	unRet = m_APMessageQ.APReceiveMsgQueue(aunMsg, unSize, nTimeout);
	
	return unRet;
}

unsigned int FactoryTest::LoadTestResult()
{
	unsigned int unRet = 0;
	unsigned char aucData[11+1] = {0};

	m_ResultLock.Lock();
	
	if (ADIFlashRead(m_BaseTestItem.m_unResultAddr, aucData, sizeof(aucData)) == ADI_SUCCESS)
	{
		if (aucData[0] == 0xaa && aucData[1] == 0x55 &&
			aucData[9+1] == 0x55 && aucData[10+1] == 0xaa)
		{
			m_stTestResult.nAVResult = aucData[2];
			m_stTestResult.nUSBResult = aucData[3];
			m_stTestResult.nSMCResult = aucData[4];
			m_stTestResult.nFPResult = aucData[5];
			m_stTestResult.nSNResult = aucData[6]; 
			m_stTestResult.nOTAResult = aucData[7];
			m_stTestResult.nEthernetResult = aucData[8];
			m_stTestResult.nReadOTA = aucData[9];
			unRet = 1;
		}
	}
	
	m_ResultLock.UnLock();

	return unRet;
}

unsigned int FactoryTest::SaveTestResult()
{
	unsigned int unRet = 0;

	m_ResultLock.Lock();

	unsigned char aucData[11+1] = {0};
	aucData[0] = 0xaa;
	aucData[1] = 0x55;
	aucData[2] = m_stTestResult.nAVResult;
	aucData[3] = m_stTestResult.nUSBResult;
	aucData[4] = m_stTestResult.nSMCResult;
	aucData[5] = m_stTestResult.nFPResult;
	aucData[6] = m_stTestResult.nSNResult; 
	aucData[7] = m_stTestResult.nOTAResult;
	aucData[8] = m_stTestResult.nEthernetResult;
	aucData[8+1] = m_stTestResult.nReadOTA;
	aucData[9+1] = 0x55; 
	aucData[10+1] = 0xaa;
	
	if (ADIFlashWrite(m_BaseTestItem.m_unResultAddr, aucData, sizeof(aucData)) == ADI_SUCCESS)
	{
		unRet = 1;
	}

	m_ResultLock.UnLock();
	
	return unRet;
}

unsigned int FactoryTest::SetOTAFlag()
{
	m_stTestResult.nReadOTA = 1;
	printf("SetOTAFlag OK\n");
	return 1;
}

unsigned int FactoryTest::ClearResultExceptSN()
{
	unsigned int unRet = 0;

	if(m_stTestResult.nSNResult == 0)
	{
		return 0;
	}

	m_ResultLock.Lock();

	unsigned char aucData[11+1] = {0};
	aucData[0] = 0xaa;
	aucData[1] = 0x55;
	aucData[2] = 0;//AV
	aucData[3] = 0;//USB
	aucData[4] = m_stTestResult.nSMCResult;//SMC
	aucData[5] = 0;//FP
	aucData[6] = m_stTestResult.nSNResult; 
	aucData[7] = m_stTestResult.nOTAResult;
	aucData[8] = m_stTestResult.nEthernetResult;
	aucData[8+1] = m_stTestResult.nReadOTA;
	aucData[9+1] = 0x55; 
	aucData[10+1] = 0xaa;
	
	if (ADIFlashWrite(m_BaseTestItem.m_unResultAddr, aucData, sizeof(aucData)) == ADI_SUCCESS)
	{
		unRet = 1;
	}
	printf("ADIFlashWrite ClearResultExceptSN %d\n", unRet);
	m_ResultLock.UnLock();

	ADISYSReboot();
	return unRet;
}

unsigned int FactoryTest::IsReadForUSBUpgrade()
{
	unsigned int unRet = 0;

	if(m_stTestResult.nAVResult == 1 && m_stTestResult.nUSBResult == 1 && m_stTestResult.nSMCResult == 1 &&
		m_stTestResult.nFPResult == 1 && m_stTestResult.nSNResult == 1 && m_stTestResult.nEthernetResult == 1 && 
		m_stTestResult.nReadOTA == 1 && m_stTestResult.nOTAResult >= 0x20)
	{
		unRet = 1;
	}
	return unRet;
}

unsigned int FactoryTest::IsReadyToOTA()
{
	unsigned int unRet = 0;
 
	if(m_stTestResult.nAVResult == 1 && m_stTestResult.nUSBResult == 1 && m_stTestResult.nSMCResult == 1 &&
		m_stTestResult.nFPResult == 1 && m_stTestResult.nSNResult == 1 && m_stTestResult.nEthernetResult == 1 && 
		m_stTestResult.nReadOTA == 1)
	{
		unRet = 1;
	}

	return unRet;
}

void FactoryTest::SetOTAStatus(int nProc)
{
	m_stTestResult.nOTAResult |= nProc;
	
	SaveTestResult();
}

unsigned int FactoryTest::CheckChipID()
{
	return m_SerialUpgrade.CheckChipID();
}

int FactoryTest::SetTestAppViewTitle(char *pcStr, int nLen)
{
	int nRet = 0;

	if(pcStr != NULL && nLen > 0)
	{
		char acVersion[32] = {0};
		
		if(GetTestAppVersion(acVersion , sizeof(acVersion)) == 1)
		{
			char acSTBType[32] = {0};
			if( IsExistCustomerCode() > 0 && GetSTBType(acSTBType, sizeof(acSTBType)))
			{
				sprintf(pcStr, "%s-%s%s", m_BaseTestItem.m_acProjectName, acVersion, acSTBType);
			}
			else
			{
				sprintf(pcStr, "%s-%s", m_BaseTestItem.m_acProjectName, acVersion);
			}
			
			nRet = 1;
		}
	}

	return nRet;
}

int FactoryTest::IsExistCustomerCode(void)
{
	int nRe = 0;

	if ( memcmp(m_BaseTestItem.m_acProjectName, "DT70", strlen("DT70")) == 0 )
	{
		nRe = 1;
	}
	else if ( memcmp(m_BaseTestItem.m_acProjectName, "FC70", strlen("FC70")) == 0 )
	{
		nRe = 1;
	}
	else if ( memcmp(m_BaseTestItem.m_acProjectName, "DT80", strlen("DT80")) == 0 )
	{
		nRe = 1;
	}

	return nRe;
}

unsigned int FactoryTest::GetSTBType(char *pBuffer, int nLen)
{
	int nRet = 0;
	unsigned char aucCustomerCodeBuf[32] = {0};
	unsigned char aucPVRFlagBuf[32] = {0};
	unsigned char aucFlag[32] = {0};
	
	if(ReadCustomerCode(aucCustomerCodeBuf, sizeof(aucCustomerCodeBuf)) == E_DATA_SUCCESS)
	{
		if(ReadPVRFlag(aucPVRFlagBuf, sizeof(aucPVRFlagBuf)) == E_DATA_SUCCESS)
		{
			nRet = 1;
		}
		else
		{
			memcpy(aucFlag, "Error", strlen("Error"));
		}
	}
	else
	{
		memcpy(aucCustomerCodeBuf, "Error", strlen("Error"));
	}

	if(nRet == 1)
	{
		if(memcmp(aucPVRFlagBuf, "ABCDEFGHAB", strlen("ABCDEFGHAB")) == 0)
		{
			memcpy(aucFlag, "HRT 8729", strlen("HRT 8729"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567812", strlen("1234567812")) == 0)
		{
			memcpy(aucFlag, "HRT 8730", strlen("HRT 8730"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567813", strlen("1234567813")) == 0)
		{
			memcpy(aucFlag, "HRT 8730 SCART", strlen("HRT 8730 SCART"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567814", strlen("1234567814")) == 0)
		{
			memcpy(aucFlag, "HRT 8730 KIT", strlen("HRT 8730 KIT"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567823", strlen("1234567823")) == 0)
		{
			memcpy(aucFlag, "HRT 8770 TWIN", strlen("HRT 8770 TWIN"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567824", strlen("1234567824")) == 0)
		{
			memcpy(aucFlag, "HRT 8772 TWIN", strlen("HRT 8772 TWIN"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567834", strlen("1234567834")) == 0)
		{
			memcpy(aucFlag, "HRT 8780 IP", strlen("HRT 8780 IP"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567825", strlen("1234567825")) == 0)
		{
			memcpy(aucFlag, "HRT 8772 HDD", strlen("HRT 8772 HDD"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567841", strlen("1234567841")) == 0)
		{
			memcpy(aucFlag, "HTL 1550", strlen("HTL 1550"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567842", strlen("1234567842")) == 0)
		{
			memcpy(aucFlag, "HTL 1550", strlen("HTL 1550"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567863", strlen("1234567863")) == 0)
		{
			memcpy(aucFlag, "HRK 7672 HDD", strlen("HRK 7672 HDD"));
		}
		else if(memcmp(aucPVRFlagBuf, "2234567802", strlen("2234567802")) == 0)
		{
			memcpy(aucFlag, "RBX2800", strlen("RBX2800"));
		}
		else if(memcmp(aucPVRFlagBuf, "2234567803", strlen("2234567803")) == 0)
		{
			memcpy(aucFlag, "ON-3001TZAP", strlen("ON-3001TZAP"));
		}
		else if(memcmp(aucPVRFlagBuf, "1234567867", strlen("1234567867")) == 0)
		{
			memcpy(aucFlag, "HRK 7622", strlen("HRK 7622"));
		}
		else
		{
			memcpy(aucFlag, "unKnow", strlen("unKnow"));
		}
	}

	if(pBuffer != NULL && nLen > 0)
	{
		sprintf(pBuffer, "(code:%s, pvr:%s)", aucCustomerCodeBuf, aucFlag);
	}

	return nRet;

}

int FactoryTest::SetAVTestDeliveryInfo(char *pcStr, int nLen)
{
	int nRet = 0;

	if(pcStr != NULL && nLen > 0)
	{
		unsigned int unFrequency = 0;
		
		if (m_AVConfig.m_vTuner_List[0]->m_nTunerType == DELIVERY_C)
		{
			unFrequency = m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0]->m_sCableDeliver.m_uFrequency;
			snprintf(pcStr, nLen, "Please Connect Signal:%d/6875/64QAM", unFrequency / 1000);
		}
		else if (m_AVConfig.m_vTuner_List[0]->m_nTunerType == DELIVERY_S)
		{
			unFrequency = m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0]->m_sSourceSatelliteDeliver.m_sLNB.m_uHighFrequency - m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0]->m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency;
			snprintf(pcStr, nLen, "Please Connect Signal:%d/27500/polar_h", unFrequency / 1000);
		}
		else if (m_AVConfig.m_vTuner_List[0]->m_nTunerType == DELIVERY_T)
		{
			unFrequency = m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0]->m_sTerrestrialDeliver.m_uFrequency;
			snprintf(pcStr, nLen, "Please Connect Signal:%d/8M/Tuner_T", unFrequency / 1000);
		}
		nRet = 1;
	}

	return nRet;
}

void FactoryTest::SetLedStatus(unsigned int unStatus)
{
	m_FrontPanelTest.SetLedStatus(unStatus);
}
