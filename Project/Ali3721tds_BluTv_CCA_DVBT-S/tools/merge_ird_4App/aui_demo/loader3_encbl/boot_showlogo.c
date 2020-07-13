/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    bootloader.c
*
*    Description:    This file contains all globe micros and functions declare
*                    of Flash boot loader.
*    History:
*           Date            Athor        Version          Reason
*       ============    =============   =========   =================
*   1.  Oct.28.2003     Justin Wu       Ver 0.1    Create file.
 *  2.  2006.5.16       Justin Wu       Ver 0.2    STO chunk support & clean up.
*****************************************************************************/
#include <sys_config.h>
#include <sys_parameters.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <api/libchunk/chunk.h>
#include <bus/sci/sci.h>
#include <bus/flash/flash.h>
#include <hal/hal_gpio.h>
#include <hal/hal_mem.h>
#include <hld/pan/pan_dev.h>
#include <hld/smc/smc.h>
#include <hld/pan/pan.h>
#include <bus/i2c/i2c.h>
#include <bus/otp/otp.h>
#include <api/libloader/ld_boot_info.h>
#ifdef M3281_BOOT_WITH_LOGO
#include <hld/dis/vpo.h>
#include <hld/decv/decv.h>
#endif

#include "bootloader.h"

#ifdef M3281_BOOT_WITH_LOGO

#undef caddr_t
#define caddr_t         void*
extern caddr_t RAMSIZE;

#define  LOGO_ID_TYPE    0x02FD0000
#define  LOGO_ID              (LOGO_ID_TYPE | 0x0100)
#define  MENU_LOGO_ID   (LOGO_ID_TYPE | 0x0100)
#define  RADIO_LOGO_ID  (LOGO_ID_TYPE | 0x0100)
#define  MEDIA_LOGO_ID  (LOGO_ID_TYPE | 0x0100)
#define  BOOT_LOGO_ID    (LOGO_ID_TYPE | 0x0100)

static struct vdec_device*  g_decv_dev = NULL;
static struct vpo_device*   g_vpo_dev = NULL;
static struct vpo_device*   g_sd_vpo_dev = NULL;
static struct tve_adjust g_tve_adjust_table[] =
{
    {TVE_ADJ_COMPOSITE_Y_DELAY, SYS_625_LINE, 2},
    {TVE_ADJ_COMPOSITE_Y_DELAY, SYS_525_LINE, 3}, //3
    {TVE_ADJ_COMPOSITE_C_DELAY, SYS_625_LINE, 2},
    {TVE_ADJ_COMPOSITE_C_DELAY, SYS_525_LINE, 2}, //3
    {TVE_ADJ_COMPONENT_Y_DELAY, SYS_625_LINE, 0x3},
    {TVE_ADJ_COMPONENT_Y_DELAY, SYS_525_LINE, 0x4}, //3
    {TVE_ADJ_COMPONENT_CB_DELAY, SYS_625_LINE, 2},
    {TVE_ADJ_COMPONENT_CB_DELAY, SYS_525_LINE, 1}, //2
    {TVE_ADJ_COMPONENT_CR_DELAY, SYS_625_LINE, 0},
    {TVE_ADJ_COMPONENT_CR_DELAY, SYS_525_LINE, 3}, //2
    {TVE_ADJ_BURST_LEVEL_ENABLE, SYS_625_LINE, 1},
    {TVE_ADJ_BURST_LEVEL_ENABLE, SYS_525_LINE, 0}, //1
    {TVE_ADJ_BURST_CB_LEVEL, SYS_625_LINE, 0x8d},
    {TVE_ADJ_BURST_CB_LEVEL, SYS_525_LINE, 0x70},
    {TVE_ADJ_BURST_CR_LEVEL, SYS_625_LINE, 0x58},
    {TVE_ADJ_BURST_CR_LEVEL, SYS_525_LINE, 0x82}, //8 bits
    {TVE_ADJ_COMPOSITE_LUMA_LEVEL, SYS_625_LINE, 0x50},
    {TVE_ADJ_COMPOSITE_LUMA_LEVEL, SYS_525_LINE, 0x4b}, //8 bits
    {TVE_ADJ_COMPOSITE_CHRMA_LEVEL, SYS_625_LINE, 0x04},
    {TVE_ADJ_COMPOSITE_CHRMA_LEVEL, SYS_525_LINE, 0x05}, //8 bits
    {TVE_ADJ_PHASE_COMPENSATION, SYS_625_LINE, 0x3D0},
    {TVE_ADJ_PHASE_COMPENSATION, SYS_525_LINE, 0xAA}, //16 bits
    {TVE_ADJ_VIDEO_FREQ_RESPONSE, SYS_625_LINE, 0x0},
    {TVE_ADJ_VIDEO_FREQ_RESPONSE, SYS_525_LINE, 0x0}, //16 bits
};

