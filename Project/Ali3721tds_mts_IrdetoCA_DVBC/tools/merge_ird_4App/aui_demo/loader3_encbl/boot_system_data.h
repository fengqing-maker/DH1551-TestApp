#ifndef _SYSTEM_DATA_COM_H_
#define _SYSTEM_DATA_COM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys_config.h>

#define OTA_FREQUENCY            586
#define OTA_BANDWIDTH            8
#define OTA_PID                    0x1ca0

#define TRANS_COLOR        0xFF
#define BLACK_COLOR        0xF4
#define WHITE_COLOR    0xFC
#define GRAY_COLOR        0xF8


void boot_sys_data_init(void);
INT32 boot_sys_data_load(union BOOT_INFO *boot_info);
INT32 boot_sys_data_save(union BOOT_INFO *boot_info);
union BOOT_INFO* get_boot_info(void);

#define BL_PRINTF(...) do{}while(0)

#ifdef __cplusplus
 }
#endif

#endif//_SYSTEM_DATA_COM_H_

