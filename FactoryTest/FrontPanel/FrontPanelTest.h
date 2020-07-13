/*
 * FrontPanelTest.h
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#ifndef FRONTPANELTEST_H_
#define FRONTPANELTEST_H_
#include "FrontPanelNotify.h"
#include "APEvent.h"
#include "APSafeThread.h"
#include "FPConfig.h"


class FrontPanelTest : public APSafeThread
{
public:
	FrontPanelTest(FrontPanelNotify* pNotify);
	virtual ~FrontPanelTest();

public:
	void Init(FPConfig csFPConfig);
	unsigned int InputKey(unsigned int unKey);
	unsigned int Start();
	unsigned int Stop();
	void SetLedStatus(unsigned int unStatus);
	
private:
	void OnceProcess ( );
	void AllLEDAndDisplayOn(unsigned int unOn);
	
	void MailLedOn ( );
	void MailLedOff ( );

	void StandbyLedOn ( );
	void StandbyLedOff ( );

	void SingalLedOn ( );
	void SingalLedOff ( );

	void RadioLedOn ( );
	void RadioLedOff ( );

	void AudioLedOn ( );
	void AudioLedOff ( );

	void RedLedOn();
	void RedLedOff();
	void GreenLedOn();
	void GreenLedOff();
	
	void PannelDisplay ( unsigned char aucData [ ], unsigned int unDataLen );

private:

	FrontPanelNotify* m_pFrontPanelNotify;

	APEvent m_APAllKeyPressedEvent;

	unsigned int m_aunKeyTested[MAX_FRONTPANEL_KEY_COUNT];
	unsigned int m_unKeyTestFinished;

	FPConfig m_FPConfig;

	unsigned int m_unLedStatus;
};

#endif /* FRONTPANELTEST_H_ */
