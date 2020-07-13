/*
*  MS_DrawScrollBar.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#ifndef _MS_DRAWSCROLLBAR_H_
#define _MS_DRAWSCROLLBAR_H_

#include "MS_DrawType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
LRESULT MSVScrollBarDrawProcByBtimapHandle(LPARAM lParam,HMSBITMAP hbmpUp,HMSBITMAP hbmpBackground,HMSBITMAP hbmpDown,HMSBITMAP hbmpThumbUp,HMSBITMAP hbmpThumbMid,HMSBITMAP hbmpThumbDown);

LRESULT MSVScrollBarDrawProcByLPLUMDBITMAP(LPARAM lParam, LPMSLUMDBITMAP lpBackground, LPMSLUMDBITMAP lpThumb);


#ifdef __cplusplus
}
#endif

#endif
