
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

/*Irdeto bbcb�ṹ��*/
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

/*Irdeto spcb�ṹ��*/
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
	unsigned int m_unVirEEpromAddr; /*vir eeprom��ʼ��ַ 4bytes*/
	unsigned int m_unVirEEpromTotalSize; /*vir eepromʹ��flash���ܴ�С 4bytes*/
	unsigned int m_unVirEEpromUnitSize; /*vir eepromһ����С��Ԫ�Ĵ�С 4bytes*/
	unsigned int m_unCrc32;/*crc32 4bytes*/
}ADIIrdetoBLFlashCfgInfo_S;

/*
 * Description: ��ʼ��irdeto��Ŀflashmap, booter loader app���̶�����Ҫ���ô˽ӿ���������flash������Ϣ
 *
 * Parameters : unAddress-���÷�������flash�е�λ��
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIIrdetoBLFlashInfoConfig(unsigned int unAddress);

/*
 * Description: ��ʼ��irdeto laoder��Ϣ, ����ſ��Զ�ȡspcb bbcb keystatus
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoAppInit(void);

/*
 * Description: ��ȡirdeto spcb����Ϣ, ֻ�е���ADIBLIrdetoAppInit����ܻ�ȡ��
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoGetSPCB(SPCB_STRUCT*  pstSPCB);

/*
 * Description: ��ȡirdeto bbcb����Ϣ, ֻ�е���ADIBLIrdetoAppInit����ܻ�ȡ��
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoGetBBCB(BBCB_STRUCT*  pstBBCB);

/*
 * Description: ��ȡirdeto key����Ϣ, ֻ�е���ADIBLIrdetoAppInit����ܻ�ȡ��
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoGetKeyStatus(IrdetoKeyStatus_S*  pstKeyStatus);

/*
 * Description: ����STB���ؾ�̬ip������������ (ip����ʹ��)
 *
 * Note: IP����������� Ȼ���ٵ��� ADIBLIrdetoSaveOTALoaderPt���������ip�Ͷ˿�
 *
 * Parameters : pstLocalIPV4Info
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoSaveLocalIpV4Info(const ADIBLLocalIPV4Info_S* pstLocalIPV4Info);

/*
 * Description:��loaderpt�ж�ȡ�����STB���ؾ�̬ip������������
 *
 * Note: ��Ӧ��ip���ý����ȡ��ǰIP��Ϣ
 *
 * Parameters : pstLocalIPV4Info
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoReadLocalIPV4Info(ADIBLLocalIPV4Info_S *pstLocalIPV4Info);

/*
 * Description: 
 *		case 1 : E_ADIBL_USB_DLΪUSB����, ����Ĭ�ϵ�usb�����ļ���irdeto.sdl �����������֮ǰ��check�Ƿ��д��ļ������޷�����
 *		case 2 : E_ADIBL_OTA_DL_DVBΪ����������OTA����, ��Ҫ��������Ƶ�������usOTAPid��ucOTATableId
 *		case 3 : E_ADIBL_OTA_DL_DVBOVERIP ʵ��Ϊ�鲥ts��������**Ŀǰ֧�ֲ�����**
 *		case 4 : E_ADIBL_IP_DL TCPIPЭ������ǩ�ֵ�sdl�ļ�, 
 *							   app��Ҫ��stIPInfo�����÷�����ip�Ͷ˿�, 
 *							   app��Ҫ����ADIBLIrdetoSaveLocalIpV4Info���ñ���IP(app�������û����û���DHCP��ȡ)
 *
 * Parameters : bEnableOTAFlag��Ϊtrueʱ�´ο����Ż��loader����
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoSaveOTALoaderPt(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt, ADI_BOOL bEnableOTAFlag);

/*
 * Description: ��flash�ж�ȡSYSSetting
 *
 * Parameters : 
 *
 * Returns	  : 
 *			   
 */
int ADIBLIrdetoGetSYSSetting(ADIBLSYSSetting_S * pstSysSetting);

/*
 * Description: ����SYSSetting��flash
 *
 * Parameters : 
 *
 * Returns	  : 
 *			   
 */
int ADIBLIrdetoSetSYSSetting(ADIBLSYSSetting_S stSysSetting);

/*
 * Description: ��ȡAPP������flash��ַ
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


