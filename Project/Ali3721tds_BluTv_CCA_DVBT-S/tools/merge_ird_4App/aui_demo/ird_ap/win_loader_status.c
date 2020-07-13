/*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_loader_status.c
*
*    Description: To realize the UI for display loader information
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

#include "osdobjs_def.h"

#include "string.id"
#include "images.id"
#include "osd_config.h"
//#include "osd_rsc.h"

#include "win_com_menu_define.h"
#include "win_com.h"
//#include "menus_root.h"
//#include "win_com_popup.h"
//#include "ap_ctrl_display.h"
//add by bill 2012-02-13
#include "../platform/board.h"
#include "win_loader_status.h"
//#include "win_diagnosis.h"
//#include "menus_root.h"
//#include "win_prog_detail.h"


/*******************************************************************************
* Objects declaration
*******************************************************************************/
static UINT16 info_name_str[30];
static UINT16 info1_str[30];
static UINT16 info2_str[30];
static UINT16 info3_str[30];

static VACTION info_con_keymap(POBJECT_HEAD pobj, UINT32 key);
static PRESULT info_con_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2);



/* define in win_com_menu_define.h already */
#define W_L         82//248
#define W_T         98
#define W_W         858//692
#define W_H         488


#define CON_L       (W_L+20)
#define CON_T       (W_T + 4)
#define CON_W       (W_W - 60)
#define CON_H       40
#define CON_GAP     4//8//12

#define INFO_TXT_NAME_L 20
#define INFO_TXT_NAME_W 230//200
#define INFO_TXT1_L (INFO_TXT_NAME_L+INFO_TXT_NAME_W)
#define INFO_TXT1_W 230
#define INFO_TXT2_L (INFO_TXT1_L+INFO_TXT1_W)
#define INFO_TXT2_W 220//180
#define INFO_TXT3_L (INFO_TXT2_L+INFO_TXT2_W)
#define INFO_TXT3_W 140//180

#define LINE_L_OF   0
#define LINE_T_OF   (CON_H+4)
#define LINE_W      CON_W
#define LINE_H      4



//#define FLAG_LOG_ENABLE    0x00000100
//#define FLAG_LOG_END       0x00000001
//#define MEMCFG_POSITION_IN_CHUNK 2
//#define LOG_THRESHOLD 9999
//#define SAMPLE_CHIP_ID_HIGH_VALUE 0x1e
//#define SAMPLE_CHIP_ID_LOW_VALUE  0x22
//#define LENGTH_2BYTES  16
//#define LENGTH_3BYTES  24

#define LDEF_CON(root, var_con,nxt_obj,l,t,w,h,conobj)        \
    DEF_CONTAINER(var_con,root,nxt_obj,C_ATTR_ACTIVE,0, \
    1,1,1,1,1, l,t,w,h, CON_SH_IDX,CON_HL_IDX,CON_SL_IDX,CON_GRY_IDX,   \
     NULL,NULL,  \
    conobj, 0,0)

#define LDEF_TXT(root,var_txt,nxt_obj,ID,l,t,w,h,res_id,str)       \
    DEF_TEXTFIELD(var_txt,root,nxt_obj,C_ATTR_ACTIVE,0, \
    ID,ID,ID,ID,ID, l,t,w,h, TXTN_SH_IDX,TXTN_HL_IDX,TXTN_SL_IDX,TXTN_GRY_IDX,   \
    NULL,NULL,  \
    C_ALIGN_LEFT | C_ALIGN_VCENTER, 0,0,res_id,str)

#define LDEF_LIST_ITEM(root,var_con,nxt_obj,var_txt_name,var_txt1,var_txt2,var_txt3, var_line,l,t,w,h)   \
    LDEF_CON(&root, var_con,nxt_obj,l,t,w,h,&var_txt_name)  \
    LDEF_TXT(&var_con,var_txt_name,&var_txt1 ,1,l + INFO_TXT_NAME_L, t,INFO_TXT_NAME_W,h,0,info_name_str)   \
    LDEF_TXT(&var_con,var_txt1,&var_txt2 ,2,l + INFO_TXT1_L, t,INFO_TXT1_W,h,0,info1_str)  \
    LDEF_TXT(&var_con,var_txt2,&var_txt3/*&varLine*/ ,3,l + INFO_TXT2_L, t,INFO_TXT2_W,h,0,info2_str)  \
    LDEF_TXT(&var_con,var_txt3,NULL/*&varLine*/ ,4,l + INFO_TXT3_L, t,INFO_TXT3_W,h,0,info3_str)  \
    LDEF_LINE(&var_con,var_line,NULL,1,1,1,1,1,l + LINE_L_OF, t + LINE_T_OF,LINE_W,LINE_H,0,0)


