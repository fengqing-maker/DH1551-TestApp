#include "adi_os.h"
#include "RemoteKey.h"
#include "Aura.h"
#include "adi_toolset.h"
#include "adi_hdicommon.h"
#include "AuraDesktop.h"
#include "MsUserMessagedefine.h"
#include "FactoryTestKey.h"

void RegisterStandbyParams();

static ADIIRDecode_S g_sIrDecode_MTCFactoryTest[] =
{
	{ 0x0F, FT_VK_F0, ADI_TRUE },
	{ 0x8F, FT_VK_F1, ADI_TRUE },
	{ 0x4F, FT_VK_F2, ADI_TRUE },
	{ 0xCF, FT_VK_F3, ADI_TRUE },
	{ 0x2F, FT_VK_F4, ADI_TRUE },
	{ 0xAF, FT_VK_F5, ADI_TRUE },
	{ 0x6F, FT_VK_F6, ADI_TRUE },
	{ 0xEF, FT_VK_F7, ADI_TRUE },
	{ 0x1F, FT_VK_F8, ADI_TRUE },
	{ 0x9F, FT_VK_F9, ADI_TRUE },
	{ 0x5F, FT_VK_FA, ADI_TRUE },
	{ 0xDF, FT_VK_FB, ADI_TRUE },
	{ 0x3F, FT_VK_FC, ADI_TRUE },
	{ 0xBF, FT_VK_FD, ADI_TRUE },
	{ 0x7F, FT_VK_FE, ADI_TRUE },
	{ 0xFF, FT_VK_FF, ADI_TRUE },
	{ 0x07, FT_VK_E0, ADI_TRUE },
	{ 0x87, FT_VK_E1, ADI_TRUE },
	{ 0x47, FT_VK_E2, ADI_TRUE },
	{ 0xC7, FT_VK_E3, ADI_TRUE },
	{ 0x27, FT_VK_E4, ADI_TRUE },
	{ 0xA7, FT_VK_E5, ADI_TRUE },
	{ 0x67, FT_VK_E6, ADI_TRUE },
	{ 0xE7, FT_VK_E7, ADI_TRUE },
	{ 0x17, FT_VK_E8, ADI_TRUE },
	{ 0x8B, FT_VK_D1, ADI_TRUE },
	{ 0x4B, FT_VK_D2, ADI_TRUE },
	{ 0xCB, FT_VK_D3, ADI_TRUE },
	{ 0x2B, FT_VK_D4, ADI_TRUE },
	{ 0xAB, FT_VK_D5, ADI_TRUE },
	{ 0x6B, FT_VK_D6, ADI_TRUE },
	{ 0xEB, FT_VK_D7, ADI_TRUE },
	{ 0x1B, FT_VK_D8, ADI_TRUE },
	{ 0x0B, FT_VK_D9, ADI_TRUE },
};

static ADIIRDecode_S g_sMAS_TV[] =
{
	{ 0x10, VK_POWER, ADI_TRUE },
	{ 0x17, VK_MUTE, ADI_TRUE },
	{ 0x41, VK_TV_RADIO, ADI_TRUE },
	{ 0x5A, VK_SUBTITLE, ADI_TRUE },
	{ 0x46, VK_AUDIO, ADI_TRUE },
	{ 0x01, VK_1, ADI_TRUE },
	{ 0x02, VK_2, ADI_TRUE },
	{ 0x03, VK_3, ADI_TRUE },
	{ 0x04, VK_4, ADI_TRUE },
	{ 0x05, VK_5, ADI_TRUE },
	{ 0x06, VK_6, ADI_TRUE },
	{ 0x07, VK_7, ADI_TRUE },
	{ 0x08, VK_8, ADI_TRUE },
	{ 0x09, VK_9, ADI_TRUE },
	{ 0x59, VK_HDMI, ADI_TRUE },
	{ 0x0, VK_0, ADI_TRUE },
	{ 0x0A, VK_RECALL, ADI_TRUE },
	{ 0x0E, VK_VOLUME_UP, ADI_TRUE },
	{ 0x0F, VK_VOLUME_DOWN, ADI_TRUE },
	{ 0x0C, VK_CHANNEL_UP, ADI_TRUE },
	{ 0x0D, VK_CHANNEL_DOWN, ADI_TRUE },
	{ 0x19, VK_UP, ADI_TRUE },
	{ 0x1A, VK_DOWN, ADI_TRUE },
	{ 0x1B, VK_LEFT, ADI_TRUE },
	{ 0x1C, VK_RIGHT, ADI_TRUE },
	{ 0x1D, VK_RETURN, ADI_TRUE },
	{ 0x15, VK_MENU, ADI_TRUE },
	{ 0x5B, VK_FAV, ADI_TRUE },
	{ 0x4B, VK_GUIDE, ADI_TRUE },
	{ 0x0B, VK_INFO, ADI_TRUE },
	{ 0x43, VK_RED, ADI_TRUE },
	{ 0x40, VK_GREEN, ADI_TRUE },
	{ 0x46, VK_YELLOW, ADI_TRUE },
	{ 0x59, VK_BLUE, ADI_TRUE },
	{ 0x42, VK_MEDIA, ADI_TRUE },
	{ 0x53, VK_FB, ADI_TRUE },
	{ 0x52, VK_FF, ADI_TRUE },
	{ 0x1E, VK_RETREAT, ADI_TRUE },
	{ 0x49, VK_JOG, ADI_TRUE },
	{ 0x13, VK_RECORD, ADI_TRUE },
	{ 0x57, VK_PAUSE, ADI_TRUE },
	{ 0x58, VK_STOP, ADI_TRUE },
	{ 0x2A, VK_SLEEP, ADI_TRUE },
	{ 0x2B, VK_TIMER, ADI_TRUE },
	{ 0x16, VK_EXIT, ADI_TRUE },
	{ 0x48, FT_VK_FE, ADI_TRUE },
	{ 0x4f, FT_VK_E2, ADI_TRUE },
	{ 0x50, FT_VK_E3, ADI_TRUE },
	{ 0x51, FT_VK_E5, ADI_TRUE },
	{ 0x47, FT_VK_F9, ADI_TRUE }
};

