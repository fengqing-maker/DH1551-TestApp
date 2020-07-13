#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H

#include <sys_define.h>

#define M36F_CHIP_MODE

#ifdef _BOARD_SB_M3511_01V01_
#define SYS_MAIN_BOARD BOARD_SB_M3511_01V01
#elif defined _BOARD_SB_M3512_01V01_
#define SYS_MAIN_BOARD BOARD_SB_M3512_01V01
#elif defined _BOARD_SB_M3515_01V01_
#define SYS_MAIN_BOARD BOARD_SB_M3515_01V01
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_SB_M3516_01V01_
#define SYS_MAIN_BOARD BOARD_SB_M3516_01V01
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_DB_M3511_01V01_
#define SMC2_SUPPORT
#define SYS_MAIN_BOARD BOARD_DB_M3511_01V01
#elif defined _BOARD_DB_M3511_01V02_
#define SMC2_SUPPORT
#define SYS_MAIN_BOARD BOARD_DB_M3511_01V02
#elif defined _BOARD_DB_M3512_01V01_
#define SYS_MAIN_BOARD BOARD_DB_M3512_01V01
#define SMC1_SUPPORT
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_DB_M3515_01V01_
#define SYS_MAIN_BOARD BOARD_DB_M3515_01V01
#define SMC1_SUPPORT
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_DB_M3515_01V04_
#define SYS_MAIN_BOARD BOARD_DB_M3515_01V04
#define SMC1_SUPPORT
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_DB_M3515B_01V01_
//#define BOARD_DB_M3515B_01V02 //M3515B new board
#define SYS_MAIN_BOARD BOARD_DB_M3515B_01V01
#define SMC1_SUPPORT
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_DB_M3516_01V01_
#define SYS_MAIN_BOARD BOARD_DB_M3516_01V01
#define SMC1_SUPPORT
#define SUPPORT_TWO_TUNER
#elif defined _BOARD_SB_M3715_01V01_
#define SYS_MAIN_BOARD BOARD_SB_M3715_01V01
#elif defined _BOARD_DB_M3715_01V01_
#define SYS_MAIN_BOARD BOARD_DB_M3715_01V01
#define SMC1_SUPPORT
#ifndef _M3503B_
#define SUPPORT_TWO_TUNER
#endif
//#define M3715_01v02
#elif defined(_BOARD_DB_M3315_01V01_)
#define SYS_MAIN_BOARD BOARD_DB_M3315_01V01
#define SMC1_SUPPORT
#define SUPPORT_TWO_TUNER
#else
#ifdef AUI
#else
    #error "BOARD define error,please check!"
#endif
#endif


#ifdef  _AUI_
#ifndef AUI
#define AUI
#endif
#endif

#ifdef  _AUI_TEST_
#define AUI_TEST
#endif

#ifdef _DVBC_ENABLE_
#define DVBC_SUPPORT
#define DVBC_NIM_MODE_J83B
#define DVBC_MODE_CHANGE
#endif

#ifdef _DVBS_ENABLE_
#define DVBS_SUPPORT
#endif

#ifdef _DVBT_ENABLE_
#define DVBT_SUPPORT
#endif

#ifdef _ISDBT_ENABLE_
#define ISDBT_SUPPORT
#endif
#ifdef _C0200A_CA_ENABLE_
#ifndef _RD_DEBUG_
#define DISABLE_PRINTF
#endif
#define SUPPORT_C0200A
#define MULTI_CAS
#define CAS_TYPE	CAS_C0200A
#define CHANCHG_VIDEOTYPE_SUPPORT
#define C0200A_PVR_SUPPORT
#ifdef _C0200A_CA_DAL_TEST_
#define DISABLE_PRINTF
#endif
#define HDCP_FROM_CE
#define HDCP_IN_FLASH
#endif

#define HDCP_FROM_CE
#define HDCP_IN_FLASH

/*************************/
#ifdef  _CAS7_CA_ENABLE_

#define SUPPORT_CAS7
#define MULTI_CAS
#define CAS_TYPE    CAS_CONAX

#define DSC_SUPPORT
#define CAS7_PVR_SUPPORT 1
#define AUDIO_CHANNEL_LANG_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define CONAX7_SPORT_MULTIDMX

#endif
/*************************/
#ifdef _DLNA_ENABLE_
  #define DLNA_SUPPORT
//  #define DLNA_CTT_TEST
#endif
#ifdef _DLNA_DMP_SUPPORT_
  #define DLNA_DMP_SUPPORT
#endif
#ifdef _DLNA_DMR_SUPPORT_
  #define DLNA_DMR_SUPPORT
#endif
#ifdef _DLNA_DMS_SUPPORT_
  #define DLNA_DMS_SUPPORT
#endif

#ifdef DLNA_CTT_TEST
  #define NETWORK_DISABLE_SEEK
#endif

#ifdef _SAT2IP_SERVER_ENABLE_
#define SAT2IP_SUPPORT
//#define SAT2IP_PATCH_FOR_DEMO
#define SAT2IP_SERVER_SUPPORT
#define MEDIA_PROVIDER_USE_RING_BUFFER
//#define FOR_DUBAI_EXP
#ifdef SUPPORT_CAS7
#define SAT2IP_REENCRYPT_REC
#endif
#endif
#ifdef _SAT2IP_CLIENT_ENABLE_
#define SAT2IP_SUPPORT
//#define SAT2IP_PATCH_FOR_DEMO
#define DSC_SUPPORT
#define SAT2IP_CLIENT_SUPPORT
#endif

#ifdef SAT2IP_SUPPORT
#define SAT2IP_MAX_SLOT  4
//#define SAT2IP_FIX_TUNER
#define SAT2IP_PRIVATE_PROTOCAL
#define SAT2IP_NEW_REQURIEMENT
#endif



#ifdef _LIB_UPNP_ENABLE_
#define LIB_UPNP_SUPPORT
#endif

#if (defined(_DLNA_DMS_SUPPORT_) && defined(_SAT2IP_SERVER_ENABLE_))
//#define SAT2IP_DMS_LIVE_SUPPORT
#endif
#define COMBOUI
#define GE_DRAW_OSD_LIB

#define TEMP_INFO_HEALTH

