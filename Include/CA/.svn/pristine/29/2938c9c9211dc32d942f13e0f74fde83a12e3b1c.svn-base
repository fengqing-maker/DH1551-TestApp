#include "adi_typedef.h"
#include "adi_irdeto_bl.h"
#include "adi_os.h"
#include "adi_osg.h"
#ifndef _CCA_INTERFACE_H_
#define _CCA_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define CA_DEMUX_MAX (4)	//One Tuner:DEMUX_MAX =2; Two Turner: DEMUX_MAX =3
#define CA_SRV_MAX (3)
#define ERRCODE_STRING_SIZE (8)
#define MAX_ES_PERSTREAM (16)
#define STREAM_STATUS_LEN (0x06)

#define	MAX_SIZE_FIRMWARE                (64)
#define MAX_SIZE_IRD_SERIALNUMBER      (32)
#define MAX_SIZE_LOASER                  (64)
#define MAX_SIZE_TXT_MAIL (511) 
#define CA_MAX_STREAMNUMBER_PERHANDLE (5)
#define CA_PRODUCT_ID_LENGTH (2) 
#define CA_MAX_PRODUCT_COUNT (400)
#define CA_IUC_GENERIC_LENGTH (512)
#define CA_CLOAK_NORMALSIZE  (64)
#define CA_CLOAK_CORELISTSIZE (256)
#define CA_MAX_MONITORMSG_LEN (256)
#define MAX_ATTRIBDATA_LEN (511)


typedef enum 
{
    ALARM_MSG,
    INFO_MSG,
    COMMAND_MSG,
    STATUS_MSG
}CloakEvent_E;

typedef enum 
{
    INFO_SERVICE_STATUS,
    INFO_LOADER_STATUS,
    INFO_PRODUCT_STATUS,
    INFO_CLIENT_STATUS, 
    INFO_COREDOWNLOAD_STATUS,
    INFO_IFCPIMAGE_STATUS,
    INFO_SOUSERMSG_ENDDATA,
    INFO_PLAYBACKSTATUS,
    INFO_PAIDNOTIFY,
    INFO_MAX
}CloakInfo_E;

typedef enum 
{
    COMMAND_APP_HOMECHANNEL_SCAN,
    COMMAND_RECONNECT_CURRENT_SERVICE,
    COMMAND_REBOOT,
    COMMAND_EMM_OTA,
    COMMAND_OTA_NEXT,
    COMMAND_OTA_DETECT,
    COMMAND_ATTRIB, 
    COMMAND_MAIL,
    COMMAND_RESETTOFACTORY,
    COMMAND_MONITOR, 
    COMMAND_EMMDES_STATUS,
    COMMAND_ECM_STATUS,
	COMMAND_HOMECHANNEL_SCAN,
	COMMAND_FORCE_TUNE_TO_SRV,
	COMMAND_INSTALLER_PINCODE,
	COMMAND_PC_PINCODE,  //父母锁密码
	COMMAND_SPE_STATUS,  //SPE rem
	COMMAND_NONPVRENABLEFLAG,	//nonPVREnableFlag
	COMMAND_PVRTLV_EXPIRYTIME,	//PVR TLV Expiry time
	COMMAND_PVRRECORD_STATUS,	//PVR_RECORD_STATUS
	COMMAND_PVRPLAYBACK_STATUS,	//PVR_PLAYBACK_STATUS
	COMMAND_COPYCONTROL_CGMS,	//COPYCONTROL_CGMS
	COMMAND_COPYCONTROL_HDCP,	//COPYCONTROL_HDCP
	COMMAND_PRE_DATE,
	COMMAND_SCRAMBLE_SERVICE,
    COMMAND_MAX
}CloakCommand_E;

typedef enum 
{
    CA_STATUS_OTA_OK, 
    CA_STATUS_OTA_STATUS,
    CA_STATUS_OTA_FAILURE,

    CA_STATUS_MAX
}CloakStatus_E;


