/*
 * TestAppSupport.cpp
 *
 *  Created on: 2015-6-22
 *      Author: gongjinjun
 */

#include "TestAppSupport.h"
#include "FactoryTestInit.h"

unsigned int GetFlashStatus(void)
{
	return GetFactoryTestInterface()->GetFlashStatus();
}

unsigned int TestAppStartPlay()
{
	return GetFactoryTestInterface()->StartPlayService();
}

unsigned int TestAppSwitchService()
{
	return GetFactoryTestInterface()->SwitchService();
}

unsigned int TestAppPlayLowFrequencyService()
{
	return GetFactoryTestInterface()->StartPlayLowFrequencyService();
}

unsigned int TestAppPlayMidFrequencyService()
{
	return GetFactoryTestInterface()->StartPlayMidFrequencyService();
}

unsigned int TestAppPlayHighFrequencyService()
{
	return GetFactoryTestInterface()->StartPlayHighFrequencyService();
}

unsigned int TestAppStopPlay()
{
	return GetFactoryTestInterface()->StopPlay();
}

unsigned int TestAppSetMaxVolume()
{
	return GetFactoryTestInterface()->SetMaxVolume();
}

unsigned int TestAppSetMute()
{
	return GetFactoryTestInterface()->SetMute();
}

unsigned int TestAppHideVideo()
{
	return GetFactoryTestInterface()->HideVideo();
}

unsigned int TestAppShowVideo()
{
	return GetFactoryTestInterface()->ShowVideo();
}

unsigned int TestAppStartFrontPanelTest()
{
	return GetFactoryTestInterface()->StartFrontPanelTest();
}

unsigned int TestAppStopFrontPanelTest()
{
	return GetFactoryTestInterface()->StopFrontPanelTest();
}

unsigned int TestAppFrontPanelInputKey(unsigned int unKey)
{
	return GetFactoryTestInterface()->FrontPanelInputKey(unKey);
}

unsigned int TestAppStartSmartCardTest()
{
	return GetFactoryTestInterface()->StartSmartCardTest();
}

unsigned int TestAppStopSmartCardTest()
{
	return GetFactoryTestInterface()->StopSmartCardTest();
}

unsigned int TestAppStartUSBTest()
{
	return GetFactoryTestInterface()->StartUSBTest();
}

unsigned int TestAppStartEthernetTest()
{
    return GetFactoryTestInterface()->StartEthernetTest(); 
}

unsigned int TestAppStopUSBTest()
{
	return GetFactoryTestInterface()->StopUSBTest();
}

unsigned int TestAppTriggerOTA()
{
	return GetFactoryTestInterface()->TriggerOTA();
}

unsigned int TestAppStartAssembleTest()
{
	return GetFactoryTestInterface()->StartAssembleTest();
}

unsigned int GetTestResult(TestResult_S * pTestResult)
{
	return GetFactoryTestInterface()->GetTestResult(pTestResult);
}

unsigned int SaveTestResult()
{
	return GetFactoryTestInterface()->SaveTestResult();
}

int GetHLFlag()
{
	return GetFactoryTestInterface()->GetHLFlag();
}

unsigned int TestAppStartOTA()
{
	return GetFactoryTestInterface()->IsReadyToOTA();
}

void PrintLog(void)
{
	GetFactoryTestInterface()->PrintLog();
}

unsigned int GetIPName(char *pcIP, int nLen)
{
	return GetFactoryTestInterface()->GetIPName( pcIP, nLen );
}

unsigned int GetMacName(unsigned char *pucMacAddress, unsigned int unLen)
{
	return GetFactoryTestInterface()->GetMacName( pucMacAddress, unLen );
}

int SetTestAppViewTitle(char *pcStr, int nLen)
{
	return GetFactoryTestInterface()->SetTestAppViewTitle(pcStr, nLen);
}

int SetAVTestDeliveryInfo(char *pcStr, int nLen)
{
	return GetFactoryTestInterface()->SetAVTestDeliveryInfo(pcStr, nLen);
}

int SetOTAFlag()
{
	return GetFactoryTestInterface()->SetOTAFlag();
}

int ClearResultExceptSN()
{
	return GetFactoryTestInterface()->ClearResultExceptSN();
}

unsigned int IsReadForUSBUpgrade()
{
	return GetFactoryTestInterface()->IsReadForUSBUpgrade();
}