static struct tve_adjust tve_adjust_table_adv[] =
{
    {TVE_ADJ_ADV_PEDESTAL_ONOFF, SYS_625_LINE, 0},
    {TVE_ADJ_ADV_PEDESTAL_ONOFF, SYS_525_LINE, 1},
    {TVE_ADJ_ADV_COMPONENT_LUM_LEVEL, SYS_625_LINE, 0x52},
    {TVE_ADJ_ADV_COMPONENT_LUM_LEVEL, SYS_525_LINE, 0x4D},
    {TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL, SYS_625_LINE, 0x4f},
    {TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL, SYS_525_LINE, 0x50},
    {TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL, SYS_625_LINE, 0x0},
    {TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL, SYS_525_LINE, 0x9},
    {TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL, SYS_625_LINE, 0x0},
    {TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL, SYS_525_LINE, 0x0},
    {TVE_ADJ_ADV_RGB_R_LEVEL, SYS_625_LINE, 0x8d},
    {TVE_ADJ_ADV_RGB_R_LEVEL, SYS_525_LINE, 0x8d},
    {TVE_ADJ_ADV_RGB_G_LEVEL, SYS_625_LINE, 0x8d},
    {TVE_ADJ_ADV_RGB_G_LEVEL, SYS_525_LINE, 0x8d},
    {TVE_ADJ_ADV_RGB_B_LEVEL, SYS_625_LINE, 0x8d},
    {TVE_ADJ_ADV_RGB_B_LEVEL, SYS_525_LINE, 0x8d},
    {TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL, SYS_625_LINE, 0x0},
    {TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL, SYS_525_LINE, 0x28},
    {TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL, SYS_625_LINE, 0x0},
    {TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL, SYS_525_LINE, 0x7},
};
static void api_scart_aspect_callback ( UINT8 b_widescr )
{
        do
        {
                NULL;
        }
        while ( 0 );
}

static void av_start ( void )
{
        struct vdec_pipinfo v_init_info;
        struct mpsource_call_back v_mpcall_back;
        struct pipsource_call_back v_pipcall_back;
        struct vp_win_config_para win_para;

        vdec_profile_level ( g_decv_dev, MP_HL, NULL );
        enum tvsystem  tvsys;
        vpo_ioctl ( g_vpo_dev, VPO_IO_GET_OUT_MODE, ( UINT32 ) &tvsys );

        v_init_info.adv_setting.init_mode = 0;
        v_init_info.adv_setting.out_sys = tvsys;

        vdec_set_output ( g_decv_dev, MP_MODE, &v_init_info, &v_mpcall_back, &v_pipcall_back );
        vpo_win_mode ( g_vpo_dev, VPO_MAINWIN, &v_mpcall_back, &v_pipcall_back );

        vdec_sync_mode ( g_decv_dev, VDEC_SYNC_FREERUN, VDEC_SYNC_I | VDEC_SYNC_P | VDEC_SYNC_B );
}

