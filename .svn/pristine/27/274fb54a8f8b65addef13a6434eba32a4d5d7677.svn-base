 /*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_dvt_mainmenu.c
*
*    Description:   The main menu of dvt
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#include <sys_config.h>
#include <types.h>
#include <basic_types.h>
#include <mediatypes.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <osal/osal.h>

#include <api/libpub/lib_hde.h>


#include <api/libosd/osd_lib.h>


#include "osdobjs_def.h"
#include "images.id"
#include "string.id"
#include "osd_config.h"

#include "win_com.h"

#include "win_dvt_mainmenu_submenu.h"
#include "win_dvt_submenu.h"
//#include "copper_common/system_data.h"

#include "win_dvt_mainmenu.h"


#define BMP_SH_ICON 0
#define BMP_HL_ICON 1
#define BMP_SL_ICON  2

#define MENU_ITME_NUM   (sizeof(mm_menu_items)/sizeof(mm_menu_items[0]))

/*******************************************************************************
 *   Objects definition
 *******************************************************************************/
static VACTION mm_con_keymap(POBJECT_HEAD p_obj, UINT32 key);
static PRESULT mm_con_callback(POBJECT_HEAD p_obj, VEVENT event, \
            UINT32 param1, UINT32 param2);

#define WIN_SH_IDX      WSTL_WIN_BODYLEFT_01_HD
#define WIN_HL_IDX      WIN_SH_IDX
#define WIN_SL_IDX      WIN_SH_IDX
#define WIN_GRY_IDX     WIN_SH_IDX

#define MENU_BG_IDX     WSTL_WIN_MAINMENU_01_HD

#define CON_SH_IDX   WSTL_WIN_MAINMENU_01_BG_HD
#define CON_HL_IDX   CON_SH_IDX
#define CON_SL_IDX   CON_SH_IDX
#define CON_GRY_IDX  CON_SH_IDX

#define BMP_SH_IDX   WSTL_MIXBACK_BLACK_IDX_HD
#define BMP_HL_IDX   BMP_SH_IDX
#define BMP_SL_IDX   BMP_SH_IDX
#define BMP_GRY_IDX  BMP_SH_IDX

#define TXT_SH_IDX   0
#define TXT_HL_IDX   0
#define TXT_SL_IDX   0
#define TXT_GRY_IDX  0


#define W_L         74//210 - 136
#define W_T         98//138 - 40

#define W_W         866

#define W_H         488

#define MENUBG_L            (W_L+30)
//#define   MENUBG_T        (W_T + 0)//(W_T + 12)
#define MENUBG_W            120


#define CON_W       100+16

#define CON_H           72//80
#define CON_GAP         20
#define MENUBG_T        (W_T + 12)
#define MENUBG_H        450

#define CON_L       (MENUBG_L+10)//(W_L + 30)//230
#define CON_T       (MENUBG_T+0)//(MENUBG_T+10)//(W_T + 12)//150

#define BMP_L_OF    0
#define BMP_T_OF    0
#define BMP_W       CON_W

#define BMP_H       CON_H//100//72//68//72

#define TXT_L_OF        (BMP_W + 20)
#define TXT_T_OF        40
#define TXT_W           210
#define TXT_H           40

#define LDEF_MENUBG(root,var_txt,nxt_obj,l,t,w,h,res_id,str)        \
    DEF_TEXTFIELD(var_txt,&root,nxt_obj,C_ATTR_ACTIVE,0,        \
              0,0,0,0,0, l,t,w,h, MENU_BG_IDX,MENU_BG_IDX,MENU_BG_IDX,MENU_BG_IDX, \
              NULL,NULL,                    \
              C_ALIGN_CENTER | C_ALIGN_VCENTER, 0,0,res_id,str)
             
LDEF_MENUBG(g_win_mainmenu,mainmenu_bg,NULL/*&mm_item_con1*/,MENUBG_L,MENUBG_T,MENUBG_W,MENUBG_H,0,NULL)


DEF_CONTAINER(g_win_mainmenu,NULL,NULL,C_ATTR_ACTIVE,0, \
          1,0,0,0,0, W_L,W_T,W_W,W_H, WIN_SH_IDX,WIN_HL_IDX,WIN_SL_IDX,WIN_GRY_IDX,   \
          mm_con_keymap,mm_con_callback,  (POBJECT_HEAD)&mainmenu_bg, 1,0)

/*******************************************************************************
 *   Local functions & variables define
 *******************************************************************************/

#define INSTALL_ID      1
#define EDITCHAN_ID     2

static UINT16 mm_item_str_ids[] =
{
    RS_DVT_TEST_AP,
};

//extern sub_menu_t *mainmenu_sub_menus[];
//************************window: key mapping & event definition**************
static VACTION mm_con_keymap(POBJECT_HEAD p_obj, UINT32 key)
{
    VACTION act = 0;

    libc_printf("mm_con_keymap key %d\n", key);
    switch(key)
    {
    case V_KEY_UP:
        act = VACT_CURSOR_UP;
        break;
    case V_KEY_DOWN:
        act = VACT_CURSOR_DOWN;
        break;
    case V_KEY_EXIT:
    case V_KEY_MENU:
        //act = VACT_CLOSE;
        break;
    case V_KEY_ENTER:
        act = VACT_ENTER;
        break;    
    default:
        act = VACT_PASS;
        break;
    }

    return act;


}


