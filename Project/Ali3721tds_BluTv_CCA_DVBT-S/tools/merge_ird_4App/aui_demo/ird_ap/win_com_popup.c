/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_com_popup.c
*
*    Description: The common function of popup
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
#include <osal/osal.h>
#include <api/libosd/osd_lib.h>
#include <api/libtsi/db_3l.h>
#include <api/libdiseqc/lib_diseqc.h>
#include <math.h>

#include "osdobjs_def.h"
#include "osd_config.h"
#include "string.id"
#include "images.id"
//#include "vkey.h"
//#include "key.h"
//#include "control.h"
#include "win_com.h"
#include "win_com_popup.h"
//#include "win_com_popup_smsg.h"

#define POP_PRINTF PRINTF
#define POPUP_MAX_TITLE_LEN 30

#include "win_com_popup_inner.h"

/*******************************************************************************
*   WINDOW's objects declaration
*******************************************************************************/
CONTAINER    g_win_popup;
                //modify for adding welcome page when only open dvbt 2011 10 17

static UINT16 msg_title[POPUP_MAX_MSG_LEN] ={0};
//modify for adding welcome page when only open dvbt 2011 10 17
static TEXT_CONTENT popup_mtxt_content_timer = {STRING_ID, {0}};
static UINT16 msg_timer_str[POPUP_MAX_TIMER_STR_LEN] = {0};
static ID popup_timer_id = OSAL_INVALID_ID;
static UINT16 cnt_poptime = 0;


static VACTION popup_btn_text_keymap(POBJECT_HEAD p_obj, UINT32 vkey);
static PRESULT popup_btn_text_callback(POBJECT_HEAD p_obj, VEVENT event, UINT32 param1, UINT32 param2);

static VACTION popup_con_keymap(POBJECT_HEAD p_obj, UINT32 vkey);
static PRESULT popup_con_callback(POBJECT_HEAD p_obj, VEVENT event, UINT32 param1, UINT32 param2);

/*******************************************************************************
*   WINDOW's objects defintion MACRO
*******************************************************************************/

#define LDEF_TXT_TITLE(root,var_txt,nxt_obj,l,t,w,h,res_id,str)        \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    0,0,0,0,0, l,t,w,h, POPUP_TITLE_SH_IDX, POPUP_TITLE_SH_IDX, 0,0,   \
    NULL, NULL,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER, 0,0,res_id,str)

#define LDEF_MULTITEXT(root,var_msg,nxt_obj,l,t,w,h)  \
    DEF_MULTITEXT(var_msg,root,nxt_obj,C_ATTR_ACTIVE,0,   \
        0,0,0,0,0, l,t,w,h,POPUPSTR_IDX,POPUPSTR_IDX,POPUPSTR_IDX,POPUPSTR_IDX,\
        NULL,NULL,  \
        C_ALIGN_CENTER | C_ALIGN_VCENTER,1, 0,0,w,h, NULL,&popup_mtxt_content)

//modify for adding welcome page when only open dvbt 2011 10 17
#define LDEF_MULTITEXT_TIMER(root,var_msg,nxt_obj,l,t,w,h)  \
    DEF_MULTITEXT(var_msg,root,nxt_obj,C_ATTR_ACTIVE,0,   \
    0,0,0,0,0, l,t,w,h,POPUPSTR_IDX,POPUPSTR_IDX,POPUPSTR_IDX,POPUPSTR_IDX,  \
    NULL,NULL,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER,1, 0,0,w,h, NULL,&popup_mtxt_content_timer)
//modify end

#define LDEF_TXT_BTM(root,var_txt,nxt_obj,ID,idl,idr,idu,idd,l,t,w,h,res_id,str)       \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    ID,idl,idr,idu,idd, l,t,w,h, POPUPSH_IDX, POPUPHL_IDX, 0,0,   \
    popup_btn_text_keymap, popup_btn_text_callback,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER, 0,0,res_id,str)

