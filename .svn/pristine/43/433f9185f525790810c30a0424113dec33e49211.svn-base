/*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_chip_status.c
*
*    Description: The menu for chip status
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

#include <api/libosd/osd_lib.h>
#include <api/libsi/si_tdt.h>

#include "osdobjs_def.h"

#include "string.id"
#include "images.id"
#include "osd_config.h"
#include "osd_rsc.h"

#include "win_com_menu_define.h"
#include "win_com.h"

#include "win_chip_status.h"


/*******************************************************************************
*   Objects definition
*******************************************************************************/
static VACTION cs_btn_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT cs_btn_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);

static VACTION cs_item_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT cs_item_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);

static VACTION cs_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT cs_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);
static VACTION win_cs_edit_keymap(POBJECT_HEAD pobj, UINT32 key);

#define MTXT_SH_IDX WSTL_TEXT_09_HD
#define MTXT_L  (W_L + 30)

#define MTXT_T ( CON_T + (CON_H + CON_GAP)*8)

#define MTXT_W (W_W - 60)
#define MTXT_H 108//150

#define CON_GAP     4//8//12
#define CS_CON_GAP CON_GAP
#define TXTN_W      550//420

#define CON_W       (W_W - 250)

#define BTN_L1      (CON_L + CON_W)
//#define BTN_L2      (BTN_L1 + BTN_W + 40)
#define BTN_T       (CON_T + (CON_H + CS_CON_GAP)*3)//(MTXT_T + MTXT_H + 30)
#define BTN_W       160
#define BTN_H       40

#define BTN_T2       (CON_T + (CON_H + CS_CON_GAP)*4)//(MTXT_T + MTXT_H + 30)

#define BTN_SH_IDX   WSTL_BUTTON_SHOR_HD
#define BTN_HL_IDX   WSTL_BUTTON_SHOR_HI_HD
#define BTN_SL_IDX   WSTL_BUTTON_01_FG_HD
#define BTN_GRY_IDX  WSTL_BUTTON_SHOR_GRY_HD

static char win_cs_pat[] = "s5";

#define MENU_WR_cs 2
#define MENU_ERASE_cs 3
#define MENU_MODIFY_cs 4

#define LDEF_CON(root, var_con,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,conobj,focus_id)     \
    DEF_CONTAINER(var_con,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, CON_SH_IDX,CON_HL_IDX,CON_SL_IDX,CON_GRY_IDX,   \
    cs_item_con_keymap,cs_item_con_callback,  \
    conobj, focus_id,1)

#define LDEF_TXTNAME(root,var_txt,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,res_id,str)       \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, TXTN_SH_IDX,TXTN_HL_IDX,TXTN_SL_IDX,TXTN_GRY_IDX,   \
    NULL,NULL,  \
    C_ALIGN_LEFT | C_ALIGN_VCENTER, 0,0,res_id,str)

#define LDEF_TXTSET(root,var_txt,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,res_id,str)        \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, TXTS_SH_IDX,TXTS_HL_IDX,TXTS_SL_IDX,TXTS_GRY_IDX,   \
    NULL,NULL,  \
    C_ALIGN_CENTER| C_ALIGN_VCENTER, 20,0,res_id,str)

#define LDEF_EDIT(root, var_num, nxt_obj, id, idl, idr, idu, idd, l, t, w, h,style,cursormode,pat,pre,sub,str)    \
    DEF_EDITFIELD(var_num,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, TXTS_SH_IDX,WSTL_BUTTON_04_HD,TXTS_SL_IDX,TXTS_GRY_IDX,   \
    win_cs_edit_keymap,NULL,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER, 20,0,style,pat,10,cursormode,pre,sub,str)


#define LDEF_MM_ITEM(root,var_con,nxt_obj,var_txt_name,var_txtset,var_line,id,idu,idd,l,t,w,h,name_id,setstr,pat)  \
    LDEF_CON(&root,var_con,nxt_obj,id,id,id,idu,idd,l,t,w,h,&var_txt_name,1)    \
    LDEF_TXTNAME(&var_con,var_txt_name,&var_txtset,0,0,0,0,0,l + TXTN_L_OF, t + TXTN_T_OF,TXTN_W,TXTN_H,name_id,NULL)\
    LDEF_EDIT(&var_con,var_txtset,NULL/*&varLine*/,1,1,1,1,1,l + TXTS_L_OF, t + TXTS_T_OF,TXTS_W,TXTS_H,\
                    NORMAL_EDIT_MODE , CURSOR_NO, pat,NULL,NULL, setstr)\
    LDEF_LINE(&var_con,var_line,NULL,1,1,1,1,1,l + LINE_L_OF, t + LINE_T_OF,LINE_W,LINE_H,0,0)


