/****************************************************************************** 
* FileName : ADI_Nagra_Interface.h
* Author:      Steve.hou
* Date:         2015.11.09
* Description: Nagra CA interface file for app integration  using,
*            
*******************************************************************************/




#include "adi_typedef.h"

#ifndef _ADI_NAGRA_INTERFACE_H_
#define _ADI_NAGRA_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define CA_SRV_MAX					(8)
#define CA_MAX_SIZE_TXT_MAIL       (1*1024)


typedef enum 
{
    TXT_MAIL             = 0,
    TXT_ANNOUNCE         = 1,
    TXT_CLUB             = 2 
}Nagra_MailType_E;
typedef struct 
{
	unsigned int m_unServiceStatus ;
	unsigned int m_unCardStatus ;
	unsigned int m_unProgramStatus;		
	unsigned int m_unEntitlementStatus;
}SrvStatus_S;
typedef struct 
{
    unsigned int     m_unYear;
    unsigned char    m_ucMonty;
    unsigned char    m_ucDay;
    unsigned char    m_ucHour;
    unsigned char    m_ucMinute;
	unsigned char    m_ucSecond;
}NagraDateTime_S;

typedef struct         
{
    unsigned char        m_ucType;                
    unsigned char        m_ucClass;               
    unsigned char        m_ucPriority;
    unsigned int       m_unLen;
    NagraDateTime_S  m_sDelTime;   
    unsigned char    m_aucContent[CA_MAX_SIZE_TXT_MAIL];

    unsigned short    m_usDuration;
    unsigned char    m_ucCoverPer; 
}NagraMailContent_S;

typedef struct        
{   
    ADI_BOOL    m_bReadFlag;           
    ADI_BOOL    m_bLockFlag;            
    NagraDateTime_S  m_sArriveTime; 
    NagraMailContent_S m_sMsgContent;
}NagraMail_S;

typedef enum 
{
	NAGRA_ALARM,
	NAGRA_COMMAND,
	NAGRA_INFO	
}Nagra_MsgTYPE_E;

typedef enum 
{
	NAGRA_ALARM_CANCEL = 0,
	NAGRA_ALARM_CARD_REMOVED,
	NAGRA_ALARM_CARD_ERROR,
	NAGRA_ALARM_CARD_MUTE,
	NAGRA_ALARM_CARD_INVALID,
	NAGRA_ALARM_CARD_BLACKLISTED,
	NAGRA_ALARM_CARD_SUSPENDED,
	NAGRA_ALARM_CARD_NEVER_PAIRED,
	NAGRA_ALARM_CARD_NOT_PAIRED,
	NAGRA_ALARM_CARD_EXPIRED,
	NAGRA_ALARM_CARD_NOT_CERTIFIED,
	NAGRA_ALARM_NO_ACCESS,
	NAGRA_ALARM_RIGHT_SUSPENDED,
	NAGRA_ALARM_BLACK_OUT,
	NAGRA_ALARM_STRONG_PAIRING_REQUIRED,
	NAGRA_ALARM_CHIPSET_PAIRING_REQUIRED,
	NAGRA_ALARM_OTHER,
	NAGRA_ALARM_MAX
}Nagra_Alarm_E;