#define MULTIVIEW_SUPPORT
#ifdef SAT2IP_CLIENT_SUPPORT
#undef MULTIVIEW_SUPPORT
#endif
#ifdef DVBT_SUPPORT
#define SUPPORT_IRAN_CALENDAR
#define BIDIRECTIONAL_OSD_STYLE
#ifdef BIDIRECTIONAL_OSD_STYLE
#undef GE_DRAW_OSD_LIB
#endif
#endif

#if defined(_SD_ONLY_) && defined(_USE_64M_MEM_)
#define SD_PVR
#endif

#ifdef _C0200A_CA_ENABLE_
#undef MULTIVIEW_SUPPORT
#endif

#ifdef ISDBT_SUPPORT
#define ISDBT_CC        1
#define ISDBT_EPG
#define SUPPORT_WO_ONE_SEG  //has problem
#endif
#ifdef _WIFI_ENABLE_
    #define WIFI_SUPPORT
#endif
#ifdef _DVBT_ENABLE_
#ifndef _BUILD_OTA_E_
//#define SUPPORT_FRANCE_HD
#endif
#endif
#ifdef _DVBT_ENABLE_
#ifndef _BUILD_OTA_E_
//#define POLAND_SPEC_SUPPORT
#endif
#endif
#if (defined(DVBT_SUPPORT)||defined(ISDBT_SUPPORT))
#ifndef _BUILD_OTA_E_
#define AUTO_OTA
#endif
#endif

#ifdef  _SCPI_SUPPORT_
#define SCPI_SUPPORT
#endif

#ifdef AUTO_OTA
//#define NEW_MANUAL_OTA
#define FRANCE_HD_NETWORK_ID  0x20FA  //for Fance TNT spec check the network
#endif

#if (defined(POLAND_SPEC_SUPPORT)||defined(AUTO_OTA)||defined(SUPPORT_FRANCE_HD))
#define SUPPORT_TP_QUALITY
#endif

/* OTA Setting */
#define OTA_CONTROL_FLOW_ENHANCE
#define SYS_OUI                    0x090E6
#define SYS_HW_MODEL           0x3503
#define SYS_HW_VERSION            0x0000
#define SYS_SW_MODEL          0x0000
#define SYS_SW_VERSION        0x0001

#ifdef _BC_CA_STD_ENABLE_
#define OPERATOR_OTA_PID	0x100	//for osm upgrade trigger
#endif

#ifdef _BC_CA_ENABLE_
#undef SYS_HW_MODEL
#undef SYS_HW_VERSION
#undef SYS_SW_MODEL
#undef SYS_SW_VERSION
#define SYS_HW_MODEL        0x0001	//defined by customer
#define SYS_HW_VERSION		0x0001	//defined by customer
#define SYS_SW_MODEL		0x0001	//defined by customer
#define SYS_SW_VERSION		0x0001	//defined by customer
#define OPERATOR_OTA_PID	0x100	//for osm upgrade trigger

//Don't change below
#ifdef _BC_VER0_
#undef SYS_SW_VERSION
#define SYS_SW_VERSION        0x0000
#endif
#ifdef _BC_VER1_
#undef SYS_SW_VERSION
#define SYS_SW_VERSION		0x0001
#endif
#ifdef _BC_VER2_
#undef SYS_SW_VERSION
#define SYS_SW_VERSION		0x0002
#endif
#endif

#ifdef AUTO_OTA
//#define AUTO_OTA_SAME_VERSION_CHECK
#endif
#ifdef _MAC_TEST
//#define MAC_TEST
#endif
#ifndef _BUILD_OTA_E_
#if((defined _RD_DEBUG_) &&(defined DVBT_SUPPORT))
#define NIM_REG_ENABLE
#endif
#endif

#ifdef _REG_ENABLE
#define REG_ENABLE
#endif
//modify for adding welcome page when only open dvbt 2011 10 19
#if (defined (DVBT_SUPPORT) || defined (ISDBT_SUPPORT))
#define SHOW_WELCOME_FIRST
#endif
//modify end
#if defined ISDBT_SUPPORT || defined DVBT_SUPPORT
#define _DTGSI_ENABLE_
#if (defined(_DTGSI_ENABLE_))
#define SI_MODULE_CONFIG   // for DTG SI specification config in the si_config.h
#define LCN_VAR_RANGE 900
#endif
#define SYS_DVBT_DEMO_MODULE  MXL101  //DB3805 external fullnim
//#define SYS_DVBT_DEMO_MODULE COFDM_M3101 //DB3805 external fullnim

#define _LCN_ENABLE_

/* FRANCE_HD TNT Related Define */
#define HD_SERVICE_TYPE_SUPPORT  //support the HD service type in the SDT
#define DATABRODCAST_SERVICE_TO_TV  //support databroadcast service change type to TV service
#define PRIVATE_DATA_SPEC INVALID_PRIVATE_DATA_SPEC // remove the private data specification check

#endif

#ifndef DVBS_SUPPORT
#define PARENTAL_SUPPORT //open feature of partetal rating control
#define RATING_LOCK_WITH_PASSWORD
#define AGE_LIMIT_FEATURE
#endif
#define CSA_PARENTAL_CONTROL //With definition: user have 4 class of rating level to set: 10, 12, 16, 18 years.
                                                      // (TNT_CSA only with the 4class of rating level : 10, 12, 16, 18 years)
                                                      //without definition: 4,5,6,...~18 years.(spec in EN300468)

//#define SMC1_SUPPORT    // First SmartCard
//#define SMC2_SUPPORT    // Second SmartCard

/*Add for standby.*/
#define STANDBY_PAN_KEY1                         0x55
#define STANDBY_PAN_KEY2                         0xFF
#define STANDBY_IR_KEY1                            0x60df708f
#define STANDBY_IR_KEY2                            0xFFFFFFFF
#define STANDBY_IR_KEY3                            0xFFFFFFFF
#define STANDBY_IR_KEY4                            0xFFFFFFFF
#define STANDBY_PAN_KEY1_ADDR1              0xB8053FFB
#define STANDBY_PAN_KEY1_ADDR2              0xB8053FFC
//#define BOOT_STANDBY_ENABLE

/*When CPUSTANDBY_SHOW_TIME is defined, panel show time. Otherwise, it will show ' OFF'*/
#define CPUSTANDBY_SHOW_TIME

#define PMU_ENABLE
#ifdef PMU_ENABLE
//#define PMU_POWERSTANDBY_CLOSE
#endif
#define RTC_TIME_SUPPORT // RTC
//#define _SUPPORT_FAST_RESUME_ //software standby, support fast resume