#define LDEF_CONTAINER(var_con,nxt_obj,l,t,w,h,focus_id)   \
    DEF_CONTAINER(var_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    0,0,0,0,0, l,t,w,h, POPUPWIN_IDX,POPUPWIN_IDX,0,0,   \
    popup_con_keymap,popup_con_callback,  \
    nxt_obj, focus_id,0)

/*******************************************************************************
*   WINDOW's objects defintion
*******************************************************************************/
LDEF_TXT_TITLE(&g_win_popup,win_popup_title_txt,&win_popup_msg_mbx, W_L + 10, W_T, W_W + 10, 40,0,msg_title)
//modify for adding welcome page when only open dvbt 2011 10 17
LDEF_MULTITEXT(&g_win_popup, win_popup_msg_mbx, &win_popup_msg_mbx_timer, MSG_L,MSG_T,MSG_W,MSG_H)
LDEF_MULTITEXT_TIMER(&g_win_popup, win_popup_msg_mbx_timer, &win_popup_yes, MSG_L,MSG_T+MSG_H,MSG_W,MSG_H)
//modify for adding welcome page when only open dvbt 2011 10 17
LDEF_TXT_BTM(&g_win_popup, win_popup_yes, &win_popup_no,    1, 3, 2, 1, 1, BTM_L,BTM_T, BTM_W, BTM_H,  \
    RS_COMMON_YES, NULL)
LDEF_TXT_BTM(&g_win_popup, win_popup_no, &win_popup_cancel, 2, 1, 3, 2, 2, BTM_L + (BTM_W + BTM_GAP)*1,BTM_T, \
    BTM_W, BTM_H,  RS_COMMON_NO, NULL)
LDEF_TXT_BTM(&g_win_popup, win_popup_cancel, NULL,          3, 2, 1, 3, 3, BTM_L + (BTM_W + BTM_GAP)*2,BTM_T, \
    BTM_W, BTM_H,  RS_COMMON_NO, NULL)

LDEF_CONTAINER(g_win_popup, &win_popup_title_txt, W_L, W_T, W_W, W_H, 1)
/*******************************************************************************
*   Local Variable & Function declare
*******************************************************************************/
static struct rect timer_rect;
                //modify for adding welcome page when only open dvbt 2011 10 17


static INT8 set_change_focus = -1;

static UINT16 msg_btn_str[3][10] = {{0,},};

//modify end
static OBJECT_HEAD *win_popup_btm_objs[] =
{
    (OBJECT_HEAD*)&win_popup_yes,
    (OBJECT_HEAD*)&win_popup_no,
    (OBJECT_HEAD*)&win_popup_cancel
};

static UINT16 btn_str_ids[] =
{
    RS_COMMON_YES,
    RS_COMMON_NO,
    RS_COMMON_NO,
};

/*******************************************************************************
*   Window's keymap, proc and  callback
*******************************************************************************/
VACTION popup_con_keymap(POBJECT_HEAD p_obj, UINT32 vkey)
{

    UINT32  hwkey __MAYBE_UNUSED__ = 0;

    VACTION act = VACT_PASS;

    if(win_popup_type!= WIN_POPUP_TYPE_SMSG)
    {
        switch(vkey)
        {
        case V_KEY_MENU:
        case V_KEY_EXIT:
            win_pp_choice = WIN_POP_CHOICE_NULL;
            act = VACT_CLOSE;
            break;
        case V_KEY_LEFT:
     
            act = VACT_CURSOR_LEFT;

            break;
        case V_KEY_RIGHT:
            act = VACT_CURSOR_RIGHT;
            break;
        default:
            break;
        }
    }
    else
    {
        if((vkey == V_KEY_EXIT)||(vkey == V_KEY_MENU))
        {
            act = VACT_CLOSE;
        } 
    }
    return act;
}

