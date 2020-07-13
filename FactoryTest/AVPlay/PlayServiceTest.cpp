/*
 * PlayServiceTest.cpp
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#include "APAssert.h"
#include "PlayServiceTest.h"
#include "adi_error.h"
#include "adi_audio.h"
#include "adi_video.h"
#include "string.h"
#include "AuraWindows.h"
#include "adi_os.h"
#include "adi_section.h"

extern HMSWND GetTestAppWnd(void);

PlayServiceTest::PlayServiceTest(ServicePlayNotify* pNotify) : 
APSafeThread( 5 * 17, 1024 * 4, "PlayServiceTest", strlen("PlayServiceTest")),
m_pNotify(pNotify),m_RequestVideoAndAudioFrame(0, this)
{
	memset(&m_AVConfig, 0, sizeof(AVConfig));

	m_pRequestPSISITable = NULL;

	PrintActTunerCount();

	m_unDeliveryIndex = 0;

	m_unLockStatus = 0;

	m_unErrorStatus = 0;

	m_ServicePos = 1;

	StartRun();
}

PlayServiceTest::~PlayServiceTest()
{
	Exit();
	
	if (m_pRequestPSISITable != NULL)
	{
		delete m_pRequestPSISITable;
	}
}

void PlayServiceTest::OnceProcess()
{
	m_APLock.Lock();
	printf("m_unLockStatus %d, m_unErrorStatus %d\n",m_unLockStatus, m_unErrorStatus);
	if((m_unLockStatus & TUNER1_DELEVERY1_OK) && (m_unLockStatus & TUNER2_DELEVERY1_OK))
	{
		if(GetTestAppWnd() != NULL)
		{
		#if 0
			if (m_unDeliveryIndex == 1 && m_AVConfig.m_nTunerCount > 1)
			{
				m_RequestVideoAndAudioFrame.Stop();

				if(m_pRequestPSISITable != NULL)
				{
					m_pRequestPSISITable->StopListen();
				}

				LockDelivery(m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0], 2);
			}
			else
			{
				if (/*(m_unLockStatus & TUNER1_DELEVERY2_OK) && */(m_unLockStatus & TUNER2_DELEVERY2_OK))
				{
					m_pNotify->ServicePlaySuccessNotify();

					ResetLockStatus();
				}
			}	
		#endif
			m_pNotify->ServicePlaySuccessNotify();
	
			ResetLockStatus();
		}
	}
	
	m_APLock.UnLock();

	ADIOSThreadSleep(1000);
}

void PlayServiceTest::ResetLockStatus(void)
{
	m_unLockStatus = 0;
	
	if(m_AVConfig.m_nTunerCount == 1)
	{
		m_unLockStatus |= (TUNER2_DELEVERY1_OK | TUNER2_DELEVERY2_OK | TUNER1_DELEVERY2_OK);
	}
	else
	{
		if (m_AVConfig.m_vTuner_List[0]->m_nTunerType == m_AVConfig.m_vTuner_List[1]->m_nTunerType)
		{
			m_unLockStatus |= TUNER2_DELEVERY2_OK | TUNER1_DELEVERY2_OK;
		}
	}
}

void PlayServiceTest::Init(AVConfig csAVConfig)
{
	//memcpy(&m_AVConfig, &csAVConfig, sizeof(AVConfig));
	m_AVConfig.m_nTunerCount = csAVConfig.m_nTunerCount;
	for(int i = 0; i<csAVConfig.m_vTuner_List.size(); i++)
	{
		m_AVConfig.m_vTuner_List.push_back(csAVConfig.m_vTuner_List[i]);
	}
	for(int i = 0;i<csAVConfig.m_vServiceList.size(); i++)
	{
		m_AVConfig.m_vServiceList.push_back(csAVConfig.m_vServiceList[i]);
	}

	m_RequestVideoAndAudioFrame.SetAVConfig(&csAVConfig);

	if (m_AVConfig.m_nTunerCount > 1 )
	{
		m_pRequestPSISITable = new RequestPSISITable(0, 1, this);

		APAssert(m_pRequestPSISITable != NULL);
	}

	ResetLockStatus();
}

