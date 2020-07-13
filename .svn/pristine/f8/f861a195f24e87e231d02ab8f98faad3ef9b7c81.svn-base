/*
*  MS_DrawVMoveText.cpp
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


MsDrawMoveText_s sMsDrawVMoveText[DRAWMOVETEXTCOUNT] = { 0 };

static void CALLBACK MSDrawControlTimerProc(HMSWND hWnd, UINT uMsg, DWORD dwIdEvent, DWORD dwTime);

static BOOL MSDrawVMoveText(HMSWND hWnd, WPARAM wParam, LPMSRECT lprcText, char *pwTextInfo, DWORD dwCurMoveStep);

BOOL MSDrawVMoveTextInit(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent, WORD wMoveInterval)
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
		if (sMsDrawVMoveText[i].m_bIsUse == FALSE)
		{
			break;
		}
	}

	if (i < DRAWMOVETEXTCOUNT)
	{
		memset(&sMsDrawVMoveText[i], 0, sizeof(MsDrawMoveText_s));

		sMsDrawVMoveText[i].m_hWnd = hWnd;
		sMsDrawVMoveText[i].m_wParam = wParam;
		sMsDrawVMoveText[i].m_hControlWnd = MSGetDlgItem(hWnd, wParam);
		sMsDrawVMoveText[i].m_dwIdEvent = dwIdEvent;
		sMsDrawVMoveText[i].m_wMoveInterval = wMoveInterval;
		sMsDrawVMoveText[i].m_dwMoveStep = 0;
		sMsDrawVMoveText[i].m_bIsUse = TRUE;

		MSGetWindowRect(MSGetDlgItem(hWnd, wParam), &sMsDrawVMoveText[i].m_Rect);

		bRet = TRUE;
	}

	return bRet;
}


BOOL MSDrawVMoveTextIntput(HMSWND hWnd, WPARAM wParam, char *pwTextInfo)
{
	int i = 0;
	BOOL bRet = FALSE;
	int nLine = 0;
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
		if ((sMsDrawVMoveText[i].m_bIsUse) && (sMsDrawVMoveText[i].m_hWnd == hWnd) && (sMsDrawVMoveText[i].m_wParam == wParam))
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
    if(NULL != hDC)
    {
        MSGetTextExtentPoint32(hDC, (LPCTSTR)pwTextInfo, 1, &tempSIZE);
        MSReleaseDC(MSGetDlgItem(hWnd, wParam), hDC);
        hDC = NULL;
    
        if(tempSIZE.cx > 0)
        {
            nLine = (sMsDrawVMoveText[i].m_Rect.right - sMsDrawVMoveText[i].m_Rect.left) / tempSIZE.cx;
        }
        else
        {
            return TRUE;
        }
        
        if(nLine > 0)
        {
            nLine = nTotalMoveStep / nLine;
        }
        else
        {
            return TRUE;
        }

        if(tempSIZE.cy - 1 > 0)
        {
            if (nLine <= ((sMsDrawVMoveText[i].m_Rect.bottom - sMsDrawVMoveText[i].m_Rect.top) / tempSIZE.cy - 1))
            {
                MSDrawVMoveText(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_wParam, &sMsDrawVMoveText[i].m_Rect, (char *)pwTextInfo, 0);
                return TRUE;
            }
        }
        else
        {
             return TRUE;
        }
        
        if (nLine > 0)
        {
            nTempStep = (sMsDrawVMoveText[i].m_dwMoveStep % nLine) + 1;
        }
        else
        {
            nTempStep = 0;
        }
    
        MSSetTimer(sMsDrawVMoveText[i].m_hControlWnd, sMsDrawVMoveText[i].m_dwIdEvent, sMsDrawVMoveText[i].m_wMoveInterval, (MSTIMERPROC)MSDrawControlTimerProc);
    
        MSDrawVMoveText(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_wParam, &sMsDrawVMoveText[i].m_Rect, (char *)pwTextInfo, nTempStep);
    }
    
	return bRet;
}

BOOL MSDrawVMoveTextDestroy(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent)
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
		if (sMsDrawVMoveText[i].m_bIsUse && \
			sMsDrawVMoveText[i].m_hWnd == hWnd   && \
			sMsDrawVMoveText[i].m_wParam == wParam && \
			sMsDrawVMoveText[i].m_dwIdEvent == dwIdEvent)
		{

            MSKillTimer(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_dwIdEvent);
            
            memset(&sMsDrawVMoveText[i],0,sizeof(MsDrawMoveText_s));
            
			sMsDrawVMoveText[i].m_bIsUse = FALSE;
			
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
		if (sMsDrawVMoveText[i].m_bIsUse && sMsDrawVMoveText[i].m_hControlWnd == hWnd)
		{
			bRet = TRUE;
			break;
		}
	}

	if (bRet == FALSE)
	{
		return;
	}

	if (sMsDrawVMoveText[i].m_dwIdEvent == dwIdEvent && MSGetActiveWindow() == MSGetParent(MSGetDlgItem(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_wParam)))
	{
		sMsDrawVMoveText[i].m_dwMoveStep++;

		MSInvalidateRect(sMsDrawVMoveText[i].m_hWnd, &sMsDrawVMoveText[i].m_Rect, TRUE);

		MSKillTimer(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_dwIdEvent);
	}
	else if (sMsDrawVMoveText[i].m_dwIdEvent == dwIdEvent && MSGetActiveWindow() != MSGetParent(MSGetDlgItem(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_wParam)))
	{
		MSKillTimer(sMsDrawVMoveText[i].m_hWnd, sMsDrawVMoveText[i].m_dwIdEvent);
	}
}

static BOOL MSDrawVMoveText(HMSWND hWnd, WPARAM wParam, LPMSRECT lprcText, char *pwTextInfo, DWORD dwCurMoveStep)
{
	BOOL bRet = FALSE;
	HMSDC hDC = NULL;
	MSSIZE tempSIZE = { 0 };

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

		if (0 == dwCurMoveStep)
		{
			dwCurMoveStep = 1;
		}

		hDC = MSGetDC(MSGetDlgItem(hWnd, wParam));
        if( NULL != hDC)
        {
            MSGetTextExtentPoint32(hDC, (LPCTSTR)pwTextInfo, 1, &tempSIZE);

        	MSReleaseDC(MSGetDlgItem(hWnd, wParam), hDC);
        	hDC = NULL;

            if(tempSIZE.cx > 0)
            {
        	    tempText = pwTextInfo + 2 * (dwCurMoveStep - 1)*((lprcText->right - lprcText->left) / tempSIZE.cx); //Note:Unicode
            }
            
        	MSSetDlgItemText(hWnd, wParam, (LPCTSTR)tempText);

        	bRet = TRUE;
        }
	}

	return bRet;
}