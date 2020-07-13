/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2011 Copyright (C)
*
*    File:    sys_config.h
*
*    Description:    This file contains all system configuration switches and
*                        parameter definations.

*****************************************************************************/

#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_
#include <sys_define.h>
#define HW_SECURE_ENABLE    //security enable
#define DUAL_CPU
#define HDMI_CEC_ENABLE
#define PAN_INFO_ALIGN

#ifdef _ENABLE_BL_ENCRYPTED_
#define BL_ENCRYPTED_ENABLE
#endif

#define SYS_PROJECT                SYS_DEFINE_NULL    /* Target project */
#define SYS_VERSION_BL            "01.000.00"        /* Boot loader: %02d.%03d.%02d */
#define SYS_VERSION_SW            "00.000.00"        /* Software:    %02d.%03d.%02d */
#define SYS_VERSION_PL            "00.000.00"        /* Program list:%02d.%03d.%02d */

#define SYS_OS_MODULE            ALI_TDS2            /* OS configuration */

#define SYS_MW_MODULE            SYS_DEFINE_NULL    /* MW configuration */

#define SYS_CA_MODULE            SYS_DEFINE_NULL    /* CA configuration */

#define SYS_EPG_MODULE            SYS_DEFINE_NULL    /* EPG configuration */

#define SYS_PROJECT_FE    PROJECT_FE_DVBT
/****************************************************************************
 * Section for HW configuration, include bus configuration.
 ****************************************************************************/
/* customer loader build related */
#define ENABLE_4M_FLASH
//#define LZO_COMPRESS_ENABLE

#define BL_DISABLE_PRINTF

#ifdef _BC_CA_ENABLE_
#define BL_DISABLE_SE
#define ENABLE_UART_UPG
#define BL_BC_AS
#define BC_CA_ENABLE
#endif

#ifdef _BC_CA_STD_ENABLE_
#define BL_DISABLE_SE
#define ENABLE_UART_UPG
#define BL_BC_STD
#define BC_CA_STD_ENABLE
#endif

#ifdef _BOARD_DEMO_M3281_01V01_
    #define SYS_MAIN_BOARD BOARD_DEMO_M3281_01V01
#else
    #ifdef _BOARD_DB_M3281_01V01_
        #define SYS_MAIN_BOARD BOARD_DB_M3281_01V01
    #endif
#endif

#define CA_NO_CRC_ENABLE

#ifdef _HW_SECURITY_ENABLE_
#define HW_SECURITY_ENABLE
#endif
//#define SUPPORT_EJTAG_VERIFY
//#define USE_SMC1

#ifdef _CAS9_VSC_ENABLE_
#define BL_VSC_ENABLE
#define CHUNKID_VSC_CODE 0x0CF30101

#define __MM_VSC_CODE_LEN    0x20000
#define __MM_VSC_DATA_LEN 0x10000
#define __MM_VSC_TOTAL_LEN (__MM_VSC_CODE_LEN+__MM_VSC_DATA_LEN)
#endif


/* makefile.cmd for LLD_PAN_XXX */
#define SYS_CHIP_MODULE            ALI_S3602        /* Chip configuration */

#define SYS_CPU_MODULE            CPU_ALI_V1  // CPU_MIPS24KE        /* CPU configuration */
#define SYS_CPU_ENDIAN            ENDIAN_LITTLE    /* CPU endian */

#define SYS_CHIP_CLOCK            27000000        /* Extarnal clock */
#define SYS_CPU_CLOCK            298000000        /* CPU clock */

#ifdef _USE_32M_MEM_
#define SYS_SDRAM_SIZE 32
#define DISABLE_USB
#else
#define SYS_SDRAM_SIZE 64
#endif

/* solution3
support: TTX, subtitle, H.264
not support: PVR, Timeshift */
#ifdef _M3281_SOLUTION3_SUPPORT_
#define M3281_SOLUTION3_SUPPORT
#endif


#define SYS_GPIO_MODULE            M3602F_GPIO        /* GPIO configuration */

