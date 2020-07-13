/*
* AuraDesktop.cpp
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#include "MSWindows.h"
#include "AuraWindows.h"
#include "AuraDesktop.h"
#include "AuraRC.h"
#include "adi_osg.h"
#include "adi_os.h"
#include "adi_tuner.h"
#include "adi_scart.h"
#include "MS_DrawPublic.h"
#include "MsUserMessagedefine.h"
#include "adi_panel.h"
#include "FactoryTestKey.h"
#include "TestAppSupport.h"
#include "FactoryTestInit.h"
#include "AutoSwitchTest.h"
#include "adi_toolset.h"

#define MAIN_APP_RUN_TIMER (12359)

static BOOL MSInitWinApp ( HMSINSTANCE hInstance, int nCmdShow );
static INT_PTR CALLBACK MainWndProc ( HMSWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
static LRESULT OnCreateMainWnd ( HMSWND hWnd, WPARAM wParam, LPARAM lParam );
static LRESULT OnKeyMainWnd(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT OnMsgMainWnd(HMSWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static LRESULT OnTimerMainWnd ( HMSWND hWnd, WPARAM wParam, LPARAM lParam );
static LRESULT OnActiveMainWnd( HMSWND hWnd, WPARAM wParam, LPARAM lParam );
static void DrawTestAppTittle(HMSWND hWnd);
static void DrawRectStr(HMSWND hWnd, MSRECT rcPaint, char str[], int nStrlen, COLORREF color);
static void DrawErrorInfo(HMSWND hWnd);
static void DrawRunTime(HMSWND hWnd);


static HMSWND g_hDVBMainWnd = NULL;

HMSINSTANCE g_hInstance = NULL;

HMSBRUSH g_hBkBrush = NULL;

extern LRESULT CALLBACK CBTestAppDialogProc(HMSWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
extern void START_UPGRADE_8M(void);

int AuraApp( HMSINSTANCE hInstance, HMSINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow )
{
    MSMSG msg;

    if ( !MSInitWinApp ( hInstance, nCmdShow ) )
    {
        return 0;
    }

    g_hInstance = hInstance;

    while ( MSGetMessage ( &msg, NULL, 0, 0 ) )
    {
        if ( !MSIsDialogMessage ( msg.hwnd, &msg ) )
        {
            MSDispatchMessage ( &msg );
        }
    }

    return ( int ) msg.wParam;
}

static BOOL MSInitWinApp ( HMSINSTANCE hInstance, int nCmdShow )
{
    HMSWND				hWndMain = NULL;
	ADIOSGSurfaceInfo_S sSurfaceInfo;
    MSWNDCLASSEX		wcex;
	ADI_HANDLE			hHandle;

    g_hBkBrush = MSCreateSolidBrush ( RGBA ( 0, 100, 0, 0 ) );

    wcex.cbSize			= sizeof( wcex );
    wcex.style			= CS_DBLCLKS;
    wcex.lpfnWndProc	= ( MSWNDPROC ) MainWndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= NULL;
    wcex.hCursor		= NULL;
    wcex.hbrBackground	= g_hBkBrush;
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= ( LPCTSTR )"AuraAppClass";
    wcex.hIconSm		= NULL;

    if ( !MSRegisterClassEx ( &wcex ) )
    {
        return FALSE;
    }

	ADIOSGGetDisplaySurface( 1, &hHandle );

	ADIOSGGetSurfaceInfo(hHandle,&sSurfaceInfo);


	hWndMain = MSCreateWindow( ( LPCTSTR )"AuraAppClass", ( LPCTSTR )"AuraApp", WS_VISIBLE, 0, 0, sSurfaceInfo.m_nWidth, sSurfaceInfo.m_nHeight, 0, 0, hInstance, 0 );
	
    if ( hWndMain == NULL )
    {
        return FALSE;
    }

    return TRUE;
}

static INT_PTR CALLBACK MainWndProc ( HMSWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	ADIOSGSurfaceInfo_S sSurfaceInfo;
    MSRECT tempRECT;
	ADI_HANDLE hHandle;

	ADIOSGGetDisplaySurface( 1, &hHandle );
	ADIOSGGetSurfaceInfo(hHandle,&sSurfaceInfo);

    tempRECT.left	= 0;
    tempRECT.top	= 0;
	tempRECT.right	= sSurfaceInfo.m_nWidth;
	tempRECT.bottom = sSurfaceInfo.m_nHeight;

    switch ( uMsg )
    {
        case WM_CREATE:
            return OnCreateMainWnd ( hWnd, wParam, lParam );

        //case WM_KEYUP:
        case WM_KEYDOWN:
			return OnKeyMainWnd(hWnd, wParam, lParam);
		case WM_PAINT:
		{
			if (GetFlashStatus() == 0)
			{
		    	DrawErrorInfo(hWnd);
			}
			else
			{
				DrawTestAppTittle(hWnd);
			}
			DrawRunTime(hWnd);
		}
		break;
		case WM_CTLCOLORSTATIC:
		{
			return MSErasureDialogBG(hWnd, (HMSDC)wParam);
		}
			break;
        case WM_ERASEBKGND: 
			return MSErasureDialogBG(hWnd,(HMSDC)wParam);
			break;
            
        case WM_TIMER:
            return OnTimerMainWnd(hWnd, wParam, lParam);
        
		case WM_ACTIVATE:
			return OnActiveMainWnd(hWnd, wParam, lParam);
			
        default:
            break;
    }

	if (uMsg > USER_MESSAGE_START && uMsg < USER_MESSAGE_END)
	{
		return OnMsgMainWnd(hWnd, uMsg, wParam, lParam);
	}

    return MSDefWindowProc ( hWnd, uMsg, wParam, lParam );
}

static LRESULT OnCreateMainWnd ( HMSWND hWnd, WPARAM wParam, LPARAM lParam )
{
	BOOL bNeedBootGuide = FALSE;
	
    g_hDVBMainWnd = hWnd;
    
	TestAppStartPlay();

	TestAppSetMaxVolume();

	MSSetTimer(hWnd, MAIN_APP_RUN_TIMER, 1000, NULL);	

    return 1;
}

static LRESULT OnTimerMainWnd ( HMSWND hWnd, WPARAM wParam, LPARAM lParam )
{
	switch (wParam)
	{
	case MAIN_APP_RUN_TIMER:
		MSRECT stRect = { 1030, 20, 1250, 120 };
		MSInvalidateRect(hWnd, &stRect, TRUE);
		break;
	}
	
    return 1;
}

static LRESULT OnActiveMainWnd( HMSWND hWnd, WPARAM wParam, LPARAM lParam )
{
	if (hWnd == MSGetActiveWindow())
	{
       
	}

	MSPostMessage( hWnd, MSG_PLAY_SERVICE_RED, 0 , 0 );

	return 0;
}

static LRESULT OnKeyMainWnd(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if(GetFlashStatus() == 0 && wParam != VK_RED)
	{
		return 1;
	}
	
	switch (wParam)
	{
#if 0
	case FT_VK_F1: //USB TEST
		TestAppSetMute();
		TestAppHideVideo();
		TestAppStartUSBTest();
		break;

	case FT_VK_F2:
		TestAppSetMute();
		TestAppHideVideo();
		TestAppStartSmartCardTest();
		break;

	case FT_VK_F3:
	{
		TestAppSetMute();
		TestAppHideVideo();
		TestAppPlayLowFrequencyService();
	}
	break;
    	 
	case FT_VK_F4: //Play/CVBS
	case FT_VK_FC:
		TestAppSetMute();
		TestAppHideVideo();
		TestAppPlayMidFrequencyService();
		/*TestAppStartPlay();
		TestAppShowVideo();
		TestAppSetMaxVolume();*/
		break;
		
	case FT_VK_F5:
	{
		TestAppSetMute();
		TestAppHideVideo();
		TestAppPlayHighFrequencyService();
	}
	break;

	case FT_VK_F6:
	case VK_YELLOW:
        {
			DealwithTunerPower();
		}
		break;
		
    case FT_VK_FA:
    case FT_VK_FB:		
		{
			DealwithTunerPolar();
		}			
	    break;

	case FT_VK_FE: //MAX VOLUME
		TestAppSetMaxVolume();
		break;

	case FT_VK_FF: //MUTE
		TestAppSetMute();
		break;

	case FT_VK_D1:
		{
			DealwithColorMode();
		}
		break;
		
	case FT_VK_D2:
		{
			DealwithAspectRatio();
		}
		break;

	case FT_VK_E8:
	case VK_RECALL:
		{
			//FOR TESTAPP AGING TEST
			ADITunerSRCDeliver_U stAVDelivery;
			stAVDelivery.m_sTerrestrialDeliver.m_uFrequency = 306000;
			stAVDelivery.m_sTerrestrialDeliver.m_uBanuidth_3 = EM_ADITUNER_BAND_8M;
			GetFactoryTestInterface()->ConfigStream(&stAVDelivery, 4701, 4702);

			TestAppStopPlay();
			ADIOSThreadSleep(100);
			TestAppStartPlay();

		}
		break;