void PlayServiceTest::PrintActTunerCount(void)
{
    int unActIDCnt = 0;
    unsigned int aunTunerID [ 4 ] = { 0 };
    
    ADITunerGetAllDeviceId ( aunTunerID, sizeof ( aunTunerID ) / sizeof ( unsigned int ), &unActIDCnt );

	printf("=[%s][%d]==ActTunerCount=%d,id:%d=\n", __FUNCTION__, __LINE__, unActIDCnt, aunTunerID[0]);
}

unsigned int PlayServiceTest::Start()
{
	unsigned int unRet = 1;

	m_APLock.Lock();

	if(m_unDeliveryIndex > 1)
	{
		m_RequestVideoAndAudioFrame.Stop();

		if(m_pRequestPSISITable != NULL)
		{
			m_pRequestPSISITable->StopListen();
		}
	}

	if (m_unDeliveryIndex != 1 || m_AVConfig.m_nTunerCount == 1)
	{
		unRet = LockDelivery(m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0], 1);
	}

	if(m_unDeliveryIndex == 1)
	{
		unRet = LockDelivery(m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0], 1);
	}

	m_APLock.UnLock();
	
	return unRet;
}

unsigned int PlayServiceTest::StartFirstDelivery(void)
{
	unsigned int unRet = 1;

	m_APLock.Lock();

	if (m_unDeliveryIndex != 1)
	{
		unRet = LockDelivery(m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[0], 1);
	}

	m_APLock.UnLock();
	
	return unRet;
}

unsigned int PlayServiceTest::StartSecondDelivery(void)
{
	unsigned int unRet = 1;

	m_APLock.Lock();

	if(m_unDeliveryIndex != 2 && m_AVConfig.m_vTuner_List[0]->m_nDeliveryCount > 1)
	{
		m_RequestVideoAndAudioFrame.Stop();

		if(m_pRequestPSISITable != NULL)
		{
			m_pRequestPSISITable->StopListen();
		}

		unRet = LockDelivery(m_AVConfig.m_vTuner_List[0]->m_vDeliveryList[1], 2);
	}

	m_APLock.UnLock();
	
	return unRet;
}

unsigned int PlayServiceTest::SetServicePos()
{
	unsigned int unRet = 1;
	if (GetTestAppWnd() != NULL && m_ServicePos < m_AVConfig.m_vServiceList.size())
	{
		m_ServicePos = m_ServicePos % (m_AVConfig.m_vServiceList.size() - 1) + 1;
	}
	unRet &= m_RequestVideoAndAudioFrame.StartPlayer(m_AVConfig.m_vServiceList[m_ServicePos]);
	return unRet;
}

unsigned int PlayServiceTest::LockDelivery(ADITunerSRCDeliver_U *pADITunerSRCDeliver, unsigned int unDeliveryIndex)
{
	unsigned int unRet = 0;

	unRet = m_RequestVideoAndAudioFrame.StartLock(pADITunerSRCDeliver);

	if (m_AVConfig.m_nTunerCount > 1 )
	{
		if (m_AVConfig.m_vTuner_List[0]->m_nTunerType == m_AVConfig.m_vTuner_List[1]->m_nTunerType)
		{
			unRet &= m_pRequestPSISITable->StartLock(pADITunerSRCDeliver);
		}
		else
		{
			unRet &= m_pRequestPSISITable->StartLock(m_AVConfig.m_vTuner_List[1]->m_vDeliveryList[0]);
		}
	}
    
	ADIOSThreadSleep(2000);
	
    ADITunerSignalInfo_S stAdiTunerInfo = { 0 };

    ADITunerGetSignalInfo ( 0, EM_ADITUNER_SIGNAL_QUALITY | EM_ADITUNER_SIGNAL_CN | EM_ADITUNER_SIGNAL_STRENGTH, &stAdiTunerInfo );
    
	printf("=[%s][%d]==m_unDeliveryIndex=%d, m_nStrength=%d, m_nQuality=%d\n", __FUNCTION__, __LINE__, unDeliveryIndex, stAdiTunerInfo.m_nStrength, stAdiTunerInfo.m_nQuality);
	
	ADITunerGetSignalInfo( 1, EM_ADITUNER_SIGNAL_QUALITY | EM_ADITUNER_SIGNAL_CN | EM_ADITUNER_SIGNAL_STRENGTH, &stAdiTunerInfo);

	printf("=[%s][%d]==m_unDeliveryIndex=%d, m_nStrength=%d, m_nQuality=%d\n", __FUNCTION__, __LINE__, unDeliveryIndex, stAdiTunerInfo.m_nStrength, stAdiTunerInfo.m_nQuality);
#if 0
	if (GetTestAppWnd() != NULL && m_ServicePos < m_AVConfig.m_vServiceList.size())
	{
		unRet &= m_RequestVideoAndAudioFrame.StartPlayer(m_AVConfig.m_vServiceList[m_ServicePos]);
	}
	else
	{
		unRet &= m_RequestVideoAndAudioFrame.StartPlayer(m_AVConfig.m_vServiceList[0]);
	}
#endif 
	if (GetTestAppWnd() != NULL)
	{
		unRet &= m_RequestVideoAndAudioFrame.StartPlayer(m_AVConfig.m_vServiceList[1]);
	}
	else
	{
		unRet &= m_RequestVideoAndAudioFrame.StartPlayer(m_AVConfig.m_vServiceList[0]);
	}
	
	if (m_AVConfig.m_nTunerCount > 1 )
	{
		unRet &= m_pRequestPSISITable->StartFilter();
	}

	m_unDeliveryIndex = unDeliveryIndex;
	
	return unRet;
}

