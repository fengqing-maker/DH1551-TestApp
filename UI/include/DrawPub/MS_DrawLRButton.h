/*
*  MS_DrawLRButton.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#ifndef _MS_DRAWLRBUTTON_H
#define _MS_DRAWLRBUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MS_DrawPublic.h"

typedef void(*MSDrawLRBArrowProc)(LPMSNMCUSTOMDRAW pMSNMLVCUSTOMDRAW);

BOOL 	MSLRButtonInit( HMSWND hWnd, DWORD dwLRButtonId, int nMinNum, int nMaxNum, int nPos );

int 	MSLRButtonGetPos(HMSWND hWnd, DWORD dwLRButtonId);

int 	MSLRButtonGetRangeMin(HMSWND hWnd, DWORD dwLRButtonId);

int 	MSLRButtonGetRangeMax(HMSWND hWnd, DWORD dwLRButtonId);

BOOL  	MSLRButtonSetPos(HMSWND hWnd, DWORD dwLRButtonId,int nPos);

LRESULT MSDrawLRButtonProcWithChar( LPARAM lParam, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, char* pMStr, int nLen, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, MSDrawLRBArrowProc pDrawLRBArrowProc);

LRESULT MSDrawLRButtonProc( LPARAM lParam, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID,  DWORD dwStrID, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, MSDrawLRBArrowProc pDrawLRBArrowProc);


LRESULT MSDrawLRButtonProcWithCharLMR(LPARAM lParam, DWORD dwFocusedBndBmpLeftID, DWORD dwFocusedBndBmpMiddleID,
        DWORD dwFocusedBndBmpRightID, DWORD dwNoFocusedBndBmpLeftID, DWORD dwNoFocusedBndBmpMiddleID,
        DWORD dwNoFocusedBndBmpRightID, char* pMStr, int nLen, DWORD dwFocusedTextColor, 
        DWORD dwNoFocusedTextColor,  HMSFONT hFont, int nTextPosToLeft, MSDrawLRBArrowProc pDrawLRBArrowProc);
 
LRESULT MSDrawLRButtonProcLMR(LPARAM lParam, DWORD dwFocusedBndBmpLeftID, DWORD dwFocusedBndBmpMiddleID,
	 DWORD dwFocusedBndBmpRightID, DWORD dwNoFocusedBndBmpLeftID, DWORD dwNoFocusedBndBmpMiddleID, DWORD dwNoFocusedBndBmpRightID, 
	 DWORD dwStrID, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor,  HMSFONT hFont, int nTextPosToLeft, MSDrawLRBArrowProc pDrawLRBArrowProc);

 
#ifdef __cplusplus
}
#endif

#endif
