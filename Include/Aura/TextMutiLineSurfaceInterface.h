

#ifndef TEXTMUTILINESURFACEINTERFACE_H_
#define TEXTMUTILINESURFACEINTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

	void * CreateTextMutiLineSurface ( MSRECT screenRECT , unsigned int unFormat , unsigned int unAlphaValue );
	unsigned int DeleteTextMutiLineSurface ( void * pTextScrollSurface );

	unsigned int SetTextMutiLineSurfaceBackColor ( void * pTextMutiLineSurface , ARGB bkColor );
	unsigned int SetTextMutiLineSurfaceBackBitmap ( void * pTextMutiLineSurface , HMSBITMAP hbkBitmap );
	unsigned int SetTextMutiLineSurfaceBackBrush ( void * pTextMutiLineSurface , HMSBRUSH hbkBrush );
	unsigned int ShowTextMutiLineSurfaceText ( void * pTextMutiLineSurface , HMSFONT hFont , unsigned int unCharSpacing , unsigned int unHightSpacing , ARGB textColor , char acShowStr [ ] , unsigned int unShowStrLen , unsigned int unXOffset , unsigned int unYOffset , MSRECT inputTetxRECT );
	unsigned int StopTextMutiLineSurfaceText ( void * pTextMutiLineSurface );

#ifdef __cplusplus
}
#endif

#endif /* #define TEXTMUTILINESURFACEINTERFACE_H_
*/