#ifndef _BUILD_OTA_E_
//#define USB_LOGO_TEST
    #ifdef USB_LOGO_TEST
        #define EHCI_USB_LOGO_TEST //for M35/M37 EHCI USB Host
    #endif
#endif

#ifdef _DVBS_ENABLE_
#define SUPPORT_UNICABLE
#define SUPPORT_DISEQC11
#ifndef _BUILD_OTA_E_
#define MULTIFEED_SUPPORT
#endif
#define SUPPORT_TUN_AV2012      //for power standby, tuner switch to sleep mode if it is AV2012
#endif
//#define AUTO_SYANDBY_DEFAULT_ON
//#define ALI_SHUTTLE_MODIFY
#define UI_MEDIA_PLAYER_REPEAT_PLAY
//#define TVE_USE_FULL_CURRENT_MODE
#ifndef _RD_DEBUG_
#define WATCH_DOG_SUPPORT
#endif
//#define DO_DDP_CERTIFICATION
#define AFD_SW_SUPPORT
#define AFD_HW_SUPPORT
#if( defined (AFD_SW_SUPPORT)) || ( defined(AFD_HW_SUPPORT))
#define SUPPORT_AFD_PARSE
#define SUPPORT_AFD_SCALE
#define SUPPORT_AFD_WSS_OUTPUT
#endif
/*preview and fullview switch smoothly, smoothly switch needs more 5M for AVC*/
#define MP_PREVIEW_SWITCH_SMOOTHLY
/*if CHANCHG_VIDEOTYPE_SUPPORT supported 
(1)change channels with still or black frame
(2)dis fill black will backup a black frame
if not supported
(1)close vpo when change channels
(2)close vpo when call dis fill black*/
#define CHANCHG_VIDEOTYPE_SUPPORT
/*support dynamic relution needs more 1M for AVC*/
//#define DYNAMIC_RESOLUTION_SUPPORT
#define TVE_VDEC_PLUG_DETECT
#ifdef SAT2IP_CLIENT_SUPPORT
#ifdef CHANCHG_VIDEOTYPE_SUPPORT
#undef CHANCHG_VIDEOTYPE_SUPPORT
#endif
#endif

#ifdef _EROM_UPG_HOST_ENABLE_
#define ENABLE_EROM
#endif

#define PVR_DYNAMIC_PID_CHANGE_TEST    //dynamic v-pid change for h264<->mpg2
/* Add "RAM_TMS_TEST" for test: doing timeshift using RAM disk.
 * If open it, MUST re-define "RAM_DISK_ADDR" and "RAM_DISK_SIZE".
 */
//#define RAM_TMS_TEST

#ifndef _BUILD_OTA_E_
#ifdef _AUI_NEED_ALI_LIB_
#define ATSC_SUBTITLE_SUPPORT
#endif
#endif

//#ifdef ATSC_SUBTITLE_SUPPORT
#define __MM_DCII_SUB_BS_LEN (16*1024)
#define __MM_SUBT_ATSC_SEC_LEN (720*576)

#ifdef _SFU_TEST_SUPPORT
#define SFU_TEST_SUPPORT
#endif


#define BOARD_S3602F_MAX    (BOARD_SB_S3602F_QFP_01V01 + 100)

#define HDMI_TV_TEST
#define DUAL_VIDEO_OUTPUT_USE_VCAP
//#define DEO_VIDEO_QUALITY_IMPROVE
#define HDMI_1080P_SUPPORT
#define HDMI_ENABLE     //  enable HDMI in vpo driver because sabbat ui cannot disable it.
#define DRAM_SPLIT


#define OSD_16BIT_SUPPORT
#define OSD_VSRC_SUPPORT
#ifdef _SUPPORT_64M_MEM
#define FONT_1BIT_SUPPORT  // for reduce memery
#endif
#define USB_SUPPORT_HUB
#define VIDEO_DEBLOCKING_SUPPORT
#define GE_SIMULATE_OSD
#define AUDIO_DESCRIPTION_SUPPORT
#ifndef _BUILD_OTA_E_
    //#define CEC_SUPPORT
    //#define HDMI_CERTIFICATION_UI
#endif

/*************************/
#ifdef _CAS9_CA_ENABLE_
#define SUPPORT_CAS9
#define SUPPORT_HW_CONAX
#define MULTI_CAS
#define DSC_SUPPORT
#define CAS_TYPE    CAS_CONAX
#define HW_SECURE_ENABLE
//#define OTA_NO_VERION_CHK
#define MULTI_DESCRAMBLE
                //support multi_program descramble
#define CAS9_PVR_SUPPORT

    #ifdef _CAS9_SMC_DEBUG_
    #define CAS9_SMC_DEBUG
    #endif

        #ifndef _RD_DEBUG_
            #define DISABLE_PRINTF
            #define REMOVE_DEBUG_INFO
        #endif

        #define DISABLE_USB_UPG
        #ifndef DISABLE_USB_UPG
            #define USBUPG_ONLY_ALLCODE//remind:CA usb upg only support selection of all code!
        #endif

    #define CAS9_V6
    #ifdef CAS9_V6
        //#define RD_SKIP_APS
        #define CAS9_DA_MUTE
        #define CAS9_PVR_SID
        #define CAS9_URI_APPLY
        //#define HDCP_BY_URI //control HDCP enable/disable by URI
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
		#define VSC_SIGNATURE_LEN	256
		#define VSC_VERSION_LEN	16
		#define __MM_VSC_CODE_LEN	0x20000
		#define __MM_VSC_DATA_LEN 0x10000
		#define __MM_VSC_TOTAL_LEN (__MM_VSC_CODE_LEN+__MM_VSC_DATA_LEN)
    #endif
	#ifdef _CAS9_SC_UPG_
		#define CAS9_SC_UPG
	#endif
#define HDCP_FROM_CE
#define AUDIO_CHANNEL_LANG_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define    ENABLE_4M_FLASH
#define MEDIAPLAYER_SUPPORT
#define HMAC_CHECK_TEMP_INFO
#define DB_SUPPORT_HMAC
#undef AUDIO_DESCRIPTION_SUPPORT
#define CA_NO_CRC_ENABLE
#endif
/**************************/
#ifdef _BC_CA_STD_ENABLE_
#ifdef AFD_HW_SUPPORT
#undef AFD_HW_SUPPORT	//temp sol to fix ali teamtrack bug
#endif
#define DISABLE_PRINTF
#define HW_SECURE_ENABLE
#ifndef _BUILD_OTA_E_
	#define SUPPORT_BC_STD
	#define BC_NSC_SUPPORT
	#define BC_NEW_CC
	//#define SELF_TEST_ENABLE

	#ifdef SELF_TEST_ENABLE
		#define NEW_SELF_TEST
	#endif
