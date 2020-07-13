/*
 * PlayServiceTest.h
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#ifndef PLAYSERVICETEST_H_
#define PLAYSERVICETEST_H_
#include "ServicePlayNotify.h"
#include "adi_tuner.h"
#include "adi_player.h"
#include "AuraTypedef.h"
#include "AVConfig.h"
#include "RequestTableNotify.h"
#include "RequestPSISITable.h"
#include "RequestVideoAndAudioFrame.h"
#include "APSafeThread.h"
#include "APLock.h"

typedef enum
{
	TUNER1_DELEVERY1_OK=0x1,
	TUNER1_DELEVERY2_OK=0x2,
	TUNER2_DELEVERY1_OK=0x4,
	TUNER2_DELEVERY2_OK=0x8
};

class PlayServiceTest : public RequestTableNotify, public APSafeThread
{
public:
	PlayServiceTest(ServicePlayNotify* pNotify);
	virtual ~PlayServiceTest();

public:
	void OnceProcess();
	void Init(AVConfig csAVConfig);
	unsigned int Start();
	unsigned int Stop();
	unsigned int SetVolume(int nVolume);
	unsigned int Mute();
	unsigned int Unmute();
	unsigned int ShowVideo();
	unsigned int HideVideo();
	
	void RequestTableSuccessNotify(unsigned int unTunerID);
	void RequestTableTimeoutNotify(unsigned int unTunerID);
	void LockDeliveryErrorNotify(unsigned int unTunerID);

	unsigned int StartFirstDelivery(void);
	unsigned int StartSecondDelivery(void);
	unsigned int SetServicePos(void);
	unsigned int LockDelivery(ADITunerSRCDeliver_U *pADITunerSRCDeliver, unsigned int unDeliveryIndex);
	void ResetLockStatus(void);

private:
	void PrintActTunerCount(void);

private:
	unsigned int m_unDeliveryIndex;
	unsigned int m_unLockStatus;
	unsigned int m_unErrorStatus;
	unsigned int m_ServicePos;
	ServicePlayNotify* m_pNotify;
	AVConfig m_AVConfig;
	RequestPSISITable *m_pRequestPSISITable;
	RequestVideoAndAudioFrame m_RequestVideoAndAudioFrame;
	APLock m_APLock;
};

#endif /* PLAYSERVICETEST_H_ */
