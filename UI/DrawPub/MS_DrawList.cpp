/*
*  MS_DrawList.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawList.h"
#include "MS_DrawControl.h"


BOOL MSDrawListInit(HMSWND hWnd, DWORD dwCtrlID, int nItemCount, int nPageItemCount, COLORREF dwBackColor )
{   
	BOOL bRet = FALSE;
	MSRECT      Rect;
	MSLV_ITEM   LVItem;

	HMSWND      hCtrlWnd = NULL;
	int         nIndex   = 0;

	if (hWnd == NULL || dwCtrlID == 0 || nPageItemCount <= 0)
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 && nPageItemCount > 0);

		return bRet;
	}

	hCtrlWnd  = MSGetDlgItem( hWnd, dwCtrlID );

	if ( hCtrlWnd != NULL )
	{
		MSListView_DeleteAllItems( hCtrlWnd );
		MSGetClientRect(hCtrlWnd, &Rect);
		MSListView_SetBkColor( hCtrlWnd ,dwBackColor );
		MSListView_SetIconSpacing(hCtrlWnd, Rect.right - Rect.left, (Rect.bottom - Rect.top) / nPageItemCount);
			
		LVItem.iSubItem = 0;
		LVItem.state = 0;
		LVItem.stateMask = 0;
		LVItem.mask = LVIF_TEXT;
		LVItem.pszText = LPSTR_TEXTCALLBACK;

		for (nIndex = 0; nIndex < nItemCount; nIndex++)
		{ 
			LVItem.iItem = nIndex;

			if (MSListView_InsertItem(hCtrlWnd, &LVItem) == -1)
			{
				break;
			}
		}

		if (nIndex == nItemCount)
		{
			bRet = TRUE;
		}
	}

	return bRet;
}


BOOL MSDrawListInitEx(HMSWND hWnd, DWORD dwCtrlID, int nItemCount, int nPageLineCount, int nColumnCount, COLORREF dwBackColor)
{
	BOOL bRet = FALSE;

	MSRECT      Rect;
	MSLV_ITEM   LVItem;
	HMSWND      hCtrlWnd = NULL;
	int         nIndex = 0;

	if (hWnd == NULL || dwCtrlID == 0 && nPageLineCount <= 0 && nColumnCount <= 0)
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 && nPageLineCount > 0 && nColumnCount > 0);
		return bRet;
	}
		

	hCtrlWnd  = MSGetDlgItem( hWnd, dwCtrlID );

	if ( hCtrlWnd != NULL )
	{
		MSListView_DeleteAllItems( hCtrlWnd );
		MSGetClientRect(hCtrlWnd, &Rect);
		MSListView_SetBkColor( hCtrlWnd ,dwBackColor );
		MSListView_SetIconSpacing(hCtrlWnd, (Rect.right - Rect.left - 18) / nColumnCount, (Rect.bottom - Rect.top) / nPageLineCount);
			
		LVItem.iSubItem = 0;
		LVItem.state = 0;
		LVItem.stateMask = 0;
		LVItem.mask = LVIF_TEXT;
		LVItem.pszText = LPSTR_TEXTCALLBACK;

		for (nIndex = 0; nIndex < nItemCount; nIndex++)
		{ 
			LVItem.iItem = nIndex;

			if (MSListView_InsertItem(hCtrlWnd, &LVItem) == -1)
			{
				break;
			}
	   }

		if (nIndex == nItemCount)
		{
			bRet = TRUE;
		}
	}

	return bRet;
}

BOOL MSDrawListInitBySize(HMSWND hWnd, DWORD dwCtrlID, int nItemCount, DWORD dwBkColor, MSSIZE* pSize)
{
	BOOL bRet = FALSE;

	MSRECT      Rect;
	MSLV_ITEM   LVItem;
	HMSWND      hCtrlWnd = NULL;
	int         nIndex = 0;

	if (hWnd != NULL && dwCtrlID != 0 && pSize != NULL)
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 && pSize != NULL);
		return bRet;
	}

	hCtrlWnd  = MSGetDlgItem( hWnd, dwCtrlID );

	if ( hCtrlWnd != NULL )
	{
		MSListView_DeleteAllItems( hCtrlWnd );
		MSGetClientRect(hCtrlWnd, &Rect);
		MSListView_SetBkColor( hCtrlWnd ,dwBkColor );
		MSListView_SetIconSpacing( hCtrlWnd, pSize->cx, pSize->cy);
			
		LVItem.iSubItem		= 0;
		LVItem.state		= 0;
		LVItem.stateMask	= 0;
		LVItem.mask			= LVIF_TEXT;
		LVItem.pszText		= LPSTR_TEXTCALLBACK;

		for (nIndex = 0; nIndex < nItemCount; nIndex++)
		{ 
			LVItem.iItem = nIndex;

			if (MSListView_InsertItem(hCtrlWnd, &LVItem) == -1)
			{
				break;
			}
		}

		if (nIndex == nItemCount)
		{
			bRet = TRUE;
		}
	}

	return bRet;
}


BOOL MSDrawListInsertItem(HMSWND hWnd, DWORD dwCtrlID, int nStartItem, int nEndItem)
{
	BOOL bRe = TRUE;
	int	ii;
	HMSWND hCtrlWnd = NULL;
	MSLV_ITEM   LV_ITEM ;

	LV_ITEM.iSubItem = 0;
	LV_ITEM.state = 0;
	LV_ITEM.stateMask = 0;
	LV_ITEM.mask = LVIF_TEXT;
	LV_ITEM.pszText = LPSTR_TEXTCALLBACK;

	hCtrlWnd = MSGetDlgItem( hWnd, dwCtrlID );

	for ( ii = nStartItem; ii <= nEndItem; ii++ )
	{ 
		LV_ITEM.iItem = ii;

		if (MSListView_InsertItem(hCtrlWnd, &LV_ITEM) == -1)
		{
			bRe = FALSE;
			break;
		}
	}

	return bRe;
}

 
BOOL MSDrawListInsertOneItem(HMSWND hWnd, DWORD dwCtrlID)
{
	MSLV_ITEM   LV_ITEM;
	HMSWND hCtrlWnd = NULL;

	ADIASSERT( hWnd != NULL );
	

	hCtrlWnd = MSGetDlgItem( hWnd, dwCtrlID );

	ADIASSERT( hCtrlWnd != NULL);

	LV_ITEM.iSubItem = 0;
	LV_ITEM.state = 0;
	LV_ITEM.stateMask = 0;
	LV_ITEM.mask = LVIF_TEXT;
	LV_ITEM.pszText = LPSTR_TEXTCALLBACK;
	LV_ITEM.iItem = 0;

	MSListView_InsertItem(MSGetDlgItem(hWnd, dwCtrlID), &LV_ITEM);


	return TRUE;
}



BOOL MSDrawListInsertOneFocusEnsureVisibleItem(HMSWND hWnd, DWORD dwCtrlID, int nIndex)
{
	BOOL bRe = TRUE;
	MSLV_ITEM   LV_ITEM ;
	HMSWND hLV = NULL;

	hLV = MSGetDlgItem(hWnd,dwCtrlID);

	LV_ITEM.iSubItem = 0;
	LV_ITEM.state = 0;
	LV_ITEM.stateMask = 0;
	LV_ITEM.mask = LVIF_TEXT;
	LV_ITEM.pszText = LPSTR_TEXTCALLBACK;
	LV_ITEM.iItem = nIndex;

	if (MSListView_InsertItem(hLV, &LV_ITEM) == -1)
	{
		bRe = FALSE;
		return bRe;
	}

	MSListView_SetItemState( hLV, nIndex, LVIS_FOCUSED, LVIS_FOCUSED);

	bRe = MSListView_EnsureVisible( hLV, nIndex, FALSE);

	return bRe;
}


BOOL MSDrawListInsertToEndListFocusEnsureVisibleItem(HMSWND hWnd, DWORD dwCtrlID)
{
	BOOL bRe = TRUE;
	MSLV_ITEM   LV_ITEM ;
	HMSWND hLV = NULL;
	int nIndex = 0;

	hLV = MSGetDlgItem(hWnd,dwCtrlID);

	nIndex = MSListView_GetItemCount(hLV);

	LV_ITEM.iSubItem = 0;
	LV_ITEM.state = 0;
	LV_ITEM.stateMask = 0;
	LV_ITEM.mask = LVIF_TEXT;
	LV_ITEM.pszText = LPSTR_TEXTCALLBACK;
	LV_ITEM.iItem = nIndex;

	if (MSListView_InsertItem(hLV, &LV_ITEM) == -1)
	{
		bRe = FALSE;
		return bRe;
	}

	MSListView_SetItemState( hLV, nIndex, LVIS_FOCUSED, LVIS_FOCUSED);

	bRe = MSListView_EnsureVisible( hLV, nIndex, FALSE);

	return bRe;
}

BOOL MSDrawListInitLVItem(HMSWND hWnd, DWORD dwCtrlID, int nCount)
{
	HMSWND hCtrlWnd = NULL;
	MSLVITEM	item;
	int			i;
	BOOL bRet = FALSE;

	ADIASSERT(hWnd != NULL);
	hCtrlWnd = MSGetDlgItem(hWnd, dwCtrlID);
	if (hCtrlWnd != NULL)
	{
		MSListView_DeleteAllItems(hCtrlWnd);
		
		item.mask       = LVIF_STATE | LVIF_TEXT;
		item.pszText 	= LPSTR_TEXTCALLBACK;
		item.state    	= 0;      
		item.stateMask  = 0;
		item.iSubItem   = 0;
		for(i = 0; i < nCount; i++)
		{
			item.iItem = i;
			if(MSListView_InsertItem(hCtrlWnd, &item) == -1)
			{
				break;
			}
		}

		if (i == nCount)
		{
			bRet = TRUE;
		}
	}

	return bRet;
}



int MSDrawListGetIndexFocusItem(HMSWND hWnd, DWORD dwCtrlID)
{
	HMSWND hCtrlWnd = NULL;

	int nFocusLVItem = -1;

	ADIASSERT( hWnd != NULL );

	hCtrlWnd = MSGetDlgItem( hWnd, dwCtrlID );

	if (NULL != hCtrlWnd)
	{
		nFocusLVItem = MSListView_GetNextItem(hCtrlWnd, -1, LVNI_FOCUSED);
	}

	return nFocusLVItem;
}

BOOL MSDrawListSetItemFocused(HMSWND hWnd, DWORD dwCtrlID, int nIndex)
{
	BOOL bRet = FALSE;
	HMSWND hCtrlWnd = NULL;

	int nFocusLVItem = -1;

	ADIASSERT( hWnd != NULL );

	hCtrlWnd = MSGetDlgItem( hWnd, dwCtrlID );

	if (NULL != hCtrlWnd)
	{
		MSListView_SetItemState(hCtrlWnd, nIndex, LVNI_FOCUSED, LVNI_FOCUSED);
		MSListView_EnsureVisible(hCtrlWnd, nIndex, FALSE);
		bRet = TRUE;
	}

	return bRet;
}


BOOL MSDrawListReDrawItem(HMSWND hWnd, DWORD dwCtrlID, int iFirst, int iLast)
{
	HMSWND hCtrlWnd = NULL;
	BOOL bRet = FALSE;

	ADIASSERT( hWnd != NULL );

	hCtrlWnd = MSGetDlgItem( hWnd, dwCtrlID );

	if (NULL != hCtrlWnd)
	{
		bRet = MSListView_RedrawItems(hCtrlWnd, iFirst, iLast);
	}
	
	return bRet;
}

int MSDrawListGetFocusItemIndex(HMSWND hWnd, DWORD dwCtrlID)
{
	int nItemCount = 0;
	int i = 0;
	HMSWND hCtrlWnd = NULL;
	
	hCtrlWnd = MSGetDlgItem( hWnd, dwCtrlID );

	nItemCount = MSListView_GetItemCount(hCtrlWnd);

	for(i = 0; i < nItemCount; i++) 
	{ 
		if(MSListView_GetItemState(hCtrlWnd, i, LVNI_FOCUSED) == LVNI_FOCUSED ) 
		{ 
			return i;
		} 
	} 

	return -1;
}

int MSDrawListGetItemCount(HMSWND hWnd, DWORD dwCtrlID)
{
	return MSListView_GetItemCount(MSGetDlgItem(hWnd, dwCtrlID));
}