#define SYS_I2C_MODULE            M6303I2C        /* I2C configuration */
#define SYS_I2C_SDA                SYS_DEFINE_NULL    /* I2C SDA GPIO pin number */
#define SYS_I2C_SCL                SYS_DEFINE_NULL    /* I2C SDL GPIO pin number */

#define SYS_PCI_MODULE            SYS_DEFINE_NULL    /* PCI configuration */

#define SYS_SCI_MODULE            UART16550        /* SCI configuration */

//#define DDR_POWER_CONTROL_ENABLE // use a GPIO to control the DDR power on/off
#ifdef DDR_POWER_CONTROL_ENABLE
    #define DDR_POWER_CTL_GPIO_POS        37        /* depends on board design */
    #define DDR_POWER_CTL_GPIO_POLAR    1        /* depends on board design */
#else
    #define DDR_POWER_CTL_GPIO_POS        0xffff    /* invalid GPIO */
    #define DDR_POWER_CTL_GPIO_POLAR    0
#endif


/****************************************************************************
 * Section for LLD configuration.
 ****************************************************************************/
#define SYS_FLASH_MODULE        AM29800B        /* Flash configuration */
#define SYS_FLASH_BASE_ADDR        0xafc00000        /* Flash base address */
#define SYS_FLASH_SIZE            0x200000        /* Flash size, in byte */

#define SYS_EEPROM_MODULE        SYS_DEFINE_NULL    /* EEPROM configuration */
#define SYS_EEPROM_BASE_ADDR    0xA0            /* EEPROM base address */
#define SYS_EEPROM_SIZE            1024            /* EEPROM size, in byte */

#define SYS_NET_MOUDLE            SYS_DEFINE_NULL    /* Net configuration */

#define SYS_DMX_MODULE            SYS_DEFINE_NULL    /* Demux configuration */

#define SYS_TUN_MODULE            SYS_DEFINE_NULL    /* Tuner configuration */
#define SYS_TUN_BASE_ADDR        SYS_DEFINE_NULL    /* Tuner device address */

#define SYS_DEM_MODULE            SYS_DEFINE_NULL    /* Demodulator configuration */
#define SYS_DEM_BASE_ADDR        SYS_DEFINE_NULL    /* Demodulator device address */

#define SYS_RFM_MODULE            SYS_DEFINE_NULL    /* RF modulator configuration */
#define SYS_RFM_BASE_ADDR        SYS_DEFINE_NULL    /* RF modulator device address */

#define SYS_IRP_MOUDLE            ROCK00 //GMI_00            /* IR Pad configuration */
#define SYS_PAN_MOUDLE            GMI_PAN_SL35

#define PANEL_DISPLAY

#define LOGO_ID                    0x02FD0100

#define STANDBY_SUSPEND                0
#define STANDBY_SHOW_PANEL            1
#define STANDBY_PANEL_SHOW_TIMER    2
#define STANDBY_PANEL_SHOW_OFF        3
#define STANDBY_PANEL_SHOW_BLANK    4
#define STANDBY_ACTION                STANDBY_SHOW_PANEL

#define    STANDBY_PANEL_SHOW_WAHT    STANDBY_PANEL_SHOW_TIMER//STANDBY_PANEL_SHOW_TIMER
#define IRP_KEY_STANDBY            0x807fc03f
#define IRP_KEY_STANDBY2        0x60df708f

#if (SYS_MAIN_BOARD == BOARD_DB_M3281_01V01)
#ifdef PANEL_16515_VFD
#define PAN_KEY_STANDBY            0xFFFF0004
#else
#define PAN_KEY_STANDBY            0xFFFF0008
#endif
#else
#define PAN_KEY_STANDBY            0xffff0001
#endif

