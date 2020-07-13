#pragma once

#include "Aura.h"


#ifdef  __cplusplus
extern "C" {
#endif

int AuraApp( HMSINSTANCE hInstance, HMSINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow );
HMSINSTANCE GetInstance ( );
HMSWND GetDVBMainWnd(void);

HMSWND GetSearchWnd(void);

HMSWND GetChannelBarWnd(void);

HMSWND GetUsbBrowserDialogWnd(void);

BOOL ShowVolumeBar(HMSWND hWnd);

HMSWND GetPVRRecordDialogWnd(void);

HMSWND GetPVRPlayerHwnd(void);

HMSWND GetTimeShiftPlayerWnd(void);


#ifdef  __cplusplus
}
#endif