typedef enum 
{
    BAKMSG_TEXT000 = 0 ,          
    BAKMSG_TEXT001 = 1 ,          
    BAKMSG_TEXT002 = 2 ,          
    BAKMSG_TEXT003 = 3 ,          
    BAKMSG_TEXT004 = 4 ,          
    BAKMSG_TEXT005 = 5 ,          
    BAKMSG_TEXT006 = 6 ,          
    BAKMSG_TEXT007 = 7 ,          
    BAKMSG_TEXT008 = 8 ,          
    BAKMSG_TEXT009 = 9 ,          
    BAKMSG_TEXT010 = 10,          
    BAKMSG_TEXT011 = 11 ,         
    BAKMSG_TEXT012 = 12 ,         
    BAKMSG_TEXT013 = 13 ,         
    BAKMSG_TEXT014 = 14 ,         
    BAKMSG_TEXT015 = 15 ,         
    BAKMSG_TEXT016 = 16 ,         
    BAKMSG_TEXT017 = 17 ,         
    BAKMSG_TEXT018 = 18 ,         
    BAKMSG_TEXT019 = 19 ,         
    BAKMSG_TEXT020 = 20 ,         
    BAKMSG_TEXT021 = 21 ,         
    BAKMSG_TEXT022 = 22 ,         
    BAKMSG_TEXT023 = 23 ,         
    BAKMSG_TEXT024 = 24 ,         
    BAKMSG_TEXT025 = 25 ,        
    BAKMSG_TEXT026 = 26 ,      
    BAKMSG_TEXT027 = 27 ,      
    BAKMSG_TEXT028 = 28 ,      
    BAKMSG_TEXT029 = 29 ,      
    BAKMSG_TEXT030 = 30 ,      
    BAKMSG_TEXT031 = 31 ,      
    BAKMSG_TEXT032 = 32 ,      
    BAKMSG_TEXT033 = 33 ,          
    BAKMSG_TEXT034 = 34 ,          
    BAKMSG_TEXT035 = 35 ,          
    BAKMSG_TEXT036 = 36 ,          
    BAKMSG_TEXT037 = 37 ,          
    BAKMSG_TEXT038 = 38 ,          
    BAKMSG_TEXT039 = 39 ,          
    BAKMSG_TEXT040 = 40 ,          
    BAKMSG_TEXT041 = 41 ,          
    BAKMSG_TEXT042 = 42 ,          
    BAKMSG_TEXT043 = 43 ,          
    BAKMSG_TEXT044 = 44 ,          
    BAKMSG_TEXT045 = 45 ,          
    BAKMSG_TEXT046 = 46 ,          
    BAKMSG_TEXT047 = 47 ,          
    BAKMSG_TEXT048 = 48 ,          
    BAKMSG_TEXT049 = 49 ,          
    BAKMSG_TEXT050 = 50 ,          
    BAKMSG_TEXT051 = 51 ,           
    BAKMSG_TEXT052 = 52 ,           
    BAKMSG_TEXT053 = 53 ,          
    BAKMSG_TEXT054 = 54 ,          
    BAKMSG_TEXT055 = 55 ,          
    BAKMSG_TEXT056 = 56 ,          
    BAKMSG_TEXT057 = 57 ,          
    BAKMSG_TEXT058 = 58 ,          
    BAKMSG_TEXT059 = 59 ,          
    BAKMSG_TEXT060 = 60 ,          
    BAKMSG_TEXT061 = 61 ,          
    BAKMSG_TEXT062 = 62 ,          
    BAKMSG_TEXT063 = 63 ,         
    BAKMSG_TEXT064 = 64 ,         
    BAKMSG_TEXT065 = 65 ,         
    BAKMSG_TEXT066 = 66 ,         
    BAKMSG_TEXT067 = 67 ,         
    BAKMSG_TEXT068 = 68 ,         
    BAKMSG_TEXT069 = 69 ,         
    BAKMSG_TEXT070 = 70 ,         
    BAKMSG_TEXT071 = 71 ,         
    BAKMSG_TEXT072 = 72 ,         
    BAKMSG_TEXT073 = 73 ,         
    BAKMSG_TEXT074 = 74 ,         
    BAKMSG_TEXT075 = 75 ,            
    BAKMSG_TEXT076 = 76 ,            
    BAKMSG_TEXT077 = 77 ,            
    BAKMSG_TEXT078 = 78 ,            
    BAKMSG_TEXT079 = 79 ,           
    BAKMSG_TEXT080 = 80 ,           
    BAKMSG_TEXT081 = 81 ,           
    BAKMSG_TEXT082 = 82 ,           
    BAKMSG_TEXT083 = 83 ,           
    BAKMSG_TEXT084 = 84 ,           
    BAKMSG_TEXT085 = 85 ,           
    BAKMSG_TEXT086 = 86 ,           
    BAKMSG_TEXT087 = 87 ,           
    BAKMSG_TEXT088 = 88 ,           
    BAKMSG_TEXT089 = 89 ,           
    BAKMSG_TEXT090 = 90 ,           
    BAKMSG_TEXT091 = 91 ,           
    BAKMSG_TEXT092 = 92 ,           
#if 1                                  
    BAKMSG_TEXT093 = 93 ,           
    BAKMSG_TEXT094 = 94 ,           
    BAKMSG_TEXT095 = 95 ,           
    BAKMSG_TEXT096 = 96 ,           
    BAKMSG_TEXT097 = 97 ,           
    BAKMSG_TEXT098 = 98 ,           
    BAKMSG_TEXT099 = 99 ,           
    BAKMSG_TEXT100 = 100 ,          
    BAKMSG_TEXT101 = 101 ,          
    BAKMSG_TEXT102 = 102 ,          
    BAKMSG_TEXT103 = 103 ,          
                    
    BAKMSG_TEXT104 = 104 ,          

    BAKMSG_TEXT105 = 105 ,          
    BAKMSG_TEXT106 = 106 ,          
    BAKMSG_TEXT107 = 107 ,          
    BAKMSG_TEXT108 = 108 ,          
    BAKMSG_TEXT109 = 109 ,          
    BAKMSG_TEXT110 = 110 ,          
    BAKMSG_TEXT111 = 111 ,          
    BAKMSG_TEXT112 = 112 ,          
#endif
   
    BAKMSG_TEXT113 = 113 ,         
    BAKMSG_TEXT114 = 114 ,         


    BAKMSG_TEXT115 = 115 ,            
    BAKMSG_TEXT116 = 116 ,            
    BAKMSG_TEXT117 = 117 ,          
    BAKMSG_TEXT118 = 118 ,         
    BAKMSG_TEXT119 = 119 ,         
    BAKMSG_TEXT120 = 120 ,         
    BAKMSG_TEXT121 = 121 ,         
    BAKMSG_TEXT122 = 122 ,         
    BAKMSG_TEXT123 = 123 ,         
    BAKMSG_TEXT124 = 124 ,         
    BAKMSG_TEXT125 = 125 ,         
    BAKMSG_TEXT126 = 126 ,         
    BAKMSG_TEXT127 = 127 ,         
    BAKMSG_TEXT128 = 128 ,         
    BAKMSG_TEXT129 = 129 ,         
    BAKMSG_TEXT130 = 130 ,         
    BAKMSG_TEXT131 = 131 ,         
    BAKMSG_TEXT132 = 132 ,         
    BAKMSG_TEXT133 = 133 ,         
    BAKMSG_TEXT134 = 134 ,         
    BAKMSG_TEXT135 = 135 ,         
    BAKMSG_TEXT136 = 136 ,         
    BAKMSG_TEXT137 = 137 ,         
    BAKMSG_TEXT138 = 138 ,         
    BAKMSG_TEXT139 = 139 ,         
    BAKMSG_TEXT140 = 140 ,         
    BAKMSG_TEXT141 = 141 ,         


    BAKMSG_TEXT142 = 142 ,          
    BAKMSG_TEXT143 = 143 ,          
    BAKMSG_TEXT144 = 144 ,          
    BAKMSG_TEXT145 = 145 ,          
    

    BAKMSG_TEXT146 = 146 ,       
    BAKMSG_TEXT147 = 147 ,       
    BAKMSG_TEXT148 = 148 ,       


    BAKMSG_TEXT149 = 149 ,          
    BAKMSG_TEXT150 = 150 ,          
    BAKMSG_TEXT151 = 151 ,          
    BAKMSG_TEXT152 = 152 ,          
    BAKMSG_TEXT153 = 153 ,          
    BAKMSG_TEXT154 = 154 ,          


	
    BAKMSG_TEXT155 = 155 ,
    BAKMSG_TEXT156 = 156 ,
    BAKMSG_TEXT157 = 157 ,
    BAKMSG_TEXT158 = 158 ,
    BAKMSG_TEXT159 = 159 ,
    BAKMSG_TEXT160 = 160 ,
    BAKMSG_TEXT161 = 161 ,
    BAKMSG_TEXT162 = 162 ,
    BAKMSG_TEXT163 = 163 ,
    BAKMSG_TEXT164 = 164 ,
    BAKMSG_TEXT165 = 165 ,
    BAKMSG_TEXT166 = 166 ,
    BAKMSG_TEXT167 = 167 ,    
    BAKMSG_TEXT168 = 168 ,
    BAKMSG_TEXT169 = 169 ,    
    BAKMSG_TEXT170 = 170 ,
    BAKMSG_TEXT171 = 171 ,
    BAKMSG_TEXT172 = 172 ,
    BAKMSG_TEXT173 = 173 ,
    BAKMSG_TEXT174 = 174 ,
    BAKMSG_TEXT175 = 175 ,
    BAKMSG_TEXT176 = 176 ,
    BAKMSG_TEXT177 = 177 ,
    BAKMSG_TEXT178 = 178 ,
    BAKMSG_TEXT179 = 179 ,
    BAKMSG_TEXT180 = 180 ,
    BAKMSG_TEXT181 = 181 ,
    BAKMSG_TEXT182 = 182 ,
    BAKMSG_TEXT183 = 183 ,
    BAKMSG_TEXT184 = 184 ,
    BAKMSG_TEXT185 = 185 ,
    BAKMSG_TEXT186 = 186 ,
    BAKMSG_TEXT187 = 187 ,
    BAKMSG_TEXT188 = 188 ,
    BAKMSG_TEXT189 = 189 ,
    BAKMSG_TEXT190 = 190 ,
    BAKMSG_TEXT191 = 191 ,
    BAKMSG_TEXT192 = 192 ,
    BAKMSG_TEXT193 = 193 ,
    BAKMSG_TEXT194 = 194 ,
    BAKMSG_TEXT195 = 195 ,
    BAKMSG_TEXT196 = 196 ,
    BAKMSG_TEXT197 = 197 ,
    BAKMSG_TEXT198 = 198 ,
    BAKMSG_TEXT199 = 199 , 
    BAKMSG_TEXT200 = 200 ,
    BAKMSG_TEXT201 = 201 ,
    BAKMSG_TEXT202 = 202 ,
    BAKMSG_TEXT203 = 203 ,
    BAKMSG_TEXT204 = 204 ,
    BAKMSG_TEXT205 = 205 ,
    BAKMSG_TEXT206 = 206 ,
    BAKMSG_TEXT207 = 207 ,
    BAKMSG_TEXT208 = 208 ,
    BAKMSG_TEXT209 = 209 ,
    BAKMSG_TEXT210 = 210 ,
    BAKMSG_TEXT211 = 211 ,
    BAKMSG_TEXT212 = 212 ,
    BAKMSG_TEXT213 = 213 ,
    BAKMSG_TEXT214 = 214 ,
    BAKMSG_TEXT215 = 215 ,
    BAKMSG_TEXT216 = 216 ,
    BAKMSG_TEXT217 = 217 ,
    BAKMSG_TEXT218 = 218 ,
    BAKMSG_TEXT219 = 219 ,
    BAKMSG_TEXT220 = 220 ,
    BAKMSG_TEXTMAX
}CloakMsgText_E;

