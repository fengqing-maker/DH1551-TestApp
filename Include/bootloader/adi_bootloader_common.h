
/*
 * adi_bootloader_common.h
 *
 * ��ͷ�ļ��ṩ��booterloader��appʹ��
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

#define STB_LABEL_LEN (16)  // STB��ǩ����

typedef struct 
{
	/*������һ��hSrcSurface, �������ֱ����blit��hSDDiaplaySurface��,
	���������Ҫͬʱblit��hSDDiaplaySurface��hHDDiaplaySurface��ʹ��������������ʾ*/
	ADI_HANDLE hSrcSurface; 

	/*����DiaplaySurface(�������Ϊ�˼��ݱ������, Ҳ�ᴴ������ڴ�)*/
	ADI_HANDLE hSDDiaplaySurface; 

	/*����DiaplaySurface(ֻ�и�������Ż���, �����������0)*/
	ADI_HANDLE hHDDiaplaySurface; 
}ADIBLOSGInfo_S;

typedef struct
{
	unsigned int m_unVer; /*�汾��*/
	unsigned int m_unSDMode;/*����PALN��ʽ ADISCREENResolution_E*/
	unsigned int m_unUartLevel; /*���ڴ�ӡ����*/
	unsigned int m_unRFChannelNum;/*RF channel*/
	unsigned int m_unHDMode; /*HD�ֱ��� ADISCREENResolution_E */
	unsigned int m_unReserved[10]; /*δʹ��*/
	unsigned int m_unCrc32;/*�������ݵ�CRC32*/
}ADIBLSYSSetting_S;

typedef enum
{
	E_FM_FLASH = 0, /* flash���� */
	E_FM_VIREEPROM = 1, /* ģ��eeprom���� */
	E_FM_MAX
}ADIBLFlashMode_E;

/* flash�������� */
typedef struct
{
	unsigned int m_unStartAddress;
	unsigned int m_unTotalSize;
	unsigned int m_unType; /*ADIBLFlashMode_E*/
}ADIBLFlashBlock_S;

typedef struct
{
	unsigned char aucAddrss[4]; /*IP�鲥��ַ--���·��������ݵ�ip��ַ*/
	unsigned short usPort; /*IP�鲥�˿�--���·��������ݵĶ˿�*/
}ADIBLIPInfo_S;

/*Ӧ�����õ�loader����ľ�̬IP��ַ����Ϣ*/
typedef struct
{
	unsigned char aucIp[4]; /*Ӧ��ͨ��DHCP��̬���ֶ���̬��STB���õ�IP��ַ*/
	unsigned char aucSubNet[4]; /*Ӧ��ͨ��DHCP��̬���ֶ���̬��STB���õ���������*/
	unsigned char aucGateway[4]; /*Ӧ��ͨ��DHCP��̬���ֶ���̬��STB���õ�Ĭ������*/
	unsigned char aucDNS1[4]; /*Ӧ��ͨ��DHCP��̬���ֶ���̬��STB���õ���ѡDNS*/
	unsigned char aucDNS2[4]; /*Ӧ��ͨ��DHCP��̬���ֶ���̬��STB���õı�ѡѡDNS*/
	unsigned char aucMACAddress[6]; /*����MAC��ַ,��Ӧ�ô���BL*/
}ADIBLLocalIPV4Info_S;

#define _BUFFERSIZE_256B_ (256)
#define _IPUPGRADE_MADIC_ (0x76983A8C)
typedef struct
{
	unsigned int unIPMagic; // must be _IPUPGRADE_MADIC_
	ADIEtherType_E eEtherType; // ���߻�����������
	ADIBLLocalIPV4Info_S stLoaderIpInfo; // ����STB�ı���IP��Ϣ
	ADIWlanAPConnectInfo_S stAPInfo; // WIFI�˺�����,��eEtherType==EM_ADIETHER_TYPE_WLANʱ����Ч	
	char acHttpURL[_BUFFERSIZE_256B_]; // http����·��
	unsigned char reserved[_BUFFERSIZE_256B_]; // ����δʹ��
}ADIBLIpDownloadInfoNew_S;// SIZE:624