PRESULT popup_con_callback(POBJECT_HEAD p_obj, VEVENT event, UINT32 param1, UINT32 param2)
{
    switch(event)
    {
    case EVN_PRE_DRAW:
        if(set_change_focus != -1)
        {
            osd_set_container_focus((PCONTAINER)p_obj, set_change_focus);
        }
        break;
    case EVN_PRE_OPEN:
        break;
    case EVN_PRE_CLOSE:
        /* Make OSD not flickering */
        if(menu_stack_get_top())
        {
            {
                *((UINT32*)param2) &= ~C_CLOSE_CLRBACK_FLG;
            }
        }
        break;

    default :
        break;
    }

    return PROC_PASS;
}
/*******************************************************************************
*   BUTTON --- proc
********************************************************************************/

VACTION popup_btn_text_keymap(POBJECT_HEAD p_obj, UINT32 vkey)
{
    VACTION act = VACT_PASS;

    if(V_KEY_ENTER == vkey)
    {
        act = VACT_ENTER;
    }

    return act;
}

PRESULT popup_btn_text_callback(POBJECT_HEAD p_obj, VEVENT event, UINT32 param1, UINT32 param2)
{
    VACTION act = 0;
    UINT16  vkey = 0;
    UINT8   id = 0;

	if(0 == vkey)
	{
		;
	}
	if(EVN_UNKNOWN_ACTION == event)
    {
        id      = p_obj->b_id;
        act     = (UINT8)(param1>>16);
        vkey    = (UINT16)param1;

        if(VACT_ENTER == act)
        {
            switch (id)
            {
                case POPUP_YES_ID:
                    win_pp_choice = WIN_POP_CHOICE_YES;
                    break;
                case POPUP_NO_ID:
                    win_pp_choice = WIN_POP_CHOICE_NO;
                    break;
                case POPUP_CANCEL_ID:
                    win_pp_choice = WIN_POP_CHOICE_CANCEL;
                    break;
                default:
                    win_pp_choice = WIN_POP_CHOICE_NULL;
                    break;
            }
            return PROC_LEAVE;
        }
    }
    return PROC_PASS;
}
/*******************************************************************************
*
*   Window  open,proc
*
*******************************************************************************/
static win_popup_type_t cur_popup_type  = WIN_POPUP_TYPE_SMSG;

void win_msg_popup_open(void)
{
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_msg_popup_smsg_open();
        return;
    }

    if(NULL == menu_stack_get_top())
    {
        if(win_pp_opened)
        {
            win_msg_popup_close();
        }
        win_popup_init();
    }

}

void win_compopup_close(void)
{
    OBJECT_HEAD *obj = NULL;

    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_close();
        cur_popup_type = !WIN_POPUP_TYPE_SMSG;
        return;
    }
    obj= (OBJECT_HEAD*)&g_win_popup;
    osd_obj_close(obj,C_CLOSE_CLRBACK_FLG);
    win_pp_opened = FALSE;
}

void win_compopup_refresh(void)
{
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_refresh();
        return;
    }
    if(win_pp_opened)
    {
        osd_draw_object((OBJECT_HEAD*)&g_win_popup, C_UPDATE_ALL);
    }
}

void win_msg_popup_close(void)
{
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_msg_popup_smsg_close();
        cur_popup_type = !WIN_POPUP_TYPE_SMSG;
        return;
    }

    if(win_pp_opened)
    {
        win_compopup_close();
    }
}

BOOL win_msg_popup_opend(void)
{
    return win_pp_opened;
}