#endif
#define BC_MULTI_DES_MAX 1
//#define _BC_STD_3281_
#define HDCP_FROM_CE
#define DSC_SUPPORT
#define CA_NO_CRC_ENABLE
//#define DISABLE_USB_UPG
#ifndef DISABLE_USB_UPG
	#define USBUPG_ONLY_ALLCODE
	#define BACKUP_USB_LOADER
#endif
#define BC_PVR_STD_SUPPORT
#ifdef BC_PVR_STD_SUPPORT
	#define BC_STD_PVR_CRYPTO 1
#endif

#define MEDIAPLAYER_SUPPORT

// PT Patch
#define BC_PATCH_BC_IOCTL				// only need to set call back once

//#define BC_PATCH_MMI_SET_SC_STATE		//	DVB C only
#ifdef _DVBC_ENABLE_
#define BC_PATCH_DVBC_DELIVERYDESP 	//	DVB C only
#endif
#define BC_PATCH_SW_CA 				//	STD BC only
#define BC_PATCH_SYS_GETBOXID			//	STD BC only
//#define BC_PATCH_BC_NSC_K_SC_HWERROR	//	STD BC only

// Channel change  (PT, sol from Jeremy)
//#define BC_PATCH_CC

// CAS (PT, sol from David,Jeremy)
//#define BC_PATCH_CAS

// UI and MISC Patch (PT, sol from Jeremy,Lowrance,Luca,etc)
#define BC_PATCH_UI

#define BC_PATCH_PURSE 				// Purse,IPPV Order related Code
#define BC_PATCH_NROSM_WM
#endif

#ifdef _BC_CA_ENABLE_
#ifndef _BUILD_OTA_E_
#define SUPPORT_BC
#define BC_NSC_SUPPORT //cardless support
#define BC_PVR_SUPPORT
#ifdef BC_PVR_SUPPORT
	#define BC_MULTI_DES_MAX 2 //maximum multi-decramble support for BC library
	#define BC_PVR_CHANNEL_ID_NUM 2 //maximum channel id support for BC library
#else
	#define BC_MULTI_DES_MAX 1
#endif
#define HW_SECURE_ENABLE
//#define SELF_TEST_ENABLE
#ifdef SELF_TEST_ENABLE
	#define NEW_SELF_TEST
	#define NEW_SELF_TEST_UART_ENABLE //enable the uart function supprot
#endif
#endif
#define HDCP_FROM_CE
#define DSC_SUPPORT
#define MEDIAPLAYER_SUPPORT
#define CA_NO_CRC_ENABLE
#define FAKE_VERITY_SIGNATURE
#define DISABLE_PRINTF
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
//#define DISABLE_USB_UPG
#ifndef DISABLE_USB_UPG
	#define USBUPG_ONLY_ALLCODE
	#define BACKUP_USB_LOADER
#endif
#ifdef _DVBC_ENABLE_
#define BC_PATCH_DVBC_DELIVERYDESP 	//	DVB C only
#endif
	#define PT_SC_PATCH //invert sc when nsc is available cause hangup problem
#ifdef BC_PVR_SUPPORT
	#define BC_PATCH_TRIGGER_STOP_REC //when trigger ota/rescan/switch, stop recording before do it
	#define BC_SWITCH_TO_PC_SUPPORT //handle pin code when replay a non-PC to PC recorded file
#endif
#endif

#ifdef _GEN_CA_ENABLE_
#define FTA_ONLY
#ifndef DSC_SUPPORT
#define DSC_SUPPORT
#endif
#define CA_NO_CRC_ENABLE
#define HW_SECURE_ENABLE

#define MEDIAPLAYER_SUPPORT
#define DISABLE_USB_UPG
#endif

#define AV_DELAY_SUPPORT
#ifdef OSD_16BIT_SUPPORT
//#define SUPPORT_DRAW_EFFECT
#else
#define HDOSD_DEO_OUTPUT
#endif

#ifdef _USB3G_SUPPORT_
#define USB3G_DONGLE_SUPPORT
#endif

#ifdef WIFI_SUPPORT
    #define SYS_NETWORK_MODULE     NET_ALIETHMAC
    #define USB_DRIVER_WIFI_SUPPORT
    #define NETWORK_SUPPORT
#else
    #define SYS_NETWORK_MODULE     NET_ALIETHMAC
#endif
#ifndef _C0200A_CA_ENABLE_
#define NETWORK_SUPPORT
#endif
#define SHOW_TWO_TUNER_LOCK_STATUS

//#define SDIO_SUPPORT


#ifdef _SHOW_ALI_DEMO_ON_SCREEN
#define SHOW_ALI_DEMO_ON_SCREEN
#endif

#ifdef _SATA_SUPPORT
#define SATA_SUPPORT
#endif

#ifndef SUPPORT_MPEG4_TEST
#define SUPPORT_MPEG4_TEST
#endif
#define AUDIOTRACK_SUPPORT
#define MP_SUBTITLE_SUPPORT
#define FS_STDIO_SUPPORT
#define RAM_DISK_SUPPORT

#define HDCP_IN_FLASH
//#define HDCP_FROM_CE

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
#define SYS_PSEARCH_SCAN_TP_ALL        SYS_FUNC_ON
#define SYS_PROJECT                    SYS_DEFINE_NULL
#if (SYS_MAIN_BOARD == BOARD_DB_M3515_01V01  || \
     SYS_MAIN_BOARD == BOARD_DB_M3516_01V01)
    #define SYS_PROJECT_SM            SYS_DEFINE_NULL
        //#define CI_ALLPASS_ENABLE
#else
    #define SYS_PROJECT_SM            SYS_DEFINE_NULL