typedef enum
{
	EMAIL_ARRIV_DESC,
	EMAIL_ARRIV_ASC

}MailSort_E;


typedef enum 
{
    ES_UNKNOWN,
    ES_AUDIO,
    ES_VIDEO,
    ES_AV,
    ES_CRYPT_MAX = 0xff
} EsType_E;

typedef struct 
{
    char m_aucStatus[ERRCODE_STRING_SIZE+1];
    CloakMsgText_E m_eTextnum;
} SrvErrorInfo_S;

typedef struct 
{
	ADI_BOOL m_isSPETimeValid;
	
	/**
     * Unique product identifier
     *
     * This value uniquely identifies a product and is the big-endian representation 
     * of the 'ID' field for the corresponding product configuration in the CA server.
     * For example, if the product ID in the head end is 1000 decimal,
     * the product ID in this structure will be {0x03, 0xe8}.
     * See ::UC_SIZE_PRODUCT_ID for its size.
     */
    unsigned char m_SPEProductID[2];

    /**
     * How long the product entitlement is remaining.
     *
     * The unit of remaining time is DAY.
     */
    unsigned int m_SPERemainingTime;
}SrvSPEStatusInfo_S;

typedef struct 
{
    int m_nIndex;
    unsigned char m_aucStatus[ERRCODE_STRING_SIZE+1];
    CloakMsgText_E m_eTextnum;
    EsType_E m_eSerEsType;
}ErrorInfo_S;

