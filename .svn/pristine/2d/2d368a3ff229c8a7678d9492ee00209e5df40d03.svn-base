/*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_mem_mani.c
*
*    Description: The menu for mem manipulate
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

//#include "time_zone_name.h"
#include "win_mem_mani.h"


//#define TIME_DISPLAY
/*******************************************************************************
*   Objects definition
*******************************************************************************/
static VACTION mem_item_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT mem_item_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);

static VACTION mem_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT mem_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);
//static VACTION win_time_edit_keymap(POBJECT_HEAD pobj, UINT32 key);



#define MTXT_SH_IDX WSTL_TEXT_09_HD
#define MTXT_L  (W_L + 30)

#define MTXT_T ( CON_T + (CON_H + CON_GAP)*7 + 8)

#define MTXT_W (W_W - 60)
#define MTXT_H 90//100//150

#define MEM_CON_GAP CON_GAP

//#define MENU_TIMESET_GMT_OFFESET_POPUP_H    300


static UINT16 status_str[60];

#define MENU_MEM_ERASE_ALL 1
#define MENU_MEM_ERASE_IRD_PART 2
#define MENU_MEM_ERASE_LOADER_PART 3
#define MENU_MEM_ERASE_CA_PART 4
#define MENU_MEM_RESET_TO_DEFAULT 5

#define LDEF_CON(root, var_con,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,conobj,focus_id)     \
    DEF_CONTAINER(var_con,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, CON_SH_IDX,CON_HL_IDX,CON_SL_IDX,CON_GRY_IDX,   \
    mem_item_con_keymap,mem_item_con_callback,  \
    conobj, focus_id,1)

#define LDEF_TXTNAME(root,var_txt,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,res_id,str)       \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, TXTN_SH_IDX,TXTN_HL_IDX,TXTN_SL_IDX,TXTN_GRY_IDX,   \
    NULL,NULL,  \
    /*C_ALIGN_LEFT |*/ C_ALIGN_VCENTER, 0,0,res_id,str)

#define LDEF_TXTSTATUS(root,var_txt,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,res_id,str)       \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,idl,idr,idu,idd, l,t,w,h, TXTN_SH_IDX,TXTN_HL_IDX,TXTN_SL_IDX,TXTN_GRY_IDX,   \
    NULL,NULL,  \
    C_ALIGN_LEFT | C_ALIGN_VCENTER, 0,0,res_id,str)

//#define LDEF_TXTSET(root,var_txt,nxt_obj,id,idl,idr,idu,idd,l,t,w,h,res_id,str)        \
//    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
//    id,idl,idr,idu,idd, l,t,w,h, TXTS_SH_IDX,TXTS_HL_IDX,TXTS_SL_IDX,TXTS_GRY_IDX,   \
//    NULL,NULL,  \
//    C_ALIGN_CENTER| C_ALIGN_VCENTER, 20,0,res_id,str)

//#define LDEF_EDIT(root, var_num, nxt_obj, id, idl, idr, idu, idd, l, t, w, h,style,cursormode,pat,pre,sub,str)    \
//    DEF_EDITFIELD(var_num,root,nxt_obj,C_ATTR_ACTIVE,0, \
//    id,idl,idr,idu,idd, l,t,w,h, TXTS_SH_IDX,WSTL_BUTTON_05_HD,TXTS_SL_IDX,TXTS_GRY_IDX,   \
//    win_time_edit_keymap,NULL,  \
//    C_ALIGN_CENTER | C_ALIGN_VCENTER, 20,0,style,pat,10,cursormode,pre,sub,str)


#define LDEF_MM_ITEM(root,var_con,nxt_obj,var_txt_name,id,idu,idd,l,t,w,h,name_id)  \
    LDEF_CON(&root,var_con,nxt_obj,id,id,id,idu,idd,l,t,w,h,&var_txt_name,1)    \
    LDEF_TXTNAME(&var_con,var_txt_name,NULL,0,0,0,0,0,l,t,w,h,name_id,NULL)//\
    //LDEF_TXTSET(&var_con,var_txtset,NULL/*&varLine*/,1,1,1,1,1,l + TXTS_L_OF, t + TXTS_T_OF,TXTS_W,TXTS_H,0,setstr)\
    //LDEF_LINE(&var_con,var_line,NULL,1,1,1,1,1,l + LINE_L_OF, t + LINE_T_OF,LINE_W,LINE_H,0,0)

