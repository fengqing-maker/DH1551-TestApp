/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_loader_param.c
*
*    Description:   The setting of OTA upgrade
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
#include <bus/tsi/tsi.h>

#include <api/libpub/lib_frontend.h>

#include <api/libosd/osd_lib.h>

#include <api/libchunk/chunk.h>
#include <sys_parameters.h>
#include <api/libc/fast_crc.h>
#include <hld/nim/nim_tuner.h>

#include "osdobjs_def.h"
#include "string.id"
#include "images.id"
#include "osd_config.h"
//#include "menus_root.h"
#include "win_com.h"
//#include "win_com_popup.h"
//#include "win_com_list.h"
//#include "win_signalstatus.h"
//#include "win_signal.h"

#include "win_com.h"
//#include "control.h"

//#define  WIN_OTA_SET_PRIVATE_MACROS
#include "win_loader_param.h"
//#include "platform/board.h"
#include "ali_dvt_internel.h"

//#define  LOADER_SEE_ID  0x07F80000
#define OTA_PRINTF(...)
//#define OTA_PRINTF          libc_printf

//===================== local variables ==========================
static UINT16 otaset_display_strs[5][30]={{0,},};
static char pid_pat[]  = "s4";//"r32~8191";

LDEF_MENU_ITEM_EDF(win_otaupg_con,wota_con0,&wota_con1,wota_txt0,wota_num0,wota_line0,1,8,2,\
            CON_L, CON_T + (CON_H + CON_GAP)*0, CON_W, CON_H,RS_FREQ, \
            NORMAL_EDIT_MODE, CURSOR_SPECIAL, lnb_pat, NULL,lnb_sub,otaset_display_strs[0])

LDEF_MENU_ITEM_SEL(win_otaupg_con,wota_con1,&wota_con2,wota_txt1,wota_num1,wota_line1,2,1,3,\
            CON_L, CON_T + (CON_H + CON_GAP)*1, CON_W, CON_H, RS_DISEQC, STRING_PROC, 0, 0, NULL)

LDEF_MENU_ITEM_SEL(win_otaupg_con,wota_con2,&wota_con3,wota_txt2,wota_num2,wota_line2,3,2,4,\
            CON_L, CON_T + (CON_H + CON_GAP)*2, CON_W, CON_H,RS_22K, STRING_PROC, 0, 0, NULL)

LDEF_MENU_ITEM_EDF(win_otaupg_con,wota_con3,&wota_con4,wota_txt3,wota_num3,wota_line3,4,3,5,\
            CON_L, CON_T + (CON_H + CON_GAP)*3,CON_W, CON_H, RS_TUN_FREQ, \
            NORMAL_EDIT_MODE, CURSOR_SPECIAL, fre_pat, NULL,fre_sub,otaset_display_strs[1])

LDEF_MENU_ITEM_SEL(win_otaupg_con,wota_con4,&wota_con5,wota_txt4,wota_num4,wota_line4,5,4,6,\
            CON_L, CON_T + (CON_H + CON_GAP)*4, CON_W, CON_H, RS_POLAR, STRING_PROC, 0, 0, NULL)

LDEF_MENU_ITEM_EDF(win_otaupg_con,wota_con5,&wota_con6,wota_txt5,wota_num5,wota_line5,6,5,7,\
            CON_L, CON_T + (CON_H + CON_GAP)*5, CON_W, CON_H, RS_SYM_RATE, NORMAL_EDIT_MODE, \
            CURSOR_SPECIAL, symb_pat,NULL,symb_sub,otaset_display_strs[2])

LDEF_MENU_ITEM_SEL(win_otaupg_con,wota_con6,&wota_con7,wota_txt6,wota_num6,wota_line6,7,6,8,\
            CON_L, CON_T + (CON_H + CON_GAP)*6, CON_W, CON_H, RS_FEC, STRING_PROC, 0, 0, NULL)