typedef struct 
{
    unsigned short m_wYear;
    unsigned char m_ucMonth;
    unsigned char m_ucDay;
    unsigned char m_ucHour;
    unsigned char m_ucMinute;
    unsigned char m_ucSecond;
}DateTime_S;

typedef struct 
{
	ADI_HANDLE 	  m_hPVRHandle;
	unsigned char m_aucStatus[ERRCODE_STRING_SIZE+1];
   	unsigned int  m_unShareEnable;
}PVRPlayBack_S;

typedef enum 
{
    MENU_SERVICE_STATUS,
    MENU_LOADER_STATUS,
    MENU_PRODUCT_STATUS,
    MENU_CLIENT_STATUS, 
    MENU_PLAYBACK_STATUS,
    MENU_MAX
}StatusMenu_E;


typedef struct 
{
    unsigned char m_ucManufacturerId;
    unsigned char m_ucHardwareVersion;
    unsigned short m_wVariant;
    unsigned short m_wSystemId;
    unsigned short m_wKeyVersion;
    unsigned short m_wSignatureVersion;
    unsigned int m_dwLdSECSSN;
    unsigned short m_usDownLoadID;
    unsigned char m_aucFirmVersion[MAX_SIZE_FIRMWARE+1];
    unsigned char m_aucLoadVersion[MAX_SIZE_LOASER+1];
    unsigned char m_aucSerialNO[MAX_SIZE_IRD_SERIALNUMBER+1];
    unsigned short m_wSpecInfo;
    DateTime_S m_stSignDateTime;
    DateTime_S m_stDownloadDateTime;
	unsigned char m_aucClientID[CA_CLOAK_NORMALSIZE];
	unsigned char m_aucCCAVersion[CA_CLOAK_NORMALSIZE];
}LoaderStatus_S;

