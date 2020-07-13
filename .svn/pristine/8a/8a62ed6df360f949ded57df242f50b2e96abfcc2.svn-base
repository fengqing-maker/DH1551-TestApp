/*
*  MS_DrawList.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#ifndef	_MS_MSDRAWLIST_H_
#define	_MS_MSDRAWLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

BOOL MSDrawListInit(HMSWND hWnd, DWORD dwCtrlID, int nItemCount, int nPageItemCount, COLORREF dwBackColor ); 

BOOL MSDrawListInitEx(HMSWND hWnd, DWORD dwCtrlID, int nItemCount, int nPageLineCount, int nColumnCount, COLORREF dwBackColor);

BOOL MSDrawListInitBySize(HMSWND hWnd, DWORD dwCtrlID, int nItemCount, COLORREF dwBkColor, MSSIZE* pSize);

BOOL MSDrawListInsertItem(HMSWND hWnd, DWORD dwCtrlID, int nStartItem, int nEndItem);

BOOL MSDrawListInsertOneItem(HMSWND hWnd, DWORD dwCtrlID);

BOOL MSDrawListInsertOneFocusEnsureVisibleItem(HMSWND hWnd, DWORD dwCtrlID, int nIndex);

BOOL MSDrawListInsertToEndListFocusEnsureVisibleItem(HMSWND hWnd, DWORD dwCtrlID);

int  MSDrawListGetIndexFocusItem(HMSWND hWnd, DWORD dwCtrlID);

BOOL MSDrawListSetItemFocused(HMSWND hWnd, DWORD dwCtrlID, int nIndex);

int MSDrawListGetFocusItemIndex(HMSWND hWnd, DWORD dwCtrlID);

int MSDrawListGetItemCount(HMSWND hWnd, DWORD dwCtrlID);

BOOL MSDrawListReDrawItem(HMSWND hWnd, DWORD dwCtrlID, int iFirst, int iLast);

#ifdef __cplusplus
}
#endif

#endif