/*******************************************************************************
*
*   exported APIs
*
*******************************************************************************/
static UINT8 win_com_popup_frame_set = 0;
void win_compopup_init(win_popup_type_t type)
{
    OBJECT_HEAD *obj = NULL;
    UINT8 i = 0;
    UINT8 btn_num = 0;
    TEXT_FIELD *txt = NULL;
    CONTAINER *win = NULL;
    POBJECT_HEAD pobj_next = NULL;
    UINT8 second_btn = 2;
    UINT8 third_btn = 3;

    cur_popup_type = type;
    if(cur_popup_type==WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_init(type);
        return;
    }
    
    win = &g_win_popup;
    pp_msg_str[0] = 0x0000;


    win_popup_type = type;
    win_popup_type = (type<=WIN_POPUP_TYPE_OKNOCANCLE)?type:WIN_POPUP_TYPE_SMSG;
    win_pp_choice = WIN_POP_CHOICE_NULL;
                //modify for adding welcome page when only open dvbt 2011 10 17
    cnt_poptime = 0;
                //modify for adding welcome page when only open dvbt 2011 10 17
    popup_mtxt_content_timer.text.p_string   = NULL;
    win_pp_choice = WIN_POP_CHOICE_NULL;
    btn_num = win_popup_btm_num[win_popup_type];

    osd_set_container_focus(win, 1);
    win->p_next_in_cntn = (OBJECT_HEAD*)&win_popup_msg_mbx;

    /* Link Window's objects */
    obj = (OBJECT_HEAD*)&win_popup_msg_mbx;
    pobj_next = (POBJECT_HEAD)&win_popup_msg_mbx_timer;
    osd_set_objp_next(obj, pobj_next);

    obj = (OBJECT_HEAD*)&win_popup_msg_mbx_timer;
    pobj_next = (btn_num<=0) ? NULL : (POBJECT_HEAD)win_popup_btm_objs[0];
    osd_set_objp_next(obj, pobj_next);

    obj = win_popup_btm_objs[0];
    pobj_next = (btn_num<=1) ? NULL : (POBJECT_HEAD)win_popup_btm_objs[1];
    osd_set_objp_next(obj, pobj_next);

    txt = (TEXT_FIELD*)win_popup_btm_objs[0];
    obj = win_popup_btm_objs[1];
    pobj_next = (btn_num<=2) ? NULL : (POBJECT_HEAD)win_popup_btm_objs[2];
    osd_set_objp_next(obj, pobj_next);

    if(1 == btn_num)
    {
        osd_set_id(win_popup_btm_objs[0], 1, 1, 1, 1, 1);
    }
    else if(second_btn == btn_num)
    {
        osd_set_id(win_popup_btm_objs[0], 1, 2, 2, 1, 1);
        osd_set_id(win_popup_btm_objs[1], 2, 1, 1, 2, 2);
    }
    else if(third_btn == btn_num)
    {
        osd_set_id(win_popup_btm_objs[0], 1, 3, 2, 1, 1);
        osd_set_id(win_popup_btm_objs[1], 2, 1, 3, 2, 2);
        osd_set_id(win_popup_btm_objs[2], 3, 2, 1, 3, 3);
    }

    for(i=0;i<3;i++)
    {
        txt = (TEXT_FIELD*)win_popup_btm_objs[i];
        txt->p_string = NULL;
        osd_set_text_field_content(txt, STRING_ID, (UINT32)btn_str_ids[i]);
    }
    win_com_popup_frame_set = 0;
    win_compopup_set_frame(W_MSG_L,W_MSG_T,W_MSG_W,W_MSG_H);
    win_com_popup_frame_set = 1;
    set_change_focus = -1;
}

void win_compopup_set_title(char *str,char *unistr,UINT16 str_id)
{
    TEXT_FIELD *txt = NULL;
    CONTAINER *win = &g_win_popup;

    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_set_title(str,unistr,str_id);
        return;
    }
    txt = &win_popup_title_txt;
    osd_set_text_field_str_point(txt, msg_title);
    if(str!=NULL)
    {
        osd_set_text_field_content(txt, STRING_ANSI, (UINT32)str);
    }
    else if(unistr!=NULL)
    {
        osd_set_text_field_content(txt, STRING_UNICODE, (UINT32)unistr);
    }
    else
    {
        if(str_id != 0)
        {
            osd_set_text_field_str_point(txt, NULL);
            osd_set_text_field_content(txt, STRING_ANSI, (UINT32)str_id);
        }
        else
        {
            win->p_next_in_cntn = (OBJECT_HEAD*)&win_popup_msg_mbx;
            return;
        }
    }

    osd_set_container_next_obj(win,txt);
}

