/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: sys_config_3281.h
*
*    Description: system config and memory mapping for M3281 project
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H
#ifdef __cplusplus
extern "C"{
#endif

#include <sys_define.h>

#if defined DUAL_ENABLE || defined _M36F_SINGLE_CPU
    #ifdef _BOARD_SB_M3281_01V01_
        #define SYS_MAIN_BOARD BOARD_SB_M3281_01V01
    #elif defined  _BOARD_DB_M3281_01V01_
        #define SYS_MAIN_BOARD BOARD_DB_M3281_01V01
    #elif defined _BOARD_DEMO_M3281_01V01_
        #define SYS_MAIN_BOARD BOARD_DEMO_M3281_01V01
    #endif
#define M36F_CHIP_MODE
#endif

#define ENABLE_EROM
#define PVR_DYNAMIC_PID_CHANGE_TEST //dynamic v-pid change for h264<->mpg2

#define VIDEO_ENGINE_NEW

#ifdef _AUI_
#define AUI
#endif

#ifdef _AUI_TEST_
#define AUI_TEST 
#endif

#define SD_UI
#define ONE_RECODER_PVR
#define SD_PVR

#ifdef _DVBC_ENABLE_
#define DVBC_SUPPORT
#define DVBC_NIM_MODE_J83B
#ifndef _32M_PVR_
#define DVBC_MODE_CHANGE
#endif
#endif

#ifdef _DVBS_ENABLE_
#define DVBS_SUPPORT
#endif

#define COMBOUI

#ifdef _H264_SUPPORT_
#define H264_32M_SUPPORT
#endif

/* M3281 solution3:support: TTX, subtitle, H.264 , not support: PVR, Timeshift */
#ifdef _M3281_SOLUTION3_SUPPORT_
#define M3281_SOLUTION3_SUPPORT
#define DISABLE_PVR_TMS
#endif

#ifdef ISDBT_SUPPORT
#define ISDBT_CC        1
#define ISDBT_EPG
#define SUPPORT_WO_ONE_SEG  //has problem
#define SYS_ISDBT_DEMO_MODULE DIB8000
#endif

//#define AUTO_OTA
#if (defined(AUTO_OTA)&&(defined(DVBT_SUPPORT)||(defined(ISDBT_SUPPORT))))
#define SUPPORT_TP_QUALITY
#endif

/* OTA Setting */
#define OTA_CONTROL_FLOW_ENHANCE
#define SYS_OUI               0x90E6
#define SYS_HW_MODEL          0x3281
#define SYS_SW_MODEL          0x0000

#define SYS_HW_VERSION      0x0001
#define SYS_SW_VERSION      0x0001

#ifdef _BC_CA_STD_ENABLE_
#define OPERATOR_OTA_PID    0x100   //for osm upgrade trigger
#endif

#ifdef _BC_CA_ENABLE_
#undef SYS_HW_MODEL
#undef SYS_HW_VERSION
#undef SYS_SW_MODEL
#undef SYS_SW_VERSION
#define SYS_HW_MODEL        0x0001  //defined by customer
#define SYS_HW_VERSION      0x0001  //defined by customer
#define SYS_SW_MODEL        0x0001  //defined by customer
#define SYS_SW_VERSION      0x0001  //defined by customer
#define OPERATOR_OTA_PID    0x100   //for osm upgrade trigger

//Don't change below
#ifdef _BC_VER0_
#undef SYS_SW_VERSION
#define SYS_SW_VERSION      0x0000
#endif
#ifdef _BC_VER1_
#undef SYS_SW_VERSION
#define SYS_SW_VERSION      0x0001
#endif
#ifdef _BC_VER2_
#undef SYS_SW_VERSION
#define SYS_SW_VERSION      0x0002
#endif
#endif

#if (defined ISDBT_SUPPORT || defined DVBT_SUPPORT)
#define _DTGSI_ENABLE_
#if (defined(_DTGSI_ENABLE_))
#define SI_MODULE_CONFIG   // for DTG SI specification config in the si_config.h
#define LCN_VAR_RANGE 900
#endif
#define _LCN_ENABLE_

/* FRANCE_HD TNT Related Define */
#define HD_SERVICE_TYPE_SUPPORT  //support the HD service type in the SDT
#define DATABRODCAST_SERVICE_TO_TV  //support databroadcast service change type to TV service
#define PRIVATE_DATA_SPEC INVALID_PRIVATE_DATA_SPEC // remove the private data specification check
#define SYS_DVBT_DEMO_MODULE COFDM_M3101
//#define SYS_DVBT_DEMO_MODULE MXL101
#endif

#ifdef DVBS_SUPPORT
#define DISEQC_SUPPORT
#endif

#ifndef DVBS_SUPPORT
#define PARENTAL_SUPPORT //open feature of partetal rating control
#define RATING_LOCK_WITH_PASSWORD
#endif

#define CSA_PARENTAL_CONTROL //With definition: user have 4 class of rating level to set: 10, 12, 16, 18 years.
                               // (TNT_CSA only with the 4class of rating level : 10, 12, 16, 18 years)
                               //without definition: 4,5,6,...~18 years.(spec in EN300468)

#ifndef _BUILD_OTA_E_
//#define USB_LOGO_TEST
#endif

#ifndef _BUILD_OTA_E_
//#define AUTO_CC_TEST
#endif

//#define AUTO_SYANDBY_DEFAULT_ON
//#define MULTIFEED_SUPPORT
//#define ALI_SHUTTLE_MODIFY
//#define SUPPORT_UNICABLE
//#define SUPPORT_DISEQC11
//#define UI_MEDIA_PLAYER_REPEAT_PLAY
//#define TVE_USE_FULL_CURRENT_MODE
#ifndef _RD_DEBUG_
#define WATCH_DOG_SUPPORT
#endif
#define MP_PREVIEW_SWITCH_SMOOTHLY
//#define DO_DDP_CERTIFICATION
//#define AFD_SW_SUPPORT
#define AFD_HW_SUPPORT

/* Add "RAM_TMS_TEST" for test: doing timeshift using RAM disk.
 * If open it, MUST re-define "RAM_DISK_ADDR" and "RAM_DISK_SIZE".*/
//#define RAM_TMS_TEST
#ifndef _BUILD_OTA_E_ //add by comer
#ifndef _32M_PVR_
#define ATSC_SUBTITLE_SUPPORT
#endif
#endif

#ifdef ATSC_SUBTITLE_SUPPORT
#define __MM_DCII_SUB_BS_LEN (16*1024)
#define __MM_SUBT_ATSC_SEC_LEN (720*576)
#else
#define __MM_DCII_SUB_BS_LEN      0//(16*1024)
#define __MM_SUBT_ATSC_SEC_LEN 0//(720*576)
#endif

#ifdef _SFU_TEST_SUPPORT
#define SFU_TEST_SUPPORT
#endif

#define BOARD_S3602F_MAX    (BOARD_SB_S3602F_QFP_01V01 + 300)

#ifdef M36F_CHIP_MODE
    #define DRAM_SPLIT
    #ifndef _USE_32M_MEM_
        #define OSD_16BIT_SUPPORT
    #endif
        #define USB_SUPPORT_HUB
    #ifdef _BC_CA_STD_ENABLE_
        #ifdef AFD_HW_SUPPORT
        #undef AFD_HW_SUPPORT   //temp sol to fix ali teamtrack bug
        #endif
        #define DISABLE_PRINTF
        #define HW_SECURE_ENABLE
        #ifndef _BUILD_OTA_E_
            #define SUPPORT_BC_STD
            //#define SELF_TEST_ENABLE

            #ifdef SELF_TEST_ENABLE
                #define NEW_SELF_TEST
            #endif
        #endif
        #define _BC_STD_3281_
        #define HDCP_FROM_CE
        #define DSC_SUPPORT
        #define CA_NO_CRC_ENABLE
        #ifndef DISABLE_USB_UPG
            #define USBUPG_ONLY_ALLCODE
            #define BACKUP_USB_LOADER
        #endif
        #define BC_PVR_STD_SUPPORT
        #ifdef BC_PVR_STD_SUPPORT
            #define BC_STD_PVR_CRYPTO 1
        #endif

        #ifndef _32M_PVR_   //vicky130329#2
            #define MEDIAPLAYER_SUPPORT
        #endif

        // PT Patch
        #define BC_PATCH_BC_IOCTL              // only need to set call back once
        #define BC_PATCH_MMI_SET_SC_STATE      //  DVB C only
        #define BC_PATCH_DVBC_DELIVERYDESP     //  DVB C only
        #define BC_PATCH_SW_CA                 //  STD BC only
        #define BC_PATCH_SYS_GETBOXID          //  STD BC only
        #define BC_PATCH_BC_NSC_K_SC_HWERROR   //  STD BC only
        #define BC_PATCH_CC// Channel change  (PT, sol from Jeremy)
        #define BC_PATCH_CAS   // CAS (PT, sol from David,Jeremy)
        #define BC_PATCH_UI// UI and MISC Patch (PT, sol from Jeremy,Lowrance,Luca,etc)
        #define BC_PATCH_PURSE                 // Purse,IPPV Order related Code
        #define BC_PATCH_NROSM_WM
    #endif

    #ifdef _BC_CA_ENABLE_
        #ifdef AFD_HW_SUPPORT
        #undef AFD_HW_SUPPORT   //temp sol to fix ali teamtrack bug
        #endif
        //#define DISABLE_PRINTF
        #define HW_SECURE_ENABLE
        #ifndef _BUILD_OTA_E_
            #define SUPPORT_BC
            #define BC_NSC_SUPPORT //cardless support
            #define BC_PVR_SUPPORT
            #ifdef BC_PVR_SUPPORT
                #define BC_MULTI_DES_MAX 2 //maximum multi-decramble support for BC library
                #define BC_PVR_CHANNEL_ID_NUM 2 //maximum channel id support for BC library
                #ifdef ONE_RECODER_PVR //support not only one pvr
                #undef ONE_RECODER_PVR
                #endif
            #else
                #define BC_MULTI_DES_MAX 1
            #endif
            #define SELF_TEST_ENABLE
            #ifdef SELF_TEST_ENABLE
                //#define NEW_SELF_TEST
                //#define NEW_SELF_TEST_UART_ENABLE //enable the uart function supprot
            #endif
        #endif  /* _BUILD_OTA_E_ */

        #define HDCP_FROM_CE
        #define DSC_SUPPORT
        #define CA_NO_CRC_ENABLE
        #define FAKE_VERITY_SIGNATURE   //Aaron20121115# for ALi bootloader signature function

        #ifdef _BC_CERTIFICATION_
            #ifdef FAKE_VERITY_SIGNATURE
                #undef FAKE_VERITY_SIGNATURE
            #endif
            #if (!defined(DISABLE_PRINTF))
                #define DISABLE_PRINTF
            #endif
        #endif
        #ifdef _BC_DEBUG_MODE_CERTIFICATION_
            #if (!defined(FAKE_VERITY_SIGNATURE))
                #define FAKE_VERITY_SIGNATURE
            #endif
            #if (!defined(DEBUG_MODE_VERITY_SIGNATURE))
                #define DEBUG_MODE_VERITY_SIGNATURE
            #endif
            #if (!defined(DISABLE_PRINTF))
            #define DISABLE_PRINTF
            #endif
        #endif

        #ifndef DISABLE_USB_UPG
            #define USBUPG_ONLY_ALLCODE
            #define BACKUP_USB_LOADER
        #endif

        #ifndef _32M_PVR_
            #define MEDIAPLAYER_SUPPORT
        #endif

        #define PT_SC_PATCH //invert sc when nsc is available cause hangup problem
        #ifdef BC_PVR_SUPPORT
            #define BC_PATCH_TRIGGER_STOP_REC //when trigger ota/rescan/switch, stop recording before do it
            #define BC_SWITCH_TO_PC_SUPPORT //handle pin code when replay a non-PC to PC recorded file
        #endif
    #endif

    #ifdef _CAS9_CA_ENABLE_
        #define SUPPORT_CAS9
        #define SUPPORT_HW_CONAX
        #define MULTI_CAS
        #define DSC_SUPPORT
        #define CAS_TYPE    CAS_CONAX
        #define HW_SECURE_ENABLE
        #define CAS9_PVR_SUPPORT
        #ifndef _RD_DEBUG_
            #define DISABLE_PRINTF
            #define REMOVE_DEBUG_INFO
        #endif

        #define AUDIO_CHANNEL_LANG_SUPPORT
        #define STO_PROTECT_BY_MUTEX
        #define  ENABLE_4M_FLASH

        #ifndef _32M_PVR_
            #define MEDIAPLAYER_SUPPORT
        #endif
        #undef MP_PREVIEW_SWITCH_SMOOTHLY
        #undef CHANCHG_VIDEOTYPE_SUPPORT

        #define DISABLE_USB_UPG
        #ifndef DISABLE_USB_UPG
        #define USBUPG_ONLY_ALLCODE//remind:CA usb upg only support selection of all code!
        #endif

        #define CAS9_V6
        #ifdef CAS9_V6
            //#define RD_SKIP_APS     //for RD debug or QT test only
            #define CAS9_DA_MUTE //vicky140115#7 U.4
               #define VPO_VIDEO_LAYER
            #define CAS9_PVR_SID
            #define CAS9_URI_APPLY
            #ifndef PREVIEW_SHOW_LOGO
                #ifndef FP_IN_PREVIEW
                    #define FP_IN_PREVIEW
                #endif
            #endif

            #ifdef _BUILD_OTA_E_    //vicky130814#1 for ota build pass
                #undef CAS9_URI_APPLY
                #ifdef FP_IN_PREVIEW
                    #undef FP_IN_PREVIEW
                #endif
            #endif

        #endif
        #ifdef _CAS9_VSC_ENABLE_
            #define CAS9_VSC
            #define VSC_SIGNATURE_LEN    256
            #define VSC_VERSION_LEN    16
            #define __MM_VSC_CODE_LEN    0x20000
            #define __MM_VSC_DATA_LEN 0x10000
            #define __MM_VSC_TOTAL_LEN (__MM_VSC_CODE_LEN+__MM_VSC_DATA_LEN)
       #endif
       #ifdef _CAS9_SC_UPG_
               #define CAS9_SC_UPG
       #endif
    #endif
    /**************************/
    #define POWER_ENJ_DEFAULT

    #ifdef _BC_CA_STD_ENABLE_
        #ifdef POWER_ENJ_DEFAULT
        #undef POWER_ENJ_DEFAULT
        #endif
    #endif
#endif

#ifdef _FTA_ONLY_
    #define FTA_ONLY
    #ifndef DSC_SUPPORT
        #define DSC_SUPPORT
    #endif
    #define CA_NO_CRC_ENABLE
    #define HW_SECURE_ENABLE

    #ifndef _32M_PVR_
        #define MEDIAPLAYER_SUPPORT
    #endif
    #undef MP_PREVIEW_SWITCH_SMOOTHLY
    #undef CHANCHG_VIDEOTYPE_SUPPORT

    #define DISABLE_USB_UPG
#endif

#ifdef OSD_16BIT_SUPPORT
//#define SUPPORT_DRAW_EFFECT
#endif

#define SYS_NETWORK_MODULE  SYS_DEFINE_NULL//NET_ALIETHMAC

#define SHOW_TWO_TUNER_LOCK_STATUS

//#define SDIO_SUPPORT

#ifdef _SHOW_ALI_DEMO_ON_SCREEN
#define SHOW_ALI_DEMO_ON_SCREEN
#endif

#if( defined (AFD_SW_SUPPORT)) || ( defined(AFD_HW_SUPPORT))
#define SUPPORT_AFD_PARSE
#define SUPPORT_AFD_SCALE
#define SUPPORT_AFD_WSS_OUTPUT
#endif

#define SUPPORT_MPEG4_TEST
#define AUDIOTRACK_SUPPORT
#define MP_SUBTITLE_SUPPORT
#define FS_STDIO_SUPPORT
#define UNIFIED_CI_PATCH
#define AUTOMATIC_STANDBY
#define PVR3_SUPPORT
#define NEW_EPG_ARCH
#define ISO8859_SUPPORT
#define SYS_AGC_SNR_API
#define SYS_TUN_MODULE_UNIFIED_API
#define MULTI_AUDIO_PID
#define M3327SW_AUTOSCAN
#define TUNER_OPTION_IX2410
#define DUP_TRANSPONDER_REMOVAL     1
#define SYS_PSEARCH_SCAN_TP_ALL     SYS_FUNC_ON
#define SYS_PROJECT                 SYS_DEFINE_NULL
#define SYS_PROJECT_SM              PROJECT_SM_FTA//PROJECT_SM_CI
#define SYS_OS_MODULE               ALI_TDS2
#define SYS_MW_MODULE               SYS_DEFINE_NULL
#define SYS_CA_MODULE               SYS_DEFINE_NULL
#define SYS_EPG_MODULE              SYS_DEFINE_NULL
#define SYS_CHIP_MODULE             ALI_S3602
#define SYS_CPU_MODULE              CPU_ALI_V1//CPU_M6303//CPU_MIPS24KE
#define SYS_CPU_ENDIAN              ENDIAN_LITTLE
#define SYS_CHIP_CLOCK              27000000
#define SYS_CPU_CLOCK               270000000
#define SYS_GPIO_MODULE             M6303GPIO
#define SYS_I2C_MODULE              M6303I2C
#define SYS_I2C_SDA                 3
#define SYS_I2C_SCL                 4
#define SYS_SCI_MODULE              UART16550
#define SYS_TSI_MODULE              M3327TSI
#define SYS_FLASH_BASE_ADDR         0xafc00000
#define SYS_FLASH_SIZE              0x400000
#define SYS_DMX_MODULE              M3327DMX
#define SYS_LNB_POWER_OFF           SYS_FUNC_ON
#define SYS_RFM_BASE_ADDR           0xca
#define SYS_IRP_MOUDLE              ROCK00
#define TABLE_BLOCK_SPACE_SIZE      (64 * 1024)
#define MAX_PROG_NUM                5000
#define MAX_TP_NUM                  3000
#define MAX_SAT_NUM                 65 //64

#ifndef _BUILD_OTA_E_
#ifdef H264_32M_SUPPORT

#ifndef M3281_SOLUTION3_SUPPORT
#define TTX_ON                      0
#define SUBTITLE_ON                 0
#define CC_ON                       0
#else
/* solution 3*/
#define TTX_ON                      1
#define SUBTITLE_ON                 1
#define CC_ON                       1
#endif

#else
#define TTX_ON                      1
#define SUBTITLE_ON                 1
#define CC_ON                       1
#endif
#else
#define TTX_ON                      0
#define SUBTITLE_ON                 0
#define CC_ON                       0
#endif

#if defined(_BC_CA_STD_ENABLE_)||defined(_BC_CA_ENABLE_)
#ifdef SELF_TEST_ENABLE
#undef CC_ON
#define CC_ON    0
#endif
#endif

#define TTX_BY_OSD
#define ALL_BY_VBI
#define TTX_BY_VBI
#define TTX_COLOR_NUMBER            256
#define DECODE_LIB_MAD              1
#define DECODE_LIB                  DECODE_LIB_MAD
#define VDEC_AV_SYNC
#define COLOR_N                     256
#define LOCAL_VSCR                  0
#define OSD_VSCREEN                 LOCAL_VSCR

#define LIST_SUPPORT                1
#define MATRIXBOX_SUPPORT           1
#define USB_MP_SUPPORT
#define ISO_5937_SUPPORT
#define DB_USE_UNICODE_STRING
#define NEW_DISEQC_LIB

#ifndef SD_UI
#define OSD_MAX_WIDTH               1008
#define OSD_MAX_HEIGHT              640
#define OSD_STARTCOL                ((1280 - OSD_MAX_WIDTH)>>1)
#define OSD_STARTROW_N              ((720 - OSD_MAX_HEIGHT)>>1)
#define OSD_STARTROW_P              ((720 - OSD_MAX_HEIGHT)>>1)
#else
#define OSD_MAX_WIDTH 608
#define OSD_MAX_HEIGHT 500
#define OSD_STARTCOL ((720 - OSD_MAX_WIDTH)>>1)
#define OSD_STARTROW_N ((576 - OSD_MAX_HEIGHT)>>1)
#define OSD_STARTROW_P ((576 - OSD_MAX_HEIGHT)>>1)
#endif

#define AC3DEC                      1
#define PSI_MONITOR_SUPPORT
#define TTX_GREEK_SUPPORT
#define TTX_ARABIC_SUPPORT
#define TTX_ARABIC_G2_SUPPORT

#define DB_VERSION                  40
#define ALI_SDK_API_ENABLE

#define GPIO_NULL 127

//vicky20101229 dbg
/*****CC macro***********/
#if(CC_ON ==1)
#define CC_BY_OSD   //vicky20110118
#define CC_BY_VBI
#define CC_MONITOR_CS   //vicky20110210
#define CC_MONITOR_CC   //vicky20110216
//End
#endif
#define TRUE_COLOR_HD_OSD
//#define SD_PVR
#define PVR_FS_SH
#ifdef _MP2_0_SUPPORT
    #define MP2_0_SUPPORT
    #define PS_TS_SUPPORT
#endif

#define HDTV_SUPPORT
#define HDMI_DISABLE
#define SUPPORT_DUAL_OUTPUT_ONOFF   0
#define DISPLAY_SETTING_SUPPORT

#ifdef DUAL_VIDEO_OUTPUT
#undef DUAL_VIDEO_OUTPUT
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#undef DUAL_VIDEO_OUTPUT_USE_VCAP
#endif

#define TTX_SUB_PAGE
#define SUPPORT_PACKET_26

//not in M3327.mdf
#define LIB_TSI3_FULL
#define ENABLE_SERIAL_FLASH
#define SUPPORT_ERASE_UNKOWN_PACKET //for ttx

#if (defined(_CAS9_CA_ENABLE_)||defined(_BC_CA_STD_ENABLE_)||defined(_BC_CA_ENABLE_)||defined(_FTA_ONLY_))
    #undef SYS_PROJECT_SM
    #define SYS_PROJECT_SM              PROJECT_SM_CA

    #ifdef SDIO_SUPPORT
    #undef SDIO_SUPPORT
    #endif

    #ifdef AV_DELAY_SUPPORT
    #undef AV_DELAY_SUPPORT
    #endif

    #ifdef SATA_SUPPORT
    #undef SATA_SUPPORT
    #endif

    #ifdef WIFI_SUPPORT
    #undef WIFI_SUPPORT
    #endif
#endif

#ifndef _BUILD_OTA_E_
#define DVR_PVR_SUPPORT
#define USB_MP_SUPPORT
#define RECORD_SUPPORT
#define USB_SAFELY_REMOVE_SUPPORT
#define USB_UPGRADE_SUPPORT_LONG_FILENAME
#define DVR_PVR_SUPPORT_SUBTITLE    1
#else
    #ifdef _BUILD_USB_LOADER_
    //#define USB_SAFELY_REMOVE_SUPPORT
    #define USB_UPGRADE_SUPPORT_LONG_FILENAME
    #undef MEDIAPLAYER_SUPPORT
    #else
    #undef USB_MP_SUPPORT
#endif
#endif

#define SYS_OS_TASK_NUM         128
#define SYS_OS_SEMA_NUM         512
#define SYS_OS_FLAG_NUM         256
#define SYS_OS_MSBF_NUM         64
#define SYS_OS_MUTX_NUM         512

#ifdef HDTV_SUPPORT
#define AVC_MEM_LEN     0x1898400
#endif

/************************************************************
other ui and ap use macro
**************************************************************/
//#define SUPPORT_TWO_TUNER
#define GLOBAL_MOTOR_ANTENNA_SETTING
#ifndef SUPPORT_TWO_TUNER
    #define SELECT_SAT_ONLY
#endif
#define SEARCH_DEFAULT_FTAONLY 0
#define DISK_MANAGER_SUPPORT

#define EPG_MULTI_TP
#define EPG_OTH_SCH_SUPPORT
#define _EPG_MULTI_SERVICE
#define GET_TOTAL_SCH_EPG
#define EPG_FAST_PARSE
#define EPG_NETWORK_PATCH
#define SUPPORT_POP_SUBT

#if (defined(DVBC_SUPPORT) || defined(DVBS_SUPPORT) || defined(DVBT_SUPPORT))
#define AUTO_UPDATE_TPINFO_SUPPORT
#endif

/* OTA data backup */
#define OTA_POWEROFF_SAFE
#define OTA_START_BACKUP_FLAG   0xFF
#define OTA_START_END_FLAG  0xFE
#define BACKUP_START_FLAG   0x55aa5a5a

#define SUPPORT_DUAL_OUTPUT_ONOFF   0
#define DISPLAY_SETTING_SUPPORT

#define AUDIO_DEF_CH_L              0x00
#define AUDIO_DEF_CH_R              0x01
#define AUDIO_DEF_CH_STEREO         0x02
#define AUDIO_DEF_CH_MONO           0x03

#define DEFAULT_AUDIO_CHANNEL       AUDIO_DEF_CH_STEREO

#define MEDIA_PLAYER_VIDEO_SUPPORT

// for video decoder
#define __MM_MPG_DEC_START_ADDR     (__MM_OSD_START_ADDR + __MM_OSD_LEN)
#define __MM_MPG_DEC_LEN            (__MM_VBV_START_ADDR - __MM_MPG_DEC_START_ADDR)
#define SYSTEM_BUF_BLOCK_SIZE       2324
#define SYSTEM_BUF_MAX_BLOCK        4

#define DB_RAM_BACKUP

#define NEW_DEMO_FRAME

#define DB_PIP_SPE_USE

#define MULTI_PARTITION_SUPPORT
#define MULTI_VOLUME_SUPPORT

#define OGG_36
#define OSDLAYER_CONFIG

#define DTG_CHAR  //for spec char display
#define GB2312_SUPPORT //to show CCTV5...

#ifdef _USE_32M_MEM_
#define SYS_SDRAM_SIZE 32
    #ifndef _32M_PVR_
        #define DISABLE_USB
    #endif
#else
#define SYS_SDRAM_SIZE 64
#endif

// Some logic blocks
#if (SYS_SDRAM_SIZE == 32)

#define __MM_SHARED_MEM_LEN     256

#define __MM_SEE_MP_BUF_LEN         0
#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_PRIVATE_SHARE_LEN  0x830000//0x8C0000//0x00a00000//10M
#else
/* solution 3 */
#define __MM_PRIVATE_SHARE_LEN  (0x830000+0x198000)
#endif
#define __MM_VOID_BUFFER_LEN        0//0x100000//0//0x00200000  //2M
#define __MM_PRIVATE_LEN            (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

#define __MM_HIGHEST_ADDR           0xa2000000//32M

#define __MM_VOID_BUFFER_ADDR   (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)
#define __MM_SHARE_BASE_ADDR    (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR   (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR       (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)    //20M

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_MAIN_TOP_ADDR      0xa17D0000//0xa1600000//22MB
#else
/* solution 3 */
#define __MM_MAIN_TOP_ADDR      0xa17D0000 - 0x198000
#endif
#ifdef _CAS9_VSC_ENABLE_
#define __MM_VSC_CODE_START_ADDR    __MM_PRIVATE_ADDR
#define __MM_VSC_DATA_START_ADDR (__MM_VSC_CODE_START_ADDR+__MM_VSC_CODE_LEN)
#endif
#define OSD_VSRC_MEM_MAX_SIZE   0x65400//0xCA800//0x195000//0x200000//0x400000  //2M
#define __MM_OSD_VSRC_MEM_ADDR  (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE)
#define __MM_FB_TOP_ADDR        __MM_OSD_VSRC_MEM_ADDR

#if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
#ifndef AUI
#error "__MM_PRIVATE_ADDR address error"
#endif
#endif

//for link only*********************************
#ifdef _32M_PVR_
    #ifdef H264_32M_SUPPORT

    #ifndef M3281_SOLUTION3_SUPPORT
        #define __MM_PVR_VOB_BUFFER_LEN  ((47*1024)*(45*2)+0x1000)//((47*1024)*(50*2)+0x1000)//((47*1024)*(68*2)+0x1000)
        #define __MM_FP_OSD_VSC_LEN       (720*576)
    #else
        #define __MM_PVR_VOB_BUFFER_LEN  (((47*1024)*(50*2)+0x1000) - 0x198000) /* solution 3 */
    #endif

    #else
        #define __MM_PVR_VOB_BUFFER_LEN  ((47*1024)*(68*2)+0x1000)//((47*1024)*(76*2)+0x1000)//0x6fb000//0
    #endif
#else
#define __MM_PVR_VOB_BUFFER_LEN 0
#endif

#define __MM_MP_BUFFER_ADDR 0
#define __MM_MP_BUFFER_LEN      0

#define __MM_SEE_MP_BUF_ADDR    0
#define __MM_SEE_MP_BUF_LEN 0

#define __MM_FB0_Y_LEN          0
#define __MM_FB1_Y_LEN          0
#define __MM_FB2_Y_LEN          0

#define __MM_FB0_C_LEN          0
#define __MM_FB1_C_LEN          0
#define __MM_FB2_C_LEN          0

#define __MM_FB3_Y_LEN          0
#define __MM_FB3_C_LEN          0
#define __MM_FB4_Y_LEN          0
#define __MM_FB4_C_LEN          0
#define __MM_FB5_Y_LEN          0
#define __MM_FB5_C_LEN          0
#define __MM_FB6_Y_LEN          0
#define __MM_FB6_C_LEN          0

#define __MM_FB0_Y_START_ADDR   0
#define __MM_FB0_C_START_ADDR   0
#define __MM_FB1_Y_START_ADDR   0
#define __MM_FB1_C_START_ADDR   0
#define __MM_FB2_Y_START_ADDR   0
#define __MM_FB2_C_START_ADDR   0
#define __MM_FB3_Y_START_ADDR   0
#define __MM_FB3_C_START_ADDR   0
#define __MM_FB4_Y_START_ADDR   0
#define __MM_FB4_C_START_ADDR   0
#define __MM_FB5_Y_START_ADDR   0
#define __MM_FB5_C_START_ADDR   0
#define __MM_FB6_Y_START_ADDR   0
#define __MM_FB6_C_START_ADDR   0

#ifdef H264_32M_SUPPORT
#define MAX_EXTRA_FB_NUM 3

#define MAX_MB_WIDTH 46//45 //(720/16)
#define MAX_MB_HEIGHT 36//36 //(576/16)
#define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance

#define one_frm_y_size      (MAX_MB_STRIDE*((MAX_MB_HEIGHT+1)/2)*512)
#define one_frm_c_size   (MAX_MB_STRIDE*((((MAX_MB_HEIGHT+1)/2)+1)/2)*512)
#define ONE_FB_SIZE (one_frm_y_size + one_frm_c_size)

#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4)
#define ONE_MV_SIZE 64*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#define const_frm_num   5
#define AVC_FB_LEN      ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN      ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x12000//0x11000 will cause overflow

#define AVC_MB_NEI_LEN      0x8000
//In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#define AVC_CMD_QUEUE_LEN 0x10000
#undef  AVC_LAF_RW_BUF_LEN
#define AVC_LAF_RW_BUF_LEN (((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

#define AVC_LAF_FLAG_BUF_LEN (0xc00*22) //when enable dual output, we need 1 more laf buffer

#define AVC_VBV_LEN     0x180000

#define AVC_FB_ADDR         ((__MM_FB_TOP_ADDR -  AVC_FB_LEN )&0xfffffe00)          //512 bytes alignment
#define AVC_DVIEW_ADDR      ((AVC_FB_ADDR -  AVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define AVC_MV_ADDR         ((AVC_DVIEW_ADDR - AVC_MV_LEN)&0xffffff00)          //256 bytes alignment
#define AVC_MB_COL_ADDR     ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR     ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_LAF_RW_BUF_ADDR   ((AVC_MB_NEI_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment

#else /* else of H264_32M_SUPPORT */
#define AVC_VBV_ADDR __MM_VBV_START_ADDR//0, in see
#define AVC_VBV_LEN  0x10000//0

#define AVC_FB_ADDR  __MM_FB_START_ADDR//0
#ifdef AVC_FB_LEN
#undef AVC_FB_LEN
#endif
#define AVC_FB_LEN   0x10000//0

#define AVC_DVIEW_ADDR (AVC_FB_ADDR+AVC_FB_LEN)//0
#define AVC_DVIEW_LEN   0

#define AVC_MV_ADDR  (AVC_DVIEW_ADDR+AVC_DVIEW_LEN)//0
#ifdef AVC_MV_LEN
#undef AVC_MV_LEN
#endif
#define AVC_MV_LEN   0x10000//0

#define AVC_MB_COL_ADDR (AVC_MV_ADDR+AVC_MV_LEN)//0
#define AVC_MB_COL_LEN 0x10000//0

#define AVC_MB_NEI_ADDR (AVC_MB_COL_ADDR+AVC_MB_COL_LEN)//0
#ifdef AVC_MB_NEI_LEN
#undef AVC_MB_NEI_LEN
#endif
#define AVC_MB_NEI_LEN  0x1000//0

#define AVC_CMD_QUEUE_ADDR (AVC_VBV_ADDR+AVC_VBV_LEN)//0, in see
#define AVC_CMD_QUEUE_LEN  0x10000//0

#define AVC_LAF_RW_BUF_ADDR (AVC_MB_NEI_ADDR+AVC_MB_NEI_LEN)//0
#ifdef AVC_LAF_RW_BUF_LEN
#undef AVC_LAF_RW_BUF_LEN
#endif
#define AVC_LAF_RW_BUF_LEN  0x10000//0

#define AVC_LAF_FLAG_BUF_ADDR (AVC_CMD_QUEUE_ADDR+AVC_CMD_QUEUE_LEN)//0, in see

#ifdef AVC_LAF_FLAG_BUF_LEN
#undef AVC_LAF_FLAG_BUF_LEN
#endif
#define AVC_LAF_FLAG_BUF_LEN  0x10000//0

#endif  /* end of H264_32M_SUPPORT */

#define __MM_DMX_REC_START_ADDR 0
//end**************************************************

#define __MM_FB_LEN             0x308400//(16*SD>3*HD)

#define __MM_MAF_LEN            0x51C00//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )

#define __MM_DVW_LEN            0//0X25FA0

#define __MM_FB_START_ADDR      ((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFF00)

// for satcodx memmap
#define __MM_DVW_START_ADDR         ((__MM_FB_START_ADDR - __MM_DVW_LEN)&0XFFFFFFF0)

#define MAX_EXTRA_FB_NUM 3

#define MAX_MB_WIDTH 46//45 //(720/16)
#define MAX_MB_HEIGHT 36//36 //(576/16)

#define __MM_GMA1_LEN           0 // 0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN           0 // 0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN       0 // 0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN                0 // 0x6DB0 // command buffer

#define __MM_GE_LEN             0//(__MM_GMA1_LEN+__MM_GMA2_LEN+__MM_TEMP_BUF_LEN+__MM_CMD_LEN) //0xBE45B0
#define __MM_OSD_LEN                (720*576)//(720*576*2)//(1280 * 720 *2)// 720*576

#define __MM_OSD1_LEN           (720*576)
#define __MM_OSD2_LEN           (720*576)

#ifdef H264_32M_SUPPORT
#define __MM_SEE_OSD_LEN        0
#define __MM_VBV_LEN                0x12C000
#else
#define __MM_VBV_LEN                0x14d000//0x46800//0x12C000//(HD = 8*SD > 4*SD)
#endif

#define __MM_DMX_SI_LEN         (32*188)//(16*188)
#define __MM_DMX_SI_TOTAL_LEN   (__MM_DMX_SI_LEN*44)

#define __MM_SI_VBV_OFFSET      __MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN       (30*188)
#define __MM_DMX_PCR_LEN        (10*188)
#define __MM_DMX_AUDIO_LEN      (256*188)//(32*188)
#ifdef H264_32M_SUPPORT
#define __MM_DMX_VIDEO_LEN      (10*512*188)//(12*512*188)//(8*512*188)
#else
#define __MM_DMX_VIDEO_LEN      (12*512*188)//(8*512*188)
#endif

#define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)

#ifdef H264_32M_SUPPORT
#define __MM_DMX_BLK_BUF_LEN    0x80000//0xbc000
#else
#define __MM_DMX_BLK_BUF_LEN    0xbc000
#endif

#ifdef H264_32M_SUPPORT

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_SUB_BS_LEN         0//0xA000 //0X2800
#define __MM_SUB_PB_LEN         0//0X19000
#else

/* solution 3 */
#define __MM_SUB_BS_LEN         0xA000
#define __MM_SUB_PB_LEN         0X19000
#endif

#else
#define __MM_SUB_BS_LEN         0xA000 //0X2800
#define __MM_SUB_PB_LEN         0X19000
#endif

#define __MM_SUB_HW_DATA_LEN 0

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN     0x8FC0
#define __MM_ISDBTCC_PB_LEN     0x7E900
#endif

#if (CC_ON==1)
#define OSD_CC_WIDTH      576//480//480//704//480//(CC_CHAR_W*40+16)//560//704(16bytes aligned)
#define OSD_CC_HEIGHT     390//360//300//360//300//450//(CC_CHAR_H*15)//500//570
#define CC_CHAR_HEIGHT      26

#define __MM_ATSC_CC_PB_RECT_LEN (OSD_CC_WIDTH*OSD_CC_HEIGHT)
#define __MM_ATSC_CC_PB_LEN  (__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0x1c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
#else
#define __MM_ATSC_CC_PB_LEN 0
#define __MM_ATSC_CC_BS_LEN 0
#endif

#ifdef H264_32M_SUPPORT

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_TTX_BS_LEN         0//0x5000//0X2800
#define __MM_TTX_PB_LEN             0//0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0//0x14500 //80*1040
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
#else

/* solution 3 */

// TTX
#define __MM_TTX_BS_LEN         0x5000//0X2800
#ifdef TTX_SUB_PAGE
#define __MM_TTX_PB_LEN             0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0x14500 //80*1040
#else
#define __MM_TTX_PB_LEN             0xCA800 //+80*1040 //
#define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
#endif
#ifdef SUPPORT_PACKET_26
#define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
#define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
#else
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
#endif
#endif

#else
// TTX
#define __MM_TTX_BS_LEN         0x5000//0X2800
#ifdef TTX_SUB_PAGE
#define __MM_TTX_PB_LEN             0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0x14500 //80*1040
#else
#define __MM_TTX_PB_LEN             0xCA800 //+80*1040 //
#define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
#endif
#ifdef SUPPORT_PACKET_26
#define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
#define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
#else
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
#endif
#endif

#define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)

#define __MM_USB_DMA_LEN                0   // 0x10FFFF currently not use
#ifdef H264_32M_SUPPORT
#define __MM_EPG_BUFFER_LEN             0x96000//0xC8000//0x100000
#else
#define __MM_EPG_BUFFER_LEN             0xC8000//0x100000
#endif
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000

#define __MM_VCAP_FB_SIZE               0

#define __MM_DBG_MEM_LEN   0x4000

#define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR

#ifdef H264_32M_SUPPORT
#define __MM_EPG_BUFFER_START       (AVC_LAF_RW_BUF_ADDR - __MM_EPG_BUFFER_LEN)
#else
#define __MM_EPG_BUFFER_START       (__MM_DVW_START_ADDR - __MM_EPG_BUFFER_LEN)
#endif

#ifdef __MM_FP_OSD_VSC_LEN
#define __MM_FP_OSD_VSC_ADDR        ((__MM_EPG_BUFFER_START - __MM_FP_OSD_VSC_LEN)&0XFFFFFFE0)
#define __MM_OSD_BK_ADDR3           ((__MM_FP_OSD_VSC_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)//for ca fingerprint
#else
#define __MM_OSD_BK_ADDR3           ((__MM_EPG_BUFFER_START - __MM_OSD2_LEN)&0XFFFFFFE0)//for ca fingerprint
#endif
#define __MM_AUTOSCAN_DB_BUFFER_ADDR    (__MM_OSD_BK_ADDR3 - __MM_AUTOSCAN_DB_BUFFER_LEN)
#define __OTA_ADDR_LEN  0X200000
#define __OTA_ADDR (__MM_AUTOSCAN_DB_BUFFER_ADDR - __OTA_ADDR_LEN)

#define __MM_PVR_VOB_BUFFER_ADDR (__MM_OSD_BK_ADDR3 - __MM_PVR_VOB_BUFFER_LEN)

#ifdef _32M_PVR_
#define __MM_DMX_AVP_START_ADDR ((__MM_PVR_VOB_BUFFER_ADDR  - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN \
                                                                    - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#else
#define __MM_DMX_AVP_START_ADDR ((__OTA_ADDR  - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#endif

#define __MM_DMX_CPU_BLK_ADDR       ((__MM_DMX_AVP_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)

#ifndef _32M_PVR_//(defined DVBC_SUPPORT && defined DVBC_NIM_MODE_J83B)
    #define __MM_NIM_BUFFER_LEN         0x200000//2M
#else
    #define __MM_NIM_BUFFER_LEN         0x0
#endif
#define __MM_NIM_BUFFER_ADDR            (__MM_DMX_CPU_BLK_ADDR - __MM_NIM_BUFFER_LEN)

#ifdef _M36F_SINGLE_CPU
// for m36f single cpu mode(only test for ali internal)
// move osd, vsrc, scap buffer to private buffer base.
#define __MM_LWIP_MEM_ADDR          (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
#else
#define __MM_OSD_BK_ADDR1           ((__MM_NIM_BUFFER_ADDR - __MM_OSD_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#endif
#define __MM_DCII_SUB_BS_START_ADDR (__MM_VCAP_FB_ADDR - __MM_DCII_SUB_BS_LEN)

#define __MM_CPU_DBG_MEM_ADDR       (__MM_DCII_SUB_BS_START_ADDR - __MM_DBG_MEM_LEN)
//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/
#define __MM_VBV_START_ADDR         ((__MM_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR         ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_DEVOUR_START_ADDR          ((__MM_MAF_START_ADDR - (0xd00 * 2) )&0XFFFFFC00)

#ifdef H264_32M_SUPPORT

#define AVC_VBV_ADDR                (__MM_PRIVATE_TOP_ADDR - AVC_VBV_LEN)   //256 bytes alignment
    #if (AVC_VBV_ADDR <= __MM_DEVOUR_START_ADDR)
    #define __MM_DMX_SEE_BLK_ADDR   ((AVC_VBV_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #else
    #define __MM_DMX_SEE_BLK_ADDR   ((__MM_DEVOUR_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #endif
#else
#define __MM_DMX_SEE_BLK_ADDR           ((__MM_DEVOUR_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#endif

#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - __MM_TTX_SUB_PAGE_LEN)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
#define __MM_TTX_BS_START_ADDR  ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR  ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_PB_START_ADDR  ((__MM_TTX_PB_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_BS_START_ADDR  ((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)

#ifdef H264_32M_SUPPORT
#define AVC_CMD_QUEUE_ADDR  ((__MM_ATSC_CC_BS_START_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)   //256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_OSD_BK_ADDR2       ((AVC_LAF_FLAG_BUF_ADDR - __MM_SEE_OSD_LEN)&0XFFFFFFF0)
#else  /* solution 3 */
#define __MM_OSD_BK_ADDR2       ((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFF0)
#endif

#else
#define __MM_OSD_BK_ADDR2       ((__MM_ATSC_CC_BS_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
#endif

#define __MM_SUB_BS_START_ADDR  ((__MM_OSD_BK_ADDR2  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR  ((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)
#define __MM_SUBT_ATSC_SEC_ADDR (__MM_SUB_PB_START_ADDR - __MM_SUBT_ATSC_SEC_LEN)

#ifdef ISDBT_CC
    #define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
    #define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
    #define __MM_SEE_DBG_MEM_ADDR      (__MM_ISDBTCC_PB_START_ADDR - __MM_DBG_MEM_LEN)
#else
    #define __MM_SEE_DBG_MEM_ADDR      (__MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)
#endif
//end of Private mem map

#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR


#elif (SYS_SDRAM_SIZE == 64)
/* memory mapping

== limitations
1. AVC and MPEG2 decoder both use about 30MB memory, MPEG2 requires one 32MB segment,
    so we put decoder buffer between [64MB, 96MB], start from 96MB and go down.
2. DMX dma buffer should under same 8M segment.
    __MM_DMX_AVP_START_ADDR, and __MM_DMX_REC_START_ADDR, must under same 8M segment,

    [126,128]  2MB -- cpu memory -- void memory, left to customer
    [96, 126] 30MB -- see memory -- private memory
    [64 , 96] 32MB -- cpu memory -- Video Decoder buffer
    [30 , 64] 34MB -- cpu memory -- PVR VOB buffer.
    [15 , 30] 15MB -- cpu memory -- Device Buffer: DMX, GE, OSD, VCAP, USB, EPG, DB, LWIP, etc.
    [0  , 15] 15MB -- cpu memory -- main code + heap

*/
#ifdef DVR_PVR_SUPPORT
    #ifdef SD_PVR
        #define __MM_PVR_VOB_BUFFER_LEN     ((47*1024)*(76*2)+0x1000)//0x6fb000
    #else
        #define __MM_PVR_VOB_BUFFER_LEN             ((47*1024)*(240*3)+0x1000)
    #endif
#else
//when define _BUILD_OTA_E_,DVR_PVR_SUPPORT don't define,pvr len will affect dmx start address align.
    #define __MM_PVR_VOB_BUFFER_LEN     ((47*1024)*(76*2)+0x1000)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE 0
#endif

#define __MM_SHARED_MEM_LEN     256
#ifdef HW_SECURE_ENABLE
    #define __MM_SEE_MP_BUF_LEN     0x00900000  //9M
    #ifdef SD_PVR
        #define __MM_PRIVATE_SHARE_LEN  0x01900000//0x01e00000  //26M
    #else
        #define __MM_PRIVATE_SHARE_LEN  0x01e00000  //30M
    #endif
    #define __MM_VOID_BUFFER_LEN    0x00100000  //2M
#else
    #define __MM_SEE_MP_BUF_LEN     0
    #define __MM_PRIVATE_SHARE_LEN  0x01e00000  //30M
    #define __MM_VOID_BUFFER_LEN    0x00200000  //2M
#endif
#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

#define __MM_HIGHEST_ADDR   0xa4000000      //64M

#define __MM_VOID_BUFFER_ADDR   (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)  //126M or 114M

#define __MM_SHARE_BASE_ADDR    (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR   (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR       (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)    //96M

#ifdef _CAS9_VSC_ENABLE_
#define __MM_VSC_CODE_START_ADDR    __MM_PRIVATE_ADDR
#define __MM_VSC_DATA_START_ADDR (__MM_VSC_CODE_START_ADDR+__MM_VSC_CODE_LEN)
#endif
#ifdef SD_PVR
    #define __MM_MAIN_TOP_ADDR      0xa2600000//0xa2000000      //36MB
    #define __MM_OSD_VSRC_MEM_ADDR  (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE)
    #define __MM_FB_TOP_ADDR        __MM_OSD_VSRC_MEM_ADDR      //32MB
#else
    #define __MM_FB_TOP_ADDR        0xa6000000      //96MB
#endif

#ifdef SD_PVR
    #if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
    #ifndef AUI
    #error "__MM_PRIVATE_ADDR address error"
    #endif
    #endif
#else
    #if(__MM_FB_TOP_ADDR != __MM_PRIVATE_ADDR)
    #ifndef AUI
    #error "__MM_PRIVATE_ADDR address error"
    #endif
    #endif
#endif

#define __MM_FB_LEN_DEVIDED     0X32A000//(HD:1920X1152X1.5)
#ifndef SD_PVR
#ifdef VIDEO_DEBLOCKING_SUPPORT
#define __MM_FB_LEN             0x10CF200//0x19c6200
#else
#define __MM_FB_LEN             0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
#endif
#define __MM_MAF_LEN            0x198C00//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#else
    #ifdef VIDEO_DEBLOCKING_SUPPORT
    #define __MM_FB_LEN             0x61BC00//0x10CF200//0x19c6200
    #else
    #define __MM_FB_LEN             0x308400//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
    #endif
    #define __MM_MAF_LEN            0X8C000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#endif
#define __MM_DVW_LEN            0

#define __MM_FB_START_ADDR      ((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFF00)

// for satcodx memmap
#define __MM_DVW_START_ADDR         ((__MM_FB2_C_START_ADDR - 0X25FA0)&0XFFFFFFF0)

#define MAX_EXTRA_FB_NUM 3
#ifndef SD_PVR
    #define MAX_MB_WIDTH 120 //(1920/16)
    #define MAX_MB_HEIGHT 68 //(1088/16)
#else
    #define MAX_MB_WIDTH 46//45 //(720/16)
    #define MAX_MB_HEIGHT 36//36 //(576/16)
#endif

#ifdef H264_SUPPORT_MULTI_BANK
    #ifndef SD_PVR
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
    #endif
#define EXTRA_FB_SIZE 0x2000
#define ONE_FB_SIZE (((MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2+EXTRA_FB_SIZE-1)&0xffffe000)+EXTRA_FB_SIZE)
#else
    #ifndef SD_PVR
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
    #endif

    #ifdef SD_PVR
        #define one_frm_y_size      (MAX_MB_STRIDE*((MAX_MB_HEIGHT+1)/2)*512)
        #define one_frm_c_size   (MAX_MB_STRIDE*((((MAX_MB_HEIGHT+1)/2)+1)/2)*512)
        #define ONE_FB_SIZE (one_frm_y_size + one_frm_c_size)
    #else
        #define ONE_FB_SIZE (MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2)
    #endif
#endif

#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4)
#define ONE_MV_SIZE 64*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifndef SD_PVR
#define AVC_FB_LEN      ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN      ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x22000
#else
#define const_frm_num   5
#define AVC_FB_LEN      ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN      ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x12000//0x11000 will cause overflow
#endif

#define AVC_MB_NEI_LEN      0x8000
//In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#define AVC_CMD_QUEUE_LEN 0x10000
#undef  AVC_LAF_RW_BUF_LEN

#define AVC_LAF_RW_BUF_LEN (((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

#define AVC_LAF_FLAG_BUF_LEN (0xc00*22) //when enable dual output, we need 1 more laf buffer

#ifndef SD_PVR
    //for CI+, must use 4MB. if this size is set to 0x200000, vbv buffer overflow could happen in 20061007d_0.ts
    #define AVC_VBV_LEN     0x400000
#else
    #define AVC_VBV_LEN     0x180000
#endif
#define AVC_FB_ADDR         ((__MM_FB_TOP_ADDR -  AVC_FB_LEN )&0xfffffe00)          //512 bytes alignment
#define AVC_DVIEW_ADDR      ((AVC_FB_ADDR -  AVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define AVC_MV_ADDR         ((AVC_DVIEW_ADDR - AVC_MV_LEN)&0xffffff00)          //256 bytes alignment
#define AVC_MB_COL_ADDR     ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR     ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_LAF_RW_BUF_ADDR   ((AVC_MB_NEI_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment

#define __MM_GMA1_LEN           0 // 0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN           0 // 0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN       0 // 0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0 // 0x6DB0 // command buffer

#define __MM_GE_LEN             (__MM_GMA1_LEN+__MM_GMA2_LEN+__MM_TEMP_BUF_LEN+__MM_CMD_LEN) //0xBE45B0
#define __MM_OSD_LEN            (720*576*2)//(1280 * 720 *2) // 720*576
#ifndef SD_PVR
#define __MM_OSD1_LEN           (1280*720*4)
#define __MM_OSD2_LEN           (1920*1080)
#else
#define __MM_OSD1_LEN           (720*576)//(720*576*4)
#define __MM_OSD2_LEN           (720*576)
#endif

#define OSD_VSRC_MEM_MAX_SIZE   0x400000    //300*1024

#ifndef SD_PVR
#define __MM_VBV_LEN            0x200000
#else
#define __MM_VBV_LEN            0x12C000//(HD = 8*SD > 4*SD)
#endif

#define __MM_DMX_SI_LEN         (32*188)//(16*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define EXTRA_VIDEO_NUM 3
    #define __MM_DMX_SI_TOTAL_LEN   (__MM_DMX_SI_LEN*(44-EXTRA_VIDEO_NUM))
#else
    #define __MM_DMX_SI_TOTAL_LEN   (__MM_DMX_SI_LEN*44)
#endif

#define __MM_SI_VBV_OFFSET      __MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN       (30*188)
#define __MM_DMX_PCR_LEN        (10*188)
#define __MM_DMX_AUDIO_LEN      (256*188)//(32*188)
#define __MM_DMX_VIDEO_LEN      (12*512*188)//(8*512*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define __MM_DMX_EXTRA_VIDEO_LEN (960*188)
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_EXTRA_VIDEO_LEN*EXTRA_VIDEO_NUM\
                                                                +__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#else
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#endif
#define __MM_DMX_BLK_BUF_LEN    0xbc000

#define __MM_SUB_BS_LEN         0xA000 //0X2800

#ifdef HD_SUBTITLE_SUPPORT
    #define __MM_SUB_PB_LEN         0xA0000 //0x50000//0X19000(1920X340 for hd subt)
#else
    #define __MM_SUB_PB_LEN         0X19000
#endif

#ifdef SUPPORT_HW_SUBT_DECODE
#define __MM_SUB_HW_DATA_LEN 0xC000
#else
#define __MM_SUB_HW_DATA_LEN 0
#endif

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN     0x8FC0
#define __MM_ISDBTCC_PB_LEN     0x7E900
#endif

#if (CC_ON==1)
#define OSD_CC_WIDTH      576//480//480//704//480//(CC_CHAR_W*40+16)//560//704(16bytes aligned)
#define OSD_CC_HEIGHT     390//360//300//360//300//450//(CC_CHAR_H*15)//500//570
#define CC_CHAR_HEIGHT      26

#define __MM_ATSC_CC_PB_RECT_LEN (OSD_CC_WIDTH*OSD_CC_HEIGHT)
#define __MM_ATSC_CC_PB_LEN  (__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0x1c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
#else
#define __MM_ATSC_CC_PB_LEN 0
#define __MM_ATSC_CC_BS_LEN 0
#endif

// TTX
#define __MM_TTX_BS_LEN         0x5000//0X2800
#ifdef TTX_SUB_PAGE
#define __MM_TTX_PB_LEN             0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0x14500 //80*1040
#else
#define __MM_TTX_PB_LEN             0xCA800 //+80*1040 //
#define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
#endif
#ifdef SUPPORT_PACKET_26
#define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
#define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
#else
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
#endif

#define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)

#define __MM_USB_DMA_LEN                0   // 0x10FFFF currently not use
#define __MM_EPG_BUFFER_LEN             0x100000
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000

#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN               0

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*4)
#else
#define __MM_VCAP_FB_SIZE               0
#endif
#define __MM_DBG_MEM_LEN   0x4000

