/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_sleeptimer.h
*
*    Description: sleep timer menu(press botton "SLEEP").
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/

#ifndef _gwin_ota_loader_H_
#define _gwin_ota_loader_H_


#ifdef __cplusplus
extern "C"
{

#endif
#include <aui_common.h>
#include <aui_os.h>
    
/*please use string array to send me message*/
#define LOADER_UI_MAIN_ID             0
#define LOADER_UI_DSN                 1
#define LOADER_UI_HW_VER              2
#define LOADER_UI_VARIANT             3
#define LOADER_UI_SUB                 4
#define LOADER_UI_CHECK_ALG           5
#define LOADER_UI_LOADER_VER          6 	/*502 stand for 5.0.2*/
#define LOADER_UI_NR_PROGRESS_BAR     7
#define LOADER_UI_ERROR_NO            8 
#define LOADER_UI_TIME                9 
#define LOADER_UI_MODULE_INFO         10      //for the module m1 in 3
#define LOADER_UI_ERROR_INFO          11      // update succuss or fail
#define LOADER_UI_STAGE_INFO          12

#define LOADER_UI_MAX_WIN_UI_MSGQ_LEN 13

#define MAX_BYTE_OF_STRING           (16)

void win_ota_loader(void);
extern AUI_RTN_CODE ui_str_msgq_snd(aui_hdl msgq_hld, const char *str_arr[], unsigned long arr_size, unsigned long ul_time_out);
extern AUI_RTN_CODE ui_str_msgq_rcv(aui_hdl p_hdl_msgq, const char *str_arr[], unsigned long arr_size,
							unsigned long* const pul_actual_size, unsigned long ul_time_out);
extern int start_win_ui_dtask(aui_hdl hdl_msgq, aui_attr_msgq *p_msgq_attr);
//extern lc_result send_ui_update_info(int type, int size, void* info_buf);
extern lc_resultsend_ui_update_info(int type, int size, void* info_buf);
void Ird_Loader_UI_init(void);


#ifdef __cplusplus
}
#endif

#endif 

