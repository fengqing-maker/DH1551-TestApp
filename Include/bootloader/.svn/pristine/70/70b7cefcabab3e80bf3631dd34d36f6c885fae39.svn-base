
/*
 * adi_bootloader_common.h
 *
 * 此头文件提供给booterloader和app使用
 *
 */

#ifndef _ADI_BL_COMMON_H_2343545___
#define _ADI_BL_COMMON_H_2343545___

#include "adi_typedef.h"
#include "adi_ir.h"
#include "adi_tuner.h"
#include "adi_flash.h"
#include "adi_net.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
	E_BL_PANEL_KEY_OK,
	E_BL_PANEL_KEY_MENU,
	E_BL_PANEL_KEY_EXIT,
	E_BL_PANEL_KEY_STANDBY,
	E_BL_PANEL_KEY_UP,
	E_BL_PANEL_KEY_DOWN,
	E_BL_PANEL_KEY_LEFT,
	E_BL_PANEL_KEY_RIGHT,	
	E_BL_PANEL_KEY_MAX
}ADIBLPanelKey_E;

#define STB_LABEL_LEN (16)  // STB标签长度

typedef struct 
{
	/*操作这一块hSrcSurface, 标清机器直接再blit到hSDDiaplaySurface上,
	高清机器需要同时blit到hSDDiaplaySurface和hHDDiaplaySurface上使标高清输出都能显示*/
	ADI_HANDLE hSrcSurface; 

	/*标清DiaplaySurface(高清机器为了兼容标清输出, 也会创建这块内存)*/
	ADI_HANDLE hSDDiaplaySurface; 

	/*高清DiaplaySurface(只有高清机器才会有, 标清机器返回0)*/
	ADI_HANDLE hHDDiaplaySurface; 
}ADIBLOSGInfo_S;

typedef struct
{
	unsigned int m_unVer; /*版本号*/
	unsigned int m_unSDMode;/*标清PALN制式 ADISCREENResolution_E*/
	unsigned int m_unUartLevel; /*串口打印级别*/
	unsigned int m_unRFChannelNum;/*RF channel*/
	unsigned int m_unHDMode; /*HD分辨率 ADISCREENResolution_E */
	unsigned int m_unReserved[10]; /*未使用*/
	unsigned int m_unCrc32;/*以上数据的CRC32*/
}ADIBLSYSSetting_S;

typedef enum
{
	E_FM_FLASH = 0, /* flash类型 */
	E_FM_VIREEPROM = 1, /* 模拟eeprom类型 */
	E_FM_MAX
}ADIBLFlashMode_E;

/* flash分区设置 */
typedef struct
{
	unsigned int m_unStartAddress;
	unsigned int m_unTotalSize;
	unsigned int m_unType; /*ADIBLFlashMode_E*/
}ADIBLFlashBlock_S;

typedef struct
{
	unsigned char aucAddrss[4]; /*IP组播地址--或下发升级数据的ip地址*/
	unsigned short usPort; /*IP组播端口--或下发升级数据的端口*/
}ADIBLIPInfo_S;

/*应用设置到loader保存的静态IP地址等信息*/
typedef struct
{
	unsigned char aucIp[4]; /*应用通过DHCP动态或手动静态给STB配置的IP地址*/
	unsigned char aucSubNet[4]; /*应用通过DHCP动态或手动静态给STB配置的子网掩码*/
	unsigned char aucGateway[4]; /*应用通过DHCP动态或手动静态给STB配置的默认网关*/
	unsigned char aucDNS1[4]; /*应用通过DHCP动态或手动静态给STB配置的首选DNS*/
	unsigned char aucDNS2[4]; /*应用通过DHCP动态或手动静态给STB配置的备选选DNS*/
	unsigned char aucMACAddress[6]; /*机器MAC地址,由应用传给BL*/
}ADIBLLocalIPV4Info_S;