void win_compopup_set_msg(char *str,char *unistr,UINT16 str_id)
{
    UINT8 btn_num = 0;
    UINT8 lines = 0;
    UINT8 *pstr = NULL;
    POBJECT_HEAD txt = (POBJECT_HEAD)&win_popup_msg_mbx;
    UINT16 totalw = 0;
    UINT16 mw = 0;
    UINT16 mh = 0;
    UINT16 l = 0;
    UINT16 t = 0;
    UINT16 w = 0;
    UINT16 h = 0;
    UINT8   title_flag = 0;
    CONTAINER *win = &g_win_popup;

    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_set_msg(str,unistr,str_id);
        return;
    }
    title_flag = (win->p_next_in_cntn == txt)? 0 : 1;

    popup_mtxt_content.b_text_type = STRING_UNICODE;
    popup_mtxt_content.text.p_string   = pp_msg_str;

    if(str!=NULL)
    {
        com_asc_str2uni((UINT8 *)str, pp_msg_str);
    }
    else if(unistr!=NULL)
    {
        com_uni_str_copy_char( (UINT8*)pp_msg_str,(UINT8*)unistr);
    }
    else
    {
        popup_mtxt_content.b_text_type        = STRING_ID;
        popup_mtxt_content.text.w_string_id   = str_id;
    }

    btn_num = win_popup_btm_num[win_popup_type];
    if(str != NULL || unistr!= NULL)
    {
        pstr = (UINT8*)pp_msg_str;
    }
    else
    {
        pstr = osd_get_unicode_string(str_id);
    }
    totalw = osd_multi_font_lib_str_max_hw(pstr,txt->b_font,&mw,&mh,0);
    totalw += MSG_LOFFSET*2;

    if(btn_num <= 1)
    {
        w = MIN_WIDHT_1ORNOBTN;
    }
    else
    {
        w = MIN_WIDTH_2BTN;
    }

    while (1)
    {
        if ((totalw + w - 1) % w != 0)
        {
            lines = (totalw + w - 1) / w + 1;
        }
        else
        {
            lines = (totalw + w - 2) / w;
        }
        if (lines <= 1)
        {
            lines = 1;
            break;
        }
        else
        {
            if (MAX_LEN_ONE_LINE != w)
            {
                w = MAX_LEN_ONE_LINE;
                continue;
            }
            break;
        }
    }

    if(mh < DEFAULT_FONT_H)
    {
        mh = DEFAULT_FONT_H;
    }
    h =  mh * lines + (lines  - 1)*4 ;
    if(0 == btn_num)
    {
        h += MSG_VOFFSET_NOBTN*2;
    }
    else
    {
        h += (MSG_VOFFSET_WITHBTN + MSG_BUTTON_TOPOFFSET + MSG_BUTTON_BOTOFFSET + BTM_H);
    }

    if(title_flag)
    {
        h += TITLE_H + 10;
    }
        l = 290;
        t = 250;

    win_compopup_set_frame(l,t,w,h);
}

void win_compopup_set_msg_ext(char *str,char *unistr,UINT16 str_id)
{
    UINT8 *pstr = NULL;
    UINT16 *retval = NULL;

	if(NULL == retval)
	{
		;
	}
	if(NULL == pstr)
	{
		;
	}
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_set_msg_ext(str,unistr,NULL,NULL,str_id);
        return;
    }
    popup_mtxt_content.b_text_type = STRING_UNICODE;
    popup_mtxt_content.text.p_string   = pp_msg_str;

    if(str!=NULL)
    {
        retval = com_str2uni_str_ext(pp_msg_str, str, POPUP_MAX_MSG_LEN-1);
    }
    else if(unistr!=NULL)
    {
        com_uni_str_copy_char_n((UINT8*)pp_msg_str, (UINT8*)unistr, POPUP_MAX_MSG_LEN-1);
    }
    else
    {
        popup_mtxt_content.b_text_type        = STRING_ID;
        popup_mtxt_content.text.w_string_id   = str_id;
    }

    if(str != NULL || unistr!= NULL)
    {
        pstr = (UINT8*)pp_msg_str;
    }
    else
    {
        pstr = osd_get_unicode_string(str_id);
    }
}