LDEF_MENU_ITEM_EDF(win_otaupg_con,wota_con7,&wota_mtxt1,wota_txt7,wota_num7,wota_line7,8,7,1,\
            CON_L, CON_T + (CON_H + CON_GAP)*7, CON_W, CON_H, RS_DL_PID, NORMAL_EDIT_MODE, \
            CURSOR_SPECIAL, pid_pat,NULL,NULL,otaset_display_strs[3])

LDEF_MTXT(win_otaupg_con,wota_mtxt1,NULL,\
        MTXT_L, MTXT_T,MTXT_W,MTXT_H,1,wota_mtxt_content)
        
//LDEF_TXT_BTN(win_otaupg_con,wota_txt8,&wota_line8, wota_line8, 9,9,9,\
//            CON_L, CON_T + (CON_H + CON_GAP)*8, CON_W, CON_H,RS_COMMON_YES)


LDEF_WIN(win_otaupg_con,&wota_con0,W_L, W_T,W_W,W_H,1)

static lc_dvbssu_dl_info_st dvbssuParameters={0};

#define PRIVATE_DATA_MAX_LEN (48)
static char g_private[PRIVATE_DATA_MAX_LEN]={0};

static char fre_pat_dvbt[]  = "r100000~858000";
static char symb_pat_dvbt[]  = "r1000~45000";
static char fre_pat_dvbc[]  = "f32";
static char symb_pat_dvbc[]  = "s5";

#define MAX_DISQ_NUM 5
static char diseqc_str[MAX_DISQ_NUM][8] =
{
    "None",
    "A",
    "B",
    "C",
    "D",
};

static char dvbs_22k_str[2][5] =
{
    "OFF",
    "ON",
};

static char tp_polarity_ids[5][15] =
{
    "Horizontal",
    "Vertical",
    "None",
    "CIRCULAR_LEFT",
    "CIRCULAR_RIGHT"
};

static char fec_str[10][5] =
{
    "1/2",
    "2/3",
    "3/4",
    "4/5",
    "5/6",
    "6/7",
    "7/8",
    "8/9",
    "3/5",
    "9/10",
};

TEXT_CONTENT wota_mtxt_content[] =
{
    {STRING_UNICODE,{0}},
};

#define DEFAULT_LNB_FREQ 9750
#define DEFAULT_TUN_FREQ 5150
#define DEFAULT_SYM      27500
#define DEFAULT_OTA_PID  0x100

static UINT32 ota_lnb_freq=DEFAULT_LNB_FREQ;
static UINT16 ota_diseqc_idx=0;
static UINT16 ota_22k_idx=0;
static UINT32 ota_freq=DEFAULT_TUN_FREQ;
static UINT16 ota_pol_idx=0;
static UINT32 ota_symb=DEFAULT_SYM;
static UINT16 ota_fec_idx=0;
static UINT16 ota_pid=DEFAULT_OTA_PID;

//static UINT16 ota_id=0;
//static UINT16 ota_satpos=0;
//static UINT16 ota_pol=0;

//static OTA_CFG m_ota_cfg;

//static OUC_CFG m_ouc_cfg;

//static UINT32 cur_front_type = 0;
/*******************************************************************************
*   key mapping and event callback definition
*******************************************************************************/

static VACTION  otaset_btn_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act=0;

    switch(key)
    {
    case V_KEY_ENTER:
    case V_KEY_RIGHT:
        act = VACT_ENTER;
        break;
    default:
        act = VACT_PASS;
        break;
    }

    return act;
}

static PRESULT  otaset_btn_callback(POBJECT_HEAD pobj,VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    VACTION unact=0;
    POBJECT_HEAD pmenu = NULL;
    INT32 func_ret=0;

	if(0 == func_ret)
	{
		;
	}
	MEMSET(&pmenu,0,sizeof(POBJECT_HEAD));
    switch(event)
    {
    case EVN_UNKNOWN_ACTION:
        unact = (VACTION)(param1>>16);
        if(VACT_ENTER == unact)
        {
        }
        break;
    default:
        break;
    }

    return ret;
}

