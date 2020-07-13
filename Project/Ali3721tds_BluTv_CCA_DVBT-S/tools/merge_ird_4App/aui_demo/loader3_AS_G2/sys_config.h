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
#include <sys_memmap.h>
//#define DUAL_CPU
#ifndef _BOARD_DB_M3822_01V01_
// M3821 can not support HDMI CEC standby at present
#define HDMI_CEC_ENABLE
#endif
#define PAN_INFO_ALIGN

#define SYS_PROJECT                SYS_DEFINE_NULL    /* Target project */

#define SYS_VERSION_BL            "01.000.00"        /* Boot loader: %02d.%03d.%02d */
#define SYS_VERSION_SW            "00.000.00"        /* Software:    %02d.%03d.%02d */
#define SYS_VERSION_PL            "00.000.00"        /* Program list:%02d.%03d.%02d */

#ifdef _BOOT_OS_E_
#define SYS_OS_MODULE            ALI_TDS2        /* OS configuration */
#define SYS_IRP_MOUDLE            ALI_00            /* IR Pad configuration */
#else
#define SYS_OS_MODULE            NO_OS        /* OS configuration */
#endif

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

//#define SUPPORT_EJTAG_VERIFY
//#define USE_SMC1

/* makefile.cmd for LLD_PAN_XXX */
#define SYS_CHIP_MODULE            ALI_S3602        /* Chip configuration */

//#define SYS_CPU_MODULE            CPU_ALI_V1  // CPU_MIPS24KE        /* CPU configuration */
#define SYS_CPU_MODULE            CPU_MIPS24KE        /* CPU configuration */
#define SYS_CPU_ENDIAN            ENDIAN_LITTLE    /* CPU endian */

#define SYS_CHIP_CLOCK            27000000        /* Extarnal clock */
#define SYS_CPU_CLOCK            594000000        /* CPU clock */

#define SYS_GPIO_MODULE            M3602F_GPIO        /* GPIO configuration */

#define SYS_I2C_MODULE            M6303I2C        /* I2C configuration */
#ifdef _BOARD_DB_M3822_01V01_
#define SYS_I2C_SDA                129             /* I2C SDA GPIO pin number */
#define SYS_I2C_SCL                128                /* I2C SDL GPIO pin number */
#else //M3503
#define SYS_I2C_SDA                134             /* I2C SDA GPIO pin number */
#define SYS_I2C_SCL                135                /* I2C SDL GPIO pin number */
#endif

#define SYS_PCI_MODULE            SYS_DEFINE_NULL    /* PCI configuration */

#define SYS_SCI_MODULE            UART16550        /* SCI configuration */


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

//#define SYS_IRP_MOUDLE            ROCK00 //GMI_00            /* IR Pad configuration */
#define SYS_PAN_MOUDLE            GMI_PAN_SL35

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
#define PAN_KEY_STANDBY            0xffff0001

#define PANEL_DISPLAY
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

#define HOOK_INT_HANDLER_BY_CP0

#define BL_ENABLE
#define BL_STANDBY_DEBUG            //open the macro to debug standby

/****************************************************************************
 * Section for SW configuration.
 ****************************************************************************/
#define HDCP_IN_FLASH
#define HDCPKEY_CHUNK_ID (HDCPKEY_CHUNID_TYPE |0x0100)

#ifdef _HW_SECURITY_ENABLE_
//#define CA_NO_CRC_ENABLE
#define HW_SECURITY_ENABLE
#endif

#ifdef _M3515_SECURE_BOOT_ENABLE_
#define M3515_SECURE_BOOT_ENABLE
#endif


#ifdef _ENABLE_BL_ENCRYPTED_
#define BL_ENCRYPTED_ENABLE     //bootloader encrypted
#endif

#ifdef _LINUX_BOOTLOADER_
#define LINUX_BOOTLOADER
#endif

#ifdef _C0300A_CA_ENABLE_
    #define C0300A_CA_ENABLE
    #define BL_DISABLE_SE
    #define ENABLE_UART_UPG
    #define BL_C0300A_AS
    #define CA_NO_CRC_ENABLE
#endif

#ifdef _C0300A_CA_STD_ENABLE_
    #define C0300A_CA_STD_ENABLE
    #define BL_DISABLE_SE
    #define ENABLE_UART_UPG
    #define BL_C0300A_STD
    #define CA_NO_CRC_ENABLE
#endif

#ifdef _CAS9_VSC_ENABLE_
	#define BL_VSC_ENABLE
	#define CHUNKID_VSC_CODE 0x0CF30101
    #define VSC_SIGNATURE_LEN	256
    #define VSC_VERSION_LEN	16
#endif

#endif    /* _SYS_CONFIG_H_ */
