/*****************************************************************************
 *    Copyright (c) 2013 ALi Corp. All Rights Reserved
 *    This source is confidential and is ALi's proprietary information.
 *    This source is subject to ALi License Agreement, and shall not be
      disclosed to unauthorized individual.
 *    File: control.h
 *
 *    Description: This head file application's control task relate APIs.
 *    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
 *****************************************************************************/

#ifndef _CONTROL_H_
#define _CONTROL_H_
#include <sys_config.h>
#include <basic_types.h>
#include "win_com.h"
#if 0
#include "ctrl_play_channel.h"
#include "ctrl_key_proc.h"
#include "ap_dynamic_pid.h"
#include "ap_ctrl_ci.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define SCART_TV_MODE_LED_DISPLAY
#ifdef _INVW_JUICE
#define DISABLE_ALI_INFORBAR    1
#endif
#define REAL_STANDBY            SYS_FUNC_ON
#define CONTROL_MBF_NAME        "mbcn"
#define CONTROL_MBF_SIZE        300
#define CONTROL_TASK_STACKSIZE  0x4000
#define CONTROL_TASK_QUANTUM    10
#ifdef _BUILD_OTA_E_
#define MAIN_MENU_HANDLE    NULL
#define CHANNEL_BAR_HANDLE  NULL
#else
#define MAIN_MENU_HANDLE    ((POBJECT_HEAD) & g_win_mainmenu)
#ifdef _INVW_JUICE
#define CHANNEL_BAR_HANDLE  ((POBJECT_HEAD) & g_win_inviewinput)
#define INVIEWJUICE_HANDLE  ((POBJECT_HEAD) & g_win_inviewinput)
#else
#define CHANNEL_BAR_HANDLE  ((POBJECT_HEAD) & g_win_progname)
#endif
#endif
#define INVALID_HK          0xFFFFFFFF
#define INVALID_MSG         0x00000000
#define C_POPUP_MSG_PASS_CI 0x00000001

#define HW_DMX_ID0  0
#define HW_DMX_ID1  1
#define SW_DMX_ID   2

#ifndef DEV_DMX_MAX_CNT
#define DEV_DMX_MAX_CNT 3
#endif
#define SET_IRCODE(a)   ((((a) >> 24) << 8) | ((a) & 0xff))

#ifdef _DTGSI_ENABLE_
struct running_data_t
{
    UINT16  service_id;
    UINT8   running_status;
};
struct sdt_running_info_t
{
    UINT8                   sd_count;
    struct running_data_t   running_data[128];
};
#endif
#ifdef _INVW_JUICE
typedef struct
{
    UINT32  type : 4;
    UINT32  state : 4;
    UINT32  count : 8;
    UINT32  ir_code : 16;
} ALI_IR_KEY_INFO;
#else
typedef struct
{
    UINT32  type : 4;
    UINT32  state : 4;
    UINT32  count : 8;
    UINT32  ir_code : 16;
} IR_KEY_INFO;
#endif
struct ir_key_map_t
{
#ifdef _INVW_JUICE
    ALI_IR_KEY_INFO key_info;
#else
    IR_KEY_INFO     key_info;
#endif
    UINT32          ui_vkey;
};
struct channel_info
{
    UINT8   mode;
    UINT8   internal_group_idx;
    P_NODE  p_node;
};
#if (defined(_MHEG5_V20_ENABLE_))
typedef enum
{
    UI_MENU_OPEN    = 0,
    UI_MENU_CLOSE,
    UI_MENU_PROC,
} uimenu_state_t;
#endif
typedef struct
{
    UINT8   mode;
    UINT8   group;
    UINT16  channel;
} channel_t;
typedef struct imagedec_frm_t
{
    UINT8   *frm_y_addr;
    UINT32  frm_y_len;
    UINT8   *frm_c_addr;
    UINT32  frm_c_len;
    UINT32  busy;
} imagedec_frm, *p_imagedec_frm;
typedef enum _op_ci_msg
{
    NOT_OP_CI,
    OP_CI_PROG_CHG,
    OP_CI_TS_TYPE_CHG,
    OP_CI_CAM_CHG,
    OP_CI_DELAY_MSG,
    OP_CI_PLAYBACK_TSG,
} OP_CI_MSG_E;

#ifdef PIP_PNG_GIF
extern UINT8       pip_time;
#endif

/**program whether reset flag */
extern UINT8    g_ca_prog_reset_flag;
extern UINT8    cur_view_type;


INT32 ap_receive_msg(control_msg_t *msg, INT32 *msg_size, UINT32 timeout);
BOOL ap_send_msg(control_msg_type_t msg_type, UINT32 msg_code, BOOL if_clear_buffer);
void ap_clear_all_message(void);
void osd_ge_init(void);
BOOL ap_task_init(void);
PRESULT ap_send_msg_to_top_menu(POBJECT_HEAD menu, control_msg_type_t msg_type, UINT32 msg_code);
void ap_scart_vcr_detect(void);

#ifdef USB_MP_SUPPORT
void mp_apcallback(UINT32 event_type, UINT32 param);
void fs_apcallback(UINT32 event_type, UINT32 param);
#endif
void ap_epg_call_back(UINT32 tp_id, UINT16 service_id, UINT8 event_type);
void ap_comand_message_proc(UINT32 msg_type, UINT32 msg_code);

#ifdef SECURITY_MP_UPG_SUPPORT
void ap_mp_upg_set_usb_plugin(BOOL bok);
BOOL ap_mp_upg_get_usb_plugin(void);
#endif
#ifdef MULTIFEED_SUPPORT
void ap_multifeed_call_back(UINT32 prog_id);
#endif
#ifdef __cplusplus
}
#endif

#endif //_CONTROL_H_