typedef enum 
{
    SRV_EMM_E,
    SRV_DES_E,
    SRV_MAX
}SrvType_E;

typedef struct 
{
    ADI_BOOL m_bIsECM;
    unsigned short m_wCAPID;
    ADI_BOOL m_bCanRecord;
    unsigned char m_ucstreamStatus[STREAM_STATUS_LEN+1];
    unsigned int m_dwESCount;
    unsigned short m_wESPID[MAX_ES_PERSTREAM];
}StreamStatus_S;

typedef struct 
{
    unsigned int m_dwClientHandle;
    SrvType_E  m_eServiceType;
    SrvErrorInfo_S m_stServiceStatus;
    unsigned int m_dwStreamCount;
    StreamStatus_S m_stStreamStatus[CA_MAX_STREAMNUMBER_PERHANDLE];
}SrvInfo_S;
typedef struct
{
	unsigned char m_aucPin[32];
	unsigned int  m_unLen;
}SystemPin_S;
typedef struct 
{
    unsigned char m_ucServiceCount;
    SrvInfo_S m_stServiceInfo[CA_DEMUX_MAX+CA_SRV_MAX];
} SvrInfoList_S;	
typedef enum
{
	E_CCA_SOURCE,
	E_SOFTCELL_SOURCE,
	E_SOFT_OTHER
}ProductType_E;

