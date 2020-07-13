/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_com_popup_inner.h
*
*    Description: The internal common function of popup
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#ifndef _WIN_COM_POPUP_INNER_H_
#define _WIN_COM_POPUP_INNER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <sys_config.h>

#include <basic_types.h>
#include <api/libosd/osd_lib.h>

#include "osd_config.h"
#include "win_com_popup.h"
#include "win_com.h"

#define POPUP_MAX_MSG_LEN   300



#define MAX_LEN_ONE_LINE        500
#define MIN_WIDTH_2BTN          500
#define MIN_WIDHT_1ORNOBTN      400

#define MSG_VOFFSET_NOBTN       60
#define MSG_VOFFSET_WITHBTN     50//40
#define MSG_LOFFSET             40
#define MSG_BUTTON_TOPOFFSET    40
#define MSG_BUTTON_BOTOFFSET    40

#define DEFAULT_FONT_H          36
#define TITLE_H                 36



#define MAX_LEN_CONAX_ONE_LINE      600

#define POPUP_MAX_TIMER_STR_LEN 10


#define W_W         540
#define W_H         360
#define W_L         GET_MID_L(W_W)
#define W_T         GET_MID_T(W_H)

#define W_MSG_L     GET_MID_L(W_MSG_W)
//#ifdef SUPPORT_CAS9

#define W_MSG_T     250


#define W_MSG_W     500
#define W_MSG_H     200

#define W_CHS_L     400
#define W_CHS_T     300
#define W_CHS_W     500
#define W_CHS_H     200

#define MSG_L       (W_L + 20)
#define MSG_T       (W_T + 40)
#define MSG_W       (W_W - 40)
#define MSG_H       80

#define BTM_L       (W_L +  W_W - (BTM_W + BTM_GAP) * 3)
#define BTM_T       (W_T + W_H - BTM_H*2)
#define BTM_W       140
#define BTM_H       38 //40
#define BTM_GAP     10


#define POPUP_YES_ID    1
#define POPUP_NO_ID     2
#define POPUP_CANCEL_ID 3

/////////style
#define POPUPWIN_IDX        WSTL_POP_WIN_01_HD
#define POPUPSH_IDX         WSTL_BUTTON_POP_SH_HD
#define POPUPHL_IDX         WSTL_BUTTON_POP_HL_HD
#define POPUP_TITLE_SH_IDX  WSTL_POP_TXT_SH_HD
#define POPUPSTR_IDX        WSTL_POP_TXT_SH_01_HD

#define POPUPWIN_IDX_SD     WSTL_POP_WIN_01_HD//sharon WSTL_POP_WIN_01_8BIT
#define POPUPSH_IDX_SD       WSTL_BUTTON_POP_SH_8BIT
#define POPUPHL_IDX_SD        WSTL_BUTTON_POP_HL_8BIT
#define POPUP_TITLE_SH_IDX_SD   WSTL_POP_TEXT_8BIT
#define POPUPSTR_IDX_SD         WSTL_POP_TEXT_8BIT

extern MULTI_TEXT  win_popup_msg_mbx;           // popup message box
extern TEXT_CONTENT popup_mtxt_content;         // popup text content
extern UINT16 pp_msg_str[POPUP_MAX_MSG_LEN];    // popup message string buffer
extern const UINT8 win_popup_btm_num[];         // popup btm number
extern win_popup_type_t win_popup_type;         // popup type
extern win_popup_choice_t win_pp_choice;        // popup choice
extern BOOL win_pp_opened;                      // popup window open flag
extern TEXT_FIELD   win_popup_title_txt;        // popup title text field
extern TEXT_FIELD   win_popup_yes;              // popup YES button
extern TEXT_FIELD   win_popup_no;               // popup NO button
extern TEXT_FIELD   win_popup_cancel;           // popup Cancel button

void win_popup_init(void);

#ifdef __cplusplus
}
#endif

#endif
