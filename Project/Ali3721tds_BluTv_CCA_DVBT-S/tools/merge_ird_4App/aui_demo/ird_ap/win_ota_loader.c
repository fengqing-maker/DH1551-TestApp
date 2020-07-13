/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_sleeptimer.c
*
*    Description: sleep timer menu(press botton "SLEEP").
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/

#include "osdobjs_def.h"
#include "osd_config.h"
#include "win_com.h"

//for osd init
#include <hld/dis/vpo.h>
#include "osd_rsc.h"
#include <aui_os.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <aui_nim.h>
#include <aui_tsi.h>

#include "win_ota_loader.h"
#include "ali_dvt_internel.h"

#include "./LoaderCore/inc/spi/LoaderCoreSPI.h"
/*******************************************************************************
*   WINDOW's objects declaration
*******************************************************************************/
static int g_ui_update_begin_time = 0;

CONTAINER  gwin_ota_loader;
TEXT_FIELD loader_txt_title;
TEXT_FIELD loader_txt_title1;

TEXT_FIELD loader_txt_title2;
TEXT_FIELD loader_txt_title21;
TEXT_FIELD loader_txt_title22;
TEXT_FIELD loader_txt_title23;

TEXT_FIELD loader_txt_title3;
TEXT_FIELD loader_txt_title31;
TEXT_FIELD loader_txt_title32;
TEXT_FIELD loader_txt_title33;


TEXT_FIELD loader_txt_title4;
TEXT_FIELD loader_txt_title41;
TEXT_FIELD loader_txt_title42;
TEXT_FIELD loader_txt_title43;


TEXT_FIELD loader_txt_title5;
TEXT_FIELD loader_txt_title6;
TEXT_FIELD loader_txt_title7;

TEXT_FIELD loader_txt_title8;
TEXT_FIELD loader_txt_title81;
TEXT_FIELD loader_txt_title82;
TEXT_FIELD loader_txt_title83;

TEXT_FIELD loader_txt_title9;
PROGRESS_BAR loader_bar;

UINT16 display_string[50][64];      //fixed for case 23 and 24

#define WIN_SH_IDX      WSTL_POP_WIN_01_8BIT

#define TITLE_SH_IDX    WSTL_POP_TEXT_8BIT
#define SET_SH_IDX      WSTL_TEXT_04_8BIT


#define W_W     OSD_MAX_WIDTH  
#define W_H     OSD_MAX_HEIGHT 
#define WIN_W     OSD_MAX_WIDTH  
#define WIN_H     OSD_MAX_HEIGHT 

#define W_L 	((OSD_MAX_WIDTH - W_W) / 2)
#define W_T		((OSD_MAX_HEIGHT - W_H) / 2)
#define WIN_L 	((OSD_MAX_WIDTH - W_W) / 2)


#define TITLE_L     (W_L + 10) 
#define TITLE_T     (W_T + 10)

#define TITLE_W     ((W_W-20)/4)
#define TITLE_H     ((W_H-20)/12)     


#define SET_L       (W_L+100)   //160
#define SET_T      70 //590

#define SET_W       200
#define SET_H       40


#define B_BG_SH_IDX         WSTL_BARBG_01_8BIT
#define B_MID_SH_IDX        WSTL_NOSHOW_IDX
#define B_SH_IDX            WSTL_BAR_01_8BIT//WSTL_BAR_01_HD

#define R_L_OFF   0 //100
#define R_T_OFF   14
#define R_R_OFF   4
#define R_L (W_L + R_L_OFF+100)
#define R_T (W_T)  //+10)
#define R_W (W_W - 110 - R_R_OFF)
#define R_H W_H
#define RCT_W       R_W
#define RCT_H       (W_H - R_T_OFF*2)


#define LDEF_PROGRESS_BAR(root,var_bar,nxt_obj,l,t,w,h,style,rl,rt,rw,rh)    \
    DEF_PROGRESSBAR(var_bar, &root, nxt_obj, C_ATTR_ACTIVE, 0, \
        0, 0, 0, 0, 0, l, t, w, h, \
    B_BG_SH_IDX, B_BG_SH_IDX, \
    B_BG_SH_IDX, B_BG_SH_IDX,\
        NULL, NULL, style, 0, 0, \
    B_MID_SH_IDX, B_SH_IDX, \
        rl,rt , rw, rh, 1, 100, 100, 1)

#define LDEF_SET(root,var_txt,nxt_obj,l,t,w,h,id,str)     \
    DEF_TEXTFIELD(var_txt,&root,nxt_obj,C_ATTR_ACTIVE,0, \
    id,id,id,id,id, l,t,w,h, SET_SH_IDX,SET_SH_IDX,SET_SH_IDX,SET_SH_IDX,   \
    NULL,NULL,  \
    C_ALIGN_CENTER | C_ALIGN_VCENTER, 0,0,0,str)
    