#endif

	case FT_VK_F9:
	case VK_GREEN:
	case FT_VK_FP_OK:
	case ADI_VK_MENU:
		{
			MSDialogBox(GetInstance(), (LPCTSTR)IDD_TESTAPP, hWnd, (MSDLGPROC)CBTestAppDialogProc);
		}
		break;

	case VK_RED:
	{
		static int nFlag = 1;
		if(nFlag == 1)
		{			
			nFlag = 0;
			TestAppHideVideo();
			START_UPGRADE_8M();
			TestAppShowVideo();
			nFlag = 1;
		}

	}
		break;

	default:
		break;
	}

	return 1;
}

static LRESULT OnMsgMainWnd(HMSWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case MSG_SHOW_TESTAPP_DIALOG:
		{
			MSDialogBox(GetInstance(), (LPCTSTR)IDD_TESTAPP, hWnd, (MSDLGPROC)CBTestAppDialogProc);
		}
		return 1;

	case MSG_PLAY_SERVICE_RED:
		{
    		TestAppStartPlay();

			TestAppSetMaxVolume();
			
			TestAppShowVideo();
		}

	default:
		break;
	}

	return 0;
}

HMSINSTANCE GetInstance ( )
{
    return g_hInstance;
}

HMSWND GetDVBMainWnd(void)
{
	return g_hDVBMainWnd;
}

