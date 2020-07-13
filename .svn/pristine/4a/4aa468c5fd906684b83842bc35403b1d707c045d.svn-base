/*
*  MS_DrawHMoveText.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aura.h"
#include "adi_os.h"
#include "AuraWindows.h"
#include "../AuraRC.h"
#include "../Resources.h"
#include "MS_DrawMoveText.h"

#define DRAWMOVETEXTCOUNT  10


static MsDrawMoveText_s sMsDrawHMoveText[DRAWMOVETEXTCOUNT] = { 0 };

static void CALLBACK MSDrawControlTimerProc(HMSWND hWnd, UINT uMsg, DWORD dwIdEvent, DWORD dwTime);

static BOOL MSDrawHMoveText(HMSWND hWnd, WPARAM wParam, LPMSRECT lprcText, char *pwTextInfo, DWORD dwCurMoveStep);

BOOL MSDrawHMoveTextInit(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent, WORD wMoveInterval)
{
	int i = 0;
	BOOL bRet = FALSE;

	if (hWnd == NULL || wParam == 0)
	{
		ADIASSERT(hWnd != NULL && wParam != 0 );
		return bRet;
	}

	for (i = 0; i < DRAWMOVETEXTCOUNT; i++)
	{
		if (sMsDrawHMoveText[i].m_bIsUse == FALSE)
		{
			break;
		}
	}

	if (i < DRAWMOVETEXTCOUNT)
	{
		memset(&sMsDrawHMoveText[i], 0, sizeof(MsDrawMoveText_s));

		sMsDrawHMoveText[i].m_hWnd			= hWnd;
		sMsDrawHMoveText[i].m_wParam		= wParam;
		sMsDrawHMoveText[i].m_hControlWnd	= MSGetDlgItem(hWnd, wParam);
		sMsDrawHMoveText[i].m_dwIdEvent		= dwIdEvent;
		sMsDrawHMoveText[i].m_wMoveInterval = wMoveInterval;
		sMsDrawHMoveText[i].m_dwMoveStep	= 0;
		sMsDrawHMoveText[i].m_bIsUse		= TRUE;

		MSGetWindowRect(MSGetDlgItem(hWnd, wParam), &sMsDrawHMoveText[i].m_Rect);

		bRet = TRUE;
	}

	return bRet;
}


BOOL MSDrawHMoveTextIntput(HMSWND hWnd, WPARAM wParam, char *pwTextInfo)
{
	int i = 0;
	BOOL bRet = FALSE;
	int nTempStep = 0;
	int nTotalMoveStep = 0;
	HMSDC hDC = NULL;
	MSSIZE tempSIZE = { 0 };

	if (hWnd == NULL || wParam == 0 || pwTextInfo == NULL)
	{
		ADIASSERT(hWnd != NULL && wParam != 0 && pwTextInfo != NULL);
		return bRet;
	}

	for (i = 0; i < DRAWMOVETEXTCOUNT; i++)
	{
		if ((sMsDrawHMoveText[i].m_bIsUse) && (sMsDrawHMoveText[i].m_hWnd == hWnd) && (sMsDrawHMoveText[i].m_wParam == wParam))
		{
			bRet = TRUE;
			break;
		}
	}

	if (bRet == FALSE)
	{
		return bRet;
	}

	nTotalMoveStep = MSwcslen((char *)pwTextInfo);
	hDC = MSGetDC(MSGetDlgItem(hWnd, wParam));
	MSGetTextExtentPoint32(hDC, (LPCTSTR)pwTextInfo, nTotalMoveStep, &tempSIZE);
	MSReleaseDC(MSGetDlgItem(hWnd, wParam), hDC);
	hDC = NULL;

	if (tempSIZE.cx < sMsDrawHMoveText[i].m_Rect.right - sMsDrawHMoveText[i].m_Rect.left)
	{
		return TRUE;
	}

	if (nTotalMoveStep > 0)
	{
		nTempStep = (sMsDrawHMoveText[i].m_dwMoveStep % nTotalMoveStep) + 1;
	}
	else
	{
		nTempStep = 0;
	}

	MSSetTimer(sMsDrawHMoveText[i].m_hControlWnd, sMsDrawHMoveText[i].m_dwIdEvent, sMsDrawHMoveText[i].m_wMoveInterval, (MSTIMERPROC)MSDrawControlTimerProc);

	MSDrawHMoveText(sMsDrawHMoveText[i].m_hWnd, sMsDrawHMoveText[i].m_wParam, &sMsDrawHMoveText[i].m_Rect, (char *)pwTextInfo, nTempStep);

	return bRet;
}

BOOL MSDrawHMoveTextDestroy(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent)
{
	int i = 0;
	BOOL bRet = FALSE;

	if (hWnd == NULL || wParam == 0)
	{
		ADIASSERT(hWnd != NULL && wParam != 0);
		return bRet;
	}

	for (i = 0; i < DRAWMOVETEXTCOUNT; i++)
	{
		if (sMsDrawHMoveText[i].m_bIsUse && \
			sMsDrawHMoveText[i].m_hWnd == hWnd   && \
			sMsDrawHMoveText[i].m_wParam == wParam && \
			sMsDrawHMoveText[i].m_dwIdEvent == dwIdEvent)
		{
			sMsDrawHMoveText[i].m_bIsUse = FALSE;
			MSKillTimer(sMsDrawHMoveText[i].m_hWnd, sMsDrawHMoveText[i].m_dwIdEvent);
			bRet = TRUE;
			break;
		}
	}

	return bRet;
}

static void CALLBACK MSDrawControlTimerProc(HMSWND hWnd, UINT uMsg, DWORD dwIdEvent, DWORD dwTime)
{
	int i = 0;

	BOOL bRet = FALSE;

	for (i = 0; i < DRAWMOVETEXTCOUNT; i++)
	{
		if (sMsDrawHMoveText[i].m_bIsUse && sMsDrawHMoveText[i].m_hControlWnd == hWnd)
		{
			bRet = TRUE;
			break;
		}
	}

	if (bRet == FALSE)
	{
		return;
	}

	if (sMsDrawHMoveText[i].m_dwIdEvent == dwIdEvent && MSGetActiveWindow() == MSGetParent(MSGetDlgItem(sMsDrawHMoveText[i].m_hWnd, sMsDrawHMoveText[i].m_wParam)))
	{
		sMsDrawHMoveText[i].m_dwMoveStep++;

		MSInvalidateRect(sMsDrawHMoveText[i].m_hWnd, &sMsDrawHMoveText[i].m_Rect, TRUE);

		MSKillTimer(sMsDrawHMoveText[i].m_hWnd, sMsDrawHMoveText[i].m_dwIdEvent);
	}
	else if (sMsDrawHMoveText[i].m_dwIdEvent == dwIdEvent && MSGetActiveWindow() != MSGetParent(MSGetDlgItem(sMsDrawHMoveText[i].m_hWnd, sMsDrawHMoveText[i].m_wParam)))
	{
		MSKillTimer(sMsDrawHMoveText[i].m_hWnd, sMsDrawHMoveText[i].m_dwIdEvent);
	}
}

static BOOL MSDrawHMoveText(HMSWND hWnd, WPARAM wParam, LPMSRECT lprcText, char *pwTextInfo, DWORD dwCurMoveStep)
{
	BOOL bRet = FALSE;

	if (NULL == lprcText || NULL == pwTextInfo)
	{
		ADIASSERT(NULL != lprcText);
		ADIASSERT(NULL != pwTextInfo);
		bRet = FALSE;
	}
	else
	{
		char   *tempText = NULL;

		if (!MSwcslen(pwTextInfo))
		{
			return bRet;
		}

		if (0 >= dwCurMoveStep)
		{
			dwCurMoveStep = 1;
		}

		tempText = pwTextInfo + 2 * (dwCurMoveStep - 1); //Note:Unicode

		MSSetDlgItemText(hWnd, wParam, (LPCTSTR)tempText);

		bRet = TRUE;
	}

	return bRet;
}