static void mm_osd_clear(void)
{
    OBJECT_HEAD mm_max_win;

    MEMSET(&mm_max_win, 0, sizeof(mm_max_win));
    osd_set_rect(&mm_max_win.frame, \
            menu_title_txt.head.frame.u_left, \
            menu_title_txt.head.frame.u_top, \
            menu_title_txt.head.frame.u_width, \
            menu_title_txt.head.frame.u_height + g_win_mainmenu.head.frame.u_height);
    osddrv_show_on_off((HANDLE)g_osd_dev, OSDDRV_OFF);
    osd_clear_object((POBJECT_HEAD)&mm_max_win, 0);
    osddrv_show_on_off((HANDLE)g_osd_dev, OSDDRV_ON);

}


BOOL mainmenu_is_opening = FALSE;
BOOL mainmenu_opened = FALSE;
int get_mainmenu_open_stat(void)
{
    return mainmenu_opened;
}

static PRESULT mm_con_callback(POBJECT_HEAD p_obj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    UINT8   focus_id = osd_get_focus_id( p_obj);
    UINT32 i = 0;
    POBJECT_HEAD item = NULL;
    BITMAP *bmp = NULL;
    UINT8 back_saved = 0;
    UINT8 av_flag = 0;
    POBJECT_HEAD submenu = NULL;
    VACTION unact = VACT_PASS;

	if(NULL == item)
	{
		;
	}

    
    item = osd_get_focus_object(p_obj);
    libc_printf("focus_id %d, event %d\n", focus_id, event);
    
    switch(event)
    {
    case EVN_PRE_OPEN:
        mainmenu_is_opening = TRUE ;

        LoaderCoreAPI_InitApplicationModule();
        
        item = osd_get_focus_object(p_obj);
        //bmp = mm_item_bmps[focus_id - 1];
        //osd_set_bitmap_content(bmp, mm_item_bmp_ids[focus_id - 1][BMP_HL_ICON]);
        //mm_enter_stop_mode(TRUE);


        wincom_open_title(p_obj,mm_item_str_ids[focus_id - C_SUBMENU_ID_BASE],0);
        //sys_data_set_cur_satidx((UINT16) (~0));//restore sat_idx
        break;
    case EVN_POST_OPEN:

        mainmenu_is_opening = FALSE;
        mainmenu_opened = TRUE;

        if(param2 != 0xFFFFFFFF)    /* 0xFFFFFFFF means open from the stack  */
        {
            submenu_set_items(mainmenu_sub_menus[focus_id - C_SUBMENU_ID_BASE]);
            submenu_show();
        }
          
        break;

    case EVN_PRE_CLOSE:
        
        
        {
            /* Make OSD not flickering */
            *((UINT32*)param2) &= ~C_CLOSE_CLRBACK_FLG;
        }
        break;

    case EVN_POST_CLOSE:
        mm_osd_clear();
        //mm_leave_stop_mode();

        mainmenu_opened = FALSE;
        break;
    case EVN_MSG_GOT:
        break;
    case EVN_KEY_GOT:
        unact = (VACTION)(param1>>16);

        if(unact == VACT_ENTER) 
        {
            submenu = (POBJECT_HEAD)&g_win_submenu;
            if(submenu_active(mainmenu_sub_menus[focus_id - C_SUBMENU_ID_BASE]) )
            {
                //osd_set_bitmap_content(bmp, mm_item_bmp_ids[index][BMP_SL_ICON]);
                //osd_draw_object((POBJECT_HEAD)bmp, C_UPDATE_ALL);
                //osd_draw_object((POBJECT_HEAD)&g_win_mainmenu, C_UPDATE_ALL);
    
                /* Make OSD not flickering */
                osd_track_object( submenu, C_DRAW_SIGN_EVN_FLG | C_UPDATE_FOCUS);
                menu_stack_push(submenu);
            }
        }
        break;
    default:
        break;
    }

    return ret;
}


// mm_foucs: begin from 0
// sub_mm_foucs: begin from 0
static BOOL win_mainmenu_set_sub_foucs(UINT8 mm_focus, UINT8 sub_mm_focus)
{
    UINT8 i = 0;

    osd_set_container_focus(&g_win_mainmenu, mm_focus+1);
    win_submenu_set_focus(mm_focus, sub_mm_focus);
    /* Set each item to noraml position and normal bmp icon */
    //for(i=0;i<MENU_ITME_NUM;i++)
    {
        //if(i == mm_focus)
        //    osd_set_bitmap_content(mm_item_bmps[i], mm_item_bmp_ids[i][BMP_SL_ICON]);
        //else
        //    osd_set_bitmap_content(mm_item_bmps[i], mm_item_bmp_ids[i][BMP_SH_ICON]);
    }

    submenu_set_items(mainmenu_sub_menus[mm_focus]);

    return TRUE;
}



