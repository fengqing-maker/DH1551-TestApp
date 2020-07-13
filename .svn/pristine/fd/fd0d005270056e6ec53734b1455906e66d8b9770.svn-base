/*
*  MS_DrawPublic.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawType.h"
#include "MS_DrawPublic.h"
#include "../Resources.h"
#include "MSWINGDI.h"
#include "adi_osg.h"


BOOL MSErasureDialogBG(HMSWND hWnd,HMSDC hDC)
{
	HMSDC hMSDC = NULL;
	ADI_HANDLE hHandle = NULL;
	HMSBRUSH hBkBrush = NULL;
	MSRECT Rect = { 0 };

	if (hDC == NULL)
	{
		return FALSE;
	}

	hBkBrush = MSCreateSolidBrush(RGBA ( 100, 100, 100, 0 ));

	MSGetWindowRect(hWnd, &Rect);
 	MSFillRect(hDC, &Rect, hBkBrush);

	MSDeleteObject((HMSOBJECT)hBkBrush);

	return 1;
}

BOOL MSFillRectByColor(HMSDC hdc, MSRECT *lpRect, COLORREF clrFill)
{	
	HMSBRUSH hbrFill = NULL;
	MSRECT  rect = {0};
	BOOL	bRet = FALSE;

	if(NULL == hdc || NULL == lpRect)
	{
		ADIASSERT(hdc != NULL);
		ADIASSERT(lpRect != NULL);

		return bRet;
	}

	
	hbrFill = MSCreateSolidBrush(clrFill);

	if (hbrFill == NULL)
	{
		return FALSE;
	}	

	rect = *lpRect;
		   
	MSFillRect(hdc, &rect, hbrFill);

	MSDeleteObject(hbrFill);
	hbrFill = NULL;
	bRet = TRUE;
	
	return  bRet;

}


BOOL MSDrawBitmap(HMSDC hDC, HMSBITMAP hMSBITMAP, MSPOINT* pMSPOINT)
{
	BOOL bRet = FALSE;
	HMSDC		hMemMSDC = NULL;
	MSSIZE      sizeBitmap;

	if(NULL == hDC || NULL == hMSBITMAP || NULL == pMSPOINT)
	{
		ADIASSERT(hDC != NULL); 
		ADIASSERT(hMSBITMAP != NULL);
		ADIASSERT(pMSPOINT != NULL);

		return bRet;
	}

	memset(&sizeBitmap, 0, sizeof(MSSIZE));

	MSGetBitmapDimensionEx(hMSBITMAP, &sizeBitmap);

	hMemMSDC = MSCreateCompatibleDC(hDC);
	MSSelectObject(hMemMSDC, hMSBITMAP);

	bRet = MSBitBlt(hDC, pMSPOINT->x, pMSPOINT->y, sizeBitmap.cx, sizeBitmap.cy, hMemMSDC, 0, 0, SRCCOPY);

	MSDeleteDC(hMemMSDC);
	
	return bRet;
}


BOOL MSDrawVRectByBitmapID(HMSDC hDC, MSRECT* pMSRECT, DWORD dwUpBitmapID, DWORD dwMidBitmapID, DWORD dwDownBitmapID)
{
	BOOL bRet = FALSE;
	HMSBITMAP	hbmpUp = NULL;
	HMSBITMAP	hbmpMid = NULL;
	HMSBITMAP	hbmpDown = NULL;

	if(NULL == hDC || NULL == pMSRECT)
	{
		ADIASSERT(hDC != NULL);
		ADIASSERT(pMSRECT != NULL);
		return bRet;
	}

	hbmpUp   = AuraLoadPNG(GetInstance(), (LPCTSTR)dwUpBitmapID);
	hbmpMid  = AuraLoadPNG(GetInstance(), (LPCTSTR)dwMidBitmapID);
	hbmpDown = AuraLoadPNG(GetInstance(), (LPCTSTR)dwDownBitmapID);

	if ( hbmpMid!=NULL)
	{
		bRet = MSDrawVRectByHMSBITMAP(hDC, pMSRECT, hbmpUp, hbmpMid, hbmpDown);
	}

	MSDeleteObject((HMSOBJECT)hbmpUp);
	MSDeleteObject((HMSOBJECT)hbmpMid);
	MSDeleteObject((HMSOBJECT)hbmpDown);
	hbmpUp = NULL;
	hbmpMid = NULL;
	hbmpDown = NULL;

	return bRet;
}

BOOL MSDrawVRectByHMSBITMAP(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmpUp, HMSBITMAP hbmpMid, HMSBITMAP hbmpDown)
{
	BOOL bRet = FALSE;

	MSRECT rect;
	MSSIZE sizeBitmap;
	HMSBRUSH hbrFill = NULL;
	MSPOINT Point;
    
	if (pMSRECT == NULL || hbmpMid == NULL)
	{
		ADIASSERT(pMSRECT != NULL);
		ADIASSERT(hbmpMid != NULL);
		return FALSE;
	}
		
	Point.x = pMSRECT->left;
	Point.y = pMSRECT->top;
	
    rect = *pMSRECT;
	
	if(hbmpUp)
	{
		bRet = MSDrawBitmap(hDC, hbmpUp, &Point);		

		if (!bRet)
		{
			return FALSE;
		}
		
		MSGetBitmapDimensionEx(hbmpUp, &sizeBitmap);	

		rect.left = pMSRECT->left;					
		rect.top = pMSRECT->top + sizeBitmap.cy;
		rect.right = rect.left + sizeBitmap.cx;
	}

	if(hbmpDown)
	{
		MSGetBitmapDimensionEx(hbmpDown, &sizeBitmap);	

		Point.x = pMSRECT->left;
		Point.y = pMSRECT->bottom - sizeBitmap.cy + 1;

		rect.bottom = Point.y;						
		if (rect.bottom < rect.top)
		{
			rect.bottom = rect.top;
		}

		bRet = MSDrawBitmap(hDC, hbmpDown, &Point);	

		if (!bRet)
		{
			return FALSE;
		}
	}

    if(hbmpMid)
	{

		hbrFill = MSCreatePatternBrush(hbmpMid);	

		ADIASSERT(hbrFill != NULL);
		if (hbrFill == NULL)
		{
			return FALSE;
		}

		MSFillRect(hDC, &rect, hbrFill);			

		MSDeleteObject(hbrFill);
		hbrFill = NULL;
	}

	return bRet;
}
 
BOOL MSDrawRoundRectByColor(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE, DWORD dwColor)
{
	HMSBRUSH hbrBackground		= NULL;		
	HMSBRUSH hbrOldBackground	= NULL;		
	BOOL bRet = FALSE;
	MSRECT rect = *pMSRECT;

	if(NULL == hDC || NULL == pMSRECT )
	{
		ADIASSERT(NULL != hDC);
		ADIASSERT(NULL != pMSRECT);
		return bRet;
	}
						
	hbrBackground = MSCreateSolidBrush(dwColor);
	ADIASSERT(NULL != hbrBackground);

	if (NULL != hbrBackground)
	{
			
		if(NULL != pMSSIZE)
		{
			hbrOldBackground = MSSelectObject(hDC, hbrBackground);

			MSRoundRect(hDC, rect.left, rect.top,  rect.right, rect.bottom, pMSSIZE->cx, pMSSIZE->cy);
			bRet = TRUE;
			MSSelectObject(hDC, hbrOldBackground);
		}
		else
		{
			bRet = MSFillRect(hDC, &rect, hbrBackground);
		}
	}
	else
	{
		bRet = FALSE;
	}

	if(hbrBackground)
	{
		MSDeleteObject(hbrBackground);
		hbrBackground = NULL;
	}
	
	return bRet;
 }
    
BOOL MSDirectDrawRectByColor(HMSDC hDC, MSRECT* pMSRECT, DWORD dwColor)
{
	HMSBRUSH hbrBackground		= NULL;		
	HMSBRUSH hbrOldBackground		= NULL;		
	BOOL bRet = FALSE;
	MSRECT rect = *pMSRECT;

	if(NULL == hDC || NULL == pMSRECT )
	{
		ADIASSERT(NULL != hDC);
		ADIASSERT(NULL != pMSRECT);

		return bRet;
	}
						
	hbrBackground = MSCreateSolidBrush(dwColor);
	ADIASSERT(NULL != hbrBackground);

	if (NULL != hbrBackground)
	{
		bRet = MSFillRect(hDC, &rect, hbrBackground);
	}
	else
	{
		bRet = FALSE;
	}

	if(hbrBackground)
	{
		MSDeleteObject(hbrBackground);
		hbrBackground = NULL;
	}
	
	return bRet;
 }

    
BOOL MSDrawRoundRectByHMSBRUSH(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE, HMSBRUSH hbr)
{
	HMSBRUSH hbrOld		= NULL;
	BOOL bRet = FALSE;
	MSRECT rect = {0};

	if(NULL == hDC || NULL == pMSRECT || NULL == hbr)
	{
		ADIASSERT(NULL != hDC);
		ADIASSERT(NULL != pMSRECT);
		ADIASSERT(NULL != hbr);
		return bRet;
	}

	memset(&rect, 0, sizeof(MSRECT));
	rect = *pMSRECT;
	
	if(NULL != pMSSIZE)
	{
		hbrOld = MSSelectObject(hDC, hbr);
		bRet = MSRoundRect(hDC, rect.left, rect.top, rect.right, rect.bottom, pMSSIZE->cx, pMSSIZE->cy);
		MSSelectObject(hDC, hbrOld);
	}
	else
	{
		bRet = MSFillRect(hDC, &rect, hbr);
	}
	
	return bRet;
}


BOOL MSDrawTextRoundRectByColor(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE,  DWORD dwBackgroundColor, LPCTSTR lpString, int nCount, UINT uFormat, DWORD dwTxtColor)
{
	BOOL bRet = FALSE;

	COLORREF oldTextColor = NULL;
	if(NULL == hDC ||NULL ==  pMSRECT || NULL == lpString)
	{
		ADIASSERT(NULL != hDC && NULL != pMSRECT && NULL != lpString);
		return bRet;
	}
	
	bRet = MSDrawRoundRectByColor(hDC, pMSRECT, pMSSIZE, dwBackgroundColor);
	if (bRet == FALSE)
	{
		return bRet;
	}

	oldTextColor = MSSetTextColor(hDC, dwTxtColor);
	bRet = MSDrawText(hDC, lpString, nCount, pMSRECT, uFormat);
	MSSetTextColor(hDC, oldTextColor);

	return bRet;
}
  
    
BOOL MSDrawTextRoundRectByHMSBRUSH(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE, HMSBRUSH hbr, LPCTSTR lpString, int nCount, UINT uFormat, DWORD dwTxtColor)
{
	BOOL bRet = FALSE;
	COLORREF oldTextColor = NULL;

	if(NULL == pMSRECT || NULL == lpString)
	{
		ADIASSERT(NULL != lpString);
		ADIASSERT(NULL != pMSRECT);
		return bRet;
	}
	
	bRet = MSDrawRoundRectByHMSBRUSH(hDC, pMSRECT, pMSSIZE, hbr);

	if (bRet == FALSE)
	{
		return bRet;
	}

	oldTextColor = MSSetTextColor(hDC, dwTxtColor);
	bRet = MSDrawText(hDC, lpString, nCount, pMSRECT, uFormat);

	MSSetTextColor(hDC, oldTextColor);

	return bRet;
}



BOOL MSDrawFormateBitmap(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmp, UINT uFormate)
{
	MSPOINT pntTmp = {0};
	MSSIZE  size;

	if(NULL == hDC || NULL  == pMSRECT || NULL == hbmp)
	{
		ADIASSERT(hDC != NULL);
		ADIASSERT(pMSRECT != NULL);
		ADIASSERT(hbmp != NULL);
		
		return FALSE;
	}
	
	MSGetBitmapDimensionEx(hbmp, &size);

	pntTmp.x = pMSRECT->left;
	pntTmp.y = pMSRECT->top;

	if ((uFormate & DT_TOP) == DT_TOP)
	{
		pntTmp.y = pMSRECT->top;
	}

	if ((uFormate & DT_LEFT) == DT_LEFT)
	{
		pntTmp.x = pMSRECT->left;
	}

	if ((uFormate & DT_RIGHT) == DT_RIGHT)
	{
		pntTmp.x = pMSRECT->right - size.cx;
	}

	if ((uFormate & DT_CENTER) == DT_CENTER)
	{
		pntTmp.x = pMSRECT->left + (pMSRECT->right - pMSRECT->left - size.cx) / 2;
	}

	if ((uFormate & DT_VCENTER) == DT_VCENTER)
	{
		pntTmp.y = pMSRECT->top + (pMSRECT->bottom - pMSRECT->top - size.cy) / 2;
	}

	if ((uFormate & DT_BOTTOM) == DT_BOTTOM)
	{
		pntTmp.y = pMSRECT->bottom - size.cy;
	}

	return MSDrawBitmap(hDC, hbmp, &pntTmp);
}


void MSDrawMoveText(HMSDC hdc, LPMSRECT lprcText, char *pwTextInfo, DWORD dwCurMoveStep, UINT uFormate)
{
	char   *tempText = NULL;

	if(NULL == lprcText ||NULL ==  pwTextInfo)
	{
		ADIASSERT(NULL != lprcText);
		ADIASSERT(NULL != pwTextInfo);
		return;
	}

	if (!MSwcslen(pwTextInfo))
	{
		return;
	}

	if (0 >= dwCurMoveStep) 
	{
		dwCurMoveStep = 1;
	}

	tempText = pwTextInfo + 2 *(dwCurMoveStep - 1); //Note:Unicode
	MSDrawText(hdc, (LPCTSTR)tempText, MSwcslen(tempText), lprcText, uFormate);	

	return;
}


BOOL MSGetStrSize(HMSDC hdc,const char *pStr, LPMSSIZE lpSize)
{
	char swStr[256];
	const char *pDestStr = pStr;

	if(NULL == pDestStr || NULL == lpSize)
	{
		ADIASSERT(NULL != pDestStr);
		ADIASSERT(NULL != lpSize);

		return FALSE;
	}
	
	MSMultiByteToWideChar(0, 0, pStr,(int)strlen(pStr), (LPWSTR)swStr, (int)(sizeof(swStr) >> 1) - 2);	
	pDestStr = swStr;	
	MSGetTextExtentPoint32(hdc, (LPCTSTR)pStr, MSwcslen(pDestStr), lpSize);

	return TRUE;
}

BOOL MSGetstrIDSSize(HMSDC hdc,DWORD dwstrIDS, IN OUT LPMSSIZE lpSize)
{
	char swStr[256];

	if (dwstrIDS == 0)
	{
		ADIASSERT(dwstrIDS != 0);
		return FALSE;
	}

	memset(swStr, 0, sizeof(swStr));

	MSLoadString(GetInstance(), dwstrIDS, (LPTSTR)swStr, (sizeof(swStr) >> 1) - 1);

	return MSGetStrSize(hdc, swStr, lpSize);
}


BOOL MSDrawRoundRectWithOutLineByColor(HMSDC hdc,const MSRECT *lprc,const MSSIZE *lpsz,COLORREF clrInBackground,COLORREF clrOutLine,const int nOutLineWidth)
{
	HMSPEN 		hpenOutline				= NULL;		
	HMSPEN 		hpenOldpen				= NULL;		
	HMSBRUSH 	hbrInBackground		= NULL;		
	HMSBRUSH 	hbrOldBackground		= NULL;		

	if(hdc == NULL || lprc == NULL || lpsz == NULL)
	{
		ADIASSERT(hdc != NULL && lprc != NULL && lpsz != NULL);
		return FALSE;
	}

	if(nOutLineWidth >1)
	{
		hpenOutline	= MSCreatePen(PS_SOLID, nOutLineWidth, clrOutLine);	
		ADIASSERT(NULL != hpenOutline);
	}

	hbrInBackground		= MSCreateSolidBrush(clrInBackground);
	ADIASSERT(NULL != hbrInBackground);

	if (NULL != hbrInBackground)
	{	
		if(hpenOutline)
		{		
			hpenOldpen		= MSSelectObject(hdc, hpenOutline);
		}
		hbrOldBackground = MSSelectObject(hdc, hbrInBackground);

		MSRoundRect(hdc, lprc->left, lprc->top, lprc->right,lprc->bottom,lpsz->cx, lpsz->cy);

		if(hpenOldpen)
		{
			MSSelectObject(hdc, hpenOldpen);
		}
		
		MSSelectObject(hdc, hbrOldBackground);	
	}    

	if(hpenOutline)
	{
		MSDeleteObject(hpenOutline);
		hpenOutline = NULL;
	}

	if(hbrInBackground)
	{
		MSDeleteObject(hbrInBackground);
		hbrInBackground = NULL;
	}

	return TRUE;
}


BOOL MSDrawRoundRectWithFrameByColor(HMSDC hdc,const MSRECT *lprc,const MSSIZE *lpsz,COLORREF clrInBackground,COLORREF clrFrame,const int nclrFrameWidth)
{
	HMSBRUSH 	hpenFrame			= NULL;		
	HMSBRUSH 	hpenOldFrame		= NULL;		
	HMSBRUSH 	hbrInBackground		= NULL;		
	HMSBRUSH 	hbrOldBackground	= NULL;		

	if(hdc == NULL || lprc == NULL || lpsz == NULL)
	{
		ADIASSERT(hdc != NULL && lprc != NULL && lpsz != NULL);
		return FALSE;
	}

	if(nclrFrameWidth >= 1)
	{
		hpenFrame = MSCreateSolidBrush(clrFrame);
		ADIASSERT(NULL != hpenFrame);
	}

	hbrInBackground	= MSCreateSolidBrush(clrInBackground);
	ADIASSERT(NULL != hbrInBackground);

	if(NULL != hpenFrame)
	{		
		hpenOldFrame = MSSelectObject(hdc, hpenFrame);
		MSRoundRect(hdc, lprc->left, lprc->top, lprc->right,lprc->bottom,lpsz->cx, lpsz->cy);
		
	}

	if (NULL != hbrInBackground)
	{
		hbrOldBackground = MSSelectObject(hdc, hbrInBackground);
		MSRoundRect(hdc, lprc->left + nclrFrameWidth, lprc->top + nclrFrameWidth, lprc->right - nclrFrameWidth,lprc->bottom - nclrFrameWidth,lpsz->cx, lpsz->cy);
	}
	
	if(hpenOldFrame)
	{
		MSSelectObject(hdc, hpenOldFrame);
	}
	
	if(hpenFrame)
	{
		MSDeleteObject(hpenFrame);
		hpenFrame = NULL;
	}

	if(hbrInBackground)
	{
		MSDeleteObject(hbrInBackground);
		hbrInBackground = NULL;
	}

	return TRUE;
}


BOOL MSDrawLineByColor(HMSDC hdc,MSRECT *lprc,COLORREF Color,int width)
{
    HMSPEN hOld= NULL;
    HMSPEN hpenLine=NULL;

	if (NULL == hdc || NULL == lprc)
	{
		ADIASSERT(hdc != NULL);
		ADIASSERT(lprc != NULL);
		return FALSE;
	}

    hpenLine = MSCreatePen(PS_SOLID, width,Color);
    hOld = MSSelectObject(hdc,hpenLine);

    MSMoveToEx(hdc, lprc->left,lprc->top, NULL);
	MSLineTo(hdc, lprc->right, lprc->top);

	MSSelectObject(hdc,hOld);

	if(hpenLine != NULL)
	{
	    MSDeleteObject(hpenLine);
	    hpenLine = NULL;
	}

	return TRUE;
}


BOOL MSDrawBitmapToRect(HMSDC hDC, HMSBITMAP hMSBITMAP, MSRECT rect, int nAlign)
{
	BOOL bRet = FALSE;
	MSPOINT drawPoint;
	MSSIZE rectSize;
	HMSBITMAP	hDestBITMAP = NULL;
	HMSDC		hMemMSDC = NULL;
	MSSIZE      sizeBitmap;

	if(NULL == hDC || NULL == hMSBITMAP)
	{
		ADIASSERT(hDC != NULL); 
		ADIASSERT(hMSBITMAP != NULL);

		return bRet;
	}
	
	rectSize.cx = rect.right - rect.left;
	rectSize.cy = rect.bottom - rect.top;

	MSGetBitmapDimensionEx(hMSBITMAP, &sizeBitmap);

	if (nAlign == 0)
	{
		drawPoint.x = (rectSize.cx - sizeBitmap.cx)/2;
		drawPoint.y = (rectSize.cy - sizeBitmap.cy)/2;
	}

	hMemMSDC = MSCreateCompatibleDC(hDC);
	MSSelectObject(hMemMSDC, hMSBITMAP);

	bRet = MSBitBlt(hDC, drawPoint.x, drawPoint.y , sizeBitmap.cx, sizeBitmap.cy, hMemMSDC, 0, 0, SRCCOPY);

	MSDeleteDC(hMemMSDC);

	return bRet;
}

BOOL MSDrawBitmapByID(HMSDC hDC, DWORD dwBmpSrcID, MSPOINT* pMSPOINT)
{
	BOOL bRet = FALSE;
	HMSBITMAP hBitMap = NULL;

	if (NULL == hDC || dwBmpSrcID == 0 || NULL == pMSPOINT)
	{
		ADIASSERT(hDC != NULL);
		ADIASSERT(pMSPOINT != NULL);
		ADIASSERT(dwBmpSrcID != 0);
		return bRet;
	}

	hBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwBmpSrcID);
	if (hBitMap != NULL)
	{
		bRet = MSDrawBitmap(hDC, hBitMap, pMSPOINT);
	}

	if (hBitMap != NULL)
	{
		MSDeleteObject((HMSOBJECT)hBitMap);
		hBitMap = NULL;
	}

	return bRet;
}

/*
 nAlign: 0 - Center, 1-left, 2-right
 */