static VACTION  otaset_item_sel_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act=0;

    switch(key)
    {
    case V_KEY_LEFT:
        act = VACT_DECREASE;
        break;
    case V_KEY_RIGHT:
        act = VACT_INCREASE;
        break;
    case V_KEY_ENTER:
        act = VACT_ENTER;//VACT_POP_UP;
        break;
    default:
        act = VACT_PASS;
        break;
    }

    return act;
}

static PRESULT  otaset_item_sel_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    UINT8 bid=0;
    UINT32 sel=0;
    UINT16 *uni_str=NULL;
    VACTION unact=0;
    MULTISEL *msel=NULL;
    CONTAINER *con = NULL;

    bid = osd_get_obj_id(pobj);

    switch(event)
    {
    case EVN_REQUEST_STRING:
        sel = param1;
        uni_str= (UINT16*)param2;
        
        if(EDIT_DISEQC_ID == bid)
        {            
            //libc_printf("diseqc sel %d\n", sel);
            com_asc_str2uni((UINT8 *)diseqc_str[sel], uni_str);
        }
        else if(EDIT_22K_ID == bid)
        {
            com_asc_str2uni((UINT8 *)dvbs_22k_str[sel], uni_str);
        }
        else if(EDIT_POL_ID == bid)
        {
            com_asc_str2uni((UINT8 *)tp_polarity_ids[sel], uni_str);
        }
        else if(EDIT_FEC_ID == bid)
        {
            com_asc_str2uni((UINT8 *)fec_str[sel], uni_str);
        }
        break;
    case EVN_POST_CHANGE:
        sel = param1;
 
        if(EDIT_DISEQC_ID == bid)
        {
            con = &wota_con1;
        }
        else if(EDIT_22K_ID == bid)
        {
             con = &wota_con2;
        }
        else if(EDIT_POL_ID == bid)
        {
             con = &wota_con4;
        }
        else if(EDIT_FEC_ID == bid)
        {
             con = &wota_con6;
        }
        osd_draw_object(con, C_UPDATE_ALL);
        osd_track_object(con,C_UPDATE_ALL);
        break;
    case EVN_UNKNOWN_ACTION:
        unact = (VACTION)(param1>>16);
        //ret = PROC_LOOP;
        break;
    default:
        break;
    }

    return ret;
}

static VACTION  otaset_item_edf_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act=0;

    switch(key)
    {
    case V_KEY_0:   case V_KEY_1:   case V_KEY_2:   case V_KEY_3:
    case V_KEY_4:   case V_KEY_5:   case V_KEY_6:   case V_KEY_7:
    case V_KEY_8:   case V_KEY_9:
        act = key - V_KEY_0 + VACT_NUM_0;
        break;
    case V_KEY_LEFT:
        act = VACT_EDIT_LEFT;
        break;
    case V_KEY_RIGHT:
        act = VACT_EDIT_RIGHT;
        break;
    default:
        act = VACT_PASS;
        break;
    }

    return act;
}

static PRESULT  otaset_item_edf_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    UINT8 bid=0;
    UINT8 status=0;
    EDIT_FIELD *edf=NULL;

    bid = osd_get_obj_id(pobj);

    edf = (EDIT_FIELD*)pobj;

    switch(event)
    {
    case EVN_POST_CHANGE:
        status = osd_get_edit_field_status(edf);
        if(SELECT_STATUS == status)
        {
            if(( EDIT_22K_ID==bid)  || (EDIT_TUN_FREQ_ID==bid ) )
            {
            }
        }
        break;
    case EVN_PARENT_FOCUS_POST_LOSE:
        libc_printf("FOCUS lose %d\n", bid);
        
        //win_otaset_get_ota_param_display();
        break;
    default:
        break;
    }

    return ret;
}

static VACTION  otaset_item_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act = VACT_PASS;

    return act;
}

static PRESULT  otaset_item_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;

    return ret;
}