void win_compopup_set_msg_utf(char *str,char *unistr,char *utf8, char *utf16,UINT16 str_id)
{
    UINT8 *pstr = NULL;
    UINT16 *retval = NULL;

	if(NULL == pstr)
	{
		;
	}
	if(NULL == retval)
	{
		;
	}
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_set_msg_ext(str,unistr,utf8,utf16,str_id);
        return;
    }
    popup_mtxt_content.b_text_type = STRING_UNICODE;
    popup_mtxt_content.text.p_string   = pp_msg_str;

    if(str!=NULL)
    {
        retval = com_str2uni_str_ext(pp_msg_str, str, POPUP_MAX_MSG_LEN-1);
    }
    else if(unistr!=NULL)
    {
        com_uni_str_copy_char_n((UINT8*)pp_msg_str, (UINT8*)unistr, POPUP_MAX_MSG_LEN-1);
    }
    else if(utf8!=NULL)
    {
    com_utf8str2uni((UINT8*)utf8, pp_msg_str);
    }
    else
    {
        popup_mtxt_content.b_text_type        = STRING_ID;
        popup_mtxt_content.text.w_string_id   = str_id;
    }

    if(str != NULL || unistr!= NULL)
    {
        pstr = (UINT8*)pp_msg_str;
    }
    else
    {
        pstr = osd_get_unicode_string(str_id);
    }
}

void win_compopup_set_btnstr(UINT32 btn_idx, UINT16 str_id)
{
    TEXT_FIELD *txt = NULL;
    UINT32 max_btn_idx = 3;

    if(btn_idx < max_btn_idx)
    {
        txt = (TEXT_FIELD*)win_popup_btm_objs[btn_idx];
        osd_set_text_field_content(txt, STRING_ID, (UINT32)str_id);
    }
}

void win_compopup_set_btnstr_ext(UINT32 btn_idx, char *str)
{
    TEXT_FIELD *txt = NULL;
    char temp_str[10] = {0};
    UINT32 max_btn_idx = 3;

    if(btn_idx < max_btn_idx)
    {
        txt = (TEXT_FIELD*)win_popup_btm_objs[btn_idx];
        snprintf(temp_str,10, "%s", str);
        txt->p_string = msg_btn_str[btn_idx];
        osd_set_text_field_content(txt, STRING_ANSI, (UINT32)temp_str);
    }
}