#define LDEF_WIN(var_con,nxt_obj,l,t,w,h,focus_id)     \
    DEF_CONTAINER(var_con,NULL,NULL,C_ATTR_ACTIVE,0, \
    0,0,0,0,0, l,t,w,h, WIN_SH_IDX/*WIN_SH_IDX*/,WIN_SH_IDX,WIN_SH_IDX,WIN_SH_IDX,   \
    NULL,NULL,  \
    nxt_obj, focus_id,0)

 LDEF_SET(gwin_ota_loader,loader_txt_title,&loader_txt_title1,\
	 TITLE_L, TITLE_T, W_W-20, TITLE_H*2,1,display_string[0])

 LDEF_SET(gwin_ota_loader,loader_txt_title1,&loader_txt_title2,\
    TITLE_L, TITLE_T+TITLE_H*2, W_W-20, TITLE_H,1,display_string[1])
    
 LDEF_SET(gwin_ota_loader,loader_txt_title2,&loader_txt_title21,\
	 TITLE_L, TITLE_T+TITLE_H*3, TITLE_W, TITLE_H,1,display_string[2])
	 
 LDEF_SET(gwin_ota_loader,loader_txt_title21,&loader_txt_title22,\
	 TITLE_L+TITLE_W*1, TITLE_T+TITLE_H*3, TITLE_W, TITLE_H,1,display_string[3])
	 
 LDEF_SET(gwin_ota_loader,loader_txt_title22,&loader_txt_title23,\
	 TITLE_L+TITLE_W*2, TITLE_T+TITLE_H*3, TITLE_W, TITLE_H,1,display_string[4])
	 
 LDEF_SET(gwin_ota_loader,loader_txt_title23,&loader_txt_title3,\
	 TITLE_L+TITLE_W*3, TITLE_T+TITLE_H*3, TITLE_W, TITLE_H,1,display_string[5])
	 
 LDEF_SET(gwin_ota_loader,loader_txt_title3,&loader_txt_title31,\
	  TITLE_L, TITLE_T+TITLE_H*4, TITLE_W, TITLE_H,1,display_string[6])
	  
 LDEF_SET(gwin_ota_loader,loader_txt_title31,&loader_txt_title32,\
	  TITLE_L+TITLE_W*1, TITLE_T+TITLE_H*4, TITLE_W, TITLE_H,1,display_string[7])
	  
 LDEF_SET(gwin_ota_loader,loader_txt_title32,&loader_txt_title33,\
	   TITLE_L+TITLE_W*2, TITLE_T+TITLE_H*4, TITLE_W, TITLE_H,1,display_string[8])
	   
 LDEF_SET(gwin_ota_loader,loader_txt_title33,&loader_txt_title4,\
		TITLE_L+TITLE_W*3, TITLE_T+TITLE_H*4, TITLE_W, TITLE_H,1,display_string[9])
		
 LDEF_SET(gwin_ota_loader,loader_txt_title4,&loader_txt_title41,\
	  TITLE_L, TITLE_T+TITLE_H*5, TITLE_W, TITLE_H,1,display_string[10])
	  
 LDEF_SET(gwin_ota_loader,loader_txt_title41,&loader_txt_title42,\
	  TITLE_L+TITLE_W*1, TITLE_T+TITLE_H*5, TITLE_W, TITLE_H,1,display_string[11])

 LDEF_SET(gwin_ota_loader,loader_txt_title42,&loader_txt_title43,\
	   TITLE_L+TITLE_W*2, TITLE_T+TITLE_H*5, TITLE_W, TITLE_H,1,display_string[12])
	   
 LDEF_SET(gwin_ota_loader,loader_txt_title43,&loader_txt_title5,\
	   TITLE_L+TITLE_W*3, TITLE_T+TITLE_H*5, TITLE_W, TITLE_H,1,display_string[13])	


 LDEF_SET(gwin_ota_loader,loader_txt_title5,&loader_txt_title6,\
	  TITLE_L, TITLE_T+TITLE_H*6, W_W-20, TITLE_H,1,display_string[14]) 

 LDEF_SET(gwin_ota_loader,loader_txt_title6,&loader_bar,\
	   TITLE_L, TITLE_T+TITLE_H*7, W_W-20, TITLE_H,1,display_string[15])

 LDEF_PROGRESS_BAR(gwin_ota_loader,loader_bar,&loader_txt_title8,TITLE_L+40/*TITLE_L+40*/,TITLE_T+TITLE_H*8, W_W-80-20/*TITLE_L-80*/, TITLE_H,\
				  PROGRESSBAR_HORI_NORMAL | PBAR_STYLE_RECT_STYLE,2,\
				 6,W_W-20-4,15)

 LDEF_SET(gwin_ota_loader,loader_txt_title8,&loader_txt_title81,\
	   TITLE_L, TITLE_T+TITLE_H*9, TITLE_W, TITLE_H,1,display_string[16])

 LDEF_SET(gwin_ota_loader,loader_txt_title81,&loader_txt_title82,\
	   TITLE_L+TITLE_W*1-40, TITLE_T+TITLE_H*9, TITLE_W+40, TITLE_H,1,display_string[17])    
	   
 LDEF_SET(gwin_ota_loader,loader_txt_title82,&loader_txt_title83,\
		TITLE_L+TITLE_W*2, TITLE_T+TITLE_H*9, TITLE_W, TITLE_H,1,display_string[18])

 LDEF_SET(gwin_ota_loader,loader_txt_title83,&loader_txt_title9,\
		TITLE_L+TITLE_W*3, TITLE_T+TITLE_H*9, TITLE_W, TITLE_H,1,display_string[19])
		
 LDEF_SET(gwin_ota_loader,loader_txt_title9,NULL,\
	   TITLE_L, TITLE_T+TITLE_H*10, W_W-20, TITLE_H*2,1,display_string[20])

 LDEF_WIN(gwin_ota_loader,&loader_txt_title,\
	W_L, W_T, WIN_W, WIN_H,1)