static void init_vppara ( struct vp_init_info *p_vpinit_info )
{
        int i;

        //api set backgound color]
        p_vpinit_info->t_init_color.u_y = 0x10;
        p_vpinit_info->t_init_color.u_cb = 0x80;
        p_vpinit_info->t_init_color.u_cr = 0x80;

        //set advanced control
        p_vpinit_info->b_brightness_value = 0;
        p_vpinit_info->f_brightness_value_sign = TRUE;
        p_vpinit_info->w_contrast_value = 0;
        p_vpinit_info->f_contrast_sign = TRUE;
        p_vpinit_info->w_saturation_value = 0;
        p_vpinit_info->f_saturation_value_sign = TRUE;
        p_vpinit_info->w_sharpness = 0;
        p_vpinit_info->f_sharpness_sign = TRUE;
        p_vpinit_info->w_hue_sin = 0;
        p_vpinit_info->f_hue_sin_sign = TRUE;
        p_vpinit_info->w_hue_cos = 0;
        p_vpinit_info->f_hue_cos_sign = TRUE;
        p_vpinit_info->b_ccir656enable = FALSE;
        //VPO_Zoom
        p_vpinit_info->t_src_rect.u_start_x = 0;
        p_vpinit_info->t_src_rect.u_width = PICTURE_WIDTH;
        p_vpinit_info->t_src_rect.u_start_y = 0;
        p_vpinit_info->t_src_rect.u_height = PICTURE_HEIGHT;
        p_vpinit_info->dst_rect.u_start_x = 0;
        p_vpinit_info->dst_rect.u_width = SCREEN_WIDTH;
        p_vpinit_info->dst_rect.u_start_y = 0;
        p_vpinit_info->dst_rect.u_height = SCREEN_HEIGHT;

        //VPO_SetAspect
        p_vpinit_info->e_tvaspect = TV_4_3;
        p_vpinit_info->e_display_mode = NORMAL_SCALE;//LETTERBOX;
        p_vpinit_info->u_nonlinear_change_point = 111;
        p_vpinit_info->u_pan_scan_offset = 90;
        //VPO_SetOutput
        for ( i = 0; i < VP_DAC_TYPENUM; i++ )
                p_vpinit_info->p_dac_config[i].b_enable = FALSE;

        p_vpinit_info->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = TRUE;
        p_vpinit_info->p_dac_config[VDAC_USE_CVBS_TYPE].t_dac_index.u_dac_first = CVBS_DAC;
        p_vpinit_info->p_dac_config[VDAC_USE_CVBS_TYPE].e_vgamode = VGA_NOT_USE;
        p_vpinit_info->p_dac_config[VDAC_USE_CVBS_TYPE].b_progressive = FALSE;

        p_vpinit_info->p_dac_config[YUV_1].b_enable = TRUE;
        p_vpinit_info->p_dac_config[YUV_1].t_dac_index.u_dac_first = YUV_DAC_Y;
        p_vpinit_info->p_dac_config[YUV_1].t_dac_index.u_dac_second = YUV_DAC_U;
        p_vpinit_info->p_dac_config[YUV_1].t_dac_index.u_dac_third = YUV_DAC_V;
        p_vpinit_info->p_dac_config[YUV_1].e_vgamode = VGA_NOT_USE;
        p_vpinit_info->p_dac_config[YUV_1].b_progressive = FALSE;

        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].b_enable = TRUE;
        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].t_dac_index.u_dac_first = RGB_DAC_R;
        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].t_dac_index.u_dac_second = RGB_DAC_G;
        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].t_dac_index.u_dac_third = RGB_DAC_B;
        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].e_vgamode = VGA_NOT_USE;
        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].b_progressive = FALSE;

        p_vpinit_info->e_tvsys = PAL;
        p_vpinit_info->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = TRUE;
        p_vpinit_info->p_dac_config[VDAC_USE_YUV_TYPE].b_enable = FALSE;
        p_vpinit_info->p_dac_config[VDAC_USE_RGB_TYPE].b_enable = TRUE;

        p_vpinit_info->b_win_on_off = FALSE;
        p_vpinit_info->u_win_mode = VPO_MAINWIN;//|VPO_PIPWIN;
        p_vpinit_info->t_pipcall_back.request_callback = NULL;
        p_vpinit_info->t_pipcall_back.release_callback = NULL;
        p_vpinit_info->p_src_change_call_back = NULL;
}