BOOL MSDrawHRectByBitmapIDEx(HMSDC hDC, MSRECT* pMSRECT, DWORD dwLeftBitmapID, DWORD dwMidBitmapID, DWORD dwRightBitmapID, int nAlign)
{
	BOOL bRelt = FALSE;
	HMSBITMAP hLeftBitMap = NULL;
	HMSBITMAP hMidBitMap = NULL;
	HMSBITMAP hRightBitMap = NULL;

	if(NULL == hDC || NULL == pMSRECT)
	{
		ADIASSERT(hDC != NULL); 
		ADIASSERT(pMSRECT != NULL);
		return FALSE;
	}

	hLeftBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwLeftBitmapID);
	ADIASSERT(hLeftBitMap != NULL);

	hMidBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwMidBitmapID);
	ADIASSERT(hMidBitMap != NULL);

	hRightBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwRightBitmapID);
	ADIASSERT(hRightBitMap != NULL);

	if (hLeftBitMap != NULL && hMidBitMap != NULL && hRightBitMap != NULL)
	{
		bRelt = MSDrawHRectByHMSBITMAPEx(hDC, pMSRECT, hLeftBitMap, hMidBitMap, hRightBitMap, nAlign);
	}
	else
	{
		MSPOINT POINT;
		MSRECT rect = *pMSRECT;
		HMSBRUSH hBrush;

		POINT.x = pMSRECT->left;
		POINT.y = pMSRECT->top;
		
		hBrush = MSCreatePatternBrush(hMidBitMap);
		bRelt = MSFillRect(hDC, &rect, hBrush);				
		
		MSDeleteObject(hBrush);
		hBrush = NULL;
	}

	if (hLeftBitMap != NULL)
	{
		MSDeleteObject((HMSOBJECT)hLeftBitMap);
		hLeftBitMap = NULL;
	}

	if (hMidBitMap != NULL)
	{
		MSDeleteObject((HMSOBJECT)hMidBitMap);
		hMidBitMap = NULL;
	}

	if (hRightBitMap != NULL)
	{
		MSDeleteObject((HMSOBJECT)hRightBitMap);
		hRightBitMap = NULL;
	}

	return bRelt;
}