#if (__MM_FB_START_ADDR < AVC_LAF_RW_BUF_ADDR)
#define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR
#else
#define __MM_FB_BOTTOM_ADDR         AVC_LAF_RW_BUF_ADDR
#endif

#define __MM_BUF_PVR_TOP_ADDR       __MM_FB_BOTTOM_ADDR
#define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)

#ifdef _MHEG5_V20_ENABLE_
#define __MM_MHEG5_BUFFER_ADDR      (__MM_PVR_VOB_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
#define __MM_DMX_AVP_START_ADDR     ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN \
                                                                    - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#else
#define __MM_DMX_AVP_START_ADDR     ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN\
                                                                    - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#endif

#define __MM_DMX_REC_START_ADDR     (__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)
#define __MM_DMX_CPU_BLK_ADDR       ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)

#define __MM_OSD_BK_ADDR3           ((__MM_EPG_BUFFER_START - __MM_OSD2_LEN)&0XFFFFFFE0)//for ca fingerprint

#if 1//(defined DVBC_SUPPORT && defined DVBC_NIM_MODE_J83B)
    #define __MM_NIM_BUFFER_LEN         0x00200000//__MM_VOID_BUFFER_LEN//2M
#else
    #define __MM_NIM_BUFFER_LEN         0x0
#endif
#define __MM_NIM_BUFFER_ADDR        ((__MM_OSD_BK_ADDR3 - __MM_NIM_BUFFER_LEN)&0XFFFFFFE0)