#define LDEF_MM_ITEM2(root,var_con,nxt_obj,var_txt_name,id,idu,idd,l,t,w,h,name_id,setstr) \
    LDEF_CON(&root,var_con,nxt_obj,id,id,id,idu,idd,l,t,w,h,&var_txt_name,1)    \
    LDEF_TXTSTATUS(&var_con,var_txt_name,NULL,0,0,0,0,0,l,t,w,h,name_id,setstr)//\
    //LDEF_EDIT(&var_con,var_txtset,NULL/*&varLine*/,1,1,1,1,1,l + TXTS_L_OF, t + TXTS_T_OF,TXTS_W,TXTS_H,\
    //                NORMAL_EDIT_MODE , CURSOR_NORMAL, pat,NULL,NULL, setstr)\
    //LDEF_LINE(&var_con,var_line,NULL,1,1,1,1,1,l + LINE_L_OF, t + LINE_T_OF,LINE_W,LINE_H,0,0)

#define LDEF_MTXT(root,var_mtxt,next_obj,l,t,w,h,cnt,content) \
    DEF_MULTITEXT(var_mtxt,&root,next_obj,C_ATTR_ACTIVE,0, \
        0,0,0,0,0, l,t,w,h, MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,MTXT_SH_IDX,   \
        NULL,NULL,  \
        C_ALIGN_LEFT | C_ALIGN_TOP, cnt,  4,4,w-8,h-8,NULL,content)


LDEF_MM_ITEM(win_mem_con,mem_item_con1, &mem_item_con2,mem_item_txtname1,\
                1,5,2, CON_L, CON_T + (CON_H + MEM_CON_GAP)*0,CON_W,CON_H, RS_ERASE_ALL)
LDEF_MM_ITEM(win_mem_con,mem_item_con2, &mem_item_con3,mem_item_txtname2,\
                2,1,3,CON_L, CON_T + (CON_H + MEM_CON_GAP)*1,CON_W,CON_H, RS_ERASE_IRD_PART)
LDEF_MM_ITEM(win_mem_con,mem_item_con3, &mem_item_con4,mem_item_txtname3,\
                3,2,4,CON_L, CON_T + (CON_H + MEM_CON_GAP)*2,CON_W,CON_H, RS_ERASE_LOADER_PART)
LDEF_MM_ITEM(win_mem_con,mem_item_con4, &mem_item_con5,mem_item_txtname4,\
                4,3,5,CON_L, CON_T + (CON_H + MEM_CON_GAP)*3,CON_W,CON_H, RS_ERASE_CA_PART)
LDEF_MM_ITEM(win_mem_con,mem_item_con5, &mem_item_con6,mem_item_txtname5,\
                5,4,1,CON_L, CON_T + (CON_H + MEM_CON_GAP)*4,CON_W,CON_H, RS_RESET_TO_DEFAULT)
                
LDEF_MM_ITEM2(win_mem_con,mem_item_con6,&mem_mtxt_note, mem_item_txtname7, 6,0,0,\
                      CON_L, CON_T + (CON_H + MEM_CON_GAP)*5,CON_W,CON_H,0,status_str)

LDEF_MTXT(win_mem_con,mem_mtxt_note,NULL,\
        MTXT_L, MTXT_T,MTXT_W,MTXT_H,1,memzone_mtxt_content)

DEF_CONTAINER(win_mem_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    1,0,0,0,0, W_L,W_T,W_W,W_H, WIN_SH_IDX,WIN_HL_IDX,WIN_SL_IDX,WIN_GRY_IDX,   \
    mem_con_keymap,mem_con_callback,  \
    (POBJECT_HEAD)&mem_item_con1, 1,0)


/*******************************************************************************
*   Local functions & variables define
*******************************************************************************/
//static date_time win_time_local_time;

TEXT_CONTENT memzone_mtxt_content[] =
{
    {STRING_UNICODE,{0}},
};

/*******************************************************************************
*   key mapping and event callback definition
*******************************************************************************/

static VACTION mem_item_con_keymap(POBJECT_HEAD pobj, UINT32 key)
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