BOOL MSDrawHRectByBitmapID(HMSDC hDC, MSRECT* pMSRECT, DWORD dwLeftBitmapID, DWORD dwMidBitmapID, DWORD dwRightBitmapID)
{
	return MSDrawHRectByBitmapIDEx( hDC, pMSRECT,  dwLeftBitmapID,  dwMidBitmapID,  dwRightBitmapID, 1);
}

/*
 nAlign: 0 - Center, 1-left, 2-right
 */
BOOL MSDrawHRectByHMSBITMAPEx(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmpLeft, HMSBITMAP hbmpMid, HMSBITMAP hbmpRight, int nAlign)
{
	BOOL bRet = FALSE;
	MSRECT rect;
	MSSIZE sizeBitmap;
	HMSBRUSH hbrFill = NULL;
	MSPOINT Point;
	int nYoffset = 0;
	int nCount = 0;
	int i = 0;

	if(NULL == hDC || NULL == pMSRECT || NULL == hbmpLeft || NULL == hbmpMid || NULL == hbmpRight)
	{
		ADIASSERT(hDC != NULL); 
		ADIASSERT(pMSRECT != NULL);
		ADIASSERT(hbmpLeft != NULL);
		ADIASSERT(hbmpMid != NULL); 
		ADIASSERT(hbmpRight != NULL);

		return bRet;
	}
	
	MSGetBitmapDimensionEx(hbmpLeft, &sizeBitmap);	

	if (nAlign == 0)
	{		
		nYoffset = (pMSRECT->bottom -  pMSRECT->top - sizeBitmap.cy) / 2;
	}


	Point.x = pMSRECT->left;
	Point.y = pMSRECT->top + nYoffset;

	bRet = MSDrawBitmap(hDC, hbmpLeft, &Point);	

	if (!bRet)
	{
		return FALSE;
	}
		
	rect.left	 = pMSRECT->left + sizeBitmap.cx;		
	rect.top	 = pMSRECT->top;
	rect.bottom	 = rect.top + sizeBitmap.cy;
		
	MSGetBitmapDimensionEx(hbmpRight, &sizeBitmap);	

	Point.x = pMSRECT->right - sizeBitmap.cx;
	Point.y = pMSRECT->top + nYoffset;

	rect.right = Point.x;							
	if (rect.right < rect.left)
	{
		rect.right = rect.left;
	}
		
	bRet = MSDrawBitmap(hDC, hbmpRight, &Point);

	if (!bRet)
	{
		return FALSE;
	}

	hbrFill = MSCreatePatternBrush(hbmpMid);	

	ADIASSERT(hbrFill != NULL);
	if (hbrFill == NULL)
	{
		return FALSE;
	}
		
	rect.top += nYoffset;
	rect.bottom += nYoffset;
	MSFillRect(hDC, &rect, hbrFill);			

	MSDeleteObject(hbrFill);
	hbrFill = NULL;

	return bRet;
}