#define __MM_GE_START_ADDR          ((__MM_NIM_BUFFER_ADDR - __MM_GE_LEN)&0XFFFFFFE0)
#ifdef _M36F_SINGLE_CPU
// for m36f single cpu mode(only test for ali internal)
// move osd, vsrc, scap buffer to private buffer base.
#define __MM_LWIP_MEM_ADDR          (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
#else
#define __MM_OSD_BK_ADDR1           ((__MM_GE_START_ADDR - __MM_OSD_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #ifndef SD_PVR
    #define __MM_OSD_VSRC_MEM_ADDR      (__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)
    #define __MM_LWIP_MEM_ADDR          (__MM_OSD_VSRC_MEM_ADDR - __MM_LWIP_MEM_LEN)
    #else
    #define __MM_LWIP_MEM_ADDR          (__MM_VCAP_FB_ADDR - __MM_LWIP_MEM_LEN)
    #endif
#endif
#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR         ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)
//#define __MM_DCII_SUB_BS_START_ADDR (__MM_USB_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_CPU_DBG_MEM_ADDR       (__MM_USB_START_ADDR - __MM_DBG_MEM_LEN)

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR

//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/
#define __MM_VBV_START_ADDR         ((__MM_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_DEVOUR_START_ADDR                          ((__MM_VBV_START_ADDR - (0xd00 * 2))&0XFFFFFC00)
#define __MM_MAF_START_ADDR         ((__MM_DEVOUR_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define AVC_VBV_ADDR                (__MM_PRIVATE_TOP_ADDR - AVC_VBV_LEN)   //256 bytes alignment