void win_ota_loader(void)
{
		osd_set_text_field_content(&loader_txt_title, STRING_ANSI, (UINT32)"Please wait download in progress...");
		osd_set_text_field_content(&loader_txt_title1,STRING_ANSI, (UINT32)"Loader data");
		osd_set_text_field_content(&loader_txt_title2,STRING_ANSI, (UINT32)"MAN ID:");
		osd_set_text_field_content(&loader_txt_title21,STRING_ANSI, (UINT32)"XXXX");
		osd_set_text_field_content(&loader_txt_title22,STRING_ANSI, (UINT32)"DSN:");
		osd_set_text_field_content(&loader_txt_title23,STRING_ANSI, (UINT32)"XXXX");
		osd_set_text_field_content(&loader_txt_title3,STRING_ANSI, (UINT32)"HW VER:"); 
		osd_set_text_field_content(&loader_txt_title31,STRING_ANSI, (UINT32)"XXXX");
		osd_set_text_field_content(&loader_txt_title32,STRING_ANSI, (UINT32)"Variant/sub");
		osd_set_text_field_content(&loader_txt_title33,STRING_ANSI, (UINT32)"XXXX");
		osd_set_text_field_content(&loader_txt_title4,STRING_ANSI, (UINT32)"Check ALG:"); 
		osd_set_text_field_content(&loader_txt_title41,STRING_ANSI, (UINT32)"XXXX");
        osd_set_text_field_content(&loader_txt_title42,STRING_ANSI, (UINT32)"Loader ver:");
		osd_set_text_field_content(&loader_txt_title43,STRING_ANSI, (UINT32)"XXXX");
		osd_set_text_field_content(&loader_txt_title5,STRING_ANSI, (UINT32)"Download progress");
		osd_set_text_field_content(&loader_txt_title6,STRING_ANSI, (UINT32)"Preparing to downloader");
        osd_set_progress_bar_value(&loader_bar, 0);
		osd_set_text_field_content(&loader_txt_title8, STRING_ANSI, (UINT32)"ERROR:");
        osd_set_text_field_content(&loader_txt_title81,STRING_ANSI, (UINT32)"0XFFFF"); 
		osd_set_text_field_content(&loader_txt_title82,STRING_ANSI, (UINT32)"Time:"); 
        osd_set_text_field_content(&loader_txt_title83,STRING_ANSI, (UINT32)"0 Second");
		osd_set_text_field_content(&loader_txt_title9,STRING_ANSI, (UINT32)"Please wait and keep power on!");
		osd_draw_object((POBJECT_HEAD)&gwin_ota_loader,C_UPDATE_ALL);
	
}

AUI_RTN_CODE ui_str_msgq_snd(aui_hdl msgq_hld, const char *str_arr[], unsigned long arr_size, unsigned long ul_time_out)
{
	int i,j;
	AUI_RTN_CODE ret;
	char *pst_msg = NULL;
	char *tmp_pmsg = NULL;
	int byte_cnt = 0;
	aui_attr_msgq msgq_attr;
	int limit_len;
	const char **snd_arr = str_arr;
	
	if((NULL == msgq_hld) || (NULL == snd_arr))
	{
		return AUI_RTN_FAIL;
	}

	ret = aui_os_msgq_attr_get(msgq_hld, &msgq_attr);
	if(AUI_RTN_SUCCESS == ret)
	{
		pst_msg = malloc(msgq_attr.ul_msg_size_max);
		if(NULL != pst_msg)
		{
			memset(pst_msg, 0x00, msgq_attr.ul_msg_size_max);
		}
		else
		{
			return AUI_RTN_FAIL;
		}
	}
	else
	{
		return AUI_RTN_FAIL;
	}
	limit_len = msgq_attr.ul_msg_size_max;
	tmp_pmsg = pst_msg; 
	byte_cnt = 0;
	for(i = 0; (i < arr_size) && (limit_len > 0); i++)
	{
		/*copy the snd_arr pointer to serial sequence memory stream*/
		if(NULL != snd_arr[i])
		{
			/*have content to be refresh*/
			memcpy(tmp_pmsg, snd_arr[i], ali_strlen(snd_arr[i]));
			tmp_pmsg += strlen(snd_arr[i]);
			*tmp_pmsg = '\0';
			tmp_pmsg++;
			byte_cnt += (strlen(snd_arr[i]) + 1);
			limit_len -= (strlen(snd_arr[i]) + 1);
		}
		else
		{
			/*no need to update, only fufill '\0'*/
			*tmp_pmsg = '\0';
			tmp_pmsg++;
			byte_cnt++;
			limit_len--;
		}
	}
	//libc_printf("before send a msg\n");
	ret = aui_os_msgq_snd(msgq_hld, pst_msg, byte_cnt, ul_time_out);
	free(pst_msg);
	pst_msg = NULL;
	tmp_pmsg = NULL;
	return ret;
}
AUI_RTN_CODE ui_str_msgq_rcv(aui_hdl p_hdl_msgq, const char *str_arr[], unsigned long arr_size,
							unsigned long* const pul_actual_size, unsigned long ul_time_out)
{
	int i=0;
    int j=0;
	AUI_RTN_CODE ret =0;
	void *pst_msg = NULL;
	void *tmp_pmsg = NULL;
	int byte_cnt = 0;
	aui_attr_msgq msgq_attr={0};
	int limit_len=0;
	const char **rcv_arr = str_arr;

	if((NULL == p_hdl_msgq) || (NULL == rcv_arr))
	{
		return AUI_RTN_FAIL;
	}
	ret = aui_os_msgq_attr_get(p_hdl_msgq, &msgq_attr);
	if(AUI_RTN_SUCCESS == ret)
	{
		pst_msg = malloc(msgq_attr.ul_msg_size_max);
		if(NULL != pst_msg)
		{
			memset(pst_msg, 0x00, msgq_attr.ul_msg_size_max);
		}
		else
		{
			return AUI_RTN_FAIL;
		}
	}
	else
	{
		return AUI_RTN_FAIL;
	}
	
	ret = aui_os_msgq_rcv(p_hdl_msgq, pst_msg, msgq_attr.ul_msg_size_max, &byte_cnt, ul_time_out);
	if(AUI_RTN_SUCCESS == ret)
	{
		limit_len = byte_cnt;
		tmp_pmsg = pst_msg; 
		for(i = 0; (i < arr_size) && (limit_len > 0); i++)
		{
			/*copy sequence string to string arr*/
			if(0 != strlen(tmp_pmsg))
			{
				rcv_arr[i] = malloc(strlen(tmp_pmsg) + 1);
				if(NULL != rcv_arr[i])
				{
					/*have content to be refresh*/
					memset(rcv_arr[i], 0x00, strlen(tmp_pmsg) + 1);
					memcpy(rcv_arr[i], tmp_pmsg, strlen(tmp_pmsg) + 1);
					tmp_pmsg += strlen(rcv_arr[i]) + 1;
					limit_len -= (strlen(rcv_arr[i]) + 1);
				}
				else
				{
					libc_printf("no mem to malloc! \n");
					goto do_error;
				}
			}
			else
			{
				rcv_arr[i] = NULL;
				tmp_pmsg++;
			}
		}	
	}
	else
	{
		for(i = 0; i < arr_size; i++)
		{
			rcv_arr[i] = NULL;
		}
	}	
	if(NULL != pul_actual_size)
	{
		*pul_actual_size = byte_cnt;
	}
    if(NULL != pst_msg)
	{
        free(pst_msg);
    	pst_msg = NULL;
    }
	return ret;
do_error:
    if(NULL != pst_msg)
	{
        free(pst_msg);
    	pst_msg = NULL;
    }
	for(i = 0; i < arr_size; i++)
	{
		if(NULL != rcv_arr[i])
		{
			free(rcv_arr[i]);
			rcv_arr[i] = NULL;
		}
	}
	return AUI_RTN_FAIL; 

}
static INT16 str_convert_bar(const char *str)
{
	if(NULL != str)
	{
		if(0 == strcmp(str, "0"))
		{
			return 0;
		}

		else if(0 == strcmp(str, "10"))
		{
			return 10;
		}

		else if(0 == strcmp(str, "20"))
		{
			return 20;
		}
		else if(0 == strcmp(str, "30"))
		{
			return 30;
		}

		else if(0 == strcmp(str, "40"))
		{
			return 40;
		}
		
		else if(0 == strcmp(str, "50"))
		{
			return 50;
		}

		else if(0 == strcmp(str, "60"))
		{
			return 60;
		}

		else if(0 == strcmp(str, "70"))
		{
			return 70;
		}
		else if(0 == strcmp(str, "80"))
		{
			return 80;
		}
		else if(0 == strcmp(str, "90"))
		{
			return 90;
		}
		else if(0 == strcmp(str, "100"))
		{
			return 100;
		}

	}
	return 0;
}