static void win_mem_enter_key(POBJECT_HEAD pobj,UINT8 id)
{
    UINT8 cur_select= 0;
    lc_result result = LC_FAILURE;
   
    switch(id)
    {
        case MENU_MEM_ERASE_ALL:
            libc_printf("enter MENU_MEM_ERASE_ALL\n");

            result = LoaderCoreSPI_Module_EraseEntireNVRAMPartition();
            if(result == LC_SUCCESS)
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Entire NVRAM erased successfully");
            else
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Entire NVRAM erased Fail");

            osd_draw_object((POBJECT_HEAD)&mem_item_con6,C_UPDATE_ALL);
            break;
        case MENU_MEM_ERASE_IRD_PART:
            libc_printf("enter MENU_MEM_ERASE_IRD_PART\n");

            result = LoaderCoreSPI_Module_EraseIrdetoNVRAMPartition();
            if(result == LC_SUCCESS)
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Irdeto NVRAM Partition erased successfully");
            else
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Irdeto NVRAM Partition erased Fail");

            osd_draw_object((POBJECT_HEAD)&mem_item_con6,C_UPDATE_ALL);
            break;
        case MENU_MEM_ERASE_LOADER_PART:

            result = LoaderCoreSPI_Module_EraseLoaderNVRAMPartition();
            if(result == LC_SUCCESS)
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Loader NVRAM Partition erased successfully");
            else
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Loader NVRAM Partition erased Fail");

            osd_draw_object((POBJECT_HEAD)&mem_item_con6,C_UPDATE_ALL);
            break;
        case MENU_MEM_ERASE_CA_PART:

            result = LoaderCoreSPI_Module_EraseCANVRAMPartition();
            if(result == LC_SUCCESS)
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: CA NVRAM Partition erased successfully");
            else
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: CA NVRAM Partition erased Fail");

            osd_draw_object((POBJECT_HEAD)&mem_item_con6,C_UPDATE_ALL);
            break;
        case MENU_MEM_RESET_TO_DEFAULT:

            result = LoaderCoreSPI_Module_RetsetToDefault();
            if(result == LC_SUCCESS)
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Reset to default successfully");
            else
                osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)"Status: Reset to default Fail");

            osd_draw_object((POBJECT_HEAD)&mem_item_con6,C_UPDATE_ALL);
            break;    
        default:
            break;
    }
}

static PRESULT mem_item_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
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
                win_mem_enter_key(pobj,id);
                break;
            case VACT_DECREASE:
                //win_mem_left_key(pobj,id);
                break;
            case VACT_INCREASE:
                //win_mem_right_key(pobj,id);
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

static VACTION mem_con_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act=VACT_PASS;
  
    UINT8 save= 0;
    INT32 ret1= 0;
    
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
        //win_mem_get_input();
        
          
        //win_compopup_init(WIN_POPUP_TYPE_OKNO);
        //win_compopup_set_msg(NULL,NULL,RS_MSG_INVALID_INPUT_CONTINUE);
        //win_compopup_set_frame(GET_MID_L(300),GET_MID_T(100),320,200);
        if(0)//(WIN_POP_CHOICE_YES == win_compopup_open_ext(&save))
        {
            act = VACT_PASS;
        }
        else
        {
            act = VACT_CLOSE;
        }
          

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

static PRESULT mem_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    char str[90] = {0};

    MULTI_TEXT *mtxt = &mem_mtxt_note;
    TEXT_CONTENT *txtcont = memzone_mtxt_content;
    txtcont->b_text_type = STRING_UNICODE;
    txtcont->text.p_string = len_display_str;
    
    switch(event)
    {
    case EVN_PRE_OPEN:
        wincom_open_title((POBJECT_HEAD)&win_mem_con,RS_MEM_MANI, 0);

        MEMSET(str,0,sizeof(str));
        snprintf(str, 90, "Status: No Operation");
        //snprintf(str, 90, "");
        osd_set_text_field_content(&mem_item_txtname7,STRING_ANSI, (UINT32)str);


        MEMSET(str,0,sizeof(str));
        snprintf(str, 90, "Press UP and Down to select option.\nPress OK to confirm selection");
        com_asc_str2uni(str, &len_display_str[0]);
        
        osd_set_container_focus((CONTAINER*)pobj,1);
        break;

    case EVN_POST_OPEN:
        break;

    case EVN_PRE_CLOSE:
        //osd_get_edit_field_mem_date(&mem_item_edit5, NULL);
         
        //    osd_get_edit_field_mem_date(&mem_item_edit6, NULL);
       
       

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