#endif
#define SYS_OS_MODULE                ALI_TDS2
#define SYS_MW_MODULE                SYS_DEFINE_NULL
#define SYS_CA_MODULE                SYS_DEFINE_NULL
#define SYS_EPG_MODULE                SYS_DEFINE_NULL
#define SYS_CHIP_MODULE                ALI_S3602
#define SYS_CPU_MODULE                CPU_MIPS24KE
#define SYS_CPU_ENDIAN                ENDIAN_LITTLE
#define SYS_CHIP_CLOCK                27000000
#define SYS_GPIO_MODULE                M6303GPIO
#define SYS_I2C_MODULE                M6303I2C
#define SYS_I2C_SDA                    3
#define SYS_I2C_SCL                    4
#define SYS_SCI_MODULE                UART16550
#define SYS_TSI_MODULE                M3327TSI
#define SYS_FLASH_BASE_ADDR            0xafc00000
#ifdef _C0200A_CA_ENABLE_
#define SYS_FLASH_SIZE                0x800000
#else
#define SYS_FLASH_SIZE                0x400000
#endif
#define SYS_DMX_MODULE                M3327DMX
#define SYS_LNB_POWER_OFF            SYS_FUNC_ON
#define SYS_RFM_BASE_ADDR            0xca
#define SYS_IRP_MOUDLE                ROCK00
#define TABLE_BLOCK_SPACE_SIZE        (64 * 1024)
#define MAX_PROG_NUM                5000
#define MAX_TP_NUM                    3000
#define MAX_SAT_NUM                    65 //64

//modify for TTX and EPG share buffer 2011 10 10
/****ttx macro*********/
#ifdef _SUPPORT_64M_MEM
//#define TTX_EPG_SHARE_MEM
#endif

//reduce the space for ota
#ifndef _BUILD_OTA_E_
#if (ISDBT_CC != 1)
#ifdef _AUI_NEED_ALI_LIB_
//#define TTX_ON                        1
//#define SUBTITLE_ON                    1
#else
//#define TTX_ON                        0
//#define SUBTITLE_ON                    0
#endif
#endif
#else
//#define TTX_ON                        0
//#define SUBTITLE_ON                    0
#endif

#define TTX_BY_OSD
#define ALL_BY_VBI
#define TTX_BY_VBI
#define TTX_COLOR_NUMBER            256
#define DECODE_LIB_MAD                1
#define DECODE_LIB                    DECODE_LIB_MAD
#define VDEC_AV_SYNC
#define COLOR_N                        256
#define LOCAL_VSCR                    0
#define OSD_VSCREEN                    LOCAL_VSCR
#define OSD_MAX_WIDTH                1008
#define OSD_MAX_HEIGHT                640
#define LIST_SUPPORT                1
#define MATRIXBOX_SUPPORT            1
#define USB_MP_SUPPORT
#define ISO_5937_SUPPORT
#define DB_USE_UNICODE_STRING
#define NEW_DISEQC_LIB
#define OSD_STARTCOL                ((1280 - OSD_MAX_WIDTH)>>1)
#define OSD_STARTROW_N                ((720 - OSD_MAX_HEIGHT)>>1)
#define OSD_STARTROW_P                ((720 - OSD_MAX_HEIGHT)>>1)
#define AC3DEC                        1
#define PSI_MONITOR_SUPPORT
#define TTX_GREEK_SUPPORT
#define TTX_ARABIC_SUPPORT
#define TTX_ARABIC_G2_SUPPORT

#define DB_VERSION                    40
#define ALI_SDK_API_ENABLE


#define GPIO_NULL 127

//vicky20101229 dbg
/*****CC macro***********/
//#define CC_ON 1
#if(CC_ON ==1)
#define CC_BY_OSD   //vicky20110118
#define CC_BY_VBI
#define CC_MONITOR_CS   //vicky20110210
#define CC_MONITOR_CC   //vicky20110216
//End
#endif
#define TRUE_COLOR_HD_OSD
#ifndef DUAL_VIDEO_OUTPUT_USE_VCAP
    #define SYSCFG_SD_VIDEO // only support SD video decoder and SD display
#endif
//#define SD_PVR
#define PVR_FS_SH
//#define HD_SUBTITLE_SUPPORT
#ifndef SD_PVR
#define HD_SUBTITLE_SUPPORT
#endif

#ifdef SD_PVR
    //#define HD_SUBTITLE_SUPPORT
    #ifndef SYSCFG_SD_VIDEO
    #define SYSCFG_SD_VIDEO
    #endif
#endif
#define HDTV_SUPPORT
#define SUPPORT_DUAL_OUTPUT_ONOFF   0
#define DISPLAY_SETTING_SUPPORT

#ifdef SD_PVR
    #ifdef DUAL_VIDEO_OUTPUT
#undef DUAL_VIDEO_OUTPUT
    #endif
    #ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#undef DUAL_VIDEO_OUTPUT_USE_VCAP
    #endif
#endif

#define TTX_SUB_PAGE
#define SUPPORT_PACKET_26

//not in M3327.mdf
#define LIB_TSI3_FULL
#define ENABLE_SERIAL_FLASH
#define SUPPORT_ERASE_UNKOWN_PACKET //for ttx

#if (defined( _CAS9_CA_ENABLE_)||defined(_BC_CA_ENABLE_)||defined(_BC_CA_STD_ENABLE_)||defined(_GEN_CA_ENABLE_))
    #undef SYS_PROJECT_SM
    #define SYS_PROJECT_SM                PROJECT_SM_CA

    #ifdef SDIO_SUPPORT
    #undef SDIO_SUPPORT
    #endif

    #ifdef NETWORK_SUPPORT
    #undef NETWORK_SUPPORT
    #endif

    #ifdef AV_DELAY_SUPPORT
    #undef AV_DELAY_SUPPORT
    #endif

    #ifdef WIFI_SUPPORT
    #undef WIFI_SUPPORT
    #endif

    #ifdef MULTIVIEW_SUPPORT
    #undef MULTIVIEW_SUPPORT
    #endif
#endif

#ifdef _CAS7_CA_ENABLE_

    #undef SYS_PROJECT_SM
    #define SYS_PROJECT_SM                PROJECT_SM_CA
    #ifdef AV_DELAY_SUPPORT
    #undef AV_DELAY_SUPPORT
    #endif
    #ifdef SDIO_SUPPORT
    #undef SDIO_SUPPORT
    #endif
#endif
#if (SYS_PROJECT_SM ==PROJECT_SM_CI)
//#define CONFIG_SLOT_NUM    2//1,2
#define CONFIG_SLOT_NUM    1
#define PFLASH_CI_SHARE_PIN
#define CI_SLOT_NS        CONFIG_SLOT_NUM