AUI_RTN_CODE ui_fresh_func(void *pv_para1,void *pv_para2)
{
	static int i=0;
	aui_hdl hdl_tmp=NULL;
	char *vs_str = NULL;
	char *tmp_str = NULL;
	const char * load_msg[LOADER_UI_MAX_WIN_UI_MSGQ_LEN];
	unsigned long byte_cnt = 0;
	int ret = AUI_RTN_SUCCESS;;
    char *info_0 = NULL;
	struct vpo_device *vpo_dev = NULL;
	
    vpo_dev = (struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0);
    ap_osd_int();
    osd_set_lang_environment(0);
    vpo_ioctl(vpo_dev, VPO_IO_HDMI_OUT_PIC_FMT, (UINT32)(YCBCR_444));
	win_ota_loader();    
	libc_printf("have enter ui fresh func! \n");
	
    g_ui_update_begin_time = osal_get_tick();
	for(i = 0; i < LOADER_UI_MAX_WIN_UI_MSGQ_LEN; i++)
	{
		load_msg[i] = NULL;
	}
	
	while(1)
	{
		ret = ui_str_msgq_rcv(pv_para1, load_msg, LOADER_UI_MAX_WIN_UI_MSGQ_LEN, &byte_cnt, 20);

		info_0 = malloc(MAX_BYTE_OF_STRING);
		if(NULL != info_0)
		{
            snprintf(info_0, MAX_BYTE_OF_STRING, "%d s",(osal_get_tick()-g_ui_update_begin_time)/1000);
            load_msg[LOADER_UI_TIME] =    info_0;
            osd_set_text_field_content(&loader_txt_title83,STRING_ANSI, (UINT32)load_msg[LOADER_UI_TIME]);
        }
		
		if(AUI_RTN_SUCCESS == ret)
		{
			osd_set_text_field_content(&loader_txt_title, STRING_ANSI, (UINT32)"SOFTWARE UPGRADE IN PROGRESS. DO NOT POWER OFF !"); 
			osd_set_text_field_content(&loader_txt_title1,STRING_ANSI, (UINT32)"Loader data");
            //TODO: update stage info
            if(NULL != load_msg[LOADER_UI_STAGE_INFO])
			{	
				 osd_set_text_field_content(&loader_txt_title6, STRING_ANSI, (UINT32)load_msg[LOADER_UI_STAGE_INFO]);
			}
			if(NULL != load_msg[LOADER_UI_MAIN_ID])
			{	
				 osd_set_text_field_content(&loader_txt_title2,STRING_ANSI, (UINT32)"MAN ID:");
				 osd_set_text_field_content(&loader_txt_title21,STRING_ANSI, (UINT32)load_msg[LOADER_UI_MAIN_ID]);
			}
			if(NULL != load_msg[LOADER_UI_DSN])
			{
				 osd_set_text_field_content(&loader_txt_title22,STRING_ANSI, (UINT32)"DSN:");
				 osd_set_text_field_content(&loader_txt_title23,STRING_ANSI, (UINT32)load_msg[LOADER_UI_DSN]);
			}
			if(NULL != load_msg[LOADER_UI_HW_VER])
			{
				 osd_set_text_field_content(&loader_txt_title3,STRING_ANSI, (UINT32)"HW VER:"); 
				 osd_set_text_field_content(&loader_txt_title31,STRING_ANSI, (UINT32)load_msg[LOADER_UI_HW_VER]);
			}
			if((NULL != load_msg[LOADER_UI_VARIANT]) && (NULL != load_msg[LOADER_UI_SUB]))
			{
				osd_set_text_field_content(&loader_txt_title32,STRING_ANSI, (UINT32)"Variant/Sub");
				if(NULL == vs_str)
				{
					vs_str = malloc(strlen(load_msg[LOADER_UI_VARIANT]) + 1 + strlen("/") + 1 + strlen(load_msg[LOADER_UI_SUB]) + 1 + 1);
				}
				if(NULL != vs_str)
				{
		
					memset(vs_str, 0x00, strlen(load_msg[LOADER_UI_VARIANT]) + 1 + strlen("/") + 1 + strlen(load_msg[LOADER_UI_SUB]) + 1 + 1);
					tmp_str = vs_str;
					memcpy(tmp_str, load_msg[LOADER_UI_VARIANT], strlen(load_msg[LOADER_UI_VARIANT]));
					tmp_str += strlen(load_msg[LOADER_UI_VARIANT]);
					memcpy(tmp_str, "/", strlen("/"));
					tmp_str += strlen("/");
					memcpy(tmp_str, load_msg[LOADER_UI_SUB], strlen(load_msg[LOADER_UI_SUB]));
					tmp_str += strlen(load_msg[LOADER_UI_SUB]);
					*tmp_str = '\0';
					osd_set_text_field_content(&loader_txt_title33,STRING_ANSI, (UINT32)vs_str);
				}
			}
			if(NULL != load_msg[LOADER_UI_CHECK_ALG])
			{
				osd_set_text_field_content(&loader_txt_title4,STRING_ANSI, (UINT32)"Check ALG:"); 
				osd_set_text_field_content(&loader_txt_title41,STRING_ANSI, (UINT32)load_msg[LOADER_UI_CHECK_ALG]);
		
			}
			if(NULL != load_msg[LOADER_UI_LOADER_VER])
			{
				osd_set_text_field_content(&loader_txt_title42,STRING_ANSI, (UINT32)"Loader VER:");
				osd_set_text_field_content(&loader_txt_title43,STRING_ANSI, (UINT32)load_msg[LOADER_UI_LOADER_VER]);
			}
			if(NULL != load_msg[LOADER_UI_NR_PROGRESS_BAR])
			{
				osd_set_text_field_content(&loader_txt_title5,STRING_ANSI, (UINT32)"Download progress");
				osd_set_progress_bar_value(&loader_bar, str_convert_bar(load_msg[LOADER_UI_NR_PROGRESS_BAR]));
			}
			
            if(NULL != load_msg[LOADER_UI_ERROR_INFO])
			{
				osd_set_text_field_content(&loader_txt_title9,STRING_ANSI, (UINT32)load_msg[LOADER_UI_ERROR_INFO]);
			}
			if(NULL != load_msg[LOADER_UI_MODULE_INFO])
			{
				osd_set_text_field_content(&loader_txt_title6,STRING_ANSI, (UINT32)load_msg[LOADER_UI_MODULE_INFO]);
			}
			if(NULL != load_msg[LOADER_UI_ERROR_NO])
			{	
				osd_set_text_field_content(&loader_txt_title8, STRING_ANSI, (UINT32)"ERROR:");
				osd_set_text_field_content(&loader_txt_title81,STRING_ANSI, (UINT32)load_msg[LOADER_UI_ERROR_NO]); 
			}
			if(NULL != load_msg[LOADER_UI_TIME])
			{
				osd_set_text_field_content(&loader_txt_title82,STRING_ANSI, (UINT32)"Used Time:"); 
				osd_set_text_field_content(&loader_txt_title83,STRING_ANSI, (UINT32)load_msg[LOADER_UI_TIME]);
			}
			osd_draw_object((POBJECT_HEAD)&gwin_ota_loader,C_UPDATE_ALL);
		}
        else
        {
            	osd_draw_object((POBJECT_HEAD)&gwin_ota_loader,C_UPDATE_ALL);
        }
		osal_task_sleep(LoaderCoreSPI_get_ui_update_rate());
		for(i = 0; i < LOADER_UI_MAX_WIN_UI_MSGQ_LEN; i++)
		{
			if(NULL != load_msg[i])
			{
				free(load_msg[i]);
 
				load_msg[i] = NULL;
			}
		}
	}
	
	if(NULL != vs_str)
	{
		free(vs_str);
		vs_str = NULL;
	}
	return AUI_RTN_SUCCESS;
}