unsigned int PlayServiceTest::Stop()
{
	return m_RequestVideoAndAudioFrame.Stop();
}

unsigned int PlayServiceTest::SetVolume(int nVolume)
{
	return ADIAUDIOSetVolume(0, nVolume);
}

unsigned int PlayServiceTest::Mute()
{
	return ADIAUDIOMute(0);
}

unsigned int PlayServiceTest::Unmute()
{
	return ADIAUDIOUnmute(0);
}

unsigned int PlayServiceTest::ShowVideo()
{
	unsigned int unRet = 0;

	if (ADIVIDEOShow(0, 1) == ADI_SUCCESS)
	{
		unRet = 1;
	}

	return unRet;
}

unsigned int PlayServiceTest::HideVideo()
{
	unsigned int unRet = 0;

	if (ADIVIDEOShow(0, 0) == ADI_SUCCESS)
	{
		unRet = 1;
	}

	return unRet;
}

void PlayServiceTest::RequestTableSuccessNotify(unsigned int unTunerID)
{
	if(m_unDeliveryIndex == 1)
	{
		if(unTunerID == 0)
		{
			m_unLockStatus |= TUNER1_DELEVERY1_OK;
		}
		else if(unTunerID == 1)
		{
			m_unLockStatus |= TUNER2_DELEVERY1_OK;
		}
	}
	else if (m_unDeliveryIndex == 2)
	{
		if(unTunerID == 0)
		{
			m_unLockStatus |= TUNER1_DELEVERY2_OK;
		}
		else if(unTunerID == 1)
		{
			m_unLockStatus |= TUNER2_DELEVERY2_OK;
		}
	}

	m_unErrorStatus = 0;

	printf("[%s][%d]  m_unLockStatus=0x%x, unTunerID=0x%x\n", __FUNCTION__, __LINE__, m_unLockStatus, unTunerID);
}

void PlayServiceTest::RequestTableTimeoutNotify(unsigned int unTunerID)
{
	//if((m_unErrorStatus & (unTunerID + m_unDeliveryIndex * 4)) != (unTunerID + m_unDeliveryIndex * 4))
	{
		m_unErrorStatus |= unTunerID + m_unDeliveryIndex * 4;

		m_pNotify->ServicePlayTimeoutNotify(unTunerID + m_unDeliveryIndex * 4);
		
		printf("RequestTableTimeoutNotify %d\n", unTunerID);
	}
}

void PlayServiceTest::LockDeliveryErrorNotify(unsigned int unTunerID)
{
	//if((m_unErrorStatus & (unTunerID + m_unDeliveryIndex * 16)) != (unTunerID + m_unDeliveryIndex * 16))
	{
		m_unErrorStatus = unTunerID + m_unDeliveryIndex * 16;

		m_pNotify->ServicePlayLockErrorNotify(m_unErrorStatus);
		
		printf("LockDeliveryErrorNotify %d\n", unTunerID);
	}
}