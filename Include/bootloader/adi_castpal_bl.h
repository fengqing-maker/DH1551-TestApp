
#ifndef _ADI_CASTPAL_BL_6345___
#define _ADI_CASTPAL_BL_6345___

#include "adi_bootloader_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//########################################################################################
//##########################################������Ϣ######################################
//########################################################################################
/* ���·���Ϊbooter core���� */
#define ADIBL_BOOTER_Partition (0)

/* ���·���Ϊloader core���� */
#define ADIBL_LOADER_Partition (1)

/* ���·���Ϊsystem info����
�˷����ǹ̶��Ĳ���������-�����̶� ����:
����ID Ӳ���汾�� ��ǩ flash��������Ϣ*/
#define ADIBL_SYS_INFO_Partition (2)

/* ���¿����õ���KEY�������� */
#define ADIBL_KEY_Partition (3)

/*����loaderpt��syssetting�����ױ������-��ͬ������ģ��eeprom�� */
#define ADIBL_VIR_EEPROM_Partition  (4)
#define ADIBL_VIR_EEPROM_LOADERPT_Partition (41)
#define ADIBL_VIR_EEPROM_SYS_SETTING_Partition (42)

/* ����MAC��ַ--SN--HDCPkey����������Ϣ���浽һ��������--�����ʽ�Լ����� */
#define ADIBL_MACADDR_SN_HDCPKey_Partition (5)

/* ����logo���� */
#define ADIBL_LOGO_Partition (6)

/* ����app���� */
#define ADIBL_APP_Partition (7)

/* ����app_RC���� */
#define ADIBL_APP_RC_Partition (8)

/* ��������*/
#define ADIBL_ALL_Partition (9)

/* ����RESERVED1���� ������Ŀ��չ*/
#define ADIBL_RESERVED1_Partition (10)

/* ����RESERVED2���� ������Ŀ��չ*/
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

	ADIBLFlashBlock_S booter; // booter(�������)!!!
	ADIBLFlashBlock_S loader; // loader(�������)!!!
	ADIBLFlashBlock_S system_info; //sysinfo---STB��Ϣ+flashmap(�������)!!!

	ADIBLFlashBlock_S key; // key---(���ܴ���)---

	unsigned int vireeprom_addr; // ģ��eeprom����(�������loaderpt+syssetting)!!!
	unsigned int vireeprom_total_size;
	unsigned int vireeprom_unit_size;
	ADIBLFlashBlock_S vireeprom_loaderpt;
	ADIBLFlashBlock_S vireeprom_system_setting;
	
	ADIBLFlashBlock_S macaddr_sn_hdcpkey; // mac sn hdcpkey(�������)!!!
	ADIBLFlashBlock_S logo; // logo(�������)!!!
	ADIBLFlashBlock_S app;  // logo(�������)!!!
	ADIBLFlashBlock_S app_rc; // logo(�������)!!!
	ADIBLFlashBlock_S all; // flash��������(�������)!!!
	ADIBLFlashBlock_S reserved1; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved2; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved3; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved4; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved5; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved6; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved7; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved8; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved9; // ����(���ܴ���)---
	ADIBLFlashBlock_S reserved10; // ����(���ܴ���)---

	unsigned int crc32;
}adi_bl_sys_Info_s;

#ifdef	__cplusplus
}
#endif


#endif