typedef struct 
{
    unsigned char m_ucSectorNum;
    ADI_BOOL m_bEntitled;
    unsigned char m_aucProductId[CA_PRODUCT_ID_LENGTH];
    DateTime_S  m_ststartDate;
    unsigned char m_ucduration;
    unsigned int m_dwproductType;
	ProductType_E m_eSourceType;
}ProductInfo_S;


typedef struct 
{
    unsigned short m_wProductCount;
    ProductInfo_S m_stProductInfo[CA_MAX_PRODUCT_COUNT];
}ProductList_S;



typedef struct 
{
    unsigned short m_wMsgLength;
    unsigned char  m_aucTmsData[CA_IUC_GENERIC_LENGTH];
}TMSData_S;


typedef struct 
{
    unsigned char m_aucIucVersion[CA_CLOAK_NORMALSIZE];
    unsigned int m_dwSN;
    TMSData_S m_stTmsData;
    unsigned char m_aucCapability[CA_IUC_GENERIC_LENGTH+1];
    unsigned char m_ucSecureTye;
    unsigned short m_wLocKId;
    unsigned int m_dwCaSystemId;
    unsigned int m_dwEcmCount;
    unsigned int m_dwEmmCount;
    unsigned int m_dwCSSN;
    unsigned char m_aucBuildInfo[CA_CLOAK_NORMALSIZE];
    unsigned char m_aucNationality[CA_CLOAK_NORMALSIZE];
    unsigned char m_aucClientID[CA_CLOAK_NORMALSIZE];
}ClientInfo_S;
typedef struct 
{
	unsigned char m_aucCoreBuildInfo[CA_CLOAK_CORELISTSIZE];
	unsigned char m_aucCoreList[CA_CLOAK_NORMALSIZE];
	unsigned char m_aucCoreUpdateStutus[CA_CLOAK_NORMALSIZE];
}CloakCoreStatus_S;
typedef struct 
{
	unsigned char m_aucImageStatus[CA_CLOAK_NORMALSIZE];
	unsigned char m_aucDownloadProgress[CA_CLOAK_NORMALSIZE];
}CloakIFCPStatus_S;

#define IRD_MESSAGE_MAX_LENGTH	(4 + 2 + 4096)  // wMsgHeader + Destination ID + Length + Payload + CRC

#define SOUSERPAYLOADLEN_MAX	0x40
typedef struct
{
    /**
     * identify the operator by its CA System ID
     */
    unsigned int m_unCaSystemID;

    /**
     * the length of raw IRD message
     */
    unsigned int m_unMsgLen;

    /**
     * raw IRD message
     */
    unsigned char m_aucSouserMsg[SOUSERPAYLOADLEN_MAX];
}ClockSubMsgStatus_S;