BOOL MSFillRectByBmpID(HMSDC hdc, MSRECT *lpRect, DWORD dwBmpID)
{	
	HMSBRUSH hbrFill = NULL;
	MSRECT rect = *lpRect;
	BOOL	bRet = FALSE;
	HMSBITMAP hBitMap = NULL;

	if(NULL == hdc || NULL == lpRect)
	{
		ADIASSERT(hdc != NULL);
		ADIASSERT(lpRect != NULL);
		return bRet;
	}
	
	hBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwBmpID);
	if (hBitMap != NULL)
	{
		hbrFill = MSCreatePatternBrush(hBitMap);
	}
		
	if (hbrFill == NULL)
	{
		return FALSE;
	}	

	MSFillRect(hdc, &rect, hbrFill);

	MSDeleteObject(hbrFill);

	if (hBitMap != NULL)
	{
		MSDeleteObject((HMSOBJECT)hBitMap);
		hBitMap = NULL;
	}

	hbrFill = NULL;
	bRet = TRUE;

	return  bRet;
}

BOOL MSFillCtrlByBmpID(HMSWND hWnd, DWORD dwCtrlID, DWORD dwBackCtrlID, DWORD dwBmpID)
{		
	HMSDC hdcCtrl = NULL;
	MSRECT rectBackCtrl;
	MSRECT rectCtrl;
	MSRECT rectDraw;
	BOOL bRet = FALSE;

	HMSWND hWndBackCtrl = MSGetDlgItem(hWnd, dwBackCtrlID);
	HMSWND hWndCtrl = MSGetDlgItem(hWnd, dwCtrlID);
	
	if (hWndCtrl == NULL || hWndBackCtrl == NULL)
	{
		ADIASSERT(hWndCtrl != NULL);
		ADIASSERT(hWndBackCtrl != NULL);
		return FALSE;
	}

	hdcCtrl = MSGetDC(hWndBackCtrl);
	
	if (hdcCtrl == NULL)
	{
		ADIASSERT(hdcCtrl != NULL);
		return FALSE;
	}

	MSGetWindowRect(hWndBackCtrl, &rectBackCtrl);
	MSGetWindowRect(hWndCtrl, &rectCtrl);

	rectDraw.left = rectCtrl.left - rectBackCtrl.left;
	rectDraw.right = rectCtrl.right - rectBackCtrl.left;
	
	MSGetClientRect(hWndBackCtrl, &rectBackCtrl);
	rectDraw.top = rectBackCtrl.top;
	rectDraw.bottom = rectBackCtrl.bottom;

	MSFillRectByBmpID(hdcCtrl, &rectDraw, dwBmpID);
	MSReleaseDC(hWndBackCtrl, hdcCtrl);
	
	return  bRet;
}

