/*
 * TestAppNotify.cpp
 *
 *  Created on: 2015-7-15
 *      Author: gongjinjun
 */

#include "TestAppNotify.h"
#include "Aura.h"
#include "AuraWindows.h"
//#include "AuraViewDialog.h"
#include "MsUserMessagedefine.h"


extern HMSWND GetTestAppWnd(void);

TestAppNotify::TestAppNotify()
{

}
 
TestAppNotify ::~TestAppNotify()
{

}

void TestAppNotify::LivePlayNotify(unsigned int unSuccess)
{
	if (GetTestAppWnd() != NULL)
	{
		MSPostMessage(GetTestAppWnd(), MSG_TESTAPP_PLAY, unSuccess, 0);
	}
}

void TestAppNotify::FrontPanelTestNotify(unsigned int unSuccess)
{

	if (GetTestAppWnd() != NULL)
	{
		MSPostMessage(GetTestAppWnd(), MSG_TESTAPP_FRONTPANEL, unSuccess, 0);
	}
}

void TestAppNotify::SmartCardTestNotify(unsigned int unSuccess)
{
	if (GetTestAppWnd() != NULL)
	{
		MSPostMessage(GetTestAppWnd(), MSG_TESTAPP_SMARTCARD, unSuccess, 0);
	}
}

void TestAppNotify::USBTestNotify(unsigned int unSuccess)
{
	if (GetTestAppWnd() != NULL)
	{
		MSPostMessage(GetTestAppWnd(), MSG_TESTAPP_USB, unSuccess, 0);
	}
}

void TestAppNotify::EthernetTestNotify(unsigned int unSuccess)
{
  if (GetTestAppWnd() != NULL)
	{
		MSPostMessage(GetTestAppWnd(), MSG_TESTAPP_ETHERNET, unSuccess, 0);
	}
}
