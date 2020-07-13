/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_module_test.c
*
*    Description: The menu for module test
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

//#include "copper_common/system_data.h"
//#include "copper_common/menu_api.h"
#include "win_com_menu_define.h"
#include "win_com.h"
//#include "win_com_popup.h"

//#include "md_zone_name.h"
#include "win_module_test.h"


/*******************************************************************************
*   Objects definition
*******************************************************************************/
static VACTION md_item_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT md_item_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);

static VACTION md_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT md_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);
static VACTION win_md_edit_keymap(POBJECT_HEAD pobj, UINT32 key);

#define MTXT_SH_IDX WSTL_TEXT_09_HD
#define MTXT_L  (W_L + 30)

#define MTXT_T ( CON_T + (CON_H + CON_GAP)*8)

#define MTXT_W (W_W - 60)
#define MTXT_H 108//150

#define CON_GAP     4//8//12
#define MD_CON_GAP CON_GAP
#define TXTN_W      480//420

static char win_md_pat[] = "s5";

#define MENU_WR_MD 2
#define MENU_ERASE_MD 3
#define MENU_MODIFY_MD 4

#define LDEF_CON(root, var_con,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,conobj,focus_id)     \
    DEF_CONTAINER(var_con,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, CON_SH_IDX,CON_HL_IDX,CON_SL_IDX,CON_GRY_IDX,   \
    md_item_con_keymap,md_item_con_callback,  \
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
    win_md_edit_keymap,NULL,  \
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

#define LDEF_MTXT(root,var_mtxt,next_obj,l,t,w,h,cnt,content) \
    DEF_MULTITEXT(var_mtxt,&root,next_obj,C_ATTR_ACTIVE,0, \
        0,0,0,0,0, l,t,w,h, MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,   \
        NULL,NULL,  \
        C_ALIGN_LEFT | C_ALIGN_TOP, cnt,  4,4,w-8,h-8,NULL,content)


LDEF_MM_ITEM2(win_md_test_con,md_item_con1, &md_item_con2,md_item_txtname1,\
                1,1,1, CON_L, CON_T + (CON_H + MD_CON_GAP)*0,CON_W,CON_H, NULL,display_strs[0])

LDEF_MM_ITEM(win_md_test_con,md_item_con2, &md_item_con3,md_item_txtname2, md_item_edit2,md_item_line2,\
                2,4,3,CON_L, CON_T + (CON_H + MD_CON_GAP)*1,CON_W,CON_H, RS_WRITE_PATTERNTO_MD,display_strs[1], win_md_pat)
LDEF_MM_ITEM(win_md_test_con,md_item_con3, &md_item_con4,md_item_txtname3,md_item_edit3,md_item_line3,\
                3,2,4,CON_L, CON_T + (CON_H + MD_CON_GAP)*2,CON_W,CON_H, RS_ERASE_MODULE,display_strs[2], win_md_pat)
LDEF_MM_ITEM(win_md_test_con,md_item_con4, &md_item_con5,md_item_txtname4,md_item_edit4,md_item_line4,\
                4,3,2,CON_L, CON_T + (CON_H + MD_CON_GAP)*3,CON_W,CON_H, RS_MODIFY_MD_LAST_BIT,display_strs[3], win_md_pat)


LDEF_MM_ITEM2(win_md_test_con,md_item_con5, &md_item_con6,md_item_txtname5,\
                5,5,5, CON_L, CON_T + (CON_H + MD_CON_GAP)*4,CON_W,CON_H, NULL,display_strs[4])
LDEF_MM_ITEM2(win_md_test_con,md_item_con6, &md_item_con7,md_item_txtname6,\
                6,6,6,CON_L, CON_T + (CON_H + MD_CON_GAP)*5,CON_W,CON_H, NULL,display_strs[5])

LDEF_MM_ITEM2(win_md_test_con,md_item_con7, &md_mtxt_zone_city,md_item_txtname7,\
                7,7,7,CON_L, CON_T + (CON_H + MD_CON_GAP)*6,CON_W,CON_H, NULL,display_strs[6])

LDEF_MTXT(win_md_test_con,md_mtxt_zone_city,NULL,\
        MTXT_L, MTXT_T,MTXT_W,MTXT_H,1,mdzone_mtxt_content)

DEF_CONTAINER(win_md_test_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    1,0,0,0,0, W_L,W_T,W_W,W_H, WIN_SH_IDX,WIN_HL_IDX,WIN_SL_IDX,WIN_GRY_IDX,   \
    md_con_keymap,md_con_callback,  \
    (POBJECT_HEAD)&md_item_con1, 1,0)


/*******************************************************************************
*   Local functions & variables define
*******************************************************************************/
TEXT_CONTENT mdzone_mtxt_content[] =
{
    {STRING_UNICODE,{0}},
};

//static UINT16 module_id_list[] =
//{
//    0x20,0x21,0x22,0x23,0x24,
//};

#define MAX_MODULE_CNT 16

static lc_uint32 g_moduleCount = 0;
static lc_uint16 g_pModuleList[MAX_MODULE_CNT];
//static lc_uint16 g_cur_shown_module = 0;

static UINT16 search_next_module_in_list(UINT16 cur_id, INT8 direct)//-1:left, 1:right
{
    UINT8 i=0;
     UINT8 md_num = g_moduleCount;//sizeof(module_id_list)/sizeof(UINT8);

     for(i=0;i<md_num;i++)
     {
        if(cur_id == g_pModuleList[i])
        {
            if((i==0) && (direct == -1))
                return g_pModuleList[md_num-1];
            else if((i==md_num-1) && (direct == 1))
                return g_pModuleList[0];
            else
                return g_pModuleList[i+direct];
        }
            
     }
}

void update_module_status(UINT16 module_id)
{
    UINT32 module_pat_cnt =0;
    UINT32 module_version = 0;
    char str[120] = {0};

    if(g_moduleCount == 0)
    {
        module_pat_cnt = 0;
        module_version = 0;
    }
    else
    {
        module_pat_cnt = LoaderCoreSPI_Module_GetModulePatternCnt(module_id);
        module_version  = LoaderCoreSPI_Module_ReadModuleVersion(module_id);
    }
    
    MEMSET(str,0,sizeof(str));
    snprintf(str, 90, "Count Patterns in Module    0x%x ", module_pat_cnt);
    osd_set_text_field_content(&md_item_txtname1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 10, "0x%x", module_id);
    osd_set_edit_field_content(&md_item_edit2, STRING_ANSI, (UINT32)str);
    osd_set_edit_field_content(&md_item_edit3, STRING_ANSI, (UINT32)str);
    osd_set_edit_field_content(&md_item_edit4, STRING_ANSI, (UINT32)str);
        
    MEMSET(str,0,sizeof(str));
    snprintf(str, 90, "Module Version              0x%x", module_version);
    osd_set_text_field_content(&md_item_txtname5,STRING_ANSI, (UINT32)str);
    
    MEMSET(str,0,sizeof(str));
    snprintf(str, 90, "Module Conut      %d", g_moduleCount);//sizeof(module_id_list)/sizeof(UINT8));
    osd_set_text_field_content(&md_item_txtname6,STRING_ANSI, (UINT32)str);

}

static VACTION win_md_edit_keymap(POBJECT_HEAD pobj, UINT32 key)
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

static VACTION md_item_con_keymap(POBJECT_HEAD pobj, UINT32 key)
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

static void win_md_enter_key(POBJECT_HEAD pobj,UINT8 id)
{
    lc_result lc_ret = LC_SUCCESS;
    UINT16 *pstring = NULL;
    UINT16 module_id =0;

    if(g_moduleCount == 0)
        return;
    
    switch(id)
    {
        case MENU_WR_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit2);
            module_id = com_uni_str2hex(pstring);
            lc_ret =  LoaderCoreSPI_Module_WritePattenToModule(module_id);

            if(lc_ret == LC_SUCCESS)
            {
                update_module_status(module_id);
				osd_draw_object((POBJECT_HEAD )&md_item_con1,C_UPDATE_ALL);
				osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Written Successfully");
            }
            else
                osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Written Fail");

            osd_draw_object((POBJECT_HEAD)&md_item_con7,C_UPDATE_ALL);
            break;
        case MENU_ERASE_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit3);
            module_id = com_uni_str2hex(pstring);
            lc_ret =  LoaderCoreSPI_Module_EarseModulePayload(module_id);

            if(lc_ret == LC_SUCCESS)
            {
                update_module_status(module_id);
				osd_draw_object((POBJECT_HEAD )&md_item_con1,C_UPDATE_ALL);
				osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Erased Successfully");
            }
            else
                osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Erased Fail");

            osd_draw_object((POBJECT_HEAD)&md_item_con7,C_UPDATE_ALL);
            break;
        case MENU_MODIFY_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit4);
            module_id = com_uni_str2hex(pstring);
            lc_ret =  LoaderCoreSPI_Module_WriteLastBitToModule(module_id);

            if(lc_ret == LC_SUCCESS)
            {
                update_module_status(module_id);
				osd_draw_object((POBJECT_HEAD )&md_item_con1,C_UPDATE_ALL);
				osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Modified Successfully");
            }
            else
                osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: Module Modified Fail");

            osd_draw_object((POBJECT_HEAD)&md_item_con7,C_UPDATE_ALL);
            break;
        default:
            break;
    }    
}