LDEF_LIST_ITEM(win_loader_status_con,info_item_con,NULL,info_txt_name,info_txt1,info_txt2,info_txt3,info_line,\
    CON_L, CON_T + (CON_H + CON_GAP)*0,CON_W,CON_H)

DEF_CONTAINER(win_loader_status_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    1,0,0,0,0, W_L,W_T,W_W,W_H, 0/*WIN_SH_IDX*/,WIN_HL_IDX,WIN_SL_IDX,WIN_GRY_IDX,   \
    info_con_keymap,info_con_callback,  \
    (POBJECT_HEAD)&info_item_con, 0,0)

/*******************************************************************************
*   Local functions & variables declare
*******************************************************************************/
static void set_info_con_rect(UINT16 l, UINT16 t, UINT16 w, UINT16 h)
{
    osd_set_rect(&info_item_con.head.frame, l,t,w,h);
    osd_set_rect(&info_txt_name.head.frame, l + INFO_TXT_NAME_L, t,INFO_TXT_NAME_W,h);
    osd_set_rect(&info_txt1.head.frame, l + INFO_TXT1_L, t,INFO_TXT1_W,h);
    osd_set_rect(&info_txt2.head.frame, l + INFO_TXT2_L, t,INFO_TXT2_W,h);
    osd_set_rect(&info_txt3.head.frame, l + INFO_TXT3_L, t,INFO_TXT3_W,h);
    osd_set_rect(&info_line.head.frame, l + LINE_L_OF, t+LINE_T_OF,LINE_W,LINE_H);
}

#define OTP_0X0_ADDR                (0x0*4)

static INT8 get_cssn(UINT32 *chip_id)
{
    UINT32 buf = 0;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;
    ret = aui_otp_read(OTP_0X0_ADDR, (UINT8 *)chip_id, 4);
    if(ret!=AUI_RTN_SUCCESS)
        return -1;
    libc_printf("0x0: 0x%x\n", *chip_id);
   
    return 0;
}

#define ASC2INT(c) ((c >= '0') ? c-'0' : c)

static void display_sys_infomation(UINT8 flag)
{
    UINT8 i=0,j=0;
    char str[30] = {0};
    UINT32 len =0;
    lc_result lc_ret = LC_FAILURE;
    lc_bbcb_parameters pBBCBParameters = {0};
    lc_bool pUpdateCRC = LC_TRUE;
    lc_uint16 pVariant = 0;
    lc_uint16 pSubVariant = 0;
    lc_uint16 pSystemId = 0;
    lc_uint16 pKeyVersion = 0;
    lc_uint16 pSignatureVersion = 0 ;
    lc_uint16 pDownloadSequenceNumber = 0;
    lc_char iSignVersion[4] = {0};
    lc_char iSignSN[4] = {0};
    
    lc_ret = LoaderCoreAPI_ReadBBCB(&pBBCBParameters, &pUpdateCRC);

    if(lc_ret!=LC_SUCCESS)
        libc_printf("display_sys_infomation: LoaderCoreAPI_ReadBBCB fail\n");
//line1
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(0),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Serial Nr:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    UINT32 serial_number = ((pBBCBParameters.serial_number[0] << 24)
                                   | (pBBCBParameters.serial_number[1] << 16)
                                   | (pBBCBParameters.serial_number[2] << 8)
                                   | (pBBCBParameters.serial_number[3] << 0));
    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%u",serial_number);
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Loader Ver:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 10, "%d.%d.%d", pBBCBParameters.loader_major_version, pBBCBParameters.loader_minor_version, pBBCBParameters.loader_version_buildnumber);
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);

    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);

//line2    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(1),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Manuf ID:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%d", pBBCBParameters.manufacturer_id);
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "H/W Ver:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%d", pBBCBParameters.hardware_version);
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);

//line3    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(2),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "OUI:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "0x%02x%02x%02x",
                 pBBCBParameters.OUI[0],
                 pBBCBParameters.OUI[1],
                 pBBCBParameters.OUI[2]);
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Boot Check Alg:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%d", pBBCBParameters.boot_check_algorithm);
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);

//line4    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(3),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Random Nr:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    UINT32 random_number = ((pBBCBParameters.random_number[0] << 24)
                                   | (pBBCBParameters.random_number[1] << 16)
                                   | (pBBCBParameters.random_number[2] << 8)
                                   | (pBBCBParameters.random_number[3] << 0));
    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%u", random_number);
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "");
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);

    lc_ret = LoaderCoreAPI_GetVariant(&pVariant, &pSubVariant);
    if(lc_ret!=LC_SUCCESS)
        libc_printf("display_sys_infomation: LoaderCoreAPI_GetVariant fail\n");

