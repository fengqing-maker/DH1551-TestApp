
#include "Aura.h"
#include "MsUserMessagedefine.h"
#include "OTANotify.h"

extern HMSWND GetTestAppWnd(void);

OTANotify::OTANotify()
{

}

OTANotify::~OTANotify()
{

}

void OTANotify::OTAStart(int nResult)
{
	MSPostMessage(GetTestAppWnd(), MSG_OTA_START, nResult, 0);
}

void OTANotify::StartWriteCore(int nResult)
{
	MSPostMessage(GetTestAppWnd(), MSG_OTA_WRITE_CORE, nResult, 0);
}

void OTANotify::StartWriteRC(int nResult)
{
	MSPostMessage(GetTestAppWnd(), MSG_OTA_WRITE_RC, nResult, 0);
}

void OTANotify::StartWriteApp(int nResult)
{
	MSPostMessage(GetTestAppWnd(), MSG_OTA_WRITE_APP, nResult, 0);
}

void OTANotify::StartOpenHL(int nResult)
{
	MSPostMessage(GetTestAppWnd(), MSG_OTA_OPEN_HL, nResult, 0);
}