#if (SYS_MAIN_BOARD == BOARD_DB_M3715_01V01 || SYS_MAIN_BOARD == BOARD_DB_M3515_01V01 || SYS_MAIN_BOARD == BOARD_DB_M3511_01V01)
    //#define CI_SUPPORT
#else
    #define CI_SUPPORT
#endif

//#define AUI_CI_SUPPORT

//#define SYS_PIN_MUX_MODE_04
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


#define SYS_OS_TASK_NUM            128
#define SYS_OS_SEMA_NUM            512
#define SYS_OS_FLAG_NUM            256
#define SYS_OS_MSBF_NUM            64
#define SYS_OS_MUTX_NUM            512

#if 0
#define SYS_OS_TASK_NUM            48
#define SYS_OS_SEMA_NUM            128
#define SYS_OS_FLAG_NUM            128
#define SYS_OS_MSBF_NUM            64   //32
#define SYS_OS_MUTX_NUM         256//128//64      //bill_wifi_20120613
#endif



/* Add "PNG_GIF_TEST" for test: If open it, PNG/GIF images can display on OSD".
 * Add "PIP_PNG_GIF" for test:
 * if open it, When full screen playing live stream, press a "PIP" key,
 * it will show a GIF file in OSD, press "PIP" key again, it will disappear,
 * but some animated GIF pictures will not display .
 * and this two define can not open at the same time
 */
//#define PNG_GIF_TEST
//#define PIP_PNG_GIF

/************************************************************
open Antiflicker
**************************************************************/
//#define ENABLE_ANTIFLICK


/************************************************************
other ui and ap use macro
**************************************************************/
#if (SYS_MAIN_BOARD == BOARD_DB_M3805_01V01)
#define SUPPORT_TWO_TUNER
#endif

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
//#define TRANSFER_FORMAT2_SUPPORT  // consistent with bootloader for P2P upgrade
//#define MULTI_CAS

#if (defined(DVBC_SUPPORT) || defined(DVBS_SUPPORT) || defined(DVBT_SUPPORT))
#define AUTO_UPDATE_TPINFO_SUPPORT
#endif

/* OTA data backup */
#define OTA_POWEROFF_SAFE
#define OTA_START_BACKUP_FLAG    0xFF
#define OTA_START_END_FLAG    0xFE
#define BACKUP_START_FLAG    0x55aa5a5a



#define SUPPORT_DUAL_OUTPUT_ONOFF   0
#define DISPLAY_SETTING_SUPPORT

#define AUDIO_DEF_CH_L                0x00
#define AUDIO_DEF_CH_R                0x01
#define AUDIO_DEF_CH_STEREO            0x02
#define AUDIO_DEF_CH_MONO            0x03

#define DEFAULT_AUDIO_CHANNEL        AUDIO_DEF_CH_STEREO


#define MEDIA_PLAYER_VIDEO_SUPPORT

// for video decoder
#define __MM_MPG_DEC_START_ADDR     (__MM_OSD_START_ADDR + __MM_OSD_LEN)
#define __MM_MPG_DEC_LEN            (__MM_VBV_START_ADDR - __MM_MPG_DEC_START_ADDR)
#define SYSTEM_BUF_BLOCK_SIZE        2324
#define SYSTEM_BUF_MAX_BLOCK        4

#define DB_RAM_BACKUP

#define NEW_DEMO_FRAME

#ifdef NEW_DEMO_FRAME
  #define DB_PIP_SPE_USE
#else
  // for ChChg TSG player
  #define CC_USE_TSG_PLAYER
  // define these 2 macro just for pass compile under NEW_DEMO_FRAME
  #define CI_SEND_CAPMT_OK_TO_APP
//#define CI_SLOT_DYNAMIC_DETECT
#endif

#ifdef NETWORK_SUPPORT
    #ifndef SYS_NETWORK_MODULE
        #define SYS_NETWORK_MODULE        SMSC9220    //NET_ENC28J60
    #endif

    #if (SYS_NETWORK_MODULE == NET_ENC28J60)
        #define STO_PROTECT_BY_MUTEX
    #endif
#endif

//#define IDE_SUPPORT

#define MULTI_PARTITION_SUPPORT
#define MULTI_VOLUME_SUPPORT

#if (!defined(_CAS9_CA_ENABLE_) && !defined(_BC_CA_ENABLE_) && !defined(_BC_CA_STD_ENABLE_))
#define MP_SPECTRUM            //support MP3 spectrum
#endif
#define OGG_36
#define OSDLAYER_CONFIG

//#define SUPPORT_DEO_HINT
#define DTG_CHAR  //for spec char display
#define GB2312_SUPPORT //to show CCTV5...

#ifdef _SUPPORT_64M_MEM
#define SYS_SDRAM_SIZE  64
#else
#define SYS_SDRAM_SIZE  128
#endif

#if (256 == COLOR_N)
#define    BIT_PER_PIXEL        8
#define     OSD_TRANSPARENT_COLOR        0xFF
#define     OSD_TRANSPARENT_COLOR_BYTE     0xFF
#define    IF_GLOBAL_ALPHA    FALSE
#elif (16 == COLOR_N)
#define    BIT_PER_PIXEL        4
#define     OSD_TRANSPARENT_COLOR        15
#define     OSD_TRANSPARENT_COLOR_BYTE     0xFF
#define    IF_GLOBAL_ALPHA    FALSE
#elif(4 == COLOR_N)
#define    BIT_PER_PIXEL        2
#define     OSD_TRANSPARENT_COLOR        3
#define     OSD_TRANSPARENT_COLOR_BYTE 0xFF
#define    IF_GLOBAL_ALPHA    TRUE
#endif

#if(BIT_PER_PIXEL    == 2)
#define    FACTOR                    2
#elif    (BIT_PER_PIXEL    == 4)
#define    FACTOR                    1
#elif    (BIT_PER_PIXEL     == 8)
#define    FACTOR                    0
#endif