#define _BUFFERSIZE_256B_ (256)
#define _IPUPGRADE_MADIC_ (0x76983A8C)
typedef struct
{
	unsigned int unIPMagic; // must be _IPUPGRADE_MADIC_
	ADIEtherType_E eEtherType; // 有线或者无线网卡
	ADIBLLocalIPV4Info_S stLoaderIpInfo; // 配置STB的本地IP信息
	ADIWlanAPConnectInfo_S stAPInfo; // WIFI账号密码,当eEtherType==EM_ADIETHER_TYPE_WLAN时候有效	
	char acHttpURL[_BUFFERSIZE_256B_]; // http下载路径
	unsigned char reserved[_BUFFERSIZE_256B_]; // 保留未使用
}ADIBLIpDownloadInfoNew_S;// SIZE:624

typedef enum
{

	E_ADIBL_UART_DL= 0, /*串口升级, 只能由booter启动的升级*/
	E_ADIBL_USB_DL = 1, /*USB升级*/
	E_ADIBL_OTA_DL_DVB = 2,/*正常流程ts流的OTA升级*/
	E_ADIBL_OTA_DL_DVBOVERIP = 3, /*ts流通过网口的ip升级*/
	E_ADIBL_IP_DL = 4, // IP 升级
	E_ADIBL_DL_MAX = 5,  // default--保持默认缺省值,避免影响其他项目
}ADIBLDLType_E;

/*IP升级返回类型*/
#define IPDL_CHECK_OK (0)
#define IPDL_CHECK_CONNECT_ERROR (1)
#define IPDL_CHECK_DATA_EXCHANGE_ERROR (2)
#define IPDL_CHECK_MANUCODE_ERROR (3)
#define IPDL_CHECK_HWVER_ERROR (4)
#define IPDL_CHECK_DLH_INCORRECT_SW_VERSION (5)
#define IPDL_CHECK_INCORRECT_SW_VERSION (6)
#define IPDL_CHECK_SAME_SW_VERSION (7)
#define IPDL_CHECK_SW_VERSION_UNKNOW_ERROR (8)
#define IPDL_CHECK_VARIANT_ERROR (9)
#define IPDL_CHECK_FILEFORMAT_ERROR (10)
#define IPDL_CHECK_FILEVERSION_ERROR (10)
#define IPDL_CHECK_MODULECOUNT_ERROR (11)
#define IPDL_CHECK_MODULEID_ERROR (12)
#define IPDL_CHECK_MODULEVERSION_ERROR (13)

typedef struct 
{
	unsigned short usOTAPid;         
	unsigned char ucOTATableId;
	ADIBLDLType_E eDLType;
	
/*
	ADITunerSRCDeliver_U结构体
	----对于DVBS CA有效返回数据为
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency 
		m_sSourceSatelliteDeliver.m_sSatellitePar.m_dSatLongitude
		m_sSourceSatelliteDeliver.m_sSatellitePar.m_uWestEastFlag 
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uPolar_4 
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uModulations_2
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uSymbolRate_24
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFECInner_4
	----对于DVBC CA有效返回数据为
		m_sCableDeliver.m_uFrequency
		m_sCableDeliver.m_uModulation_8
		m_sCableDeliver.m_uSymbolRate_24
	----对于DVBT CA有效返回数据为
		m_sTerrestrialDeliver.m_uFrequency
		m_sTerrestrialDeliver.m_uBanuidth_3
 */
	ADITunerSRCDeliver_U unionDeliver; /* DVB S:0x43,  C:0x44,  T:0x5A,  T2:0x7F (eDLType=E_ADIBL_OTA_DL_DVB有效)*/
	ADIBLIPInfo_S stIPInfo; /*IP (eDLType=E_ADIBL_OTA_DL_DVBOVERIP, 或E_ADIBL_IP_DL有效, 表示前端的IP地址(组播地址)和端口)*/
}ADIBLOtaLoaderPt_S;

#define __LZMA_PROPS_SIZE__ (5)
#define __IMAGE_EXTEND__ (64)
#define __COMPRESS_TYPE_LZMA__ (0xA9B8C7D6)