static RET_CODE av_init ( void )
{
    struct vp_init_info t_vpinit_info;
    UINT32 ret = RET_FAILURE;

    g_vpo_dev = ( struct vpo_device * ) dev_get_by_id ( HLD_DEV_TYPE_DIS, 0 );
    g_decv_dev = ( struct vdec_device * ) dev_get_by_id ( HLD_DEV_TYPE_DECV, 0 );
    FIXED_PRINTF ( "%s line %d,g_vpo_dev = 0x%08x,g_decv_dev = 0x%08x\n",
                    __func__, __LINE__, ( UINT32 ) g_vpo_dev, ( UINT32 ) g_decv_dev );

    ret = vdec_open ( g_decv_dev );
    if( RET_SUCCESS != ret)
    {
       FIXED_PRINTF ( "%s vdec_open fail, g_decv_dev = 0x%08x\n",
                        __FUNCTION__, g_decv_dev);
       return RET_FAILURE;
    }

    init_vppara ( &t_vpinit_info );
    ret = vpo_open ( g_vpo_dev, &t_vpinit_info );
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF ( "%s vpo_open fail, g_vpo_dev = 0x%08x\n",
                        __FUNCTION__, g_vpo_dev);
       return RET_FAILURE;
    }
    ret = vpo_ioctl ( g_vpo_dev, VPO_IO_SWAFD_ENABLE, TRUE );
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF ( "[%s] vpo_ioctl :0x%x fail, \n",
                        __FUNCTION__, (UINT32)VPO_IO_SWAFD_ENABLE);
       return RET_FAILURE;
    }

    ret = vpo_ioctl ( g_vpo_dev, VPO_IO_SET_LAYER_ORDER, MP_GMAS_GMAF_AUXP );
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF ( "[%s] vpo_ioctl :0x%x fail, \n",
                        __FUNCTION__, (UINT32)VPO_IO_SET_LAYER_ORDER);
       return RET_FAILURE;
    }

    ret = vpo_ioctl ( g_vpo_dev, VPO_IO_PILLBOX_CUT_FLAG, 0 );
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF ( "[%s] vpo_ioctl :0x%x fail, \n",
                        __FUNCTION__, (UINT32)VPO_IO_PILLBOX_CUT_FLAG);
       return RET_FAILURE;
    }

    return RET_SUCCESS;
}

static void vpo_dev_attach ( void )
{
    struct vp_feature_config vp_config;
    struct tve_feature_config tve_config;
    struct vdec_config_par vdec_config_par;

    MEMSET ( ( void * ) &vp_config, 0, sizeof ( struct vp_feature_config ) );
    MEMSET ( ( void * ) &tve_config, 0, sizeof ( struct tve_feature_config ) );

    vp_config.b_avoid_mosaic_by_freez_scr = FALSE;    /* macro VDEC_AVOID_MOSAIC_BY_FREEZE_SCR */

    vp_config.b_mheg5enable = FALSE;              /* macro  _MHEG5_SUPPORT_ */

    vp_config.b_osd_mulit_layer = TRUE;//FALSE;      /* macro OSD_MULTI_LAYER */
    vp_config.b_overshoot_solution = FALSE;         /* macro VIDEO_OVERSHOOT_SOLUTION */
    vp_config.b_p2ndisable_maf = FALSE; //TRUE;
    vp_config.b_support_extra_win = FALSE;//TRUE;    /* macro VIDEO_SUPPORT_EXTRA_DVIEW_WINDOW */

    /* macro VIDEO_ADPCM_ONOFF(VIDEO_ADPCM_ON:TRUE VIDEO_ADPCM_OFF:FALSE) */
    vp_config.b_adpcmenable = FALSE;
    vp_config.p_mpget_mem_info = NULL;


    //api_Scart_Aspect_Switch;
    vp_config.p_src_asp_ratio_change_call_back = api_scart_aspect_callback;


    tve_config.config = YUV_SMPTE | TVE_TTX_BY_VBI; //|TVE_NEW_CONFIG;

    tve_config.tve_adjust = g_tve_adjust_table;
    vpo_m33_attach ( &vp_config, &tve_config );
    tve_advance_config ( tve_adjust_table_adv );

}