typedef enum  
{
    NAGRA_CMD_RESET_PIN_CODE, 
    NAGRA_CMD_MAIL,     
    NAGRA_CMD_FORCE_IDENTIFICATION_STANDARD,
    NAGRA_CMD_FORCE_IDENTIFICATION_ZONEID,    
    NAGRA_CMD_SET_MACROVISION_CPS,
    NAGRA_CMD_ENABLE_VIDEO,
    NAGRA_CMD_ENABLE_AUDIO,
    NAGRA_CMD_ENABLE_SMARTCARD1,
    NAGRA_CMD_ENABLE_SMARTCARD2,
    NAGRA_CMD_ENABLE_HARDDISC,
    NAGRA_CMD_ENABLE_DVD,
    NAGRA_CMD_ENABLE_SERIALPORT1,
    NAGRA_CMD_ENABLE_SERIALPORT2,
    NAGRA_CMD_ENABLE_PARALLELPORT,
    NAGRA_CMD_ENABLE_USBPORT,
    NAGRA_CMD_ENABLE_1394PORT,
    NAGRA_CMD_ENABLE_SPAREPORT1,
    NAGRA_CMD_ENABLE_SPAREPORT2,
    NAGRA_CMD_ENABLE_PERIPHERAL1,
    NAGRA_CMD_ENABLE_PERIPHERAL2,  
    NAGRA_CMD_SET_NETWORK_ID,
    NAGRA_CMD_MASTER_SLAVE_INIT,
    NAGRA_CMD_MASTER_SLAVE_CANCELLATION,
    NAGRA_CMD_MASTER_SLAVE_SINGLE_SHOT,
    NAGRA_CMD_MASTER_SLAVE_AUTOMATIC,
    NAGRA_CMD_SET_PIN_CODE,    
    NAGRA_CMD_FORCE_STANDBY_STANDARD,
    NAGRA_CMD_FORCE_STANDBY_ZONEID,   
    NAGRA_CMD_CONFIG_CAMLOCK,
    NAGRA_CMD_COPY_PROTECTION_VALIDATE,
    NAGRA_CMD_COPY_PROTECTION_REVOKE,
    NAGRA_CMD_COPY_PROTECTION_FORCE_AUTHENTICATION,
    NAGRA_CMD_COPY_PROTECTION_SET_KEY_SESSION_PERIOD,  
    NAGRA_CMD_RESTORE_FACTORY_SETTING,  
    NAGRA_CMD_FORCE_TUNE,
    NAGRA_CMD_FORCE_TUNE_WITH_TIMEOUT,
    NAGRA_CMD_FORCE_TUNE_ZONE,
    NAGRA_CMD_FORCE_TUNE_WITH_TIMEOUT_IPTV,
    NAGRA_CMD_FORCE_TUNE_ZONE_IPTV,   
    NAGRA_CMD_POP_UP,
    NAGRA_CMD_POP_UP_REMOVE,
    NAGRA_CMD_MOVIE_KEY,
    NAGRA_CMD_PUSH_VOD_CONTENT_CONFIG,
    NAGRA_CMD_PUSH_VOD_PARTITION_FORMATTING,
    NAGRA_CMD_PUSH_VOD_ERASE_ASSET,
    NAGRA_CMD_PUSH_VOD_EARSE_METADATA_FILE,
    NAGRA_CMD_PUSH_VOD_SET_DOWNLOADS_WAKEUP,
    NAGRA_CMD_FORCE_SOFTWARE_DWONLOAD_STANDARD,
    NAGRA_CMD_FORCE_SOFTWARE_DWONLOAD_BY_ID,
    NAGRA_CMD_CHANGE_USAGE_ID_RESIDENT_SOFTWARE,
    NAGRA_CMD_CHANGE_USAGE_ID_DOWNLOADABLE_APPS,  
    NAGRA_CMD_SET_COMMUNITY_TYPE,
    NAGRA_CMD_FORMAT_LOGICAL_DISK,
    NAGRA_CMD_USAGE_MONITORING,
    NAGRA_CMD_BROADCAST_NETWORK_OPERATOR_LOCK,
    NAGRA_CMD_SET_ZONE_ID,
    NAGRA_CMD_CANCEL_ID,
    NAGRA_CMD_SET_COUNTRYCODE,
    NAGRA_CMD_EMM_WAKE_UP_DISABLING_FEATURE,
    NAGRA_CMD_EMM_WAKE_UP_SETTING_PARAMETERS,
    NAGRA_CMD_UPDATE_COHABITATION_TABLES,
    NAGRA_CMD_REBOOT_STB,   
    NAGRA_CMD_BGA_DISABLE,
    NAGRA_CMD_BGA_ENABLE,
    NAGRA_CMD_SET_PAIRING_CONFIG,
    NAGRA_CMD_FINGERPRINT,
    NAGRA_CMD_NUM
}Nagra_Cmd_E;

typedef enum 
{
	Nagra_INFO_SYSTEM_INFORMATION,			
	Nagra_INFO_SMARTCARD_INFOMAITON,		
	Nagra_INFO_SMARTCARD_DELTATIME			
}Nagra_Info_E;


typedef struct
{
	unsigned char           		m_aucCakVer[64];
	unsigned char           		m_aucIrdSerNum[64];
	unsigned char           		m_aucProInfo[64];
}SysInfo_S;

typedef struct
{
	unsigned char           		m_ucSCStatuc;
	unsigned char           		m_aucSCVer[64];
	unsigned char           		m_aucSCNum[64];
}SmartCardInfo_S;
typedef struct 
{
   unsigned int m_unCAData;
   unsigned int m_unCADataSize;
   unsigned int m_unCADataBack;
   unsigned int m_unCADataBackSize;
   unsigned int m_unPKCSC;
   unsigned int m_unPKCSCSize;
   unsigned int m_unIRD;
   unsigned int m_unIRDSize;
   unsigned int m_unMail;
   unsigned int m_unMailSize;
}Nagra_FlashInfo_S;

int ADI_Nagra_SetAddress(Nagra_FlashInfo_S sNagraFlash);

int ADI_Nagra_ReqSysInfo(void);
int ADI_Nagra_ReqScInfo(void);

int ADI_Nagra_Mail_Del(unsigned int dwIndex);
int ADI_Nagra_Mail_DelAll(void);
int ADI_Nagra_Mail_GetNum(void);
int ADI_Nagra_Mail_GetInfo(unsigned int dwIndex, NagraMail_S** ppstTxt);

ADI_BOOL ADI_Nagra_Mail_VerifyNewFlag(void);
int ADI_Nagra_Mail_SetReadFlag(unsigned int dwIndex, ADI_BOOL bRead);

ADI_BOOL ADI_Nagra_GetSysIrdSN(unsigned char  *pucNumber, int nLen);
ADI_BOOL ADI_Nagra_GetSCNumber(unsigned char  *pucNumber, int nLen);
extern void GetNetWorkTime(ADIOSSysTime_S *pTime);

#ifdef  __cplusplus
}
#endif

#endif 