int start_win_ui_dtask(aui_hdl hdl_msgq, aui_attr_msgq *p_msgq_attr)
{
	static int start_flag = 0;
	aui_attr_task attr_task;
	void *p_ui_dtask_hld = NULL;
	AUI_RTN_CODE ret = AUI_RTN_SUCCESS;

	if((NULL == hdl_msgq) || (NULL == p_msgq_attr))
	{
		return AUI_RTN_FAIL;
	}
	if(0 == start_flag)
	{
		strcpy(attr_task.sz_name,"win_ui_taskd");
		attr_task.ul_priority = OSAL_PRI_NORMAL;
		attr_task.p_fun_task_entry = ui_fresh_func;
		attr_task.ul_quantum = 10;
		attr_task.ul_stack_size = 0x4000;
		attr_task.para1 = hdl_msgq;
		ret = aui_os_task_create(&attr_task,&p_ui_dtask_hld);
		libc_printf("have create win ui task! \n");
		if(AUI_RTN_SUCCESS == ret)
		{
			start_flag = 1;
		}
	}
	return AUI_RTN_SUCCESS;
}


static int is_ui_inited = 0;
static aui_hdl g_msgq_hld = NULL;
static int ui_update_begin_time = 0;

#define INFO_BUFFER_LEN              (16)
#define INFO_BUFFER_LONG_LEN         (64)