/***********************************************************************
 AP feature support  maro define
*************************************************************************/
#define LOGO_ID_TYPE       0x02FD0000
#define LOGO_ID            (LOGO_ID_TYPE | 0x0100)
#define MENU_LOGO_ID       (LOGO_ID_TYPE | 0x0100)
#define RADIO_LOGO_ID      (LOGO_ID_TYPE | 0x0100)
#define MEDIA_LOGO_ID      (LOGO_ID_TYPE | 0x0100)
#define BOOT_LOGO_ID       (LOGO_ID_TYPE | 0x0100)
#define MAINCODE_ID        0x01FE0101
#define KEY_STORE_ID       0x21DE0100
#define OTA_LOADER_ID      0x00FF0100
#define SEECODE_ID         0x06F90101
#define DECRYPT_KEY_ID     0x22DD0100
#define HDCPKEY_CHUNK_ID   (HDCPKEY_CHUNID_TYPE |0x0100)
#define STBINFO_ID         0x20DF0100
#define CADATA_ID          0x05FA0100
#define DEFAULT_DB_ID      0x03FC0100
#define USER_DB_ID         0x04FB0100
#define CIPLUSKEY_CHUNK_ID 0x09F60101
#define CHUNKID_VSC_CODE   0x0CF30101
#define BOOTLOADER_CHUNK_ID 0x23010010

#ifdef _EROM_UPG_HOST_ENABLE_
//for erom upgrade --->
#define BK_PLAIN_CHUNK_ID		0x03FC0101
#define UK_PLAIN_CHUNK_ID		0x03FC0102
#define EROM_CLIENT_ID			0x03FC0103
#define EROM_SEE_CLIENT_ID		0x03FC0104

#define EROM_CLIENT_ADDR __MM_DMX_AVP_START_ADDR //__MM_PVR_VOB_BUFFER_ADDR	//for erom client abs
#define EROM_CLIENT_LEN	0x30000	//erom client abs max len
#define EROM_SEE_CLIENT_ADDR (EROM_CLIENT_ADDR+EROM_CLIENT_LEN)	//for erom see client abs
#define EROM_SEE_CLIENT_LEN	0x63000//0x30000	//erom see client abs max len
#define FW_ADDR		(EROM_SEE_CLIENT_ADDR+EROM_SEE_CLIENT_LEN)	//for fw.abs
#define FW_LEN		0x400000	//fw.abs max len
#define UK_PLAIN_ADDR		(FW_ADDR+FW_LEN)	//for fw.abs
#define UK_PLAIN_LEN		0x10000
// < --- erom upgrade end
#endif

#ifdef _MPLOADER_UPG_HOST_ENABLE_
//for mploader upgrade --->
#define FW_ADDR                __MM_DMX_AVP_START_ADDR
#define FW_LEN                 0x800000	//fw.abs max len

#define MPLOADERCLIENT_OFFSET  0x620000 //mploader client block's offset from flash begin
#define MPLOADERCLIENT_SIZE    0x20000
#define PK_BACKUP_OFFSET      (MPLOADERCLIENT_OFFSET+MPLOADERCLIENT_SIZE) //pk backup block's offset from flash begin
#define PK_BACKUP_SIZE         0x10000
#define SWUK_BACKUP_OFFSET    (PK_BACKUP_OFFSET+PK_BACKUP_SIZE) //sw_uk backup block's offset from flash begin
#define SWUK_BACKUP_SIZE       0x10000

#define MPLOADERCLIENT_ADDR   (SYS_FLASH_BASE_ADDR - 0x800000 + MPLOADERCLIENT_OFFSET)
#define SWUK_BACKUP_ADDR      (SYS_FLASH_BASE_ADDR - 0x800000 + SWUK_BACKUP_OFFSET)
#define PK_BACKUP_ADDR        (SYS_FLASH_BASE_ADDR - 0x800000 + PK_BACKUP_OFFSET)

#define MPLOADERCLIENT_HEAD_SIZE      4   //the size of mploader_client head(len), 4byte
#define MPLOADERCLIENT_SIGNATURE_SIZE 132 //the size of mploader_client signature

#define SWUK_OFFSET            0x1080
#define SWUK_SIZE              0x50
#define PK_OFFSET              0x1400
#define PK_SIZE                0x258
#define USERDB_OFFSET          0x490000
#define USERDB_SIZE            0x150000
#define RECOVERYMEMORY_OFFSET  0x610000
#define RECOVERYMEMORY_SIZE    0x10000
// < --- mploader upgrade end
#endif

#define BINCODE_COMPRESSED
#define OTA_STATIC_SWAP_MEM

#define VIDEO_SUPPORT_EXTRA_DVIEW_WINDOW
#define VDEC27_SUPPORT_COLORBAR
//#define VIDEO_OVERSHOOT_SOLUTION
#define VIDEO_SYNC_ISSUE



#define ANTENNA_INSTALL_BEEP    2

/* If define ANTENNA_INSTALL_BEEP ==1,
    then DVBT_BEE_TONE have effect,
   else if (ANTENNA_INSTALL_BEEP == 2)
       then AUDIO_SPECIAL_EFFECT have effect */
#define AUDIO_SPECIAL_EFFECT    /* play mpeg audio file*/
#define ASE_EXT
#define DVBT_BEE_TONE    /* continues beep*/
//#define ALI_SDK_API_ENABLE


#define CODEC_I2S (0x0<<1)
#define CODEC_LEFT (0x1<<1)
#define CODEC_RIGHT (0x2<<1)


#define EASY_DM_SWITCH
#define PSI_MONITOR_PAT_SUPPORT

#define KEYBOARD_SUPPORT

/* If "RAM_TMS_TEST" is defined, MUST re-define "RAM_DISK_ADDR" and "RAM_DISK_SIZE".
 *    1. RAM_DISK_ADDR: MUST NOT share with other module.
 *    2. RAM_DISK_SIZE: MUST (>= 14MByte) for SD and (>= 32MByte) for HD.
 */
#ifdef RAM_TMS_TEST
    #define RAM_DISK_ADDR    __MM_PVR_VOB_BUFFER_ADDR
    #define RAM_DISK_SIZE    ((__MM_PVR_VOB_BUFFER_LEN / (47*1024) / 3) * (47*1024))
#endif


/***********************************************************
AP and UI  use GPIO configure
************************************************************/
#define EXTERNAL_PULL_HIGH        TRUE    // for I2C_gpio.c

// comon function
#define SYS_12V_SWITCH        SYS_FUNC_OFF


#if (SYS_MAIN_BOARD == BOARD_DB_M3606_01V01)
#ifndef USB_MP_SUPPORT
#undef  MULTI_VOLUME_SUPPORT
#endif