static void vdec_dev_attach ( void )
{
    struct vdec_config_par vdec_config_par;
    MEMSET ( ( void * ) &vdec_config_par, 0, sizeof ( struct vdec_config_par ) );

    vdec_config_par.mem_map.frm0_y_size  = __MM_FB_LEN;
    vdec_config_par.mem_map.frm0_c_size = 0;
    vdec_config_par.mem_map.frm1_y_size  = 0;
    vdec_config_par.mem_map.frm1_c_size = 0;
    vdec_config_par.mem_map.frm2_y_size = 0;
    vdec_config_par.mem_map.frm2_c_size = 0;

     /*coship need to use this FB buffer start address as its own heap top address in bootloader.*/
    vdec_config_par.mem_map.frm0_y_start_addr = __MM_FB_START_ADDR;
    //so the avaliable malloc range is[0x808xxxxx + sizeof(.booloader),__MM_FB_START_ADDR]
    vdec_config_par.mem_map.frm0_c_start_addr = 0; //about 10~11M heap space avaliable.need change alloc.c RAM_SIZE.
    vdec_config_par.mem_map.frm1_y_start_addr = 0;
    vdec_config_par.mem_map.frm1_c_start_addr = 0;
    vdec_config_par.mem_map.frm2_y_start_addr = 0;
    vdec_config_par.mem_map.frm2_c_start_addr = 0;


    vdec_config_par.mem_map.dvw_frm_size = 0;
    vdec_config_par.mem_map.dvw_frm_start_addr = 0;

    vdec_config_par.mem_map.maf_size = __MM_MAF_LEN;
    vdec_config_par.mem_map.maf_start_addr = __MM_MAF_START_ADDR;    //see address so won`t effect coship malloc.
    vdec_config_par.mem_map.ext_maf_buf1 = __MM_DEVOUR_START_ADDR;                  //
    vdec_config_par.mem_map.ext_maf_buf2 = __MM_DEVOUR_START_ADDR + 0xd00;  //

    vdec_config_par.mem_map.vbv_size = ( ( __MM_VBV_LEN - 4 ) & 0xFFFFFF00 );
    vdec_config_par.mem_map.vbv_start_addr = ( ( __MM_VBV_START_ADDR & 0xfffffff ) | 0x80000000 );
    vdec_config_par.mem_map.vbv_end_addr = ( ( vdec_config_par.mem_map.vbv_start_addr ) +  \
                                             vdec_config_par.mem_map.vbv_size - 1 );

    vdec_config_par.user_data_parsing = TRUE; /* macro USER_DATA_PARSING */
    vdec_config_par.dtg_afd_parsing = TRUE;     //SUPPORT_AFD_SCALE
    vdec_config_par.drop_freerun_pic_before_firstpic_show = FALSE; /* macro VDEC27_DROP_FREERUN_BEFORE_FIRSTSHOW */
    vdec_config_par.reset_hw_directly_when_stop = TRUE;  /* macro VDEC27_STOP_REST_HW_DIRECTLY*/
    vdec_config_par.show_hd_service = FALSE;      /* macro SUPPORT_SHOW_HD_SERVICE */
    vdec_config_par.still_frm_in_cc = FALSE;          /* macro STILL_FRAME_IN_CC */
    vdec_config_par.not_show_mosaic = FALSE;      /* macro VDEC_AVOID_MOSAIC_BY_FREEZE_SCR */
    vdec_config_par.adpcm.adpcm_mode = FALSE;  /* macro VIDEO_ADPCM_ONOFF(VIDEO_ADPCM_ON:TRUE VIDEO_ADPCM_OFF:FALSE)*/
    vdec_config_par.adpcm.adpcm_ratio = 0;

    /* macro VDEC27_SML_FRM_ONOFF(VDEC27_SML_FRM_OFF: FALSE   VDEC27_SML_FRM_ON: TRUE)*/
    vdec_config_par.sml_frm.sml_frm_mode = FALSE;
    vdec_config_par.return_multi_freebuf = TRUE;        /* macro VDEC27_SUPPORT_RETURN_MULTI_FREEBUF */
    vdec_config_par.sml_frm.sml_frm_size = 0;           /* macro VDEC27_SML_FRM_SIZE*/
    vdec_config_par.lm_shiftthreshold = 2;                   /* macro VDEC27_LM_SHIFTTHRESHOLD*/
    vdec_config_par.vp_init_phase = 0;                        /* macro DEFAULT_MP_FILTER_ENABLE*/

    /* macro VDEC27_PREVIEW_SOLUTION(VDEC27_PREVIEW_VE_SCALE or VDEC27_PREVIEW_DE_SCALE)*/
    vdec_config_par.preview_solution = VDEC27_PREVIEW_DE_SCALE;
    vdec_m36_attach ( &vdec_config_par );
}