#define LDEF_MM_ITEM2(root,var_con,nxt_obj,var_txt_name,id,idu,idd,l,t,w,h,name_id,setstr) \
    LDEF_CON(&root,var_con,nxt_obj,id,id,id,idu,idd,l,t,w,h,&var_txt_name,1)    \
    LDEF_TXTNAME(&var_con,var_txt_name,NULL,0,0,0,0,0,l + TXTN_L_OF, t + TXTN_T_OF,TXTN_W,TXTN_H,name_id,setstr)\
    //LDEF_EDIT(&var_con,var_txtset,NULL/*&varLine*/,1,1,1,1,1,l + TXTS_L_OF, t + TXTS_T_OF,TXTS_W,TXTS_H,\
    //                NORMAL_EDIT_MODE , CURSOR_NORMAL, pat,NULL,NULL, setstr)\
    //LDEF_LINE(&var_con,var_line,NULL,1,1,1,1,1,l + LINE_L_OF, t + LINE_T_OF,LINE_W,LINE_H,0,0)

#define LDEF_TXT_BTN(root,var_txt,next_obj,l,t,w,h,ID,idu,idd,res_id)      \
    DEF_TEXTFIELD(var_txt,&root,next_obj,C_ATTR_ACTIVE,0, \
    ID,ID,ID,idu,idd, l,t,w,h, BTN_SH_IDX,BTN_HL_IDX,BTN_SL_IDX,BTN_GRY_IDX,   \
    cs_btn_keymap,cs_btn_callback,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER, 10,0,res_id,NULL)
    
#define LDEF_MTXT(root,var_mtxt,next_obj,l,t,w,h,cnt,content) \
    DEF_MULTITEXT(var_mtxt,&root,next_obj,C_ATTR_ACTIVE,0, \
        0,0,0,0,0, l,t,w,h, MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,   \
        NULL,NULL,  \
        C_ALIGN_LEFT | C_ALIGN_TOP, cnt,  4,4,w-8,h-8,NULL,content)


LDEF_MM_ITEM2(win_cs_test_con,cs_item_con1, &cs_item_con2,cs_item_txtname1,\
                1,1,1, CON_L, CON_T + (CON_H + CS_CON_GAP)*0,CON_W,CON_H, NULL,display_strs[0])

LDEF_MM_ITEM2(win_cs_test_con,cs_item_con2, &cs_item_con3,cs_item_txtname2,\
                2,2,2, CON_L, CON_T + (CON_H + CS_CON_GAP)*3,CON_W,CON_H, NULL,display_strs[1])
LDEF_MM_ITEM2(win_cs_test_con,cs_item_con3, &cs_item_con4,cs_item_txtname3,\
                3,3,3,CON_L, CON_T + (CON_H + CS_CON_GAP)*4,CON_W,CON_H, NULL,display_strs[2])

LDEF_MM_ITEM2(win_cs_test_con,cs_item_con4, &cs_btn_ok,cs_item_txtname4,\
                4,4,4,CON_L, CON_T + (CON_H + CS_CON_GAP)*5,CON_W,CON_H, NULL,display_strs[3])


LDEF_TXT_BTN(win_cs_test_con,cs_btn_ok,&cs_btn_ok2, \
        BTN_L1, BTN_T, BTN_W, BTN_H,5,6,6,RS_BLOW)

LDEF_TXT_BTN(win_cs_test_con,cs_btn_ok2,&cs_mtxt_zone_city, \
        BTN_L1, BTN_T2, BTN_W, BTN_H,6,5,5,RS_BLOW)

LDEF_MTXT(win_cs_test_con,cs_mtxt_zone_city,NULL,\
        MTXT_L, MTXT_T,MTXT_W,MTXT_H,1,cszone_mtxt_content)

DEF_CONTAINER(win_cs_test_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    1,0,0,0,0, W_L,W_T,W_W,W_H, WIN_SH_IDX,WIN_HL_IDX,WIN_SL_IDX,WIN_GRY_IDX,   \
    cs_con_keymap,cs_con_callback,  \
    (POBJECT_HEAD)&cs_item_con1, 5,0)


/*******************************************************************************
*   Local functions & variables define
*******************************************************************************/
TEXT_CONTENT cszone_mtxt_content[] =
{
    {STRING_UNICODE,{0}},
};

#define OTP_0X3_ADDR            (0x03*4)
#define OTP_0XDD_ADDR           (0xdd*4)


#define FUSE_SECURE_BOOT_ID 5
#define FUSE_CWMODE_ID      6