#endif
//modify for adding welcome page when only open dvbt 2011 10 17
#ifdef RECORD_SUPPORT
#define PVR_AUTO_STANDBY_SUPPORT
#endif
//modify end

#undef  SYS_GPIO_MODULE
#define SYS_GPIO_MODULE M3602F_GPIO

#define SYS_LNB_POWER_OFF   SYS_FUNC_ON
//add for set DacType
#define VDAC_USE_CVBS_TYPE      CVBS_1
#define VDAC_USE_RGB_TYPE       RGB_1
#define VDAC_USE_YUV_TYPE       YUV_1

#define CVBS_DAC                DAC3

//#define SVIDEO_DAC_Y            DAC1
//#define SVIDEO_DAC_C            DAC0

#define RGB_DAC_R               DAC2
#define RGB_DAC_G               DAC1
#define RGB_DAC_B               DAC0

#define YUV_DAC_Y               DAC2
#define YUV_DAC_U               DAC1
#define YUV_DAC_V               DAC0


#ifdef _BUILD_OTA_E_
    #undef CI_SLOT_DYNAMIC_DETECT
    #define DMX_XFER_V_ES_BY_DMA     //added for s3601. transfer video ES by DMA, others by CPU copy
    #undef CI_SUPPORT
    #undef CC_USE_TSG_PLAYER
    #undef MULTI_VOLUME_SUPPORT
    #undef DYNAMIC_PID_SUPPORT
    #undef NETWORK_SUPPORT
    #undef SUPPORT_DEO_HINT
    #undef AUTOMATIC_STANDBY
    #undef MP_SUBTITLE_SUPPORT
    #undef SUPPORT_MPEG4_TEST
    #undef SHOW_ALI_DEMO_ON_SCREEN
    #undef AUDIO_DESCRIPTION_SUPPORT
    #undef RAM_TMS_TEST
    #undef MULTI_CAS
    #undef CAS_TYPE
    #undef SUPPORT_HW_CONAX
    #undef SUPPORT_CAS9
    #undef SUPPORT_CAS7
    #undef CAS9_V6
    #undef CAS9_PVR_SUPPORT
    #undef C0200A_PVR_SUPPORT
    #undef CAS7_PVR_SUPPORT
    #undef AV_DELAY_SUPPORT
    #define DSC_SUPPORT
    #undef GB2312_SUPPORT //reduce the space for ota
    #undef PVR_DYNAMIC_PID_CHANGE_TEST
    #undef WIFI_SUPPORT
    #undef TEMP_INFO_HEALTH
    #undef SCPI_SUPPORT
    #undef AUTO_UPDATE_TPINFO_SUPPORT
    #undef MULTIVIEW_SUPPORT
    #undef DLNA_SUPPORT
    #undef DLNA_DMP_SUPPORT
    #undef DLNA_DMR_SUPPORT
    #undef DLNA_DMS_SUPPORT
    #undef CC_ON
    #undef CC_BY_OSD
    #undef CC_BY_VBI
    #undef CC_MONITOR_CS
    #undef CC_MONITOR_CC
#endif


#ifdef DVBS_SUPPORT
#define SYS_PROJECT_FE                PROJECT_FE_DVBS
#elif ( defined(DVBT_SUPPORT) || defined(DVBT2_SUPPORT) )
#define SYS_PROJECT_FE                PROJECT_FE_DVBT
#elif defined  ISDBT_SUPPORT
#define SYS_PROJECT_FE                PROJECT_FE_ISDBT
#elif defined  DVBC_SUPPORT
#define SYS_PROJECT_FE                PROJECT_FE_DVBC
#else
#ifdef AUI
#else
#error "not define SYS_PROJECT_FE"
#endif
#endif

//below need clear
#ifdef DVBC_SUPPORT
    #define DVBC_COUNTRY_BAND_SUPPORT
   // #define SHOW_WELCOME_SCREEN  //Don't need the maro any more for we show welcome page in another way 20120211//need  define DVBC_COUNTRY_BAND_SUPPORT
    #define QAM_ONLY_USAGE       SYS_FUNC_OFF
    #define SYS_DEM_BASE_ADDR      0x42    //0x40
    //#define TUNER_I2C_BYPASS
#endif

#ifdef DVBC_SUPPORT
  #define FE_DVBC_SUPPORT
#endif
#ifdef DVBS_SUPPORT
  #define FE_DVBS_SUPPORT
#if defined(DVBT2_SUPPORT)
    #define SYS_DVBT_DEMO_MODULE    MN88472 //SHARP6158
    #define SYS_TUN_MODULE          MXL301  //MXL603
#elif defined(DVBT_SUPPORT)
    #define SYS_DVBT_DEMO_MODULE    MXL101//COFDM_M3101
#endif

#if ! defined(SYS_TUN_MODULE)
    #define SYS_TUN_MODULE              ANY_TUNER //IX2410
#endif
  #define DISEQC_SUPPORT
#endif

#define SYS_DEM_MODULE          ALI_S3501
#define SYS_TUN_MODULE          ANY_TUNER //MXL136 MXL5007 IX2410 NM120 RT820T

#define PERSIAN_SUPPORT//modify for adding welcome page when only open dvbt 2011 10 17
// I2C config same for all M3602 board now
#define I2C_FOR_TUNER           I2C_TYPE_SCB0
#define I2C_FOR_HZ6303          I2C_TYPE_SCB0
#define I2C_FOR_S3501           I2C_TYPE_SCB0

//#define DISABLE_USB
#ifdef MP_SUBTITLE_SUPPORT
#define MP_SUBTITLE_SETTING_SUPPORT //for mp ext subtitle setting support:font size/fg_color/bg_color/position
#endif

#ifdef  TEMP_INFO_HEALTH
//#define BACKUP_TEMP_INFO
#endif

#if (defined(_NESTOR_SUPPORT_))
	// nestor always need network and printf support
	#define NETWORK_SUPPORT
	#if (defined(DISABLE_PRINTF))
		#undef DISABLE_PRINTF
	#endif
#else
	#ifdef NETWORK_SUPPORT
    	#undef NETWORK_SUPPORT
	#endif
#endif
//#define USBUPG_MEMCFG_SUPPORT //for RD MEMCFG usb upgrade

#include "sys_memmap.h" //this line must be placed at the end.

#endif    // __SYS_CONFIG_H