static VACTION  otaset_keymap(POBJECT_HEAD pobj, UINT32 key)
{
    VACTION act=0;

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

void get_download_service_nvram_info()
{
    lc_result lc_ret = LC_SUCCESS;
    lc_buffer_st pPrivateData={0};
    char show_buffer[256]={0};
    ird_spi_dmd_delivery_t *nvram_info= NULL;
    ird_spi_dmd_satellite_desc_t * sat_info = NULL;

    lc_ret = LC_InitializePSVariable();

    if(LC_SUCCESS == lc_ret)
    {
        libc_printf("LC_InitializePSVariable success\n");
    }
    else
    {
        libc_printf("LC_InitializePSVariable fail\n");
    }

    lc_ret = LC_UtilGetDvbssuDownloadParameters(&dvbssuParameters, g_private);

    if(LC_SUCCESS == lc_ret)
    {
        nvram_info = (ird_spi_dmd_delivery_t *)g_private;
        sat_info = (ird_spi_dmd_satellite_desc_t *) & (nvram_info->delivery.satellite);
        nvram_info->device_type = DMD_SATELLITE;
        #if 0
        DVT_APP_LOG("type of dvbtype is 0x%02x\n", nvram_info->device_type);
        DVT_APP_LOG(" sat_info frequency  0x%05x\n", sat_info->frequency);
        DVT_APP_LOG(" sat_info symbol_rate  0x%05x\n", sat_info->symbol_rate);
        DVT_APP_LOG(" sat_info modulation_system  0x%05x\n", sat_info->modulation_system);
        DVT_APP_LOG(" sat_info polarization  0x%05x\n", sat_info->polarization);
        DVT_APP_LOG(" sat_info modulation  0x%05x\n", sat_info->modulation);
        DVT_APP_LOG(" sat_info fec_rate  0x%05x\n", sat_info->fec_rate);
        DVT_APP_LOG(" sat_info roll_off  0x%05x\n", sat_info->roll_off);
        DVT_APP_LOG(" sat_info lnb_tone_state  0x%05x\n", sat_info->lnb_tone_state);
        DVT_APP_LOG(" sat_info diseqc_port  0x%05x\n", sat_info->diseqc_port);
        DVT_APP_LOG(" sat_info band.lo  0x%05x\n", sat_info->band.lo);
        DVT_APP_LOG("pDvbssuParameters.pid (0x%04x)\n", dvbssuParameters.pid);
        #endif

        libc_printf("LC_UtilGetDvbssuDownloadParameters success\n");
    }
    else
    {
        libc_printf("LC_UtilGetDvbssuDownloadParameters fail\n");
    }

    lc_ret = LC_FinalizePSVariable();

    if(LC_SUCCESS == lc_ret)
    {
        libc_printf("LC_FinalizePSVariable success\n");
    }
    else
    {
        libc_printf("LC_FinalizePSVariable fail\n");
    }
}

static PRESULT  otaset_callback(POBJECT_HEAD pobj, VEVENT event, UINT32 param1, UINT32 param2)
{
    PRESULT ret = PROC_PASS;
    PRESULT func_ret = PROC_PASS;
    POBJECT_HEAD    pfocusobj = NULL;
    MULTISEL *msel=NULL;
    char str[120] = {0};
    VACTION unact = VACT_PASS;

    MULTI_TEXT *mtxt = &wota_mtxt1;
    TEXT_CONTENT *txtcont = wota_mtxt_content;
    txtcont->b_text_type = STRING_UNICODE;
    txtcont->text.p_string = len_display_str;
    
	if(0 == func_ret)
	{
		;
	}
	MEMSET(&pfocusobj,0,sizeof(POBJECT_HEAD));
  
    switch(event)
    {
    case EVN_PRE_OPEN:

        get_download_service_nvram_info();
        
        msel = &wota_num1;
        osd_set_multisel_count(msel, MAX_DISQ_NUM);

        msel = &wota_num2;
        osd_set_multisel_count(msel, 2);//22k

        msel = &wota_num4;
        osd_set_multisel_count(msel, 5);//pol

        msel = &wota_num6;
        osd_set_multisel_count(msel, 10);//fec

        MEMSET(str,0,sizeof(str));
        snprintf(str, 120, "Press UP and Down to select option, LEFT and RIGHT to modify Module.\nPress OK to confirm selection");
        com_asc_str2uni((UINT8 *)str, &len_display_str[0]);

        wincom_open_title(pobj,RS_LOADER_PARAM, 0);

        pfocusobj = osd_get_focus_object(pobj);
        if(pfocusobj != NULL)
        {
            if(pfocusobj->b_attr != C_ATTR_ACTIVE)
            {
                pfocusobj = osd_get_adjacent_object(pfocusobj,VACT_CURSOR_DOWN);
                if(pfocusobj != NULL)
                {
                    func_ret=osd_change_focus(pobj,pfocusobj->b_id,0);
                }
            }
        }
        
        win_otaset_load_ota_param_display();
       
        break;
    case EVN_POST_DRAW:
        break;
    case EVN_PRE_CLOSE:
        /* Make OSD not flickering */
        *((UINT32*)param2) &= ~C_CLOSE_CLRBACK_FLG;

        win_otaset_get_ota_param_display();
        break;
    case EVN_POST_CLOSE:
        break;
    case EVN_MSG_GOT:
        break;
    case EVN_KEY_GOT:
        unact = (VACTION)(param1>>16);

        if(unact == VACT_ENTER) 
        {
            libc_printf("enter\n");
            win_otaset_get_ota_param_display();
        }
    default:
        break;
    }

    return ret;

}

void win_otaset_load_ota_param_display()
{
    EDIT_FIELD *edf=NULL;
    MULTISEL *msel=NULL;
    BOOL func_flag=FALSE;
    char str[10];

    ird_spi_dmd_delivery_t *nvram_info= NULL;
    ird_spi_dmd_satellite_desc_t * sat_info = NULL;

    nvram_info = (ird_spi_dmd_delivery_t *)g_private;
    sat_info = (ird_spi_dmd_satellite_desc_t *) & (nvram_info->delivery.satellite);
        
    ota_lnb_freq = (sat_info->band.lo/1000);

    if(DMD_DISEQC_PORTA == sat_info->diseqc_port)
    {
        ota_diseqc_idx = 1;
    }
    else if(DMD_DISEQC_PORTB == sat_info->diseqc_port)
    {
        ota_diseqc_idx = 2;
    }
    else if(DMD_DISEQC_PORTC == sat_info->diseqc_port)
    {
        ota_diseqc_idx = 3;
    }
    else if(DMD_DISEQC_PORTD == sat_info->diseqc_port)
    {
        ota_diseqc_idx = 4;
    }
    else
    {//none
        ota_diseqc_idx = 0;
    }

    if(DMD_LNB_TONE_22KHZ == sat_info->lnb_tone_state)
    {
        ota_22k_idx = 1;
    }
    else
    {//off
        ota_22k_idx = 0;
    }
    
    ota_freq = (sat_info->frequency/1000);

    if(DMD_PLR_HORIZONTAL == sat_info->polarization)
    {
        ota_pol_idx = 0;
    }
    else if(DMD_PLR_VERTICAL == sat_info->polarization)
    {
        ota_pol_idx = 1;
    }
    else if(DMD_PLR_CIRCULAR_LEFT == sat_info->polarization)
    {
        ota_pol_idx = 3;
    }
    else if(DMD_PLR_CIRCULAR_RIGHT == sat_info->polarization)
    {
        ota_pol_idx = 4;
    }
    else
    {//none
        ota_pol_idx = 2;
    }

    ota_symb = sat_info->symbol_rate;

    if(DMD_FEC_1_2 == sat_info->fec_rate)
    {
        ota_fec_idx = 0;
    }
    else if(DMD_FEC_2_3 == sat_info->fec_rate)
    {
        ota_fec_idx = 1;
    }
    else if(DMD_FEC_3_4 == sat_info->fec_rate)
    {
        ota_fec_idx = 2;
    }
    else if(DMD_FEC_4_5 == sat_info->fec_rate)
    {
        ota_fec_idx = 3;
    }
    else if(DMD_FEC_5_6 == sat_info->fec_rate)
    {
        ota_fec_idx = 4;
    }
    else if(DMD_FEC_6_7 == sat_info->fec_rate)
    {
        ota_fec_idx = 5;
    }
    else if(DMD_FEC_7_8 == sat_info->fec_rate)
    {
        ota_fec_idx = 6;
    }
    else if(DMD_FEC_8_9 == sat_info->fec_rate)
    {
        ota_fec_idx = 7;
    }
    else if(DMD_FEC_3_5 == sat_info->fec_rate)
    {
        ota_fec_idx = 8;
    }
    else if(DMD_FEC_9_10 == sat_info->fec_rate)
    {
        ota_fec_idx = 9;
    }
    else
    {// 1 /2        
        ota_fec_idx = 0;
    }

    ota_pid = dvbssuParameters.pid;
    
	edf = &wota_num0;
    func_flag=osd_set_edit_field_content(edf, STRING_NUMBER, ota_lnb_freq);

    msel = &wota_num1;
    func_flag=osd_set_multisel_sel(msel, ota_diseqc_idx);
    
    msel = &wota_num2;
    func_flag=osd_set_multisel_sel(msel, ota_22k_idx);

    edf = &wota_num3;
    func_flag=osd_set_edit_field_content(edf, STRING_NUMBER, ota_freq);

    msel = &wota_num4;
    func_flag=osd_set_multisel_sel(msel, ota_pol_idx);
    
    edf = &wota_num5;
    func_flag=osd_set_edit_field_content(edf, STRING_NUMBER, ota_symb);

    msel = &wota_num6;
    osd_set_multisel_sel(msel, ota_fec_idx);

    MEMSET(str,0,sizeof(str));
    snprintf(str, 10, "%x", ota_pid);
    
    edf = &wota_num7;
    func_flag=osd_set_edit_field_content(edf, STRING_ANSI, (UINT32)str);
		 
}

lc_result download_service_nvram_parametor_update(lc_bool is_check_valid)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_buffer_st pPrivateData = {0};
    ird_spi_dmd_delivery_t *nvram_info = NULL;
    ird_spi_dmd_satellite_desc_t * sat_info = NULL;
    
    //memcpy(g_private, private, PRIVATE_DATA_MAX_LEN);
    nvram_info = (ird_spi_dmd_delivery_t *)g_private;
    sat_info = (ird_spi_dmd_satellite_desc_t *) & (nvram_info->delivery.satellite);

    sat_info->band.lo = ota_lnb_freq * 1000;

    if(0 == ota_diseqc_idx)
    {
        sat_info->diseqc_port = DMD_DISEQC_DEFAULT;
    }
    else if(1 == ota_diseqc_idx)
    {
        sat_info->diseqc_port = DMD_DISEQC_PORTA;
    }
    else if(2 == ota_diseqc_idx)
    {
        sat_info->diseqc_port = DMD_DISEQC_PORTB;
    }
    else if(3 == ota_diseqc_idx)
    {
        sat_info->diseqc_port = DMD_DISEQC_PORTC;
    }
    else if(4 == ota_diseqc_idx)
    {
        sat_info->diseqc_port = DMD_DISEQC_PORTD;
    }
    else
    {
        sat_info->diseqc_port = DMD_DISEQC_DEFAULT;
    }

    if(ota_22k_idx == 1)
    {
        sat_info->lnb_tone_state =   DMD_LNB_TONE_22KHZ;
    }
    else
    {
        sat_info->lnb_tone_state =   DMD_LNB_TONE_OFF;
    }

    sat_info->frequency = ota_freq* 1000;

    if(0 == ota_pol_idx)
    {
        sat_info->polarization = DMD_PLR_HORIZONTAL;
    }
    else if(1 == ota_pol_idx)
    {
        sat_info->polarization = DMD_PLR_VERTICAL;
    }
    else if(3 == ota_pol_idx)
    {
        sat_info->polarization = DMD_PLR_CIRCULAR_LEFT;
    }
    else if(4 == ota_pol_idx)
    {
        sat_info->polarization = DMD_PLR_CIRCULAR_RIGHT;
    }
    else
    {
        sat_info->polarization = DMD_PLR_NONE;
    }

    sat_info->symbol_rate = ota_symb;

    if(ota_fec_idx == 0)
    {
        sat_info->fec_rate = DMD_FEC_1_2;
    }
    else if(ota_fec_idx == 1)
    {
        sat_info->fec_rate = DMD_FEC_2_3;
    }
    else if(ota_fec_idx == 2)
    {
        sat_info->fec_rate = DMD_FEC_3_4;
    }
    else if(ota_fec_idx == 3)
    {
        sat_info->fec_rate = DMD_FEC_4_5;
    }
    else if(ota_fec_idx == 4)
    {
        sat_info->fec_rate = DMD_FEC_5_6;
    }
    else if(ota_fec_idx == 5)
    {
        sat_info->fec_rate = DMD_FEC_6_7;
    }       
    else if(ota_fec_idx == 6)
    {
        sat_info->fec_rate = DMD_FEC_7_8;
    }        
    else if(ota_fec_idx == 7)
    {
        sat_info->fec_rate = DMD_FEC_8_9;
    }       
    else if(ota_fec_idx == 8)
    {
        sat_info->fec_rate = DMD_FEC_3_5;
    }       
    else if(ota_fec_idx == 9)
    {
        sat_info->fec_rate = DMD_FEC_9_10;
    }        
    else
    {
        sat_info->fec_rate = DMD_FEC_1_2;
    }

    dvbssuParameters.pid  = ota_pid;
    
    if (sat_info->frequency > 10 * 1000 * 1000) 
    { // > 10GHz is Ku band
        sat_info->band.downlink = (sat_info->frequency > 11700 * 1000)
            ? DMD_DOWNLINK_Ku_HIGH : DMD_DOWNLINK_Ku_LOW;
    } else if (sat_info->frequency < sat_info->band.lo){
        sat_info->band.downlink = DMD_DOWNLINK_C;
    }

    pPrivateData.bytes = g_private;
    pPrivateData.length = PRIVATE_DATA_MAX_LEN;
    lc_ret =  LoaderCoreAPI_WriteDVBSSUParameters(&dvbssuParameters, &pPrivateData);

    if(LC_SUCCESS == lc_ret)
    {
        libc_printf("LoaderCoreAPI_WriteDVBSSUParameters success\n");
    }
    else
    {
        libc_printf("LoaderCoreAPI_WriteDVBSSUParameters fail\n");
    }

    return lc_ret;
}

