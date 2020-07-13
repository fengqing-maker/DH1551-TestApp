
#ifndef _ADI_CASTPAL_BL_6345___
#define _ADI_CASTPAL_BL_6345___

#include "adi_bootloader_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//########################################################################################
//##########################################分区信息######################################
//########################################################################################
/* 以下分区为booter core分区 */
#define ADIBL_BOOTER_Partition (0)

/* 以下分区为loader core分区 */
#define ADIBL_LOADER_Partition (1)

/* 以下分区为system info分区
此分区是固定的不允许升级-出厂固定 包括:
厂商ID 硬件版本号 标签 flash分区表信息*/
#define ADIBL_SYS_INFO_Partition (2)

/* 以下可能用到的KEY数据区域 */
#define ADIBL_KEY_Partition (3)

/*以下loaderpt和syssetting是容易变更区域-共同保存在模拟eeprom中 */
#define ADIBL_VIR_EEPROM_Partition  (4)
#define ADIBL_VIR_EEPROM_LOADERPT_Partition (41)
#define ADIBL_VIR_EEPROM_SYS_SETTING_Partition (42)

/* 以下MAC地址--SN--HDCPkey三个出厂信息保存到一个分区中--具体格式自己定义 */
#define ADIBL_MACADDR_SN_HDCPKey_Partition (5)

/* 以下logo区域 */
#define ADIBL_LOGO_Partition (6)

/* 以下app区域 */
#define ADIBL_APP_Partition (7)

/* 以下app_RC区域 */
#define ADIBL_APP_RC_Partition (8)

/* 完整区域*/
#define ADIBL_ALL_Partition (9)

/* 以下RESERVED1区域 用于项目扩展*/
#define ADIBL_RESERVED1_Partition (10)

/* 以下RESERVED2区域 用于项目扩展*/
#define ADIBL_RESERVED2_Partition (11)
#define ADIBL_RESERVED3_Partition (12)
#define ADIBL_RESERVED4_Partition (13)
#define ADIBL_RESERVED5_Partition (14)
#define ADIBL_RESERVED6_Partition (15)
#define ADIBL_RESERVED7_Partition (16)
#define ADIBL_RESERVED8_Partition (17)
#define ADIBL_RESERVED9_Partition (18)
#define ADIBL_RESERVED10_Partition (19)

//########################################################################################

#define STB_INVALID_FLASH_START_ADDR (0xFFFFFFFF) 
#define STB_INVALID_FLASH_SIZE (0) 

typedef struct
{
	unsigned int  manufacturer_id; 
	unsigned short  hardware_id;
	unsigned short  variant;
	char stb_label[STB_LABEL_LEN];
	unsigned char oui[3];
	unsigned char reserved[13]; /*not used!!*/

	ADIBLFlashBlock_S booter; // booter(必须存在)!!!
	ADIBLFlashBlock_S loader; // loader(必须存在)!!!
	ADIBLFlashBlock_S system_info; //sysinfo---STB信息+flashmap(必须存在)!!!

	ADIBLFlashBlock_S key; // key---(可能存在)---

	unsigned int vireeprom_addr; // 模拟eeprom区域(必须存在loaderpt+syssetting)!!!
	unsigned int vireeprom_total_size;
	unsigned int vireeprom_unit_size;
	ADIBLFlashBlock_S vireeprom_loaderpt;
	ADIBLFlashBlock_S vireeprom_system_setting;
	
	ADIBLFlashBlock_S macaddr_sn_hdcpkey; // mac sn hdcpkey(必须存在)!!!
	ADIBLFlashBlock_S logo; // logo(必须存在)!!!
	ADIBLFlashBlock_S app;  // logo(必须存在)!!!
	ADIBLFlashBlock_S app_rc; // logo(必须存在)!!!
	ADIBLFlashBlock_S all; // flash所有区域(必须存在)!!!
	ADIBLFlashBlock_S reserved1; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved2; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved3; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved4; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved5; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved6; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved7; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved8; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved9; // 保留(可能存在)---
	ADIBLFlashBlock_S reserved10; // 保留(可能存在)---

	unsigned int crc32;
}adi_bl_sys_Info_s;

#ifdef	__cplusplus
}
#endif


#endif