//line5    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(4),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Variant:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    if (pVariant == 0xffff) 
    {
        snprintf(str, 30, "%d", -1);
    } 
    else 
    {
        snprintf(str, 30, "%d", pVariant);
    }
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Sub Variant:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    if (pSubVariant == 0xffff) 
    {
        snprintf(str, 30, "%d", -1);
    } 
    else 
    {
        snprintf(str, 30, "%d", pSubVariant);
    }
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);

    lc_ret = LoaderCoreAPI_GetUKInfo(&pSystemId, &pKeyVersion, &pSignatureVersion);
    if(lc_ret!=LC_SUCCESS)
        libc_printf("display_sys_infomation: LoaderCoreAPI_GetUKInfo fail\n");

//line6    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(5),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Key Status:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    if(lc_ret == LC_SUCCESS)
        snprintf(str, 30, "LC_SUCCESS");
    else
        snprintf(str, 30, "LC_FAILURE");
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Key Ver:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%d", pKeyVersion);
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL); 

    lc_ret = LoaderCoreAPI_GetDownloadSequenceNumber(&pDownloadSequenceNumber);
    if(lc_ret!=LC_SUCCESS)
    {
        pDownloadSequenceNumber = 0xffff;
        libc_printf("display_sys_infomation: LoaderCoreAPI_GetDownloadSequenceNumber fail\n");
    }

//line7    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(6),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "DL Seq Nr:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30,  "%d", pDownloadSequenceNumber);
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Key Sys ID:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    if (pSystemId == 0xffff) 
    {
        snprintf(str, 30, "%d", -1);
    } 
    else 
    {
        snprintf(str, 30, "0x%04x", pSystemId);
    }
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);

    lc_ret = LoaderCoreAPI_GetISignInfo(iSignVersion, iSignSN);
    if(lc_ret!=LC_SUCCESS)
        libc_printf("display_sys_infomation: LoaderCoreAPI_GetISignInfo fail\n");

//line8    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(7),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "ISIGN Ver:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%d.%d.%c%d", \
                 ASC2INT(iSignVersion[0]), \
                 ASC2INT(iSignVersion[1]), \
                 ASC2INT(iSignVersion[2]), \
                 ASC2INT(iSignVersion[3]));
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "ISIGN Ser:");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%d%d%d%d", \
                 ASC2INT(iSignSN[0]), \
                 ASC2INT(iSignSN[1]), \
                 ASC2INT(iSignSN[2]), \
                 ASC2INT(iSignSN[3]));
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL); 

//line9    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(8),CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "CSSN:");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    UINT32 uChipID = 0;
    get_cssn(&uChipID);
    
    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "%u", uChipID);
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "");
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL); 

//line10    
    //re-arrange the container.
    set_info_con_rect(CON_L, CON_T + (CON_H + CON_GAP)*(9)+18,CON_W,CON_H);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "Press Exit to back");
    osd_set_text_field_content(&info_txt_name,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "to Main menu");
    osd_set_text_field_content(&info_txt1,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "");
    osd_set_text_field_content(&info_txt2,STRING_ANSI, (UINT32)str);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 30, "");
    osd_set_text_field_content(&info_txt3,STRING_ANSI, (UINT32)str);
    
    osd_draw_object((POBJECT_HEAD )&info_item_con,C_UPDATE_ALL);  
}

/*******************************************************************************
*   Window's keymap, proc and  callback
*******************************************************************************/
static VACTION info_con_keymap(POBJECT_HEAD pobj __MAYBE_UNUSED__, UINT32 vkey)
{
    VACTION act=0;

    switch(vkey)
    {
    case V_KEY_MENU:
    case V_KEY_EXIT:
        act = VACT_CLOSE;
        break;
    default:
        act = VACT_PASS;
    break;
    }

    return act;
}

static PRESULT info_con_callback(POBJECT_HEAD pobj __MAYBE_UNUSED__, 
    VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    POBJECT_HEAD submenu = NULL;
    INT32 result = 0;

	if(0 == result)
	{
		;
	}
    switch(event)
    {
    case EVN_PRE_OPEN:
        wincom_open_title((POBJECT_HEAD)&win_loader_status_con,RS_LOADER_STATUS, 0);
        break;
    case EVN_POST_OPEN:
        display_sys_infomation(0);
        break;
    case EVN_PRE_CLOSE:
        /* Make OSD not flickering */
        *((UINT32*)param2) &= ~C_CLOSE_CLRBACK_FLG;
        break;
    case EVN_POST_CLOSE:
        break;
    case EVN_UNKNOWN_ACTION:
        param1 &= 0xff;
        break;
    default:
        break;
    }
    return ret;
}


