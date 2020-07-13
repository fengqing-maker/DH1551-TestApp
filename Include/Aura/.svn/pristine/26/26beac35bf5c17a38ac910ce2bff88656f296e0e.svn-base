/*
 * DrawAuraSurfaceInterface.h
 *
 *  Created on: 2015-7-19
 *      Author: Demo
 */

#ifndef _DRAWAURASURFACEINTERFACE_H_
#define _DRAWAURASURFACEINTERFACE_H_

#include "MSWindows.h"

#ifdef __cplusplus
extern "C" {
#endif

    unsigned int FillAuraSurfaceColor ( void * pAuraSurface, MSRECT inputMSRECT, unsigned int unColor );
    unsigned int ClearAuraSurfaceColor ( void * pAuraSurface, unsigned int unColor );
    unsigned int DrawAuraSurfaceText ( void * pAuraSurface, HMSFONT hFont, unsigned int unCharSpacing, unsigned int unX, unsigned int unY, char acStr [ ], unsigned int unStrLen, unsigned int unColor );
	unsigned int DrawAuraSurfaceTextMutiLine ( void * pAuraSurface , HMSFONT hFont , unsigned int unCharSpacing , unsigned int unHightSpacing , unsigned int unX , unsigned int unY , char acStr [ ] , unsigned int unStrLen , unsigned int unColor );
	unsigned int GetAuraSurfaceTextWidthAndHeight ( HMSFONT hFont, unsigned int unCharSpacing, char acStr [ ], unsigned int unStrLen, unsigned int & unWidth, unsigned int & unHeight );
	unsigned int GetAuraSurfaceTextWidthAndHeightByDC ( HMSDC hDC , unsigned int unCharSpacing , char acStr [ ] , unsigned int unStrLen , unsigned int & unWidth , unsigned int & unHeight );
	unsigned int GetAuraSurfaceStringWidthAndHeight ( HMSFONT hFont, char acStr [ ], unsigned int unStrLen, unsigned int & unWidth, unsigned int & unHeight );
    unsigned int GetAuraSurfaceStringWidthAndHeightEx ( HMSFONT hFont, char acStr [ ], unsigned int unStrLen, int nLineSpace, int nInterCharSpace, unsigned int & unWidth, unsigned int & unHeight );

	unsigned int GetAuraSurfaceTextCount ( HMSDC hDC , unsigned int unCharSpacing , char acStr [ ] , unsigned int unStrLen , unsigned int unWidth );

    unsigned int DrawAuraSurfaceBitmap ( void * pAuraSurface, HMSBITMAP hBitmap, unsigned int unX, unsigned int unY );
    void SetAuraSurfaceTextSpace ( unsigned int unSpace );

	unsigned int DrawSurfaceText ( ADI_HANDLE hSurface, HMSFONT hFont, unsigned int unX, unsigned int unY, char acStr [ ], unsigned int unStrLen, unsigned int unColor );
	unsigned int FillSurfaceColor ( ADI_HANDLE hSurface, MSRECT inputMSRECT, unsigned int unColor );
	unsigned int GetSurfaceFontWidthAndHeight ( HMSFONT hFont, unsigned int * punWidth, unsigned int * punHeight );
	
#ifdef __cplusplus
}
#endif


#endif /* _DRAWAURASURFACEINTERFACE_H_ */