lc_result send_ui_update_info(int type, int size, void* info_buf)
{
    AUI_RTN_CODE ret = AUI_RTN_SUCCESS;
    lc_result lc_ret = LC_SUCCESS;
    aui_attr_msgq attr_msgq = {0};
    const char * load_msg[LOADER_UI_MAX_WIN_UI_MSGQ_LEN] = {0};
    lc_bbcb_st *bbcb_info = LC_NULL;
    char info_0[INFO_BUFFER_LEN] = {0};
    char info_1[INFO_BUFFER_LEN] = {0};
    char info_2[INFO_BUFFER_LEN] = {0};
    char info_3[INFO_BUFFER_LEN] = {0};
    char info_4[INFO_BUFFER_LEN] = {0};
    char info_long_message[INFO_BUFFER_LONG_LEN] = {0};
    char stage_info_message[INFO_BUFFER_LONG_LEN] = {0};
    lc_uint16 var = 0xffff;
    lc_uint16 sub_var = 0xffff;
    lc_uint16 info_value_3 = 0;
    char long_info_0[INFO_BUFFER_LONG_LEN] = {0};

    lc_uint16 process_data_stage = 0xffff;
    lc_uint16 cur_module = 0xffff;
    lc_uint16 module_num = 0;

    if((UI_INFO_TYPE_TIME != type) && (NULL == info_buf))
    {
        lc_ret = LC_FAILURE;
        libc_printf("%s() Line(%d) input data invalid\n", __FUNCTION__, __LINE__);
        return lc_ret;
    }

    if(0 == is_ui_inited)
    {
        attr_msgq.ul_buf_size = 0x2000;
        attr_msgq.ul_msg_size_max = LOADER_UI_MAX_WIN_UI_MSGQ_LEN * INFO_BUFFER_LONG_LEN;
        ret = aui_os_msgq_create(&attr_msgq, &g_msgq_hld);

        if(0 != ret)
        {
            lc_ret = LC_FAILURE;
            libc_printf("%s() Line(%d) aui_os_msgq_create fail\n", __FUNCTION__, __LINE__);
            return lc_ret;
        }

        ret = start_win_ui_dtask(g_msgq_hld, &attr_msgq);

        if(0 != ret)
        {
            libc_printf("%s() Line(%d) start_win_ui_dtask fail\n", __FUNCTION__, __LINE__);
            lc_ret = LC_FAILURE;

            if(0 != aui_os_msgq_delete(g_msgq_hld))
            {
                libc_printf("%s() Line(%d) aui_os_msgq_delete fail\n", __FUNCTION__, __LINE__);
            }

            return lc_ret;
        }
		
        ui_update_begin_time = osal_get_tick();
        is_ui_inited = 1;
        osal_task_sleep(200);
    }

    /////////
    //Converting data!
    /////////
    switch(type)
    {
        case UI_INFO_TYPE_BBCB_INFO:
        {
            bbcb_info = (lc_bbcb_st *)info_buf;
#ifdef DECIMAL_SUPPORT
            snprintf(info_0, INFO_BUFFER_LEN, "%d", bbcb_info->manufacturer_id);
#else
            snprintf(info_0, INFO_BUFFER_LEN, "0x%02x", bbcb_info->manufacturer_id);
#endif
            load_msg[LOADER_UI_MAIN_ID] =    info_0;

#if 0
#ifdef DECIMAL_SUPPORT
            snprintf(info_1, INFO_BUFFER_LEN, "%d.%d.%d",
                     bbcb_info->OUI[0],
                     bbcb_info->OUI[1],
                     bbcb_info->OUI[2]);
#else
            snprintf(info_1, INFO_BUFFER_LEN, "0x%02x%02x%02x",
                     bbcb_info->OUI[0],
                     bbcb_info->OUI[1],
                     bbcb_info->OUI[2]);
#endif
            load_msg[LOADER_UI_DSN] =         info_1;

#endif			
			
#ifdef DECIMAL_SUPPORT
            snprintf(info_2, INFO_BUFFER_LEN, "%d", bbcb_info->hardware_version);
            load_msg[LOADER_UI_HW_VER] =     info_2;
            snprintf(info_3, INFO_BUFFER_LEN, "%d", bbcb_info->boot_check_algorithm);
            load_msg[LOADER_UI_CHECK_ALG] =  info_3;
            snprintf(info_4, INFO_BUFFER_LEN, "%d.%d.%d", bbcb_info->loader_major_version, bbcb_info->loader_minor_version,bbcb_info->loader_version_buildnumber);
            load_msg[LOADER_UI_LOADER_VER] = info_4;
#else
            snprintf(info_2, INFO_BUFFER_LEN, "0x%02x", bbcb_info->hardware_version);
            load_msg[LOADER_UI_HW_VER] =     info_2;
            snprintf(info_3, INFO_BUFFER_LEN, "0x%02x", bbcb_info->boot_check_algorithm);
            load_msg[LOADER_UI_CHECK_ALG] =  info_3;
            snprintf(info_4, INFO_BUFFER_LEN, "%x.%x.%x", bbcb_info->loader_major_version, bbcb_info->loader_minor_version,bbcb_info->loader_version_buildnumber);
            load_msg[LOADER_UI_LOADER_VER] = info_4;
#endif
            
            break;
        }
        case UI_INFO_TYPE_DSN:
        {
#ifdef DECIMAL_SUPPORT
            snprintf(info_0, INFO_BUFFER_LEN, "%d", *((lc_uint16*)info_buf));
#else
            snprintf(info_0, INFO_BUFFER_LEN, "0x%04x", *((lc_uint16*)info_buf));
#endif
            load_msg[LOADER_UI_DSN] =         info_0;
            break;
        }
        
        case UI_INFO_TYPE_MODULE_INFO:
        {
            process_data_stage = *(lc_uint16 *)info_buf;
            cur_module = *((lc_uint16 *)info_buf + 1);
            module_num = *((lc_uint16 *)info_buf + 2);

            if(UI_MODULE_DATA_DOWNLOAD == process_data_stage)
            {
                snprintf(info_long_message, INFO_BUFFER_LONG_LEN, "Downloading data...M%d of %d", cur_module, module_num);
            }
            else if(UI_MODULE_DATA_CHECK == process_data_stage)
            {
                snprintf(info_long_message, INFO_BUFFER_LONG_LEN, "Checking data...M%d of %d", cur_module, module_num);
            }
            else if(UI_MODULE_DATA_UPDATE == process_data_stage)
            {
                snprintf(info_long_message, INFO_BUFFER_LONG_LEN, "Updating data...M%d of %d", cur_module, module_num);
            }

            load_msg[LOADER_UI_MODULE_INFO] =    info_long_message;
            break;
        }

        case UI_INFO_TYPE_MODULE_FINAL:
        {
            snprintf(info_long_message, INFO_BUFFER_LONG_LEN, "%s", info_buf);
            load_msg[LOADER_UI_MODULE_INFO] =    info_long_message;
            break;
        }

        case UI_INFO_TYPE_ERROR_CODE:
        {
            //Errors are showing like 0X012 but as per document should be 0X12
            if(SPI_DIS_ERR_WITH_MODID == size)
            {
                snprintf(long_info_0, INFO_BUFFER_LONG_LEN, "0x%02x  ModuleId: 0x%02x", *((unsigned int*)info_buf), *((unsigned int *)info_buf + 1));
            }
            else
            {
                snprintf(long_info_0, INFO_BUFFER_LONG_LEN, "0x%02x", *((unsigned int*)info_buf));
            }

            if(0xbe1 == *((unsigned int*)info_buf))
            {
                memset(long_info_0,0,sizeof(long_info_0));
                snprintf(long_info_0, INFO_BUFFER_LONG_LEN, "%s", "0xbE1");  
            }
            else if (0xbbb == *((unsigned int*)info_buf))
            {
                memset(long_info_0,0,sizeof(long_info_0));
                snprintf(long_info_0, INFO_BUFFER_LONG_LEN, "%s", " ");  
            }
            load_msg[LOADER_UI_ERROR_NO] =    long_info_0;
            libc_printf("========>error info:%s\n", long_info_0);
            memset(info_long_message, 0, INFO_BUFFER_LONG_LEN);
            //get_error_message_by_no(*((unsigned int*)info_buf), info_long_message);
            load_msg[LOADER_UI_ERROR_INFO] =    info_long_message;
            //printf("%s, %d: error msg: %s\n", __func__, __LINE__, info_long_message);
            break;
        }

        case UI_INFO_TYPE_PROCESS:
        {
            var = *(lc_uint16 *)info_buf; // var is the percentage of the process bar

            if(var > 100)
            {
                var = 100;
            }

            var = var / 10 * 10;
            snprintf(info_0, INFO_BUFFER_LEN, "%d", var);
            load_msg[LOADER_UI_NR_PROGRESS_BAR] =    info_0;
            break;
        }

        case UI_INFO_TYPE_TIME:
        {
            var = *(lc_uint16 *)info_buf;
            snprintf(info_0, INFO_BUFFER_LEN, " %d s", (osal_get_tick() - ui_update_begin_time) / 1000);
            load_msg[LOADER_UI_TIME] =    info_0;
            break;
        }

        case UI_INFO_TYPE_ERROR_INFO:
        {
            snprintf(info_long_message, INFO_BUFFER_LONG_LEN, "%s", info_buf);
            load_msg[LOADER_UI_ERROR_INFO] =    info_long_message;
            break;
        }

        case UI_INFO_TYPE_VAR:
        {
            var = *(lc_uint16 *)info_buf;
#ifdef DECIMAL_SUPPORT
            snprintf(info_0, INFO_BUFFER_LEN, "%d", (var == 65535)?(-1):var);
#else
            snprintf(info_0, INFO_BUFFER_LEN, "0x%02x", var);
#endif
            load_msg[LOADER_UI_VARIANT] =    info_0;

            sub_var = *((lc_uint16 *)info_buf + 1);
#ifdef DECIMAL_SUPPORT
            snprintf(info_1, INFO_BUFFER_LEN, "%d", (sub_var == 65535)?(-1):sub_var);
#else
            snprintf(info_1, INFO_BUFFER_LEN, "0x%02x", sub_var);
#endif
            load_msg[LOADER_UI_SUB] =    info_1;
            break;
        }
        case UI_INFO_TYPE_STAGE:
        {
            // TODO: update stage info
            snprintf(stage_info_message, INFO_BUFFER_LONG_LEN, "%s", info_buf);
            load_msg[LOADER_UI_STAGE_INFO] =    stage_info_message;
            break;
        }

        default:
        {
            break;
        }
    }

    ret = ui_str_msgq_snd(g_msgq_hld, load_msg, LOADER_UI_MAX_WIN_UI_MSGQ_LEN, 50);
    osal_task_sleep(100);
    return 0;
}