typedef enum
{

	E_ADIBL_UART_DL= 0, /*��������, ֻ����booter����������*/
	E_ADIBL_USB_DL = 1, /*USB����*/
	E_ADIBL_OTA_DL_DVB = 2,/*��������ts����OTA����*/
	E_ADIBL_OTA_DL_DVBOVERIP = 3, /*ts��ͨ�����ڵ�ip����*/
	E_ADIBL_IP_DL = 4, // IP ����
	E_ADIBL_DL_MAX = 5,  // default--����Ĭ��ȱʡֵ,����Ӱ��������Ŀ
}ADIBLDLType_E;

/*IP������������*/
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
	ADITunerSRCDeliver_U�ṹ��
	----����DVBS CA��Ч��������Ϊ
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency 
		m_sSourceSatelliteDeliver.m_sSatellitePar.m_dSatLongitude
		m_sSourceSatelliteDeliver.m_sSatellitePar.m_uWestEastFlag 
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uPolar_4 
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uModulations_2
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uSymbolRate_24
		m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFECInner_4
	----����DVBC CA��Ч��������Ϊ
		m_sCableDeliver.m_uFrequency
		m_sCableDeliver.m_uModulation_8
		m_sCableDeliver.m_uSymbolRate_24
	----����DVBT CA��Ч��������Ϊ
		m_sTerrestrialDeliver.m_uFrequency
		m_sTerrestrialDeliver.m_uBanuidth_3
 */
	ADITunerSRCDeliver_U unionDeliver; /* DVB S:0x43,  C:0x44,  T:0x5A,  T2:0x7F (eDLType=E_ADIBL_OTA_DL_DVB��Ч)*/
	ADIBLIPInfo_S stIPInfo; /*IP (eDLType=E_ADIBL_OTA_DL_DVBOVERIP, ��E_ADIBL_IP_DL��Ч, ��ʾǰ�˵�IP��ַ(�鲥��ַ)�Ͷ˿�)*/
}ADIBLOtaLoaderPt_S;

#define __LZMA_PROPS_SIZE__ (5)
#define __IMAGE_EXTEND__ (64)
#define __COMPRESS_TYPE_LZMA__ (0xA9B8C7D6)

typedef struct
{
	unsigned int unCompressType;/* ѹ������ ��ǰ:__COMPRESS_TYPE_LZMA__*/
	unsigned int unOrgImgSize;/* ԭʼ��ִ��bin�ļ���С*/
	unsigned int unOrgImgCRC32;/* ԭʼ��ִ��bin�ļ�crc32*/

	unsigned int unCompressImgSize;/* ԭʼ��ִ��bin�ļ���ѹ��֮��Ĵ�С*/
	unsigned int unCompressImgCRC32;/* ԭʼ��ִ��bin�ļ���ѹ��֮���crc32*/
	
	unsigned char aucLzmaProperties[__LZMA_PROPS_SIZE__];/*ѹ��ʱ�����ɵ�5�ֽ�����, ��ѹ��Ҫ�õ�*/
	unsigned char aucReserved[3]; /* ��aucLzmaProperties��Ӧ--4�ֽڶ���, ������û��ʹ�� */

	/* ����һ���ڴ��ַ, ����ѹ���ԭʼ��ִ��bin�ļ�ֱ��copy�������ַ, �����Ҫ�����ӿ���ת, ѹ�������л����������ַ*/
	unsigned int unExeMemAddr;
	
	unsigned char aucExtend[__IMAGE_EXTEND__];/* Ԥ��,��չû��ʹ�� */
	
	unsigned int unHeadCRC32;/*�����������ݵ�CRC32*/
	
}ADIBLImageHead_S; // ECOS Head

#define IMG_HEAD_SIZE (sizeof(ADIBLImageHead_S))