typedef struct
{
	unsigned int unCompressType;/* 压缩类型 当前:__COMPRESS_TYPE_LZMA__*/
	unsigned int unOrgImgSize;/* 原始可执行bin文件大小*/
	unsigned int unOrgImgCRC32;/* 原始可执行bin文件crc32*/

	unsigned int unCompressImgSize;/* 原始可执行bin文件被压缩之后的大小*/
	unsigned int unCompressImgCRC32;/* 原始可执行bin文件被压缩之后的crc32*/
	
	unsigned char aucLzmaProperties[__LZMA_PROPS_SIZE__];/*压缩时候生成的5字节属性, 解压需要用到*/
	unsigned char aucReserved[3]; /* 与aucLzmaProperties对应--4字节对齐, 保留的没有使用 */

	/* 此是一个内存地址, 将解压后的原始可执行bin文件直接copy到这个地址, 最后还需要驱动接口跳转, 压缩工具中会配置这个地址*/
	unsigned int unExeMemAddr;
	
	unsigned char aucExtend[__IMAGE_EXTEND__];/* 预留,扩展没有使用 */
	
	unsigned int unHeadCRC32;/*以上所有数据的CRC32*/
	
}ADIBLImageHead_S; // ECOS Head

#define IMG_HEAD_SIZE (sizeof(ADIBLImageHead_S))

// Linux Kernel Head>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define __LINUX_KERNEL_MGIC__ (0xA3B4C5D6)
#define __LINUX_BOOTARGS_SIZE (2048)
typedef struct
{
	unsigned int unKLMagic; // __LINUX_KERNEL_MGIC__
	unsigned int unKLExeMemAddr; // 引导地址
	unsigned char ucKLBootargs[__LINUX_BOOTARGS_SIZE]; // bootargs字符串 
	unsigned char aucKLExtend[__IMAGE_EXTEND__];// 预留,扩展没有使用
	unsigned int unALLappSize; //整个app的大小(KL,RFS,CON,APP,MWLIB,LIB)
	unsigned int unKLSize; //Kernel的大小
	unsigned int unKLCRC32;//Kernel的CRC32
	unsigned int unKLHeadCRC32;//以上所有数据的CRC32
}ADIBLLinuxKernelHead_S;
#define LINUXKL_HEAD_SIZE (sizeof(ADIBLLinuxKernelHead_S))  // 0x858(2136)
// Linux Kernel Head<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define __MAX_SIGNATURE_LEN (1024)
#define __VFY_FLAG (0xA8A7A5A1)

typedef struct
{
	unsigned int unVerifyFlag;                      /*__VFY_FLAG*/
	unsigned int unSignatureOffset;                 /*Signature offset*/
	unsigned int unSignatureLen;                    /*Signature length*/
	unsigned int unVerifyOrgImageOffset;            /*org image offset*/
	unsigned int unVerifyOrgImageLen;               /*org image length*/
	unsigned int unCRC32;                           /*CRC32 of the head*/
}ADIBLImageSignatureHead_S;

#define IMG_SIGN_HEAD_SZIE (sizeof(ADIBLImageSignatureHead_S))

extern unsigned int ADISOCKInit(unsigned int nParam);

/*
 * Description: 模拟eeprom配置【配置bl的 模拟eeprom--loaderpt-syssetting等】
 *
 * Note: 此接口为booter/loader/app公共接口 都需要设置存储loaderpt-syssetting等常变化数据的模拟eeprom
 *
 * Parameters :   unVEEPROMAddr: loaderpt-syssetting模拟eeprom在flash中真正的起始地址
 *                unVEEPROMSize:
 *
 *
 * Returns	  : 0: 工程
 *             其他: 失败
 *			   
 */
int ADIBLInitVirEEPROM(unsigned int unVEEPROMAddr, unsigned int unVEEPROMSize,unsigned int unVEEPROMUserSize);

