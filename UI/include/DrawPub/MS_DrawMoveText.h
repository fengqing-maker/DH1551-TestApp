/*
*  MS_DrawHMoveText.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#ifndef _MS_DRAWHMOVETEXT_H
#define _MS_DRAWHMOVETEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MS_DrawPublic.h"

typedef struct MSDRAWMOVETEXT
{
	HMSWND m_hWnd;
	WPARAM m_wParam;
	HMSWND m_hControlWnd;
	DWORD  m_dwIdEvent;
	DWORD  m_dwMoveStep;
	WORD   m_wMoveInterval;
	MSRECT m_Rect;
	BOOL   m_bIsUse;
}MsDrawMoveText_s;

BOOL MSDrawHMoveTextInit(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent, WORD wMoveInterval);

BOOL MSDrawHMoveTextIntput(HMSWND hWnd, WPARAM wParam, char *pwTextInfo);

BOOL MSDrawHMoveTextDestroy(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent);

BOOL MSDrawVMoveTextInit(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent, WORD wMoveInterval);

BOOL MSDrawVMoveTextIntput(HMSWND hWnd, WPARAM wParam, char *pwTextInfo);

BOOL MSDrawVMoveTextDestroy(HMSWND hWnd, WPARAM wParam, DWORD  dwIdEvent);


#ifdef __cplusplus
}
#endif

#endif