#ifdef PANEL_DISPLAY
#define MAX_GPIO_NUM                   127
#define FP_LOCK_GPIO_NUM            127
#define FP_STANDBY_GPIO_NUM         127
#define FP_CLOCK_GPIO_NUM           127
#define FP_DATA_GPIO_NUM            127
#define FP_KEY1_GPIO_NUM            127
#define FP_COM1_GPIO_NUM            127
#define FP_COM2_GPIO_NUM            127
#define FP_COM3_GPIO_NUM            127
#define FP_COM4_GPIO_NUM            127
#endif
//#define GUNZIP_SUPPORT
//#define TRANSFER_FORMAT2_SUPPORT

#ifdef _EROM_E_
#define ENABLE_EROM
#endif
#ifdef _MULTI_SECTION_E
#define SUPPORT_MULTI_SECTION
#endif

#define ENABLE_SERIAL_FLASH


#define GPIO_MUTE    0
#define SCART_MUTE    1


#if (SYS_MAIN_BOARD == BOARD_DB_M3281_01V01)
#define SYS_MUTE_MODE                GPIO_MUTE
#if(SYS_MUTE_MODE == GPIO_MUTE)
  #define MUTE_CIRCUIT_GPIO_NUM        76
#else
  #define SCART_POWER_DOWN_GPIO_NUM    70
#endif
#endif


#if(SYS_SDRAM_SIZE == 64)
/*#define __MM_VOID_BUFFER_LEN        0x00100000    //2M
#define __MM_SHARED_MEM_LEN          256
#define __MM_PRIVATE_SHARE_LEN    0x01900000    //26M
#define __MM_HIGHEST_ADDR          0xa4000000        //64M*/
/*---------------------selwyn add ---------*/
#ifndef M3281_BOOT_WITH_LOGO
#define __MM_VOID_BUFFER_LEN        0x00100000    //2M
#define __MM_SHARED_MEM_LEN          256
#define __MM_PRIVATE_SHARE_LEN    0x01900000    //26M
#define __MM_HIGHEST_ADDR          0xa4000000        //64M
#else
#define VDAC_USE_CVBS_TYPE              CVBS_1
#define VDAC_USE_RGB_TYPE                   RGB_1
#define VDAC_USE_YUV_TYPE                   YUV_1
#define CVBS_DAC                                    DAC3

#define YUV_DAC_Y                                   DAC1
#define YUV_DAC_U                                   DAC0
#define YUV_DAC_V                               DAC2

#define RGB_DAC_R                                   DAC2
#define RGB_DAC_G                                   DAC1
#define RGB_DAC_B                                   DAC0

#define __MM_SHARED_MEM_LEN          256

#define __MM_SEE_MP_BUF_LEN          0x00900000
#define __MM_PRIVATE_SHARE_LEN    0x01900000//0x01e00000    //26M
#define __MM_VOID_BUFFER_LEN        0x00100000
#define __MM_PRIVATE_LEN            (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

#define __MM_HIGHEST_ADDR           0xa4000000        //64M

#define __MM_VOID_BUFFER_ADDR    (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)
#define __MM_SHARE_BASE_ADDR         (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR            (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //20M

#define __MM_MAIN_TOP_ADDR        0xa2600000//0xa2000000        //36MB

#define OSD_VSRC_MEM_MAX_SIZE     0x400000    //for coship osd booter dont need osd buffer.
#define __MM_OSD_VSRC_MEM_ADDR    (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE)
#define __MM_FB_TOP_ADDR            __MM_OSD_VSRC_MEM_ADDR

#if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
#error "__MM_PRIVATE_ADDR address error"
#endif


#define __MM_PVR_VOB_BUFFER_LEN     0


#define __MM_MP_BUFFER_ADDR        0
#define __MM_MP_BUFFER_LEN        0

#define __MM_SEE_MP_BUF_ADDR        0
#define __MM_SEE_MP_BUF_LEN        0

#define __MM_FB0_Y_LEN                0
#define __MM_FB1_Y_LEN                0
#define __MM_FB2_Y_LEN                0

#define __MM_FB0_C_LEN                0
#define __MM_FB1_C_LEN                0
#define __MM_FB2_C_LEN                0