static INT8 Is_SecureBoot_En()
{
    UINT32 buf = 0;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;
    ret = aui_otp_read(OTP_0XDD_ADDR, (UINT8 *)&buf, 4);
    if(ret!=AUI_RTN_SUCCESS)
        return -1;
    libc_printf("0xDD: 0x%x\n", buf);
    if((buf>>1)&0x1 == 1)
        return 1;//check sig
    else
        return 0;
}

static INT8 Enable_SecureBoot()
{
    UINT32 buf = 0;
    INT8 tmp = -1;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;

    buf = 1 << 1; //bit 1  
    ret = aui_otp_write(OTP_0XDD_ADDR, (UINT8 *)&buf, 4);
    
    tmp = Is_SecureBoot_En();
    if(tmp!=1)
        return -1;
    else
        return 0;
}

static INT8 Is_CWMode_En()
{
    UINT32 buf = 0;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;
    ret = aui_otp_read(OTP_0X3_ADDR, (UINT8 *)&buf, 4);
    if(ret!=AUI_RTN_SUCCESS)
        return -1;
    libc_printf("0x3: 0x%x\n", buf);
    if((buf>>23)&0x1 == 1)
        return 1;//force KL
    else
        return 0;
}

static INT8 Enable_CWMode()
{
    UINT32 buf = 0;
    INT8 tmp = -1;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;

    buf = 1 << 23; //bit 23  
    ret = aui_otp_write(OTP_0X3_ADDR, (UINT8 *)&buf, 4);
    
    tmp = Is_CWMode_En();
    if(tmp!=1)
        return -1;
    else
        return 0;
}

static INT8 Is_Jtag_Fused()
{
    UINT32 buf = 0;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;
    UINT32 val = 0;
    ret = aui_otp_read(OTP_0XDD_ADDR, (UINT8 *)&buf, 4);
    if(ret!=AUI_RTN_SUCCESS)
        return -1;
    libc_printf("0xDD: 0x%x\n", buf);
    val = (buf>>2)&0x3;
    if(val == 0)
        return 0;//jtag can use 
    else
        return 1;//jtag can't use
}

static VACTION cs_btn_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act = VACT_PASS;

    if(V_KEY_ENTER == key)
    {
        act = VACT_ENTER;
    }
    return act;
}


static PRESULT cs_btn_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    //PRESULT ret = PROC_LEAVE;
    VACTION unact= PROC_PASS;
    UINT8 bid= 0;
    char hint[64] = {0};
    UINT8 back_saved = 0;
    win_popup_choice_t choice = WIN_POP_CHOICE_NO;
    INT8 tmp = 0;
    char str[90];

    bid = osd_get_obj_id(pobj);

    switch(event)
    {
    case EVN_UNKNOWN_ACTION:
        unact = (VACTION)(param1>>16);
        if(VACT_ENTER == unact)
        {
            //ret = PROC_LEAVE;
            
            win_compopup_init(WIN_POPUP_TYPE_OKNO);
            if(bid == FUSE_SECURE_BOOT_ID)
                snprintf(hint, 64, "Are you sure to enable Secure Boot?");
            else
                snprintf(hint, 64, "Are you sure to enable CW Mode protect?");
            win_compopup_set_msg(hint, NULL, 0);
            win_compopup_set_default_choice(WIN_POP_CHOICE_NO);
            choice = win_compopup_open_ext(&back_saved);
            if (WIN_POP_CHOICE_YES == choice)
            {
                //to do,left to customer
                libc_printf("to do, will fuse!\n");
                #if 1
                if(bid == FUSE_SECURE_BOOT_ID)
                {
                    //Enable_SecureBoot();
                    tmp = Is_SecureBoot_En();
                    MEMSET(str,0,sizeof(str));
                    snprintf(str, 90, "SecureBoot Fuse            %s", (tmp==1)?"Enabled":"Disabled");        
                    osd_set_text_field_content(&cs_item_txtname2,STRING_ANSI, (UINT32)str);//(UINT32)"SecureBoot Fuse            Disabled");
                    osd_draw_object((POBJECT_HEAD)&cs_item_con2,C_UPDATE_ALL);
                }
                else
                {
                    //Enable_CWMode();
                    tmp = Is_CWMode_En();
                    MEMSET(str,0,sizeof(str));
                    snprintf(str, 90, "CwMode Fuse                %s", (tmp==1)?"Enabled":"Disabled");        
                    osd_set_text_field_content(&cs_item_txtname3,STRING_ANSI, (UINT32)str);//"CwMode Fuse                Disabled");
                    osd_draw_object((POBJECT_HEAD)&cs_item_con3,C_UPDATE_ALL);
                }
                #endif
                return ret;
            }
        }
        break;
    default:
        break;
    }
    return ret;
}