/*
 * Description: 注册模拟eeprom【预留App/自定义使用】
 *
 * Note: 与ADIBLInitVirEEPROM完全独立, 没有联系--为不同的模拟eeprom区域!!!
 *
 * Parameters : unFlashAddr 模拟eeprom使用的flash起始地址
 *				unFlashSize 模拟eeprom使用的flash总大小
 *				unEEPROMSize 模拟eeprom单元的总大小
 *				unMagicFlag 模拟eeprom的标识,一般情况赋值为0(模块会自己管理), 否则必须为一个特殊magic数据例如0xBCA1A5C7, 0xA7890976等数据
 *
 * note:	使用模拟eeprom必须先调用此注册接口, 否则读写模拟eeprom失败
 * Returns	  : 0--成功
 * 				其他--失败
 *			   
 */
int ADIBLVirEEPROMRegister(unsigned int  unFlashAddr,unsigned int  unFlashSize, unsigned int  unEEPROMSize, unsigned int unMagicFlag);

/*
 * Description: 取消注册模拟eeprom【预留App/自定义使用】
 *
 * Note: 与ADIBLInitVirEEPROM完全独立, 没有联系--为不同的模拟eeprom区域!!!
 *
 * Parameters : unFlashAddr 模拟eeprom使用的flash起始地址
 *
 * note:	反注册模拟eeprom后将不能再读写此flash起始地址的模拟eeprom数据
 *
 * Returns	  : 0--成功
 * 				其他--失败
 *			   
 */
int ADIBLVirEEPROMUnRegister(unsigned int  unFlashAddr);

/*
 * Description: 读取模拟eeprom数据【预留App/自定义使用】
 *
 * Note: 与ADIBLInitVirEEPROM完全独立, 没有联系--为不同的模拟eeprom区域!!!
 *
 * Parameters : unVirEEpromStartFlashAddr 模拟eeprom使用的flash起始地址
 *				unOffset---数据偏移
 *				pucData---读取数据的buffer
 *				unLength---读取数据的长度
 *
 * note:	必须先调用ADIBLVirEEPROMRegister再读取数据
 *
 * Returns	  : 0--成功
 * 				其他--失败
 *			   
 */
int  ADIBLVirEEPROMRead(unsigned int unVirEEpromStartFlashAddr, unsigned int unOffset, unsigned char * pucData,unsigned int unLength);

/*
 * Description: 读取模拟eeprom数据【预留App/自定义使用】
 *
 * Note: 与ADIBLInitVirEEPROM完全独立, 没有联系--为不同的模拟eeprom区域!!!
 *
 * Parameters : unVirEEpromStartFlashAddr 模拟eeprom使用的flash起始地址
 *				unOffset---数据偏移
 *				pucData---写入数据的buffer
 *				unLength----写入数据的长度
 *
 * note:	必须先调用ADIBLVirEEPROMRegister再读取数据
 *
 * Returns	  : 0--成功
 * 				其他--失败
 *			   
 */
int ADIBLVirEEPROMWrite(unsigned int unVirEEpromStartFlashAddr, unsigned int unOffset, unsigned char * pucData, unsigned int unLength);

/*
 * Description: 给app调用来检查网络上的升级数据是否可用
 *
 *
 * Parameters : pLocalIPV4Info 本地静态IP信息-用于联通网络
 *				pServerIPInfo 服务器的ip和端口
 *
 *
 * Returns	  : IPDL_CHECK_OK 有可用的ip升级数据
 * 				IPDL_CHECK_CONNECT_ERROR 网络连接出错
 * 				IPDL_CHECK_DATA_EXCHANGE_ERROR 网络数据通讯出错
 * 				IPDL_CHECK_MANUCODE_ERROR 升级数据中manucode与STB不一致
 * 				IPDL_CHECK_HWVER_ERROR 升级数据中hw ver与STB不一致
 * 				IPDL_CHECK_DLH_INCORRECT_SW_VERSION 升级数据下载头的软件版本号不对
 * 				IPDL_CHECK_INCORRECT_SW_VERSION 升级数据包含的软件版本不对
 * 				IPDL_CHECK_SAME_SW_VERSION 升级数据包含的软件版本与STB为同一个版本
 * 				IPDL_CHECK_SW_VERSION_UNKNOW_ERROR 升级数据包含的软件版本未知的异常
 *			   
 */