void win_compopup_set_frame(UINT16 x,UINT16 y,UINT16 w,UINT16 h)
{
    OBJECT_HEAD *obj = NULL;
    UINT8 i = 0;
    UINT8 btn_num = 0;
    UINT16 btn_left = 0;
    UINT16 btn_top = 0;
    UINT16 btm_width = 0;
    UINT16 topoffset = 0;
    UINT16 botoffset = 0;
    const UINT8 second_btn = 2;

    OBJECT_HEAD *objmbx = NULL;
    OBJECT_HEAD *objmbx_timer = NULL;
                //modify for adding welcome page when only open dvbt 2011 10 17
    MULTI_TEXT *mbx = NULL;
    MULTI_TEXT *mbx_timer = NULL;
                //modify for adding welcome page when only open dvbt 2011 10 17
    UINT8   title_flag = 0;
    CONTAINER *win = &g_win_popup;
    TEXT_FIELD *txt_title = &win_popup_title_txt;

    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_set_frame(x,y,w,h);
        return;
    }

    title_flag = (osd_get_container_next_obj(win) == (POBJECT_HEAD)txt_title)?1:0;
    if(title_flag)
    {
        osd_set_rect(&txt_title->head.frame, x + 10, y + 6, w - 20, TITLE_H);
    }

    obj = (OBJECT_HEAD*)&g_win_popup;
    osd_set_rect(&obj->frame, x,y,w,h);
    btn_num = win_popup_btm_num[win_popup_type];
    objmbx = (OBJECT_HEAD*)&win_popup_msg_mbx;
    objmbx_timer = (OBJECT_HEAD*)&win_popup_msg_mbx_timer;
                //modify for adding welcome page when only open dvbt 2011 10 17
    mbx = &win_popup_msg_mbx;
    mbx_timer = &win_popup_msg_mbx_timer;
                //modify for adding welcome page when only open dvbt 2011 10 17

    if(0 == btn_num)
    {

        mbx->b_align = C_ALIGN_CENTER | C_ALIGN_VCENTER;

        topoffset = MSG_VOFFSET_NOBTN;
        if(h - topoffset*2 < DEFAULT_FONT_H)
        {
            topoffset = (h - DEFAULT_FONT_H)/2;
        }

        botoffset = topoffset;
        if(title_flag)
        {
            topoffset += TITLE_H;
        }
    }
    else
    {
        mbx->b_align = C_ALIGN_CENTER | C_ALIGN_TOP;
        topoffset = MSG_VOFFSET_WITHBTN;//h/5;
        botoffset = topoffset + BTM_H;
        if(title_flag)
        {
            topoffset += TITLE_H;
        }
    }

    osd_set_obj_rect(objmbx,x + MSG_LOFFSET,y + topoffset,w - MSG_LOFFSET*2, h - botoffset - topoffset);

    //modify for adding welcome page when only open dvbt 2011 10 17
    timer_rect.u_start_x = x + MSG_LOFFSET+5;
    timer_rect.u_start_y = y + topoffset;
    timer_rect.u_width  = w - MSG_LOFFSET*2-10;
    timer_rect.u_height = h - botoffset - topoffset;
    osd_set_obj_rect(objmbx_timer,x + MSG_LOFFSET+5,y + topoffset+40,\
                    w - MSG_LOFFSET*2-10,0);
    //modify end
    mbx->rc_text.u_width  = objmbx->frame.u_width;
    mbx->rc_text.u_height = objmbx->frame.u_height;
    //modify for adding welcome page when only open dvbt 2011 10 17
    mbx_timer->rc_text.u_width  = objmbx->frame.u_width;
    mbx_timer->rc_text.u_height = 40/*objmbx->frame.uHeight*/;
    //modify end

    for(i=0;i<btn_num;i++)
    {
        obj = win_popup_btm_objs[i];
        btm_width = BTM_W;

        if(1 == btn_num)
        {
            btn_left = x + (w - btm_width)/2;
        }
        else if(second_btn == btn_num)
        {
            btn_left = x + ( w - btm_width*btn_num - BTM_GAP)/2 + (btm_width + BTM_GAP) *i ;
        }
        else
        {
            btn_left = x +  w - (btm_width + BTM_GAP) * ( btn_num - i) - 40;
        }
        btn_top = h - MSG_BUTTON_BOTOFFSET - BTM_H;
        osd_set_rect(&obj->frame, btn_left,(y + btn_top),btm_width,BTM_H);
    }

}

void win_compopup_set_pos(UINT16 x,UINT16 y)
{
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_set_pos(x,y);
        return;
    }
    osd_move_object((POBJECT_HEAD)&g_win_popup, x, y, FALSE);
}