BOOL MSDrawHRectByHMSBITMAP(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmpLeft, HMSBITMAP hbmpMid, HMSBITMAP hbmpRight)
{
	return MSDrawHRectByHMSBITMAPEx( hDC,  pMSRECT,  hbmpLeft,  hbmpMid,  hbmpRight, 1);
}

BOOL MSDrawLine(HMSDC	hdc, MSPOINT PointStart, MSPOINT PointEnd, COLORREF	LineColor, int nWidth )
{
	HMSPEN 		hpenline				= NULL;		
	HMSPEN 		hpenOldpen				= NULL;		

	if(hdc == NULL)
	{
		ADIASSERT(NULL);	
		return FALSE;
	}
	
	if(nWidth >0)
	{
		hpenline = MSCreatePen(PS_SOLID, nWidth, LineColor);	
		ADIASSERT(NULL != hpenline);
	}

	hpenOldpen		= MSSelectObject(hdc, hpenline);


	MSMoveToEx(hdc,PointStart.x, PointStart.y, NULL );
	
	MSLineTo(hdc, PointEnd.x, PointEnd.y);


	MSSelectObject(hdc, hpenOldpen);
	if(hpenline)
	{	
		MSDeleteObject(hpenline);
		hpenline = NULL;
	}

	return TRUE;
}