AUI_RTN_CODE LoaderCoreAPI_Start_dtask(void *pv_para1,void *pv_para2)
{
  LoaderCoreAPI_StartBootLoader(pv_para1);
}

extern void LoaderCore_dvbs_connect(char *private_data, int pid);

#include <aui_fs.h>
#include <aui_rtc.h>
#include <errno.h>
#define ENC_IMG_MEMORY_ADDR 0xA3000000
#define CHUNK_HEADER_SIZE 0x80
#define CHUNK_LENGTH    4
#define WRITE_DIR "/mnt/uda1/"
#define WRITE_USB_FILE "/mnt/uda1/app_upg.bin"
static UINT32 data_len =0;

INT32 Is_Need_Write_Enc_Img()
{//0, need write; -1, igmore
    UINT8 *data_addr = NULL;
    UINT32 chunk_id = HL_MODULE_MAINCODE;
    UINT8 header[CHUNK_HEADER_SIZE]={0};
    UINT8 *img_addr = (UINT8 *)ENC_IMG_MEMORY_ADDR;
    INT32 ret = -1;
    
    data_addr = aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1);
	if(LC_FAILURE!=data_addr)
	{
       data_len = aui_flash_fetch_long(data_addr + CHUNK_LENGTH) + 0x10;
       libc_printf("main code addr 0x%x, chunk total len 0x%x\n", data_addr, data_len);
	   ret = ps_data_read_write(READ,data_addr, CHUNK_HEADER_SIZE,header, 0, FALSE);
       if(ret == 0)
       {
           if(MEMCMP(header, img_addr, CHUNK_HEADER_SIZE)==0)
               ret = 0;
           else
           {
               ret = -1;
               #if 0
               ret = 0;
               libc_printf("force set to 0, for test only\n");
               MEMCPY(img_addr, header, CHUNK_HEADER_SIZE);
               img_addr[CHUNK_HEADER_SIZE]=osal_get_tick()%255;
               libc_printf("magic 0x%x\n", img_addr[CHUNK_HEADER_SIZE]);
               MEMCPY(img_addr+data_len-CHUNK_HEADER_SIZE, header, CHUNK_HEADER_SIZE);
               #endif
           }
       }
	}
    libc_printf("need write enc img %d\n", ret);
    return ret;
}