int ADIBLCheckIPDownload(ADIBLLocalIPV4Info_S *pLocalIPV4Info, ADIBLIPInfo_S *pServerIPInfo);
int ADIBLCheckIPDownloadURL(char acHttpURL[_BUFFERSIZE_256B_]);

/*
 * Description: 是否开启BL下的打印
 *
 *
 * Parameters : bEnable ADI_TRUE开启  ADI_FALSE关闭 
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetDebugSwitch(ADI_BOOL bEnable);

typedef int  (* AdapterCallback)(unsigned int unParam1, unsigned int unParam2, unsigned int unParam3, unsigned int unParam4);

/*
 * Description: RegisterExternLoaderCallBack
 *
 *
 * Parameters : AdapterCallback 
 *
 * Returns	  : 
 *			   
 */
void ADIBLRegisterExternLoaderCallBack(AdapterCallback fn);


/*
 * Description: nand flash flash protect enable
 *
 *
 * Parameters : mode :  set 1  enable it 
 *				blkSize :  block size (64k, 128k..)
 *				reserved1, reserved2: reserved
 *
 * Returns	  : 
 *			   
 */
void ADIBLFlashProtectConfigure(unsigned int mode, unsigned int blkSize, unsigned int reserved1, unsigned int reserved2);

#define UPGRADE_FILE_OK (0x00)// File can be upgraded
#define UPGRADE_FILE_ERR_Format (0x01) // "Format of this File is error"
#define UPGRADE_FILE_ERR_ManuID (0x02) // "ManuID of this File is error"
#define UPGRADE_FILE_ERR_HWVersion (0x03) // "HWVersion of this File is error"
#define UPGRADE_FILE_ERR_FILEVersion (0x04) // "FileVersion of this File is error"
#define UPGRADE_FILE_ERR_Variant (0x05) // "Variant of this File is error"
#define UPGRADE_FILE_ERR_DSN (0x06) // "DownloadSequenceNumber of this File is error"
#define UPGRADE_FILE_ERR_Module_Count (0x07) // "Module count of CD5 File is error"
#define UPGRADE_FILE_ERR_Module_ID (0x08) // "Module ID of CD5 File is error"
#define UPGRADE_FILE_ERR_Module_Version (0x09) // "Module Version of CD5 File is error"
#define UPGRADE_FILE_ERR_Open_USB_DEVICE (0x0A) // "Open USB Device failed"
#define UPGRADE_FILE_ERR_NO_IRDETOCD5 (0x0B) // "Can not find IRDETO.CD5"
#define UPGRADE_FILE_ERR_NO_IRDETOSDL (0x0C) // "Can not find irdeto.sdl"
#define UPGRADE_FILE_ERR_Default (0xFF) // "Unkonw error" 
/**
 * Check If a file can be upgraded by USB
 *
 * This function can be called by application to check if there is a file Available for upgrading. 
 *
 * @param[in] nDeviceId: USB device ID
 *            nIsUnicode : 0:not unicode,  1:unicode
 * 
 * @return
 *    :: UPGRADE_FILE_OK ~ UPGRADE_FILE_ERR_Default
 *
 */ 
int ADIBLIsUpgradeFileAvailable(int nDeviceId, int nIsUnicode);