BOOL MSDrawSettingBackGround(HMSDC hDC, MSPOINT *ptPoint, DWORD dwTopBitmapID, DWORD dwMidBitmapID, DWORD dwButtomBitmapID, int nCount)
{
	BOOL bRet = FALSE;
	HMSDC	hMemMSDC = NULL;
	MSSIZE stSize = {0};
	HMSBITMAP hBitMapTop = NULL;
	HMSBITMAP hBitMapMid = NULL;
	HMSBITMAP hBitMapBottom = NULL;

	if(NULL == hDC || NULL == ptPoint || 0 == nCount)
	{
		ADIASSERT(hDC != NULL); 
		ADIASSERT(ptPoint != NULL);
		ADIASSERT(nCount != 0);
		return bRet;
	}
	
	if(nCount == 2)
	{
		hBitMapTop = AuraLoadPNG(GetInstance(), (LPCTSTR)dwTopBitmapID);
		hBitMapBottom = AuraLoadPNG(GetInstance(), (LPCTSTR)dwButtomBitmapID);
		
		if(NULL == hBitMapTop || NULL == hBitMapBottom)
		{
			ADIASSERT(hBitMapTop!= NULL); 
			ADIASSERT(hBitMapBottom != NULL);
			return bRet;
		}

		memset(&stSize, 0, sizeof(MSSIZE)); 	
		MSGetBitmapDimensionEx(hBitMapTop, &stSize);
		MSDrawBitmap(hDC, hBitMapTop, ptPoint);
		
		ptPoint->y += stSize.cy;
		MSDrawBitmap(hDC, hBitMapBottom, ptPoint);
			
	}
	else
	{
		int ii = 0;

		hBitMapTop = AuraLoadPNG(GetInstance(), (LPCTSTR)dwTopBitmapID);
		hBitMapMid	= AuraLoadPNG(GetInstance(), (LPCTSTR)dwMidBitmapID);
		hBitMapBottom = AuraLoadPNG(GetInstance(), (LPCTSTR)dwButtomBitmapID);
		
		if(NULL == hBitMapTop || NULL == hBitMapMid || NULL == hBitMapBottom)
		{
			ADIASSERT(hBitMapTop!= NULL); 
			ADIASSERT(hBitMapMid != NULL);
			ADIASSERT(hBitMapBottom != NULL);
			return bRet;
		}
		
		memset(&stSize, 0, sizeof(MSSIZE)); 	
		MSGetBitmapDimensionEx(hBitMapTop, &stSize);
		MSDrawBitmap(hDC, hBitMapTop, ptPoint);
		ptPoint->y += stSize.cy;

		memset(&stSize, 0, sizeof(MSSIZE)); 	
		MSGetBitmapDimensionEx(hBitMapMid, &stSize);
		for(ii = 2; ii < nCount; ii++)
		{
			MSDrawBitmap(hDC, hBitMapMid, ptPoint);
			ptPoint->y += stSize.cy;
		}
		
		MSDrawBitmap(hDC, hBitMapBottom, ptPoint);		
	}
	
	MSDeleteObject((HMSOBJECT)hBitMapTop);
	MSDeleteObject((HMSOBJECT)hBitMapMid);
	MSDeleteObject((HMSOBJECT)hBitMapBottom);
	
	return bRet;
}

