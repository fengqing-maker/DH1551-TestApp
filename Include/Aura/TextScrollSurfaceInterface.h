/*
 * TextScrollSurfaceInterface.h
 *
 *  Created on: 2016-2-25
 *      Author: HXC
 */

#ifndef TEXTSCROLLSURFACEINTERFACE_H_
#define TEXTSCROLLSURFACEINTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

	void * CreateTextScrollSurface ( MSRECT screenRECT , unsigned int unFormat , unsigned int unAlphaValue );
	unsigned int DeleteTextScrollSurface ( void * pTextScrollSurface );

	unsigned int SetTextScrollSurfaceBackColor ( void * pTextScrollSurface, ARGB bkColor );
	unsigned int SetTextScrollSurfaceBackBitmap ( void * pTextScrollSurface, HMSBITMAP hbkBitmap );
	unsigned int SetTextScrollSurfaceBackBrush ( void * pTextScrollSurface, HMSBRUSH hbkBrush );
	unsigned int ShowTextScrollSurfaceText(void * pTextScrollSurface, unsigned int unSpeed, HMSFONT hFont, unsigned int unCharSpacing, ARGB textColor, char acShowStr[], unsigned int unShowStrLen);
	unsigned int StopTextScrollSurfaceText ( void * pTextScrollSurface );
	
#ifdef __cplusplus
}
#endif

#endif /* TEXTSCROLLSURFACEINTERFACE_H_ */