void win_compopup_set_default_choice(win_popup_choice_t choice)
{
    win_pp_choice = choice;
    g_win_popup.focus_object_id = win_pp_choice ;
}

 win_popup_choice_t win_compopup_open(void)
{
    CONTAINER *con =&g_win_popup;
    PRESULT b_result = PROC_LOOP;
    UINT32 hkey = 0;
    UINT ct =cnt_poptime;
    BOOL old_value = FALSE;

    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_open();
        return WIN_POP_CHOICE_NULL;
    }

    win_msg_popup_close();

    win_popup_init();
    if(win_popup_type!=WIN_POPUP_TYPE_SMSG)
    {
        old_value = FALSE;
        old_value  = ap_enable_key_task_get_key(TRUE);
        while(b_result != PROC_LEAVE)
        {
       
            hkey = ap_get_key_msg();
            if((INVALID_HK == hkey) || (INVALID_MSG == hkey))
            {
                continue;
            }

           
            b_result = osd_obj_proc((POBJECT_HEAD)con, (MSG_TYPE_KEY<<16),hkey,0);
            
        }
        //api_stop_timer(&popup_timer_id);
        //modify end
        ap_enable_key_task_get_key(old_value);
    }

    return win_pp_choice;
}

win_popup_choice_t win_com_popup_open(win_popup_type_t type,char *str,UINT16 str_id)
{
    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_com_popup_smsg_open(type,str,str_id);
        return WIN_POP_CHOICE_NULL;
    }
    win_compopup_init(type);
    win_compopup_set_msg(str,NULL,str_id);
    return win_compopup_open();
}

win_popup_choice_t win_compopup_open_ext(UINT8 *back_saved)
{
    win_popup_choice_t ret = WIN_POP_CHOICE_NO;
    win_popup_type_t  type = win_popup_type;



    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_open_ext();
        return WIN_POP_CHOICE_NULL;
    }
    wincom_backup_region(&g_win_popup.head.frame);
    ret = win_compopup_open();
    if(type != WIN_POPUP_TYPE_SMSG)
    {
        *back_saved = 1;
        if(win_pp_opened)
        {
            win_msg_popup_close();
        }
        wincom_restore_region();
    }
    else
    {
        *back_saved = 0;
    }

    return ret;
}

win_popup_choice_t win_compopup_open_enh(POBJECT_HEAD root_obj, UINT32 draw_mode, UINT32 cmd)
{
    win_popup_choice_t ret = WIN_POP_CHOICE_NO;
    struct osdrect *frame_ptr = NULL;
    POBJECT_HEAD obj = NULL;
    UINT16 x = 0;
    UINT16 y = 0;
    BOOL adjust_xy = FALSE;

    if(NULL == root_obj)
    {
        ASSERT(0);
        return WIN_POP_CHOICE_NULL;
    }

    frame_ptr = &(root_obj->frame);
    obj = (POBJECT_HEAD)&g_win_popup;

    if((obj->frame.u_height > frame_ptr->u_height) || (obj->frame.u_width > frame_ptr->u_width))
    {
        return WIN_POP_CHOICE_NULL;
    }

    x = obj->frame.u_left;
    y = obj->frame.u_top;
    if(obj->frame.u_top < frame_ptr->u_top)
    {
        x = frame_ptr->u_top;
        adjust_xy = TRUE;
    }
    if(obj->frame.u_left < frame_ptr->u_left)
    {
        y = frame_ptr->u_left;
        adjust_xy = TRUE;
    }
    if(adjust_xy)
    {
        win_compopup_set_frame(x,y,obj->frame.u_width,obj->frame.u_height);
    }

    ret = win_compopup_open();

    //if(root_obj)
    //{
        if(draw_mode&0x01)
        {
            osd_track_object(root_obj,cmd);
        }
        else// if(!(draw_mode&0x01))
        {
            osd_draw_object(root_obj,cmd);
        }
    //}
    return ret;
}

void win_compopup_smsg_restoreback(void)
{

    if(cur_popup_type == WIN_POPUP_TYPE_SMSG)
    {
        //win_compopup_smsg_smsg_restoreback();
        return;
    }
    if(win_pp_opened)
    {
        win_msg_popup_close();
    }
    wincom_restore_region();
}

