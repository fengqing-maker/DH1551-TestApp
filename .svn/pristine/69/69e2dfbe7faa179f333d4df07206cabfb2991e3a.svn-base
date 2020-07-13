/*
*  MS_DrawScrollBar.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawScrollBar.h"
#include "MS_DrawPublic.h"

BOOL MSDrawScrollBarBackGround(HMSDC hMSDC, MSRECT* pMSRECT, HMSBITMAP hbmpUp, HMSBITMAP hbmpBackground, HMSBITMAP hbmpDown);
BOOL MSDrawScrollBarHumb(HMSDC hMSDC, MSRECT* pMSRECT, HMSBITMAP hbmpThumbUp, HMSBITMAP hbmpThumbMid, HMSBITMAP hbmpThumbDown);


LRESULT MSVScrollBarDrawProcByBtimapHandle( LPARAM lParam, HMSBITMAP hbmpUp, HMSBITMAP hbmpMid,  HMSBITMAP hbmpDown, HMSBITMAP hbmpThumbUp,HMSBITMAP hbmpThumbMid,HMSBITMAP hbmpThumbDown)
{
	int nRet = CDRF_SKIPDEFAULT;
	LPMSNMCUSTOMDRAW  pLPMSNMCUSTOMDRAW = NULL;

	if (lParam == NULL)
	{
		return nRet;
	}

	pLPMSNMCUSTOMDRAW = ( LPMSNMCUSTOMDRAW ) lParam;

	switch( pLPMSNMCUSTOMDRAW->dwItemSpec )
	{
		case SBCD_BKGND:	
			{
				if ((hbmpMid != NULL) && (hbmpUp != NULL) && (hbmpDown != NULL))
				{
					MSDrawScrollBarBackGround(pLPMSNMCUSTOMDRAW->hdc, &pLPMSNMCUSTOMDRAW->rc, hbmpUp, hbmpMid, hbmpDown);
				}

				nRet = CDRF_SKIPDEFAULT;
			}
			break;

		case SBCD_CHANNEL:	
			{
				if ((hbmpMid != NULL) && (hbmpUp != NULL) && (hbmpDown != NULL))
				{
					MSDrawScrollBarBackGround(pLPMSNMCUSTOMDRAW->hdc, &pLPMSNMCUSTOMDRAW->rc, NULL, hbmpMid, NULL);
				}

				nRet = CDRF_SKIPDEFAULT;
			}
			break;

		case SBCD_THUMB:	
			{
				MSDrawScrollBarHumb(pLPMSNMCUSTOMDRAW->hdc, &pLPMSNMCUSTOMDRAW->rc, hbmpThumbUp, hbmpThumbMid, hbmpThumbDown);
				
				nRet = CDRF_SKIPDEFAULT;
			}
			break;

		default:
			break;
	}

	return nRet;
}

LRESULT MSVScrollBarDrawProcByLPLUMDBITMAP(LPARAM lParam, LPMSLUMDBITMAP lpBackground, LPMSLUMDBITMAP lpThumb)
{

	if ((lpBackground == NULL) || (lpThumb == NULL))
	{
		ADIASSERT((lpBackground != NULL) && (lpThumb != NULL));
		return 0;
	}
	
	return MSVScrollBarDrawProcByBtimapHandle( lParam, lpBackground->m_hbmpUp, lpBackground->m_hbmpMid, lpBackground->m_hbmpDown, lpThumb->m_hbmpUp,lpThumb->m_hbmpMid,lpThumb->m_hbmpDown);
}

BOOL MSDrawScrollBarBackGround(HMSDC hMSDC, MSRECT* pMSRECT, HMSBITMAP hbmpUp, HMSBITMAP hbmpMid, HMSBITMAP hbmpDown)
{
	MSPOINT tempMSPOINT;
	MSSIZE  tempMSSIZE;
	MSRECT  tempMSRECT;
	HMSBRUSH	hMSBRUSH = NULL;

	if ((hMSDC == NULL) || (pMSRECT == NULL) || (hbmpMid == NULL))
	{
		ADIASSERT((hMSDC != NULL) && (pMSRECT != NULL) && (hbmpMid != NULL));
		return FALSE;
	}

	if ( hbmpUp != NULL )
	{
		tempMSPOINT.x = pMSRECT->left;
		tempMSPOINT.y = pMSRECT->top;

		MSDrawBitmap( hMSDC, hbmpUp, &tempMSPOINT );
	}

	if ( hbmpDown != NULL )
	{
		MSGetBitmapDimensionEx( hbmpDown, &tempMSSIZE ); 

		tempMSPOINT.x = pMSRECT->left;
		tempMSPOINT.y = pMSRECT->bottom - tempMSSIZE.cy;

		MSDrawBitmap( hMSDC, hbmpDown, &tempMSPOINT );
	}

	if (hbmpMid != NULL)
	{
		hMSBRUSH = MSCreatePatternBrush(hbmpMid);
		ADIASSERT(hMSBRUSH != NULL);

		tempMSRECT = *pMSRECT;
		MSFillRect(hMSDC, &tempMSRECT, hMSBRUSH);

		MSDeleteObject(hMSBRUSH);
		hMSBRUSH = NULL;
	}

	return TRUE;
}


BOOL MSDrawScrollBarHumb( HMSDC hMSDC,MSRECT* pMSRECT, HMSBITMAP hbmpThumbUp, HMSBITMAP hbmpThumbMid, HMSBITMAP hbmpThumbDown )
{
	MSRECT tempMSRECT;
	MSSIZE tempMSSIZE;

	if ((hMSDC==NULL) || (pMSRECT==NULL) || (hbmpThumbMid==NULL))
	{	
		ADIASSERT((hMSDC != NULL) && (pMSRECT != NULL) && (hbmpThumbMid != NULL));
		return FALSE;
	}

	tempMSRECT = *pMSRECT;
	MSGetBitmapDimensionEx( hbmpThumbMid, &tempMSSIZE ); 

	if(tempMSSIZE.cx <(tempMSRECT.right - tempMSRECT.left))
	{
		tempMSRECT.left += ( tempMSRECT.right - tempMSRECT.left - tempMSSIZE.cx ) /2 + 2;
		tempMSRECT.right = tempMSRECT.left + tempMSSIZE.cx;
	}
		
	MSDrawVRectByHMSBITMAP(hMSDC, &tempMSRECT, hbmpThumbUp, hbmpThumbMid, hbmpThumbDown);

	return TRUE;
}