#define __MM_FB3_Y_LEN                0
#define __MM_FB3_C_LEN                0
#define __MM_FB4_Y_LEN                0
#define __MM_FB4_C_LEN                0
#define __MM_FB5_Y_LEN                  0
#define __MM_FB5_C_LEN                  0
#define __MM_FB6_Y_LEN                  0
#define __MM_FB6_C_LEN                  0

#define __MM_FB0_Y_START_ADDR    0
#define __MM_FB0_C_START_ADDR    0
#define __MM_FB1_Y_START_ADDR    0
#define __MM_FB1_C_START_ADDR    0
#define __MM_FB2_Y_START_ADDR    0
#define __MM_FB2_C_START_ADDR    0
#define __MM_FB3_Y_START_ADDR    0
#define __MM_FB3_C_START_ADDR    0
#define __MM_FB4_Y_START_ADDR    0
#define __MM_FB4_C_START_ADDR    0
#define __MM_FB5_Y_START_ADDR    0
#define __MM_FB5_C_START_ADDR    0
#define __MM_FB6_Y_START_ADDR    0
#define __MM_FB6_C_START_ADDR    0

//end**************************************************

#define __MM_FB_LEN                    0x308400//0x26D000//0x308400//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
#define __MM_MAF_LEN                0X8C000//0x29C00//0x8000//0X8C000//0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#define __MM_VBV_LEN                0x200000//0x46800//0x12C000//(HD = 8*SD > 4*SD)
#define __MM_DBG_MEM_LEN           0x4000
#define __MM_DVW_LEN                0//0X25FA0
#define __MM_DMX_SI_LEN            (32*188)//(16*188)
#define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*44)
#define __MM_SI_VBV_OFFSET        __MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN        (30*188)
#define __MM_DMX_PCR_LEN        (10*188)
#define __MM_DMX_AUDIO_LEN        (256*188)//(32*188)
#define __MM_DMX_VIDEO_LEN        (12*512*188)//(8*512*188)
#define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#define __MM_DMX_VIDEO_LEN        (12*512*188)//(8*512*188)
#define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)
#define __MM_DMX_BLK_BUF_LEN    0xbc000
#define __MM_EPG_BUFFER_LEN             0x100000
#define __MM_OSD1_LEN           (1280*720*4)
#define __MM_OSD2_LEN            (1920*1080)
#define __MM_NIM_BUFFER_LEN            0x00200000
#define __MM_GE_LEN                   0
#define __MM_OSD_LEN            (720*576*2)
#define __MM_VCAP_FB_SIZE               0
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN                 0
#define __MM_USB_DMA_LEN                0
#define __MM_DCII_SUB_BS_LEN       0

#define __MM_FB_START_ADDR        ((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFF00)

#define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR
#define __MM_BUF_PVR_TOP_ADDR       __MM_FB_BOTTOM_ADDR
#define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
#define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#define __MM_DMX_REC_START_ADDR        (__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)
#define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)
#define __MM_OSD_BK_ADDR3            ((__MM_EPG_BUFFER_START - __MM_OSD2_LEN)&0XFFFFFFE0)//for ca fingerprint

#define __MM_NIM_BUFFER_ADDR        ((__MM_OSD_BK_ADDR3 - __MM_NIM_BUFFER_LEN)&0XFFFFFFE0)
#define __MM_GE_START_ADDR            ((__MM_NIM_BUFFER_ADDR - __MM_GE_LEN)&0XFFFFFFE0)
#define __MM_OSD_BK_ADDR1              ((__MM_GE_START_ADDR - __MM_OSD_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#define __MM_LWIP_MEM_ADDR          (__MM_VCAP_FB_ADDR - __MM_LWIP_MEM_LEN)
#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)
#define __MM_DCII_SUB_BS_START_ADDR (__MM_USB_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_CPU_DBG_MEM_ADDR          (__MM_DCII_SUB_BS_START_ADDR - __MM_DBG_MEM_LEN)
//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/
#define __MM_VBV_START_ADDR            ((__MM_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_DEVOUR_START_ADDR          ((__MM_MAF_START_ADDR - (0xd00 * 2) )&0XFFFFFC00)
#define __MM_DMX_SEE_BLK_ADDR            ((__MM_DEVOUR_START_ADDR - 0x00)&0XFFFFFFE0)