#if (AVC_VBV_ADDR <= __MM_MAF_START_ADDR)
#define __MM_DMX_SEE_BLK_ADDR   ((AVC_VBV_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#else
#define __MM_DMX_SEE_BLK_ADDR   ((__MM_MAF_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#endif

#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - __MM_TTX_SUB_PAGE_LEN)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
#define __MM_TTX_BS_START_ADDR  ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR  ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
#define __MM_SEE_MP_BUF_ADDR    (__MM_TTX_PB_START_ADDR -  __MM_SEE_MP_BUF_LEN)

#define AVC_CMD_QUEUE_ADDR  ((__MM_SEE_MP_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define __MM_OSD_BK_ADDR2       ((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)

#define __MM_SUB_BS_START_ADDR  ((__MM_OSD_BK_ADDR2  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR  ((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_PB_START_ADDR  ((__MM_SUB_PB_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_BS_START_ADDR  ((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)

#define __MM_DCII_SUB_BS_START_ADDR (__MM_ATSC_CC_BS_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_SUBT_ATSC_SEC_ADDR (__MM_DCII_SUB_BS_START_ADDR - __MM_SUBT_ATSC_SEC_LEN)


#ifdef _M36F_SINGLE_CPU
// for m3f single cpu(only test for ali internal)
// more osd, vsrc, scap buffer to private buffer base.
#define __MM_OSD_BK_ADDR1           ((__MM_SUBT_ATSC_SEC_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#define __MM_OSD_VSRC_MEM_ADDR      (__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)
#define __MM_SEE_DBG_MEM_ADDR      (__MM_OSD_VSRC_MEM_ADDR - __MM_DBG_MEM_LEN)
    #if(__MM_SEE_DBG_MEM_ADDR < __MM_PRIVATE_ADDR)
        #ifndef AUI
        #error "__MM_SEE_DBG_MEM_ADDR address error"
        #endif
    #endif
