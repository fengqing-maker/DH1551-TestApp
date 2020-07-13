/*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_upg.c
*
*    Description: To realize the UI for upgrade sw
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
#include <bus/otp/otp.h>

#include <api/libosd/osd_lib.h>
#include <api/libchunk/chunk.h>
#include <hal/hal_gpio.h>

#include <api/libfs2/stdio.h>

#include <api/libfs2/statvfs.h>
 #include <asm/chip.h>
#include <aui_misc.h>

#include "osdobjs_def.h"

#include "string.id"
#include "images.id"
#include "osd_config.h"

#include "win_com_menu_define.h"
#include "win_com.h"
#include "win_upg.h"

/*******************************************************************************
* Objects declaration
*******************************************************************************/
static VACTION upg_btn_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT upg_btn_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);

static VACTION upg_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT upg_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);


#define WIN_SH_IDX      WSTL_WIN_BODYRIGHT_01_HD
#define MTXT_SH_IDX     WSTL_TEXT_09_HD

#define BTN_SH_IDX   WSTL_BUTTON_SHOR_HD
#define BTN_HL_IDX   WSTL_BUTTON_SHOR_HI_HD
#define BTN_SL_IDX   WSTL_BUTTON_01_FG_HD
#define BTN_GRY_IDX  WSTL_BUTTON_SHOR_GRY_HD

/* define in win_com_menu_define.h already */
#define W_L         82//248
#define W_T         98
#define W_W         858//692
#define W_H         488

#define CON_L       W_L
#define CON_T       (W_T + 4)
#define CON_W       (W_W - 46)
#define CON_H       40
#define CON_GAP     12

#define MTXT_L      (W_L + 20)
#define MTXT_T      (W_T + 30)
#define MTXT_W      (W_W - 60)
#define MTXT_H      200

#define BTN_L1      (W_L + 120 + 120)
#define BTN_L2      (BTN_L1 + BTN_W + 40)
#define BTN_T       (MTXT_T + MTXT_H + 30)
#define BTN_W       160
#define BTN_H       40


#define MTXT_CTN_CNT  1//(sizeof(upg_mtxt_content)/sizeof(TEXT_CONTENT))
#define BTN_YES_ID  1
#define BTN_NO_ID   2

#define LDEF_MTXT(root,var_mtxt,next_obj,l,t,w,h,cnt,content) \
    DEF_MULTITEXT(var_mtxt,&root,next_obj,C_ATTR_ACTIVE,0, \
        0,0,0,0,0, l,t,w,h, MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,   \
        NULL,NULL,  \
        C_ALIGN_LEFT | C_ALIGN_TOP, cnt,  4,4,w-8,h-8,NULL,content)

#define LDEF_TXT_BTN(root,var_txt,next_obj,l,t,w,h,ID,idl,idr,res_id)      \
    DEF_TEXTFIELD(var_txt,&root,next_obj,C_ATTR_ACTIVE,0, \
    ID,idl,idr,ID,ID, l,t,w,h, BTN_SH_IDX,BTN_HL_IDX,BTN_SL_IDX,BTN_GRY_IDX,   \
    upg_btn_keymap,upg_btn_callback,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER, 10,0,res_id,NULL)


#define LDEF_WIN(var_con,nxt_obj,l,t,w,h,focus_id)     \
    DEF_CONTAINER(var_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    0,0,0,0,0, l,t,w,h, WIN_SH_IDX,WIN_SH_IDX,WIN_SH_IDX,WIN_SH_IDX,   \
    upg_keymap,upg_callback,  \
    nxt_obj, focus_id,0)

LDEF_MTXT(win_upg_con,upg_mtxt,&upg_btn_ok, \
        MTXT_L, MTXT_T,MTXT_W,MTXT_H,MTXT_CTN_CNT,upg_mtxt_content)

LDEF_TXT_BTN(win_upg_con,upg_btn_ok,&upg_btn_cancel, \
        BTN_L1, BTN_T, BTN_W, BTN_H,1,2,2,RS_COMMON_YES)

