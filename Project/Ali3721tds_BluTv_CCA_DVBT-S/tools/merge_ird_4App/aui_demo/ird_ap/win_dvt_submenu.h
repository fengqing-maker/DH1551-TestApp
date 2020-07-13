/*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_dvt_submenu.h
*
*    Description: solution to show all the submenu.
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/

#ifndef _WIN_SUBMENU_H_
#define _WIN_SUBMENU_H_
#ifdef __cplusplus
extern "C"
{
#endif


#define UI_MENU_FOR_DEMO    1
#define C_SUBMENU_PAGE      9
#define C_SUBMENU_ID_BASE   1

typedef UINT8 (*check_item_active)(UINT32 item_id);

typedef enum
{
    ITEM_TYPE_NOMAL = 0,
    ITEM_TYPE_SUBSET,
}menu_item_type_t;

typedef struct
{
    UINT8  item_type;
    UINT16 item_name;
    UINT8  need_pwd;
    PFN_CALLBACK item_callback;
}sub_menu_item_t;


typedef struct _sub_menu
{
    UINT16  item_count;
    UINT16  title_id;
    sub_menu_item_t *items;
    PFN_CALLBACK  menu_callback;
    check_item_active check_item_active;
    UINT16 list_page;
    UINT16 list_top;
    UINT16 list_sel;
}sub_menu_t;

enum
{
    MEDIAPLAYER_ID = 1,
    EDITCHAN_ID ,
    INSTALL_ID,
    SYSTEMSET_ID,
    TOOLS_ID,
//  GAMES_ID,
//  REC_ID,
};
/*************mediaplayer***************/
enum
{
        MEDIAPLAYER_RECORD_ID = C_SUBMENU_ID_BASE,
        MEDIAPLAYER_VIDEO_ID,
        MEDIAPLAYER_MUSIC_ID,
        MEDIAPLAYER_IMAGE_ID,
};

/*************editchannel***************/
enum
{
    CHLIST_TV_LIST_ID = C_SUBMENU_ID_BASE,
    CHLIST_RADIO_LIST_ID,
    CHLIST_DELETE_ALL_CHAN_ID,
};

/*************installation***************/
#if 0
enum
{
#if (SYS_PROJECT_FE == PROJECT_FE_DVBC)
    INSTALL_QUICKSCAN_ID = C_SUBMENU_ID_BASE,
    INSTALL_AUTOSCAN_ID,
#else
    INSTALL_ANTENNA_CONNECT_ID = C_SUBMENU_ID_BASE,
    INSTALL_SAT_LIST_ID,
    INSTALL_ANTENNA_SET_ID,
    INSTALL_SINGLESRCH_ID,
    INSTALL_MULTISRCH_ID,
    INSTALL_TPSRCH_ID,
#endif

    INSTALL_T_AUTOSCAN_ID,
    INSTALL_T_CHANSCAN_ID,

#ifdef USB_LOGO_TEST
    INSTALL_USB_ELECTRIAL_TEST_ID,
#endif
};
#endif
/*************conditional access**********/
enum
{
    WIN_SUBSCRIPTION_ID = C_SUBMENU_ID_BASE,
    WIN_EVENT_ID,
    WIN_PURSE_ID,
    WIN_CAPIN_ID,
    WIN_MATURITY_ID,
    WIN_CAABOUT_ID,
    WIN_MAILLIST_ID,
};

/*************system***************/
enum
{
    SYSTEM_LANG_ID = C_SUBMENU_ID_BASE,
    SYSTEM_TV_ID,
#ifdef DISPLAY_SETTING_SUPPORT
    SYSTEM_DISPLAY_ID,
#endif
    SYSTEM_TIME_ID,
    SYSTEM_TIMER_ID,
    SYSTEM_PARENT_ID,
    SYSTEM_OSDSET_ID,
#ifdef _INVW_JUICE
#else
#ifdef FAV_GROP_RENAME
    SYSTEM_FAVNAME_ID,
#endif
#endif
#ifdef AUDIO_DESCRIPTION_SUPPORT
    SYSTEM_AUDIO_DESCRIPTION_ID,
#endif
#ifdef MULTIVIEW_SUPPORT
        SYSTEM_MULTIVIEW_ID,
#endif

#ifndef DISABLE_PVR_TMS
#ifdef _INVW_JUICE
    RECORD_HDDINFO_ID,
    RECORD_PVR_SETTING,
#ifndef DISK_MANAGER_SUPPORT
    RECORD_PVRMANAGE_ID ,
    RECORD_HDDFORMAT_ID,
#endif
#else
#ifndef DISK_MANAGER_SUPPORT
    RECORD_PVRMANAGE_ID ,
    RECORD_HDDINFO_ID,
#else
    RECORD_HDDINFO_ID ,
#endif

