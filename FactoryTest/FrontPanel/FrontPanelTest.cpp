/*
 * PlayServiceTest.cpp
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#include "string.h"
#include "FactoryTestInit.h"
#include "APAssert.h"
#include "FrontPanelTest.h"
#include "adi_os.h"
#include "adi_panel.h"

FrontPanelTest::FrontPanelTest(FrontPanelNotify* pNotify) :
m_pFrontPanelNotify(pNotify), APSafeThread(3*17+1, 16*1024, "FrontPanel", strlen("FrontPanel"))
{
	APAssert(pNotify != NULL);

	memset(m_aunKeyTested, 0, sizeof(unsigned int)*MAX_FRONTPANEL_KEY_COUNT);
	m_unKeyTestFinished = 0;

	m_unLedStatus = 0;
	
	StartRun();
}

FrontPanelTest::~FrontPanelTest()
{
	Exit();
}

void FrontPanelTest::SetLedStatus(unsigned int unStatus)
{
	m_unLedStatus = unStatus;
}

void FrontPanelTest::Init(FPConfig csFPConfig)
{
	memcpy(&m_FPConfig, &csFPConfig, sizeof(FPConfig));
	
	printf("-[%s][%d]-----m_FPConfig.m_unKeyCount:%d-\n", __FUNCTION__, __LINE__, m_FPConfig.m_unKeyCount);
}

unsigned int FrontPanelTest::Start()
{
	unsigned int unLEDOn = 1;
	unsigned int unSuccess = 0;
	unsigned int ii;

	memset(m_aunKeyTested, 0, sizeof(unsigned int)*MAX_FRONTPANEL_KEY_COUNT);

	AllLEDAndDisplayOn(unLEDOn);

	m_APAllKeyPressedEvent.ResetEvent();
	while (m_APAllKeyPressedEvent.Wait(1000) != 1)
	{
		unLEDOn = unLEDOn == 1 ? 0 : 1;
		AllLEDAndDisplayOn(unLEDOn);
	}

	for (ii = 0; ii < m_FPConfig.m_unKeyCount; ii++)
	{
		if (m_aunKeyTested[ii] != 1)
		{
			break;
		}
	}
	if (m_FPConfig.m_unKeyCount == ii)
	{
		AllLEDAndDisplayOn(0);

		unSuccess = 1;
	}

	m_pFrontPanelNotify->FrontPanelTestFinish(unSuccess);

	return unSuccess;
}

unsigned int FrontPanelTest::Stop()
{
	m_APAllKeyPressedEvent.SetEvent();

	return 1;
}

unsigned int FrontPanelTest::InputKey(unsigned int unKey)
{
	unsigned int unRet = 0;

	unsigned int ii;
	
	for (ii = 0; ii < m_FPConfig.m_unKeyCount; ii++)
	{
		if (m_FPConfig.m_aunKeyList[ii] == unKey)
		{
			m_aunKeyTested[ii] = 1;
			unRet = 1;
			break;
		}
	}

	
	for (ii = 0; ii < m_FPConfig.m_unKeyCount; ii++)
	{
		if (m_aunKeyTested[ii] != 1)
		{
			break;
		}
	}
	
	if (m_FPConfig.m_unKeyCount == ii)
	{
		m_pFrontPanelNotify->FrontPanelTestFinish(1);
		m_unKeyTestFinished = 1;
	}

	return unRet;
}

void FrontPanelTest::OnceProcess ( )
{
	static unsigned int unLEDOn = 1;
	
	if(m_unKeyTestFinished > 0)
	{
		char* pDisplayStr = "PASS";
		PannelDisplay((unsigned char*)pDisplayStr, 4);
		ADIOSThreadSleep(5000);
		m_unKeyTestFinished = 0;
		memset(m_aunKeyTested, 0, sizeof(unsigned int)*MAX_FRONTPANEL_KEY_COUNT);
		
	}
	else
	{
		AllLEDAndDisplayOn(unLEDOn);

		if(m_unLedStatus == 1)
		{
			unLEDOn = 0;
		}
		else
		{
			FactoryTestInterface *pFactoryTestInterface = GetFactoryTestInterface();
			if(pFactoryTestInterface != NULL && pFactoryTestInterface->IsReadyToOTA() > 0)
			{
				unLEDOn = 1;
			}
			else
			{
				unLEDOn = unLEDOn == 1 ? 0 : 1;
			}
		}
	}

	ADIOSThreadSleep(1000);
}

void FrontPanelTest::AllLEDAndDisplayOn(unsigned int unOn)
{
	if (unOn == 1)
	{
		MailLedOn();
		RadioLedOn();
		AudioLedOn();
		StandbyLedOn();
		SingalLedOn();
		GreenLedOff();
		RedLedOn();

		char* pDisplayStr = "8888";
		PannelDisplay((unsigned char*)pDisplayStr, 4);
	}
	else
	{
		MailLedOff();
		RadioLedOff();
		AudioLedOff();
		StandbyLedOff();
		SingalLedOff();
		RedLedOff();
		GreenLedOn();

		char* pDisplayStr = "    ";
		PannelDisplay((unsigned char*)pDisplayStr, 4);
	}
}

void FrontPanelTest::MailLedOn ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_MAIL;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::MailLedOff ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_MAIL;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::StandbyLedOn ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_POWER;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::StandbyLedOff ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_POWER;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::SingalLedOn ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_SIGNAL;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::SingalLedOff ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_SIGNAL;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::RadioLedOn ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_RADIO;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}
void FrontPanelTest::RadioLedOff ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_RADIO;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::AudioLedOn ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_AUDIO;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}
void FrontPanelTest::AudioLedOff ( )
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;

    tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_AUDIO;
    tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;

    ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

void FrontPanelTest::RedLedOn()
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;
    
	tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_RED;
	tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;
	
	ADIPanelDisplay(0,&tempADIPanelLightValule_S);
}

void FrontPanelTest::RedLedOff()
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;
    
	tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_RED;
	tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;
	
	ADIPanelDisplay(0,&tempADIPanelLightValule_S);
}

void FrontPanelTest::GreenLedOn()
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;
    
	tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_GREEN;
	tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_ON;
	
	ADIPanelDisplay(0,&tempADIPanelLightValule_S);
}

void FrontPanelTest::GreenLedOff()
{
    ADIPanelLightValule_S tempADIPanelLightValule_S;
    
	tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_GREEN;
	tempADIPanelLightValule_S.m_uValue.m_sCtrlValue.m_eCtrlValue = EM_ADIPANEL_CTRL_OFF;
	
	ADIPanelDisplay(0,&tempADIPanelLightValule_S);
}

void FrontPanelTest::PannelDisplay ( unsigned char aucData [ ], unsigned int unDataLen )
{
	ADIPanelLightValule_S tempADIPanelLightValule_S;

	memset ( &tempADIPanelLightValule_S, 0, sizeof( ADIPanelLightValule_S ) );

	tempADIPanelLightValule_S.m_eLightName = EM_ADIPANEL_TEXT0;
	tempADIPanelLightValule_S.m_uValue.m_sTextValue.m_eDisplayType = EM_ADIPANEL_TEXT_STRING;

	tempADIPanelLightValule_S.m_uValue.m_sTextValue.m_nStrCount = ( unDataLen < sizeof( tempADIPanelLightValule_S.m_uValue.m_sTextValue.m_szStr ) ? unDataLen : sizeof( tempADIPanelLightValule_S.m_uValue.m_sTextValue.m_szStr ) );
	memcpy ( ( void * ) ( tempADIPanelLightValule_S.m_uValue.m_sTextValue.m_szStr ), aucData, tempADIPanelLightValule_S.m_uValue.m_sTextValue.m_nStrCount );
	
	ADIPanelDisplay ( 0, &tempADIPanelLightValule_S );
}

