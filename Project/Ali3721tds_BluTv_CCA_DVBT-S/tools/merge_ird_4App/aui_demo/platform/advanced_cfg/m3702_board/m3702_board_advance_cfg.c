/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: m3503_board_advance_cfg.c
*
*    Description: Advance config of M3503 board
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#include "../advanced_cfg.h"
#include <bus/otp/otp.h>
#include <hld/vbi/vbi.h>
#include <hld/sdec/sdec.h>
#include <api/libclosecaption/lib_closecaption.h>
#include <hld/smc/smc.h>
#include "../../../platform/board.h"
#if defined _C0200A_CA_ENABLE_ || defined _BC_AUI_
#include <aui_dmx.h>
#endif

#ifdef ALICAST_SUPPORT
#include <api/libwfd/nmp_hdcp2.h>
#endif
/*********************************************************************************************************************/

extern INT32 isdbtcc_dec_attach(struct sdec_feature_config * cfg_param);
extern void isdbtcc_disply_init(struct sdec_device *dev);

static advance_cfg_para g_cfg_para;
advance_cfg_para *get_board_advance_cfg(void)
{
    return &g_cfg_para;
}

#ifdef HDTV_SUPPORT
static void avc_attach(void)
{
#ifndef _BUILD_OTA_E_
    struct vdec_avc_config_par vdec_avc_cfg;

    MEMSET(&vdec_avc_cfg, 0, sizeof(struct vdec_avc_config_par));
    vdec_avc_cfg.max_additional_fb_num = MAX_EXTRA_FB_NUM;
    vdec_avc_cfg.memmap.support_multi_bank = g_cfg_para.h264_support_mulit_bank;  //H264_SUPPORT_MULTI_BANK
 /*   if(g_cfg_para.chanchg_video_type_support)                                     //CHANCHG_VIDEOTYPE_SUPPORT
    {
        vdec_avc_cfg.memmap.support_conti_memory = 0;
        if(vdec_avc_cfg.memmap.support_conti_memory==0)
        {
            vdec_avc_cfg.memmap.frame_buffer_base = AVC_FB_ADDR;
            vdec_avc_cfg.memmap.frame_buffer_len = AVC_FB_LEN;
            vdec_avc_cfg.memmap.dv_frame_buffer_base = AVC_DVIEW_ADDR;
            vdec_avc_cfg.memmap.dv_frame_buffer_len = AVC_DVIEW_LEN;
            vdec_avc_cfg.memmap.mv_buffer_base = AVC_MV_ADDR;
            vdec_avc_cfg.memmap.mv_buffer_len = AVC_MV_LEN;
            vdec_avc_cfg.memmap.mb_col_buffer_base = AVC_MB_COL_ADDR;
            vdec_avc_cfg.memmap.mb_col_buffer_len = AVC_MB_COL_LEN;
            vdec_avc_cfg.memmap.mb_neighbour_buffer_base = AVC_MB_NEI_ADDR;
            vdec_avc_cfg.memmap.mb_neighbour_buffer_len = AVC_MB_NEI_LEN;
            vdec_avc_cfg.memmap.cmd_queue_buffer_base = AVC_CMD_QUEUE_ADDR;
            vdec_avc_cfg.memmap.cmd_queue_buffer_len = AVC_CMD_QUEUE_LEN;
            //vdec_avc_cfg.memmap.vbv_buffer_base = 0x84000000;
            //vdec_avc_cfg.memmap.vbv_buffer_len = 0x1000000;
            //  vdec_avc_cfg.memmap.vbv_buffer_base = (0xa7000000);//(AVC_VBV_ADDR & 0x0fffffff) | 0x80000000;
            // vdec_avc_cfg.memmap.vbv_buffer_len = 0x400000; //AVC_VBV_LEN;
            vdec_avc_cfg.memmap.vbv_buffer_base = (AVC_VBV_ADDR & 0x0fffffff) | 0x80000000;
            vdec_avc_cfg.memmap.vbv_buffer_len = 0x300000;
            vdec_avc_cfg.memmap.laf_rw_buf = AVC_LAF_RW_BUF_ADDR;
            vdec_avc_cfg.memmap.laf_rw_buffer_len = AVC_LAF_RW_BUF_LEN;
            vdec_avc_cfg.memmap.laf_flag_buf = AVC_LAF_FLAG_BUF_ADDR;
            vdec_avc_cfg.memmap.laf_flag_buffer_len = AVC_LAF_FLAG_BUF_LEN;
        }
        else
        {
            vdec_avc_cfg.memmap.vbv_buffer_base = (AVC_VBV_ADDR & 0x0fffffff) | 0x80000000;
            vdec_avc_cfg.memmap.vbv_buffer_len = 0x300000;
            vdec_avc_cfg.memmap.cmd_queue_buffer_base = vdec_avc_cfg.memmap.vbv_buffer_base - AVC_CMD_QUEUE_LEN;
            vdec_avc_cfg.memmap.cmd_queue_buffer_len = AVC_CMD_QUEUE_LEN;
            vdec_avc_cfg.memmap.mb_col_buffer_base = vdec_avc_cfg.memmap.cmd_queue_buffer_base - AVC_MB_COL_LEN;
            vdec_avc_cfg.memmap.mb_col_buffer_len = AVC_MB_COL_LEN;
            vdec_avc_cfg.memmap.mb_neighbour_buffer_base = vdec_avc_cfg.memmap.mb_col_buffer_base - AVC_MB_NEI_LEN;
            vdec_avc_cfg.memmap.mb_neighbour_buffer_len = AVC_MB_NEI_LEN;
            vdec_avc_cfg.memmap.avc_mem_len = AVC_MEM_LEN;
            vdec_avc_cfg.memmap.avc_mem_addr = vdec_avc_cfg.memmap.mb_neighbour_buffer_base - vdec_avc_cfg.memmap.avc_mem_len;
        }
    }
    else*/ if(g_cfg_para.avc_unify_mem_support)  //AVC_SUPPORT_UNIFY_MEM
    {
        vdec_avc_cfg.memmap.support_conti_memory = 1;
        vdec_avc_cfg.memmap.vbv_buffer_base = (AVC_VBV_ADDR & 0x0fffffff) | 0x80000000;
        vdec_avc_cfg.memmap.vbv_buffer_len = AVC_VBV_LEN;
    	vdec_avc_cfg.memmap.cmd_queue_buffer_base = (vdec_avc_cfg.memmap.vbv_buffer_base - AVC_CMD_QUEUE_LEN) | 0xa0000000;
        vdec_avc_cfg.memmap.cmd_queue_buffer_len = AVC_CMD_QUEUE_LEN;
    	vdec_avc_cfg.memmap.mb_col_buffer_base = vdec_avc_cfg.memmap.cmd_queue_buffer_base - AVC_MB_COL_LEN - AVC_MV_LEN;
    	vdec_avc_cfg.memmap.mb_col_buffer_len = AVC_MB_COL_LEN + AVC_MV_LEN;
        vdec_avc_cfg.memmap.mb_neighbour_buffer_base = vdec_avc_cfg.memmap.mb_col_buffer_base - AVC_MB_NEI_LEN;
        vdec_avc_cfg.memmap.mb_neighbour_buffer_len = AVC_MB_NEI_LEN;
        vdec_avc_cfg.memmap.avc_mem_len = AVC_MEM_LEN;
    	vdec_avc_cfg.memmap.avc_mem_addr = (vdec_avc_cfg.memmap.mb_neighbour_buffer_base - vdec_avc_cfg.memmap.avc_mem_len + 1023) & 0xfffffc00;
        vdec_avc_cfg.memmap.avc_mem_len = vdec_avc_cfg.memmap.mb_neighbour_buffer_base - vdec_avc_cfg.memmap.avc_mem_addr;
    }
    else
    {
        vdec_avc_cfg.memmap.frame_buffer_base = AVC_FB_ADDR;
        vdec_avc_cfg.memmap.frame_buffer_len = AVC_FB_LEN;
        vdec_avc_cfg.memmap.dv_frame_buffer_base = AVC_DVIEW_ADDR;
        vdec_avc_cfg.memmap.dv_frame_buffer_len = AVC_DVIEW_LEN;
        vdec_avc_cfg.memmap.mv_buffer_base = AVC_MV_ADDR;
        vdec_avc_cfg.memmap.mv_buffer_len = AVC_MV_LEN;
        vdec_avc_cfg.memmap.mb_col_buffer_base = AVC_MB_COL_ADDR;
        vdec_avc_cfg.memmap.mb_col_buffer_len = AVC_MB_COL_LEN;
        vdec_avc_cfg.memmap.mb_neighbour_buffer_base = AVC_MB_NEI_ADDR;
        vdec_avc_cfg.memmap.mb_neighbour_buffer_len = AVC_MB_NEI_LEN;
        vdec_avc_cfg.memmap.cmd_queue_buffer_base = AVC_CMD_QUEUE_ADDR;
        vdec_avc_cfg.memmap.cmd_queue_buffer_len = AVC_CMD_QUEUE_LEN;
        //vdec_avc_cfg.memmap.vbv_buffer_base = 0x84000000;
        //vdec_avc_cfg.memmap.vbv_buffer_len = 0x1000000;
        vdec_avc_cfg.memmap.vbv_buffer_base = (AVC_VBV_ADDR & 0x0fffffff) | 0x80000000;
        vdec_avc_cfg.memmap.vbv_buffer_len = AVC_VBV_LEN;
        vdec_avc_cfg.memmap.laf_rw_buf = AVC_LAF_RW_BUF_ADDR;
        vdec_avc_cfg.memmap.laf_rw_buffer_len = AVC_LAF_RW_BUF_LEN;
        vdec_avc_cfg.memmap.laf_flag_buf = AVC_LAF_FLAG_BUF_ADDR;
        vdec_avc_cfg.memmap.laf_flag_buffer_len = AVC_LAF_FLAG_BUF_LEN;

        #ifdef DYNAMIC_RESOLUTION_SUPPORT
        vdec_avc_cfg.memmap.support_conti_memory = 2;
        #endif

    /*  if(AVC_LAF_FLAG_BUF_ADDR < __MM_BUF_PVR_TOP_ADDR)
        {
            libc_printf("no enough buffer for AVC");
            ASSERT(0);
        }
    */
    }
/*  if(__MM_PVR_BFFUER_END < __MM_BUF_TOP_ADDR)
    {
        libc_printf("no enough buffer for stack __MM_PVR_BFFUER_END = 0x%x,__MM_BUF_TOP_ADDR = 0x%x\n",
            __MM_PVR_BFFUER_END,
            __MM_BUF_TOP_ADDR);
        ASSERT(0);
    }
*/
#ifndef _BUILD_OTA_E_
    //print_memory_layout();
#endif

    vdec_avc_cfg.dtg_afd_parsing = g_cfg_para.afd_scale_support;

    vdec_avc_attach(&vdec_avc_cfg);
#endif
}

