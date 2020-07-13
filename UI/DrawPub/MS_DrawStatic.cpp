/*
*  MS_DrawStatic.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#include "MSWindows.h"
#include "MS_DrawStatic.h"


BOOL MSLoadBitmapToStatic( HMSWND hMSWND, DWORD dwControlID, HMSBITMAP hBitmap )
{
	BOOL bRet = FALSE;
	HMSWND hCtrlWND = NULL;

	if (hMSWND == NULL || dwControlID == 0 || hBitmap == 0)
	{
		ADIASSERT(hMSWND != NULL && dwControlID != 0 && hBitmap != 0);

		return bRet;
	}	

	hCtrlWND = MSGetDlgItem( hMSWND, dwControlID );

	if ( hCtrlWND != NULL )
	{
		MSSendMessage( hCtrlWND, STM_SETIMAGE, IMAGE_BITMAP, hBitmap );

		bRet = TRUE;
	}
	

	return bRet;
}

