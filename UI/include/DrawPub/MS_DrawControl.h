/*
*  MS_DrawControl.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#ifndef _MS_DRAWCONTROL_H_
#define _MS_DRAWCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

BOOL MSSetDlgItemTextByIDS(HMSWND hWnd, DWORD dwCtrlID, DWORD dwStrID);

BOOL MSSetWindowTextByIDS(HMSWND hWnd, DWORD dwStrID);

BOOL MSSetDlgItemTextByChar(HMSWND hWnd, DWORD dwCtrlID, const char* pStr, int nCount);

BOOL MSSetWindowTextByChar(HMSWND hWnd, const char* pStr, int nCount);

BOOL MSDrawDlgItemTextEx(HMSWND hWnd, int nIDDlgItem, DWORD dwStrID);

#ifdef __cplusplus
}
#endif

#endif