#else

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#define __MM_SEE_DBG_MEM_ADDR      (__MM_ISDBTCC_PB_START_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_SEE_DBG_MEM_ADDR      (__MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)
#endif
#endif

// for jpeg decoder memmap
#ifdef SD_PVR
#define __MM_FB0_Y_LEN          (736*576 + 1024)
#else
#define __MM_FB0_Y_LEN          (1920*1088+1024)//(736*576+512) //for high definition jpg decode
#endif
#define __MM_FB1_Y_LEN          __MM_FB0_Y_LEN
#define __MM_FB2_Y_LEN          __MM_FB0_Y_LEN

#define __MM_FB0_C_LEN          (__MM_FB0_Y_LEN/2)
#define __MM_FB1_C_LEN          __MM_FB0_C_LEN
#define __MM_FB2_C_LEN          __MM_FB0_C_LEN

#define __MM_FB3_Y_LEN          (736*576+1024)
#define __MM_FB3_C_LEN          (__MM_FB3_Y_LEN/2)
#define __MM_FB4_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB4_C_LEN          __MM_FB3_C_LEN
#define __MM_FB5_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB5_C_LEN          __MM_FB3_C_LEN
#define __MM_FB6_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB6_C_LEN          __MM_FB3_C_LEN

#ifdef HW_SECURE_ENABLE
#ifdef SD_PVR
    #define __MM_FB0_Y_START_ADDR   (__MM_TTX_P26_DATA_BUF_ADDR & 0xFFFFFE00)
    #define __MM_FB0_C_START_ADDR   (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

    #define __MM_FB1_Y_START_ADDR   ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
    #define __MM_FB1_C_START_ADDR   ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

    #define __MM_FB2_Y_START_ADDR   ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
    #define __MM_FB2_C_START_ADDR   ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

    #if (__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN > __MM_PRIVATE_TOP_ADDR)
    #ifndef AUI
    #error "jpeg frame buffer overflow ! please check it"
    #endif
    #endif

    #define __MM_FB3_Y_START_ADDR   0 //((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR   0 //((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR   0 //((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR   0 //((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR   0 //((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR   0 //((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR   0 //((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR   0 //((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
    #define __MM_MP_BUFFER_LEN      (__MM_TTX_BS_START_ADDR - __MM_SEE_MP_BUF_ADDR)
    #define __MM_MP_BUFFER_ADDR     __MM_SEE_MP_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