    RECORD_PVR_SETTING,
    RECORD_HDDFORMAT_ID,
#endif
#endif

        SYSTEM_MISC_ID,
};

/*************tools***************/
enum
{
    TEST_APP_LOADER_ID = C_SUBMENU_ID_BASE,
    TEST_APP_MEM_ID,
    TEST_APP_MODULE_ID,
    TEST_APP_LOADER_NV_ID,
    TEST_APP_UPG_ID,
    TEST_APP_STATUS_ID,
    TEST_APP_NOTE1_ID,
    TEST_APP_NOTE2_ID,
};

/*************game***************/
/*enum
{
    GAMES_SNAKE_ID = C_SUBMENU_ID_BASE,
    GAMES_SUDOKU_ID,
};
*/
/*
enum
{
#ifndef DISK_MANAGER_SUPPORT
    RECORD_PVRMANAGE_ID = C_SUBMENU_ID_BASE,
    RECORD_HDDINFO_ID,
#else
    RECORD_HDDINFO_ID = C_SUBMENU_ID_BASE,
#endif
    RECORD_PVR_SETTING,
    RECORD_HDDFORMAT_ID,
};
*/
extern CONTAINER g_win_submenu;

extern CONTAINER subm_item_con1;
extern CONTAINER subm_item_con2;
extern CONTAINER subm_item_con3;
extern CONTAINER subm_item_con4;
extern CONTAINER subm_item_con5;
extern CONTAINER subm_item_con6;
extern CONTAINER subm_item_con7;
extern CONTAINER subm_item_con8;
extern CONTAINER subm_item_con9;
extern CONTAINER subm_item_con10;

extern TEXT_FIELD subm_item_txtidx1;
extern TEXT_FIELD subm_item_txtidx2;
extern TEXT_FIELD subm_item_txtidx3;
extern TEXT_FIELD subm_item_txtidx4;
extern TEXT_FIELD subm_item_txtidx5;
extern TEXT_FIELD subm_item_txtidx6;
extern TEXT_FIELD subm_item_txtidx7;
extern TEXT_FIELD subm_item_txtidx8;
extern TEXT_FIELD subm_item_txtidx9;
extern TEXT_FIELD subm_item_txtidx10;

extern TEXT_FIELD subm_item_txtname1;
extern TEXT_FIELD subm_item_txtname2;
extern TEXT_FIELD subm_item_txtname3;
extern TEXT_FIELD subm_item_txtname4;
extern TEXT_FIELD subm_item_txtname5;
extern TEXT_FIELD subm_item_txtname6;
extern TEXT_FIELD subm_item_txtname7;
extern TEXT_FIELD subm_item_txtname8;
extern TEXT_FIELD subm_item_txtname9;
extern TEXT_FIELD subm_item_txtname10;

extern TEXT_FIELD subm_item_txtset1;
extern TEXT_FIELD subm_item_txtset2;
extern TEXT_FIELD subm_item_txtset3;
extern TEXT_FIELD subm_item_txtset4;
extern TEXT_FIELD subm_item_txtset5;
extern TEXT_FIELD subm_item_txtset6;
extern TEXT_FIELD subm_item_txtset7;
extern TEXT_FIELD subm_item_txtset8;
extern TEXT_FIELD subm_item_txtset9;
extern TEXT_FIELD subm_item_txtset10;

//extern TEXT_FIELD info_txt;
//extern SCROLL_BAR   subm_scrollbar;


extern sub_menu_t *sub_menu_desc;

BOOL submenu_set_items(sub_menu_t* sub_menu);
void submenu_set_item_setting(UINT32 itemidx,char* str, UINT16 id);
void submenu_set_item_attr(UINT32 itemidx, UINT8 b_attr);

BOOL submenu_active(sub_menu_t* sub_menu);
void submenu_show(void);


#ifdef __cplusplus
}
#endif
#endif//_WIN_SUBMENU_H_