#if 1
#ifndef _BUILD_OTA_E_
static char decv_hevc_name[] = {"DECV_HEVC_0"};
#endif

static void hevc_attach(void)
{
#ifndef _BUILD_OTA_E_
    struct vdec_hevc_config_par vdec_hevc_cfg;

    MEMSET(&vdec_hevc_cfg, 0, sizeof(struct vdec_hevc_config_par));

    vdec_hevc_cfg.max_additional_fb_num = MAX_EXTRA_FB_NUM;

    vdec_hevc_cfg.max_additional_fb_num = MAX_EXTRA_FB_NUM;
    vdec_hevc_cfg.memmap.support_multi_bank = g_cfg_para.h264_support_mulit_bank;  //H264_SUPPORT_MULTI_BANK
    vdec_hevc_cfg.memmap.support_conti_memory = 0;

    /* For seucre coding, use the Private Memory(AS) */
    vdec_hevc_cfg.memmap.vbv_buffer_base = HEVC_VBV_ADDR;
    vdec_hevc_cfg.memmap.vbv_buffer_len = HEVC_VBV_LEN - 256;
    vdec_hevc_cfg.memmap.ph_buffer_base = HEVC_PICTURE_SYNTAX_BUF_ADDR;
    vdec_hevc_cfg.memmap.ph_buffer_len = HEVC_PICTURE_SYNTAX_LEN;
    vdec_hevc_cfg.memmap.ep_cmd_queue_buffer_base = HEVC_EP_QUEUE_BUF_ADDR;
    vdec_hevc_cfg.memmap.ep_cmd_queue_buffer_len = HEVC_EP_QUEUE_LEN;
    vdec_hevc_cfg.memmap.md_cmd_queue_buffer_base = HEVC_CMD_QUEUE_BUF_ADDR;
    vdec_hevc_cfg.memmap.md_cmd_queue_buffer_len = HEVC_CMD_QUEUE_LEN;

    /* Use the Main Memory(AS) */
    vdec_hevc_cfg.memmap.mp_frame_buffer_base = HEVC_FB_ADDR;
    vdec_hevc_cfg.memmap.mp_frame_buffer_len = HEVC_FB_LEN;
    vdec_hevc_cfg.memmap.dv_frame_buffer_base = HEVC_DVIEW_ADDR;
    vdec_hevc_cfg.memmap.dv_frame_buffer_len = HEVC_DVIEW_LEN;
    vdec_hevc_cfg.memmap.collocated_mv_buffer_base = HEVC_MV_ADDR;
    vdec_hevc_cfg.memmap.collocated_mv_buffer_len = HEVC_MV_LEN;

    vdec_hevc_cfg.memmap.inner_es_buffer_base = HEVC_INNER_ES_ADDR;
    vdec_hevc_cfg.memmap.inner_es_buffer_len = HEVC_INNER_ES_LEN;
    vdec_hevc_cfg.memmap.inner_aux_buffer_base = HEVC_INNER_AUX_ADDR;
    vdec_hevc_cfg.memmap.inner_aux_buffer_len = HEVC_INNER_AUX_LEN;
    vdec_hevc_cfg.memmap.neighbour_buffer_base = HEVC_MB_NEI_ADDR;
    vdec_hevc_cfg.memmap.neighbour_buffer_len = HEVC_MB_NEI_LEN;
    vdec_hevc_cfg.memmap.laf_buffer_base = HEVC_LAF_ADDR;
    vdec_hevc_cfg.memmap.laf_buffer_len = HEVC_LAF_LEN;

#ifndef _BUILD_OTA_E_
    //print_memory_layout();
#endif
    vdec_hevc_cfg.decv_hevc_inst_name = decv_hevc_name;
    vdec_hevc_cfg.dtg_afd_parsing = g_cfg_para.afd_scale_support;

    vdec_hevc_attach(&vdec_hevc_cfg);
#endif
}
#endif

