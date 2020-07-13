/*****************************************************************************
 *    Copyright (c) 2018 ALi Corp. All Rights Reserved
 *    This source is confidential and is ALi's proprietary information.
 *    This source is subject to ALi License Agreement, and shall not be
      disclosed to unauthorized individual.
 *    File: ap_ctrl.c
 *
 *    Description: This source file contains control application's
      OSD/menu relative functions.
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
#include <bus/tsi/tsi.h>
#include <hal/hal_gpio.h>
#include <hld/hld_dev.h>
#include <api/libpub/lib_frontend.h>
#include <hld/dis/vpo.h>
#include <api/libmp/media_player_api.h>
#include <api/libmp/pe.h>
#include <hld/pan/pan.h>
#include <hld/pan/pan_dev.h>
//#include "copper_common/com_api.h"
#include "../platform/board.h"
//#include "vkey.h"
#include "osd_rsc.h"
#include "win_dvt_mainmenu.h"
#include "win_com.h"
//#include "win_com_popup.h"
//#include "control.h"
//#include "usb_tpl.h"
//#include "menus_root.h"
//#include "ap_ctrl_mheg5.h"
//#include "ctrl_key_proc.h"
//#include "ap_ctrl_display.h"
//#include "ap_ctrl_time.h"

#include <aui_nim.h>
#include <aui_tsi.h>

#include "ali_dvt_internel.h"
#include "./LoaderCore/inc/spi/LoaderCoreSPI.h"
#define  IRD_NIM_DEBUG  libc_printf


struct osd_device *g_osd_dev = NULL;
struct osd_device *g_osd_dev2 = NULL;
extern struct pan_device*   g_pan_dev;

#define CONTROL_MBF_SIZE        300
#define CONTROL_TASK_STACKSIZE  0x4000
#define CONTROL_TASK_QUANTUM    10
OSAL_ID      control_mbf_id = INVALID_ID;
#define     INPUT_TASK_STACKSIZE        0x1000
#define     INPUT_TASK_QUANTUM      10
#define     INPUT_TASK_PRIORITY     OSAL_PRI_NORMAL

BOOL ap_is_key_task_get_key(void);
BOOL key_get_key(struct pan_key *key_struct, UINT32 timeout);
UINT32 scan_code_to_msg_code(struct pan_key *key_struct);


UINT32 ap_hk_to_vk(UINT32 start, UINT32 key_info, UINT32 *vkey)
{
    UINT32                      i = 0;
    UINT16                      n = 0;
    UINT16                      key_count = 0;
    //sys_state_t                 system_state = SYS_STATE_INITIALIZING;
    struct ir_key_map_t   *g_itou_key_tab = NULL;
    IR_KEY_INFO                 *pinfo = NULL;

    IR_KEY_INFO                 my_key = *(IR_KEY_INFO *) &key_info;


	if(0 == key_count)
	{
		;
	}
    if (NULL == vkey)
    {
        return 0;
    }
    //system_state = api_get_system_state();
    n = board_get_key_map_cnt();
    g_itou_key_tab = board_get_key_map();
    if (NULL == g_itou_key_tab)
    {
        return 0;
    }

    *vkey = V_KEY_NULL;
    for (i = start; i < n; i++)
    {
        pinfo = &g_itou_key_tab[i].key_info;
        key_count = pinfo->count;
        if ((pinfo->type == my_key.type) && (pinfo->state == my_key.state) && (pinfo->ir_code == my_key.ir_code))
        {
            *vkey = g_itou_key_tab[i].ui_vkey;
            
            break;
        }
    }

    return (i + 1);
}


UINT32 ap_vk_to_hk(UINT32 start, UINT32 vkey, UINT32 *key_info)
{
    UINT16                      i = 0;
    UINT16                      n = 0;
    struct ir_key_map_t   *g_itou_key_tab = NULL;

    if (NULL == key_info)
    {
        return 0;
    }
    n = board_get_key_map_cnt();
    g_itou_key_tab = board_get_key_map();
    if (NULL == g_itou_key_tab)
    {
        return 0;
    }

    *key_info = INVALID_HK;
    for (i = start; i < n; i++)
    {
        if (g_itou_key_tab[i].ui_vkey == vkey)
        {
            *key_info = *(UINT32 *) &g_itou_key_tab[i].key_info;
            break;
        }
    }

    return (i + 1);
}

#define UI_SCREEN_WIDTH 1280

#define UI_SCREEN_WIDTH2    720    //720////1280
#define UI_SCREEN_HEIGHT2   576    //576////720

static const osd_scale_param m_osd_scale_map_576[] =
{
    {PAL, 1,1,1,1/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},
    {PAL_N, 1,1,1,1/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},

    {NTSC, 1,6,1,5/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {NTSC_443, 1,6,1,5/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_60, 1,6,1,5/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_M, 1,6,1,5/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},

    {LINE_720_25, 9, 4, 16, 5/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720 }*/},
    {LINE_720_30, 9, 4, 16, 5/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720}*/},

    {LINE_1080_25, 3,8,8,15/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
    {LINE_1080_30, 3,8,8,15/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
};
static const osd_scale_param m_osd_scale_map_480[] =

{
    {PAL, 1,5,1,6/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},
    {PAL_N, 1,5,1,6/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},

    {NTSC, 1,1,1,1/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {NTSC_443, 1,1,1,1/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_60, 1,1,1,1/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_M, 1,1,1,1/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},

    {LINE_720_25, 9, 2, 16, 3/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720 }*/},
    {LINE_720_30, 9, 2, 16, 3/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720}*/},

    {LINE_1080_25, 3,12,8,27/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
    {LINE_1080_30, 3,12,8,27/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
};

static const osd_scale_param m_osd_scale_map_720[] =
{
    {PAL, 16,5,9,4,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},
    {PAL_N, 16,5,9,4,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},

    {NTSC, 16,3,9,2,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {NTSC_443, 16,3,9,2,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_60, 16,3,9,2,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_M, 16,3,9,2,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},

    {LINE_720_25, 1, 1, 1, 1},
    {LINE_720_30, 1, 1, 1, 1},

    {LINE_1080_25, 2,2,3,3,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
    {LINE_1080_30, 2,2,3,3,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
};

static const osd_scale_param m_osd_scale_map_1080[] =
{
    {PAL, 8,15,3,8,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},
    {PAL_N, 8,15,3,8,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},

    {NTSC, 8,9,3,4,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {NTSC_443, 8,9,3,4,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_60, 8,9,3,4,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_M, 8,9,3,4,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},

    {LINE_720_25, 3, 3, 2, 2,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720 }*/},
    {LINE_720_30, 3, 3, 2, 2,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720}*/},

    {LINE_1080_25, 1,1,1,1,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
    {LINE_1080_30, 1,1,1,1,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
};

static const osd_scale_param m_osd_scale_map_1024[] = 
{
    {PAL, 64,1,45,1,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},
    {PAL_N, 64,1,45,1,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 576}*/},

    {NTSC, 64,6,45,5,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {NTSC_443, 64,6,45,5,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_60, 64,6,45,5,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},
    {PAL_M, 64,6,45,5,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 720, 480}*/},

    {LINE_720_25, 4, 4, 5, 5,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720 }*/},
    {LINE_720_30, 4, 4, 5, 5,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1280, 720}*/},

    {LINE_1080_25, 8,8,15,15,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
    {LINE_1080_30, 8,8,15,15,/*{UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, 1920, 1080}*/},
};

UINT32 ap_get_osd_scale_param(enum tvsystem tvmode, INT32 screenwidth)
{
    UINT32 i = 0;
    UINT32 size_480 = 0;
    UINT32 size_576 = 0;
    UINT32 size_720 = 0;
    UINT32 size_1080 = 0;
    UINT32 size = 0;
    UINT32 size_1024 =0;
    const osd_scale_param  *p_ui_map = NULL;
    const UINT16 screen_wid_1280 = 1280;
    const UINT16 screen_wid_1920 = 1920;
    const UINT16 screen_wid_720 = 720;
    const UINT16 screen_wid_480 = 480;
    const UINT16 screen_wid_1024 = 1024;

    size = 0;
    p_ui_map = NULL;
    size_720  = ARRAY_SIZE(m_osd_scale_map_720);
    size_1080 = ARRAY_SIZE(m_osd_scale_map_1080);
    size_576 = ARRAY_SIZE(m_osd_scale_map_576);
    size_480 = ARRAY_SIZE(m_osd_scale_map_480);
    size_1024 = ARRAY_SIZE(m_osd_scale_map_1024);

    if ((LINE_1080_24 == tvmode) || (LINE_1152_ASS == tvmode) || (LINE_1080_ASS == tvmode)
        || (LINE_1080_50 == tvmode))
    {
        tvmode = LINE_1080_25;
    }
    else if (LINE_1080_60  == tvmode)
    {
        tvmode = LINE_1080_30;
    }
    if(screenwidth == screen_wid_1280)
    {
        size = size_720;
        p_ui_map = m_osd_scale_map_720;
    }
    else if(screenwidth == screen_wid_1920)
    {
        size = size_1080;
        p_ui_map = m_osd_scale_map_1080;
    }
    else if(screenwidth == screen_wid_720)
    {
        //ASSERT(0);
        size = size_576;
        p_ui_map = m_osd_scale_map_576;
    }
    else if(screenwidth == screen_wid_480)
    {
        size = size_480;
        p_ui_map = m_osd_scale_map_480;
    }
     else if(screenwidth == screen_wid_1024)
    {
        size = size_1024;
        p_ui_map = m_osd_scale_map_1024;
    }
    for (i = 0; i < size; i++)
    {
        if (p_ui_map[i].tv_sys == tvmode)
        {
            return (UINT32)&(p_ui_map[i]);
        }
    }

    // default to PAL
    return (UINT32)&(p_ui_map[0]);
}

static BOOL pre_ntsc = 0;
void api_osd_set_tv_system(BOOL ntsc)
{
    struct osdrect rect;

    if(ntsc==pre_ntsc)
    {
        return;
    }
    MEMSET(&rect, 0x0, sizeof(struct osdrect));
    osd_get_rect_on_screen(&rect);
    if(ntsc)
    {
        rect.u_top = OSD_STARTROW_N;
    }
    else
    {
        rect.u_top = OSD_STARTROW_P;
    }
    /*
      It's a big bug to show on osd when switching tv system.
    */
    osd_set_rect_on_screen(&rect);
    pre_ntsc = ntsc;
}

void set_osd_pos_for_tv_system(enum tvsystem tvmode)
{
    UINT32 param = 0;
    pcosd_scale_param pscalemp = NULL;

    if ((LINE_1080_24 == tvmode) || (LINE_1152_ASS == tvmode) || (LINE_1080_ASS == tvmode)
        || (LINE_1080_50 == tvmode))
    {
        tvmode = LINE_1080_25;
    }
    else if (LINE_1080_60 == tvmode)
    {
        tvmode = LINE_1080_30;
    }
    if((PAL == tvmode) || (PAL_N == tvmode))
    {
        api_osd_set_tv_system(FALSE);
    }
    else if(LINE_1080_25 == tvmode)
    {
        api_osd_set_tv_system(FALSE);
    }
    else if(LINE_1080_30 == tvmode)
    {
        api_osd_set_tv_system(TRUE);
    }
    else if(LINE_720_25 == tvmode)
    {
        api_osd_set_tv_system(FALSE);
    }
    else if(LINE_720_30 == tvmode)
    {
        api_osd_set_tv_system(TRUE);
    }
    else
    {
        api_osd_set_tv_system(TRUE);
    }
    param = ap_get_osd_scale_param(tvmode, UI_SCREEN_WIDTH);
    pscalemp = (pcosd_scale_param )param;
    if(pscalemp->h_div > pscalemp->h_mul)
    {
        osddrv_scale((HANDLE)g_osd_dev,OSD_SET_SCALE_MODE,OSD_SCALE_FILTER);
    }
    else
    {
        if (sys_ic_get_chip_id() == ALI_S3602)
        {
            osddrv_scale((HANDLE)g_osd_dev,OSD_SET_SCALE_MODE,OSD_SCALE_DUPLICATE);
        }
        else
        {
            osddrv_scale((HANDLE)g_osd_dev,OSD_SET_SCALE_MODE,OSD_SCALE_FILTER);
        }
    }
    osddrv_scale((HANDLE)g_osd_dev, OSD_SCALE_WITH_PARAM, param);
    param = ap_get_osd_scale_param(tvmode, UI_SCREEN_WIDTH2);
    osddrv_scale((HANDLE)g_osd_dev2, OSD_SCALE_WITH_PARAM, param);


}

void ap_osd_int(void)
{
    struct osd_region_info   osd_region_info;
    struct osd_rsc_info      osd_rsc_info;
    ge_hw_cmd_buffer        ge_hw_buf_config;
    UINT8                   *buffer = NULL;
    enum tvsystem           tvsys = PAL;
    struct ge_device    *ge_dev = NULL;

    g_osd_dev = (struct osd_device *)dev_get_by_id(HLD_DEV_TYPE_OSD, 0);
    g_osd_dev2 = (struct osd_device *)dev_get_by_id(HLD_DEV_TYPE_OSD, 1);
    vpo_ioctl((struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0), VPO_IO_GET_OUT_MODE, (UINT32) (&tvsys));
    osd_region_info.osddev_handle = (HANDLE) g_osd_dev;
    if (((ALI_S3821==sys_ic_get_chip_id()) && (sys_ic_get_rev_id() == IC_REV_1))||
        (ALI_C3505==sys_ic_get_chip_id()))
    {
        osd_region_info.t_open_para.e_mode = OSD_HD_ARGB1555;
    }
    else
    {
        osd_region_info.t_open_para.e_mode = OSD_256_COLOR;    // OSD_HD_ARGB8888;
    }
    osd_region_info.t_open_para.u_galpha_enable = IF_GLOBAL_ALPHA;
    osd_region_info.t_open_para.u_galpha = 0x0F;
    osd_region_info.t_open_para.u_pallette_sel = 0;
#ifdef OSD_VSRC_SUPPORT
    osd_region_info.u_is_use_vscr = 1;
#else
    osd_region_info.u_is_use_vscr = 0;
#endif
#ifdef TRUE_COLOR_HD_OSD
    osd_region_info.osdrect.u_left = OSD_STARTCOL;       //(720 - OSD_MAX_WIDTH)>>1;
#else
    osd_region_info.osdrect.u_left = (720 - OSD_MAX_WIDTH) >> 1;
#endif
    osd_region_info.osdrect.u_top = OSD_STARTROW_P;
    osd_region_info.osdrect.u_width = OSD_MAX_WIDTH;
    osd_region_info.osdrect.u_height = OSD_MAX_HEIGHT;
    MEMSET(&osd_rsc_info, 0x0, sizeof(osd_rsc_info));
    osd_rsc_info.osd_get_lang_env = osd_get_lang_environment;
    osd_rsc_info.osd_get_obj_info = osd_get_obj_info;
    osd_rsc_info.osd_get_rsc_data = osd_get_rsc_obj_data;
    osd_rsc_info.osd_get_thai_font_data = osd_get_thai_font_data;
    osd_rsc_info.osd_rel_rsc_data = osd_release_obj_data;
    osd_rsc_info.osd_get_font_lib = osd_get_default_font_lib;
    osd_rsc_info.osd_get_win_style = osdext_get_win_style;
    osd_rsc_info.osd_get_str_lib_id = osdext_get_msg_lib_id;
    osd_rsc_info.ap_hk_to_vk = ap_hk_to_vk;
    osd_region_init(&osd_region_info, &osd_rsc_info);
    ge_dev = (struct ge_device *)dev_get_by_id(HLD_DEV_TYPE_GE, 0);
    if (ge_dev != NULL && (0 == osd_region_info.u_is_use_vscr))
    {
        buffer                                          = NULL;
        buffer = (UINT8 *)malloc(1024 * 50 * sizeof(UINT32));
        if (buffer != NULL)
        {
            ge_hw_buf_config.b_is_lq = FALSE;
            ge_hw_buf_config.p_buffer = (UINT32 *)buffer;
            ge_hw_buf_config.n_buffer_len = 1024 * 50;    ///the buffer size in DW
            ge_io_ctrl(ge_dev, GE_IO_SET_HW_CMD_BUFFER, (UINT32) & ge_hw_buf_config);
        }
    }

#ifdef TRUE_COLOR_HD_OSD
#ifdef HDOSD_DEO_OUTPUT
    osddrv_io_ctl((HANDLE) g_osd_dev, OSD_IO_SET_DEO_AUTO_SWITCH, TRUE);
#else
    osddrv_io_ctl((HANDLE) g_osd_dev, OSD_IO_SET_DEO_AUTO_SWITCH, FALSE);
#endif
#else
    osddrv_io_ctl((HANDLE) g_osd_dev, OSD_IO_SET_DEO_AUTO_SWITCH, TRUE);
#endif
    osddrv_io_ctl((HANDLE) g_osd_dev2, OSD_IO_SET_DEO_AUTO_SWITCH, FALSE);
    osd_show_on_off(OSDDRV_OFF);
    set_osd_pos_for_tv_system(tvsys);
    osd_show_on_off(OSDDRV_ON);
#ifdef ENABLE_ANTIFLICK
    if (sys_ic_get_chip_id() == ALI_S3811 || sys_ic_get_chip_id() == ALI_S3602F || sys_ic_get_chip_id() == ALI_S3503)
    {
        SYSTEM_DATA *sys_data;
        sys_data = sys_data_get();
        if ((SCART_RGB == sys_data->avset.scart_out)
        || ((SCART_YUV == sys_data->avset.scart_out)
           && ((sys_data->avset.tv_mode == TV_MODE_PAL) || (sys_data->avset.tv_mode == TV_MODE_NTSC358))))
        {
            osddrv_io_ctl((HANDLE) g_osd_dev, OSD_IO_ENABLE_ANTIFLICK, 1);
        }
    }
#endif
}


unsigned int get_sat_if(const ird_spi_dmd_satellite_desc_t *satellite)
{
    unsigned int freq = 0; // An Invalid value
    switch (satellite->band.downlink)
    {
        case DMD_DOWNLINK_INJECTION:
            freq = satellite->frequency;
            break;
        case DMD_DOWNLINK_CUSTOM:
            freq = satellite->frequency;
            break;
        case DMD_DOWNLINK_Ku_LOW:
            freq = (satellite->frequency - satellite->band.lo);
            break;
        case DMD_DOWNLINK_Ku_HIGH:
            freq = (satellite->frequency - satellite->band.lo);
            break;
        case DMD_DOWNLINK_C:
            freq = (satellite->band.lo - satellite->frequency);
            break;
        default:
            break;
    }
    return freq;
}

int diseqc_operations(aui_hdl nim_hdl, unsigned long dmd_id, const ird_spi_dmd_satellite_desc_t *satellite)
{
    int port_flag =0 ;
    int polar_flag =0 ;
    unsigned char port_cmd[4] = { 0xE0, 0x10, 0x38, 0xF0 };
    aui_nim_22k_status lnb_tone = AUI_NIM_22K_OFF;
    aui_nim_polar polar = AUI_NIM_POLAR_HORIZONTAL;

    // Turn of the continuous tone if present
    if (AUI_RTN_SUCCESS != aui_nim_set22k_onoff(nim_hdl, AUI_NIM_22K_OFF))
    {
        IRD_NIM_DEBUG("Invokes aui_nim_set22k_onoff error!\n");
        return -1;
    }

    // Change of Voltage if required
    polar_flag = 1;
    switch (satellite->polarization)
    {
        case DMD_PLR_HORIZONTAL:     /* Select horizontal polarization */
            polar = AUI_NIM_POLAR_HORIZONTAL;
            break;
        case  DMD_PLR_VERTICAL:      /* Select vertical polarization */
            polar = AUI_NIM_POLAR_VERTICAL;
            break;
        case DMD_PLR_NONE:           /* No polarization (used when LNB power is off) */
            polar_flag = 0;
            break;
        case DMD_PLR_CIRCULAR_LEFT:  /* Select circular left polarization */
            polar = AUI_NIM_CPOLAR_LEFT;
            break;
        case DMD_PLR_CIRCULAR_RIGHT:  /* Select circular right polarization */
            polar = AUI_NIM_CPOLAR_RIGHT;
            break;
        default:
            polar_flag = 0;
            break;
    }
    if (0 != polar_flag)
    {
        if (AUI_RTN_SUCCESS !=aui_nim_set_polar(nim_hdl, polar))
        {
            IRD_NIM_DEBUG("Invokes aui_nim_set_polar error! %d\n", polar);
            return 1;
        } 
        else
        {
            IRD_NIM_DEBUG("AUI LNB polar %s OK\n",(polar == AUI_NIM_POLAR_HORIZONTAL) ? "H" : "V");
        }
    }

    // Full DiSEqC Message
    osal_task_sleep(20); // more than 15ms
    port_flag = 1;
    // DATA SET nibble (bit4 ~ bit1): Opt Pos Polar Band
    // PORT A: Opt A/Pos A
    // PORT B: Opt A/Pos B
    // PORT C: Opt B/Pos A
    // PORT D: Opt B/Pos B
    switch (satellite->diseqc_port) {
        case DMD_DISEQC_PORTA:
            break;
        case DMD_DISEQC_PORTB:
            port_cmd[3] += 4;
            break;
        case DMD_DISEQC_PORTC:
            port_cmd[3] += 8;
            break;
        case DMD_DISEQC_PORTD:
            port_cmd[3] += 12;
            break;
        default:
            port_flag = 0;
            break;
    }
    if (0 != port_flag)
    {
        if (AUI_RTN_SUCCESS !=aui_diseqc_oper(nim_hdl, AUI_DISEQC_MODE_BYTES, port_cmd, 4,NULL, NULL))
        {
            IRD_NIM_DEBUG("AUI Diseqc port set error\n");
            return 1;
        }
        else
        {
            IRD_NIM_DEBUG("AUI Diseqc port Ok %d\n", port_cmd[3]);
        }
    }

    // Start continuous tone if required
    osal_task_sleep(20); // The gap between ToneBurst and continuos tone should be more than 15ms
    if ((DMD_LNB_TONE_OFF ==satellite->lnb_tone_state )
        || (DMD_LNB_TONE_22KHZ ==satellite->lnb_tone_state ))
    {
        lnb_tone = AUI_NIM_22K_OFF;
        if (DMD_LNB_TONE_22KHZ == satellite->lnb_tone_state ) 
        {
            lnb_tone = AUI_NIM_22K_ON;
        }
        if (AUI_RTN_SUCCESS !=aui_nim_set22k_onoff(nim_hdl, lnb_tone)) 
        {
            IRD_NIM_DEBUG("Invokes aui_nim_set22k_onoff error!\n");
            return 1;
        }
        else
        {
            IRD_NIM_DEBUG("AUI LNB tone %s OK\n",lnb_tone == AUI_NIM_22K_ON ? "ON" : "OFF");
        }
    }

    return 0;
}


void LoaderCore_dvbs_connect(char *private_data, int pid)
{
   
    int ret = 0;
	//lc_result result = LC_SUCCESS;
    struct aui_nim_attr nim_attr;
    struct aui_nim_connect_param param;
    aui_hdl nim_hdl;
    aui_signal_status info;
    aui_hdl tsi_hdl;
    aui_attr_tsi attr_tsi;
    int lock_status = AUI_NIM_STATUS_UNKNOWN;
    ird_spi_dmd_delivery_t *pDelivery = NULL;
    unsigned long dmd_id =1;
    ird_spi_dmd_satellite_desc_t *satellite = NULL;

    if(NULL == private_data)
    {
        IRD_NIM_DEBUG("input private data is NULL\n");
        return LC_FAILURE;
    }

    pDelivery = (ird_spi_dmd_delivery_t *)private_data;
    satellite = (ird_spi_dmd_satellite_desc_t *) &(pDelivery->delivery.satellite);

    IRD_NIM_DEBUG("type of dvbtype is 0x%03x\n", pDelivery->device_type);
    IRD_NIM_DEBUG(" sat_info frequency  0x%05x\n", satellite->frequency);
    IRD_NIM_DEBUG(" sat_info symbol_rate  0x%05x\n", satellite->symbol_rate);
    IRD_NIM_DEBUG(" sat_info modulation_system  0x%05x\n", satellite->modulation_system);
    IRD_NIM_DEBUG(" sat_info polarization  0x%05x\n", satellite->polarization);
    IRD_NIM_DEBUG(" sat_info modulation  0x%05x\n", satellite->modulation);
    IRD_NIM_DEBUG(" sat_info fec_rate  0x%05x\n", satellite->fec_rate);
    IRD_NIM_DEBUG(" sat_info roll_off  0x%05x\n", satellite->roll_off);
    IRD_NIM_DEBUG(" sat_info lnb_tone_state  0x%05x\n", satellite->lnb_tone_state);
    IRD_NIM_DEBUG(" sat_info diseqc_port  0x%05x\n", satellite->diseqc_port);
    IRD_NIM_DEBUG(" sat_info band.lo  0x%05x\n", satellite->band.lo);
    IRD_NIM_DEBUG(" sat_info band.downlink  0x%05x\n", satellite->band.downlink);
	IRD_NIM_DEBUG(" sat_info PID %05d\n",pid);

    if (aui_find_dev_by_idx(AUI_MODULE_NIM, dmd_id, &nim_hdl))
    {
        IRD_NIM_DEBUG("\r\n NIM %d not found\n", dmd_id);
        return LC_FAILURE;
    }

    memset(&param, 0, sizeof(struct aui_nim_connect_param));
    switch (pDelivery->device_type)
    {
        case DMD_SATELLITE:
            satellite = &pDelivery->delivery.satellite;
            ret = diseqc_operations(nim_hdl, dmd_id, satellite);
            if (0 != ret)
            {
                IRD_NIM_DEBUG("DiSEqC operation error\n");
                return LC_FAILURE;
            }
            param.ul_freq = get_sat_if(satellite) / 1000;
            param.en_demod_type = AUI_NIM_QPSK;
            param.connect_param.sat.ul_symrate = satellite->symbol_rate;
            param.connect_param.sat.fec = AUI_NIM_FEC_AUTO; // Use auto mode
            break;
        case DMD_CABLE:
        case DMD_TERRESTRIAL:
        case DMD_IP:
            IRD_NIM_DEBUG("DMD type %d not support yet\n",pDelivery->device_type);
            return LC_FAILURE;
        default:
            IRD_NIM_DEBUG("Unknown DMD type %d \n",pDelivery->device_type);
            return LC_FAILURE;
    }
    IRD_NIM_DEBUG("NIM connect dev %d type %d, src %ld, polar %d, IF %d (band %d), symb %ld\n",
                    dmd_id,
                    param.en_demod_type,
                    param.connect_param.sat.ul_src,
                    param.connect_param.sat.ul_polar,
                    param.ul_freq,
                    param.connect_param.sat.ul_freq_band,
                    param.connect_param.sat.ul_symrate);

	IRD_NIM_DEBUG("nim connect dev %d freq %d, symb %d\n", dmd_id, satellite->frequency, satellite->symbol_rate);

    if (AUI_RTN_SUCCESS !=aui_nim_connect(nim_hdl, &param))
    {
        IRD_NIM_DEBUG("Invokes aui_nim_connect error!\n");
        return LC_FAILURE;
    }
    IRD_NIM_DEBUG("Invokes aui_nim_connect ok!\n");    
    unsigned int retry = 0;
    while( AUI_NIM_STATUS_LOCKED != lock_status)
    {
        if(AUI_RTN_SUCCESS !=aui_nim_is_lock(nim_hdl, &lock_status) )
        {
            IRD_NIM_DEBUG("is_lock error\n");
            aui_nim_disconnect(&nim_hdl);
            //aui_nim_close(&nim_hdl);
            return LC_FAILURE;
        }
        IRD_NIM_DEBUG("aui_nim_is_lock retry: %d\n", retry);
        if (retry >= 30) {
            IRD_NIM_DEBUG("aui_nim_is_lock retry timeout\n");
            //break;
            return LC_FAILURE;
        }
        retry++;
        aui_os_task_sleep(200);
    }
    IRD_NIM_DEBUG("Invokes aui_nim_is_lock ok!\n");    
    aui_os_task_sleep(200);
    if(AUI_RTN_SUCCESS != aui_nim_signal_info_get(nim_hdl, &info) )
    {
        IRD_NIM_DEBUG("info_get error\n");
        aui_nim_disconnect(&nim_hdl);
        //aui_nim_close(&nim_hdl);
        return LC_FAILURE;
    }
    IRD_NIM_DEBUG("Invokes aui_nim_signal_info_get ok!\n");    

    info.ul_freq = param.ul_freq;
    IRD_NIM_DEBUG("info: freq %ld, strength %d, quality %d, ber %d, rf_level %d,"
                "signal_cn %d\n", info.ul_freq, (int)info.ul_signal_strength,
                (int)info.ul_signal_quality, (int)info.ul_bit_error_rate,
                (int)info.ul_rf_level, (int)info.ul_signal_cn);
    return LC_SUCCESS;
	
}



#ifndef _BUILD_OTA_E_
typedef enum
{
    //key
    CTRL_MSG_SUBTYPE_KEY = 0,
    CTRL_MSG_SUBTYPE_KEY_UI,
    CTRL_MSG_TYPE_KEY = 2,
    //cmd
    CTRL_MSG_SUBTYPE_CMD_ENTER_ROOT,
    CTRL_MSG_SUBTYPE_CMD_EXIT_ROOT,
    CTRL_MSG_SUBTYPE_CMD_EXIT_TOP,
    CTRL_MSG_SUBTYPE_CMD_EXIT_ALL,
    CTRL_MSG_SUBTYPE_CMD_EXIT,
    CTRL_MSG_SUBTYPE_CMD_SLEEP,
    CTRL_MSG_SUBTYPE_CMD_PLAY_PROGRAM,
    CTRL_MSG_SUBTYPE_CMD_UPDATE_VIEW,
    CTRL_MSG_SUBTYPE_CMD_DEL_FILE,
    CTRL_MSG_SUBTYPE_CMD_FACTORY_RESET,
    CTRL_MSG_SUBTYPE_CMD_TIMER_WAKEUP,
    CTRL_MSG_SUBTYPE_CMD_TIMER_EXPIRE,
    CTRL_MSG_SUBTYPE_CMD_TIMER_RECORD,
    CTRL_MSG_SUBTYPE_CMD_TVSAT_SWITCH,
    CTRL_MSG_SUBTYPE_CMD_SCAN,
    CTRL_MSG_SUBTYPE_CMD_TP_TURN,
    CTRL_MSG_SUBTYPE_CMD_UPGRADE,
    CTRL_MSG_SUBTYPE_CMD_UPGRADE_SLAVE,
    CTRL_MSG_SUBTYPE_CMD_REBOOT,
    CTRL_MSG_SUBTYPE_CMD_EPG_PF_UPDATED,
    CTRL_MSG_SUBTYPE_CMD_EPG_SCH_UPDATED,
    CTRL_MSG_SUBTYPE_CMD_EPG_DETAIL_UPDATED,
    CTRL_MSG_SUBTYPE_CMD_EPG_FULL,
    CTRL_MSG_SUBTYPE_CMD_PIDCHANGE,
    CTRL_MSG_SUBTYPE_CMD_AUDIO_PIDCHANGE,
    CTRL_MSG_SUBTYPE_CMD_TIMEDISPLAYUPDATE,
    CTRL_MSG_SUBTYPE_CMD_TIMESECONDUPDATE,
    CTRL_MSG_SUBTYPE_CMD_AGE_LIMIT_UPDATED,
    CTRL_MSG_SUBTYPE_CMD_PLAYMUSIC,
    CTRL_MSG_SUBTYPE_CMD_PLAYIMAGE,
    CTRL_MSG_SUBTYPE_CMD_SYSDATA_SAVE,
    CTRL_MSG_SUBTYPE_CMD_FILE_INFO_UPDATE,
    CTRL_MSG_SUBTYPE_CMD_POPUP,
    CTRL_MSG_SUBTYPE_CMD_OPERATE_CI,
    CTRL_MSG_SUBTYPE_CMD_STO,
    CTRL_MSG_SUBTYPE_CMD_EXIT_VFORMAT,
    CTRL_MSG_SUBTYPE_CMD_EDID_READY,
    CTRL_MSG_SUBTYPE_CMD_HOT_PLUG_OUT,

#ifdef AUTO_UPDATE_TPINFO_SUPPORT
    CTRL_MSG_SUBTYPE_CMD_UPDATE_TPINFO,
    CTRL_MSG_SUBTYPE_CMD_START_TP_SCAN,
    CTRL_MSG_SUBTYPE_CMD_PLAY_CHANNEL,
#endif

#ifdef MULTIFEED_SUPPORT
    CTRL_MSG_SUBTYPE_CMD_MULTIFEED,
#endif
#ifdef CC_BY_OSD
    CTRL_MSG_SUBTYPE_CMD_CS_UPDTAED, //vicky20110210
#endif

    CTRL_MSG_SUBTYPE_CMD_PIDCHANGE_PLAYBACK,/*detect pid changed when playback,for fix BUG41625*/

    CTRL_MSG_TYPE_CMD = 100,

    //status
    CTRL_MSG_SUBTYPE_STATUS_SIGNAL,
    CTRL_MSG_SUBTYPE_STATUS_BITERROR,
    CTRL_MSG_SUBTYPE_STATUS_TIMEOUT,
    CTRL_MSG_SUBTYPE_STATUS_RF_SET,
    CTRL_MSG_SUBTYPE_STATUS_PVR,
    CTRL_MSG_SUBTYPE_STATUS_MCAS,
    CTRL_MSG_SUBTYPE_STATUS_CI,
    CTRL_MSG_SUBTYPE_STATUS_CI_UPG,
    CTRL_MSG_SUBTYPE_STATUS_SCROLL_STRING,

    CTRL_MSG_SUBTYPE_STATUS_USB,

    CTRL_MSG_SUBTYPE_STATUS_USBMOUNT,
    CTRL_MSG_SUBTYPE_STATUS_USBREMOUNT,
    CTRL_MSG_SUBTYPE_STATUS_USBUNMOUNT,
    CTRL_MSG_SUBTYPE_STATUS_USBOVER,
    CTRL_MSG_SUBTYPE_STATUS_USBREFLASH,
    CTRL_MSG_SUBTYPE_STATUS_IMAGEOVER,
    CTRL_MSG_SUBTYPE_STATUS_IMGTOOVER,
    CTRL_MSG_SUBTYPE_STATUS_PROC_UPDATE,
    CTRL_MSG_SUBTYPE_STATUS_MP3OVER,
    CTRL_MSG_SUBTYPE_STATUS_JPEG_DEC_PROCESS,
    CTRL_MSG_SUBTYPE_STATUS_JPEG_DEC_ERR,
     CTRL_MSG_SUBTYPE_STATUS_SPECTRUM_UPDATE,
    CTRL_MSG_SUBTYPE_STATUS_MPLAYER_DISPLAY,
    CTRL_MSG_SUBTYPE_STATUS_VIDEO_OVER,
    CTRL_MSG_SUBTYPE_STATUS_SCRIMBLE_SIGN,
    CTRL_MSG_SUBTYPE_STATUS_BUILD_IDX,
    CTRL_MSG_SUBTYPE_STATUS_COPYFILE_NEWFILE,
    CTRL_MSG_SUBTYPE_STATUS_COPYFILE_PROGRESS,
    CTRL_MSG_SUBTYPE_STATUS_COPYFILE_ERR,
    CTRL_MSG_SUBTYPE_STATUS_COPYFILE_CANT_COPY,
    CTRL_MSG_SUBTYPE_STATUS_COPYFILE_OVERWRITE,
    CTRL_MSG_SUBTYPE_STATUS_VIDEO_DEC_ERR,
    CTRL_MSG_SUBTYPE_STATUS_PARSE_END,

#ifdef AUTOMATIC_STANDBY
    CTRL_MSG_SUBTYPE_STATUS_AUTOMATIC_STANDBY_TIME,
#endif
#ifdef MULTIFEED_SUPPORT
    CTRL_MSG_SUBTYPE_EXIT,
#endif
#ifdef AUDIO_DESCRIPTION_SUPPORT
     CTRL_MSG_SUBTYPE_STATUS_AUDIO_DESCRIPTION,
#endif
     CTRL_MSG_SUBTYPE_STATUS_AUDIO_TYPE_UPDATE,
     CTRL_MSG_SUBTYPE_NEXT_CHAPTER,
     CTRL_MSG_SUBTYPE_STATUS_OTA_PROCESS_MSG,

//modify for adding welcome page when only open dvbt 2011 10 19
    CTRL_MSG_TYPE_POPUP_TIMER,
    CTRL_MSG_SUBTYPE_CMD_AUTO_STANDBY,
    CTRL_MSG_SUBTYPE_CMD_AUTO_STANDBY_TIMER,
    CTRL_MSG_SUBTYPE_CMD_PVR_AUTO_STANDBY_TIMER,
//modify end
#ifdef AUTO_OTA
    CTRL_MSG_SUBTYPE_CMD_OTA_INFORM,
#endif
 }control_msg_type_t;

typedef struct
{
    control_msg_type_t    msg_type;
    UINT32                msg_code;
}control_msg_t, *p_control_msg_t;

static UINT8        ap_ctrl_msg_count = 0;
#define MAX_CONTINUE_PROC_MSG_CNT   3
#define MAX_KEY_PER_CHECK           10

BOOL ap_send_msg(control_msg_type_t msg_type, UINT32 msg_code, BOOL if_clear_buffer);

static ER ap_ctrl_tsk_get_msg(control_msg_t *msg, UINT32 *msg_siz)
{
    BOOL    bkey_task_get_key = FALSE;
    ER      retval = E_FAILURE;
    UINT32  msg_code = 0;
    struct pan_key  key_struct;
    struct pan_key  key_struct_tmp;
    UINT8           get_key_cnt = 0;

    MEMSET(&key_struct, 0, sizeof(struct pan_key));
    MEMSET(&key_struct_tmp, 0, sizeof(struct pan_key));
    bkey_task_get_key = ap_is_key_task_get_key();
    // receive queue message
    if (bkey_task_get_key || (ap_ctrl_msg_count < MAX_CONTINUE_PROC_MSG_CNT))
    {
        // the job to get key now set to key_task, or continuous process queue msg less then 3
        retval = osal_msgqueue_receive(msg, (INT *)msg_siz, control_mbf_id, 100);
        if ((!bkey_task_get_key) && (OSAL_E_OK == retval))
        {
            ap_ctrl_msg_count++;
        }
    }
    else
    {
        // already continuous processed 3 msg, should give chance to process key msg
        retval = OSAL_E_FAIL;
        ap_ctrl_msg_count = 0;
    }

    if ((!bkey_task_get_key) && (retval != OSAL_E_OK))
    {
        // ctrl tsk receive key
        get_key_cnt = 0;
        while (get_key_cnt++ < MAX_KEY_PER_CHECK)
        {
            if (!key_get_key(&key_struct_tmp, 0))
            {
                break;
            }

            if ((PAN_KEY_RELEASE == key_struct_tmp.state) && (key_struct_tmp.count >= 1))
            {
                break;  //this will not lose the last PRESSED key.
            }

            MEMCPY(&key_struct, &key_struct_tmp, sizeof(key_struct));   //save it temp
            retval = E_OK;
        }

        if (E_OK == retval)
        {
            msg_code = scan_code_to_msg_code(&key_struct);
            msg->msg_type = CTRL_MSG_SUBTYPE_KEY;
            msg->msg_code = msg_code;
            retval = OSAL_E_OK;
        }
        else
        {
            ap_ctrl_msg_count = 0;
        }
    }

    return retval;
}

typedef enum _key_proc_ret
{
    RET_KEY_NONE = 0,
    RET_KEY_RETURN = 1,
    RET_KEY_POP_PRE_MENU = 2,
    RET_KEY_MENU_KEY_PROC,
    RET_KEY_CEHCK_PROC_RETURN,
    RET_KEY_UNKOWN_KEY_PROC,
    RET_KEY_HK_TO_VKEY,
} RET_KEY_PROC_E;

static RET_KEY_PROC_E ap_subkey_proc(UINT32 *pkey, UINT32 *pvkey, UINT32 *prevkey, UINT32 *pstart, UINT32 *pnext_start)
{
    UINT32  key = *pkey;
    UINT32  vkey = *pvkey;
    UINT32  start = *pstart;
    UINT32  next_start = *pnext_start;

    if (V_KEY_NULL != vkey)
    {

    }

    if (0 == start)
    {
        *prevkey = vkey;
    }

    start = next_start;
    if (V_KEY_NULL == vkey)
    {
        if (*prevkey == vkey)
        {   /* First time */
            *pvkey = vkey;
            *pkey = key;
            *pstart = start;
            *pnext_start = next_start;

            return RET_KEY_RETURN;
        }
        else
        {
            /* If try mapping the key for sever times ,then
               try to use the first mapping vkey for unkown key processing.
               ( Only valid for no menu on screen processing )*/
            vkey = *prevkey;
            *pvkey = vkey;
            *pkey = key;
            *pstart = start;
            *pnext_start = next_start;

            return RET_KEY_UNKOWN_KEY_PROC;
        }
    }

    else
    {
    }

    *pvkey = vkey;
    *pkey = key;
    *pstart = start;
    *pnext_start = next_start;

    return RET_KEY_NONE;
}

static RET_KEY_PROC_E ap_key_nonkey_msg_proc(UINT32 msg_type, UINT32 msg_code, POBJECT_HEAD topmenu,
                        PRESULT *proc_ret, UINT32 *osd_msg_type, UINT32 *osd_msg_code)
{
    if ((CTRL_MSG_SUBTYPE_CMD_EXIT_ROOT == msg_type) || (CTRL_MSG_SUBTYPE_CMD_EXIT_TOP == msg_type))
    {
        if (CTRL_MSG_SUBTYPE_CMD_EXIT_ROOT == msg_type)
        {
            if ((msg_code == (UINT32) topmenu) && (topmenu != NULL))
            {
                *proc_ret = osd_obj_close(topmenu, C_DRAW_SIGN_EVN_FLG | C_CLOSE_CLRBACK_FLG);
                *proc_ret = PROC_PASS;
                return RET_KEY_POP_PRE_MENU;
            }

        }
        else    //CTRL_MSG_SUBTYPE_CMD_EXIT_TOP
        {
            if (NULL == topmenu)
            {
                return RET_KEY_RETURN;
            }

            *proc_ret = osd_obj_close(topmenu, C_DRAW_SIGN_EVN_FLG | C_CLOSE_CLRBACK_FLG);
            *proc_ret = PROC_PASS;
            return RET_KEY_POP_PRE_MENU;
        }
    }
    else
    {
        *osd_msg_type = (MSG_TYPE_MSG << 16) | (msg_type & 0xFFFF);
        *osd_msg_code = msg_code;
    }

    return RET_KEY_NONE;
}

static RET_KEY_PROC_E ap_key_pop_pre_menu(PRESULT *proc_ret)
{
    //BOOL            bhint_flag = FALSE;
    POBJECT_HEAD    new_menu = NULL;

    menu_stack_pop();
    new_menu = menu_stack_get_top();

    if (new_menu != NULL)    /* Open the top menu */
    {
        //win_msg_popup_close();
        *proc_ret = osd_obj_open(new_menu, MENU_OPEN_TYPE_STACK);
        if (PROC_LEAVE == *proc_ret)
        {
            return RET_KEY_POP_PRE_MENU;
        }

        *proc_ret = PROC_LOOP;
    }
    else    /* Restore previous menu */
    {
        *proc_ret = PROC_LOOP;
    }

    return RET_KEY_NONE;
}

static RET_KEY_PROC_E ap_key_proc_no_menu(POBJECT_HEAD *topmenu, UINT32 key, UINT32 vkey,
      UINT32 __MAYBE_UNUSED__ osd_msg_type, UINT32 osd_msg_code, PRESULT *proc_ret)
{
    BOOL    bfind = FALSE;
    BOOL    bflag =FALSE;
    POBJECT_HEAD    new_menu = NULL;
    

    bfind = FALSE;//menus_find_root(CTRL_MSG_SUBTYPE_KEY, osd_msg_code, &bflag, &new_menu);

    if (!bfind)
    {
        return RET_KEY_HK_TO_VKEY;
    }
    else /* Enter a new menu*/
    {
        //win_msg_popup_close();

        /* Open the new menu*/
        *proc_ret = osd_obj_open(new_menu, MENU_OPEN_TYPE_KEY + vkey);

        if (*proc_ret != PROC_LEAVE)
        {
            menu_stack_push(new_menu);
            if (bflag)
            {
                *topmenu = new_menu;
                return RET_KEY_MENU_KEY_PROC;
            }
            *proc_ret = PROC_LOOP;
        }
        else
        {
            *proc_ret = PROC_PASS;
        }
    }

    return RET_KEY_NONE;
}

void ap_key_commsg_proc(UINT32 msg_type, UINT32 msg_code)
{
    POBJECT_HEAD                topmenu = NULL;
    PRESULT                     proc_ret = 0;
    UINT32                      key = 0;
    UINT32                      vkey = 0;
    UINT32                      prevkey = 0xFFFFFFFF;
    UINT32                      osd_msg_type = 0;
    UINT32                      osd_msg_code = 0;
    UINT32                      start = 0;
    UINT32                      next_start = 0;
    RET_KEY_PROC_E              key_ret = RET_KEY_NONE;

    topmenu = menu_stack_get_top();


    if (msg_type <= CTRL_MSG_TYPE_KEY)
    {
        key = msg_code;
        if (CTRL_MSG_SUBTYPE_KEY == msg_type)
        {
            osd_msg_type = (MSG_TYPE_KEY << 16);
HK_TO_VKEY:
            next_start = ap_hk_to_vk(start, key, &vkey);
            key_ret = ap_subkey_proc(&key, &vkey, &prevkey, &start, &next_start);
            if (RET_KEY_RETURN == key_ret)
            {
                return;
            }
            if (RET_KEY_UNKOWN_KEY_PROC == key_ret)
            {
                proc_ret = PROC_PASS;
                goto UNKOWN_KEY_PROC;
            }
        }
        else        /*CTRL_MSG_SUBTYPE_KEY_UI,abandon type*/
        {
            vkey = key;
            next_start = ap_vk_to_hk(0, vkey, &key);
        }
        
        osd_msg_code = key;
    }
    else
    {
        // other msg process
        key_ret = ap_key_nonkey_msg_proc(msg_type, msg_code, topmenu, &proc_ret, &osd_msg_type, &osd_msg_code);

        if (RET_KEY_RETURN == key_ret)
        {
            return;
        }
        if (RET_KEY_POP_PRE_MENU == key_ret)
        {
            goto POP_PRE_MENU;
        }
        if (RET_KEY_CEHCK_PROC_RETURN == key_ret)
        {
            goto CEHCK_PROC_RETURN;
        }
    }
    proc_ret = PROC_PASS;
    if (topmenu != NULL)
    { // now has some menu displaying, forward msg to menu
MENU_KEY_PROC:
        proc_ret = osd_obj_proc(topmenu, osd_msg_type, osd_msg_code, osd_msg_code);
CEHCK_PROC_RETURN :
        if (PROC_LEAVE == proc_ret)
        {
POP_PRE_MENU:
            key_ret = ap_key_pop_pre_menu(&proc_ret);

            if (RET_KEY_RETURN == key_ret)
            {
                return;
            }

            if (RET_KEY_POP_PRE_MENU == key_ret)
            {
                goto POP_PRE_MENU;
            }
        }

    }
    else
    {   // no menu on the top
        if (msg_type <= CTRL_MSG_TYPE_KEY)
        {
            key_ret = ap_key_proc_no_menu(&topmenu, key, vkey, osd_msg_type, osd_msg_code, &proc_ret);
            if (RET_KEY_UNKOWN_KEY_PROC == key_ret)
            {
                goto UNKOWN_KEY_PROC;
            }
            if (RET_KEY_HK_TO_VKEY == key_ret)
            {
                goto HK_TO_VKEY;
            }
            if (RET_KEY_MENU_KEY_PROC == key_ret)
            {
                goto MENU_KEY_PROC;
            }
        }

    }

UNKOWN_KEY_PROC:
    if (PROC_PASS == proc_ret)
    {
        //ap_key_unknown_proc(msg_type, msg_code, key, vkey);
    }
}

static void ap_control_task(void)
{
    struct vpo_device *vpo_dev = NULL;
    ER              retval = E_FAILURE;
    control_msg_t    msg;
    UINT32          msg_siz = 0;
    
    vpo_dev = (struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0);
    ap_osd_int();
    osd_set_lang_environment(0);
    vpo_ioctl(vpo_dev, VPO_IO_HDMI_OUT_PIC_FMT, (UINT32)(YCBCR_444));

    if (osd_obj_open((UINT32)&g_win_mainmenu, MENU_OPEN_TYPE_OTHER) != PROC_LEAVE)
    {
        menu_stack_push((UINT32)&g_win_mainmenu);
    }

    ap_send_msg(CTRL_MSG_SUBTYPE_KEY_UI, V_KEY_ENTER, FALSE);
    
    while(1)
    {
        // Recieve MSG to process.
        retval = ap_ctrl_tsk_get_msg(&msg, &msg_siz);
        if (OSAL_E_OK == retval)
        {
             // massage valid, dispatch this message.
             ap_key_commsg_proc(msg.msg_type, msg.msg_code);
        }
        
    }
}

BOOL ap_task_init(void)
{
    ID control_task_id = OSAL_INVALID_ID;
    OSAL_T_CMBF t_cmbf;
    OSAL_T_CTSK t_ctsk;

	MEMSET(&t_cmbf, 0, sizeof(OSAL_T_CTSK));
    MEMSET(&t_ctsk, 0, sizeof(OSAL_T_CTSK));
    
    t_cmbf.bufsz = CONTROL_MBF_SIZE * sizeof(control_msg_t);
    t_cmbf.maxmsz = sizeof(control_msg_t);
    t_cmbf.name[0] = 'c';
    t_cmbf.name[1] = 't';
    t_cmbf.name[2] = 'l';
    control_mbf_id = OSAL_INVALID_ID;
    control_task_id = OSAL_INVALID_ID;
    control_mbf_id = osal_msgqueue_create(&t_cmbf);
    if (OSAL_INVALID_ID == control_mbf_id)
    {
        PRINTF("cre_mbf control_mbf_id failed\n");
        return FALSE;
    }
    
    t_ctsk.stksz = CONTROL_TASK_STACKSIZE + 0x5000;
    t_ctsk.quantum = CONTROL_TASK_QUANTUM;
    t_ctsk.itskpri = OSAL_PRI_NORMAL;
    t_ctsk.name[0] = 'C';
    t_ctsk.name[1] = 'T';
    t_ctsk.name[2] = 'L';
    t_ctsk.task = (FP) ap_control_task;
    control_task_id = osal_task_create(&t_ctsk);
    if (OSAL_INVALID_ID == control_task_id)
    {
        PRINTF("cre_tsk control_task_id failed\n");
        return FALSE;
    }



    return TRUE;
}

void ap_clear_all_message(void)
{
    ER              retval = E_FAILURE;
    control_msg_t    msg;
    UINT32          msg_siz = 0;

    do
    {
        retval = osal_msgqueue_receive((VP) & msg, (INT *)&msg_siz, control_mbf_id, 0);
    }
    while (E_OK == retval);
}

INT32 ap_receive_msg(control_msg_t *msg, INT32 *msg_siz, UINT32 timeout)
{
    INT32   ret = E_FAILURE;

    if ((NULL == msg) || (NULL == msg_siz))
    {
        return ret;
    }

    ret = osal_msgqueue_receive(msg, (INT*)&msg_siz, control_mbf_id, timeout);
    return ret;
}

BOOL ap_send_msg(control_msg_type_t msg_type, UINT32 msg_code, BOOL if_clear_buffer)
{
    ER              ret_val = E_FAILURE;
    control_msg_t    control_msg;

	MEMSET(&control_msg, 0, sizeof(control_msg_t));
    control_msg.msg_type = msg_type;
    control_msg.msg_code = msg_code;
    ret_val = osal_msgqueue_send(control_mbf_id, &control_msg, sizeof(control_msg_t), 0);
    if (E_OK != ret_val)
    {
        if (if_clear_buffer)
        {
            ap_clear_all_message();
            ret_val = osal_msgqueue_send(control_mbf_id, &control_msg, sizeof(control_msg_t), 0);
        }
        else
        {
        	return FALSE;//lose the msg.
        }
    }

    return TRUE;//ret_val;
}

static OSAL_ID INPUT_TASK_ID = OSAL_INVALID_ID;
#define KEY_DETECT_INTERVAL     100
static BOOL     enable_key_task_get_key = FALSE;    //g_key_task_get_key

BOOL ap_is_key_task_get_key(void)
{
    return enable_key_task_get_key;
}

BOOL ap_enable_key_task_get_key(BOOL enable)
{
    BOOL    old_value = enable_key_task_get_key;

    enable_key_task_get_key = enable;
    return old_value;
}

BOOL key_get_key(struct pan_key *key_struct, UINT32 timeout)
{
    struct pan_key *pan_key = NULL;

    pan_key = pan_get_key(g_pan_dev,timeout);

    if ( NULL == pan_key )
    {
        return FALSE;
    }

    MEMCPY(key_struct, pan_key, sizeof(struct pan_key));
    if (PAN_KEY_INVALID == key_struct->code)
    {
        return FALSE;
    }
    
    return TRUE;
}

UINT32 scan_code_to_msg_code(struct pan_key *key_struct)
{
    IR_KEY_INFO msg_code;

    ASSERT(4 == sizeof(IR_KEY_INFO));

    msg_code.type = key_struct->type;
    msg_code.state = key_struct->state;
    msg_code.count = key_struct->count;
    msg_code.ir_code = SET_IRCODE(key_struct->code);
    return *(UINT32 *) (&msg_code);
}

UINT32 ap_get_popup_msg(UINT32 flag)
{
    OSAL_ER             retval = E_FAILURE;
    control_msg_t        msg;
    UINT32              msg_siz = 0;
    UINT32              vkey = 0;

    MEMSET(&msg, 0x0, sizeof(control_msg_t));
    
    retval = ap_receive_msg(&msg, (INT32 *)&msg_siz, 100);
    if (OSAL_E_OK != retval)
    {
        return INVALID_MSG;
    }

    if (msg.msg_type <= CTRL_MSG_TYPE_KEY)
    {
        ap_hk_to_vk(0, msg.msg_code, &vkey);
        return msg.msg_code;
    }

    return INVALID_MSG;
    //ap_send_msg(msg.msg_type, msg.msg_code, TRUE);
    //return ap_get_popup_msg_ext(flag);
}

UINT32 ap_get_key_msg(void)
{
    return ap_get_popup_msg(0);
}

static void key_task(void)
{
    UINT32  ret= 0;
    UINT32  msg_code= 0;
    UINT32 hkey1 = INVALID_HK;
    board_cfg *cfg = NULL;
    struct pan_key key_struct;

    ret = 0;
    MEMSET(&key_struct, 0, sizeof(struct pan_key));
    while(1)
    {
        osal_task_sleep(KEY_DETECT_INTERVAL);
        
        if(ap_is_key_task_get_key() && key_get_key(&key_struct, 1))      
        {
            msg_code = scan_code_to_msg_code(&key_struct);
            
            ap_send_msg(CTRL_MSG_SUBTYPE_KEY, msg_code, FALSE);
        }
    }
}

UINT8 key_init(void)
{
    OSAL_T_CTSK t_ctsk;

    MEMSET(&t_ctsk, 0, sizeof(OSAL_T_CTSK));
    t_ctsk.stksz    =       INPUT_TASK_STACKSIZE * 4;
    t_ctsk.quantum  =   INPUT_TASK_QUANTUM;
    t_ctsk.itskpri  =       INPUT_TASK_PRIORITY;
    t_ctsk.name[0]  = 'K';
    t_ctsk.name[1]  = 'E';
    t_ctsk.name[2]  = 'Y';
    t_ctsk.task = (FP)key_task;

    INPUT_TASK_ID = osal_task_create(&t_ctsk);
    if(OSAL_INVALID_ID==INPUT_TASK_ID)
    {
        return FALSE;
    }

    return TRUE;
}
#endif