typedef enum 
{
    PVRTLV_UNKNOWN_TAG = 0x0,
    PVRTLV_CCI_TAG = 0x04,
    PVRTLV_ExpiryTime_TAG = 0x06,
    PVRTLV_NonPVREnable_TAG = 0x11,
    PVRTLV_VODASSETID_TAG = 0x14,
    PVRTLV_PVRShareable_TAG = 0x15,
    PVRTLV_DeviceDomainID_TAG = 0x16,
    PVRTLV_TAG_MAX = 0xFF
}PVRTLVType_E;

typedef struct
{
    /* Type of the TLV */
    PVRTLVType_E m_eTLVTag;

    /* the length of all TLVs */
    unsigned short m_unTLVLen;

    /* the TLV data */
    unsigned char m_aucTLVData[0x10];
}ClockPVRTLVData_S;

#define CCA_MAX_PVRMETADATA_LEN (0x100)

typedef struct
{
    unsigned char m_PVRCCIApsInfo;		//uc_copycontrol_cci
    unsigned char m_PVRCCIEmiInfo;		//uc_copycontrol_cci
	unsigned char m_nonPVREnableFlag;
	unsigned int  m_unPVRExpiryTime;	//计时单位为second -- The expiry time of the content, as seconds from 1 January 2000 00:00. 
	
	unsigned int  m_unPVRMetalen;
	unsigned char m_aucPVRMetadata[CCA_MAX_PVRMETADATA_LEN];
}ADIPVRMetadata_S;		//same with uc_buffer_st;


typedef struct 
{
    unsigned int m_dwClientHandle;
    unsigned char m_ucMonitorMsg[CA_MAX_MONITORMSG_LEN+1];
}ECMEMMMonitor_S;


typedef struct 
{
    unsigned int m_dwClientHandle;
    unsigned char m_aucStatus[ERRCODE_STRING_SIZE+1];
    CloakMsgText_E m_eTextnum;
}ServiceStatus_S;


typedef struct 
{
    unsigned char m_aucStatus[ERRCODE_STRING_SIZE+1];
    unsigned short m_wECMPID;
}ECMStatus_S;



typedef enum 
{
    TXT_TYPE_MAIL,
    TXT_TYPE_ANNOUNCE,
    TXT_TYPE_CLUBNUM, 
    TXT_TYPE_MAX
}TxtType_E;

typedef enum 
{
    TXT_SHOW_NORMAL,
    TXT_SHOW_TIMED,	
    TXT_SHOW_FORCED,

    TXT_SHOW_MAX
}TxtShowMode_E;


typedef struct 
{ 
    TxtType_E m_eType; 
    TxtShowMode_E m_eClass;
    unsigned char m_ucPriority; 
    unsigned short m_wLen; 
    DateTime_S  m_stDeleteTime;
    unsigned char m_aucContent[MAX_SIZE_TXT_MAIL+1];
}CloakMsg_S;


typedef enum 
{
    CA_TMS_TYPE_NORMALMAIL ,
    CA_TMS_TYPE_FORCEDMAIL ,
    CA_TMS_TYPE_FINGERPRT , 
    CA_TMS_TYPE_FINGERPRTOPTION,
    
    CA_TMS_TYPE_MAX
}CloakTmsType_E;

typedef struct 
{
    unsigned short m_wMsgLength; 
    unsigned char m_aucMessageData[MAX_ATTRIBDATA_LEN+1];
    CloakTmsType_E m_eType;
    
  
    ADI_BOOL m_bFlash; 
    ADI_BOOL m_bBanner; 
    unsigned char m_ucCoverPer;
    unsigned short m_wDuration;

    ADI_BOOL m_bCovert;	
	unsigned char		m_ucLocationX;	
    unsigned char		m_ucLocationY;  
    unsigned char       m_ucBgTransAlpha; 
    unsigned int	    m_dwBgColour;		
    unsigned char       m_ucFontTransAlpha; 
    unsigned int	    m_dwFontColour;	  
    unsigned char		m_ucFontType;	 
}CloakAttribCovert_S;
typedef struct 
{
	unsigned short        m_wNetworkID; 
	unsigned short        m_wTransportStreamID; 
	unsigned short        m_wServiceID; 
}IRDServiceInfo_S;

