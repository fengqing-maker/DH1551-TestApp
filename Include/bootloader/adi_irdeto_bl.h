
#ifndef _IRD_APP_F_H_847528345___
#define _IRD_APP_F_H_847528345___

#include "adi_tuner.h"
#include "adi_bootloader_common.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define RANDOM_NUMBER_LEN     	 (4)
#define SERIAL_NUMBER_SIZE    	 (4)
#define BBCB_MAX_SIZE (24)
#define MAC_LENGH (16)

/*Irdeto bbcb结构体*/
typedef struct
{
	unsigned short          ulCRC;
	unsigned char           bManufactureCode;
	unsigned char           bHW_Version;
	unsigned char           bLDR_Version_Major;
	unsigned char           bLDR_Version_Minor;
	unsigned char           abSerialNumber[SERIAL_NUMBER_SIZE];
	unsigned char           abRandomNumber[RANDOM_NUMBER_LEN];
	unsigned char           bLoaderType;
	unsigned char	        Reserved[9];
}BBCB_STRUCT;

typedef struct
{
	unsigned char   bNon_MAC_mask;
	unsigned char   MAC[MAC_LENGH];
}PT_LOG_STRUCT_MAC;

/*Irdeto spcb结构体*/
typedef struct
{
	unsigned char  bLoad_sequence_number;
	unsigned char  bPartition_count;
	unsigned int   uBin2ird_version;
	unsigned int   uBin2ird_serial_number;
	unsigned char  abSign_time_date[5];
	unsigned char  abDownload_time_date[5];
	unsigned short wDownload_duration;
	unsigned int   uImage_size;
	unsigned short wMACLength; 
	PT_LOG_STRUCT_MAC astPartition[256];
	unsigned char  bMAC_SPCB[MAC_LENGH];
}SPCB_STRUCT;

typedef struct
{
    unsigned char      ucKeyStatus;
    unsigned char      ucLastImage;
    unsigned short     usSysID;
    unsigned short     usKeyVer;
    unsigned short     usVariant;
    unsigned short     usSigVer;
    unsigned int       unRandomNum;
}IrdetoKeyStatus_S;

typedef enum
{
	E_FSH_BOOTER = 0,
	E_FSH_LOADER = 1,
	E_FSH_BBCB = 2,
	E_FSH_SPCB = 3,
	E_FSH_KEY = 4,
	E_FSH_LOADER_PT = 5,
	E_FSH_SYSSETTING = 6,
	E_FSH_LOGO = 7,
	E_FSH_APP = 8,
	E_FSH_IRDETO_CFG_APP = 9,
	E_FSH_MAX
}ADIIrdetoBLFlashType_E;

/*flash cfg==140bytes*/
typedef struct
{
	ADIBLFlashBlock_S m_stFshBooter;/*booter 12bytes*/
	ADIBLFlashBlock_S m_stFshLoader;/*loader 12bytes*/
	ADIBLFlashBlock_S m_stFshBBCB;/*bbcb 12bytes*/
	ADIBLFlashBlock_S m_stFshSPCB;/*spcb 12bytes*/
	ADIBLFlashBlock_S m_stFshKey;/*key 12bytes*/
	ADIBLFlashBlock_S m_stFshLoaderPT;/*loader pt 12bytes*/
	ADIBLFlashBlock_S m_stFshSYSSetting;/*sys set 12bytes*/
	ADIBLFlashBlock_S m_stFshLogo; /*logo 12bytes*/
	ADIBLFlashBlock_S m_stFshApp;/*app 12bytes*/
	ADIBLFlashBlock_S m_stFshIrdetoCfgApp;/*cfg app 12bytes*/
	unsigned int m_unIrdetoCfgOnePtSize;/*cfg app one pt size 4bytes*/
	unsigned int m_unVirEEpromAddr; /*vir eeprom起始地址 4bytes*/
	unsigned int m_unVirEEpromTotalSize; /*vir eeprom使用flash的总大小 4bytes*/
	unsigned int m_unVirEEpromUnitSize; /*vir eeprom一个最小单元的大小 4bytes*/
	unsigned int m_unCrc32;/*crc32 4bytes*/
}ADIIrdetoBLFlashCfgInfo_S;

/*
 * Description: 初始化irdeto项目flashmap, booter loader app工程都必须要调用此接口配置整个flash分区信息
 *
 * Parameters : unAddress-配置分区表在flash中的位置
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIIrdetoBLFlashInfoConfig(unsigned int unAddress);

/*
 * Description: 初始化irdeto laoder信息, 后面才可以读取spcb bbcb keystatus
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoAppInit(void);

/*
 * Description: 读取irdeto spcb的信息, 只有调用ADIBLIrdetoAppInit后才能获取到
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoGetSPCB(SPCB_STRUCT*  pstSPCB);

/*
 * Description: 读取irdeto bbcb的信息, 只有调用ADIBLIrdetoAppInit后才能获取到
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoGetBBCB(BBCB_STRUCT*  pstBBCB);

/*
 * Description: 读取irdeto key的信息, 只有调用ADIBLIrdetoAppInit后才能获取到
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoGetKeyStatus(IrdetoKeyStatus_S*  pstKeyStatus);

/*
 * Description: 保存STB本地静态ip参数用来连网 (ip升级使用)
 *
 * Note: IP升级必须调用 然后再调用 ADIBLIrdetoSaveOTALoaderPt保存服务器ip和端口
 *
 * Parameters : pstLocalIPV4Info
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoSaveLocalIpV4Info(const ADIBLLocalIPV4Info_S* pstLocalIPV4Info);

/*
 * Description:从loaderpt中读取保存的STB本地静态ip参数用来连网
 *
 * Note: 供应用ip设置界面读取当前IP信息
 *
 * Parameters : pstLocalIPV4Info
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoReadLocalIPV4Info(ADIBLLocalIPV4Info_S *pstLocalIPV4Info);

/*
 * Description: 
 *		case 1 : E_ADIBL_USB_DL为USB升级, 由于默认的usb升级文件是irdeto.sdl 调用这个函数之前请check是否有此文件否则无法升级
 *		case 2 : E_ADIBL_OTA_DL_DVB为正常码流的OTA升级, 需要设置升级频点参数和usOTAPid和ucOTATableId
 *		case 3 : E_ADIBL_OTA_DL_DVBOVERIP 实际为组播ts流的升级**目前支持不完整**
 *		case 4 : E_ADIBL_IP_DL TCPIP协议升级签字的sdl文件, 
 *							   app需要在stIPInfo中设置服务器ip和端口, 
 *							   app需要调用ADIBLIrdetoSaveLocalIpV4Info设置本地IP(app可以由用户设置或者DHCP获取)
 *
 * Parameters : bEnableOTAFlag当为true时下次开机才会进loader升级
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoSaveOTALoaderPt(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt, ADI_BOOL bEnableOTAFlag);

/*
 * Description: 从flash中读取SYSSetting
 *
 * Parameters : 
 *
 * Returns	  : 
 *			   
 */
int ADIBLIrdetoGetSYSSetting(ADIBLSYSSetting_S * pstSysSetting);

/*
 * Description: 设置SYSSetting到flash
 *
 * Parameters : 
 *
 * Returns	  : 
 *			   
 */
int ADIBLIrdetoSetSYSSetting(ADIBLSYSSetting_S stSysSetting);

/*
 * Description: 获取APP结束的flash地址
 *
 * Parameters : 
 *
 * Returns	  : 
 *			   
 */
int ADIBLIrdetoGetAppEndFlashAddress(unsigned int *punAddress);

#ifdef	__cplusplus
}
#endif


#endif