/*
 * Description: 设置通用规范的bl的flashmap
 *
 * Note: 此接口必须调用否则无法找到分区信息, 需要在以下所有接口调用之前调用 必须调用的接口
 *
 * Parameters :  unAddress 根据flashmap存储位置确定 向bl开发人员确认
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLFlashInfoConfig(unsigned int unAddress);

/*
 * Description: 初始化应用需要获取信息, loaderpt等, 是应用中bl第二个被调用的接口
 *
 * Note:
 *
 * Parameters :  无
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLAppInit(void);

/*
 * Description: 从flash读取syssetting
 *
 * Note:
 *
 * Parameters :  pstSysSetting 读取的syssetting
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLGetSYSSetting(ADIBLSYSSetting_S * pstSysSetting);

/*
 * Description: 设置syssetting到flash
 *
 * Note:
 *
 * Parameters :  stSysSetting 设置到flash中的的syssetting
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLSetSYSSetting(ADIBLSYSSetting_S stSysSetting);

/*
 * Description: 设置当前的tuner info
 *
 * Note:
 *
 * Parameters :  unTunerId tunerid
 *               eTunerType Tuner类型
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLSaveOTATunerInfo(unsigned int unTunerId, ADITunerType_E eTunerType);

/*
 * Description: 当有OTA信息写ota loaderpt
 *
 * Note:
 *
 * Parameters :  pstOtaLoaderPt 写到flash的loaderpt结构体
 *				 bEnableOTAFlag 是不是重启后进入OTA  ADI_TRUE为重启后进入OTA   ADI_FALSE为重启后不进入OTA
 *				bNeedCheckSWVer 是否需要loader中比较软件版本
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLSaveOTALoaderPt(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt, ADI_BOOL bEnableOTAFlag, ADI_BOOL bNeedCheckSWVer);

/*
 * Description: 读当前的 loaderpt信息
 *
 * Note:
 *
 * Parameters :  pstOtaLoaderPt 写到flash的loaderpt结构体
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLReadOTALoaderPt(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt);

/*
 * Description: 保存WLan信息到BL控制的flash
 *
 * Note: IP升级使用
 *
 * Parameters : psWLanAPConf
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLSaveIpDownloadData(ADIBLIpDownloadInfoNew_S * psIpDownloadInfo);

/*
 * Description: 设置OTA升级时的AntennaPower开关
 *
 * Note:
 *
 * Parameters :  unTunerId 目前保留的
 *				 ucEnable :  1打开   0关闭
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLSaveOTAAntennaPowerEnableFlag(unsigned int unTunerId, unsigned char ucEnable);

/*
 * Description: 读取厂商OUI
 *
 * Note:
 *
 * Parameters :  厂商OUI
 *
 * Returns	  :  无
 *            
 *			   
 */
void ADIBLGetOUI(unsigned char oui[3]);

/*
 * Description: 读取厂商ID
 *
 * Note:
 *
 * Parameters :  无
 *
 * Returns	  :  厂商ID
 *            
 *			   
 */
unsigned short ADIBLGetMaunID(void);

/*
 * Description: 读取硬件版本号
 *
 * Note:
 *
 * Parameters :  无
 *
 * Returns	  :  硬件版本号
 *            
 *			   
 */
unsigned short ADIBLGetHWVersion(void);

/*
 * Description: 读取客户变量Variant
 *
 * Note:
 *
 * Parameters :  无
 *
 * Returns	  : 客户变量Variant
 *            
 *			   
 */
unsigned short ADIBLGetVariant(void);

/*
 * Description: 读取软件版本号/dsn
 *
 * Note:
 *
 * Parameters :  无
 *
 * Returns	  :  软件版本号/dsn
 *            
 *			   
 */
unsigned short ADIBLGetSWVersion(void);

/*
 * Description: 获取当前的需要配置有线还是无线
 *
 * Note:
 *
 * Parameters :  无
 *
 * Returns	  :  ADIEtherType_E
 *            
 *			   
 */
ADIEtherType_E ADIBLGetEtherTypeCfg(void);

/*
 * Description: 读取STB的型号
 *
 * Note: label的内存空间大小需要大于等于STB_LABEL_LEN
 *
 * Parameters :  label 存放STB型号内存空间
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLGetSTBLabel(char label[STB_LABEL_LEN]);

/*
 * Description: 获取当前Loader的版本号
 *
 * Note: 包含主版本和子版本,保留版本
 *
 * Parameters :  pnVer1 主版本
 *               pnVer2 子版本
 *               pnVer3 保留版本
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLGetLoaderVersion(int *pnVer1, int *pnVer2, int *pnVer3);

/*
 * Description: 获取当前Irdeto Key信息
 *
 *
 * Parameters :  pSystemId key_sys_id
 *               pKeyVersion key版本
 *				 pSignatureVersion key签字版本
 *
 * Returns	  :   0 success,  other failed
 *			   
 */
