/*
*  MS_DrawPublic.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#ifndef	_MS_DRAWPUBLIC_H_
#define	_MS_DRAWPUBLIC_H_

#include "MSWindows.h"
#include "MS_DrawType.h"

#ifdef __cplusplus
extern "C" {
#endif


BOOL MSErasureDialogBG(HMSWND hWnd, HMSDC hDC);

BOOL MSFillRectByBmpID(HMSDC hdc, MSRECT *lpRect, DWORD dwBmpID);

BOOL MSFillCtrlByBmpID(HMSWND hWnd, DWORD dwCtrlID, DWORD dwBackCtrlID, DWORD dwBmpID);

BOOL MSFillRectByColor(HMSDC hdc, MSRECT *lpRect, COLORREF clrFill);

BOOL MSDrawBitmap(HMSDC hDC, HMSBITMAP hMSBITMAP, MSPOINT* pMSPOINT);

BOOL MSDrawBitmapToRect(HMSDC hDC, HMSBITMAP hMSBITMAP, MSRECT rect, int nAlign);

BOOL MSDrawHRectByBitmapIDEx(HMSDC hDC, MSRECT* pMSRECT, DWORD dwLeftBitmapID, DWORD dwMidBitmapID, DWORD dwRightBitmapID, int nAlign);

BOOL MSDrawHRectByBitmapID(HMSDC hDC, MSRECT* pMSRECT, DWORD dwLeftBitmapID, DWORD dwMidBitmapID, DWORD dwRightBitmapID);

BOOL MSDrawBitmapByID(HMSDC hDC, DWORD dwBmpSrcID, MSPOINT* pMSPOINT);

BOOL MSDrawHRectByHMSBITMAP(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmpLeft, HMSBITMAP hbmpMid, HMSBITMAP hbmpRight);

BOOL MSDrawHRectByHMSBITMAPEx(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmpLeft, HMSBITMAP hbmpMid, HMSBITMAP hbmpRight, int nAlign);

BOOL MSDrawVRectByBitmapID(HMSDC hDC, MSRECT* pMSRECT, DWORD dwUpBitmapID, DWORD dwMidBitmapID, DWORD dwDownBitmapID);

BOOL MSDrawVRectByHMSBITMAP(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmpUp, HMSBITMAP hbmpMid, HMSBITMAP hbmpDown);

BOOL MSDrawRoundRectByColor(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE, DWORD dwColor);

BOOL MSDirectDrawRectByColor(HMSDC hDC, MSRECT* pMSRECT, DWORD dwColor);

BOOL MSDrawRoundRectByHMSBRUSH(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE, HMSBRUSH hbr);

BOOL MSDrawTextRoundRectByColor(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE,  DWORD dwBackgroundColor, LPCTSTR lpString, int nCount, UINT uFormat, DWORD dwTxtColor);

BOOL MSDrawTextRoundRectByHMSBRUSH(HMSDC hDC, MSRECT* pMSRECT, MSSIZE* pMSSIZE, HMSBRUSH hbr, LPCTSTR lpString, int nCount, UINT uFormat, DWORD dwTxtColor);

BOOL MSDrawFormateBitmap(HMSDC hDC, MSRECT* pMSRECT, HMSBITMAP hbmp, UINT uFormate);

void MSDrawMoveText(HMSDC hdc, LPMSRECT lprcText, char *pwTextInfo, DWORD dwCurMoveStep, UINT uFormate);

BOOL MSGetStrSize(HMSDC hdc,const char *pStr,LPMSSIZE lpSize);

BOOL MSGetstrIDSSize(HMSDC hdc,DWORD dwstrIDS,LPMSSIZE lpSize);

BOOL MSDrawRoundRectWithOutLineByColor(HMSDC hdc, const MSRECT *lprc,const MSSIZE *lpsz, COLORREF clrInBackground,COLORREF clrOutLine, const int	 nOutLineWidth );

BOOL MSDrawRoundRectWithFrameByColor(HMSDC hdc,const MSRECT *lprc,const MSSIZE *lpsz,COLORREF clrInBackground,COLORREF clrFrame,const int nclrFrameWidth);

BOOL MSDrawLine(HMSDC hdc, MSPOINT PointStart, MSPOINT PointEnd,  COLORREF	LineColor, int nWidth );

BOOL MSDrawLineByColor(HMSDC hdc,MSRECT *lprc,COLORREF Color,int width);
BOOL MSDrawSettingBackGround(HMSDC hDC, MSPOINT *ptPoint, DWORD dwTopBitmapID, DWORD dwMidBitmapID, DWORD dwButtomBitmapID, int nCount);

#ifdef __cplusplus
}
#endif

#endif