#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - 0x00)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - 0x00)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  0x00)
#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - 0x00)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - 0x00)&0XFFFFFFFC)

#define __MM_OSD_BK_ADDR2       ((__MM_TTX_PB_START_ADDR - 0x00)&0XFFFFFFF0)

#define __MM_SUB_BS_START_ADDR    ((__MM_OSD_BK_ADDR2  - 0x00)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - 0x00)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    ((__MM_SUB_HW_DATA_ADDR - 0x00)&0XFFFFFFFC)
#define __MM_SUBT_ATSC_SEC_ADDR (__MM_SUB_PB_START_ADDR - 0x00)

#define __MM_SEE_DBG_MEM_ADDR      (__MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)


//end of Private mem map

#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR
#endif
/*---------------------selwyn add end---------*/
#elif(SYS_SDRAM_SIZE == 32)

#ifndef M3281_BOOT_WITH_LOGO
#define __MM_VOID_BUFFER_LEN        0//0x00100000    //2M
#define __MM_SHARED_MEM_LEN          256

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_PRIVATE_SHARE_LEN    0x830000//0x8C0000//0x00a00000//10M
#else
/* solution 3 */
#define __MM_PRIVATE_SHARE_LEN    (0x830000+0x198000)
#endif
#define __MM_HIGHEST_ADDR          0xa2000000        //32M

#else

#define VDAC_USE_CVBS_TYPE              CVBS_1
#define VDAC_USE_RGB_TYPE                   RGB_1
#define VDAC_USE_YUV_TYPE                   YUV_1
#define CVBS_DAC                                    DAC3

#define YUV_DAC_Y                                   DAC1
#define YUV_DAC_U                                   DAC0
#define YUV_DAC_V                               DAC2

#define RGB_DAC_R                                   DAC2
#define RGB_DAC_G                                   DAC1
#define RGB_DAC_B                                   DAC0

#define __MM_SHARED_MEM_LEN          256

#define __MM_SEE_MP_BUF_LEN          0

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_PRIVATE_SHARE_LEN    0x830000//0x8C0000//0x00a00000//10M
#else
/* solution 3 */
#define __MM_PRIVATE_SHARE_LEN    (0x830000+0x198000)
#endif

#define __MM_VOID_BUFFER_LEN        0//0x100000//0//0x00200000    //2M
#define __MM_PRIVATE_LEN            (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

#define __MM_HIGHEST_ADDR           0xa2000000//32M

#define __MM_VOID_BUFFER_ADDR    (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)
#define __MM_SHARE_BASE_ADDR         (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR            (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //20M

#ifndef M3281_SOLUTION3_SUPPORT
#define __MM_MAIN_TOP_ADDR        0xa17D0000//0xa1600000//22MB
#else
/* solution 3 */
#define __MM_MAIN_TOP_ADDR        0xa17D0000 - 0x198000
#endif

#define OSD_VSRC_MEM_MAX_SIZE     0    //for coship osd booter dont need osd buffer.
#define __MM_OSD_VSRC_MEM_ADDR    (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE)
#define __MM_FB_TOP_ADDR            __MM_OSD_VSRC_MEM_ADDR

#if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
#error "__MM_PRIVATE_ADDR address error"
#endif


#define __MM_PVR_VOB_BUFFER_LEN     0


#define __MM_MP_BUFFER_ADDR        0
#define __MM_MP_BUFFER_LEN        0

#define __MM_SEE_MP_BUF_ADDR        0
#define __MM_SEE_MP_BUF_LEN        0

#define __MM_FB0_Y_LEN                0
#define __MM_FB1_Y_LEN                0
#define __MM_FB2_Y_LEN                0