#else
    #define __MM_FB0_Y_START_ADDR   (__MM_SEE_MP_BUF_ADDR & 0xFFFFFE00)
    #define __MM_FB0_C_START_ADDR   (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

    #define __MM_FB1_Y_START_ADDR   ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
    #define __MM_FB1_C_START_ADDR   ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

    #define __MM_FB2_Y_START_ADDR   ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
    #define __MM_FB2_C_START_ADDR   ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

    #define __MM_FB3_Y_START_ADDR   0 //((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR   0 //((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR   0 //((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR   0 //((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR   0 //((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR   0 //((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR   0 //((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR   0 //((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
    #define __MM_MP_BUFFER_LEN      (__MM_PRIVATE_TOP_ADDR - __MM_TTX_P26_DATA_BUF_ADDR)
    #define __MM_MP_BUFFER_ADDR     __MM_TTX_P26_DATA_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
#endif
#else
    #define __MM_FB0_Y_START_ADDR   (__MM_FB_START_ADDR)
    #define __MM_FB0_C_START_ADDR   (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

    #define __MM_FB1_Y_START_ADDR   ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
    #define __MM_FB1_C_START_ADDR   ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

    #define __MM_FB2_Y_START_ADDR   ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
    #define __MM_FB2_C_START_ADDR   ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

    #define __MM_FB3_Y_START_ADDR   ((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR   ((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR   ((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR   ((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR   ((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR   ((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR   ((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR   ((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
