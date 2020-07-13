/*
*  MS_DrawProgress.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawProgress.h"
#include "MS_DrawControl.h"
#include "MS_DrawPublic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//using namespace std;


BOOL MSProgressInit(HMSWND hWnd, DWORD dwCtrlID, int nMini, int nMax, int nCurrentPos)
{
	BOOL	bRet = FALSE;

	if(hWnd == NULL || nMini >nMax || nCurrentPos <nMini || nCurrentPos > nMax)
	{
		ADIASSERT(hWnd != NULL && nMini < nMax && nCurrentPos > nMini && nCurrentPos < nMax);
		return bRet;
	}
	
	MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_SETRANGE, (WPARAM)0, (LPARAM)MAKELPARAM(nMini, nMax));
	MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_SETPOS,   (WPARAM)nCurrentPos, (LPARAM)0);

	bRet = TRUE;
	
	return bRet;
}


BOOL MSProgressSetPos(HMSWND hWnd, DWORD dwCtrlID, int nPos)
{
	BOOL bRet = FALSE;

	if (hWnd == NULL || dwCtrlID == 0 || nPos < 0 )
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 && nPos > 0);
		return bRet;
	}
	
	MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_SETPOS, nPos, 0);
	bRet = TRUE;
	
	return bRet;
}

int MSProgressGetPos(HMSWND hWnd, DWORD dwCtrlID)
{
	if (hWnd == NULL || dwCtrlID == 0  )
	{
		return 0;
	}
	
	return MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_GETPOS, 0, 0);
}


BOOL MSProgressSetStep(HMSWND hWnd, DWORD dwCtrlID, int nStep)
{
	BOOL bRet = FALSE;
	if(hWnd == NULL || dwCtrlID == 0 )
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 );
		return bRet;
	}
	
	MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_SETSTEP, nStep, 0);
	bRet = TRUE;
	
	return bRet;
}


static BOOL MSProgressDraw(  MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, HMSBITMAP hbmpBackgroudLeft, HMSBITMAP hbmpBackgroudMiddle, HMSBITMAP hbmpBackgroudRight, 
																  HMSBITMAP hbmpForegroundLeft, HMSBITMAP hbmpForegroundMiddle, HMSBITMAP hbmpForegroundRight )
{
	MSRECT tempMSRECT;
	MSSIZE tempMSSIZE;
	MSPOINT tempMSPOINT;
	int nCurrentPos;
	int nLeftProGressLocation = 0;
	int nxBackgroudLeft = 0;
	int nxForegroundLeft = 0;
	LPMSNMHDR pLPMSNMHDR = NULL;

	if (pMSNMLVCUSTOMDRAW == NULL)
	{
		return FALSE;
	}
		
	pLPMSNMHDR = (LPMSNMHDR)pMSNMLVCUSTOMDRAW;
	tempMSRECT = pMSNMLVCUSTOMDRAW->nmcd.rc;

	if ( hbmpBackgroudLeft != NULL )
	{
			MSGetBitmapDimensionEx( hbmpBackgroudLeft, &tempMSSIZE );
			nxBackgroudLeft = tempMSSIZE.cx;

			tempMSPOINT.x = tempMSRECT.left;

			tempMSPOINT.y = tempMSRECT.top + ( tempMSRECT.bottom - tempMSRECT.top - tempMSSIZE.cy )/2;

			MSDrawBitmap( pMSNMLVCUSTOMDRAW->nmcd.hdc, hbmpBackgroudLeft, &tempMSPOINT );

			tempMSRECT.left += tempMSSIZE.cx ;
			MSGetBitmapDimensionEx( hbmpForegroundLeft, &tempMSSIZE );
			nxForegroundLeft = tempMSSIZE.cx;
			nLeftProGressLocation = (int)( nxBackgroudLeft - nxForegroundLeft);
	}

	if ( hbmpBackgroudRight != NULL )
	{
			MSGetBitmapDimensionEx( hbmpBackgroudRight, &tempMSSIZE );

			tempMSRECT.right -= tempMSSIZE.cx ;

			tempMSPOINT.x = tempMSRECT.right;

			MSDrawBitmap( pMSNMLVCUSTOMDRAW->nmcd.hdc, hbmpBackgroudRight, &tempMSPOINT );
	}

	if ( hbmpBackgroudMiddle != NULL )
	{
			HMSBRUSH  hBackgroudMiddleBr = MSCreatePatternBrush( hbmpBackgroudMiddle );

			if ( hBackgroudMiddleBr != NULL )
			{
				MSGetBitmapDimensionEx( hbmpBackgroudMiddle, &tempMSSIZE );

				tempMSRECT.top += ( tempMSRECT.bottom - tempMSRECT.top - tempMSSIZE.cy ) / 2;
				tempMSRECT.bottom = tempMSRECT.top + tempMSSIZE.cy;

				MSFillRect( pMSNMLVCUSTOMDRAW->nmcd.hdc, &tempMSRECT ,hBackgroudMiddleBr );

				MSDeleteObject( hBackgroudMiddleBr );
			}
	}

	nCurrentPos = ( int ) MSSendMessage( ( HMSWND ) pLPMSNMHDR->hwndFrom, ( int )PBM_GETPOS,( int ) 0,( int ) 0 ); 

	if ( nCurrentPos > 0 )
	{
			MSSIZE tempMSSIZE1;

			int nMax;

			nMax = ( int ) MSSendMessage( ( HMSWND ) pLPMSNMHDR->hwndFrom, ( int )PBM_GETRANGE, ( int ) 0, ( int ) 0 );

			tempMSRECT = pMSNMLVCUSTOMDRAW->nmcd.rc;
			tempMSRECT.right = ( tempMSRECT.right - tempMSRECT.left ) * nCurrentPos / nMax ;

			MSGetBitmapDimensionEx( hbmpBackgroudLeft, &tempMSSIZE );
			MSGetBitmapDimensionEx( hbmpForegroundRight, &tempMSSIZE1 );

			if ( ( tempMSRECT.right - tempMSRECT.left ) < ( tempMSSIZE.cx + tempMSSIZE1.cx ) )
			{
				tempMSRECT.right = tempMSRECT.left + tempMSSIZE.cx + tempMSSIZE1.cx ;
			}

			if ( hbmpForegroundLeft != NULL )
			{

				MSGetBitmapDimensionEx( hbmpForegroundLeft, &tempMSSIZE );
			
            
				tempMSPOINT.x  =tempMSRECT.left + nLeftProGressLocation;
				tempMSPOINT.y = tempMSRECT.top + ( tempMSRECT.bottom - tempMSRECT.top - tempMSSIZE.cy )/2;

				MSDrawBitmap( pMSNMLVCUSTOMDRAW->nmcd.hdc, hbmpForegroundLeft, &tempMSPOINT );

				tempMSRECT.left += tempMSSIZE.cx  ;	
			}


			if ( hbmpForegroundRight != NULL )
			{
				tempMSRECT.right -= tempMSSIZE1.cx ;

				tempMSPOINT.x = tempMSRECT.right+nLeftProGressLocation;

				MSDrawBitmap( pMSNMLVCUSTOMDRAW->nmcd.hdc, hbmpForegroundRight, &tempMSPOINT );
			}

			if ( hbmpForegroundMiddle != NULL )
			{
				HMSBRUSH hForegroundMiddleBr = MSCreatePatternBrush( hbmpForegroundMiddle );

				if ( hForegroundMiddleBr != NULL )
				{
					MSGetBitmapDimensionEx( hbmpForegroundMiddle, &tempMSSIZE );

					tempMSRECT.top += ( tempMSRECT.bottom - tempMSRECT.top - tempMSSIZE.cy ) / 2;
					tempMSRECT.bottom = tempMSRECT.top + tempMSSIZE.cy;
                    tempMSRECT.left += nLeftProGressLocation;
				   	tempMSRECT.right += nLeftProGressLocation;
					MSFillRect( pMSNMLVCUSTOMDRAW->nmcd.hdc, &tempMSRECT ,hForegroundMiddleBr );

					MSDeleteObject( hForegroundMiddleBr );
				}
			}
	}
	
	return TRUE;
}


LRESULT MSDrawProgressProcByPNG(LPARAM lParam, DWORD dwBackgroudLeftPng, DWORD dwBackgroudMiddlePng, DWORD dwBackgroudRightPng,
										DWORD dwForegroundLeftPng, DWORD dwForegroundMiddlePng, DWORD dwForegroundRightPng)
{
	int nRet = 0;
	MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW = NULL;

	if (lParam == NULL)
	{
		return nRet;
	}

	pMSNMLVCUSTOMDRAW = (MSNMLVCUSTOMDRAW*)lParam;

	switch (pMSNMLVCUSTOMDRAW->nmcd.dwDrawStage)
	{
		case CDDS_PREERASE:
			nRet = CDRF_DODEFAULT;
			break;

		case CDDS_PREPAINT:
			nRet = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			{
				HMSBITMAP hbmpBackgroudLeft = NULL;
				HMSBITMAP hbmpBackgroudMiddle = NULL;
				HMSBITMAP hbmpBackgroudRight = NULL;
				HMSBITMAP hbmpForegroundLeft = AuraLoadPNG(GetInstance(), (LPCTSTR)dwForegroundLeftPng);
				HMSBITMAP hbmpForegroundMiddle = AuraLoadPNG(GetInstance(), (LPCTSTR)dwForegroundMiddlePng);
				HMSBITMAP hbmpForegroundRight = AuraLoadPNG(GetInstance(), (LPCTSTR)dwForegroundRightPng);
				if(dwBackgroudLeftPng != 0)
				{
					 hbmpBackgroudLeft = AuraLoadPNG(GetInstance(), (LPCTSTR)dwBackgroudLeftPng);
					 hbmpBackgroudMiddle = AuraLoadPNG(GetInstance(), (LPCTSTR)dwBackgroudMiddlePng);
					 hbmpBackgroudRight = AuraLoadPNG(GetInstance(), (LPCTSTR)dwBackgroudRightPng);
				}
				
				MSProgressDraw(pMSNMLVCUSTOMDRAW, hbmpBackgroudLeft, hbmpBackgroudMiddle, hbmpBackgroudRight, hbmpForegroundLeft, hbmpForegroundMiddle, hbmpForegroundRight);

				if ( hbmpBackgroudLeft != NULL )
				{
					MSDeleteObject( (HMSOBJECT)hbmpBackgroudLeft );
				}

				if ( hbmpBackgroudMiddle != NULL )
				{
					MSDeleteObject((HMSOBJECT)hbmpBackgroudMiddle);
				}

				if ( hbmpBackgroudRight != NULL )
				{
					MSDeleteObject((HMSOBJECT)hbmpBackgroudRight);
				}

				if ( hbmpForegroundLeft != NULL )
				{
					MSDeleteObject((HMSOBJECT)hbmpForegroundLeft);
				}

				if ( hbmpForegroundMiddle != NULL )
				{
					MSDeleteObject((HMSOBJECT)hbmpForegroundMiddle);
				}

				if ( hbmpForegroundRight != NULL )
				{
					MSDeleteObject((HMSOBJECT)hbmpForegroundRight);
				}
			}

			nRet = CDRF_SKIPDEFAULT;

			break;
	}
	
	return nRet;
}


LRESULT MSProgressDrawProcByBitmapHandle( LPARAM lParam, HMSBITMAP hbmpBackgroudLeft, HMSBITMAP hbmpBackgroudMiddle, HMSBITMAP hbmpBackgroudRight,
										 HMSBITMAP hbmpForegroundLeft, HMSBITMAP hbmpForegroundMiddle, HMSBITMAP hbmpForegroundRight )
{
	int nRet = 0;
	MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW = NULL;

	if (lParam == NULL)
	{
		return nRet;
	}

	pMSNMLVCUSTOMDRAW = ( MSNMLVCUSTOMDRAW* ) lParam;

	switch( pMSNMLVCUSTOMDRAW->nmcd.dwDrawStage )
	{
		case CDDS_PREERASE:
			nRet = CDRF_DODEFAULT;
			break;

		case CDDS_PREPAINT:
			nRet = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			MSProgressDraw( pMSNMLVCUSTOMDRAW, hbmpBackgroudLeft, hbmpBackgroudMiddle, hbmpBackgroudRight, hbmpForegroundLeft, hbmpForegroundMiddle, hbmpForegroundRight );
			nRet = CDRF_SKIPDEFAULT;
			break;
	}

	return nRet;
}

int MSProgressGetPercent(HMSWND hWnd, DWORD dwCtrlID, char* pszPercentStr, int nBufSize)
{
	int		nPos	= -1;
	int		nRange	= -1;

	if (pszPercentStr == NULL || nBufSize <= 0)
	{
		ADIASSERT(pszPercentStr != NULL && nBufSize > 0);
		return nPos;
	}

	nRange = (int)MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_GETRANGE, 0, 0);
	nPos   = (int)MSSendMessage(MSGetDlgItem(hWnd, dwCtrlID), PBM_GETPOS, 0, 0);

	if ((nRange > 0) && (nPos >= 0) && (nPos <= nRange))
	{
		int		nPercent = 0;
		char	szBufM[40] = {0};

		nPercent = (nPos * 100) / nRange;			
		sprintf(szBufM,"%d%%", nPercent);
		MSMultiByteToWideChar(0, 0, (LPCSTR)szBufM, 40, (LPWSTR)pszPercentStr, (nBufSize >> 1) - 2);
	}	
	else
	{
		nPos = -1;
	}
	
	return nPos;
}