typedef struct Mail		
{
    ADI_BOOL  m_bReadFlag;
    DateTime_S m_stArriveTime;
    CloakMsg_S m_stMail;
} CloakMail_S;

typedef struct
{
   unsigned int m_unCANvrm;
   unsigned int m_unCANvrmSize;
   unsigned int m_unCANvrmBk;
   unsigned int m_unCANvrmBkSize;
   unsigned int m_unSecureCore;
   unsigned int m_unSecureCoreSize;
   unsigned int m_unSecureCoreBK;
   unsigned int m_unSecureCoreBKSize;
   unsigned int m_unCfgSoftCell;
   unsigned int m_unCfgSoftCellSize;
   unsigned int m_unCfgSoftCellBK;
   unsigned int m_unCfgSoftCellBKSize;
   unsigned int m_unMailAddr;
   unsigned int m_unMailSize;
   unsigned int m_unIFCPPart1;
   unsigned int m_unIFCPPart1Size;
   unsigned int m_unIFCPPart2;
   unsigned int m_unIFCPPart2Size;
}CADataFlash_S;


int AlarmMsg_GetCompLevelShutType(unsigned int dwGroupHandle);
int ADI_Cloak_SetFingerColor(unsigned int * punColor, unsigned int unCnt);

/*

邮件相关的函数
*/
int ADI_CA_MailDel(unsigned int dwIndex);
int ADI_CA_MailDelAll(void);
int ADI_CA_MailGetNum(void);
int ADI_CA_MailGetInfo(unsigned int dwIndex, CloakMail_S** ppstTxt);
ADI_BOOL ADI_CA_HaveNewMail(void);
int ADI_CA_MailUnReadNum(void);
int ADI_CA_Mail_Sort(MailSort_E emStyle);


int ADI_Cloak_MailSetReadFlag(unsigned int dwIndex, ADI_BOOL bRead);

int ADI_CCA_SetPEFData(unsigned char *pucPEFHexBuf, unsigned int unPEFHexLen);

ADI_BOOL ADICloakGetEndDate ( DateTime_S *psPreView );
ADI_BOOL ADICloakGetPrivewStatus ( unsigned int unNetID, unsigned int unTSID, unsigned int unSrvID, SrvSPEStatusInfo_S * psPreView );

int Menu_EnterIrdetoMenu( StatusMenu_E eQueryDataType);
void Menu_ExitIrdetoMenu(void);
unsigned int ADI_CCA_GetMenuClientSN(void);


int ADI_CA_Nvrm_EraseCAFlash(void);
int ADI_CA_Nvrm_ResetCAData(void);

int ADI_CA_MenuEnableMonitor( unsigned int dwServiceHandle, ADI_BOOL bIsEnable);

ADI_BOOL ADI_CA_SetOverFPType(ADI_BOOL bShowSN);

unsigned int ADI_CA_SetAddress(CADataFlash_S pCaDataPartition);

unsigned int ADI_CA_SetFPUISurface(ADIOSGRect_S * psUpdateRect, unsigned int unFontSize);

//Buffer 最小长度为64
unsigned int ADI_CCA_GetMenuClientID ( unsigned char * pucBuf, unsigned int unBufLen );


//对应CCA TSC文件中CDSN, String 最小长度为16
int ADICAGetCAIDString(char * pcCAIDData, unsigned int unCAIDLen);
//对应CCA TSC文件中PRIVATEDATA, String 最小长度为32
int ADICAGetPrivateData(unsigned char * pdata, unsigned int * nLen);

extern unsigned int Get32Font(void);

extern void GetNetWorkTime(ADIOSSysTime_S *pTime);

#ifdef  __cplusplus
}
#endif

#endif