static UINT8 api_get_chunk_add_len ( UINT32 id, UINT32* addr, UINT32* len )
{
    INT32 ret;
    CHUNK_HEADER chuck_hdr;

    ret = sto_get_chunk_header ( id, &chuck_hdr );
    if ( ret == 0 )
            return 0;

    *addr = ( UINT32 ) sto_chunk_goto ( &id, 0xFFFFFFFF, 1 ) + CHUNK_HEADER_SIZE;
    *len = chuck_hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME;

    return 1;
}

static void api_show_bootup_logo ( void )
{
    int i;
    void* p_write_buffer;
    UINT32 u_size_got;
    RET_CODE ret_code;
    UINT32 logo_id, addr, len;
    struct sto_device *sto_flash_dev;
    UINT8 *logo_buf;

    logo_id = BOOT_LOGO_ID;
    if ( api_get_chunk_add_len ( logo_id, &addr, &len ) == 0 )
            return;
    logo_buf = ( UINT8 * ) MALLOC ( len );
    if(NULL == logo_buf)
        return;
    ret_code = vdec_start ( ( struct vdec_device * ) dev_get_by_id ( HLD_DEV_TYPE_DECV, 0 ) );
    sto_flash_dev = ( struct sto_device * ) dev_get_by_id ( HLD_DEV_TYPE_STO, 0 );

    for ( i = 0; i < 2; i++ )
    {
    #ifdef DUAL_ENABLE
        sto_get_data(sto_flash_dev, (UINT8 *)logo_buf, addr, len);
        vdec_copy_data((UINT32)g_decv_dev,(UINT32)logo_buf,len,&u_size_got);
    #else
        ret_code = vdec_vbv_request(g_decv_dev, len, &p_write_buffer,&u_size_got,NULL);
        sto_get_data(sto_flash_dev, (UINT8 *)p_write_buffer, addr, u_size_got);
        vdec_vbv_update((UINT32)g_decv_dev, u_size_got);
    #endif
    }

    FREE ( logo_buf );
}

static void video_dev_close ( void )
{
    struct  ycb_cr_color bgcolor;
    if ( g_vpo_dev )
            vpo_win_onoff ( g_vpo_dev, FALSE );

    bgcolor.u_y = 16;
    bgcolor.u_cb = 128;
    bgcolor.u_cr = 128;

    if ( g_vpo_dev )
            vpo_ioctl ( g_vpo_dev, VPO_IO_SET_BG_COLOR, ( UINT32 ) &bgcolor );
    if ( g_decv_dev )
            vdec_close ( g_decv_dev );
}


void see_heap_top_set()
{
    hld_dev_see_init ( __MM_SEE_DBG_MEM_ADDR );
}

RET_CODE bl_show_logo_init(void)
{
    UINT32 ret = RET_FAILURE ;

   /*be aware __MM_SEE_DBG_MEM_ADDR = 0xa1e5b400,
   * as see heaptop when with logo.
   */
    see_heap_top_set ();

    vpo_dev_attach();
    vdec_dev_attach();
    ret = av_init();
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF ( "[%s] avInit fail \n",__FUNCTION__);
       return RET_FAILURE;
    }
    av_start();
    api_show_bootup_logo();
    return RET_SUCCESS;
}
void bl_show_logo_close(void)
{
    video_dev_close();
}

#endif