#ifdef DVR_PVR_SUPPORT
    #define __MM_MP_BUFFER_LEN          __MM_PVR_VOB_BUFFER_LEN
    #define __MM_MP_BUFFER_ADDR         __MM_PVR_VOB_BUFFER_ADDR
#else
    #define __MM_MP_BUFFER_LEN          0x1000000
    #define __MM_MP_BUFFER_ADDR         ((__MM_FB2_C_START_ADDR - __MM_MP_BUFFER_LEN)&0XFFFFFFF0)
#endif
#endif
//end of Private mem map

#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR

#endif //#elif (SYS_SDRAM_SIZE == 64)

#ifdef HW_SECURE_ENABLE
#define __MM_VIDEO_FILE_BUF_ADDR    __MM_SEE_MP_BUF_ADDR
#define __MM_VIDEO_FILE_BUF_LEN     (__MM_PRIVATE_TOP_ADDR - __MM_SEE_MP_BUF_ADDR)
#else
#define __MM_VIDEO_FILE_BUF_ADDR    __MM_MP_BUFFER_ADDR
#define __MM_VIDEO_FILE_BUF_LEN     __MM_MP_BUFFER_LEN
#endif

#if (256 == COLOR_N)
#define BIT_PER_PIXEL       8
#define     OSD_TRANSPARENT_COLOR       0xFF
#define     OSD_TRANSPARENT_COLOR_BYTE  0xFF
#define IF_GLOBAL_ALPHA FALSE
#elif (16 == COLOR_N)
#define BIT_PER_PIXEL       4
#define     OSD_TRANSPARENT_COLOR       15
#define     OSD_TRANSPARENT_COLOR_BYTE  0xFF
#define IF_GLOBAL_ALPHA FALSE
#elif(4 == COLOR_N)
#define BIT_PER_PIXEL       2
#define     OSD_TRANSPARENT_COLOR       3
#define     OSD_TRANSPARENT_COLOR_BYTE 0xFF
#define IF_GLOBAL_ALPHA TRUE
#endif