// Linux Kernel Head>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define __LINUX_KERNEL_MGIC__ (0xA3B4C5D6)
#define __LINUX_BOOTARGS_SIZE (2048)
typedef struct
{
	unsigned int unKLMagic; // __LINUX_KERNEL_MGIC__
	unsigned int unKLExeMemAddr; // ������ַ
	unsigned char ucKLBootargs[__LINUX_BOOTARGS_SIZE]; // bootargs�ַ��� 
	unsigned char aucKLExtend[__IMAGE_EXTEND__];// Ԥ��,��չû��ʹ��
	unsigned int unALLappSize; //����app�Ĵ�С(KL,RFS,CON,APP,MWLIB,LIB)
	unsigned int unKLSize; //Kernel�Ĵ�С
	unsigned int unKLCRC32;//Kernel��CRC32
	unsigned int unKLHeadCRC32;//�����������ݵ�CRC32
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
 * Description: ģ��eeprom���á�����bl�� ģ��eeprom--loaderpt-syssetting�ȡ�
 *
 * Note: �˽ӿ�Ϊbooter/loader/app�����ӿ� ����Ҫ���ô洢loaderpt-syssetting�ȳ��仯���ݵ�ģ��eeprom
 *
 * Parameters :   unVEEPROMAddr: loaderpt-syssettingģ��eeprom��flash����������ʼ��ַ
 *                unVEEPROMSize:
 *
 *
 * Returns	  : 0: ����
 *             ����: ʧ��
 *			   
 */
int ADIBLInitVirEEPROM(unsigned int unVEEPROMAddr, unsigned int unVEEPROMSize,unsigned int unVEEPROMUserSize);

/*
 * Description: ע��ģ��eeprom��Ԥ��App/�Զ���ʹ�á�
 *
 * Note: ��ADIBLInitVirEEPROM��ȫ����, û����ϵ--Ϊ��ͬ��ģ��eeprom����!!!
 *
 * Parameters : unFlashAddr ģ��eepromʹ�õ�flash��ʼ��ַ
 *				unFlashSize ģ��eepromʹ�õ�flash�ܴ�С
 *				unEEPROMSize ģ��eeprom��Ԫ���ܴ�С
 *				unMagicFlag ģ��eeprom�ı�ʶ,һ�������ֵΪ0(ģ����Լ�����), �������Ϊһ������magic��������0xBCA1A5C7, 0xA7890976������
 *
 * note:	ʹ��ģ��eeprom�����ȵ��ô�ע��ӿ�, �����дģ��eepromʧ��
 * Returns	  : 0--�ɹ�
 * 				����--ʧ��
 *			   
 */
int ADIBLVirEEPROMRegister(unsigned int  unFlashAddr,unsigned int  unFlashSize, unsigned int  unEEPROMSize, unsigned int unMagicFlag);

/*
 * Description: ȡ��ע��ģ��eeprom��Ԥ��App/�Զ���ʹ�á�
 *
 * Note: ��ADIBLInitVirEEPROM��ȫ����, û����ϵ--Ϊ��ͬ��ģ��eeprom����!!!
 *
 * Parameters : unFlashAddr ģ��eepromʹ�õ�flash��ʼ��ַ
 *
 * note:	��ע��ģ��eeprom�󽫲����ٶ�д��flash��ʼ��ַ��ģ��eeprom����
 *
 * Returns	  : 0--�ɹ�
 * 				����--ʧ��
 *			   
 */
int ADIBLVirEEPROMUnRegister(unsigned int  unFlashAddr);

/*
 * Description: ��ȡģ��eeprom���ݡ�Ԥ��App/�Զ���ʹ�á�
 *
 * Note: ��ADIBLInitVirEEPROM��ȫ����, û����ϵ--Ϊ��ͬ��ģ��eeprom����!!!
 *
 * Parameters : unVirEEpromStartFlashAddr ģ��eepromʹ�õ�flash��ʼ��ַ
 *				unOffset---����ƫ��
 *				pucData---��ȡ���ݵ�buffer
 *				unLength---��ȡ���ݵĳ���
 *
 * note:	�����ȵ���ADIBLVirEEPROMRegister�ٶ�ȡ����
 *
 * Returns	  : 0--�ɹ�
 * 				����--ʧ��
 *			   
 */
int  ADIBLVirEEPROMRead(unsigned int unVirEEpromStartFlashAddr, unsigned int unOffset, unsigned char * pucData,unsigned int unLength);

/*
 * Description: ��ȡģ��eeprom���ݡ�Ԥ��App/�Զ���ʹ�á�
 *
 * Note: ��ADIBLInitVirEEPROM��ȫ����, û����ϵ--Ϊ��ͬ��ģ��eeprom����!!!
 *
 * Parameters : unVirEEpromStartFlashAddr ģ��eepromʹ�õ�flash��ʼ��ַ
 *				unOffset---����ƫ��
 *				pucData---д�����ݵ�buffer
 *				unLength----д�����ݵĳ���
 *
 * note:	�����ȵ���ADIBLVirEEPROMRegister�ٶ�ȡ����
 *
 * Returns	  : 0--�ɹ�
 * 				����--ʧ��
 *			   
 */
int ADIBLVirEEPROMWrite(unsigned int unVirEEpromStartFlashAddr, unsigned int unOffset, unsigned char * pucData, unsigned int unLength);

/*
 * Description: ��app��������������ϵ����������Ƿ����
 *
 *
 * Parameters : pLocalIPV4Info ���ؾ�̬IP��Ϣ-������ͨ����
 *				pServerIPInfo ��������ip�Ͷ˿�
 *
 *
 * Returns	  : IPDL_CHECK_OK �п��õ�ip��������
 * 				IPDL_CHECK_CONNECT_ERROR �������ӳ���
 * 				IPDL_CHECK_DATA_EXCHANGE_ERROR ��������ͨѶ����
 * 				IPDL_CHECK_MANUCODE_ERROR ����������manucode��STB��һ��
 * 				IPDL_CHECK_HWVER_ERROR ����������hw ver��STB��һ��
 * 				IPDL_CHECK_DLH_INCORRECT_SW_VERSION ������������ͷ������汾�Ų���
 * 				IPDL_CHECK_INCORRECT_SW_VERSION �������ݰ���������汾����
 * 				IPDL_CHECK_SAME_SW_VERSION �������ݰ���������汾��STBΪͬһ���汾
 * 				IPDL_CHECK_SW_VERSION_UNKNOW_ERROR �������ݰ���������汾δ֪���쳣
 *			   
 */
int ADIBLCheckIPDownload(ADIBLLocalIPV4Info_S *pLocalIPV4Info, ADIBLIPInfo_S *pServerIPInfo);
int ADIBLCheckIPDownloadURL(char acHttpURL[_BUFFERSIZE_256B_]);

/*
 * Description: �Ƿ���BL�µĴ�ӡ
 *
 *
 * Parameters : bEnable ADI_TRUE����  ADI_FALSE�ر� 
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
 * Description: ����ͨ�ù淶��bl��flashmap
 *
 * Note: �˽ӿڱ�����÷����޷��ҵ�������Ϣ, ��Ҫ���������нӿڵ���֮ǰ���� ������õĽӿ�
 *
 * Parameters :  unAddress ����flashmap�洢λ��ȷ�� ��bl������Աȷ��
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLFlashInfoConfig(unsigned int unAddress);

/*
 * Description: ��ʼ��Ӧ����Ҫ��ȡ��Ϣ, loaderpt��, ��Ӧ����bl�ڶ��������õĽӿ�
 *
 * Note:
 *
 * Parameters :  ��
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLAppInit(void);

/*
 * Description: ��flash��ȡsyssetting
 *
 * Note:
 *
 * Parameters :  pstSysSetting ��ȡ��syssetting
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLGetSYSSetting(ADIBLSYSSetting_S * pstSysSetting);

/*
 * Description: ����syssetting��flash
 *
 * Note:
 *
 * Parameters :  stSysSetting ���õ�flash�еĵ�syssetting
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLSetSYSSetting(ADIBLSYSSetting_S stSysSetting);

/*
 * Description: ���õ�ǰ��tuner info
 *
 * Note:
 *
 * Parameters :  unTunerId tunerid
 *               eTunerType Tuner����
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLSaveOTATunerInfo(unsigned int unTunerId, ADITunerType_E eTunerType);

/*
 * Description: ����OTA��Ϣдota loaderpt
 *
 * Note:
 *
 * Parameters :  pstOtaLoaderPt д��flash��loaderpt�ṹ��
 *				 bEnableOTAFlag �ǲ������������OTA  ADI_TRUEΪ���������OTA   ADI_FALSEΪ�����󲻽���OTA
 *				bNeedCheckSWVer �Ƿ���Ҫloader�бȽ�����汾
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLSaveOTALoaderPt(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt, ADI_BOOL bEnableOTAFlag, ADI_BOOL bNeedCheckSWVer);

/*
 * Description: ����ǰ�� loaderpt��Ϣ
 *
 * Note:
 *
 * Parameters :  pstOtaLoaderPt д��flash��loaderpt�ṹ��
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLReadOTALoaderPt(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt);

/*
 * Description: ����WLan��Ϣ��BL���Ƶ�flash
 *
 * Note: IP����ʹ��
 *
 * Parameters : psWLanAPConf
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLSaveIpDownloadData(ADIBLIpDownloadInfoNew_S * psIpDownloadInfo);

/*
 * Description: ����OTA����ʱ��AntennaPower����
 *
 * Note:
 *
 * Parameters :  unTunerId Ŀǰ������
 *				 ucEnable :  1��   0�ر�
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLSaveOTAAntennaPowerEnableFlag(unsigned int unTunerId, unsigned char ucEnable);

/*
 * Description: ��ȡ����OUI
 *
 * Note:
 *
 * Parameters :  ����OUI
 *
 * Returns	  :  ��
 *            
 *			   
 */
void ADIBLGetOUI(unsigned char oui[3]);

/*
 * Description: ��ȡ����ID
 *
 * Note:
 *
 * Parameters :  ��
 *
 * Returns	  :  ����ID
 *            
 *			   
 */
unsigned short ADIBLGetMaunID(void);

/*
 * Description: ��ȡӲ���汾��
 *
 * Note:
 *
 * Parameters :  ��
 *
 * Returns	  :  Ӳ���汾��
 *            
 *			   
 */
unsigned short ADIBLGetHWVersion(void);

/*
 * Description: ��ȡ�ͻ�����Variant
 *
 * Note:
 *
 * Parameters :  ��
 *
 * Returns	  : �ͻ�����Variant
 *            
 *			   
 */
unsigned short ADIBLGetVariant(void);

/*
 * Description: ��ȡ����汾��/dsn
 *
 * Note:
 *
 * Parameters :  ��
 *
 * Returns	  :  ����汾��/dsn
 *            
 *			   
 */
unsigned short ADIBLGetSWVersion(void);

/*
 * Description: ��ȡ��ǰ����Ҫ�������߻�������
 *
 * Note:
 *
 * Parameters :  ��
 *
 * Returns	  :  ADIEtherType_E
 *            
 *			   
 */
ADIEtherType_E ADIBLGetEtherTypeCfg(void);

/*
 * Description: ��ȡSTB���ͺ�
 *
 * Note: label���ڴ�ռ��С��Ҫ���ڵ���STB_LABEL_LEN
 *
 * Parameters :  label ���STB�ͺ��ڴ�ռ�
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLGetSTBLabel(char label[STB_LABEL_LEN]);

/*
 * Description: ��ȡ��ǰLoader�İ汾��
 *
 * Note: �������汾���Ӱ汾,�����汾
 *
 * Parameters :  pnVer1 ���汾
 *               pnVer2 �Ӱ汾
 *               pnVer3 �����汾
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLGetLoaderVersion(int *pnVer1, int *pnVer2, int *pnVer3);

/*
 * Description: ��ȡ��ǰIrdeto Key��Ϣ
 *
 *
 * Parameters :  pSystemId key_sys_id
 *               pKeyVersion key�汾
 *				 pSignatureVersion keyǩ�ְ汾
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
 * Description: ����NandCfg
 *
 * Note ����Nandflash����, �������ȵ��� ���ܵ��������ӿ�
 *
 * Parameters :  pstInitParam flash��С����
 *               pstInitPartition ����������Ϣ[boot loader sysdata ��Щ����������������]
 *				 unFlashMapAddr Flashmap�߼�������ʼ��ַ
 *
 * Returns	  :   0 success,  other failed

// �������� boot  loader  sys_data �����ǹ̶���
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

	// ����Ϊ����NandFlash�ķ�������,���������޸�
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


