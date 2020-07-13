/*
*  MS_DrawLRButton.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#include "MSWindows.h"
#include "../Resources.h"
#include "MS_DrawLRButton.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"


static LRESULT  MSDrawLRButtonBar(LPMSNMCUSTOMDRAW LpLrcd, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, char* pMStr, int nLen, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, MSDrawLRBArrowProc pDrawLRBArrowProc);
static LRESULT MSDrawLRButtonText(LPMSNMCUSTOMDRAW pstDrawItem, const char * szText, int nTextPosToLeft);
static LRESULT  MSDrawLRButtonBarLMR(LPMSNMCUSTOMDRAW LpLrcd, DWORD dwFocusedBndBmpLeftID, 
    DWORD dwFocusedBndBmpMiddleID, DWORD dwFocusedBndBmpRightID, DWORD dwNoFocusedBndBmpLeftID, 
    DWORD dwNoFocusedBndBmpMiddleID, DWORD dwNoFocusedBndBmpRightID, char* pMStr, int nLen, 
    DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, HMSFONT hFont, int nTextPosToLeft, MSDrawLRBArrowProc pDrawLRBArrowProc);

BOOL MSLRButtonInit( HMSWND hWnd, DWORD dwLRButtonId, int nMinNum, int nMaxNum, int nPos )
{
	BOOL bRet = FALSE;
	HMSWND hWndLRBtnCtrl = NULL;

	if(hWnd == NULL || dwLRButtonId == 0 || nPos > nMaxNum || nPos < nMinNum)
	{
		ADIASSERT(hWnd != NULL && dwLRButtonId != 0 && nPos < nMaxNum && nPos > nMinNum);
		return bRet;
	}
	
	hWndLRBtnCtrl = MSGetDlgItem(hWnd, dwLRButtonId);
	bRet = MSLRButton_SetRange( hWndLRBtnCtrl, TRUE, nMinNum, nMaxNum );
	bRet &= MSLRButton_SetPos( hWndLRBtnCtrl, TRUE, nPos );
	
	return bRet;
}


int MSLRButtonGetPos(HMSWND hWnd, DWORD dwLRButtonId)
{
	int nPos = -1;
	
	if(hWnd == NULL || dwLRButtonId == 0)
	{
		ADIASSERT(hWnd != NULL && dwLRButtonId != 0 );
		return nPos;
	}

	nPos = MSLRButton_GetPos(MSGetDlgItem(hWnd, dwLRButtonId));
		
	return nPos;
}

int MSLRButtonGetRangeMin(HMSWND hWnd, DWORD dwLRButtonId)
{
	int nRangeMin = -1;
	
	if (hWnd == NULL || dwLRButtonId == 0)
	{
		ADIASSERT(hWnd != NULL && dwLRButtonId != 0);
		return nRangeMin;
	}

	nRangeMin = MSLRButton_GetRangeMin(MSGetDlgItem(hWnd, dwLRButtonId));

	return nRangeMin;
}

int MSLRButtonGetRangeMax(HMSWND hWnd, DWORD dwLRButtonId)
{
	int nRangeMax = -1;
	
	if (hWnd == NULL || dwLRButtonId == 0)
	{
		ADIASSERT(hWnd != NULL && dwLRButtonId != 0);
		return nRangeMax;
	}

	nRangeMax = MSLRButton_GetRangeMax(MSGetDlgItem(hWnd, dwLRButtonId));
		
	return nRangeMax;
}

BOOL MSLRButtonSetRange(HMSWND hWnd, DWORD dwLRButtonID, int nMin, int nMax)
{
	BOOL bRet = FALSE;

	if (hWnd == NULL || dwLRButtonID == 0)
	{
		ADIASSERT(hWnd != NULL && dwLRButtonID != 0);
		return bRet;
	}

	MSLRButton_SetRange(MSGetDlgItem(hWnd, dwLRButtonID), TRUE, nMin, nMax);
	bRet = TRUE;
	
	return bRet;
}


BOOL  MSLRButtonSetPos(HMSWND hWnd, DWORD dwLRButtonId,int nPos)
{
	BOOL bRet = FALSE;
	
	if (hWnd == NULL || dwLRButtonId == 0)
	{
		ADIASSERT(hWnd != NULL && dwLRButtonId != 0);
		return bRet;
	}

	bRet = MSLRButton_SetPos(MSGetDlgItem(hWnd, dwLRButtonId),TRUE,nPos);
		
	return bRet;
}


LRESULT MSDrawLRButtonProcWithChar(LPARAM lParam, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, char* pMStr, int nLen, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor,  MSDrawLRBArrowProc pDrawLRBArrowProc)
{
	LPMSNMHDR  nHdr = (LPMSNMHDR )lParam ; 
	int nRet = 0;
	BOOL bRet = FALSE;
	if(nHdr->code == NM_CUSTOMDRAW )
	{  
		LPMSNMCUSTOMDRAW  LpLrcd = (LPMSNMCUSTOMDRAW) lParam ;

		switch(LpLrcd->dwDrawStage )  
		{
		case  CDDS_PREPAINT :           
			nRet = CDRF_NOTIFYITEMDRAW;
			break;

		case  CDDS_ITEMPREPAINT :
			nRet = MSDrawLRButtonBar(LpLrcd, dwFocusedBndBmpID, dwNoFocusedBndBmpID, pMStr, nLen, dwFocusedTextColor, dwNoFocusedTextColor, pDrawLRBArrowProc);
			break;
		}
	}

	return  nRet;
}

LRESULT MSDrawLRButtonProcWithCharLMR(LPARAM lParam, DWORD dwFocusedBndBmpLeftID, DWORD dwFocusedBndBmpMiddleID,
        DWORD dwFocusedBndBmpRightID, DWORD dwNoFocusedBndBmpLeftID, DWORD dwNoFocusedBndBmpMiddleID,
        DWORD dwNoFocusedBndBmpRightID, char* pMStr, int nLen, DWORD dwFocusedTextColor, 
        DWORD dwNoFocusedTextColor,  HMSFONT hFont, int nTextPosToLeft, MSDrawLRBArrowProc pDrawLRBArrowProc)
{
	LPMSNMHDR  nHdr = (LPMSNMHDR )lParam ; 
	int nRet = 0;
	BOOL bRet = FALSE;
	if(nHdr->code == NM_CUSTOMDRAW )
	{  
		LPMSNMCUSTOMDRAW  LpLrcd = (LPMSNMCUSTOMDRAW) lParam ;

		switch(LpLrcd->dwDrawStage )  
		{
		case  CDDS_PREPAINT :           
			nRet = CDRF_NOTIFYITEMDRAW;
			break;

		case  CDDS_ITEMPREPAINT :
			nRet = MSDrawLRButtonBarLMR(LpLrcd, dwFocusedBndBmpLeftID, dwFocusedBndBmpMiddleID, 
                dwFocusedBndBmpRightID, dwNoFocusedBndBmpLeftID, dwNoFocusedBndBmpMiddleID, dwNoFocusedBndBmpRightID,
                pMStr, nLen, dwFocusedTextColor, dwNoFocusedTextColor, hFont, nTextPosToLeft, pDrawLRBArrowProc);
			break;
		}
	}

	return  nRet;
}

LRESULT MSDrawLRButtonProc(LPARAM lParam, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, DWORD dwStrID, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor,  MSDrawLRBArrowProc pDrawLRBArrowProc)
{
	int nRet = 0;
	char TxtBuf[256] = {0};

	memset(TxtBuf, 0, sizeof(TxtBuf));

	if (MSLoadString(GetInstance(), dwStrID, (LPTSTR)TxtBuf, (sizeof(TxtBuf) >> 1) - 1) > 0)
	{
		nRet = MSDrawLRButtonProcWithChar(lParam, dwFocusedBndBmpID, dwNoFocusedBndBmpID, TxtBuf, MSwcslen(TxtBuf), dwFocusedTextColor, dwNoFocusedTextColor, pDrawLRBArrowProc);
	}

	return  (LRESULT)nRet;
}


LRESULT MSDrawLRButtonProcLMR(LPARAM lParam, DWORD dwFocusedBndBmpLeftID, DWORD dwFocusedBndBmpMiddleID,
    DWORD dwFocusedBndBmpRightID, DWORD dwNoFocusedBndBmpLeftID, DWORD dwNoFocusedBndBmpMiddleID, DWORD dwNoFocusedBndBmpRightID, 
    DWORD dwStrID, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor,  HMSFONT hFont, int nTextPosToLeft, MSDrawLRBArrowProc pDrawLRBArrowProc)
{
	int nRet = 0;
	char TxtBuf[256] = {0};

	memset(TxtBuf, 0, sizeof(TxtBuf));

	if (MSLoadString(GetInstance(), dwStrID, (LPTSTR)TxtBuf, (sizeof(TxtBuf) >> 1) - 1) > 0)
	{
		nRet = MSDrawLRButtonProcWithCharLMR(lParam, dwFocusedBndBmpLeftID, dwFocusedBndBmpMiddleID, 
            dwFocusedBndBmpRightID, dwNoFocusedBndBmpLeftID, dwNoFocusedBndBmpMiddleID, dwNoFocusedBndBmpRightID,
            TxtBuf, MSwcslen(TxtBuf), dwFocusedTextColor, dwNoFocusedTextColor, hFont, nTextPosToLeft, pDrawLRBArrowProc);
	}

	return  (LRESULT)nRet;
}

static LRESULT  MSDrawLRButtonBar(LPMSNMCUSTOMDRAW LpLrcd, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, char* pMStr, int nLen, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, MSDrawLRBArrowProc pDrawLRBArrowProc)
{
	int nRet = 0;
	MSRECT    tempMSRECT;
	MSPOINT   tempPoint;
	HMSBITMAP hMSFocusBITMAP = NULL;
	HMSBITMAP hMSNoFocusBITMAP = NULL;

	if (LpLrcd == NULL  || pMStr == NULL)
	{
		return 0;
	}

	tempPoint.x = LpLrcd->rc.left;
	tempPoint.y = LpLrcd->rc.top;

	tempMSRECT  = LpLrcd->rc;
		
	hMSFocusBITMAP   = AuraLoadPNG(GetInstance(), (LPCTSTR)dwFocusedBndBmpID);
	hMSNoFocusBITMAP = AuraLoadPNG(GetInstance(), (LPCTSTR)dwNoFocusedBndBmpID);
		
	if ( ( LpLrcd->uItemState & CDIS_FOCUS ) == CDIS_FOCUS )
	{    
		MSSetTextColor( LpLrcd->hdc, dwFocusedTextColor );
		tempPoint.y -= 5;
		if (hMSFocusBITMAP != NULL)
		{
			MSDrawBitmapToRect(LpLrcd->hdc, hMSFocusBITMAP, LpLrcd->rc, 0);
		}
			
		MSDrawText(LpLrcd->hdc, (LPCTSTR)pMStr, nLen, &tempMSRECT, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	else
	{
		MSSetTextColor( LpLrcd->hdc, dwNoFocusedTextColor );
		if (hMSNoFocusBITMAP != NULL)
		{
			MSDrawBitmapToRect(LpLrcd->hdc, hMSNoFocusBITMAP, LpLrcd->rc, 0);
		}

		MSDrawText(LpLrcd->hdc, (LPCTSTR)pMStr, nLen, &tempMSRECT, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}

	//»­LRBtnµÄ×óÓÒ¼ýÍ·
	if (pDrawLRBArrowProc != NULL)
	{
		pDrawLRBArrowProc(LpLrcd);
	}

	if (hMSFocusBITMAP != NULL)
	{
		MSDeleteObject((HMSOBJECT)hMSFocusBITMAP);
	}

	if (hMSNoFocusBITMAP != NULL)
	{
		MSDeleteObject((HMSOBJECT)hMSNoFocusBITMAP);
	}

	return CDRF_SKIPDEFAULT;
}

static LRESULT  MSDrawLRButtonBarLMR(LPMSNMCUSTOMDRAW LpLrcd, DWORD dwFocusedBndBmpLeftID, 
    DWORD dwFocusedBndBmpMiddleID, DWORD dwFocusedBndBmpRightID, DWORD dwNoFocusedBndBmpLeftID, 
    DWORD dwNoFocusedBndBmpMiddleID, DWORD dwNoFocusedBndBmpRightID, char* pMStr, int nLen, 
    DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, HMSFONT hFont, int nTextPosToLeft, MSDrawLRBArrowProc pDrawLRBArrowProc)
{
	int nRet = 0;  
    DWORD dwPrevColor = 0;

	if (LpLrcd == NULL  || pMStr == NULL)
	{
		return 0;
	}

	dwPrevColor = MSSetTextColor(LpLrcd->hdc, dwFocusedTextColor);

    if ( ( LpLrcd->uItemState & ODS_FOCUS ) == ODS_FOCUS ) 	
	{		
		MSDrawHRectByBitmapID( LpLrcd->hdc, &LpLrcd->rc, dwFocusedBndBmpLeftID, dwFocusedBndBmpMiddleID, dwFocusedBndBmpRightID);
	}
	else
	{				
        if(dwNoFocusedBndBmpLeftID != 0 && dwNoFocusedBndBmpLeftID != 0 && dwNoFocusedBndBmpRightID != 0)
        {
            MSDrawHRectByBitmapID( LpLrcd->hdc, &LpLrcd->rc, dwNoFocusedBndBmpLeftID, dwNoFocusedBndBmpLeftID, dwNoFocusedBndBmpRightID);
        }
    }

    MSSelectObject(LpLrcd->hdc, hFont);
    
    MSDrawLRButtonText(LpLrcd, pMStr, nTextPosToLeft);
	
	MSSetTextColor( LpLrcd->hdc, dwPrevColor );
    
	//»­LRBtnµÄ×óÓÒ¼ýÍ·
	if (pDrawLRBArrowProc != NULL)
	{
		pDrawLRBArrowProc(LpLrcd);
	}

	return CDRF_SKIPDEFAULT;
}


static LRESULT MSDrawLRButtonText(LPMSNMCUSTOMDRAW pstDrawItem, const char * szText, int nTextPosToLeft)
{
	if (NULL == pstDrawItem || szText == NULL)
	{
		ADIASSERT(NULL != pstDrawItem && szText != NULL);
		return 0;
	}

	if ( nTextPosToLeft < 0 )
	{
		MSDrawText(pstDrawItem->hdc, (LPCTSTR)szText, MSwcslen(szText), &pstDrawItem->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	else 
	{
		MSRECT rect = pstDrawItem->rc;
			
		rect.left += nTextPosToLeft;

		MSDrawText(pstDrawItem->hdc, (LPCTSTR)szText, MSwcslen(szText), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	
	return 0;
}