void Ird_Write_Enc_Img_To_Usb()
{
    unsigned int fs_dev = 0;
	unsigned int actual_num =0 ;
    //aui_f_hdl fp = NULL;
    static int wait_times = 0;
    AUI_RTN_CODE fs_ret = AUI_RTN_FAIL;
    UINT8 new_name[]={'E','N','C','_','%','^'};
    aui_hdl rtc_handler;
	aui_clock clock;
    UINT8 file_name[64]={0};
    FILE *file = NULL;
    UINT32 n = 0;

    libc_printf("--enter write to USB ---\n");

    wait_times = 0;
	while((AUI_RTN_SUCCESS == aui_fs_get_alldevid(&fs_dev,1,&actual_num) )&& (0 == fs_dev))
	{
		libc_printf("Warning: filesystem not mounted,waiting@%d!\n", wait_times);
        wait_times += 1;
        if(60 == wait_times)
        {
            libc_printf("not found USB, timeout\n");
            send_ui_update_info(UI_INFO_TYPE_STAGE,0,"not found USB, timeout, pls reboot");
            return;
        }
		AUI_SLEEP(500);
	}
	libc_printf("%s line %d,fs_dev = %d\n",__func__,__LINE__,fs_dev);
    send_ui_update_info(UI_INFO_TYPE_STAGE,0,"USB ready, start dump image..");
/////////////////////////////////////////////////////////////////////////	
    //must init time, or create file will fail
    fs_ret = aui_rtc_init();
	fs_ret = aui_rtc_open(&rtc_handler);
	if (fs_ret != AUI_RTN_SUCCESS) 
    {
		libc_printf("Init RTC time failed.\n");
		fs_ret = -1;
	} 
    else 
    {
		clock.year=  2018;
		clock.month = 1;
		clock.date= 1;
		clock.day= 1;
		clock.hour = 0;
		clock.min = 0;
		clock.sec = 0;
		fs_ret = aui_rtc_set_time(rtc_handler, &clock);
        libc_printf("ret %d, set Current time: %04d-%02d-%02d %02d:%02d:%02d\n",
				fs_ret, clock.year,clock.month, clock.date,
				clock.hour, clock.min, clock.sec);
	}
    //add 'ENC_' flag to main code chunk name for BL decrypt
    MEMCPY((UINT8 *)ENC_IMG_MEMORY_ADDR+0x10, new_name, 6);
    
    libc_printf("%s line %d, test write.\n",__func__,__LINE__);

    sprintf((char *)file_name, WRITE_USB_FILE);
    fs_ret = fs_remove((char *)file_name);
    libc_printf("fs_remove ret %d\n", fs_ret);
    fs_ret = fsync(WRITE_DIR);
    libc_printf("fsync ret %d\n", fs_ret);
    
    sprintf((char *)file_name, WRITE_USB_FILE);
    file = fopen((char *)file_name, "w");
    libc_printf("fopen file w 0x%x\n", file);
    n = fwrite((UINT8 *)ENC_IMG_MEMORY_ADDR, data_len, 1, file);
    libc_printf("fwrite src 0x%x, len 0x%x, ret 0x%x\n", ENC_IMG_MEMORY_ADDR, data_len, n);
    fs_ret = fflush(file);
    libc_printf("fflush ret %d\n", fs_ret);
    fs_ret = fclose(file);
    libc_printf("fclose ret %d\n", fs_ret);
    fs_ret = fsync(WRITE_DIR);
    libc_printf("fsync ret %d\n", fs_ret);
    file = NULL;

    osal_task_sleep(3000);
    send_ui_update_info(UI_INFO_TYPE_STAGE,0,"dump finish, please power off STB");
}

void Ird_Loader_UI_init(void)
{
	INT32 len =0;
    executecode_func pfunc = {0};
    libc_printf("%d %s run!\n", __LINE__, __FUNCTION__);
    get_boot_total_area_len(&len);
    aui_flash_chunk_init(len, 0x800000-len);
	LC_fs_init();
    pfunc.Application = NULL;
    pfunc.Bootloader = NULL;
    pfunc.Strapup = NULL;
    pfunc.Updateinfo = send_ui_update_info;
    LoaderCoreSPI_SetExecuteCodeFunc(&pfunc);

#if 1//check need write encrypted HL image to USB or not
    if(Is_Need_Write_Enc_Img() == 0)
    {
        send_ui_update_info(UI_INFO_TYPE_STAGE,0,"found encrypt image, wait USB to dump");
        Ird_Write_Enc_Img_To_Usb();
        libc_printf("USB dump end\n");
        do
        {
            osal_task_sleep(500);
        }
        while(1);
    }
#endif
    static int start_flag = 0;
	aui_attr_task attr_task;
	void *p_ui_dtask_hld = NULL;
	AUI_RTN_CODE ret = AUI_RTN_SUCCESS;
    strcpy(attr_task.sz_name,"LoaderCoreAPI_dtask");
	attr_task.ul_priority = OSAL_PRI_NORMAL;
	attr_task.p_fun_task_entry = LoaderCoreAPI_Start_dtask;
	attr_task.ul_quantum = 10;
	attr_task.ul_stack_size = 0x4000;
	attr_task.para1 = LoaderCore_dvbs_connect;
	ret = aui_os_task_create(&attr_task,&p_ui_dtask_hld);
	libc_printf("have create LoaderCoreAPI_dtask! \n");
   
}

