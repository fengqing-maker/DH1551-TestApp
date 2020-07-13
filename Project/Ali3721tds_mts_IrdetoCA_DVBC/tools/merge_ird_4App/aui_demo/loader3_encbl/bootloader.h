/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: bootloader.h
*
*    Description:
*
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
     KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
     IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
     PARTICULAR PURPOSE.
*****************************************************************************/

#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys_config.h>
#include <sys_parameters.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <api/libc/fast_crc.h>
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
#include <api/librsa/flash_cipher.h>
#include <api/librsa/rsa_verify.h>
#include <api/libzip/gnuzip.h>
#include <asm/chip.h>
#include <hld/dsc/dsc.h>
#include <hld/crypto/crypto.h>


#ifdef FIXED_PRINTF
#undef FIXED_PRINTF
#endif

#ifdef BL_DISABLE_PRINTF
#define FIXED_PRINTF(...)     do{}while(0)
#else
#define FIXED_PRINTF     libc_printf
#endif

#define SYS_SW_FAIL     0x1
#define SYS_SW_PASS     0x0

#define BITMAP_LIST             NULL
#define BITMAP_LIST_NUM         0

#ifdef ENABLE_UART_UPG
#ifdef US_TICKS
#undef US_TICKS
#endif
#ifdef WAIT_300MS
#undef WAIT_300MS
#endif
#define US_TICKS       (sys_ic_get_cpu_clock()*1000000 / 2000000)
#define WAIT_100MS          (100000 * US_TICKS)
#define WAIT_300MS          (300000 * US_TICKS)
#define WAIT_500MS            (500000 * US_TICKS)
#define WAIT_5MS            (5000 * US_TICKS)
#define MS_TICKS        (1000*US_TICKS)
#endif

#define SECTOR_OFFSET_BIT 16
#define FLASH_SECTOR_SIZE (64*1024)
#define HW_SET_GPIO 0x104

/* Calcuate InternalBufferSize for 7-zip */
#define LZMA_BASE_SIZE  1846
#define LZMA_LIT_SIZE   768
#define BUFFER_SIZE     ((LZMA_BASE_SIZE + (LZMA_LIT_SIZE << (0 + 2))) \
             * sizeof(UINT16))

#define OTA_SEE_CODE  3
#define OTA_CPU_CODE  2
#define SEE_CODE  1
#define MAIN_CODE 0
#define MAIN_ENTRY 0x80000200
#define C_SECTOR_SIZE 0x10000

#define MAX_CODE_LEN  (0x400000)

#ifdef BL_VSC_ENABLE
#define VSC_SIGNATURE_LEN   256
#define VSC_VERSION_LEN        16
#endif


typedef struct pan_gpio_info gpio_info_t;

#if((SYS_MAIN_BOARD == BOARD_DEMO_M3281_01V01)|| \
      (SYS_MAIN_BOARD == BOARD_DB_M3281_01V01))
#define GPIO_REG                    0xb8000040//0xb8000430  //gpio0 ~ gpio31
#define GPIOA_REG                   0xb80000a0//0xb8000434  //gpio32 ~ gpio63
#define GPIOB_REG                   0xb80000D0//0xb8000438  //gpio64 ~ gpio95
#define GPIOC_REG                   0xb8000150//0xb800043c  //gpio96 ~ gpio127
#endif

typedef struct
{
        UINT32 i2c_id;
        UINT32 bps;
        UINT32 en;
        gpio_info_t *sda;
        gpio_info_t *scl;
} i2c_cfg;

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_array)      (sizeof(_array)/sizeof(_array[0]))
#endif


extern UINT8 *g_see_unziped;// see unziped target address
extern UINT32 g_ota_offset; // ota buffer

extern void __SEE_ROM_START(); // BL_SEE virtual start address
extern void __SEE_ROM_END(); // BL_SEE virtual end address

extern struct pan_device *panel_dev; // BL pan device pointer
extern struct sto_device *flash_dev;// BL nor flash device pointer

#ifdef LZO_COMPRESS_ENABLE
extern int unlzo ( unsigned char *in, unsigned char *out, unsigned char *buf );
#endif

RET_CODE bl_enter_ota_loader(UINT8 *ota_decrypted, UINT32 ota_len);

RET_CODE bl_enter_sys_sw(UINT8 *see_decrypted, UINT32 see_mc_len, \
                    UINT8 *main_decrypted, UINT32 cpu_mc_len);

RET_CODE bl_prepare_key(UINT8 *pos);

#ifdef BL_VSC_ENABLE
RET_CODE bl_prepare_key_see(UINT8 *pos);
#endif

RET_CODE bl_prepare_key_ext(UINT8* plain_uk);

RET_CODE bl_init_dev(void);


#if(defined(ENABLE_4M_FLASH))
UINT8 find_second_loader ( void );
#endif
RET_CODE bl_prepare_otaloader(UINT8 *ota_decrypted,UINT8 key_pos,
                    UINT32 block_addr, UINT32 block_len, UINT8 *len);

/*show logo APIs*/
RET_CODE bl_show_logo_init();
void bl_show_logo_close();

/*helper APIs*/
RET_CODE bl_len_check(UINT32 len);

#ifdef __cplusplus
 }
#endif

#endif