//TS-Y82-48 userID 02FD  protocol NEC6122
static ADIIRDecode_S g_sIrDecode_TSY82 [ ] =
{
	// 
	{ 0x0E, VK_POWER, ADI_TRUE },
	{ 0x40, VK_MUTE, ADI_TRUE },
	{ 0x05, VK_TV_RADIO, ADI_TRUE },
	{ 0x62, VK_TELETEXT, ADI_TRUE },
	{ 0x06, VK_SUBTITLE, ADI_TRUE },
	{ 0x60, VK_AUDIO, ADI_TRUE },
	{ 0x12, VK_1, ADI_TRUE },
	{ 0x16, VK_2, ADI_TRUE },
	{ 0x02, VK_3, ADI_TRUE },
	{ 0x1A, VK_4, ADI_TRUE },
	{ 0x1E, VK_5, ADI_TRUE },
	{ 0x03, VK_6, ADI_TRUE },
	{ 0x0F, VK_7, ADI_TRUE },
	{ 0x0B, VK_8, ADI_TRUE },
	{ 0x07, VK_9, ADI_TRUE },
	{ 0x09, VK_HDMI, ADI_TRUE },
	{ 0x44, VK_0, ADI_TRUE },
	{ 0x4C, VK_RECALL, ADI_TRUE },
	{ 0x51, VK_VOLUME_UP, ADI_TRUE },
	{ 0x59, VK_VOLUME_DOWN, ADI_TRUE },
	{ 0x1D, VK_PAGE_DOWN, ADI_TRUE },
	{ 0x00, VK_PAGE_UP, ADI_TRUE },
	{ 0x54, VK_CHANNEL_UP, ADI_TRUE },
	{ 0x5C, VK_CHANNEL_DOWN, ADI_TRUE },
	{ 0x41, VK_UP, ADI_TRUE },
	{ 0x45, VK_DOWN, ADI_TRUE },
	{ 0x4D, VK_LEFT, ADI_TRUE },
	{ 0x5D, VK_RIGHT, ADI_TRUE },
	{ 0x11, VK_RETURN, ADI_TRUE },
	{ 0x50, VK_MENU, ADI_TRUE },
	{ 0x01, VK_BACK, ADI_TRUE },
	{ 0x0C, VK_MAIL_INFO, ADI_TRUE },
	{ 0x56, VK_FAV, ADI_TRUE },
	{ 0x48, VK_GUIDE, ADI_TRUE },
	{ 0x58, VK_INFO, ADI_TRUE },
	{ 0x13, VK_RED, ADI_TRUE },
	{ 0x17, VK_GREEN, ADI_TRUE },
	{ 0x1B, VK_YELLOW, ADI_TRUE },
	{ 0x1F, VK_BLUE, ADI_TRUE },
	{ 0x55, VK_GAME, ADI_TRUE },
	{ 0x61, VK_MEDIA, ADI_TRUE },
	{ 0x42, VK_FB, ADI_TRUE },
	{ 0x5A, VK_FF, ADI_TRUE },
	{ 0x63, VK_RETREAT, ADI_TRUE },
	{ 0x64, VK_JOG, ADI_TRUE },
	{ 0x0D, VK_RECORD, ADI_TRUE },
	{ 0x46, VK_PLAY, ADI_TRUE },
	{ 0x4A, VK_PAUSE, ADI_TRUE },
	{ 0x65, VK_STOP, ADI_TRUE },
	{ 0x2A, VK_SLEEP, ADI_TRUE },
	{ 0x2B, VK_TIMER, ADI_TRUE },
	{ 0x08, VK_PVR, ADI_TRUE },	
	{ 0x4B, VK_EXIT, ADI_TRUE},	
};

