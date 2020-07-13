#include "AuraRC.h"
#include "UIViewInfo.h"
#include "FactoryTestKey.h"

static IDCInfo g_stControl[] = 
{
	{ IDC_ITEM1, 		IDC_ITEM1_MSG, 			IDC_ITEM1_RESULT },
	{ IDC_ITEM2, 		IDC_ITEM2_MSG, 			IDC_ITEM2_RESULT },
	{ IDC_ITEM3, 		IDC_ITEM3_MSG, 			IDC_ITEM3_RESULT },
	{ IDC_ITEM4, 		IDC_ITEM4_MSG, 			IDC_ITEM4_RESULT },
	{ IDC_ITEM5, 		IDC_ITEM5_MSG, 			IDC_ITEM5_RESULT },
	{ IDC_ITEM6, 		IDC_ITEM6_MSG, 			IDC_ITEM6_RESULT },
	{ IDC_AV, 			IDC_AV_MSG, 			IDC_AV_RESULT },
	{ IDC_USB, 			IDC_USB_MSG, 			IDC_USB_RESULT },
	{ IDC_Network, 		IDC_Network_MSG, 		IDC_Network_RESULT},
	{ IDC_SmartCard, 	IDC_SmartCard_MSG, 		IDC_SmartCard_RESULT },
	{ IDC_FRONT_PANEL, 	IDC_FRONT_PANEL_MSG, 	IDC_FRONT_PANEL_RESULT },
	{ IDC_SN, 			IDC_SN_MSG, 			IDC_SN_RESULT },
	{ IDC_OTA, 			IDC_OTA_MSG, 			IDC_OTA_RESULT }
};

static ItemInfo g_sItemInfo[] = 
{
	{E_AUTO, E_22K, 		"22K"},
	{E_AUTO, E_ASP, 		"Ratio"},
	{E_AUTO, E_DIS, 		"Display"},
	{E_AUTO, E_STUNER, 		"STuner"},
	{E_AUTO, E_TTUNER, 		"ETuner"},
	{E_STIC, E_CARD, 		"CardID"},
	{E_STIC, E_IR, 			"IRLine"},
	{E_MANU, E_AV, 			"AV"},
	{E_MANU, E_USB, 		"USB"},
	{E_MANU, E_ETHERNET, 	"Ethernet"},
	{E_MANU, E_SMARTCARD, 	"SmartCard"},
	{E_MANU, E_FRONT_PANEL, "FrontPanel"},
	{E_MANU, E_SN, 			"SN"},
	{E_MANU, E_OTA_ID, 		"OTA"}
};

static InputKeyStruct g_sInputKey[7] = 
{
	{FT_VK_FP_POWER, 	"POWER", 	0},
	{FT_VK_FP_OK, 		"OK", 		0},
	{FT_VK_FP_UP, 		"CH+", 		0},
	{FT_VK_FP_DOWN, 	"CH-", 		0},
	{FT_VK_FP_RIGHT, 	"VOL+", 	0},
	{FT_VK_FP_LEFT, 	"VOL-", 	0},
	{FT_VK_FP_MENU, 	"MENU", 	0}
};

static int g_TestCount = 0;

static ItemID g_Index[E_MAX] = { E_MAX }; 

IDCInfo *GetIDCInfo( void )
{
	return g_stControl;
}

ItemInfo *GetItemInfo( void )
{
	return g_sItemInfo;
}

InputKeyStruct *GetInputKeyStruct( void )
{
	return g_sInputKey;
}

int GetInputKeyCount( void )
{
	return sizeof(g_sInputKey) / sizeof(InputKeyStruct);
}

int GetItemCount( void )
{
	return g_TestCount;
}

ItemID *GetIndex( void )
{
	return g_Index;
}

void SetTestItem(int nTestItem[], int nCount)
{
	if( nCount < E_MAX )
	{		
		for(int ii = 0; ii < nCount; ii++)
		{
			g_Index[ii] = (ItemID)nTestItem[ii];
		}
		g_TestCount = nCount;
	}
}

void SetTestItem(BaseTestItem csBaseTestItem)
{
	if(csBaseTestItem.m_nS22K)
	{
		g_Index[g_TestCount++] = E_22K;
	}
	if(csBaseTestItem.m_nASP)
	{
		g_Index[g_TestCount++] = E_ASP;
	}
	if(csBaseTestItem.m_nDis)
	{
		g_Index[g_TestCount++] = E_DIS;
	}
	if(csBaseTestItem.m_nST)
	{
		g_Index[g_TestCount++] = E_STUNER;
	}
	if(csBaseTestItem.m_nTT)
	{
		g_Index[g_TestCount++] = E_TTUNER;
	}
	if(csBaseTestItem.m_nCR)
	{
		g_Index[g_TestCount++] = E_CARD;
	}
	if(csBaseTestItem.m_nIR)
	{
		g_Index[g_TestCount++] = E_IR;
	}
	if(csBaseTestItem.m_nAV)
	{
		g_Index[g_TestCount++] = E_AV;
	}
	if(csBaseTestItem.m_nUSB)
	{
		g_Index[g_TestCount++] = E_USB;
	}
	if(csBaseTestItem.m_nNet)
	{
		g_Index[g_TestCount++] = E_ETHERNET;
	}
	if(csBaseTestItem.m_nSMC)
	{
		g_Index[g_TestCount++] = E_SMARTCARD;
	}
	if(csBaseTestItem.m_nFP)
	{
		g_Index[g_TestCount++] = E_FRONT_PANEL;
	}
	if(csBaseTestItem.m_nSN)
	{
		g_Index[g_TestCount++] = E_SN;
	}
	if(csBaseTestItem.m_nOTA)
	{
		g_Index[g_TestCount++] = E_OTA_ID;
	}
}

int GetCtrlCount( void )
{
	return sizeof(g_stControl) / sizeof(IDCInfo);
}