static void win_md_left_key(POBJECT_HEAD pobj,UINT8 id)
{
    UINT16 *pstring = NULL;
    UINT32 i = 0;
    UINT16 new_md_id = 0;
    char str[20];

    if(g_moduleCount <=1)
        return ;
    
    switch(id)
    {
        case MENU_WR_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit2);
            break;
        case MENU_ERASE_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit3);
            break;
        case MENU_MODIFY_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit4);
            break;
        default:
            return;
            break;
    }

    i= com_uni_str2hex(pstring);
    new_md_id = search_next_module_in_list(i, -1);
    libc_printf("cur id 0x%x, new id 0x%x\n", i, new_md_id);
    
    update_module_status(new_md_id);
	osd_draw_object((POBJECT_HEAD )&md_item_con1,C_UPDATE_ALL);
    osd_draw_object((POBJECT_HEAD )&md_item_con2,C_UPDATE_ALL);
    osd_draw_object((POBJECT_HEAD )&md_item_con3,C_UPDATE_ALL);
    osd_draw_object((POBJECT_HEAD )&md_item_con4,C_UPDATE_ALL);
    osd_track_object(pobj,C_UPDATE_ALL);

}

static void win_md_right_key(POBJECT_HEAD pobj,UINT8 id)
{
    UINT16 *pstring = NULL;
    UINT32 i = 0;
    UINT16 new_md_id = 0;
    char str[20];

    if(g_moduleCount <=1)
        return ;

    switch(id)
    {
        case MENU_WR_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit2);
            break;
        case MENU_ERASE_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit3);
            break;
        case MENU_MODIFY_MD:
            pstring = (UINT16*)osd_get_edit_field_content(&md_item_edit4);
            break;
        default:
            return;
            break;
    }

    i= com_uni_str2hex(pstring);
    new_md_id = search_next_module_in_list(i, 1);
    libc_printf("cur id 0x%x, new id 0x%x\n", i, new_md_id);
    
    update_module_status(new_md_id);
	osd_draw_object((POBJECT_HEAD )&md_item_con1,C_UPDATE_ALL);
    osd_draw_object((POBJECT_HEAD )&md_item_con2,C_UPDATE_ALL);
    osd_draw_object((POBJECT_HEAD )&md_item_con3,C_UPDATE_ALL);
    osd_draw_object((POBJECT_HEAD )&md_item_con4,C_UPDATE_ALL);
    osd_track_object(pobj,C_UPDATE_ALL);

}

