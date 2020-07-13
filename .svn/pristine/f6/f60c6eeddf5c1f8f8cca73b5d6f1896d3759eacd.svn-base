#ifndef UI_VIEW_INFO_H_
#define UI_VIEW_INFO_H_

#include "BaseTestItem.h"

typedef struct
{
	int ButtonIDS;
	int MSGIDS;
	int ResultIDS;
}IDCInfo;

typedef enum 
{
	E_22K=0,
	E_ASP,
	E_DIS,
	E_STUNER,
	E_TTUNER,
	E_CARD,
	E_IR,
	E_AV,
	E_USB,
	E_ETHERNET,
	E_SMARTCARD,
	E_FRONT_PANEL,
	E_SN,
	E_OTA_ID,
	E_MAX
}ItemID;

typedef enum
{
	E_AUTO=0,
	E_MANU,
	E_STIC,
	E_UNKNOW
}TestType;

typedef struct
{
	TestType enTestType;
	ItemID enItemID;
	char acStr[64];	
}ItemInfo;

typedef struct
{
	unsigned int unKey;
	char acName[8];
	unsigned int unPressed;
}InputKeyStruct;

IDCInfo *GetIDCInfo( void );

ItemInfo *GetItemInfo( void );

InputKeyStruct *GetInputKeyStruct( void );

int GetItemCount( void );

void SetTestItem(BaseTestItem csBaseTestItem);

int GetCtrlCount( void );

ItemID *GetIndex( void );

int GetInputKeyCount( void );

#endif/*UI_VIEW_INFO_H_*/

