/*
*  MS_DrawListPubFun.cpp
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawPublic.h"
#include "MS_DrawListPubType.h"
#include "MS_DrawListPub.h"
#include "../AuraRC.h"
#include "../Resources.h"

#define TIMER_MOVE_CELL	(265)

static MSRECT m_rcMoveCell[10];
static int nMoveStep = 0;
static int g_nRectCnt = 0;


static void CALLBACK MSDrawListPubFunCellTimerProc(HMSWND hWnd, UINT uMsg, DWORD dwIdEvent, DWORD dwTime);

static void MSDrawListPubFunDrawItem            (MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, LPMSDRAWLISTPUB_INITPARAM pstListInitParam, int nItemState);

static int  MSDrawListPubFunDrawOneCell			(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nIndex);

static void MSDrawListPubFunDrawCellBorder		(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nFocusState);

static void MSDrawListPubFunDrawBitmapCell		(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nFocusState);

static BOOL MSDrawListPubFunSetCellRect         (LPMSRECT lprc, MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell);


int MSDrawListPublicOneItemByCell(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW,	MSLISTCELL* lpMSListCell,int nCellCount)
{
	int nErrorCode = 0;
	int i, nRetDrawItemProc = 0;	
	LPMSDRAWLISTPUB_INITPARAM pstListInitParam = NULL;
	LPMSLISTCELL lpCell = NULL;

	if (pMSNMLVCUSTOMDRAW == NULL || NULL == lpMSListCell || nCellCount <= 0)
	{
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(nCellCount > 0);
		return -1;
	}

	if(lpMSListCell->m_pItemCustomPar)
	{
		pstListInitParam = lpMSListCell->m_pItemCustomPar;
	}
	
	ADIASSERT(NULL != pstListInitParam);

	if (pstListInitParam->m_pDrawListItemProc != NULL)
	{		
		nRetDrawItemProc = pstListInitParam->m_pDrawListItemProc(pMSNMLVCUSTOMDRAW);

		if (nRetDrawItemProc == 1)
		{
			return nErrorCode;
		}
	}

	if (nRetDrawItemProc != 2)		
	{
		if ((pMSNMLVCUSTOMDRAW->nmcd.uItemState & CDIS_FOCUS) == CDIS_FOCUS)
		{
			if (MSGetFocus() == pMSNMLVCUSTOMDRAW->nmcd.hdr.hwndFrom)
			{
				MSDrawListPubFunDrawItem(pMSNMLVCUSTOMDRAW, pstListInitParam, MS_LIFS_FOCUS);
			}
			else
			{
				MSDrawListPubFunDrawItem(pMSNMLVCUSTOMDRAW, pstListInitParam, MS_LIFS_LOSTFOCUS);
			}
		}
		else
		{
			MSDrawListPubFunDrawItem(pMSNMLVCUSTOMDRAW, pstListInitParam, MS_LIFS_NOFOCUS);
		}
	}

	lpCell = lpMSListCell;

	for (i = 0; i < nCellCount; i++)
	{		
		MSDrawListPubFunDrawOneCell(pMSNMLVCUSTOMDRAW, lpCell, i);
		lpCell++;
	}	

	return nErrorCode;
}

static BOOL MSDrawListPubInitNMLVCELLCUSTOMDRAW(LPMSNMLVCELLCUSTOMDRAW stpMSNMLVCELLCUSTOMDRAW, MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSRECT rcCell, MSLISTCELL* lpMSListCell, int nIndex)
{
	if (stpMSNMLVCELLCUSTOMDRAW == NULL || pMSNMLVCUSTOMDRAW == NULL || lpMSListCell == NULL)
	{
		ADIASSERT(stpMSNMLVCELLCUSTOMDRAW != NULL && pMSNMLVCUSTOMDRAW != NULL && lpMSListCell != NULL);
		return FALSE;
	}

	stpMSNMLVCELLCUSTOMDRAW->m_lpMSNMLVCUSTOMDRAW = pMSNMLVCUSTOMDRAW;
	stpMSNMLVCELLCUSTOMDRAW->m_nCellIndex = nIndex;
	stpMSNMLVCELLCUSTOMDRAW->m_bCustomTxtColor = lpMSListCell->m_bCustomTxtColor;
	stpMSNMLVCELLCUSTOMDRAW->m_dwFocusTxtColor = lpMSListCell->m_dwFocusTxtColor;
	stpMSNMLVCELLCUSTOMDRAW->m_dwLostTxtColor = lpMSListCell->m_dwLostTxtColor;
	stpMSNMLVCELLCUSTOMDRAW->m_dwNoFocusTxtColor = lpMSListCell->m_dwNoFocusTxtColor;
	stpMSNMLVCELLCUSTOMDRAW->m_hbrFocusBackground = lpMSListCell->m_hbrFocusBackground;
	stpMSNMLVCELLCUSTOMDRAW->m_hbrLostBackground = lpMSListCell->m_hbrLostBackground;
	stpMSNMLVCELLCUSTOMDRAW->m_hbrNoFocusBackground = lpMSListCell->m_hbrNoFocusBackground;
	stpMSNMLVCELLCUSTOMDRAW->m_hpenFocusBorder = lpMSListCell->m_hpenFocusBorder;
	stpMSNMLVCELLCUSTOMDRAW->m_hpenLostBorder = lpMSListCell->m_hpenLostBorder;
	stpMSNMLVCELLCUSTOMDRAW->m_hpenNoFocusBorder = lpMSListCell->m_hpenNoFocusBorder;
	stpMSNMLVCELLCUSTOMDRAW->m_emCellType = lpMSListCell->m_emCellType;
	stpMSNMLVCELLCUSTOMDRAW->m_emContentType = lpMSListCell->m_emContentType;
	stpMSNMLVCELLCUSTOMDRAW->m_dwParam1 = lpMSListCell->m_dwParam1;
	stpMSNMLVCELLCUSTOMDRAW->m_dwParam2 = lpMSListCell->m_dwParam2;
	stpMSNMLVCELLCUSTOMDRAW->m_uBorderFormate = lpMSListCell->m_uBorderFormate;
	stpMSNMLVCELLCUSTOMDRAW->m_uContentFormate = lpMSListCell->m_uContentFormate;
	stpMSNMLVCELLCUSTOMDRAW->m_rcCell.left = rcCell.left;
	stpMSNMLVCELLCUSTOMDRAW->m_rcCell.top = rcCell.top;
	stpMSNMLVCELLCUSTOMDRAW->m_rcCell.right = rcCell.right;
	stpMSNMLVCELLCUSTOMDRAW->m_rcCell.bottom = rcCell.bottom;
	stpMSNMLVCELLCUSTOMDRAW->m_pItemCustomPar = lpMSListCell->m_pItemCustomPar;

	return TRUE;
}

static BOOL MS_DrawListFocusCell(MSLISTCELL* lpMSListCell, MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSRECT rcCellInput)
{
	MSRECT rcCell = rcCellInput;

	if (lpMSListCell == NULL || pMSNMLVCUSTOMDRAW == NULL)
	{
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return FALSE;
	}

	if (lpMSListCell->m_hbrFocusBackground != NULL)
	{
		MSFillRect(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rcCell, lpMSListCell->m_hbrFocusBackground);
	}

	if (lpMSListCell->m_uBorderFormate != MS_CELLBORDER_DEFAULT)
	{
		MSDrawListPubFunDrawCellBorder(pMSNMLVCUSTOMDRAW, lpMSListCell, 1);
	}

	if ((lpMSListCell->m_emContentType == MS_CONTENTTYPE_STRING) && (lpMSListCell->m_dwParam1 != NULL))
	{
		COLORREF clrOld;

		if (lpMSListCell->m_bCustomTxtColor)
		{
			clrOld = MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_dwFocusTxtColor);
		}
		else
		{
			LPMSDRAWLISTPUB_INITPARAM pstListInitParam = NULL;
			if (lpMSListCell->m_pItemCustomPar)
			{
				pstListInitParam = lpMSListCell->m_pItemCustomPar;
			}

			ADIASSERT(NULL != pstListInitParam);

			clrOld = MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, pstListInitParam->m_dwFocusTextColor);
		}

		if (lpMSListCell->m_nMoveType == MS_MOVETYPE_STATIC)
		{
			MSDrawText(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, -1, &rcCell, lpMSListCell->m_uContentFormate);
		}
		else
		{
			int nTotalMoveStep = MSwcslen((char *)lpMSListCell->m_dwParam1);
			static DWORD dwOldItemIndex = 0;
			static HMSWND hWndOldList = NULL;
			int nTempStep = 0;

			if ((dwOldItemIndex != pMSNMLVCUSTOMDRAW->nmcd.dwItemSpec) || (hWndOldList != pMSNMLVCUSTOMDRAW->nmcd.hdr.hwndFrom))
			{
				dwOldItemIndex = pMSNMLVCUSTOMDRAW->nmcd.dwItemSpec;
				hWndOldList = pMSNMLVCUSTOMDRAW->nmcd.hdr.hwndFrom;
				nMoveStep = 0;
			}

			if (nTotalMoveStep > 0)
			{
				nTempStep = (nMoveStep % nTotalMoveStep) + 1;
			}
			else
			{
				nTempStep = 0;
			}

			if (lpMSListCell->m_nMoveType == MS_MOVETYPE_AUTO)
			{
				MSSIZE sizeStr;

				MSGetTextExtentPoint32(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, MSwcslen((char *)lpMSListCell->m_dwParam1), &sizeStr);

				if (sizeStr.cx > lpMSListCell->m_nCellWidth)
				{
					MSSetTimer(pMSNMLVCUSTOMDRAW->nmcd.hdr.hwndFrom, TIMER_MOVE_CELL, lpMSListCell->m_uMoveInterval, (MSTIMERPROC)MSDrawListPubFunCellTimerProc);

					if (g_nRectCnt >= sizeof(m_rcMoveCell) / sizeof(m_rcMoveCell[0]))
					{
						g_nRectCnt = 0;
					}

					MSSetRect(&m_rcMoveCell[g_nRectCnt], rcCell.left, rcCell.top, rcCell.right, rcCell.bottom);

					MSDrawMoveText(pMSNMLVCUSTOMDRAW->nmcd.hdc, &m_rcMoveCell[g_nRectCnt], (char *)lpMSListCell->m_dwParam1, nTempStep, lpMSListCell->m_uContentFormate);
					g_nRectCnt++;
				}
				else
				{
					MSDrawText(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, -1, &rcCell, lpMSListCell->m_uContentFormate);
				}
			}
			else
			{
				MSSetTimer(pMSNMLVCUSTOMDRAW->nmcd.hdr.hwndFrom, TIMER_MOVE_CELL, lpMSListCell->m_uMoveInterval, (MSTIMERPROC)MSDrawListPubFunCellTimerProc);

				if (g_nRectCnt >= sizeof(m_rcMoveCell) / sizeof(m_rcMoveCell[0]))
				{
					g_nRectCnt = 0;
				}
				MSSetRect(&m_rcMoveCell[g_nRectCnt], rcCell.left, rcCell.top, rcCell.right, rcCell.bottom);
				MSDrawMoveText(pMSNMLVCUSTOMDRAW->nmcd.hdc, &m_rcMoveCell[g_nRectCnt], (char *)lpMSListCell->m_dwParam1, nTempStep, lpMSListCell->m_uContentFormate);
				g_nRectCnt++;
			}
		}
		MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, clrOld);
	}
	else
	{
		MSDrawListPubFunDrawBitmapCell(pMSNMLVCUSTOMDRAW, lpMSListCell, MS_LIFS_FOCUS);
	}

	return TRUE;
}

static BOOL MS_DrawListLostFocusCell(MSLISTCELL* lpMSListCell, MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSRECT rcCellInput)
{
	MSRECT rcCell = rcCellInput;

	if (lpMSListCell == NULL || pMSNMLVCUSTOMDRAW == NULL)
	{
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return FALSE;
	}

	if (lpMSListCell->m_hbrLostBackground != NULL)
	{
		MSFillRect(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rcCell, lpMSListCell->m_hbrLostBackground);
	}

	if (lpMSListCell->m_uBorderFormate != MS_CELLBORDER_DEFAULT)
	{
		MSDrawListPubFunDrawCellBorder(pMSNMLVCUSTOMDRAW, lpMSListCell, 2);
	}

	if ((lpMSListCell->m_emContentType == MS_CONTENTTYPE_STRING) && (lpMSListCell->m_dwParam1 != NULL))
	{
		if (lpMSListCell->m_bCustomTxtColor)
		{
			COLORREF clrOld = MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_dwLostTxtColor);

			MSDrawText(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, -1, &rcCell, lpMSListCell->m_uContentFormate);

			MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, clrOld);
		}
		else
		{
			LPMSDRAWLISTPUB_INITPARAM pstListInitParam = NULL;
			COLORREF clrOld;
			if (lpMSListCell->m_pItemCustomPar)
			{
				pstListInitParam = lpMSListCell->m_pItemCustomPar;
			}

			ADIASSERT(NULL != pstListInitParam);

			clrOld = MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, pstListInitParam->m_dwLostFocusTextColor);

			MSDrawText(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, -1, &rcCell, lpMSListCell->m_uContentFormate);

			MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, clrOld);
		}
	}
	else
	{
		MSDrawListPubFunDrawBitmapCell(pMSNMLVCUSTOMDRAW, lpMSListCell, MS_LIFS_LOSTFOCUS);
	}
	
	return TRUE;
}

static BOOL MS_DrawListNoFocusCell(MSLISTCELL* lpMSListCell, MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSRECT rcCellInput)
{
	MSRECT rcCell = rcCellInput;

	if (lpMSListCell == NULL || pMSNMLVCUSTOMDRAW == NULL)
	{
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return FALSE;
	}

	if (lpMSListCell->m_hbrNoFocusBackground != NULL)
	{
		MSFillRect(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rcCell, lpMSListCell->m_hbrNoFocusBackground);
	}

	if (lpMSListCell->m_uBorderFormate != MS_CELLBORDER_DEFAULT)
	{
		MSDrawListPubFunDrawCellBorder(pMSNMLVCUSTOMDRAW, lpMSListCell, 0);;
	}

	if ((lpMSListCell->m_emContentType == MS_CONTENTTYPE_STRING) && (lpMSListCell->m_dwParam1 != NULL))
	{
		if (lpMSListCell->m_bCustomTxtColor)
		{
			COLORREF clrOld = MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_dwNoFocusTxtColor);

			MSDrawText(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, -1, &rcCell, lpMSListCell->m_uContentFormate);

			MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, clrOld);
		}
		else
		{

			COLORREF clrOld = MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, RGBA(255, 255, 255, 255));

			MSDrawText(pMSNMLVCUSTOMDRAW->nmcd.hdc, (LPCTSTR)lpMSListCell->m_dwParam1, -1, &rcCell, lpMSListCell->m_uContentFormate);

			MSSetTextColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, clrOld);
		}
	}
	else
	{
		MSDrawListPubFunDrawBitmapCell(pMSNMLVCUSTOMDRAW, lpMSListCell, MS_LIFS_NOFOCUS);
	}

	return TRUE;
}
static int MSDrawListPubFunDrawOneCell(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nIndex)
{
	MSRECT rcCell;

	if (NULL == lpMSListCell || NULL == pMSNMLVCUSTOMDRAW)
	{
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return 0;
	}

	if (lpMSListCell->m_hFont != NULL)
	{
		MSSelectObject(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_hFont);
	}

	MSDrawListPubFunSetCellRect(&rcCell, pMSNMLVCUSTOMDRAW, lpMSListCell);

	if (lpMSListCell->m_pDrawListCellProc != NULL)	
	{
		int nCellProcRet = MS_DLI_DODEFAULT;
		MSNMLVCELLCUSTOMDRAW stMSNMLVCELLCUSTOMDRAW;

		MSDrawListPubInitNMLVCELLCUSTOMDRAW(&stMSNMLVCELLCUSTOMDRAW, pMSNMLVCUSTOMDRAW, rcCell, lpMSListCell, nIndex);
			
		nCellProcRet = lpMSListCell->m_pDrawListCellProc(&stMSNMLVCELLCUSTOMDRAW);

		if (nCellProcRet == MS_DLI_SKIPDEFAULT)
		{
				return MS_DLI_SKIPDEFAULT;
		}
	}
	
	if ((pMSNMLVCUSTOMDRAW->nmcd.uItemState & CDIS_FOCUS) == CDIS_FOCUS)	// Item Focus
	{
		if (MSGetFocus() == pMSNMLVCUSTOMDRAW->nmcd.hdr.hwndFrom)	// List Focus 
		{	
			MS_DrawListFocusCell(lpMSListCell, pMSNMLVCUSTOMDRAW, rcCell);
		}
		else			
		{
			MS_DrawListLostFocusCell(lpMSListCell, pMSNMLVCUSTOMDRAW, rcCell);
		}
	}
	else			
	{
		MS_DrawListNoFocusCell(lpMSListCell, pMSNMLVCUSTOMDRAW, rcCell);
	}
	 
	
	return 0;
}

static void MSDrawListPubFunDrawCellBorder(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nFocusState)
{
	HMSPEN hpenTmp;
	MSRECT rcCell;

	if (NULL == lpMSListCell || NULL == pMSNMLVCUSTOMDRAW)
	{
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return;
	}

	if (nFocusState > MS_LIFS_LOSTFOCUS || nFocusState < MS_LIFS_NOFOCUS)
	{
		ADIASSERT(nFocusState <= MS_LIFS_LOSTFOCUS && nFocusState >= MS_LIFS_NOFOCUS);
		return;
	}

	switch (nFocusState) 
	{
	case 0:
		if (lpMSListCell->m_hpenNoFocusBorder != NULL)
		{
			hpenTmp = MSSelectObject(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_hpenNoFocusBorder);
		}
		else
		{
			return;
		}
		break;
        
	case 1:
		if (lpMSListCell->m_hpenFocusBorder != NULL)
		{
			hpenTmp = MSSelectObject(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_hpenFocusBorder);
		}
		else
		{
			return;
		}
		break;

	case 2:
		if (lpMSListCell->m_hpenLostBorder != NULL)
		{
			hpenTmp = MSSelectObject(pMSNMLVCUSTOMDRAW->nmcd.hdc, lpMSListCell->m_hpenLostBorder);
		}
		else
		{
			return;
		}
		break;
	default:
		break;
	}

	MSDrawListPubFunSetCellRect(&rcCell, pMSNMLVCUSTOMDRAW, lpMSListCell);

	if ((lpMSListCell->m_uBorderFormate & MS_CELLBORDER_LEFT) == MS_CELLBORDER_LEFT) 
	{
		MSMoveToEx(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.left, rcCell.top, NULL);
		MSLineTo(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.left, rcCell.bottom);
	}
	
	if  ((lpMSListCell->m_uBorderFormate & MS_CELLBORDER_RIGHT) == MS_CELLBORDER_RIGHT) 
	{
		MSMoveToEx(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.right, rcCell.top, NULL);
		MSLineTo(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.right, rcCell.bottom);
	}

	if ((lpMSListCell->m_uBorderFormate & MS_CELLBORDER_UP) == MS_CELLBORDER_UP) 
	{
		MSMoveToEx(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.left, rcCell.top, NULL);
		MSLineTo(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.right, rcCell.top);
	}

	if ((lpMSListCell->m_uBorderFormate & MS_CELLBORDER_DOWN) == MS_CELLBORDER_DOWN) 
	{
		MSMoveToEx(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.left, rcCell.bottom, NULL);
		MSLineTo(pMSNMLVCUSTOMDRAW->nmcd.hdc, rcCell.right, rcCell.bottom);
	}

	MSSelectObject(pMSNMLVCUSTOMDRAW->nmcd.hdc, hpenTmp);
	hpenTmp = NULL;
}

static void MSDrawListPubFunDrawItem(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, LPMSDRAWLISTPUB_INITPARAM pstListInitParam, int nItemState)
{
	int nDrawStyleTmp;
	MSRECT rect;

	if (NULL == pstListInitParam || NULL == pMSNMLVCUSTOMDRAW)
	{
		ADIASSERT(NULL != pstListInitParam);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return;
	}

	rect = pMSNMLVCUSTOMDRAW->nmcd.rc;
	rect.right--;

	switch (nItemState)
	{
	case MS_LIFS_NOFOCUS:
		nDrawStyleTmp = pstListInitParam->m_emNoFocusDrawStyle;
		break;

	case MS_LIFS_FOCUS:
		nDrawStyleTmp = pstListInitParam->m_emFocusDrawStyle;
		break;

	case MS_LIFS_LOSTFOCUS:
		nDrawStyleTmp = pstListInitParam->m_emLostFocusDrawStyle;
		break;
	default:
		break;
	}

	switch (nDrawStyleTmp)
	{
	case MSPV_DS_COLOR:
		{
			MSSIZE sizeTmp = {0};

			sizeTmp.cx = pstListInitParam->m_dwNoFocusMid;
			sizeTmp.cy = pstListInitParam->m_dwNoFocusRight;

			if (nItemState == MS_LIFS_NOFOCUS)
			{			
				MSDrawRoundRectWithOutLineByColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, 
					&sizeTmp, pstListInitParam->m_dwNoFocusLeft,pstListInitParam->m_dwNoFocusOutLineColor,pstListInitParam->m_nOutLineWidth);
			}
			else if (nItemState == MS_LIFS_FOCUS)
			{
				MSDrawRoundRectWithOutLineByColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, 
					&sizeTmp, pstListInitParam->m_dwFocusLeft,pstListInitParam->m_dwLostFocusOutLineColor,pstListInitParam->m_nOutLineWidth);
			}
			else
			{
				MSDrawRoundRectWithOutLineByColor(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, 
					&sizeTmp, pstListInitParam->m_dwLostLeft,pstListInitParam->m_dwFocusOutLineColor,pstListInitParam->m_nOutLineWidth);
			}
		}
		break;

	case MSPV_DS_BITMAPID:
		{
			if (nItemState == MS_LIFS_NOFOCUS)
			{
				MSDrawHRectByBitmapID(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, pstListInitParam->m_dwNoFocusLeft, pstListInitParam->m_dwNoFocusMid, pstListInitParam->m_dwNoFocusRight);
			}
			else if (nItemState == MS_LIFS_FOCUS)
			{
				MSDrawHRectByBitmapID(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, pstListInitParam->m_dwFocusLeft, pstListInitParam->m_dwFocusMid, pstListInitParam->m_dwFocusRight);
			}
			else 
			{
				MSDrawHRectByBitmapID(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, pstListInitParam->m_dwLostLeft, pstListInitParam->m_dwLostMid, pstListInitParam->m_dwLostRight);
			}
		}
		break;

	case MSPV_DS_HMSBITMAP:
		{
			if (nItemState == MS_LIFS_NOFOCUS)
			{
				MSDrawHRectByHMSBITMAP(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, pstListInitParam->m_dwNoFocusLeft, pstListInitParam->m_dwNoFocusMid, pstListInitParam->m_dwNoFocusRight);
			}
			else if (nItemState == MS_LIFS_FOCUS)
			{
				MSDrawHRectByHMSBITMAP(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, pstListInitParam->m_dwFocusLeft, pstListInitParam->m_dwFocusMid, pstListInitParam->m_dwFocusRight);
			}
			else
			{
				MSDrawHRectByHMSBITMAP(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rect, pstListInitParam->m_dwLostLeft, pstListInitParam->m_dwLostMid, pstListInitParam->m_dwLostRight);
			}			
		}
		break;

	default:
		break;
	}
}

static void MSDrawListPubFunDrawBitmapCell(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nFocusState)
{
	MSRECT rcCell;

	if (NULL == lpMSListCell || NULL == pMSNMLVCUSTOMDRAW)
	{
		ADIASSERT(NULL != lpMSListCell);
		ADIASSERT(NULL != pMSNMLVCUSTOMDRAW);
		return;
	}

	if (nFocusState > MS_LIFS_LOSTFOCUS || nFocusState < MS_LIFS_NOFOCUS)
	{
		ADIASSERT(nFocusState <= MS_LIFS_LOSTFOCUS && nFocusState >= MS_LIFS_NOFOCUS);
		return;
	}
	
	MSDrawListPubFunSetCellRect(&rcCell, pMSNMLVCUSTOMDRAW, lpMSListCell);

	if ((lpMSListCell->m_dwParam2 != 0) && (nFocusState == MS_LIFS_FOCUS))
	{		
		MSDrawFormateBitmap(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rcCell, (HMSBITMAP)lpMSListCell->m_dwParam2, lpMSListCell->m_uContentFormate);		

		return;
	}

	if (lpMSListCell->m_dwParam1 != 0)
	{
		
		MSDrawFormateBitmap(pMSNMLVCUSTOMDRAW->nmcd.hdc, &rcCell, (HMSBITMAP)lpMSListCell->m_dwParam1, lpMSListCell->m_uContentFormate);		
	}
}

static void CALLBACK MSDrawListPubFunCellTimerProc(HMSWND hWnd, UINT uMsg, DWORD dwIdEvent, DWORD dwTime)
{
	int i;

	if (TIMER_MOVE_CELL == dwIdEvent && MSGetActiveWindow() == MSGetParent(hWnd))
	{	
		nMoveStep ++;
		
		for (i = 0; i < g_nRectCnt; i++)
		{
			
			MSInvalidateRect(hWnd, &m_rcMoveCell[i], TRUE); 

		}
		MSKillTimer(hWnd, TIMER_MOVE_CELL);
	}
	else if (TIMER_MOVE_CELL == dwIdEvent && MSGetActiveWindow() != MSGetParent(hWnd))
	{
		MSKillTimer(hWnd, TIMER_MOVE_CELL);
	}
}


static BOOL MSDrawListPubFunSetCellRect(OUT LPMSRECT lprc, MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell)
{	
	if (lprc == NULL || pMSNMLVCUSTOMDRAW == NULL ||  lpMSListCell == NULL )
	{
		ADIASSERT(lprc != NULL);
		ADIASSERT(pMSNMLVCUSTOMDRAW != NULL);
		ADIASSERT(lpMSListCell != NULL);

		return FALSE;
	}

	return MSSetRect(lprc, pMSNMLVCUSTOMDRAW->nmcd.rc.left + lpMSListCell->m_nCellPos, pMSNMLVCUSTOMDRAW->nmcd.rc.top, pMSNMLVCUSTOMDRAW->nmcd.rc.left + lpMSListCell->m_nCellPos + lpMSListCell->m_nCellWidth, pMSNMLVCUSTOMDRAW->nmcd.rc.bottom);
}

