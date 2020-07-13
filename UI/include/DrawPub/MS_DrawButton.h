/*
*  MS_DrawButton.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#ifndef _MS_MSDRAWBUTTON_H_
#define _MS_MSDRAWBUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MS_DrawType.h"


LRESULT MSButtonDrawProcByHMSBITMAP( LPARAM lParam, HMSBITMAP hbmpFocused, HMSBITMAP hbmpNoFocused,DWORD dwStrID, DWORD dwFocusedTextColor, DWORD dwNoFocusedTextColor, int nTextPosToLeft );


LRESULT MSButtonDrawProcByBitmapID( LPARAM lParam, DWORD dwFocusedBndBmpID, DWORD dwNoFocusedBndBmpID, DWORD dwStrID, DWORD dwFocusedTextColor,DWORD dwNoFocusedTextColor, HMSFONT hFont, int nTextPosToLeft );


LRESULT MSButtonDrawProcByLMRBitmapID(LPARAM lParam, DWORD dwFocusedLeftBndBmpID,  DWORD dwFocusedMidBndBmpID,   DWORD dwFocusedRightBndBmpID, \
													 DWORD dwNoFocusedLeftBndBmpID,DWORD dwNoFocusedMidBndBmpID, DWORD dwNoFocusedRightBndBmpID,\
													 DWORD dwStrID, DWORD dwFocusedTextColor,DWORD dwNoFocusedTextColor, HMSFONT hFont, int nTextPosToLeft);



#ifdef __cplusplus
}
#endif

#endif
