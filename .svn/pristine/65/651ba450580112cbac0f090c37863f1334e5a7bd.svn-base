/*
 * SNNotify.cpp
 *
 *  Created on: 2015-8-17
 *      Author: linc
 */

#include "SNNotify.h"
#include "stdio.h"
#include "Aura.h"
#include "MsUserMessagedefine.h"


extern HMSWND GetTestAppWnd(void);

SNNotify::SNNotify()
{

}

SNNotify::~SNNotify()
{

}

void SNNotify::UpgradeStarted()
{
	MSPostMessage(GetTestAppWnd(), MSG_UPGRADE_START, 0, 0);
}

void SNNotify::UpgradeSuccess()
{
	MSPostMessage(GetTestAppWnd(), MSG_UPGRADE_SUCCESS, 0, 0);
}

void SNNotify::UpgradeFail()
{
	MSPostMessage(GetTestAppWnd(), MSG_UPGRADE_FAIL, 0, 0);
}

void SNNotify::UpgradeTimeOut()
{
	MSPostMessage(GetTestAppWnd(), MSG_UPGRADE_TIMEOUT, 0, 0);
}

void SNNotify::UpgradeEraseSuccess()
{
	MSPostMessage(GetTestAppWnd(), MSG_UPGRADE_ERASE, 0, 0);
}


