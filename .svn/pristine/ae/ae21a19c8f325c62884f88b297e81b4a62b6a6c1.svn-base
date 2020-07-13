/*
*  MS_DrawProgress.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#ifndef _MS_DRAWPROGRESS_H_
#define _MS_DRAWPROGRESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

BOOL    MSProgressInit(HMSWND hWnd, DWORD dwCtrlID, int nMini, int nMax, int nCurrentPos);

BOOL    MSProgressSetPos(HMSWND hWnd, DWORD dwCtrlID, int nPos);

BOOL    MSProgressSetStep(HMSWND hWnd, DWORD dwCtrlID, int nStep);

LRESULT MSProgressDrawProcByBitmapHandle( LPARAM lParam, HMSBITMAP hbmpBackgroudLeft, HMSBITMAP hbmpBackgroudMiddle, HMSBITMAP hbmpBackgroudRight, HMSBITMAP hbmpForegroundLeft, HMSBITMAP hbmpForegroundMiddle, HMSBITMAP hbmpForegroundRight );

LRESULT MSDrawProgressProcByPNG(LPARAM lParam, DWORD dwBackgroudLeftBmpID, DWORD dwBackgroudMiddleBmpID, DWORD dwBackgroudRightBmpID, DWORD dwForegroundLeftBmpID, DWORD dwForegroundMiddleBmpID, DWORD dwForegroundRightBmpID);

int		MSProgressGetPercent(HMSWND hWnd, DWORD dwCtrlID, char* pszPercentStr, int nBufSize);
int MSProgressGetPos(HMSWND hWnd, DWORD dwCtrlID);
					

#ifdef __cplusplus
}
#endif

#endif