static void DrawRectStr(HMSWND hWnd, MSRECT rcPaint, char str[], int nStrlen, COLORREF color)
{
	WCHAR paintstr[512] = { 0 };
	MSPAINTSTRUCT stPaint = { 0 };	
	HMSPEN 		hpenline				= NULL;		
	HMSPEN 		hpenOldpen				= NULL;	
	int nWidth = 3;
	
	HMSDC hdc = MSBeginPaint(hWnd, &stPaint);	
	MSMultiByteToWideChar( 0, 0, str, nStrlen, paintstr, sizeof(paintstr) - 2);
	MSSetTextColor( hdc, color);
	MSDrawText(hdc, (LPCTSTR)paintstr, MSwcslen((char*)paintstr), &rcPaint, DT_CENTER | DT_VCENTER);

	if(hdc == NULL)
	{
		ADIASSERT(NULL);
		return;
	}
	
	if(nWidth >0)
	{
		hpenline = MSCreatePen(PS_SOLID, nWidth, color);
		ADIASSERT(NULL != hpenline);
	}

	hpenOldpen		= MSSelectObject(hdc, hpenline);
	MSMoveToEx(hdc,rcPaint.left, rcPaint.top, NULL );
	MSLineTo(hdc, rcPaint.right, rcPaint.top);	
	MSLineTo(hdc, rcPaint.right, rcPaint.bottom);	
	MSLineTo(hdc, rcPaint.left, rcPaint.bottom);	
	MSLineTo(hdc, rcPaint.left, rcPaint.top);
	MSSelectObject(hdc, hpenOldpen);
	if(hpenline)
	{
		MSDeleteObject(hpenline);
		hpenline = NULL;
	}
	
	MSEndPaint(hWnd, &stPaint);
}

static void DrawTestAppTittle(HMSWND hWnd)
{
	MSRECT        rcPaint = {30, 20, 210, 120};
	
	DrawRectStr(hWnd, rcPaint, "TestApp", strlen("TestApp"), RGBA(0, 255, 100,255));
}

static void DrawErrorInfo(HMSWND hWnd)
{
	MSRECT        rcPaint = {500, 300, 780, 420};
	
	DrawRectStr(hWnd, rcPaint, "Flash Data Error", strlen("Flash Data Error"), RGBA(255,0,0,255));
}

static void DrawRunTime(HMSWND hWnd)
{
	MSRECT        rcPaint = { 1030, 20, 1250, 120 };
	char acRunTime[32] = { 0 };

	unsigned int unTick = ADIOSGetTickCount() / 1000;

	unsigned int unSecond = unTick % 60;
	unsigned int unMinute = (unTick / 60) % 60;
	unsigned int unHour = (unTick / 3600) % 24;
	unsigned int unDay = unTick / (3600 * 24);

	snprintf(acRunTime, sizeof(acRunTime), "%d %02d:%02d:%02d", unDay, unHour, unMinute, unSecond);

	DrawRectStr(hWnd, rcPaint, acRunTime, strlen(acRunTime), RGBA(0, 255, 100, 255));
}
