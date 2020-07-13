 /*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_dvt_mainmenu_submenu.c
*
*    Description:   The sub menu of dvt mainmenu
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#include "win_dvt_mainmenu_submenu.h"
//#include "key.h"
//#include "win_filelist.h"


#define WAIT_TIME_SEC   15

static PRESULT ca_item_callback(POBJECT_HEAD p_obj, VEVENT event, UINT32 param1,
                UINT32 param2);
static UINT8 ca_check_item_active(UINT32 id);

static PRESULT mediaplayer_con_item_callback(POBJECT_HEAD p_obj, VEVENT event,
                         UINT32 param1, UINT32 param2);
static PRESULT editchannel_con_item_callback(POBJECT_HEAD p_obj, VEVENT event,
                         UINT32 param1, UINT32 param2);
static PRESULT installation_con_item_callback(POBJECT_HEAD p_obj, VEVENT event,
                          UINT32 param1, UINT32 param2);
static PRESULT system_con_item_callback(POBJECT_HEAD p_obj, VEVENT event,
                    UINT32 param1, UINT32 param2);
static PRESULT tools_con_item_callback(POBJECT_HEAD p_obj, VEVENT event,
                       UINT32 param1, UINT32 param2);

static UINT8 mediaplayer_check_item_active(UINT32 id);
static UINT8 editchannel_check_item_active(UINT32 id);
static UINT8 installation_check_item_active(UINT32 id);
static UINT8 system_check_item_active(UINT32 id);
static UINT8 tools_check_item_active(UINT32 id);
extern BOOL set_movedish_flag(BOOL flag);

static sub_menu_item_t tools_items[] = {
    // tools
    {ITEM_TYPE_NOMAL, RS_LOADER_STATUS, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_MEM_MANI, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_MODULE_CHECK, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_LOADER_NV_PARA, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_UPG_SW, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_SECURE_STATUS, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_SELECT_KEY_INFO, 0, tools_con_item_callback},
    {ITEM_TYPE_NOMAL, RS_OK_KEY_INFO, 0, tools_con_item_callback},
};

static sub_menu_t sub_menu_tools = {
    ARRAY_SIZE(tools_items),
    RS_DVT_TEST_AP,
    tools_items,
    NULL,
    tools_check_item_active,
    C_SUBMENU_PAGE, 0, 0,
};

//////////////////////////////////////////////////////////////////////////////
// sub menu structure definition
//////////////////////////////////////////////////////////////////////////////

sub_menu_t *mainmenu_sub_menus[] = {
    &sub_menu_tools,
};

static void enter_sub_menu(POBJECT_HEAD *menus, UINT32 idx)
{
    POBJECT_HEAD sub_menu_win = NULL;
    UINT32 param = 0;

    sub_menu_win = menus[idx];
    if (sub_menu_win != NULL)
    {
        param = MENU_OPEN_TYPE_MENU + idx + C_SUBMENU_ID_BASE;
        
        if (osd_obj_open(sub_menu_win, param) != PROC_LEAVE)
        {
            menu_stack_push(sub_menu_win);
        }
    }
}

static PRESULT tools_con_item_callback(POBJECT_HEAD p_obj, VEVENT event,
                       UINT32 param1, UINT32 param2)
{
    //UINT8 back_saved = 0;
    PRESULT ret = PROC_PASS;
    UINT8 unact = 0;
    UINT8 id = osd_get_obj_id(p_obj) + sub_menu_desc->list_top;

    switch (event)
    {
    case EVN_UNKNOWN_ACTION:
        unact = (VACTION) (param1 >> 16);
        if (VACT_ENTER == unact)
        {
            libc_printf("enter tool sub menu\n");
            enter_sub_menu(tools_sub_menus, id - 1);
            ret = PROC_LOOP;
        }
        break;
    default:
        break;
    }

    return ret;
}

static UINT8 tools_check_item_active(UINT32 id)
{
    UINT8 action = 0;

    action = C_ATTR_ACTIVE;

    switch (id)
    {
    case TEST_APP_NOTE1_ID:
    case TEST_APP_NOTE2_ID: 
        action = C_ATTR_INACTIVE;
        break;
    default:
        break;
    }

    return action;
}

void win_submenu_set_focus(UINT8 mm_focus, UINT8 sub_foucs)
{
    mainmenu_sub_menus[mm_focus]->list_sel = sub_foucs;

    if (sub_foucs > C_SUBMENU_PAGE)
    {
        mainmenu_sub_menus[mm_focus]->list_top = sub_foucs - C_SUBMENU_PAGE - 1;
    }
}

