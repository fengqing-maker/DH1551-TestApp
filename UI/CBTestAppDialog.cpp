/*
* CBTestAppDialog.cpp
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AuraDesktop.h"
#include "Aura.h"
#include "AuraWindows.h"
#include "AuraRC.h"
#include "Resources.h"
#include "adi_os.h"
#include "MSWINUser.h"
#include "MS_DrawControl.h"
#include "MS_DrawPublic.h"
#include "MS_DrawListPub.h"
#include "MS_DrawScrollBar.h"
#include "MS_DrawListPubType.h"
#include "MS_DrawList.h"
#include "MS_DrawLRButton.h"
#include "TestAppSupport.h"
#include "MsUserMessagedefine.h"
#include "MS_DrawButton.h"
#include "FactoryTestKey.h"
#include "adi_screen.h"
#include "STBDataInterface.h"
#include "adi_aout.h"
#include "adi_audio.h"
#include "adi_panel.h"
#include "adi_uart.h"
#include "AutoSwitchTest.h"
#include "MSWINGDI.h"
#include "UIViewInfo.h"
#include "ReadSTBAndCardID.h"
#include "adi_flash.h"
#include "adi_bootloader_common.h"
#include "adi_toolset.h"


#define PASS_STR "PASS"
#define FAIL_STR "FAIL"
#define NOT_TEST_STR "NOT TEST"
#define NOT_VERIFY "NOT VERIFY"

#define AUDIO_SWITCH_TIMER 12345
#define INIT_DELAY_TIMER 12346
#define SWITCH_ITEM_TIMER 12347
#define APP_RUN_TIME_TIMER 12348


static int g_nTimerIndex[E_MAX];
static int g_nTimerNum = 0;

static InputKeyStruct *g_pInputKey;
static ItemInfo *g_ActTestItem;
static int g_ActTestCount = 0;
static ItemID *g_ActID;
static IDCInfo *g_AllTestCtrl;	
static int g_ItemID[E_MAX] = {0};

static HMSWND g_hTestAppWnd = NULL;

static BOOL g_bFrontKeyPressed = FALSE;
static char g_acSN[MAX_SN_LEN] = {0};

static int g_nOTAFlag = 0;

static void USBUpgrade(void);

static LRESULT 	OnInitTestAppDialogView			(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT 	OnCommandTestAppDialogView	(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT 	OnPaintTestAppDialogView			(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT 	OnNotifyTestAppDialogView		(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT 	OnColorTestAppView				(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT OnTimerTestAppView					(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT 	OnDestroyTestAppDialogView		(HMSWND hWnd, WPARAM wParam, LPARAM lParam);
static LRESULT OnDrawItemTestAppView			(HMSWND hWnd, WPARAM wParam, LPARAM lParam);

int MSTestAppSetBkColor(HMSWND hWnd, IN HMSDC hDC, IN COLORREF bkRgb);

static LRESULT DowithUserMsg( HMSWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT DoUpgradeMessage(HMSWND hWnd, UINT message);
static LRESULT DoOTAMessage(HMSWND hWnd, UINT message, WPARAM wParam);
static LRESULT OnTestAppItemMsg(HMSWND hWnd, UINT message, WPARAM wParam);
static void  NextStartItem(HMSWND hWnd, ItemID enItemID);

static void TestAppDoUpAndDown(HMSWND hWnd, BOOL bUp);
static void TestAppDoReturn(HMSWND hWnd);
static unsigned int StartTestAV(HMSWND hWnd);
static unsigned int StartTestUSB(HMSWND hWnd);
static unsigned int StartTestEthernet(HMSWND hWnd);
static unsigned int StartTestSmartCard(HMSWND hWnd);
static unsigned int StartTestFrontPanel(HMSWND hWnd);
static unsigned int StartSNUpgrade(HMSWND hWnd);
static unsigned int StartOTA(HMSWND hWnd);

static void FrontPanelInputKey(HMSWND hWnd, unsigned int unKey);
static LRESULT TestAppAdjustposition(HMSWND hWnd);
static void StartTestInit(HMSWND hWnd);
static int GetTestResultByID(int nID);
static int GetNetTestSuccessStr(char *pacStr, int nLen);
static void VoltageShowMsgAndResult(HMSWND hWnd, int nID);
static void ShowMsgAndResult(HMSWND hWnd, int nID);
static void InitAllInfo(HMSWND hWnd);
static void SwitchService(HMSWND hWnd);

LRESULT CALLBACK CBTestAppDialogProc( HMSWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
        case WM_INITDIALOG:
			return OnInitTestAppDialogView(hWnd, wParam,  lParam);

        case WM_COMMAND:	
			return OnCommandTestAppDialogView(hWnd, wParam, lParam);

		case WM_PAINT:
			return OnPaintTestAppDialogView(hWnd, wParam, lParam);

        case WM_ERASEBKGND:
			return MSErasureDialogBG(hWnd, (HMSDC)wParam);

		case WM_CTLCOLORSTATIC:
			return OnColorTestAppView(hWnd, wParam, lParam);

		case WM_NOTIFY:
			return OnNotifyTestAppDialogView(hWnd, wParam, lParam);
			
		case WM_DRAWITEM:
			return OnDrawItemTestAppView(hWnd, wParam, lParam);

		case WM_TIMER:
			return OnTimerTestAppView(hWnd, wParam, lParam);
			
        case WM_DESTROY:
			return OnDestroyTestAppDialogView(hWnd, wParam, lParam);        
		
        default:
            break;
    }
	
	return DowithUserMsg( hWnd, message, wParam, lParam);
}

static LRESULT OnInitTestAppDialogView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AuraAddShortcutKey(hWnd, VK_LEFT, VK_LEFT);
	AuraAddShortcutKey(hWnd, VK_RIGHT, VK_RIGHT);
	AuraAddShortcutKey(hWnd, VK_UP, VK_UP);
	AuraAddShortcutKey(hWnd, VK_DOWN, VK_DOWN);
	AuraAddShortcutKey(hWnd, VK_BACK, VK_BACK);
	AuraAddShortcutKey(hWnd,VK_EXIT,VK_EXIT);
	AuraAddShortcutKey(hWnd, VK_RETURN, VK_RETURN);
	AuraAddShortcutKey(hWnd, VK_VOLUME_UP, VK_VOLUME_UP);
	AuraAddShortcutKey(hWnd, VK_VOLUME_DOWN, VK_VOLUME_DOWN);
	AuraAddShortcutKey(hWnd, VK_GREEN, VK_GREEN);
	AuraAddShortcutKey(hWnd, VK_RED, VK_RED);	
	
	AuraAddShortcutKey(hWnd, FT_VK_F9, FT_VK_F9);
	AuraAddShortcutKey(hWnd, ADI_VK_MENU, ADI_VK_MENU);
	AuraAddShortcutKey(hWnd, FT_VK_FE, FT_VK_FE);
	AuraAddShortcutKey(hWnd, FT_VK_E2, FT_VK_E2);
	AuraAddShortcutKey(hWnd, FT_VK_E5, FT_VK_E5);
	AuraAddShortcutKey(hWnd, FT_VK_E3, FT_VK_E3);
	AuraAddShortcutKey(hWnd, FT_VK_D8, FT_VK_D8);
	AuraAddShortcutKey(hWnd, FT_VK_E0, FT_VK_E0);
	AuraAddShortcutKey(hWnd, ADI_VK_COLORED_KEY_0, ADI_VK_COLORED_KEY_0);
	AuraAddShortcutKey(hWnd, FT_VK_F0, FT_VK_F0);
	AuraAddShortcutKey(hWnd, FT_VK_E6, FT_VK_E6);
	AuraAddShortcutKey(hWnd, ADI_VK_COLORED_KEY_3, ADI_VK_COLORED_KEY_3);
	AuraAddShortcutKey(hWnd, ADI_VK_9, ADI_VK_9);

	AuraAddShortcutKey(hWnd, FT_VK_FP_POWER, FT_VK_FP_POWER);
	AuraAddShortcutKey(hWnd, FT_VK_FP_OK, FT_VK_FP_OK);
	AuraAddShortcutKey(hWnd, FT_VK_FP_LEFT, FT_VK_FP_LEFT);
	AuraAddShortcutKey(hWnd, FT_VK_FP_RIGHT, FT_VK_FP_RIGHT);
	AuraAddShortcutKey(hWnd, FT_VK_FP_UP, FT_VK_FP_UP);
	AuraAddShortcutKey(hWnd, FT_VK_FP_DOWN, FT_VK_FP_DOWN);    

	char acTestAppTitle[128] = { 0 };

	SetTestAppViewTitle(acTestAppTitle, sizeof(acTestAppTitle));//∂¡»°±ÍÃ‚
	
	MSSetDlgItemTextByChar(hWnd, IDC_TESTAPP_TITLE_STATIC, acTestAppTitle, sizeof(acTestAppTitle));
	
	g_hTestAppWnd = hWnd;
		
	InitAllInfo(hWnd);

	TestAppAdjustposition(hWnd);

	ADISCREENSetOSDTransparency(90);
	
	MSSetTimer(hWnd, INIT_DELAY_TIMER, 10, NULL);
	MSSetTimer(hWnd, APP_RUN_TIME_TIMER, 1000, NULL);

	return 0;
}

static LRESULT OnCommandTestAppDialogView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD	wKeyCode = 0;

	wKeyCode = LOWORD(wParam);
	switch (wKeyCode)
	{			
		case VK_BACK:
		case FT_VK_D8:
		case VK_EXIT:
			MSEndDialog(hWnd, 0);
			return 1;
			
		case VK_RIGHT:
		case FT_VK_E3:
			ADIUartDisable(0, ADI_FALSE);
			PrintLog();
			ADIUartDisable(0, ADI_TRUE);
			return 1;
			
		case VK_UP:
		case FT_VK_FE:
			TestAppDoUpAndDown(hWnd, TRUE);
			return 1;
			
		case VK_DOWN:
		case FT_VK_E5:
			TestAppDoUpAndDown(hWnd, FALSE);
			return 1;
	        
		case VK_RETURN:
		case FT_VK_E2:
			{
	            TestAppDoReturn(hWnd);
				return 1;
			}
			break;
		case FT_VK_E0:
		case ADI_VK_COLORED_KEY_3:
			SetOTAFlag();
			break;

		case FT_VK_F0:
		case ADI_VK_COLORED_KEY_0:
			ClearResultExceptSN();
		break;

		case FT_VK_E6:
		case ADI_VK_FAV:
			if(IsReadForUSBUpgrade() == 1)
			{
				USBUpgrade();
			}
		break;
		#if 0
		case FT_VK_F9:
		{
			SwitchService(hWnd);
		}
			break;
		#endif
		default:
			FrontPanelInputKey(hWnd, LOWORD(wParam));
			break;
	}
	return 0;
}

static LRESULT OnPaintTestAppDialogView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	MSPAINTSTRUCT ps = { 0 };
	HMSDC         hdc = NULL;

	hdc = MSBeginPaint(hWnd, &ps);
	
	MSEndPaint(hWnd, &ps);

	return 0;
}

static LRESULT OnColorTestAppView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int ii = 0;
	int nCtrlID = MSGetDlgCtrlID((HMSWND)lParam);
	
	for(ii = 0; ii < g_ActTestCount; ii++)
	{
		if(g_AllTestCtrl[ii].MSGIDS == nCtrlID || g_AllTestCtrl[ii].ResultIDS == nCtrlID)
		{
			if( g_ActTestItem[g_ActID[ii]].enTestType == E_MANU )
			{
				MSTestAppSetBkColor((HMSWND)lParam, (HMSDC)wParam, RGBA(0, 155, 155, 255));
			}
			else
			{
				MSTestAppSetBkColor((HMSWND)lParam, (HMSDC)wParam, RGBA(0, 155, 0, 255));
			}
			break;
		}
	}

	if( g_ActTestCount == ii )
	{
		MSTestAppSetBkColor((HMSWND)lParam, (HMSDC)wParam, RGBA(0, 155, 155, 255));
	}
	
	MSSetTextColor((HMSDC)wParam, RGBA(0, 0, 0, 255));

	return 0;

}

static LRESULT OnNotifyTestAppDialogView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

static LRESULT OnDrawItemTestAppView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	LPMSDRAWITEMSTRUCT pDS = (LPMSDRAWITEMSTRUCT)lParam;
	
	if (pDS != NULL)
	{
		CHAR cWdStr[64] = {0};
		
		for(int ii = 0; ii < g_ActTestCount; ii++)
		{
			if( g_AllTestCtrl[ii].ButtonIDS == pDS->CtlID )
			{
				if( g_ActTestItem[g_ActID[ii]].enTestType == E_MANU )
				{
					if ((pDS->itemState & ODS_FOCUS) == ODS_FOCUS)
					{
						MSTestAppSetBkColor(hWnd, pDS->hDC, RGBA(0xFF, 0xFF, 0, 0xFF));//YELLOW
					}
					else
					{
						int nResult = 0;
						nResult = GetTestResultByID(g_ActID[ii]);
						if (nResult == 0)
						{
							MSTestAppSetBkColor(hWnd, pDS->hDC, RGBA(0xF0, 0xF0, 0xF0, 0xFF));
						}
						else if (nResult == 1)
						{
							MSTestAppSetBkColor(hWnd, pDS->hDC, RGBA(0x0, 0xFF, 0x0, 0xFF));
						}
						else
						{ 
							if(g_ActID[ii] != E_SN && g_ActID[ii] != E_OTA_ID)
							{
								MSTestAppSetBkColor(hWnd, pDS->hDC, RGBA(0xFF, 0, 0, 0xFF));//RED
							}
							else
							{
								MSTestAppSetBkColor(hWnd, pDS->hDC, RGBA(0xF0, 0xF0, 0xF0, 0xFF));
							}
						}
					}
				}
				else
				{
					MSTestAppSetBkColor(hWnd, pDS->hDC, RGBA(0, 155, 0, 255));
				}
						
				MSSetTextColor(pDS->hDC, RGBA(0x0, 0x0, 0x0, 0xff));
				MSMultiByteToWideChar(0, 0, (LPCSTR)g_ActTestItem[g_ActID[ii]].acStr, sizeof(g_ActTestItem[g_ActID[ii]].acStr), (LPWSTR)cWdStr, sizeof(cWdStr) >> 1);
				MSDrawText(pDS->hDC, (LPCTSTR)cWdStr, MSwcslen((const char*)cWdStr), &pDS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				MSSetDlgItemText(hWnd, pDS->CtlID, (LPCTSTR)cWdStr);
				return 1;
			}
		}		
	}
	
	return 0;
}

int MSTestAppSetBkColor(HMSWND hWnd, IN HMSDC hDC, IN COLORREF bkRgb)
{
	HMSDC hMSDC = NULL;
	ADI_HANDLE hHandle = NULL;
	HMSBRUSH hBkBrush = NULL;
	MSRECT Rect = { 0 };

	if (hDC == NULL)
	{
		return FALSE;
	}

	hBkBrush = MSCreateSolidBrush(bkRgb);

	MSGetClientRect(hWnd, &Rect);
	MSFillRect(hDC, &Rect, hBkBrush);

	MSDeleteObject((HMSOBJECT)hBkBrush);

	return 1;
}

static LRESULT OnTimerTestAppView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	static BOOL s_bPlayHMDI = TRUE;
	char acStr[MAX_SN_LEN * 2] = {0};
	
	switch(wParam)
	{
		case AUDIO_SWITCH_TIMER:
			MSKillTimer( hWnd, AUDIO_SWITCH_TIMER );
			s_bPlayHMDI = (s_bPlayHMDI == TRUE) ? FALSE : TRUE;
			if(s_bPlayHMDI)
			{
				ADIAUDIOSetDeviceVolume(0, EM_ADIAOUT_HDMI, 31);
				ADIAUDIOSetDeviceVolume(0, EM_ADIAOUT_RCA, 0);
			}
			else
			{
				ADIAUDIOSetDeviceVolume(0, EM_ADIAOUT_HDMI, 0);
				ADIAUDIOSetDeviceVolume(0, EM_ADIAOUT_RCA, 31);
			}
			MSSetTimer( hWnd, AUDIO_SWITCH_TIMER, 3000, NULL );
			break;

		case INIT_DELAY_TIMER:
		{
			MSKillTimer(hWnd, INIT_DELAY_TIMER);
			
			StartTestInit(hWnd);

			if(g_ItemID[E_SN] != E_MAX)
			{
				int nResult = GetTestResultByID(E_SN);

				if( nResult != 0 )
				{
					if(ReadSTBID(g_acSN, sizeof(g_acSN)) == E_DATA_SUCCESS)
					{
						sprintf(acStr, "SN: %s", g_acSN);
						
						MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].MSGIDS, acStr, strlen(acStr));
						if(nResult == 1)
						{
							MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, PASS_STR, strlen(PASS_STR));
						}
						else
						{
							MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, NOT_VERIFY, strlen(NOT_VERIFY));
						}
					}
				}
			}
		}
			break;
			
		case SWITCH_ITEM_TIMER:
		{
			MSKillTimer(hWnd, SWITCH_ITEM_TIMER);
			
			if(GetTestResultByID(E_SN) == 0)
			{
				int nFlag = E_MAX;
				for(int ii = 0; ii < g_nTimerNum; ii++)
				{
					switch(g_nTimerIndex[ii])
					{
						case E_ASP:
						case E_DIS:
						{
							if(nFlag == E_MAX)
							{
								if(g_nTimerIndex[ii] == E_ASP)
								{
									DealwithAspectRatio();
									VoltageShowMsgAndResult(hWnd, E_ASP);
									g_nTimerIndex[ii] = E_DIS;
								}
								else
								{
									DealwithColorMode();
									VoltageShowMsgAndResult(hWnd, E_DIS);
									g_nTimerIndex[ii] = E_ASP;
								}
								nFlag = ii;
							}
						}
							break;
							
						case E_STUNER:
						{
							DealwithTunerPolar();
							VoltageShowMsgAndResult(hWnd, E_STUNER);
						}
							break;
							
						case E_TTUNER:
						{
							DealwithTunerPower();
							VoltageShowMsgAndResult(hWnd, E_TTUNER);
						}
							break;
							
						default:
							break;
					}
				}				
				MSSetTimer( hWnd, SWITCH_ITEM_TIMER, 1000, NULL);
			}
		}
			break;

		case APP_RUN_TIME_TIMER:
		{
								   char acRunTime[32] = { 0 };

								   unsigned int unTick = ADIOSGetTickCount() / 1000;

								   unsigned int unSecond = unTick % 60;
								   unsigned int unMinute = (unTick / 60) % 60;
								   unsigned int unHour = (unTick / 3600) % 24;
								   unsigned int unDay = unTick / (3600 * 24);

								   snprintf(acRunTime, sizeof(acRunTime), "%d %02d:%02d:%02d", unDay, unHour, unMinute, unSecond);
								   MSSetDlgItemTextByChar(hWnd, IDC_SHOW_TIME, acRunTime, strlen(acRunTime));
		}
			break;
			
		default:
			break;
	}

	return 1;
}

static LRESULT OnDestroyTestAppDialogView(HMSWND hWnd, WPARAM wParam, LPARAM lParam)
{
	g_hTestAppWnd = NULL;

	MSKillTimer(hWnd, SWITCH_ITEM_TIMER);
	
	MSKillTimer(hWnd, INIT_DELAY_TIMER);
	
	MSKillTimer(hWnd, APP_RUN_TIME_TIMER);
	
	return 0;
}

static LRESULT 	OnTestAppItemMsg(HMSWND hWnd, UINT message, WPARAM wParam)
{
	ItemID curItemID = E_MAX;

	curItemID = (ItemID)(message - MSG_TESTAPP_PLAY + E_AV);
	if(GetCardStatus() == 1 && curItemID != E_MAX)
	{
		if(curItemID == E_FRONT_PANEL)
		{
			g_bFrontKeyPressed = FALSE;
			for (int ii = 0; ii < GetInputKeyCount(); ii++)
			{
				g_pInputKey[ii].unPressed = 0;
			}
		}		
		
		if( g_ItemID[curItemID] != E_MAX )
		{
			ShowMsgAndResult(hWnd, curItemID);

			int nIndex = ( g_ActTestCount + g_ItemID[curItemID] + 1 ) % g_ActTestCount ;

			NextStartItem(hWnd, g_ActID[nIndex]);

			SaveTestResult();
		}	
	}

	return 0;
}

static void  NextStartItem(HMSWND hWnd, ItemID enItemID)
{
	if( g_ItemID[enItemID] != E_MAX )
	{
		MSSetFocus(MSGetDlgItem(hWnd, g_AllTestCtrl[g_ItemID[enItemID]].ButtonIDS));
		switch(enItemID)
		{
			case E_AV :
			{
				StartTestAV(hWnd);
				break;
			}
			case E_USB :
			{
				StartTestUSB(hWnd);
				break;
			}
			case E_ETHERNET :
			{
				StartTestEthernet(hWnd);
				break;
			}
			case E_SMARTCARD:
			{
				StartTestSmartCard(hWnd);
				break;
			}
			case E_FRONT_PANEL:
			{
				ShowMsgAndResult(hWnd, E_FRONT_PANEL);
				StartTestFrontPanel(hWnd);
				break;
			}
			case E_SN:
			{
				StartSNUpgrade(hWnd);
				
				g_bFrontKeyPressed = FALSE;
				for (int ii = 0; ii < GetInputKeyCount(); ii++)
				{
					g_pInputKey[ii].unPressed = 0;
				}
				break;
			}
			case E_OTA_ID:
			{
				StartOTA(hWnd);
				
				ShowMsgAndResult(hWnd, E_OTA_ID);
				break;
			}
			default : 
				break;
		}
	}
	
}

static void TestAppDoUpAndDown(HMSWND hWnd, BOOL bUp)
{
	int i = 0;
	
	for (i = 0; i < g_ActTestCount; i++)
	{
		if (MSGetDlgCtrlID(MSGetFocus()) == g_AllTestCtrl[i].ButtonIDS)
		{
			break;
		}
	}
	
	for (int j = 0; j < g_ActTestCount; j++)
	{
		if ( bUp )
		{
			i = (i + g_ActTestCount - 1) % g_ActTestCount;
		}
		else
		{
			i = (i + g_ActTestCount + 1) % g_ActTestCount;
		}

		if( g_ActTestItem[g_ActID[i]].enTestType == E_MANU )
		{	
			MSSetFocus(MSGetDlgItem(hWnd, g_AllTestCtrl[i].ButtonIDS));
			ShowMsgAndResult(hWnd, g_ActID[i]);
			break;
		}
	}
}

static void TestAppDoReturn(HMSWND hWnd)
{
	int i = 0;
	char* pcStr = NULL;
	DWORD dwIDC = MSGetDlgCtrlID(MSGetFocus());

	for(i = 0; i < g_ActTestCount; i++)
	{
		if(g_AllTestCtrl[i].ButtonIDS == dwIDC)
		{
			switch(g_ActID[i])
			{
				case E_AV:
					StartTestAV(hWnd);
					break;
					
				case E_USB:
					StartTestUSB(hWnd);
					break;
					
				case E_ETHERNET:
					StartTestEthernet(hWnd);
					break;

				case E_SMARTCARD:
					StartTestSmartCard(hWnd);
					break;

				case E_FRONT_PANEL:
					StartTestFrontPanel(hWnd);
					break;

				case E_SN:
					StartSNUpgrade(hWnd);
					break;

				case E_OTA_ID:
					StartOTA(hWnd);
					break;
			}
			break;
		}
	}
}
static void SwitchService(HMSWND hWnd)
{
		TestAppSwitchService();
		TestAppSetMaxVolume();
		TestAppShowVideo();
}

static unsigned int StartTestAV(HMSWND hWnd)
{
	if( g_ItemID[E_AV] != E_MAX )
	{
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_AV]].MSGIDS, "Start Test Audio And Video", strlen("Start Test Audio And Video"));
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_AV]].ResultIDS, "Testing", strlen("Testing"));
		
		TestAppStartPlay();
		TestAppSetMaxVolume();
		TestAppShowVideo();
	}
		
	return 1;
}

static unsigned int StartTestUSB(HMSWND hWnd)
{
	if( g_ItemID[E_USB] != E_MAX )
	{
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_USB]].MSGIDS, "Start Test USB", strlen("Start Test USB"));
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_USB]].ResultIDS, "Testing", strlen("Testing"));
	}

	return TestAppStartUSBTest();
}

static unsigned int StartTestEthernet(HMSWND hWnd)
{
	if( g_ItemID[E_ETHERNET] != E_MAX )
	{
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_ETHERNET]].MSGIDS, "Start Test Ethernet", strlen("Start Test Ethernet"));
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_ETHERNET]].ResultIDS, "Testing", strlen("Testing"));
	}

	return TestAppStartEthernetTest();
}

static unsigned int StartTestSmartCard(HMSWND hWnd)
{
	if( g_ItemID[E_SMARTCARD] != E_MAX )
	{
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SMARTCARD]].MSGIDS, "Start Test SmartCard", strlen("Start Test SmartCard"));
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SMARTCARD]].ResultIDS, "Testing", strlen("Testing"));
	}

	return TestAppStartSmartCardTest();
}

static unsigned int StartTestFrontPanel(HMSWND hWnd)
{
	if(!g_bFrontKeyPressed)
	{	
		if( g_ItemID[E_FRONT_PANEL] != E_MAX )
		{				
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_FRONT_PANEL]].MSGIDS, "Start Test FrontPanel", strlen("Start Test FrontPanel"));
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_FRONT_PANEL]].ResultIDS, "Testing", strlen("Testing"));
		}

		for (int ii = 0; ii < GetInputKeyCount(); ii++)
		{
			g_pInputKey[ii].unPressed = 0;
		}
	}
	
	return 1;
}

static unsigned int StartSNUpgrade(HMSWND hWnd)
{
	char acStr[128] = {0};
	int nResult = GetTestResultByID(E_SN);

	if(strlen(g_acSN) > 0 && nResult != 0)
	{
		sprintf(acStr, "Alredy has SN:%s", g_acSN);
		if( g_ItemID[E_SN] != E_MAX )
		{				
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].MSGIDS, acStr, strlen(acStr));
			if(nResult == 1)
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, PASS_STR, strlen(PASS_STR));
			}
			else
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, NOT_VERIFY, strlen(NOT_VERIFY));
			}
		}
	}
	else
	{
		ShowMsgAndResult(hWnd, E_SN);
	}

	return 0;
}

static unsigned int StartOTA(HMSWND hWnd)
{
	if( g_ItemID[E_OTA_ID] != E_MAX )
	{
		if(g_nOTAFlag == 1)
		{
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "OTA Already Start", strlen("Already Start"));
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].ResultIDS, "Writing", strlen("Writing"));
		}
		else
		{
			int nFlag = GetHLFlag();
			if( nFlag )
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "OTA With HL", strlen("OTA With HL"));
			}
			else
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "OTA With NO HL", strlen("OTA With NO HL"));
			}
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].ResultIDS, "Waiting", strlen("Waiting"));
		}
	}	

	return 0;
}

static void FrontPanelInputKey(HMSWND hWnd, unsigned int unKey)
{
	if (unKey == FT_VK_FP_POWER || unKey == FT_VK_FP_OK ||
		unKey == FT_VK_FP_MENU || unKey == FT_VK_FP_LEFT ||
		unKey == FT_VK_FP_RIGHT || unKey == FT_VK_FP_UP ||
		unKey == FT_VK_FP_DOWN)
	{

		char acTmp[64];
		memset(acTmp, 0, sizeof(acTmp));
		for (int ii = 0; ii < GetInputKeyCount(); ii++)
		{
			if (g_pInputKey[ii].unKey == unKey && g_pInputKey[ii].unPressed == 1)
			{
				return;
			}

			if (g_pInputKey[ii].unPressed == 1)
			{
				strcat(acTmp, g_pInputKey[ii].acName);
				strcat(acTmp, "  ");
			}
			else if (g_pInputKey[ii].unKey == unKey && g_pInputKey[ii].unPressed == 0)
			{
				strcat(acTmp, g_pInputKey[ii].acName);
				strcat(acTmp, "  ");
				g_pInputKey[ii].unPressed = 1;
			}
		}
		TestAppFrontPanelInputKey(unKey);
		g_bFrontKeyPressed = TRUE;
		if(g_ItemID[E_FRONT_PANEL] != E_MAX)
		{
			if(MSGetDlgCtrlID(MSGetFocus())!= g_AllTestCtrl[g_ItemID[E_FRONT_PANEL]].ButtonIDS)
			{
				MSSetFocus(MSGetDlgItem(hWnd, g_AllTestCtrl[g_ItemID[E_FRONT_PANEL]].ButtonIDS));
			}
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_FRONT_PANEL]].MSGIDS, acTmp, strlen(acTmp));
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_FRONT_PANEL]].ResultIDS, "Testing", strlen("Testing"));
		}
	}
}

static void FactoryTestCommand(unsigned int unKey)
{
	switch (unKey)
	{
	case FT_VK_FF:
		TestAppSetMute();
		break;
	case FT_VK_FE:
		TestAppSetMaxVolume();
		break;
	case FT_VK_F1:
		TestAppStartUSBTest();
		break;
	case FT_VK_F4:
	case FT_VK_FC:
		TestAppStartPlay();
		break;
	case FT_VK_F9:
		TestAppStartAssembleTest();
		break;

	default:
		break;
	}
}

HMSWND GetTestAppWnd(void)
{
	return g_hTestAppWnd;
}


static LRESULT TestAppAdjustposition(HMSWND hWnd)
{
	int i = 0;
	HMSWND hWndCtrl;
	int AdjustHeight = 0;
	MSRECT firstRectBN = { 0 };
	MSRECT firstRectMS = { 0 };
	MSRECT firstRectRT = { 0 };
	MSRECT lastRect = { 0 };
	int nCount = GetCtrlCount();
	
	MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[0].ButtonIDS), &firstRectBN);
	MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[0].MSGIDS), &firstRectMS);
	MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[0].ResultIDS), &firstRectRT);
	MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[nCount-1].ButtonIDS), &lastRect);

	if(g_ActTestCount > 1)
	{
		AdjustHeight = (lastRect.top - firstRectBN.top) / (g_ActTestCount - 1);
	}
	else
	{
		AdjustHeight = -1;
	}
	
	for (i = 0; i < g_ActTestCount; i++)
	{
		hWndCtrl = MSGetDlgItem(hWnd, g_AllTestCtrl[i].ButtonIDS);
		MSMoveWindow(hWndCtrl, firstRectBN.left, firstRectRT.top, firstRectBN.right - firstRectBN.left, firstRectBN.bottom - firstRectBN.top, TRUE);
		
		hWndCtrl = MSGetDlgItem(hWnd, g_AllTestCtrl[i].MSGIDS);
		MSMoveWindow(hWndCtrl, firstRectMS.left, firstRectRT.top, firstRectMS.right - firstRectMS.left, firstRectMS.bottom - firstRectMS.top, TRUE);
		
		hWndCtrl = MSGetDlgItem(hWnd, g_AllTestCtrl[i].ResultIDS);
		MSMoveWindow(hWndCtrl, firstRectRT.left, firstRectRT.top, firstRectRT.right - firstRectRT.left, firstRectRT.bottom - firstRectRT.top, TRUE);

		firstRectRT.top += AdjustHeight;
		firstRectRT.bottom += AdjustHeight;
	}

	for( ; i < nCount ; i++)
	{
		hWndCtrl = MSGetDlgItem(hWnd, g_AllTestCtrl[i].ButtonIDS);
		MSMoveWindow(hWndCtrl, 0, 0, 0, 0, FALSE);
		
		hWndCtrl = MSGetDlgItem(hWnd, g_AllTestCtrl[i].MSGIDS);
		MSMoveWindow(hWndCtrl, 0, 0, 0, 0, FALSE);
		
		hWndCtrl = MSGetDlgItem(hWnd, g_AllTestCtrl[i].ResultIDS);
		MSMoveWindow(hWndCtrl, 0, 0, 0, 0, FALSE);	
	}
	
	return 1;
}

static LRESULT DoUpgradeMessage(HMSWND hWnd, UINT message)
{
	if( g_ItemID[E_SN] != E_MAX )
	{
		switch(message)
		{
			case MSG_UPGRADE_START:
				break;
				
			case MSG_UPGRADE_SUCCESS:
			{
				char acSN[MAX_SN_LEN] = {0};
				char acStr[128] = {0};
				
				if(ReadSTBID(acSN, sizeof(acSN)) == E_DATA_SUCCESS)
				{
					sprintf(acStr, "Upgrade SN Success,SN:%s", acSN);
					MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].MSGIDS, acStr, strlen(acStr));
					if(GetTestResultByID(E_SN) == 1)
					{
						MSRECT stRect = {0};
						MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, PASS_STR, strlen(PASS_STR));
						
						MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ButtonIDS), &stRect);
						MSInvalidateRect(hWnd, &stRect, FALSE);

						MSSetFocus(MSGetDlgItem(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].ButtonIDS));
						
						StartOTA(hWnd);
					}
					else
					{
						MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, NOT_VERIFY, strlen(NOT_VERIFY));
					}
				}

				break;
			}
				
			case MSG_UPGRADE_FAIL:
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].MSGIDS, "SN Test Finished", strlen("SN Test Finished"));
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, FAIL_STR, strlen(FAIL_STR));
				break;

			case MSG_UPGRADE_TIMEOUT:
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].MSGIDS, "SN Test Finished", strlen("SN Test Finished"));
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_SN]].ResultIDS, "TimeOut", strlen("TimeOut"));
				break;
			
			case MSG_UPGRADE_ERASE:
				memset(g_acSN, 0, sizeof(g_acSN));
				StartSNUpgrade(hWnd);
				break;

			default:
				break;
		}
	}
		
	return 1;
}

static LRESULT DoOTAMessage(HMSWND hWnd, UINT message, WPARAM wParam)
{
	if( g_ItemID[E_OTA_ID] != E_MAX )
	{
		switch(message)
		{
		case MSG_OTA_START:
			{
				g_nOTAFlag = 1;
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "STB Start OTA", strlen("STB Start OTA"));
				break;
			}
			
		case MSG_OTA_WRITE_CORE:
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "STB Writing Core", strlen("STB Writing Core"));
				break;
			}
			
		case MSG_OTA_WRITE_RC:
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "STB Writing RC", strlen("STB Writing RC"));
				break;
			}
		
		case MSG_OTA_WRITE_APP:
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "STB Writing APP", strlen("STB Writing APP"));
				break;
			}
		
		case MSG_OTA_OPEN_HL:
			{
				MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].MSGIDS, "STB OPEN HL", strlen("STB OPEN HL"));
				break;
			}
		
		default:
			break;
		}
		
		if(wParam == 0)
		{
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].ResultIDS, "Writing", strlen("Writing"));
		}
		else
		{
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[E_OTA_ID]].ResultIDS, FAIL_STR, strlen(FAIL_STR));
		}
	}
		
	return 1;
}

static void StartTestInit(HMSWND hWnd)
{
	TestResult_S stTestResult = {0};

	if(hWnd == NULL)
	{
		return;
	}
	
	if (GetTestResult(&stTestResult) > 0)
	{
		int nResult = 0;
		for(int i = 0 ; i < g_ActTestCount ; i++)
		{
			if(g_ActTestItem[g_ActID[i]].enTestType == E_MANU)
			{
				switch (g_ActID[i])
				{
				case E_AV:
					nResult = stTestResult.nAVResult;
					break;
			
				case E_USB:
					nResult = stTestResult.nUSBResult;
					break;
			
				case E_ETHERNET:
					nResult = stTestResult.nEthernetResult;
					break;
			
				case E_SMARTCARD:
					nResult = stTestResult.nSMCResult;
					break;
			
				case E_FRONT_PANEL:
					nResult = stTestResult.nFPResult;
					break;
			
				case E_SN:
					nResult = stTestResult.nSNResult;
					break;
			
				case E_OTA_ID:
					nResult = stTestResult.nOTAResult;
					break;
			
				default:
					nResult = 0;
					break;
				}
				
				if(nResult == 1)
				{
					ShowMsgAndResult(hWnd, g_ActID[i]);
				}
				else
				{
					NextStartItem(hWnd, g_ActID[i]);
					break;
				}
			}
		}
	}
}

static int GetTestResultByID(int nID)
{
	int nResult = 0;
	TestResult_S stTestResult = {0};

	if(GetTestResult(&stTestResult) > 0)
	{
		switch (nID)
		{
		case E_AV:
			nResult = stTestResult.nAVResult;
			break;
	
		case E_USB:
			nResult = stTestResult.nUSBResult;
			break;
	
		case E_ETHERNET:
			nResult = stTestResult.nEthernetResult;
			break;
	
		case E_SMARTCARD:
			nResult = stTestResult.nSMCResult;
			break;
	
		case E_FRONT_PANEL:
			nResult = stTestResult.nFPResult;
			break;
	
		case E_SN:
			nResult = stTestResult.nSNResult;
			break;
	
		case E_OTA_ID:
			nResult = stTestResult.nOTAResult;
			break;
	
		default:
			break;
		}
	}

	return nResult;
}

static LRESULT DowithUserMsg( HMSWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
		case MSG_TESTAPP_PLAY:
		case MSG_TESTAPP_USB:
		case MSG_TESTAPP_ETHERNET:
		case MSG_TESTAPP_SMARTCARD:
		case MSG_TESTAPP_FRONTPANEL:
		{
			return OnTestAppItemMsg(hWnd, message, wParam);
		}
			
		case MSG_UPGRADE_START:
		case MSG_UPGRADE_SUCCESS:
		case MSG_UPGRADE_FAIL:
		case MSG_UPGRADE_TIMEOUT:
		case MSG_UPGRADE_ERASE:
		{
			return DoUpgradeMessage(hWnd, message);
		}

		case MSG_OTA_START:
		case MSG_OTA_WRITE_CORE:
		case MSG_OTA_WRITE_RC:
		case MSG_OTA_WRITE_APP:
		case MSG_OTA_OPEN_HL:
		{
			return DoOTAMessage(hWnd, message, wParam);
		}

		default:
			break;
	}	

	return 0;
}

static int GetNetTestSuccessStr(char *pacStr, int nLen)
{
	int nRet = 0;
	char acIPName[32] = { 0 };
	unsigned char aucMacName[32] = { 0 };

	if(pacStr != NULL && nLen > 0)
	{
		if(GetIPName( acIPName, sizeof(acIPName) ) == 0 && GetMacName( aucMacName, sizeof(aucMacName) ) == 0)
		{
			sprintf(pacStr, "IP:%s, Mac:%s", acIPName, aucMacName);
			nRet = 1;
		}
	}

	return nRet;
}

static void ShowMsgAndResult(HMSWND hWnd, int nID)
{
	if(g_ItemID[nID] != E_MAX)
	{
		char acMsgStr[128] = { 0 };
		char acResultStr[64] = { 0 };
		MSRECT stRect = {0};
		int nFlag = 1;
		int nResult = 0;
		
		nResult = GetTestResultByID(nID);
		
		switch (nID)
		{
		case E_AV:
		{				  
			if (nResult == 0)
			{	
				SetAVTestDeliveryInfo(acMsgStr, sizeof(acMsgStr)); 					
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 1)
			{
			   strcpy(acMsgStr, "AV Test Finished");
			   strcpy(acResultStr, PASS_STR);
			}
			else if (nResult == 4)
			{
			   strcpy(acMsgStr, "Tuner 1 play Freqency timeout");
			   strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 5)
			{
			   strcpy(acMsgStr, "Tuner 2 play Freqency timeout");
			   strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 8)
			{
			   strcpy(acMsgStr, "Tuner 1 play Freqency timeout");
			   strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 9)
			{
			   //strcpy(acMsgStr, "Tuner 2 play Freqency timeout");
			   //strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 16)
			{
			   //strcpy(acMsgStr, "Tuner 1 Lock Freqency fail");
			   //strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 17)
			{
			   //strcpy(acMsgStr, "Tuner 2 Lock Freqency fail");
			   //strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 32)
			{
			   //strcpy(acMsgStr, "Tuner 1 Lock Freqency fail");
			   //strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 33)
			{
			   //strcpy(acMsgStr, "Tuner 2 Lock Freqency fail");
			   //strcpy(acResultStr, FAIL_STR);
			}
			else
			{
			   //strcpy(acMsgStr, "AV Test Finished");
			   //strcpy(acResultStr, FAIL_STR);
			}
		}
			break;
	
		case E_USB:
		{					
			if (nResult == 0)
			{
				strcpy(acMsgStr, "Please Insert USB Device");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 1)
			{
				strcpy(acMsgStr, "USB Test Finished");
				strcpy(acResultStr, PASS_STR);
			}
			else if (nResult == 2)
			{
				strcpy(acMsgStr, "No USB Inserted");
				strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 3)
			{
				strcpy(acMsgStr, "USB Port2 NOT Inserted");
				strcpy(acResultStr, FAIL_STR);
			}
			else if (nResult == 4)
			{
				strcpy(acMsgStr, "USB Port1 NOT Inserted");
				strcpy(acResultStr, FAIL_STR);
			}
			else
			{
				strcpy(acMsgStr, "USB Test Finished");
				strcpy(acResultStr, FAIL_STR);
			}
		}
			break;
	
		case E_ETHERNET:
		{					
			if (nResult == 0)
			{
				strcpy(acMsgStr, "Please Insert Ethernet Cable");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 1)
			{
				if(GetNetTestSuccessStr( acMsgStr, sizeof(acMsgStr)) == 0)
				{
					strcpy(acMsgStr, "Ethernet Test Finished");
				}
				strcpy(acResultStr, PASS_STR);
			}
			else if (nResult == 2)
			{
				strcpy(acMsgStr, "No Ethernet Cable Inserted");
				strcpy(acResultStr, FAIL_STR);
			}
			else
			{
				strcpy(acMsgStr, "Ethernet Test Finished");
				strcpy(acResultStr, FAIL_STR);
			}
		}
			break;
	
		case E_SMARTCARD:
		{		
			if (nResult == 0)
			{
				strcpy(acMsgStr, "Please Insert SmartCard");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 1)
			{
				strcpy(acMsgStr, "SmartCard Test Finished");
				strcpy(acResultStr, PASS_STR);
			}
			else if (nResult == 2)
			{
				strcpy(acMsgStr, "No SmartCard Inserted");
				strcpy(acResultStr, FAIL_STR);
			}
			else
			{
				strcpy(acMsgStr, "SmartCard Test Finished");
				strcpy(acResultStr, FAIL_STR);
			}
		}
			break;
	
		case E_FRONT_PANEL:
		{
			if(g_bFrontKeyPressed)
			{
				return ;
			}
			if (nResult == 0)
			{
				strcpy(acMsgStr, "Please Press Front Button One by One");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 1)
			{
				strcpy(acMsgStr, "Front Panel Test Finished");
				strcpy(acResultStr, PASS_STR);
			}
			else
			{
				strcpy(acMsgStr, "Front Panel Test Finished");
				strcpy(acResultStr, FAIL_STR);
			}
		}
			break;
	
		case E_SN:
		{
			if (nResult != 1)
			{
				char acSN[MAX_SN_LEN] = {0};
				
				if(nResult != 0 && ReadSTBID(acSN, sizeof(acSN)) == E_DATA_SUCCESS)
				{
					sprintf(acMsgStr, "SN:%s", acSN);
					strcpy(acResultStr, NOT_VERIFY);
				}
				else
				{
					strcpy(acMsgStr, "Please Connect Uart");
					strcpy(acResultStr, NOT_TEST_STR);
				}
			}
			else if (nResult == 1)
			{
				char acSN[MAX_SN_LEN] = {0};
				
				if(ReadSTBID(acSN, sizeof(acSN)) == E_DATA_SUCCESS)
				{
					sprintf(acMsgStr, "SN:%s", acSN);
					strcpy(acResultStr, PASS_STR);
				}
			}
		}
			break;
	
		case E_OTA_ID:
		{
			if (nResult == 0)
			{
				strcpy(acMsgStr, "Waiting for Other Test Finish");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 1)
			{
				strcpy(acMsgStr, "OTA Test Finished");
				strcpy(acResultStr, PASS_STR);
			}
			else if (nResult == 2)
			{
				strcpy(acMsgStr, "Core Write Success");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 4)
			{
				strcpy(acMsgStr, "Core Write Success");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else if (nResult == 32)
			{
				strcpy(acMsgStr, "Open HL Success");
				strcpy(acResultStr, NOT_TEST_STR);
			}
			else
			{
				strcpy(acMsgStr, "Begin Locking OTA frequency");
				strcpy(acResultStr, NOT_TEST_STR);
			}
		}
			break;
	
		default:
			nFlag = 0;
			break;
		}

		if (nFlag == 1)
		{
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[nID]].MSGIDS, acMsgStr, strlen(acMsgStr));
			MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[nID]].ResultIDS, acResultStr, strlen(acResultStr));

			MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[g_ItemID[nID]].ButtonIDS), &stRect);
			MSInvalidateRect(hWnd, &stRect, FALSE);
		}
	}
}

static void VoltageShowMsgAndResult(HMSWND hWnd, int nID)
{
	int nFlag = 1;
	char acMsgStr[128] = { 0 };
	char acResultStr[64] = { 0 };
	MSRECT stRect = {0}; 
	
	switch(nID)
	{
		case E_22K:
		{
			memcpy(acMsgStr, "The 22k switch is ON", sizeof("The 22k switch is ON"));
			memcpy(acResultStr, "ON", sizeof("ON"));
		}
			break;
			
		case E_DIS:
		{
			if(GetColorMode() == EM_ADISCART_COLOR_RGB)
			{
				memcpy(acMsgStr, "The Color Mode is RGB", sizeof("The Color Mode is RGB"));
				memcpy(acResultStr, "1--3V", sizeof("1--3V"));
			}
			else
			{
				memcpy(acMsgStr, "The Color Mode is CVBS", sizeof("The Color Mode is CVBS"));
				memcpy(acResultStr, "0--0.4V", sizeof("0--0.4V"));
			}
		}
			break;
			
		case E_ASP:
		{
			if(GetDisplayMode() == EM_ADISCART_DISPLAY_16_9)
			{
				memcpy(acMsgStr, "The Aspect Ratio is 16:9", sizeof("The Aspect Ratio is 16:9"));
				memcpy(acResultStr, "5--7V", sizeof("5--7V"));
			}
			else
			{
				memcpy(acMsgStr, "The Aspect Ratio is 4:3", sizeof("The Aspect Ratio is 4:3"));
				memcpy(acResultStr, "9.5--12V", sizeof("9.5--12V"));
			}
		}
			break;
			
		case E_STUNER:
		{
			if(GetPolarMode() == EM_ADITUNER_POLARISATION_H)
			{
				memcpy(acMsgStr, "The POLARISATION in POLAR_H Mode", sizeof("The POLARISATION in POLAR_H Mode"));
				memcpy(acResultStr, "18V", sizeof("18V"));
			}
			else
			{
				memcpy(acMsgStr, "The POLARISATION in POLAR_V Mode", sizeof("The POLARISATION in POLAR_V Mode"));
				memcpy(acResultStr, "13V", sizeof("13V"));
			}
		}
			break;
			
		case E_TTUNER:
		{
			if(GetPowerEnable())
			{
				memcpy(acMsgStr, "Tuner with electric", sizeof("Tuner with electric"));
				memcpy(acResultStr, "5V", sizeof("5V"));
			}
			else
			{
				memcpy(acMsgStr, "Tuner with no electric", sizeof("Tuner with no electric"));
				memcpy(acResultStr, "0V", sizeof("0V"));
			}
		}
			break;
			
		case E_CARD:
			if(ReadCardID(acMsgStr, sizeof(acMsgStr)) == 1)
			{
				strcpy(acResultStr, PASS_STR);
			}
			else
			{
				strcpy(acResultStr, FAIL_STR);
			}
			break;
			
		case E_IR:
		{
			memcpy(acMsgStr, "Test By Manually Press RCU", sizeof("Test By Manually Press RCU"));
			memcpy(acResultStr, "ManualTest", sizeof("ManualTest"));
		}
			break;
		
		default:
			nFlag = 0;
			break;
	}
	
	if( nFlag && g_ItemID[nID] != E_MAX )
	{
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[nID]].MSGIDS, acMsgStr, strlen(acMsgStr));
		MSSetDlgItemTextByChar(hWnd, g_AllTestCtrl[g_ItemID[nID]].ResultIDS, acResultStr, strlen(acResultStr));
		MSGetWindowRect(MSGetDlgItem(hWnd, g_AllTestCtrl[g_ItemID[nID]].ButtonIDS), &stRect);
		MSInvalidateRect(hWnd, &stRect, FALSE);
	}
}

static void InitAllInfo(HMSWND hWnd)
{
	int ii = 0;

	if(g_ActTestCount == 0)
	{
		g_pInputKey = GetInputKeyStruct();

		g_ActTestCount = GetItemCount();

		g_ActTestItem = GetItemInfo();

		g_AllTestCtrl = GetIDCInfo();

		g_ActID = GetIndex();

		for(ii = 0; ii < E_MAX; ii++)
		{
			g_ItemID[ii] = E_MAX;
		}
		
		for(ii = 0; ii < g_ActTestCount; ii++)
		{
			g_ItemID[g_ActID[ii]] = ii;
		}

		for (ii = 0; ii < g_ActTestCount; ii++)
		{
			if(g_ActTestItem[g_ActID[ii]].enTestType == E_AUTO)
			{
				g_nTimerIndex[ii] = g_ActID[ii];
				g_nTimerNum++;
			}
		}
	}
	
	for(ii = 0; ii < g_ActTestCount; ii++)
	{
		if(g_ActTestItem[g_ActID[ii]].enTestType != E_MANU)
		{
			VoltageShowMsgAndResult(hWnd, g_ActID[ii]);
		}
	}

	if(g_nTimerNum > 0)
	{
		MSSetTimer(hWnd, SWITCH_ITEM_TIMER, 1000, NULL);
	}
}

void USBUpgrade(void)
{
	ADIBLOtaLoaderPt_S stLrdPt;
	memset(&stLrdPt, 0, sizeof(stLrdPt));
	stLrdPt.eDLType = E_ADIBL_USB_DL;

	ADIBLSaveOTALoaderPt(&stLrdPt, 1, 1);

	ADIOSThreadSleep(2000);

	ADISYSReboot();

}