#define __MM_FB0_C_LEN                0
#define __MM_FB1_C_LEN                0
#define __MM_FB2_C_LEN                0

#define __MM_FB3_Y_LEN                0
#define __MM_FB3_C_LEN                0
#define __MM_FB4_Y_LEN                0
#define __MM_FB4_C_LEN                0
#define __MM_FB5_Y_LEN                  0
#define __MM_FB5_C_LEN                  0
#define __MM_FB6_Y_LEN                  0
#define __MM_FB6_C_LEN                  0

#define __MM_FB0_Y_START_ADDR    0
#define __MM_FB0_C_START_ADDR    0
#define __MM_FB1_Y_START_ADDR    0
#define __MM_FB1_C_START_ADDR    0
#define __MM_FB2_Y_START_ADDR    0
#define __MM_FB2_C_START_ADDR    0
#define __MM_FB3_Y_START_ADDR    0
#define __MM_FB3_C_START_ADDR    0
#define __MM_FB4_Y_START_ADDR    0
#define __MM_FB4_C_START_ADDR    0
#define __MM_FB5_Y_START_ADDR    0
#define __MM_FB5_C_START_ADDR    0
#define __MM_FB6_Y_START_ADDR    0
#define __MM_FB6_C_START_ADDR    0

//end**************************************************

#define __MM_FB_LEN                    0x308400//0x26D000//0x308400//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
#define __MM_MAF_LEN                0x51C00//0x29C00//0x8000//0X8C000//0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#define __MM_VBV_LEN                0x14d000//0x46800//0x12C000//(HD = 8*SD > 4*SD)
#define __MM_DBG_MEM_LEN           0x4000
#define __MM_DVW_LEN                0//0X25FA0

#define __MM_FB_START_ADDR        ((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFF00)


#define __MM_CPU_DBG_MEM_ADDR          (__MM_FB_START_ADDR - __MM_DBG_MEM_LEN)

//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/
#define __MM_VBV_START_ADDR            ((__MM_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_DEVOUR_START_ADDR          ((__MM_MAF_START_ADDR - (0xd00 * 2) )&0XFFFFFC00)
#define __MM_DMX_SEE_BLK_ADDR            ((__MM_DEVOUR_START_ADDR - 0x00)&0XFFFFFFE0)

#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - 0x00)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - 0x00)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  0x00)
#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - 0x00)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - 0x00)&0XFFFFFFFC)

#define __MM_OSD_BK_ADDR2       ((__MM_TTX_PB_START_ADDR - 0x00)&0XFFFFFFF0)

#define __MM_SUB_BS_START_ADDR    ((__MM_OSD_BK_ADDR2  - 0x00)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - 0x00)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    ((__MM_SUB_HW_DATA_ADDR - 0x00)&0XFFFFFFFC)
#define __MM_SUBT_ATSC_SEC_ADDR (__MM_SUB_PB_START_ADDR - 0x00)

#define __MM_SEE_DBG_MEM_ADDR      (__MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)


//end of Private mem map

#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR
#endif
#endif

#ifndef M3281_BOOT_WITH_LOGO
#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)
#define __MM_VOID_BUFFER_ADDR    (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)//
#define __MM_SHARE_BASE_ADDR     (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)//
#define __MM_HEAP_TOP_ADDR        __MM_PRIVATE_ADDR    //
#endif

#define __MM_SEE_FW_BOOT_ADDR      (__MM_PRIVATE_ADDR|0x200)
#ifdef _CAS9_VSC_ENABLE_
#define SEE_ENTRY (__MM_PRIVATE_ADDR + __MM_VSC_TOTAL_LEN + 0x200)
#else
#define SEE_ENTRY (__MM_PRIVATE_ADDR + 0x200)
#endif
#define HOOK_INT_HANDLER_BY_CP0

#define BOOTLOADER_TEMP_ADDR    0xA0500000
#define BL_ENABLE
#endif    /* _SYS_CONFIG_H_ */