static VACTION win_cs_edit_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION action = VACT_PASS;

    switch(key)
    {
        case V_KEY_LEFT:
            action = VACT_EDIT_LEFT;
            break;
        case V_KEY_RIGHT:
            action = VACT_EDIT_RIGHT;
            break;
        case V_KEY_0:   case V_KEY_1:   case V_KEY_2:   case V_KEY_3:
        case V_KEY_4:   case V_KEY_5:   case V_KEY_6:   case V_KEY_7:
        case V_KEY_8:   case V_KEY_9:
            action = key - V_KEY_0 + VACT_NUM_0;
            break;
        default:
            break;
    }

    return action;
}

/*******************************************************************************
*   key mapping and event callback definition
*******************************************************************************/

static VACTION cs_item_con_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act =VACT_PASS;

    switch(key)
    {
    case V_KEY_RIGHT:
        act = VACT_INCREASE;
        break;
    case V_KEY_LEFT:
        act = VACT_DECREASE;
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

static void win_cs_enter_key(POBJECT_HEAD pobj,UINT8 id)
{
    switch(id)
    {
        case MENU_WR_cs:       
            //osd_set_text_field_content(&cs_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Written Successfully");
            //osd_draw_object((POBJECT_HEAD)&cs_item_con7,C_UPDATE_ALL);
            break;
        case MENU_ERASE_cs:
            //osd_set_text_field_content(&cs_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Erased Successfully");
            //osd_draw_object((POBJECT_HEAD)&cs_item_con7,C_UPDATE_ALL);
            break;
        case MENU_MODIFY_cs:
            //osd_set_text_field_content(&cs_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Modified Successfully");
            //osd_draw_object((POBJECT_HEAD)&cs_item_con7,C_UPDATE_ALL);
            break;
        default:
            break;
    }    
}

static PRESULT cs_item_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    UINT8   unact=VACT_PASS;
    UINT8   id = osd_get_obj_id(pobj);

    switch(event)
    {
    case EVN_FOCUS_PRE_GET:
        break;

    case EVN_FOCUS_PRE_LOSE:
        break;

    case EVN_UNKNOWN_ACTION:
        unact = (VACTION)(param1>>NON_ACTION_LENGTH) ;
        switch(unact)
        {
            case VACT_ENTER:
                win_cs_enter_key(pobj,id);
                break;
            default:
                break;
        }
        ret = PROC_LOOP;
        break;
    default:
        break;
    }
    return ret;

}

static VACTION cs_con_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act=VACT_PASS;
 
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
        act = VACT_CLOSE;
       
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

static PRESULT cs_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    char str[120] = {0};
    INT8 tmp1 = 0;
    INT8 tmp2 = 0;
    INT8 tmp3 = 0;
    
    MULTI_TEXT *mtxt = &cs_mtxt_zone_city;
    TEXT_CONTENT *txtcont = cszone_mtxt_content;
    txtcont->b_text_type = STRING_UNICODE;
    txtcont->text.p_string = len_display_str;
    
    switch(event)
    {
    case EVN_PRE_OPEN:
        tmp1 = Is_SecureBoot_En();
        tmp2 = Is_CWMode_En();
        tmp3 = Is_Jtag_Fused();
        
        wincom_open_title((POBJECT_HEAD)&win_cs_test_con,RS_SECURE_STATUS, 0);

        osd_set_text_field_content(&cs_item_txtname1,STRING_ANSI, (UINT32)"Decode Type                Advanced Security");

        MEMSET(str,0,sizeof(str));
        snprintf(str, 90, "SecureBoot Fuse            %s", (tmp1==1)?"Enabled":"Disabled");        
        osd_set_text_field_content(&cs_item_txtname2,STRING_ANSI, (UINT32)str);//(UINT32)"SecureBoot Fuse            Disabled");

        MEMSET(str,0,sizeof(str));
        snprintf(str, 90, "CwMode Fuse                %s", (tmp2==1)?"Enabled":"Disabled");        
        osd_set_text_field_content(&cs_item_txtname3,STRING_ANSI, (UINT32)str);//"CwMode Fuse                Disabled");

        MEMSET(str,0,sizeof(str));
        snprintf(str, 90, "JTAG Fuse                   %s", (tmp3==1)?"Enabled":"Disabled");        
        osd_set_text_field_content(&cs_item_txtname4,STRING_ANSI, (UINT32)str);//"JTAG Fuse                   Disabled");

        MEMSET(str,0,sizeof(str));
        snprintf(str, 120, "Press Exit to return to Main Menu.\nPress OK to confirm");
        com_asc_str2uni(str, &len_display_str[0]);

       
        osd_set_container_focus((CONTAINER*)pobj,5);
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

