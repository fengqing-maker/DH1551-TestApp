/*
 * SmartCardTest.h
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#ifndef SMARTCARDTEST_H_
#define SMARTCARDTEST_H_
#include "SmartCardNotify.h"
#include "adi_smc.h"
#include "SMCConfig.h"

class SmartCardTest
{
public:
	SmartCardTest(unsigned int unIndex, ADISMCProtocol_E eProtocol, SmartCardNotify* pNotify);
	virtual ~SmartCardTest();

public:
	void Init(SMCConfig csSMCConfig);

	unsigned int Start();
	unsigned int Stop();
	
	unsigned int CardIn(unsigned int unIndex);
	unsigned int CardOut(unsigned int unIndex);

private:

	unsigned int ResetCard(unsigned int unIndex);
	unsigned int CardConfig(unsigned int unIndex, ADISMCProtocol_E eProtocol);

private:

	unsigned int m_unSmartCardIndex;
	unsigned int m_unSmartCardStatus;

	ADISMCProtocol_E m_eSmcProtocol;

	SmartCardNotify* m_pSmartCardNotify;

	SMCConfig m_SMCConfig;
};

#endif /* SMARTCARDTEST_H_ */