void get_hdmi_config(struct config_hdmi_parm *hdmi_param)
{
    if(NULL == hdmi_param)
        return;

    MEMSET(hdmi_param, 0, sizeof(struct config_hdmi_parm));

    hdmi_param->spd_vendor_name = (UINT8 *)"ALi Corp";
    hdmi_param->spd_product_desc = (UINT8 *)"M3602 HD STB";
    hdmi_param->i2c_for_eddc = g_cfg_para.i2c_for_eddc; //I2C_FOR_EDDC;    //I2C_TYPE_SCB2, I2C_TYPE_GPIO1
    hdmi_param->otp_ce_load_hdcp_key = FALSE;
    #if (defined (_GEN_CA_ENABLE_) || defined (_C1800A_CA_ENABLE_))
    hdmi_param->hdcp_disable = 1;//GEN CA HDMI force output.
    #else
    hdmi_param->hdcp_disable = g_cfg_para.hdcp_disable;
    #endif
    hdmi_param->boot_media = g_cfg_para.vpo_active;

    if(hdmi_param->hdcp_disable == FALSE)
    {
        hdmi_param->cm_scl = g_cfg_para.hdmi_cm_scl; //SYS_I2C_SCL2;
        hdmi_param->cm_sda = g_cfg_para.hdmi_cm_sda; //SYS_I2C_SDA2;

//        hdmi_param->hdcp_cstm_key = CUSTOMER_HDCP_KEY;     <=== CUSTOMER_HDCP_KEY is a 286 Bytes UINT8 arrary.
#ifndef HDCP_IN_FLASH    // Customer assigned HDCP Key from interface. (286 Bytes)
        hdmi_param->hdcp_cstm_key = NULL;//                     <=== if load key from external cryptomemory, please assign NULL to it.
        //hdmi_param->cm_scl = SYS_I2C_SCL2;
        //hdmi_param->cm_sda = SYS_I2C_SDA2;

        hdmi_param->cm_password = NULL;   // ALi Demo
        hdmi_param->cm_secretseed = NULL; // ALi Demo
#else
#ifdef HDCP_FROM_CE
        hdmi_param->otp_ce_load_hdcp_key = TRUE;
        hdmi_param->hdcp_cstm_key = NULL;//                     <=== if load key from external cryptomemory, please assign NULL to it.
        //hdmi_param->cm_scl = SYS_I2C_SCL2;
        //hdmi_param->cm_sda = SYS_I2C_SDA2;
        hdmi_param->cm_password = NULL;   // ALi Demo
        hdmi_param->cm_secretseed = NULL; // ALi Demo
#else
        hdmi_param->otp_ce_load_hdcp_key = FALSE; // For 3603 decrypt hdcp by otp root password, shuold assign TRUE
        {
            UINT8    *hdcp_internal_keys, all_is_0xff[286];
            UINT8    key1[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
            UINT8    key2[8] = {0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01};
            #ifdef C3041
            UINT8    key3[8] = {0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x01};
            #else
            UINT8    key3[8] = {0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23};
            #endif
            UINT8    plaintext[8];
            UINT16     i;
            UINT32 id = HDCPKEY_CHUNK_ID;
            UINT32 hdcp_chunk;

            //Load ALi licsensed key here from ATMEL Crypto memory
            hdcp_internal_keys = (UINT8 *)MALLOC(sizeof(UINT8)*286);
            if(NULL == hdcp_internal_keys )
            {
                ASSERT(0);
                return;
            }
            MEMSET(all_is_0xff, 0xff, 286);
            hdcp_chunk = (UINT32)sto_chunk_goto(&id,0xFFFFFFFF,1) ;
            if((UINT32)ERR_FAILUE == hdcp_chunk)
            {
                hdmi_param->hdcp_cstm_key = NULL;
                //hdmi_param->cm_scl = SYS_I2C_SCL2;
                //hdmi_param->cm_sda = SYS_I2C_SDA2;
                hdmi_param->cm_password = NULL;   // ALi Demo
                hdmi_param->cm_secretseed = NULL; // ALi Demo
            }
            else
            {
                sto_get_data( (struct sto_device *)dev_get_by_id(HLD_DEV_TYPE_STO, 0), hdcp_internal_keys,
                        hdcp_chunk+ CHUNK_HEADER_SIZE, 286);

                //hdmi_param->cm_scl = SYS_I2C_SCL2;
                //hdmi_param->cm_sda = SYS_I2C_SDA2;
                hdmi_param->cm_password = NULL;   // ALi Demo
                hdmi_param->cm_secretseed = NULL; // ALi Demo

                if(MEMCMP(hdcp_internal_keys, all_is_0xff, 286) == 0)
                {
                    // No HDCP Key in flash
                    hdmi_param->hdcp_cstm_key = NULL;
                }
                else
                {
                         // Skip the first 6 bytes. 0x00 + 5bytes KSV
                    for(i=6; i<286; i+=8)
                    {
                        triple_des_decryption(hdcp_internal_keys+i, plaintext, key1, key2, key3);
                        MEMCPY(hdcp_internal_keys+i, plaintext, 8);

                    #if 0
                        libc_printf("HDCP key: %08x,%08x\n",((UINT32*)plaintext)[0],((UINT32*)plaintext)[1]);
                    #endif
                     }
                    hdmi_param->hdcp_cstm_key = hdcp_internal_keys;
                }
            }
        }
#endif
#endif

    }
}

#endif

#ifdef ALICAST_SUPPORT
#define HDCP20KEY_CHUNK_ID 0x09F60200
 tReceiverKeySets g_H2KeySets;

void get_hdmi20_config(tReceiverKeySets *h2_KeySets)
{
	UINT8 *hdcp_internal_keys, all_is_0xff[858];
	UINT8 Key1[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
	UINT8 Key2[8] = {0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01};
	UINT8 Key3[8] = {0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23};
	UINT8 Plaintext[8];
	UINT16 i;
	UINT32 id = HDCP20KEY_CHUNK_ID;//HDCPKEY20_CHUNK_ID;
	UINT32 hdcp_chunk;

	MEMSET(h2_KeySets, 0, sizeof(tReceiverKeySets));

	//hdmi_param->hdcp_cstm_key = CUSTOMER_HDCP_KEY;	 <=== CUSTOMER_HDCP_KEY is a 286 Bytes UINT8 arrary.
	//Load ALi licsensed key here from ATMEL Crypto memory
	hdcp_internal_keys = (UINT8 *)MALLOC(sizeof(UINT8)*858);
	memset(all_is_0xff, 0xff, 858);
	hdcp_chunk = (UINT32)sto_chunk_goto(&id,0xFFFFFFFF,1) ;

	sto_get_data( (struct sto_device *)dev_get_by_id(HLD_DEV_TYPE_STO, 0), hdcp_internal_keys,hdcp_chunk+ CHUNK_HEADER_SIZE, 858);
	if(MEMCMP(hdcp_internal_keys, all_is_0xff, 858) == 0)
	{
		// No HDCP Key in flash
		//hdmi_param->hdcp_cstm_key = NULL;
	}
	else
	{
		for(i=0; i<856; i+=8)//last remain 2 bytes ,it don't decrypt
		{
			triple_des_decryption(hdcp_internal_keys+i, Plaintext, Key1, Key2, Key3);
			memcpy(hdcp_internal_keys+i, Plaintext, 8);
		 }

		memcpy( &h2_KeySets->lc,&hdcp_internal_keys[0] , 16 );
		memcpy( &h2_KeySets->rxPubKeyCert,&hdcp_internal_keys[16] , 522 );
		memcpy( &h2_KeySets->kPrivRx,&hdcp_internal_keys[538] , 320 );
		//hdmi_param->hdcp_cstm_key = hdcp_internal_keys;
	}
}
#endif

static void deca_dev_attach(void)
{
#ifndef _BUILD_OTA_E_
    extern void deca_m36_attach(struct deca_feature_config *config);
    extern void deca_m36_ext_dec_enable(struct deca_device*dev, struct deca_feature_config  *config);
    extern void deca_m36_ext_dec_enable2(struct deca_device*dev, struct deca_feature_config  *config);
    extern void deca_m36_dvr_enable(struct deca_device*dev);

    struct deca_feature_config deca_config;
    MEMSET(&deca_config, 0, sizeof(struct deca_feature_config));
    deca_config.support_desc = g_cfg_para.audio_description_support;
    if(deca_config.support_desc)
    {
        deca_config.ad_static_mem_flag = 1;
        deca_config.ad_static_mem_addr = __MM_OSD_BK_ADDR2;
        deca_config.ad_static_mem_size = __MM_SEE_OSD2_LEN;
    }
    /* support dynamic sample rate change by default*/
    deca_config.detect_sprt_change = 1;
#ifdef _DD_SUPPORT
    deca_config.priv_dec_addr = __MM_PRIV_DEC_ADDR;
    deca_config.priv_dec_size = __MM_PRIV_DEC_LEN;
#endif

#if (defined(__MM_STILL_PICTURE_MEM_ADDR) && defined(__MM_STILL_PICTURE_MEM_LEN))
    deca_config.pcm_ring_buff_start = __MM_STILL_PICTURE_MEM_ADDR;
	deca_config.pcm_ring_buff_len = __MM_STILL_PICTURE_MEM_LEN;
#endif

    deca_m36_attach(&deca_config);
    deca_m36_ext_dec_enable((struct deca_device * )dev_get_by_id(HLD_DEV_TYPE_DECA, 0), &deca_config);
    deca_m36_ext_dec_enable2((struct deca_device *)dev_get_by_id(HLD_DEV_TYPE_DECA, 0), &deca_config);
#ifdef DVR_PVR_SUPPORT
    deca_m36_dvr_enable((struct deca_device*)dev_get_by_id(HLD_DEV_TYPE_DECA, 0));
#endif
#endif
}

static void snd_dev_attach(void)
{
#ifndef _BUILD_OTA_E_
    extern void snd_m36g_attach(struct snd_feature_config  *config);

     struct snd_feature_config snd_config;
     MEMSET(&snd_config, 0, sizeof(struct snd_feature_config));
    snd_config.output_config.mute_num = g_cfg_para.sys_mute_gpio;
    snd_config.output_config.mute_polar     = g_cfg_para.sys_mute_polar;
    snd_config.output_config.mute_ext_gpio_clock = g_cfg_para.sys_mute_gpio_clock;
    snd_config.output_config.mute_ext_gpio_data  =  g_cfg_para.sys_mute_gpio_data;
    snd_config.output_config.dac_precision = 24;
    snd_config.output_config.dac_format     = CODEC_I2S;
    snd_config.output_config.is_ext_dac     = 0;
    snd_config.output_config.ext_mute_mode = g_cfg_para.ext_mute_mode;
    snd_config.support_spdif_mute = 1;
    snd_config.output_config.chip_type_config = g_cfg_para.snd_output_chip_type; //QFP
    snd_config.support_desc = g_cfg_para.audio_description_support;
    snd_config.conti_clk_while_ch_chg = 1;

#ifdef SUPPORT_AUDIO_DELAY
    snd_config.support_desc |= SND_SUPPORT_DDPLUS;
#endif

    snd_m36g_attach(&snd_config);
#endif
}

static void dmx_dev_general_attach(void)
{
    struct dmx_pre_attach_param dmx_pre_attach;
    struct dmx_feature_config dmx_config;

    MEMSET(&dmx_config, 0, sizeof(struct dmx_feature_config));
    MEMSET(&dmx_pre_attach, 0, sizeof(struct dmx_pre_attach_param));

    dmx_config.mm_map.dmx0_dma_buf = __MM_DMX_AVP_START_ADDR;
    dmx_config.mm_map.dmx1_dma_buf = __MM_DMX_REC_START_ADDR;
    dmx_config.mm_map.ts_audio_cb_len = (__MM_DMX_AUDIO_LEN/188);
    dmx_config.mm_map.ts_video_cb_len = (__MM_DMX_VIDEO_LEN/188);
    dmx_config.mm_map.ts_pcr_cb_len = (__MM_DMX_PCR_LEN/188);
    dmx_config.mm_map.ts_ttx_cb_len = (__MM_DMX_DATA_LEN/188);
    dmx_config.mm_map.ts_common_cb_len = (__MM_DMX_SI_LEN/188);
#ifndef _BUILD_OTA_E_
    dmx_config.mm_map.ts_united_cb_len = (__MM_DMX_REC_LEN/188);
#else
    dmx_config.mm_map.ts_united_cb_len = (0xBC000/188);//(__MM_DMX_REC_LEN/188);
#endif
    dmx_config.mm_map.total_pid_filt_num = (4+__MM_DMX_SI_TOTAL_LEN/__MM_DMX_SI_LEN);
//    dmx_config.video_bitrate_detect = 1;
    dmx_config.sync_times = 3;
    dmx_config.clock_polarity = 0;
    dmx_config.sync_mode = 1;
    dmx_pre_attach.my_size = sizeof(struct dmx_pre_attach_param);
    dmx_pre_attach.dmx_ts_blk_buf1 = __MM_DMX_CPU_BLK_ADDR;
    dmx_pre_attach.dmx_ts_blk_buf2 = __MM_DMX_SEE_BLK_ADDR;
    dmx_pre_attach.dmx_ts_blk_buf1_size = __MM_DMX_BLK_BUF_LEN;
    dmx_pre_attach.dmx_ts_blk_buf2_size = __MM_DMX_SEE_BLK_BUF_LEN;


#ifndef FPGA_TEST
    dma_init();
#endif
    dmx_m36f_pre_attach(&dmx_pre_attach);
    dmx_m36f_attach(&dmx_config);
#ifdef DVR_PVR_SUPPORT
    /*enable DVR feature. Only DVR proj can call this function, this function will enlarge dmx driver code size*/
    MEMSET(&dmx_config, 0, sizeof(struct dmx_feature_config));
    dmx_m36f_dvr_attach(&dmx_config);
#endif

    if(g_cfg_para.front_end_num > 1)
        dmx_api_enhance_attach(&dmx_config);
}

#ifdef FSC_SUPPORT
static void dmx_dev_fsc_attach(void)
{
    struct dmx_feature_config dmx_config;

    struct dmx_hw_param dmx_hw_param_list[DMX_HW_ATTACH_NUM];
    struct dmx_buf_param  dmx_dma_buf_list[DMX_HW_ATTACH_NUM];
    struct dmx_buf_param  main_blk_buf_list[DMX_HW_ATTACH_NUM];
    struct dmx_buf_param  see_blk_buf_list[1];

    MEMSET(&dmx_config, 0, sizeof(struct dmx_feature_config));
    MEMSET(&dmx_hw_param_list[0], 0, sizeof(struct dmx_hw_param)*DMX_HW_ATTACH_NUM);
    MEMSET(&main_blk_buf_list[0], 0, sizeof(struct dmx_buf_param)*DMX_HW_ATTACH_NUM);
    MEMSET(&see_blk_buf_list[0], 0, sizeof(struct dmx_buf_param)*1);

    dmx_hw_param_list[0].play_mode = DMX_GENERAL_PLAY;
    dmx_hw_param_list[0].dmx_type = DMX_TYPE_HW;
    dmx_hw_param_list[0].total_pid_filt_num  = (4+__MM_DMX_SI_TOTAL_LEN/__MM_DMX_SI_LEN);
    dmx_hw_param_list[0].dmx_id = 0;
    STRCPY(&dmx_hw_param_list[0].dmx_name[0], "DMX_S3601_0");
    dmx_hw_param_list[0].clock_polarity = 0;
    dmx_hw_param_list[0].sync_mode = 1;
    dmx_hw_param_list[0].sync_times = 3;
    #if (DMX_HW_ATTACH_NUM > 1)
    dmx_hw_param_list[1].play_mode = DMX_GENERAL_PLAY;
    dmx_hw_param_list[1].dmx_type = DMX_TYPE_HW;
    dmx_hw_param_list[1].total_pid_filt_num  = (4+__MM_DMX_SI_TOTAL_LEN/__MM_DMX_SI_LEN);
    dmx_hw_param_list[1].dmx_id = 1;
    STRCPY(&dmx_hw_param_list[1].dmx_name[0], "DMX_S3601_1");
    dmx_hw_param_list[1].clock_polarity = 0;
    dmx_hw_param_list[1].sync_mode = 1;
    dmx_hw_param_list[1].sync_times = 3;
    #endif
    #if (DMX_HW_ATTACH_NUM > 2)
    dmx_hw_param_list[2].play_mode = DMX_GENERAL_PLAY;
    dmx_hw_param_list[2].dmx_type = DMX_TYPE_HW;
    dmx_hw_param_list[2].total_pid_filt_num  = (4+__MM_DMX_SI_TOTAL_LEN/__MM_DMX_SI_LEN);
    dmx_hw_param_list[2].dmx_id = 3;        //
    STRCPY(&dmx_hw_param_list[2].dmx_name[0], "DMX_S3601_3");
    dmx_hw_param_list[2].clock_polarity = 0;
    dmx_hw_param_list[2].sync_mode = 1;
    dmx_hw_param_list[2].sync_times = 3;
    #endif
    #if (DMX_HW_ATTACH_NUM > 3)
    dmx_hw_param_list[3].play_mode = DMX_GENERAL_PLAY;
    dmx_hw_param_list[3].dmx_type = DMX_TYPE_HW;
    dmx_hw_param_list[3].total_pid_filt_num  = (4+__MM_DMX_SI_TOTAL_LEN/__MM_DMX_SI_LEN);
    dmx_hw_param_list[3].dmx_id = 4;        //
    STRCPY(&dmx_hw_param_list[3].dmx_name[0], "DMX_S3601_4");
    dmx_hw_param_list[3].clock_polarity = 0;
    dmx_hw_param_list[3].sync_mode = 1;
    dmx_hw_param_list[3].sync_times = 3;
    #endif

    dmx_dma_buf_list[0].buf_addr = __MM_DMX0_DMA_START_ADDR;
    dmx_dma_buf_list[0].buf_index = 0;
    dmx_dma_buf_list[0].buf_size = __MM_DMX_REC_LEN;
    dmx_dma_buf_list[0].buf_type = DMX_DMA_BUF;
    #if (DMX_HW_ATTACH_NUM > 1)
    dmx_dma_buf_list[1].buf_addr = __MM_DMX1_DMA_START_ADDR;
    dmx_dma_buf_list[1].buf_index = 1;
    dmx_dma_buf_list[1].buf_size = __MM_DMX_REC_LEN;
    dmx_dma_buf_list[1].buf_type = DMX_DMA_BUF;
    #endif
    #if (DMX_HW_ATTACH_NUM > 2)
    dmx_dma_buf_list[2].buf_addr = __MM_DMX2_DMA_START_ADDR;
    dmx_dma_buf_list[2].buf_index = 3;
    dmx_dma_buf_list[2].buf_size = __MM_DMX_REC_LEN;
    dmx_dma_buf_list[2].buf_type = DMX_DMA_BUF;
    #endif
    #if (DMX_HW_ATTACH_NUM > 3)
    dmx_dma_buf_list[3].buf_addr = __MM_DMX3_DMA_START_ADDR;
    dmx_dma_buf_list[3].buf_index = 4;
    dmx_dma_buf_list[3].buf_size = __MM_DMX_REC_LEN;
    dmx_dma_buf_list[3].buf_type = DMX_DMA_BUF;
    #endif

    main_blk_buf_list[0].buf_addr = __MM_DMX0_MAIN_BLK_START_ADDR;
    main_blk_buf_list[0].buf_index = 0;
    main_blk_buf_list[0].buf_size = __MM_DMX_BLK_BUF_LEN;
    main_blk_buf_list[0].buf_type = DMX_MAIN_BLK_BUF;
    #if (DMX_HW_ATTACH_NUM > 1)
    main_blk_buf_list[1].buf_addr = __MM_DMX1_MAIN_BLK_START_ADDR;
    main_blk_buf_list[1].buf_index = 1;
    main_blk_buf_list[1].buf_size = __MM_DMX_BLK_BUF_LEN;
    main_blk_buf_list[1].buf_type = DMX_MAIN_BLK_BUF;
    #endif
    #if (DMX_HW_ATTACH_NUM > 2)
    main_blk_buf_list[2].buf_addr = __MM_DMX2_MAIN_BLK_START_ADDR;
    main_blk_buf_list[2].buf_index = 3;
    main_blk_buf_list[2].buf_size = __MM_DMX_BLK_BUF_LEN;
    main_blk_buf_list[2].buf_type = DMX_MAIN_BLK_BUF;
    #endif
    #if (DMX_HW_ATTACH_NUM > 3)
    main_blk_buf_list[3].buf_addr = __MM_DMX3_MAIN_BLK_START_ADDR;
    main_blk_buf_list[3].buf_index = 4;
    main_blk_buf_list[3].buf_size = __MM_DMX_BLK_BUF_LEN;
    main_blk_buf_list[3].buf_type = DMX_MAIN_BLK_BUF;
    #endif

    see_blk_buf_list[0].buf_addr = __MM_DMX_SEE_BLK_ADDR;
    see_blk_buf_list[0].buf_index = 0;
    see_blk_buf_list[0].buf_size = __MM_DMX_SEE_BLK_BUF_LEN;
    see_blk_buf_list[0].buf_type = DMX_SEE_BLK_BUF;

    dmx_config.attach_mode = DMX_ATTACH_NEW;
    dmx_config.hw_param_config.p_hw_param_list = &dmx_hw_param_list[0];
    dmx_config.hw_param_config.dmx_num = DMX_HW_ATTACH_NUM;
    dmx_config.dma_param_config.p_dma_buf_list = &dmx_dma_buf_list[0];
    dmx_config.dma_param_config.dmx_dma_buf_num = DMX_HW_ATTACH_NUM;
    dmx_config.main_blk_param_config.p_main_blk_buf_list = &main_blk_buf_list[0];
    dmx_config.main_blk_param_config.dmx_main_blk_num = DMX_HW_ATTACH_NUM;
    dmx_config.see_blk_param_config.p_see_blk_buf_list = &see_blk_buf_list[0];
    dmx_config.see_blk_param_config.dmx_see_blk_num = 1;

#ifndef FPGA_TEST
	dma_init();
#endif
	dmx_m36f_attach(&dmx_config);
}
#endif

void dmx_dev_attach(void)
{
#ifdef FSC_SUPPORT
	dmx_dev_fsc_attach();
#else
	dmx_dev_general_attach();
#endif
	// dmx_dev_general_attach();
}

#ifdef DUAL_ENABLE
static void osd_m36f_dev_attach(void)
{
	OSD_DRIVER_CONFIG osd_config;
	MEMSET((void *)&osd_config,0,sizeof(OSD_DRIVER_CONFIG));
	osd_config.u_mem_base = __MM_OSD_BK_ADDR1;
	osd_config.u_mem_size = __MM_OSD_LEN;
	osd_config.b_static_block = TRUE;
	osd_config.b_direct_draw = FALSE;
	osd_config.b_cacheable = TRUE;
	osd_config.b_vfilter_enable = TRUE;
	osd_config.b_p2nscale_in_normal_play = FALSE;
	osd_config.b_p2nscale_in_subtitle_play = TRUE;
	osd_config.u_dview_scale_ratio[OSD_PAL][0] = 384;
	osd_config.u_dview_scale_ratio[OSD_PAL][1] = 510;
	osd_config.u_dview_scale_ratio[OSD_NTSC][0] = 384;
	osd_config.u_dview_scale_ratio[OSD_NTSC][1] = 426;
	osd_config.af_par[0].id = 0;
	osd_config.af_par[0].vd = 1;
	osd_config.af_par[0].af = 1;
	osd_config.af_par[0].id = 1;
	osd_config.af_par[0].vd = 1;
	osd_config.af_par[0].af = 1;
	osd_m36g_attach("OSD_M36F_0", &osd_config);

#ifndef OSD2_DISABLE

	if(g_cfg_para.hd_subtitle_support)
	{
		osd_config.b_p2nscale_in_normal_play = TRUE;
		osd_config.b_p2nscale_in_subtitle_play = TRUE;
	}

	osd_config.u_mem_base = __MM_OSD_BK_ADDR2;
	osd_config.u_mem_size = __MM_SEE_OSD2_LEN;
	osd_config.b_p2nscale_in_normal_play = TRUE;
	osd_m36g_attach("OSD_M36F_1", &osd_config);
#endif //#ifndef OSD2_DISABLE

	libc_printf("osd attach ok\n");
}
#endif

void ge_dev_attach(void)
{
#ifndef OSD2_DISABLE
    ge_layer_config_t osd_config[2];
#else
	ge_layer_config_t osd_config[1];
#endif

	MEMSET((void *)&osd_config, 0, sizeof(osd_config));

	osd_config[0].mem_base = __MM_OSD_BK_ADDR1;
	osd_config[0].mem_size = __MM_OSD1_LEN;
	osd_config[0].b_direct_draw = FALSE;
	osd_config[0].b_cacheable = FALSE;
	osd_config[0].b_scale_filter_enable = TRUE;
	osd_config[0].b_p2nscale_in_normal_play = FALSE;
	osd_config[0].b_p2nscale_in_subtitle_play = TRUE;
	osd_config[0].hw_layer_id = GMA_HW_LAYER0;
	osd_config[0].color_format = GE_PF_ARGB8888;
	osd_config[0].pixel_pitch = OSD_MAX_WIDTH;
	osd_config[0].width = OSD_MAX_WIDTH;
	osd_config[0].height = OSD_MAX_HEIGHT;
	osd_config[0].b_newfeature = TRUE;

#ifndef OSD2_DISABLE

#if 1//(defined(_CAS9_CA_ENABLE_) || defined(_C0200A_CA_ENABLE_)||defined(_GEN_CA_ENABLE_) || defined (_C1800A_CA_ENABLE_))
	osd_config[1].mem_base = __MM_OSD_BK_ADDR2_MAIN;
#else
	osd_config[1].mem_base = __MM_OSD_BK_ADDR2;
#endif

#ifdef AUI
        // AUI project, need set the memory in MAIN. because SEE OSD2 memory share with audio description.
        osd_config[1].mem_base = __MM_OSD_BK_ADDR2_MAIN;
#endif

	osd_config[1].mem_size = __MM_OSD2_LEN;
	osd_config[1].b_direct_draw = FALSE;
	osd_config[1].b_cacheable = FALSE;
	osd_config[1].b_scale_filter_enable = TRUE;
	osd_config[1].b_p2nscale_in_normal_play = TRUE;
	osd_config[1].b_p2nscale_in_subtitle_play = TRUE;
	osd_config[1].hw_layer_id = GMA_HW_LAYER1;
	osd_config[1].color_format = GE_PF_CLUT8;
	osd_config[1].pixel_pitch = 1920;
	osd_config[1].width = 1920;
	osd_config[1].height = 1080;
#endif  //#ifndef OSD2_DISABLE


	ge_m36f_attach(osd_config, ARRAY_SIZE(osd_config));
	struct ge_device* ge_dev = (struct ge_device*)dev_get_by_id(HLD_DEV_TYPE_GE, 0);

#ifndef SEE_CPU
	extern void osd_dev_api_attach(struct ge_device *ge_dev, UINT32 osd_layer_id);

	#ifdef GE_SIMULATE_OSD
	osd_dev_api_attach(ge_dev, GMA_HW_LAYER0);
        #ifndef OSD2_DISABLE
	osd_dev_api_attach(ge_dev, GMA_HW_LAYER1);
        #endif //#ifndef OSD2_DISABLE
	#endif //#ifdef GE_SIMULATE_OSD
#endif

#ifdef DUAL_ENABLE
	//osd_m36f_dev_attach();
#endif
};

void vpo_dev_attach(void)
{
	struct vp_feature_config vp_config;
	struct tve_feature_config tve_config;
	struct tve_feature_config sd_tve_config;
	UINT32 otp_tve_fs_value  = 0;

	MEMSET((void *)&tve_config,0,sizeof(struct tve_feature_config));
	MEMSET((void *)&sd_tve_config,0,sizeof(struct tve_feature_config));
	MEMSET((void *)&vp_config,0,sizeof(struct vp_feature_config));

	vp_config.b_avoid_mosaic_by_freez_scr = FALSE;    /* macro VDEC_AVOID_MOSAIC_BY_FREEZE_SCR */
#if 0 //(defined(_MHEG5_V20_ENABLE_))
	vp_config.b_mheg5enable = TRUE;                  /* macro  _MHEG5_ENABLE_ */
#else
	vp_config.b_mheg5enable = FALSE;                  /* macro  _MHEG5_ENABLE_ */
#endif

	vp_config.b_osd_mulit_layer = FALSE;                  /* macro OSD_MULTI_LAYER */
	vp_config.b_overshoot_solution = FALSE;            /* macro VIDEO_OVERSHOOT_SOLUTION */
	vp_config.b_p2ndisable_maf= FALSE;
	vp_config.b_support_extra_win = FALSE;                /* macro VIDEO_SUPPORT_EXTRA_DVIEW_WINDOW */
	vp_config.b_adpcmenable= FALSE;                    /* macro VIDEO_ADPCM_ONOFF(VIDEO_ADPCM_ON:TRUE VIDEO_ADPCM_OFF:FALSE) */
	vp_config.p_mpget_mem_info = NULL;
	vp_config.p_src_asp_ratio_change_call_back = g_cfg_para.scart_aspect_change;//api_Scart_Aspect_Switch;
	vp_config.bl_fireware_smoothly = g_cfg_para.vpo_active;
#ifdef CHANCHG_VIDEOTYPE_SUPPORT
#ifdef VFB_SUPPORT
	//b_config_still_picture_memroy means see to backup automatically,
	//but need too much buffer,VFB must use see to backup, others don't need.
	vp_config.b_config_still_picture_memroy = TRUE;
	//vp_config.still_picture_memory_addr = __MM_STILL_PICTURE_MEM_ADDR;//NULL;
	//vp_config.still_picture_memory_len = __MM_STILL_PICTURE_MEM_LEN;//0;
	vp_config.still_picture_memory_addr = __MM_FRAME_BACKUP_ADDR;
	vp_config.still_picture_memory_len = __MM_FRAME_BACKUP_LEN;
#endif
#endif

	tve_config.config = YUV_SMPTE|TVE_TTX_BY_VBI|TVE_CC_BY_VBI;
#ifdef TVE_VDEC_PLUG_DETECT
	tve_config.config |= TVE_PLUG_DETECT_ENABLE;
#endif
	if(g_cfg_para.tve_full_current_mode)
		tve_config.config |= TVE_FULL_CUR_MODE;

#ifdef SUPPORT_AFD_WSS_OUTPUT
	tve_config.config |=TVE_WSS_BY_VBI;
#endif

#ifdef CGMS_A_SUPPORT
	sd_tve_config.config |= TVE_WSS_BY_VBI | CGMS_WSS_BY_VBI;
#endif

//	tve_config.config |= TVE_NEW_CONFIG_1;
	tve_config.tve_tbl_all = NULL;//g_cfg_para.tve_tbl;

#if defined(DUAL_VIDEO_OUTPUT_USE_VCAP)
	tve_config.tve_adjust = g_cfg_para.tve_adjust;
	tve_config.tve_adjust_adv = g_cfg_para.tve_adjust_adv;
#endif    
	extern void m36g_vpo_attach(struct vp_feature_config *vp_cfg, struct tve_feature_config *tvec_cfg);
	m36g_vpo_attach(&vp_config, &tve_config);

#if defined(DUAL_VIDEO_OUTPUT_USE_VCAP)
	vcap_attach_t vcap_param;
	vcap_param.fb_addr = __MM_VCAP_FB_ADDR;
	vcap_param.fb_size = __MM_VCAP_FB_SIZE;
	m36g_vcap_attach(&vcap_param);

#if 0 //(defined(_MHEG5_V20_ENABLE_))
        sd_tve_config.config = YUV_SMPTE;
#else
        sd_tve_config.config = YUV_SMPTE|TVE_TTX_BY_VBI|TVE_CC_BY_VBI;
#endif

#ifdef SUPPORT_AFD_WSS_OUTPUT
	sd_tve_config.config |=TVE_WSS_BY_VBI;
#endif

	sd_tve_config.tve_adjust = g_cfg_para.tve_adjust;
	sd_tve_config.tve_adjust_adv = g_cfg_para.tve_adjust_adv;
	extern void m36g_vpo_sd_attach(struct vp_feature_config * vp_cfg, struct tve_feature_config*tvec_cfg);

	m36g_vpo_sd_attach(&vp_config, &sd_tve_config);
#endif

	otp_init(NULL);
	otp_read(0xDF*4,(UINT8*)(&otp_tve_fs_value),4);
	otp_tve_fs_value = (otp_tve_fs_value>>6) & 0x0000000F;
	vpo_ioctl((struct vpo_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_DIS),VPO_IO_OTP_SET_VDAC_FS,otp_tve_fs_value);
}

void vdec_dev_attach(void)
{
#ifndef _BUILD_OTA_E_
	/* !!!!!Note !!!!!
	**If you copy this code to other project, please check feature configuration firstly
	**!!!!!Note !!!!!
	*/
	struct vdec_config_par vdec_config_par;

#ifdef FPGA_TEST
	return;
#endif

	MEMSET((void *)&vdec_config_par,0,sizeof(struct vdec_config_par));
	//vdec_config_par.mem_map.frm0_Y_size  = 0;
	vdec_config_par.mem_map.frm0_y_size  = __MM_FB_LEN;
	vdec_config_par.mem_map.frm0_c_size = 0;
	vdec_config_par.mem_map.frm1_y_size  = 0;
	vdec_config_par.mem_map.frm1_c_size = 0;
	vdec_config_par.mem_map.frm2_y_size = 0;
	vdec_config_par.mem_map.frm2_c_size = 0;
	vdec_config_par.mem_map.frm0_y_start_addr = __MM_FB_START_ADDR;
	vdec_config_par.mem_map.frm0_c_start_addr = 0;
	vdec_config_par.mem_map.frm1_y_start_addr = 0;
	vdec_config_par.mem_map.frm1_c_start_addr = 0;
	vdec_config_par.mem_map.frm2_y_start_addr = 0;
	vdec_config_par.mem_map.frm2_c_start_addr = 0;
	vdec_config_par.mem_map.dvw_frm_size = 0;
	vdec_config_par.mem_map.dvw_frm_start_addr = 0;
	vdec_config_par.mem_map.maf_size = __MM_MAF_LEN;
	vdec_config_par.mem_map.maf_start_addr = __MM_MAF_START_ADDR;
	vdec_config_par.mem_map.vbv_size = ((__MM_VBV_LEN-4)&0xFFFFFF00);
	vdec_config_par.mem_map.vbv_start_addr = ((__MM_VBV_START_ADDR&0xfffffff)|0x80000000);
	vdec_config_par.mem_map.vbv_end_addr = ((vdec_config_par.mem_map.vbv_start_addr) +  vdec_config_par.mem_map.vbv_size - 1);

	vdec_config_par.user_data_parsing = TRUE; /* macro USER_DATA_PARSING */
	vdec_config_par.dtg_afd_parsing = g_cfg_para.afd_scale_support;     //SUPPORT_AFD_SCALE
	vdec_config_par.drop_freerun_pic_before_firstpic_show = FALSE; /* macro VDEC27_DROP_FREERUN_BEFORE_FIRSTSHOW */
	vdec_config_par.reset_hw_directly_when_stop = TRUE;  /* macro VDEC27_STOP_REST_HW_DIRECTLY*/
	vdec_config_par.show_hd_service = FALSE;      /* macro SUPPORT_SHOW_HD_SERVICE */
	vdec_config_par.still_frm_in_cc = FALSE;          /* macro STILL_FRAME_IN_CC */
	vdec_config_par.not_show_mosaic = FALSE;      /* macro VDEC_AVOID_MOSAIC_BY_FREEZE_SCR */
	vdec_config_par.adpcm.adpcm_mode = FALSE;  /* macro VIDEO_ADPCM_ONOFF(VIDEO_ADPCM_ON:TRUE VIDEO_ADPCM_OFF:FALSE)*/
	vdec_config_par.adpcm.adpcm_ratio = 0;
	vdec_config_par.sml_frm.sml_frm_mode = FALSE;  /* macro VDEC27_SML_FRM_ONOFF(VDEC27_SML_FRM_OFF: FALSE   VDEC27_SML_FRM_ON: TRUE)*/
	vdec_config_par.return_multi_freebuf = TRUE;        /* macro VDEC27_SUPPORT_RETURN_MULTI_FREEBUF */
	vdec_config_par.sml_frm.sml_frm_size = 0;           /* macro VDEC27_SML_FRM_SIZE*/
	vdec_config_par.lm_shiftthreshold = 2;                   /* macro VDEC27_LM_SHIFTTHRESHOLD*/
	vdec_config_par.vp_init_phase = 0;                        /* macro DEFAULT_MP_FILTER_ENABLE*/
	vdec_config_par.preview_solution = VDEC27_PREVIEW_DE_SCALE; /* macro VDEC27_PREVIEW_SOLUTION(VDEC27_PREVIEW_VE_SCALE or VDEC27_PREVIEW_DE_SCALE)*/
	vdec_m36_attach(&vdec_config_par);

#ifdef DVR_PVR_SUPPORT
	struct vdec_device *vdec_config_dev = (struct vdec_device *)dev_get_by_name("DECV_S3601_0");
	vdec_enable_advance_play(vdec_config_dev);
#endif

#ifdef HDTV_SUPPORT
	avc_attach();
	//hevc_attach();
#endif
	
	libc_printf("%s,%d\n", __FUNCTION__, __LINE__);
#if !defined(SD_PVR) && !defined(HEVC_DISABLE)
		hevc_attach();
#endif
	
#ifdef CHANCHG_VIDEOTYPE_SUPPORT
#ifndef VFB_SUPPORT //for not vfb support, use AUI to backup still picture in MAIN CPU
		aui_decv_set_backup_memory_info(__MM_FRAME_BACKUP_ADDR, __MM_FRAME_BACKUP_LEN);
#endif
#endif


    libc_printf("%s,%d\n", __FUNCTION__, __LINE__);

#endif
}

static void ttx_subt_attach(void)
{
#if    (TTX_ON == 1)

	struct vbi_config_par vbi_config;
	MEMSET(&vbi_config,0,sizeof(struct vbi_config_par));

	vbi_config.ttx_by_vbi = TRUE;
	vbi_config.cc_by_vbi = FALSE;
	vbi_config.vps_by_vbi = FALSE;
	vbi_config.wss_by_vbi = FALSE;

	vbi_config.hamming_24_16_enable = FALSE;
	vbi_config.hamming_8_4_enable = FALSE;
	vbi_config.erase_unknown_packet = TRUE;

	if(g_cfg_para.ttx_packet_26_support)
	{
		vbi_config.parse_packet26_enable = TRUE;
		vbi_config.mem_map.p26_data_buf_start_addr = __MM_TTX_P26_DATA_BUF_ADDR;
		vbi_config.mem_map.p26_data_buf_size = __MM_TTX_P26_DATA_LEN;
		vbi_config.mem_map.p26_nation_buf_start_addr = __MM_TTX_P26_NATION_BUF_ADDR;
		vbi_config.mem_map.p26_nation_buf_size = __MM_TTX_P26_NATION_LEN;
	}

	if(g_cfg_para.ttx_sub_page)
	{
		vbi_config.ttx_sub_page = TRUE;
		vbi_config.mem_map.sub_page_start_addr = __MM_TTX_SUB_PAGE_BUF_ADDR;
		vbi_config.mem_map.sub_page_size = __MM_TTX_SUB_PAGE_LEN;
	}

	vbi_config.user_fast_text = FALSE;
	vbi_config.mem_map.sbf_start_addr = __MM_TTX_BS_START_ADDR;
	vbi_config.mem_map.sbf_size = __MM_TTX_BS_LEN;
	vbi_config.mem_map.pbf_start_addr = __MM_TTX_PB_START_ADDR;
	vbi_attach(&vbi_config);

	struct vbi_device *vbi_config_dev = NULL;
	vbi_config_dev = (struct vbi_device *)dev_get_by_id(HLD_DEV_TYPE_VBI,0);
	vbi_hld_enable_ttx_by_osd(vbi_config_dev);
#endif

#if (SUBTITLE_ON == 1)
#ifdef SUBT_FUNC_POINTER_ENABLE
	lib_subt_init();
#endif

#include <api/libsubt/subt_osd.h>
	struct sdec_feature_config cfg_param;
	MEMSET(&cfg_param, 0, sizeof(struct sdec_feature_config));
	cfg_param.temp_buf_len = 0xa000;//(8*1024);  // > segment len
	cfg_param.temp_buf = NULL;
	cfg_param.bs_hdr_buf_len = 800;//200;
	cfg_param.bs_hdr_buf = 0;
	cfg_param.bs_buf = (UINT8*)__MM_SUB_BS_START_ADDR;
	cfg_param.bs_buf_len = __MM_SUB_BS_LEN;
	cfg_param.pixel_buf = (UINT8*)__MM_SUB_PB_START_ADDR;
	cfg_param.tsk_qtm = 2;//10;    //fix BUG05435
	cfg_param.tsk_pri = OSAL_PRI_HIGH;//OSAL_PRI_NORMAL;//OSAL_PRI_HIGH
	cfg_param.transparent_color = OSD_TRANSPARENT_COLOR;

#ifdef DUAL_ENABLE
	cfg_param.sdec_hw_buf = (UINT8*)__MM_SUB_HW_DATA_ADDR;
	cfg_param.sdec_hw_buf_len = __MM_SUB_HW_DATA_LEN;
#else
	cfg_param.subt_draw_pixel = osd_subt_draw_pixel;
	cfg_param.region_is_created = osd_region_is_created;
	cfg_param.subt_create_region = osd_subt_create_region;
	cfg_param.subt_region_show = osd_subt_region_show;
	cfg_param.subt_delete_region = osd_subt_delete_region;
#endif

	sdec_attach(&cfg_param);
	subt_hld_disply_bl_init((struct sdec_device *)dev_get_by_name("SDEC_M3327_0"));
#endif

#ifdef ATSC_SUBTITLE_SUPPORT
	struct atsc_subt_config_par atsc_subt_par;
	struct atsc_subt_config_par* patsc_subt_par=&atsc_subt_par;
	MEMSET(&atsc_subt_par,0x00,sizeof(struct atsc_subt_config_par));

	patsc_subt_par->bs_buf_len=__MM_DCII_SUB_BS_LEN;
	patsc_subt_par->bs_buf_addr=(UINT8*)__MM_DCII_SUB_BS_START_ADDR;
	patsc_subt_par->sec_buf_len=__MM_SUBT_ATSC_SEC_LEN;
	patsc_subt_par->sec_buf_addr=(UINT8*)__MM_SUBT_ATSC_SEC_ADDR;
	patsc_subt_par->outline_thickness_from_stream=FALSE; //TRUE;
	patsc_subt_par->drop_shadow_right_from_stream=FALSE;
	patsc_subt_par->drop_shadow_bottom_from_stream=FALSE;
	patsc_subt_par->outline_thickness=2;
	patsc_subt_par->drop_shadow_right=2;
	patsc_subt_par->drop_shadow_bottom=2;
	lib_subt_atsc_attach(patsc_subt_par);
#endif

#ifndef _AUI_
#if (CC_ON==1)
	extern UINT32 ap_get_osd_scale_param(enum tvsystem e_tvmode, INT32 n_screen_width);

	struct atsc_cc_config_par cc_param;
	MEMSET(&cc_param,0,sizeof(struct atsc_cc_config_par));

	cc_param.pb_buf_addr=(UINT8*)__MM_ATSC_CC_PB_START_ADDR;
	cc_param.pb_buf_len=__MM_ATSC_CC_PB_LEN;
	cc_param.bs_buf_addr=(UINT8*)__MM_ATSC_CC_BS_START_ADDR;
	cc_param.bs_buf_len=__MM_ATSC_CC_BS_LEN;
	cc_param.osd_layer_id=1;
	cc_param.cc_width=OSD_CC_WIDTH;
	cc_param.cc_height=OSD_CC_HEIGHT;
	cc_param.w_polling_time=500;      // 500ms
	cc_param.b_ccscan=4;         // 4*500ms ->2sec
	cc_param.b_dtvccscan=4;      // 4*500ms ->2sec
	cc_param.osd_get_scale_para = ap_get_osd_scale_param;
	lib_atsc_cc_attach(&cc_param);  //vicky20110224

	vbi_cc_init();
#endif
#endif

#if (ISDBT_CC ==1)
	struct sdec_feature_config cc_cfg_param;
	// fill data to [cc_cfg_param]
	MEMSET(&cc_cfg_param, 0, sizeof(struct sdec_feature_config)); /*set default value of  mem as 0.*/

	cc_cfg_param.bs_hdr_buf = 0;
	cc_cfg_param.bs_hdr_buf_len = 200;/*size under checking.*/
	cc_cfg_param.bs_buf =(UINT8*)__MM_ISDBTCC_BS_START_ADDR;
	cc_cfg_param.bs_buf_len = 184*cc_cfg_param.bs_hdr_buf_len;
	cc_cfg_param.tsk_qtm = 10;
	cc_cfg_param.tsk_pri = OSAL_PRI_NORMAL    ;
	cc_cfg_param.transparent_color = OSD_TRANSPARENT_COLOR;

	lib_isdbtcc_init();
	isdbtcc_dec_attach(&cc_cfg_param);
	// isdbtcc_disply_init((struct sdec_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_SDEC));
	isdbtcc_disply_init((struct sdec_device *)dev_get_by_name("ISDBT_CC_0"));
#endif
}

#ifdef _C0200A_CA_ENABLE_
#ifndef _BUILD_UPG_LOADER_
void nvcak_smc_attach(void)
{
	struct smc_dev_config smc_config;
	board_cfg *cfg = NULL;
	UINT32 init_clk = 3600000;

	cfg = get_board_cfg();
	chip_gpio_set(cfg->smc_5v_ctl, 1);

	MEMSET(&smc_config, 0, sizeof(struct smc_dev_config));
	smc_config.init_clk_trigger= 1;
	smc_config.init_clk_number = 1;
	smc_config.force_tx_rx_trigger = 1;
	smc_config.def_etu_trigger = 1;
	smc_config.default_etu = 372;
	smc_config.warm_reset_trigger = 1;
	smc_config.force_tx_rx_cmd = 0xdd;//command start.
	smc_config.force_tx_rx_cmd_len = 5;//command length.
	smc_config.init_clk_array = &init_clk;
	smc_config.class_selection_supported = 1;
	smc_config.board_supported_class = BOARD_SUPPORT_CLASS_A|BOARD_SUPPORT_CLASS_B;
	smc_config.invert_detect = 1;
	//smc_config.invert_power = 1;
	smc_dev_attach(0, &smc_config);
}
#endif
#endif

#if defined(_AUI_NESTOR_) || defined(_AUI_TEST_)
extern void board_class_select(enum class_selection cls_sel);
#endif
void smc_attach(void)
{
	struct smc_dev_config smc_config;
	static UINT32 init_clk = 6000000;
#if defined(MULTI_CAS) || defined(_AUI_NESTOR_) || defined(_AUI_TEST_)
	OTP_CONFIG my_otp_cfg;

	MEMSET(&smc_config, 0, sizeof(struct smc_dev_config));
	MEMSET((void *)(&my_otp_cfg), 0, sizeof(OTP_CONFIG));
	otp_init(&my_otp_cfg);

	smc_config.init_clk_trigger= 1;
	smc_config.init_clk_number = 1;
	smc_config.force_tx_rx_trigger = 1;
	//smc_config.apd_disable_trigger = 1;
	//smc_config.disable_pps = 1;
	if(g_cfg_para.cas_type == CAS_CONAX)
	{
		smc_config.def_etu_trigger = 1;
		smc_config.default_etu = 372;
	#ifdef CAS9_V6
		smc_config.warm_reset_trigger = 0; //Disable warm reset in cnx stb kit 6
	#else
		smc_config.warm_reset_trigger = 1;
	#endif
		smc_config.force_tx_rx_cmd = 0xdd;//CONAX command start.
		smc_config.force_tx_rx_cmd_len = 5; //CONAX command length.
		init_clk = 3600000;
		smc_config.invert_detect=0;
	}

	smc_config.init_clk_array = &init_clk;
	smc_config.class_selection_supported = 1;
	smc_config.board_supported_class = BOARD_SUPPORT_CLASS_A|BOARD_SUPPORT_CLASS_B;
	smc_config.class_select =  g_cfg_para.class_select; //board_class_select;
#if defined(_AUI_NESTOR_) || defined(_AUI_TEST_)
	smc_config.class_select = board_class_select;
#endif

	smc_config.invert_detect = g_cfg_para.invert_detect;
#if defined(_AUI_NESTOR_) || defined(_AUI_TEST_)
	smc_config.invert_detect = 1;
#endif

#ifdef _BOARD_DB_M3527_01V01_
	smc_config.invert_detect = 1;
#endif

#ifdef _BOARD_DB_M3627_02V01_
	smc_config.invert_detect = 1;
#endif

#ifdef SMC1_SUPPORT
	smc_dev_attach(0, &smc_config);
#elif defined(SMC2_SUPPORT)
	smc_dev_attach(1, &smc_config);
#endif
#endif

#if defined(_BC_CA_ENABLE_) || defined(SUPPORT_BC_STD)//|| defined(_AUI_CASTPAL_)
#ifndef _BUILD_OTA_E_
	init_clk = 4800000;

	MEMSET(&smc_config, 0, sizeof(struct smc_dev_config));
	smc_config.init_clk_trigger= 1;
	smc_config.init_clk_number = 1;
	smc_config.force_tx_rx_trigger = 1;
	smc_config.apd_disable_trigger = 1;
	smc_config.disable_pps = 0;
	smc_config.init_clk_array = &init_clk;
	smc_config.invert_detect = g_cfg_para.invert_detect;
	smc_config.default_etu = 372;
	smc_config.def_etu_trigger = 1;

#ifdef SMC1_SUPPORT
	smc_dev_attach(0, &smc_config);
#elif defined(SMC2_SUPPORT)
	smc_dev_attach(1, &smc_config);
#endif
#endif
#endif

}

#if (defined(_C0200A_CA_ENABLE_) || defined (_BC_AUI_)) && !defined(_BUILD_UPG_LOADER_)
static AUI_RTN_CODE aui_dmx_callbackinit(aui_dmx_module_attr * dmx_module_attr)
{
	dmx_dev_attach();
	return SUCCESS;
}
#endif
void board_advance_init(advance_cfg_para* cfg_para)
{
	if(NULL != cfg_para)
		MEMCPY(&g_cfg_para, cfg_para, sizeof(advance_cfg_para));

	deca_dev_attach();
	snd_dev_attach();

#if (defined(_C0200A_CA_ENABLE_) || defined (_BC_AUI_)) && !defined(_BUILD_UPG_LOADER_)
	aui_dmx_module_attr dmx_module_attr;
	MEMSET(&dmx_module_attr,0,sizeof(dmx_module_attr));

	dmx_module_attr.ul_dev_cnt = 4;
	dmx_module_attr.ul_init_flag = TRUE;
	dmx_module_attr.dmx_capability[0].ul_dev_idx = 0;
	dmx_module_attr.dmx_capability[0].dev_type = AUI_DMX_DEV_TYPE_HARDWARE;
	dmx_module_attr.dmx_capability[1].ul_dev_idx = 1;
	dmx_module_attr.dmx_capability[1].dev_type = AUI_DMX_DEV_TYPE_HARDWARE;
	dmx_module_attr.dmx_capability[2].ul_dev_idx = 2;
	dmx_module_attr.dmx_capability[2].dev_type = AUI_DMX_DEV_TYPE_HARDWARE;
	dmx_module_attr.dmx_capability[3].ul_dev_idx = 3;
	dmx_module_attr.dmx_capability[3].dev_type = AUI_DMX_DEV_TYPE_SOFTWARE;
	aui_dmx_init(aui_dmx_callbackinit, (void *)(&dmx_module_attr));
#else
	dmx_dev_attach();
#endif

#ifdef CI_SUPPORT
#if (SYS_CIC_MODULE == CIMAX_27)
	struct cic_config_param cic_param = {0x86, I2C_TYPE_GPIO};
	cic_cimax_attach(&cic_param);
#else
	cic_m3602_attach();
#endif
#endif

	ge_dev_attach();
	vpo_dev_attach();
	vdec_dev_attach();
	ttx_subt_attach();
#ifdef _C0200A_CA_ENABLE_

#ifndef _BUILD_UPG_LOADER_
    nvcak_smc_attach();
#endif

#else
	smc_attach();
#endif

#ifdef CI_PLUS_SUPPORT
	otp_init(NULL);
#endif

#if defined(HDTV_SUPPORT) && (!defined(HDMI_DISABLE))
	extern INT32 hdmi_tx_attach(struct config_hdmi_parm *hdmi_param);

	struct config_hdmi_parm hdmi_param;
	get_hdmi_config(&hdmi_param);
	hdmi_tx_attach(&hdmi_param);
#endif

#ifdef ALICAST_SUPPORT
	get_hdmi20_config(&g_H2KeySets);
	hdcp2_load_KeySets(&g_H2KeySets);
#endif

	if(g_cfg_para.ce_api_enabled)
		ce_api_attach();
}