#if     (BIT_PER_PIXEL  == 2)
#define FACTOR                  2
#elif   (BIT_PER_PIXEL    == 4)
#define FACTOR                  1
#elif   (BIT_PER_PIXEL     == 8)
#define FACTOR                  0
#endif
/***********************************************************************
 AP feature support  maro define
*************************************************************************/
#define  LOGO_ID_TYPE 0x02FD0000
#define  LOGO_ID            (LOGO_ID_TYPE | 0x0100)
#define  MENU_LOGO_ID   (LOGO_ID_TYPE | 0x0100)
#define  RADIO_LOGO_ID  (LOGO_ID_TYPE | 0x0100)
#define  MEDIA_LOGO_ID  (LOGO_ID_TYPE | 0x0100)
#define  BOOT_LOGO_ID   (LOGO_ID_TYPE | 0x0100)
#define  MAINCODE_ID        0x01FE0101
#define KEY_STORE_ID        0x21DE0100
#define OTA_LOADER_ID   0x00FF0100
#define SEECODE_ID       0x06F90101
#define DECRYPT_KEY_ID  0x22DD0100
#define HDCPKEY_CHUNK_ID (HDCPKEY_CHUNID_TYPE |0x0100)
#define STBINFO_ID       0x20DF0100
#define  CADATA_ID      0x05FA0100
#define  DEFAULT_DB_ID  0x03FC0100
#define USER_DB_ID       0x04FB0100
#define CIPLUSKEY_CHUNK_ID 0x09F60101
#define CHUNKID_VSC_CODE 0x0CF30101

//for erom upg
#define BK_PLAIN_CHUNK_ID       0x03FC0101
#define UK_PLAIN_CHUNK_ID       0x03FC0102
#define EROM_CLIENT_ID          0x03FC0103
#define EROM_SEE_CLIENT_ID      0x03FC0104

#define EROM_CLIENT_ADDR __MM_DMX_AVP_START_ADDR //__MM_PVR_VOB_BUFFER_ADDR //for erom client abs
#define EROM_CLIENT_LEN 0x30000 //erom client abs max len
#define EROM_SEE_CLIENT_ADDR (EROM_CLIENT_ADDR+EROM_CLIENT_LEN) //for erom see client abs
#define EROM_SEE_CLIENT_LEN 0x30000 //erom see client abs max len
#define FW_ADDR     (EROM_SEE_CLIENT_ADDR+EROM_SEE_CLIENT_LEN)  //for fw.abs
#define FW_LEN      0x400000    //fw.abs max len
#define UK_PLAIN_ADDR       (FW_ADDR+FW_LEN)    //for fw.abs
#define UK_PLAIN_LEN        0x10000

#define BINCODE_COMPRESSED
#define OTA_STATIC_SWAP_MEM
//----------------------------------------------------------

#define VIDEO_SUPPORT_EXTRA_DVIEW_WINDOW
#define VDEC27_SUPPORT_COLORBAR
//#define VIDEO_OVERSHOOT_SOLUTION
#define VIDEO_SYNC_ISSUE

//#define ANTENNA_INSTALL_BEEP  2

/* If define ANTENNA_INSTALL_BEEP ==1,
    then DVBT_BEE_TONE have effect,
   else if (ANTENNA_INSTALL_BEEP == 2)
    then AUDIO_SPECIAL_EFFECT have effect */

//#define AUDIO_SPECIAL_EFFECT    /* play mpeg audio file*/
//#define ASE_EXT
//#define DVBT_BEE_TONE   /* continues beep*/

#define CODEC_I2S (0x0<<1)
#define CODEC_LEFT (0x1<<1)
#define CODEC_RIGHT (0x2<<1)

#define EASY_DM_SWITCH
#define PSI_MONITOR_PAT_SUPPORT

#define KEYBOARD_SUPPORT

/* If "RAM_TMS_TEST" is defined, MUST re-define "RAM_DISK_ADDR" and "RAM_DISK_SIZE".
 *  1. RAM_DISK_ADDR: MUST NOT share with other module.
 *  2. RAM_DISK_SIZE: MUST (>= 14MByte) for SD and (>= 32MByte) for HD.
 */
#ifdef RAM_TMS_TEST
    #define RAM_DISK_ADDR   __MM_PVR_VOB_BUFFER_ADDR
    #define RAM_DISK_SIZE   ((__MM_PVR_VOB_BUFFER_LEN / (47*1024) / 3) * (47*1024))
#endif
/***********************************************************
AP and UI  use GPIO configure
************************************************************/
#define SYS_12V_SWITCH      SYS_FUNC_OFF

#if(SYS_MAIN_BOARD >= BOARD_SB_S3602F_QFP_01V01 && SYS_MAIN_BOARD < BOARD_S3602F_MAX)

#undef  SYS_GPIO_MODULE
#define SYS_GPIO_MODULE M3602F_GPIO

#define SYS_LNB_POWER_OFF   SYS_FUNC_ON

#define VDAC_USE_CVBS_TYPE      CVBS_1
#define VDAC_USE_RGB_TYPE       RGB_1
#define VDAC_USE_YUV_TYPE       YUV_1

#define CVBS_DAC                DAC3

#if (SYS_MAIN_BOARD == BOARD_SB_S3602F_QFP_01V01)
#define RGB_DAC_R               DAC2
#define RGB_DAC_G               DAC0
#define RGB_DAC_B               DAC1

#define YUV_DAC_Y               DAC0
#define YUV_DAC_U               DAC1
#define YUV_DAC_V               DAC2
#else
#define YUV_DAC_Y               DAC1
#define YUV_DAC_U               DAC0
#define YUV_DAC_V               DAC2

#define RGB_DAC_R               DAC2
#define RGB_DAC_G               DAC1
#define RGB_DAC_B               DAC0
#endif
#endif

#ifdef _BUILD_OTA_E_
    #undef CI_SLOT_DYNAMIC_DETECT
    #define DMX_XFER_V_ES_BY_DMA    //added for s3601. transfer video ES by DMA, others by CPU copy
    #undef CC_USE_TSG_PLAYER
    #undef CI_STREAM_PASS_MATCH_CARD
    #undef MP2_0_SUPPORT
    #undef MULTI_VOLUME_SUPPORT
    #undef PS_TS_SUPPORT
    #undef DYNAMIC_PID_SUPPORT
    #undef SUPPORT_DEO_HINT
    #undef AUTOMATIC_STANDBY
    #undef MP_SUBTITLE_SUPPORT
    #undef SUPPORT_MPEG4_TEST
    #undef SHOW_ALI_DEMO_ON_SCREEN
    #undef SUPPORT_DRAW_EFFECT
    #undef AUDIO_DESCRIPTION_SUPPORT
    #undef RAM_TMS_TEST
    #undef MULTI_CAS
    #undef CAS_TYPE
    #undef SUPPORT_HW_CONAX
    #undef SUPPORT_CAS9
    #undef CAS9_PVR_SUPPORT
    #undef AV_DELAY_SUPPORT
    #define DSC_SUPPORT
    #undef AUTO_UPDATE_TPINFO_SUPPORT
    #undef PVR_DYNAMIC_PID_CHANGE_TEST
#endif

//below need clear
#ifdef DVBC_SUPPORT
    #define DVBC_COUNTRY_BAND_SUPPORT
    #define QAM_ONLY_USAGE      SYS_FUNC_OFF
    #define SYS_DEM_BASE_ADDR   0x42    //0x40
    //#define TUNER_I2C_BYPASS
#endif

#ifdef DVBS_SUPPORT
#define SYS_PROJECT_FE              PROJECT_FE_DVBS
#elif defined  DVBT_SUPPORT
#define SYS_PROJECT_FE              PROJECT_FE_DVBT
#elif defined  ISDBT_SUPPORT
#define SYS_PROJECT_FE              PROJECT_FE_ISDBT
#elif defined  DVBC_SUPPORT
#define SYS_PROJECT_FE              PROJECT_FE_DVBC
#else
#ifndef AUI
#error "not define SYS_PROJECT_FE"
#endif
#endif
//#define SYS_DEM_MODULE                ALI_S3501
#ifdef DVBC_SUPPORT
  #define FE_DVBC_SUPPORT
#endif
#ifdef DVBS_SUPPORT
  #define FE_DVBS_SUPPORT
#endif
#define SYS_TUN_MODULE              ANY_TUNER //IX2410 
// I2C config same for all M3602 board now
#define I2C_FOR_TUNER           I2C_TYPE_SCB0
#define I2C_FOR_HZ6303          I2C_TYPE_SCB0
#define I2C_FOR_S3501           I2C_TYPE_SCB0

#ifdef MP_SUBTITLE_SUPPORT
#define MP_SUBTITLE_SETTING_SUPPORT //for mp ext subtitle setting support:font size/fg_color/bg_color/position
#endif

#ifndef CHECKCHUNK_ENABLE
//#define CHECKCHUNK_ENABLE
#endif


#ifdef __cplusplus
 }
#endif

#endif  // __SYS_CONFIG_H