static PRESULT md_item_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
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
                win_md_enter_key(pobj,id);
                break;
            case VACT_DECREASE:
                win_md_left_key(pobj,id);
                break;
            case VACT_INCREASE:
                win_md_right_key(pobj,id);
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

static VACTION md_con_keymap(POBJECT_HEAD pobj, UINT32 key)
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

lc_result md_init_module_list(void)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 *pModuleList = LC_NULL;
    lc_uint32 all_module_cnt = 0;
    
    if((g_moduleCount == 0) || (LC_NULL == g_pModuleList))
    {
    #if 0
        g_pModuleList[0]=0x21;
        g_pModuleList[1]=0x22;
        g_pModuleList[2]=0x23;
        g_moduleCount = 3;
        return LC_SUCCESS;
    #endif 
        result = LC_GetAndCheckExistingModuleList(&pModuleList, &all_module_cnt);
        libc_printf("%s - %d, result: %d\n", __func__, __LINE__, result);
        if(LC_SUCCESS == result)
        {
            libc_printf("LC_GetAndCheckExistingModuleList success\n");
            int i, cnt = 0;
            for(i = 0; i < all_module_cnt; i++)
            {
                libc_printf("%d: 0x%x\n", i, pModuleList[i]);
                if (pModuleList[i] > 0x1f) {
                    g_pModuleList[cnt] = pModuleList[i];
                    cnt++;
                    if (cnt >= MAX_MODULE_CNT)
                        break;
                }
            }
            g_moduleCount = cnt;
        }
        else
        {
            libc_printf("LC_GetAndCheckExistingModuleList fail\n");
            g_moduleCount = 0;
            return LC_FAILURE;
        }
    }
    else 
    {
        libc_printf("module list already init.\n");
    }
    return LC_SUCCESS;
}

static PRESULT md_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    char str[120] = {0};
    UINT32 module_pat_cnt =0;
    UINT32 module_version = 0;
    
    MULTI_TEXT *mtxt = &md_mtxt_zone_city;
    TEXT_CONTENT *txtcont = mdzone_mtxt_content;
    txtcont->b_text_type = STRING_UNICODE;
    txtcont->text.p_string = len_display_str;
    
    switch(event)
    {
    case EVN_PRE_OPEN:
        md_init_module_list();
        
        wincom_open_title((POBJECT_HEAD)&win_md_test_con,RS_MODULE_TEST, 0);

        update_module_status(g_pModuleList[0]);
       
        osd_set_text_field_content(&md_item_txtname7,STRING_ANSI, (UINT32)"Status: No operation ");

        MEMSET(str,0,sizeof(str));
        snprintf(str, 120, "Press UP and Down to select option, LEFT and RIGHT to modify Module.\nPress OK to confirm selection");
        com_asc_str2uni(str, &len_display_str[0]);
 
        osd_set_container_focus((CONTAINER*)pobj,2);
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

