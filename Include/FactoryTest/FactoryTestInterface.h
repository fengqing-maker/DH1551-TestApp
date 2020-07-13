/*
 * FactoryTestInterface.h
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#ifndef FACTORYTESTINTERFACE_H_
#define FACTORYTESTINTERFACE_H_
#include "adi_tuner.h"
#include "FactoryTestNotify.h"
#include "FactoryTestParamSet.h"

typedef struct
{
	int nAVResult; // 0: not test; 1: passed; -1:failed
	int nUSBResult; // 0: not test; 1: passed; -1:failed; 2:No USB
	int nEthernetResult; //1: passed; 0:failed; 
	int nSMCResult; // 0: not test; 1: passed; -1:failed; 2:No SmartCard
	int nFPResult; // 0: not test; 1: passed; -1:failed
	int nSNResult; // 0: not test; 1: passed; -1:failed
	int nOTAResult; // 0: not test; 1: passed; -1:failed
	int nReadOTA; // 0: not ready; 1: ready
}TestResult_S;

class FactoryTestInterface
{
public:
	FactoryTestInterface();
	virtual ~FactoryTestInterface();

public:
	virtual unsigned int GetFlashStatus(void) = 0;
	virtual void SetFactoryConfig(FactoryTestParamSet csFactoryTestParamSet) = 0;
	virtual int GetHLFlag() = 0;
	virtual void PrintLog(void) = 0;
	virtual int SetTestAppViewTitle(char *pcStr, int nLen) = 0;
	virtual int SetAVTestDeliveryInfo(char *pcStr, int nLen) = 0;
	virtual void SetLedStatus(unsigned int unStatus) = 0;
	
	virtual unsigned int StartPlayService() = 0;
	virtual unsigned int SwitchService() = 0;
	virtual unsigned int StopPlay() = 0;
	virtual unsigned int SetMaxVolume() = 0;
	virtual unsigned int SetMute() = 0;
	virtual unsigned int ShowVideo() = 0;
	virtual unsigned int HideVideo() = 0;
	virtual unsigned int StartPlayLowFrequencyService() = 0;
	virtual unsigned int StartPlayMidFrequencyService() = 0;
	virtual unsigned int StartPlayHighFrequencyService() = 0;

	virtual unsigned int StartFrontPanelTest() = 0;
	virtual unsigned int StopFrontPanelTest() = 0;
	virtual unsigned int FrontPanelInputKey(unsigned int unKey) = 0;

	virtual unsigned int StartSmartCardTest() = 0;
	virtual unsigned int StopSmartCardTest() = 0;

	virtual unsigned int StartUSBTest() = 0;
	virtual unsigned int StopUSBTest() = 0;
	
	virtual unsigned int StartEthernetTest() = 0 ;
	virtual unsigned int StopEthernetTest() = 0 ;
	virtual unsigned int GetIPName(char *pcIP, int nLen) = 0;
	virtual unsigned int GetMacName(unsigned char *pucMacAddress, unsigned int unLen) = 0;

	virtual unsigned int TriggerOTA() = 0;

	virtual unsigned int StartAssembleTest() = 0;

	virtual unsigned int RegisterNotify(FactoryTestNotify* pNotify) = 0;

	virtual unsigned int GetTestResult(TestResult_S * pTestResult) = 0;
	
	virtual void SetSNUpgradeStatus(unsigned int unFinish) = 0;

	virtual unsigned int SaveTestResult() = 0;

	virtual unsigned int IsReadyToOTA() = 0;

	virtual void SetOTAStatus(int nProc) = 0;
	
	virtual unsigned int CheckChipID() = 0;

	virtual unsigned int SetOTAFlag() = 0;

	virtual unsigned int ClearResultExceptSN() = 0;

	virtual unsigned int IsReadForUSBUpgrade()=0;

};

#endif /* FACTORYTESTINTERFACE_H_ */


