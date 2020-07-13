/*
*  MS_DrawButton.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawButton.h"
#include "MS_DrawControl.h"
#include "MS_DrawPublic.h"
#include "MS_DrawButton.h"

static LRESULT MSDrawButtonText(LPMSDRAWITEMSTRUCT pstDrawItem, const char * szText, int nTextPosToLeft)
{
	if (NULL == pstDrawItem || szText == NULL)
	{
		ADIASSERT(NULL != pstDrawItem && szText != NULL);
		return 0;
	}

	if ( nTextPosToLeft < 0 )
	{
		MSDrawText(pstDrawItem->hDC, (LPCTSTR)szText, MSwcslen(szText), &pstDrawItem->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	else 
	{
		MSRECT rect = pstDrawItem->rcItem;
			
		rect.left += nTextPosToLeft;

		MSDrawText(pstDrawItem->hDC, (LPCTSTR)szText, MSwcslen(szText), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	
	return 0;
}


LRESULT MSButtonDrawProcByHMSBITMAP( LPARAM lParam, HMSBITMAP hbmpFocused, HMSBITMAP hbmpNoFocused,DWORD dwStrID,  DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, int nTextPosToLeft )
{
	char szText[64];
	DWORD dwPrevColor = 0;
	MSPOINT point;
	LPMSDRAWITEMSTRUCT pstDrawItem = (LPMSDRAWITEMSTRUCT)lParam;
	
	if ( NULL == lParam || NULL == hbmpFocused || NULL == hbmpNoFocused )
	{
		ADIASSERT(NULL != lParam && NULL != hbmpFocused && NULL != hbmpNoFocused);

		return 0;
	}
 
    memset( szText, 0, sizeof(szText) );
        
	if ( ( pstDrawItem->itemState & ODS_FOCUS ) == ODS_FOCUS ) 	
	{		
		dwPrevColor = MSSetTextColor(pstDrawItem->hDC, dwFocusedTextColor);
		if ( NULL != hbmpFocused )
		{
			memset(&point, 0, sizeof(MSPOINT));
			point.x = pstDrawItem->rcItem.left;
			point.y = pstDrawItem->rcItem.top;
			MSDrawBitmap( pstDrawItem->hDC, hbmpFocused, &point );
		}
	}
	else
	{				
		dwPrevColor = MSSetTextColor(pstDrawItem->hDC, dwNoFocusedTextColor);
		if ( NULL != hbmpNoFocused )
		{
			memset(&point, 0, sizeof(MSPOINT));
			point.x = pstDrawItem->rcItem.left;
			point.y = pstDrawItem->rcItem.top;
			MSDrawBitmap( pstDrawItem->hDC, hbmpNoFocused, &point );
		}
	}

	if (MSLoadString(GetInstance(), dwStrID, (LPTSTR)szText, sizeof(szText) >> 1) != FALSE)
	{
		MSDrawButtonText(pstDrawItem, szText, nTextPosToLeft);
	}
		
	MSSetTextColor( pstDrawItem->hDC, dwPrevColor );
	
	return 0;
}


LRESULT MSButtonDrawProcByBitmapID( LPARAM lParam, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, DWORD dwStrID, DWORD dwFocusedTextColor,DWORD dwNoFocusedTextColor, HMSFONT hFont, int nTextPosToLeft )
{
	HMSBITMAP hBitMap = NULL;
	char szText[64];
	DWORD dwPrevColor = 0;
	MSPOINT point;
	LPMSDRAWITEMSTRUCT pstDrawItem = (LPMSDRAWITEMSTRUCT)lParam;

	if(NULL == lParam || NULL == dwFocusedBndBmpID || NULL == dwNoFocusedBndBmpID)
	{
		ADIASSERT( dwFocusedBndBmpID != 0 && dwNoFocusedBndBmpID != 0 );
		ADIASSERT(NULL != lParam);

		return 0;
	}
	
	memset(szText,0,sizeof(szText));
        
	if ( ( pstDrawItem->itemState & ODS_FOCUS ) == ODS_FOCUS ) 	
	{		
		dwPrevColor = MSSetTextColor( pstDrawItem->hDC, dwFocusedTextColor );

		memset(&point, 0, sizeof(MSPOINT));

		point.x = pstDrawItem->rcItem.left;
		point.y = pstDrawItem->rcItem.top;

		hBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwFocusedBndBmpID);
		if (hBitMap != NULL)
		{
			MSDrawBitmap(pstDrawItem->hDC, hBitMap, &point);
		}
	}
	else
	{				
		dwPrevColor = MSSetTextColor( pstDrawItem->hDC, dwNoFocusedTextColor );

		memset(&point, 0, sizeof(MSPOINT));

		point.x = pstDrawItem->rcItem.left;
		point.y = pstDrawItem->rcItem.top;
		hBitMap = AuraLoadPNG(GetInstance(), (LPCTSTR)dwNoFocusedBndBmpID);
		if (hBitMap != NULL)
		{
			MSDrawBitmap(pstDrawItem->hDC, hBitMap, &point);
		}
	}
    
    MSSelectObject(pstDrawItem->hDC, hFont);

	if (MSLoadString(GetInstance(), dwStrID, (LPTSTR)szText, sizeof(szText) >> 1) != FALSE)
	{
		MSDrawButtonText(pstDrawItem, szText, nTextPosToLeft);
	}

	MSSetTextColor( pstDrawItem->hDC, dwPrevColor );
	

	if (hBitMap != NULL)
	{
		MSDeleteObject((HMSOBJECT)hBitMap);
		hBitMap = NULL;
	}

	return 0;
}


LRESULT MSButtonDrawProcByLMRBitmapID( LPARAM lParam, DWORD dwFocusedLeftBndBmpID, DWORD dwFocusedMidBndBmpID, 
									                  DWORD dwFocusedRightBndBmpID,DWORD dwNoFocusedLeftBndBmpID, 
									                  DWORD dwNoFocusedMidBndBmpID,DWORD dwNoFocusedRightBndBmpID, 
									                  DWORD dwStrID,               DWORD dwFocusedTextColor, 
													  DWORD dwNoFocusedTextColor,  HMSFONT hFont, int nTextPosToLeft)
{
	char szText[64];	
	DWORD dwPrevColor = 0;
	HMSBITMAP hBmpLeft = NULL;
	HMSBITMAP hBmpMid = NULL;
	HMSBITMAP hBmpRight = NULL;
	LPMSDRAWITEMSTRUCT pstDrawItem = (LPMSDRAWITEMSTRUCT)lParam;

	if (NULL == lParam || hFont == NULL )
	{
		ADIASSERT(NULL != lParam && hFont != NULL);
		return 0;
	}
	
	memset(szText,0,sizeof(szText));
        
	if ( ( pstDrawItem->itemState & ODS_FOCUS ) == ODS_FOCUS ) 	
	{		
		dwPrevColor = MSSetTextColor( pstDrawItem->hDC, dwFocusedTextColor );
		MSDrawHRectByBitmapID( pstDrawItem->hDC, &pstDrawItem->rcItem, dwFocusedLeftBndBmpID, dwFocusedMidBndBmpID, dwFocusedRightBndBmpID);
	}
	else
	{				
		dwPrevColor = MSSetTextColor( pstDrawItem->hDC, dwNoFocusedTextColor );
		MSDrawHRectByBitmapID( pstDrawItem->hDC, &pstDrawItem->rcItem, dwNoFocusedLeftBndBmpID, dwNoFocusedMidBndBmpID, dwNoFocusedRightBndBmpID);
	}
		
	MSSelectObject(pstDrawItem->hDC, hFont);

	if (MSLoadString(GetInstance(), dwStrID, (LPTSTR)szText, sizeof(szText) >> 1) != FALSE)
	{
		MSDrawButtonText(pstDrawItem, szText, nTextPosToLeft);
	}

	MSSetTextColor( pstDrawItem->hDC, dwPrevColor );
	
	return 0;
}
