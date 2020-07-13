#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys_config.h>
#include <sys_parameters.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <api/libchunk/chunk.h>
#include <bus/flash/flash.h>
#include <bus/sci/sci.h>
#include <hal/hal_mem.h>
#include <hld/smc/smc.h>
#include <api/libloader/ld_boot_info.h>

#include <hld/dsc/dsc.h>
#include <bus/nand/ali_nand.h>
#include <hld/pan/pan.h>
#include <hld/pan/pan_dev.h>
#include <boot/boot_common.h>

#ifdef _HW_SECURITY_ENABLE_
#include <api/librsa/flash_cipher.h>
#include <api/librsa/rsa_verify.h>
#include <hld/sec_boot/sec_boot.h>
#endif

#ifdef BL_C0300A_AS //aaron
#include <api/libcas/c0300a/bc_types.h>
#endif

#ifdef FIXED_PRINTF
#undef FIXED_PRINTF
#endif

#ifdef BL_DISABLE_PRINTF
#define FIXED_PRINTF(...)           do{}while(0)
#else
#define FIXED_PRINTF                libc_printf
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_array)      (sizeof(_array)/sizeof(_array[0]))
#endif

#define US_TICKS                    (sys_ic_get_cpu_clock()*1000000 / 2000000)
#define MS_TICKS                    (1000 * US_TICKS)
#define WAIT_5MS                    (5000 * US_TICKS)
#define WAIT_100MS                  (100000 * US_TICKS)
#define WAIT_300MS                  (300000 * US_TICKS)
#define WAIT_500MS                    (500000 * US_TICKS)

#define SECTOR_OFFSET_BIT           16
#define FLASH_SECTOR_SIZE           (64*1024)
#define HW_SET_GPIO                 0x104

/* Calcuate InternalBufferSize for 7-zip */
#define LZMA_BASE_SIZE              1846
#define LZMA_LIT_SIZE               768
#define BUFFER_SIZE                 ((LZMA_BASE_SIZE + \
                                     (LZMA_LIT_SIZE << (0 + 2))) * \
                                        sizeof(UINT16))

#define OTA_SEE_CODE                3
#define OTA_CPU_CODE                2
#define SEE_CODE                    1
#define MAIN_CODE                   0
#ifndef LINUX_BOOTLOADER
    #define MAIN_ENTRY              0x80000200
#else
    #define MAIN_ENTRY              0x85000000
#endif
#define C_SECTOR_SIZE               0x10000

/* State Machine Parameters */
#define UPG_DESC_BOOT_RUN_NONE        0x03
#define UPG_DESC_BOOT_RUN_ENTER        0x00
#define UPG_DESC_BOOT_RUN_START        0x01
#define UPG_DESC_BOOT_RUN_OVER        0x02

#define UPG_DESC_BOOT_UPG_NONE        0x07
#define UPG_DESC_BOOT_UPG_NO        0x00
#define UPG_DESC_BOOT_UPG_START        0x01
#define UPG_DESC_BOOT_UPG_OVER        0x02
#define UPG_DESC_BOOT_UPG_RUN        0x03

#define UPG_DESC_UBOOT1             0x00
#define UPG_DESC_UBOOT2             0x01

//#define USE_SMC1
#define JTAG_KEY_SIZE               256
#define CFG_KEY_LEN                 (0x2000)  // reversed for sig key
#define DEAD2BEE                    0xdead2bee
#define DEAD3BEE                    0xdead3bee //??

#define SIGNATURE_SIZE              256

#define NO_ERR                      0
#define ERR_1                       1
#define ERR_2                       2
#define ERR_3                       3
#define ERR_4                       4
#define ERR_5                       5

#define MODE_0                      0
#define MODE_1                      1

#define MAIN_OK                     0x1
#define SEE_OK                      0x2
#define OTA_LOADER_OK               0x4

struct state_machine_t
{
    unsigned int b_boot_status;
    unsigned int b_lowlevel_status;
    unsigned int b_application_status;
    unsigned int b_bootloader_upgrade;
    unsigned int b_lowlevel_upgrade;
    unsigned int b_application_upgrade;
    unsigned int b_bootloader_run_cnt;
    unsigned int b_lowlevel_run_cnt;
    unsigned int b_application_run_cnt;
    unsigned int b_reserved1;
    unsigned int b_reserved2;

    //for expand
    unsigned int b_need_upgrade;
    unsigned int b_backup_exist;
    unsigned int b_lowlevel_backup_exist;
    unsigned int b_boot_backup_exist;
    unsigned int b_nor_upgrade;
    unsigned int b_nor_reserved;
    unsigned int b_nor_reserved_upgrade;
    unsigned int b_nand_reserved;
    unsigned int b_nand_reserved_upgrade;
    unsigned int b_nand_whole_upgrade;
    unsigned int b_cur_uboot;
    unsigned int b_reserved[4];
};

extern UINT32 unzip_length;
extern UINT32 g_boot_type;

#if(defined(ENABLE_4M_FLASH))
extern UINT32 g_ota_offset;
#endif

extern struct pan_device *panel_dev;
extern struct sto_device *flash_dev;

void app_init(void);
void bl_init_flash(void);
void boot_enter_standby(void);
void set_os_config(UINT16 task_num, UINT16 sema_num, UINT16 flg_num, UINT16 mbf_num, UINT16 mutex_num);
void bl_load_and_launch_ota(void);
void bl_load_and_launch_sw(void);
RET_CODE bl_init_logo(void);
RET_CODE bl_get_chunk_len(UINT32 id, UINT32 *addr, UINT32 *len);
RET_CODE bl_get_uboot_addr(UINT32 boot_type, UINT32 *uboot_addr);
RET_CODE api_load_data_from_nandflash(unsigned long addr, unsigned long len, UINT8 *buf);

UINT8 find_second_loader(void);
UINT8 *bl_unzip_sw(UINT8 *decrypted, UINT32 mc_len,UINT32 type);
UINT8 *expand_ram(UINT32 addr, UINT32 len, int unzip(UINT8 *, UINT8 *, UINT8 *), UINT32 type);
INT32 check_program(void);
RET_CODE bl_enter_sys_sw(UINT8 *main_entry, UINT32 cpu_mc_len);
RET_CODE bl_enter_sys_zip_sw(UINT8 *zip_see, UINT32 see_mc_len,UINT8 *zip_main, UINT32 cpu_mc_len);
extern int un7zip(UINT8 *, UINT8 *, UINT8 *);

#ifdef _HW_SECURITY_ENABLE_
void set_uboot_config(UINT32 uboot_entry);
RET_CODE bl_prepare_key(struct UKEY_INFO *ukey);
#ifdef BL_VSC_ENABLE
RET_CODE bl_prepare_key_see(struct UKEY_INFO *ukey);
#endif
#endif

#ifdef DUAL_ENABLE
RET_CODE bl_init_see(UINT32 see_entry);
extern void __SEE_ROM_START();
extern void __SEE_ROM_END();
#endif

#ifdef ENABLE_UART_UPG
RET_CODE check_sw_upgrade(void);
void serial_upgrade(void);
#endif

#ifdef __cplusplus
 }
#endif

#endif

