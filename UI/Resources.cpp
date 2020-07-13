

#include "Aura.h"
#include "AuraWindows.h"
#include "Resources.h"
#include "AuraDesktop.h"
#include "adi_typedef.h"
#include "AuraRC.h"
#include "MS_DrawControl.h"

HMSFONT g_hFont32 = NULL;
HMSFONT g_hFont24 = NULL;
HMSFONT g_hFont16 = NULL;

HMSFONT Get32Font( )
{
	if ( g_hFont32 == NULL )
	{
		g_hFont32 = MSCreateFont( 24, 12, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH | FF_MODERN, ( LPCTSTR )"CFNT0" );
	}

	return g_hFont32;
}

HMSFONT Get24Font( )
{
	if ( g_hFont24 == NULL )
	{
		g_hFont24 = MSCreateFont( 24, 12, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH | FF_MODERN, ( LPCTSTR )"CFNT1" );
	}

	return g_hFont24;
}

HMSFONT Get16Font( )
{
	if ( g_hFont16 == NULL )
	{
		g_hFont16 = MSCreateFont(24, 12, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH | FF_MODERN, (LPCTSTR)"CFNT2");
	}

	return g_hFont16;
}

int GetUIDefinition(void)
{
	return UI_MODE;
}

/*
*  format  Jun,23 Tue 11:25
*/