static ADIIREquipList_S g_sIrEquipList_MTCFT =
{
	EM_ADIIR_PROTOCOL_NEC,
	0xD5B3,
	sizeof(g_sIrDecode_MTCFactoryTest) / sizeof(ADIIRDecode_S),
	g_sIrDecode_MTCFactoryTest
};

static ADIIREquipList_S g_sIrMAS_TV =
{
	EM_ADIIR_PROTOCOL_NEC,
	0x08F7,
	sizeof(g_sMAS_TV) / sizeof(ADIIRDecode_S),
	g_sMAS_TV
};

static ADIIREquipList_S g_sIrEquipList_TSY82 =
{
	EM_ADIIR_PROTOCOL_NEC,
	0x02FD,
	sizeof( g_sIrDecode_TSY82 ) / sizeof( ADIIRDecode_S ),
	g_sIrDecode_TSY82
};

void AppIrCallBack(ADIKeyCallbackType eCallbackType ,void * pvUserData)
{
	ADIKeyParam_S * pstKeyParam = (ADIKeyParam_S *)pvUserData;

	if  (EM_ADI_KEY_RELEASE== pstKeyParam->m_eKeyStatus || pstKeyParam->m_uLogicValue == 0)  // 表示按键弹起
	{
		return;
	}
	
	if (EM_ADI_KEY_CALLBACK_PANEL == eCallbackType)
	{
		unsigned int unFactoryTestKey = 0;

		switch (pstKeyParam->m_uLogicValue)
		{
		case ADI_VK_POWER:
			unFactoryTestKey = FT_VK_FP_POWER;
			break;
		case ADI_VK_OK:
			unFactoryTestKey = FT_VK_FP_OK;
			break;
		case VK_LEFT:
			unFactoryTestKey = FT_VK_FP_LEFT;
			break;
		case VK_RIGHT:
			unFactoryTestKey = FT_VK_FP_RIGHT;
			break;
		case VK_UP:
			unFactoryTestKey = FT_VK_FP_UP;
			break;
		case VK_DOWN:
			unFactoryTestKey = FT_VK_FP_DOWN;
			break;
		default:
			return;
		}

		pstKeyParam->m_uLogicValue = unFactoryTestKey;
	}

	printf("%s %d pstKeyParam->m_uLogicValue=0x%x \n", __FUNCTION__, __LINE__, pstKeyParam->m_uLogicValue);

	AuraInputKeyEvent(pstKeyParam->m_uLogicValue);

}

void AppIrDebugCallBack(ADIKeyCallbackType eCallbackType, void * pvUserData)
{
	ADIIRDebug_t * pstKeyParam = (ADIIRDebug_t *)pvUserData;

	if (EM_ADI_KEY_PRESS == pstKeyParam->m_ucKeyStatus)
	{
		printf("%s %d IrDebug usercode=0x%x keycode=0x%x\n", __FUNCTION__, __LINE__, pstKeyParam->m_dwUserID, pstKeyParam->m_dwKeyCode);
	}
}

ADIIREquipList_S*  GetIrWquipList_MTCFT(void)
{
	return &g_sIrEquipList_MTCFT;
}

static ADIIREquipList_S*  GetIrMAS_TV(void)
{
	return &g_sIrMAS_TV;
}

static ADIIREquipList_S*  GetIrWquipList_TSY82 ( void )
{
	return &g_sIrEquipList_TSY82;
}

void MSAppIrInit()
{
	unsigned int hIRHandle;
    ADIIRAddKeySendCallback(AppIrCallBack);
	//ADIIRAddKeyDebugCallback(AppIrDebugCallBack);
	RegisterStandbyParams();
	ADIIRAddEquipment(GetIrWquipList_MTCFT(), &hIRHandle);
	//ADIIRAddEquipment(GetIrMAS_TV(), &hIRHandle);
	//ADIIRAddEquipment(GetIrWquipList_TSY82(), &hIRHandle);
}

void RegisterStandbyParams()
{
	ADISYSWakeupParams_S stParam;
	ADI_BOOL bReal = TRUE;
	
	memset(&stParam, 0, sizeof(stParam));
	stParam.m_bModeEnable = ADI_TRUE;
	stParam.m_eWakeUpMode = ADISYS_WAKEUPE_MODE_IR;
	stParam.m_uWakeupParams.m_stIRKeys.m_nKeyNum = 1;
	stParam.m_uWakeupParams.m_stIRKeys.m_astKeys[0].m_eIRProtocol = EM_ADIIR_PROTOCOL_NEC;
	stParam.m_uWakeupParams.m_stIRKeys.m_astKeys[0].m_nUserID = 0x02FD;
	stParam.m_uWakeupParams.m_stIRKeys.m_astKeys[0].m_nKeyCode = 0x0E;
	
	ADISYSSetWakeupParams(&stParam);
}