INT32 win_otaset_get_ota_param_display()
{
    EDIT_FIELD *edf=NULL;
    MULTISEL *msel=NULL;
    UINT32 val=0;
    INT32 ret = 0;
    BOOL func_flag=FALSE;
    UINT16 *pstring = NULL;
    UINT8 need_save = 0;

    UINT32 cur_ota_lnb_freq=DEFAULT_LNB_FREQ;
    UINT16 cur_ota_diseqc_idx=0;
    UINT16 cur_ota_22k_idx=0;
    UINT32 cur_ota_freq=DEFAULT_TUN_FREQ;
    UINT16 cur_ota_pol_idx=0;
    UINT32 cur_ota_symb=DEFAULT_SYM;
    UINT16 cur_ota_fec_idx=0;
    UINT16 cur_ota_pid=DEFAULT_OTA_PID;
    lc_result lc_ret = LC_FAILURE;

    lc_loader_pt_st stLdrPt;
    lc_dvbssu_dl_info_st DvbSsuParameters;
    lc_uchar privateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH];

	if(FALSE == func_flag)
	{
		;
	}

    edf = &wota_num0;
    osd_get_edit_field_int_value(edf, &cur_ota_lnb_freq);
    if(cur_ota_lnb_freq!=ota_lnb_freq)
    {
        need_save = 1;
        ota_lnb_freq = cur_ota_lnb_freq;
    }
    libc_printf("ota_lnb_freq %d ", ota_lnb_freq);

    msel = &wota_num1;
    cur_ota_diseqc_idx=osd_get_multisel_sel(msel);
    if(cur_ota_diseqc_idx!=ota_diseqc_idx)
    {
        need_save = 1;
        ota_diseqc_idx = cur_ota_diseqc_idx;
    }
    libc_printf("ota_diseqc_idx %d ", ota_diseqc_idx);
    
    msel = &wota_num2;
    cur_ota_22k_idx=osd_get_multisel_sel(msel);
    if(cur_ota_22k_idx!=ota_22k_idx)
    {
        need_save = 1;
        ota_22k_idx = cur_ota_22k_idx;
    }
    libc_printf("ota_22k_idx %d ", ota_22k_idx);

    edf = &wota_num3;
    osd_get_edit_field_int_value(edf, &cur_ota_freq);
    if(cur_ota_freq!=ota_freq)
    {
        need_save = 1;
        ota_freq = cur_ota_freq;
    }
    libc_printf("ota_freq %d ", ota_freq);

    msel = &wota_num4;
    cur_ota_pol_idx=osd_get_multisel_sel(msel);
    if(cur_ota_pol_idx!=ota_pol_idx)
    {
        need_save = 1;
        ota_pol_idx = cur_ota_pol_idx;
    }
    libc_printf("ota_pol_idx %d ", ota_pol_idx);
    
    edf = &wota_num5;
    func_flag=osd_get_edit_field_int_value(edf, &cur_ota_symb);
    if(cur_ota_symb!=ota_symb)
    {
        need_save = 1;
        ota_symb = cur_ota_symb;
    }
    libc_printf("ota_symb %d ", ota_symb);
    
    msel = &wota_num6;
    cur_ota_fec_idx = osd_get_multisel_sel(msel);
    if(cur_ota_fec_idx!=ota_fec_idx)
    {
        need_save = 1;
        ota_fec_idx = cur_ota_fec_idx;
    }
    libc_printf("ota_fec_idx %d ", ota_fec_idx);

    edf = &wota_num7;
    pstring = (UINT16*)osd_get_edit_field_content(edf);
    cur_ota_pid = com_uni_str2hex(pstring);
    if(cur_ota_pid!=ota_pid)
    {
        need_save = 1;
        ota_pid = cur_ota_pid;
    }
    libc_printf("ota_pid 0x%x\n ", ota_pid);

    if(need_save)
    {
        libc_printf("do save parameter!\n");

        lc_ret = download_service_nvram_parametor_update(LC_FALSE);
        if(LC_SUCCESS == lc_ret)
        {
            libc_printf("save param OK!\n");
		    /* Get and check DVB-SSU download parameters from Loader Partition. */

		      lc_ret = LC_ReadLoaderPartition(&stLdrPt); 	 

              memcpy(&DvbSsuParameters, &stLdrPt.sharedMemory.otaDownloadPara.dvbssuInfo, sizeof(lc_dvbssu_dl_info_st));
              memcpy(privateInfo, stLdrPt.sharedMemory.otaDownloadPara.privateInfo, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
    
				if (LC_SUCCESS == lc_ret)
				{
					lc_ret = LC_VerifyDVBSSUParameters(&DvbSsuParameters);
					if( LC_SUCCESS != lc_ret ) /* both of them are corrupted. */
					{
						libc_printf("Verify param fail!\n");
					}
					else
					{
					  	LoaderCore_dvbs_connect(privateInfo,DvbSsuParameters.pid);
					}
				}

			}
			else
			{
				libc_printf("save param fail!\n");
			}
		}
		return ret;
	}