LDEF_TXT_BTN(win_upg_con,upg_btn_cancel,NULL, \
        BTN_L2, BTN_T, BTN_W, BTN_H,2,1,1,RS_COMMON_NO)

LDEF_WIN(win_upg_con,&upg_mtxt,W_L, W_T,W_W,W_H,2)
/*******************************************************************************
*   Local functions & variables declare
*******************************************************************************/
TEXT_CONTENT upg_mtxt_content[] =
{
    {STRING_UNICODE,{0}},
};

/*******************************************************************************
*   Window's keymap, proc and  callback
*******************************************************************************/
static VACTION upg_btn_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act = VACT_PASS;

    if(V_KEY_ENTER == key)
    {
        act = VACT_ENTER;
    }
    return act;
}

static lc_result update_dl_flag(lc_download_type dlType)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_bool enableDl = LC_TRUE;

    if(OTA_DOWNLOAD != dlType)
    {
        libc_printf("%s() dlType is invalid!!\n", __FUNCTION__);
        lc_ret = LC_FAILURE;
        return lc_ret;
    }

    lc_ret =  LoaderCoreAPI_SetDownloadFlag(enableDl, dlType);

    if(LC_SUCCESS == lc_ret)
    {
        libc_printf("%s() LoaderCoreAPI_SetDownloadFlag success!!\n", __FUNCTION__);
    }
    else
    {
        libc_printf("%s() LoaderCoreAPI_SetDownloadFlag fail!!\n", __FUNCTION__);
    }

    return lc_ret;
}

static PRESULT upg_btn_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    //PRESULT ret = PROC_LEAVE;
    VACTION unact= PROC_PASS;
    UINT8 bid= 0;
   
    bid = osd_get_obj_id(pobj);

    switch(event)
    {
    case EVN_UNKNOWN_ACTION:
        unact = (VACTION)(param1>>16);
        if(VACT_ENTER == unact)
        {
            ret = PROC_LEAVE;
            if(BTN_NO_ID == bid)
            {
                break;
            }
            libc_printf("set ota flag\n");
            if(LC_SUCCESS == update_dl_flag(OTA_DOWNLOAD))
            {
                libc_printf("set ota upgrade success\n");
				aui_sys_reboot(0);
            }
            else
            {
                libc_printf("set ota upgrade fail\n");
            }
        }
        break;
    default:
        break;
    }
    return ret;
}

static VACTION upg_keymap(POBJECT_HEAD pobj, UINT32 vkey)
{
    VACTION act = VACT_PASS;

    switch(vkey)
    {
    case V_KEY_LEFT:
        act = VACT_CURSOR_LEFT;
        break;
    case V_KEY_RIGHT:
        act = VACT_CURSOR_RIGHT;
        break;
    case V_KEY_MENU:
    case V_KEY_EXIT:
        act= VACT_CLOSE;
    break;
    default:
        break;
    }
    return act;
}

static PRESULT upg_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    CONTAINER *cont = (CONTAINER*)pobj;
    char str[120] = {0};

    MULTI_TEXT *mtxt = &upg_mtxt;
    TEXT_CONTENT *txtcont = upg_mtxt_content;
    txtcont->b_text_type = STRING_UNICODE;
    txtcont->text.p_string = len_display_str;
    
    switch(event)
    {
        case EVN_PRE_OPEN:
            osd_set_container_focus(cont, BTN_NO_ID);
            wincom_open_title((POBJECT_HEAD)&win_upg_con,RS_UPG_SW, 0);

            MEMSET(str,0,sizeof(str));
            snprintf(str, 120, "Set Over The Air Download Flag and Start High Level Initialized Download?");
            com_asc_str2uni((UINT8 *)str, &len_display_str[0]);

            break;

        case EVN_POST_OPEN:
            break;

        case EVN_PRE_CLOSE:
        /* Make OSD not flickering */
        *((UINT32*)param2) &= ~C_CLOSE_CLRBACK_FLG;

            break;

        case EVN_POST_CLOSE:
            break;
        default:
            break;
    }
    return ret;
}