int ADIBLReadIrdetoStoreKey(unsigned short* pSystemId,  unsigned short* pKeyVersion, unsigned short* pSignatureVersion);

#define NAND_PARTITION_CNT (16)

typedef struct
{
	ADIFLASHPartition_S stNandFlashPartition[NAND_PARTITION_CNT];
	unsigned int unCount;
	unsigned int unCRC32;
}ADIBLNandFlashPartitionCfg_S;

/*
 * Description: 设置NandCfg
 *
 * Note 这是Nandflash配置, 必须首先调用 才能调用其他接口
 *
 * Parameters :  pstInitParam flash大小配置
 *               pstInitPartition 基础分区信息[boot loader sysdata 这些分区不可以再升级]
 *				 unFlashMapAddr Flashmap逻辑分区起始地址
 *
 * Returns	  :   0 success,  other failed

// 例子如下 boot  loader  sys_data 分区是固定的
#define FLASH_CFG_ADDR (0x005A0000)
 	 
int init_bl_nand_flash(void)
{
	int nRst = 0;

	ADIBLNandFlashPartitionCfg_S stCfg;
	ADIFLASHInitParams_S sInitParams;

	memset(&stCfg, 0, sizeof(stCfg));
	memset(&sInitParams, 0, sizeof(sInitParams));

	sInitParams.m_uBaseAddress  = 0x0;
	sInitParams.m_uChipSize = 0x8000000;
	sInitParams.m_uVPPGPIOIndex = 0x0;

	// 以下为基本NandFlash的分区配置,不可以再修改
	strcpy(stCfg.stNandFlashPartition[0].m_szPTName, "boot");
	stCfg.stNandFlashPartition[0].m_uOffset = 0x00000000;
	stCfg.stNandFlashPartition[0].m_uPTSize = 0x000C0000;
	stCfg.stNandFlashPartition[0].m_uSpareSize = 0x00020000;

	strcpy(stCfg.stNandFlashPartition[1].m_szPTName, "loader");
	stCfg.stNandFlashPartition[1].m_uOffset = 0x000C0000;
	stCfg.stNandFlashPartition[1].m_uPTSize = 0x00560000;
	stCfg.stNandFlashPartition[1].m_uSpareSize = 0x00060000;

	strcpy(stCfg.stNandFlashPartition[2].m_szPTName, "sys_data");
	stCfg.stNandFlashPartition[2].m_uOffset = 0x00620000;
	stCfg.stNandFlashPartition[2].m_uPTSize = 0x00220000;
	stCfg.stNandFlashPartition[2].m_uSpareSize = 0x00080000;
	stCfg.unCount = 3;

	nRst = ADLBLNandFlashCfg(0, &sInitParams, &stCfg, FLASH_CFG_ADDR);
	if(nRst != 0)
	{
		printf("[%s %d]ADLBLNandFlashCfg FLASH_CFG_ADDR(0x%x) :%d \n", __FUNCTION__, __LINE__, FLASH_CFG_ADDR, nRst);
		return -1;
	}

	ADIBLFlashProtectConfigure(1, 0x20000, 0, 0);

	nRst = ADIBLFlashInfoConfig(FLASH_CFG_ADDR);
	if(nRst != 0)
	{
		printf("[%s %d]ADIBLFlashInfoConfig FLASH_CFG_ADDR(0x%x) :%d \n", __FUNCTION__, __LINE__, FLASH_CFG_ADDR, nRst);
		return -2;
	}

	return 0;
}

 *			   
 */
int ADLBLNandFlashCfg(int nFlashIndex, ADIFLASHInitParams_S *pstInitParam, ADIBLNandFlashPartitionCfg_S *pstInitPartition, unsigned int unFlashMapAddr);

#ifdef	__cplusplus
}
#endif


#endif


