#include "adi_typedef.h"
#include "adi_irdeto_bl.h"
#include "adi_os.h"
#include "adi_osg.h"


#ifndef _ADI_IRDETO_INTERFACE_H_
#define _ADI_IRDETO_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define     MAX_SC_NUMBER       2 
#define     SC_NUMBER_LEN       16 
#define     SC_TYPE_LEN         8 
#define     SC_VER_LEN          8 
#define     SC_NATION_LEN       8 

#define     SOURCE_SMARTCARD    4 
#define     SOURCE_APPLICATION  32
#define     SOURCE_MOD_EMM_SOURCE 6
#define     SOURCE_MOD_ECM_SOURCE 9							   
#define     SOURCE_EMM_SOURCE 2
#define     SOURCE_ECM_SOURCE 1
#define 	CA_MAX_PRODUCT_COUNT (400)							 

#define 	CA_DEMUX_MAX 				 2 
#define 	CA_SRV_MAX 					 8
#define 	INVALID_BAKMSG_TEXT         (0xFFFF )
#define 	CA_MAX_SIZE_FINGERPRINT     (15)
#define 	CA_MAX_SIZE_TXT_MAIL        (512)
#define		MAX_CPNT					 20
#define		CPNT_STATUS_NAME_LEN		 32
#define		CPNT_STATUS_VERSION_LEN	     21
#define		CPNT_STATUS_DATE_LEN		 128
#define     MAX_SERVICE_RESOURCES        32
#define     MAX_SRC_EMM_MONITOR_LEN      64
#define     MAX_SRC_ECM_MONITOR_LEN      64
#define     MAX_ECMSERVICE_STREAMS       32
#define		MAX_EMM_USERLOAD_LEN		 256 
#define		MAX_ATTRIBDATA_LEN 			 511
#define 	MAX_SC_PINCODE_LEN			 2
#define 	MAX_PAYLOAD_LEN 			 256
#define 	MAX_SC_USERINFO_LEN 		 28
#define 	CA_MAX_COUNTRY_NUM           (20)
#define 	MAX_SC_NUMSECTOR_SIZE 		 8
#define		CA_MAX_SIZE_LOASER                  (64)
#define		CA_MAX_SIZE_FIRMWARE                (64)
#define  	CA_MAX_SIZE_IRD_SERIALNUMBER      (32)


//错误信息级别
typedef enum _STATUS_SEVERITY_EN
{
	IRDETO_STATUS_FATAL = 1,             
	IRDETO_STATUS_ERROR = 2,             
	IRDETO_STATUS_WARNING = 3,           
	IRDETO_STATUS_INFO = 4,             
	IRDETO_STATUS_INFO_DND = 5          
} IRDETO_STATUS_SEVERITY_EN;

typedef enum
{
	CA_TXT_SHOW_NORMAL,
	CA_TXT_SHOW_TIMED,
	CA_TXT_SHOW_FORCED,

	CA_TXT_SHOW_MAX
}CA_TxtShowMode_E;

//error文本信息
typedef enum _BAKMSG_TEXT_EN
{
    MSG_TEXT000 = 0 ,          
    MSG_TEXT001 = 1 ,          
    MSG_TEXT002 = 2 ,          
    MSG_TEXT003 = 3 ,          
    MSG_TEXT004 = 4 ,          
    MSG_TEXT005 = 5 ,          
    MSG_TEXT006 = 6 ,          
    MSG_TEXT007 = 7 ,          
    MSG_TEXT008 = 8 ,          
    MSG_TEXT009 = 9 ,          
    MSG_TEXT010 = 10,          
    MSG_TEXT011 = 11 ,         
    MSG_TEXT012 = 12 ,         
    MSG_TEXT013 = 13 ,         
    MSG_TEXT014 = 14 ,         
    MSG_TEXT015 = 15 ,         
    MSG_TEXT016 = 16 ,         
    MSG_TEXT017 = 17 ,         
    MSG_TEXT018 = 18 ,         
    MSG_TEXT019 = 19 ,         
    MSG_TEXT020 = 20 ,         
    MSG_TEXT021 = 21 ,         
    MSG_TEXT022 = 22 ,         
    MSG_TEXT023 = 23 ,         
    MSG_TEXT024 = 24 ,         
    MSG_TEXT025 = 25 ,        
    MSG_TEXT026 = 26 ,      
    MSG_TEXT027 = 27 ,      
    MSG_TEXT028 = 28 ,      
    MSG_TEXT029 = 29 ,      
    MSG_TEXT030 = 30 ,      
    MSG_TEXT031 = 31 ,      
    MSG_TEXT032 = 32 ,      
    MSG_TEXT033 = 33 ,          
    MSG_TEXT034 = 34 ,          
    MSG_TEXT035 = 35 ,          
    MSG_TEXT036 = 36 ,          
    MSG_TEXT037 = 37 ,          
    MSG_TEXT038 = 38 ,          
    MSG_TEXT039 = 39 ,          
    MSG_TEXT040 = 40 ,          
    MSG_TEXT041 = 41 ,          
    MSG_TEXT042 = 42 ,          
    MSG_TEXT043 = 43 ,          
    MSG_TEXT044 = 44 ,          
    MSG_TEXT045 = 45 ,          
    MSG_TEXT046 = 46 ,          
    MSG_TEXT047 = 47 ,          
    MSG_TEXT048 = 48 ,          
    MSG_TEXT049 = 49 ,          
    MSG_TEXT050 = 50 ,          
    MSG_TEXT051 = 51 ,           
    MSG_TEXT052 = 52 ,           
    MSG_TEXT053 = 53 ,          
    MSG_TEXT054 = 54 ,          
    MSG_TEXT055 = 55 ,          
    MSG_TEXT056 = 56 ,          
    MSG_TEXT057 = 57 ,          
    MSG_TEXT058 = 58 ,          
    MSG_TEXT059 = 59 ,          
    MSG_TEXT060 = 60 ,          
    MSG_TEXT061 = 61 ,          
    MSG_TEXT062 = 62 ,          
    MSG_TEXT063 = 63 ,         
    MSG_TEXT064 = 64 ,         
    MSG_TEXT065 = 65 ,         
    MSG_TEXT066 = 66 ,         
    MSG_TEXT067 = 67 ,         
    MSG_TEXT068 = 68 ,         
    MSG_TEXT069 = 69 ,         
    MSG_TEXT070 = 70 ,         
    MSG_TEXT071 = 71 ,         
    MSG_TEXT072 = 72 ,         
    MSG_TEXT073 = 73 ,         
    MSG_TEXT074 = 74 ,         
    MSG_TEXT075 = 75 ,            
    MSG_TEXT076 = 76 ,            
    MSG_TEXT077 = 77 ,            
    MSG_TEXT078 = 78 ,            
    MSG_TEXT079 = 79 ,           
    MSG_TEXT080 = 80 ,           
    MSG_TEXT081 = 81 ,           
    MSG_TEXT082 = 82 ,           
    MSG_TEXT083 = 83 ,           
    MSG_TEXT084 = 84 ,           
    MSG_TEXT085 = 85 ,           
    MSG_TEXT086 = 86 ,           
    MSG_TEXT087 = 87 ,           
    MSG_TEXT088 = 88 ,           
    MSG_TEXT089 = 89 ,           
    MSG_TEXT090 = 90 ,           
    MSG_TEXT091 = 91 ,           
    MSG_TEXT092 = 92 ,           
#if 1                                  
    MSG_TEXT093 = 93 ,           
    MSG_TEXT094 = 94 ,           
    MSG_TEXT095 = 95 ,           
    MSG_TEXT096 = 96 ,           
    MSG_TEXT097 = 97 ,           
    MSG_TEXT098 = 98 ,           
    MSG_TEXT099 = 99 ,           
    MSG_TEXT100 = 100 ,          
    MSG_TEXT101 = 101 ,          
    MSG_TEXT102 = 102 ,          
    MSG_TEXT103 = 103 ,          
                    
    MSG_TEXT104 = 104 ,          

    MSG_TEXT105 = 105 ,          
    MSG_TEXT106 = 106 ,          
    MSG_TEXT107 = 107 ,          
    MSG_TEXT108 = 108 ,          
    MSG_TEXT109 = 109 ,          
    MSG_TEXT110 = 110 ,          
    MSG_TEXT111 = 111 ,          
    MSG_TEXT112 = 112 ,          
#endif
   
    MSG_TEXT113 = 113 ,         
    MSG_TEXT114 = 114 ,         


    MSG_TEXT115 = 115 ,            
    MSG_TEXT116 = 116 ,            
    MSG_TEXT117 = 117 ,          
    MSG_TEXT118 = 118 ,         
    MSG_TEXT119 = 119 ,         
    MSG_TEXT120 = 120 ,         
    MSG_TEXT121 = 121 ,         
    MSG_TEXT122 = 122 ,         
    MSG_TEXT123 = 123 ,         
    MSG_TEXT124 = 124 ,         
    MSG_TEXT125 = 125 ,         
    MSG_TEXT126 = 126 ,         
    MSG_TEXT127 = 127 ,         
    MSG_TEXT128 = 128 ,         
    MSG_TEXT129 = 129 ,         
    MSG_TEXT130 = 130 ,         
    MSG_TEXT131 = 131 ,         
    MSG_TEXT132 = 132 ,         
    MSG_TEXT133 = 133 ,         
    MSG_TEXT134 = 134 ,         
    MSG_TEXT135 = 135 ,         
    MSG_TEXT136 = 136 ,         
    MSG_TEXT137 = 137 ,         
    MSG_TEXT138 = 138 ,         
    MSG_TEXT139 = 139 ,         
    MSG_TEXT140 = 140 ,         
    MSG_TEXT141 = 141 ,         


    MSG_TEXT142 = 142 ,          
    MSG_TEXT143 = 143 ,          
    MSG_TEXT144 = 144 ,          
    MSG_TEXT145 = 145 ,          
    

    MSG_TEXT146 = 146 ,       
    MSG_TEXT147 = 147 ,       
    MSG_TEXT148 = 148 ,       


    MSG_TEXT149 = 149 ,          
    MSG_TEXT150 = 150 ,          
    MSG_TEXT151 = 151 ,          
    MSG_TEXT152 = 152 ,          
    MSG_TEXT153 = 153 ,          
    MSG_TEXT154 = 154 ,          
    MSG_TEXT155 = 155 ,          
    MSG_TEXT156 = 156 ,          

    MSG_TEXTMAX
}IRDETO_BAKMSG_TEXT_EN;

//主界面需要显示的status
typedef enum _MENU_STATUS_EN
{
	CA_MENU_SOFTCELL_STATUS,
	CA_MENU_SMARTCARD_STATUS,
	CA_MENU_DVBSERVICE_STATUS,
	CA_MENU_SERVICEINDEX_STATUS,
	CA_MENU_EMM_SERVICE_STATUS, 
	CA_MENU_DES_SERVICE_STATUS,
	CA_MENU_LOADER_STATUS,
	CA_MENU_COMPONENTS_STATUS,
	CA_MENU_PRODUCTLIST_STATUS,
	CA_MENU_MR_CARD_STATUS,
	CA_MENU_MAX_DATA
}IRDETO_MENU_STATUS_EN;



//错误类型
typedef enum _CAEEVENTGROUP_EN
{
	ALARM_IRD3_MSG,
	INFO_IRD3_MSG,
	COMMAND_IRD3_MSG,
	STATUS_IRD3_MSG
}IRDETO_CAEEVENTGROUP_EN;

//Status 信息
typedef enum _CASTATUS_EN
{
	STATUS_OTA_OK,        
	STATUS_OTA_STATUS,    
	STATUS_OTA_FAILURE,   
	STATUS_SMC_IN,		
	STATUS_SMC_OUT,		
	STATUS_SMC_ERROR		
	
}IRDETO_CASTATUS_EN;

//Irdeto Infor 消息
typedef enum _CAINFO_EN
{
	INFO_SOFTCELL_STATUS = 0, 
	INFO_SC_STATUS,           
	INFO_MONI_EMM_STATUS = 2, 
	INFO_MONI_DES_STATUS ,   
	INFO_SRC_EMM_STATUS = 4, 
	INFO_SRC_ECM_STATUS ,    
    INFO_COMPONENTS_STATUS = 6,
    INFO_SC_PINCODECHANGE_STATUS,
    INFO_SC_PINCODCHECK_STATUS = 8,
    INFO_REMOTECHANNEL_STATUS,   
	INFO_IRD_STATUS = 10,     
	INFO_IRD_LOADER_STATUS,       
	INFO_MEMORY_ERROR = 12,   
	INFO_SC_NUMSECTOR_STATUS, 
	INFO_CAREGION_STATUS = 14,
	INFO_SCUSERDATA_STATUS ,  
	INFO_EMM_USERLOAD_STATUS = 16, 
	INFO_DVBSERVICE_STATUS , 
	INFO_MAIL = 18,  
	INFO_PRODUCTLIST_STATUS,
	INFO_MR_CARD_STATUS = 20,  
	INFO_MR_USERPROFILE_DATA,
	INFO_MAXS
}IRDETO_CAINFO_EN;

//command 消息
typedef enum _CACOMMAND_EN
{
	COMMAND_FINGER_PRINT = 0,
	COMMAND_HOMECHANNEL_SET, 
	COMMAND_HOMECHANNEL_SCANS = 2,
	COMMAND_APP_HOMECHANNEL_SCANS,
	COMMAND_RESET_CHANNEL = 4,        
	COMMAND_RECONNECT_CURRENT_SERVICES,
	COMMAND_REBOOTS = 6,               
	COMMAND_TUNE_SERVICE,             
	COMMAND_CHANGE_PGPIN = 8,         
	COMMAND_CHANGE_INSTALLPIN,        
	COMMAND_EMM_OTAS = 10,             
	COMMAND_OTA_NEXTS,                 
	COMMAND_OTA_DETECTS = 12,          
	COMMAND_ATTRIBS,                   
	COMMAND_SURFLOCK = 14,    
	COMMAND_MRPIN,
	COMMAND_MAXS	
}IRDETO_CACOMMAND_EN;

//邮件类型
typedef enum _TXTTYPE_ST
{
	CA_TXT_MAIL         	= 0,
	CA_TXT_ANNOUNCE     	= 1,
	CA_TXT_CLUB         	= 2 
}IRDETO_TXTTYPE_ST;

//OTA检测错误类型
typedef enum _OTAERROR_E    
{
	CA_OTA_ERROR_1,
	CA_OTA_ERROR_2
}OTAERROR_E;

typedef struct 
{
	unsigned char m_aucPPGPIN[16];
	unsigned int  m_unLen;
}MSG_PGPIN_S;

//TMS类型
typedef enum _TMSTYPE_EN
{
	CA_TMS_NORMALMAIL ,   
	CA_TMS_FORCEDMAIL ,   
	CA_TMS_FINGERPRT ,    
	CA_TMS_MAXTYPE  
}IRDETO_TMSTYPE_EN;

//ES 类型
typedef enum _ESCURRENTTYPE_E
{
	CA_ES_IRDETO , 
	CA_ES_OTHER ,  
	CA_ES_FREE,    
	CA_ES_MAX
}ESCURRENTTYPE_E;

//Service类型EMM or Descrambler
typedef enum _SERVICETYPE_EN
{
    SERVICE_EMM , 
    SERVICE_DES , 
    SERVICE_MAX
}IRDETO_SERVICETYPE_EN;

//关闭音视频类型
typedef enum 
{
    EM_CA_SHUT_BOTH_AV, 
    EM_CA_SHUT_AUDIO,  
    EM_CA_SHUT_VIDEO   
}E_CaCompLevelType;

//重启类型
typedef enum 
{
	EM_IRDETO_REBOOTOTA = 0 ,   
	EM_IRDETO_REBOOTEMM ,   
	EM_IRDETO_REBOOTTYPEMAX  
}RebootType_E;

//日期类型结构体
typedef struct _CADATETIME_ST
{
	unsigned int   	 m_dwYear;
	unsigned char    m_cMonty;
	unsigned char    m_cDay; 
	unsigned char    m_cHour; 
	unsigned char    m_cMinute;
	unsigned char    m_cSecond;
}IRDETO_CADATETIME_ST;

//错误消息提示结构体
typedef struct _ServiceInfo_S
{
	unsigned char    m_bSeverity;
	unsigned short    m_wStatus;
	unsigned char    m_bSource;
	unsigned short    m_wTextnum;
} ServiceInfo_S;

typedef struct _Error_Info_S
{
    unsigned int   m_wServiceHandle;
	unsigned char    m_bSeverity;
	unsigned short    m_wStatus;
	unsigned char    m_bSource;
    unsigned short    m_wTextnum;	
}Error_Info_S;

//卡信息结构体
typedef struct _SMARTCARDSTATUS_S
{
    ServiceInfo_S m_stScStatus;
    unsigned char    m_szScNumber[SC_NUMBER_LEN];
    unsigned char    m_szScType[SC_TYPE_LEN];
    unsigned char    m_szScVer[SC_VER_LEN];
    unsigned char    m_szNationality[SC_NATION_LEN];
    unsigned short   m_wPatchLevel;
    unsigned short   m_wOwnerId;
    unsigned char    m_bVariant;
    unsigned char    m_bBuild;
}SMARTCARDSTATUS_S;
typedef enum
{
	SMC_OUT,
	SMC_IN,
	SC_ERROR
}IrdetoSCStatus_E;
typedef enum
{
	IR_EMAIL_ARRIV_DESC,
	IR_EMAIL_ARRIV_ASC

}IrdetoMailSort_E;

//邮件内容属性结构体
typedef struct _CAMSG_S
{
	unsigned char    	 m_cType; 
	unsigned char    	 m_cClass;
	unsigned char    	 m_cPriority;
	unsigned int   		 m_dwLen; 
	IRDETO_CADATETIME_ST m_stDeleteTime; 	
	unsigned char    	 m_szContent[CA_MAX_SIZE_TXT_MAIL];
    unsigned short       m_wDuration;
    unsigned char        m_bCoverPer;
}CAMSG_S;

//邮件结构体
typedef struct _CA_MAIL_S		
{	
	ADI_BOOL   			  m_bReadFlag;
	ADI_BOOL   			  m_bLockFlag;
	IRDETO_CADATETIME_ST  m_stArriveTime; 
	CAMSG_S 	  m_stMsg; 
}CAMailMSG_S;

//当前OTA状态结构体
typedef struct _OTASTATUS_S 
{
	unsigned char    m_cStep;	
	unsigned char    m_cTimeLeft;
}OTASTATUS_S;


typedef struct _COMPONSTAUT_INFO_ST
{
    unsigned char    m_bMajor;
    unsigned char    m_bMinor;
    unsigned int     m_uSubVersion;
	unsigned char	 m_szComponName[CPNT_STATUS_NAME_LEN];	
	unsigned char	 m_szComponDate[CPNT_STATUS_DATE_LEN];	
    unsigned char	 m_szComponVersion[CPNT_STATUS_VERSION_LEN];	
}IRDETO_COMPONSTAUT_INFO_ST;

typedef struct _COMPONSTAUTS_ST
{
	unsigned char			   m_bTotalComponItem;
	IRDETO_COMPONSTAUT_INFO_ST m_szComponts[MAX_CPNT];	
}IRDETO_COMPONSTAUTS_ST;

typedef struct _CASTATUS_S
{
	unsigned char	m_bMajor;
	unsigned char	m_bMinor;
	unsigned int    m_uSubVersion; 
	char			m_acNameString[CPNT_STATUS_NAME_LEN];
	char			m_acBuildInfoString[CPNT_STATUS_DATE_LEN]; 
	char			m_acCaTaskVerString[CPNT_STATUS_VERSION_LEN];
}CASTATUS_S;

//EMM状态信息界面
typedef struct _EMMSRVSTATUS_S
{
	unsigned int          	  m_wEmmHandle; 
	unsigned short            m_wServiceHandle; 
	ServiceInfo_S   	  m_stGlobalStatus; 
	ServiceInfo_S   	  m_stServiceStatus;
	unsigned short            m_wEmmPid; 
	ADI_BOOL				  m_fEmmServiceDefine;
	unsigned char			  m_bRscCount;
	unsigned int         	  m_awRscType[MAX_SERVICE_RESOURCES];
	ServiceInfo_S 	  m_stRscStatus[MAX_SERVICE_RESOURCES];
    unsigned char             m_acEmmString[MAX_SRC_EMM_MONITOR_LEN];
    unsigned int         	  m_dwEmmResourceID; 
}EMMSRVSTATUS_S;

//ECM节目status界面状态信息
typedef struct _DESSRVSTATUS_S
{
	unsigned int			m_wGroupHandle;
	unsigned int			m_wServiceHandle;
	unsigned int			m_wServiceType;
	ServiceInfo_S    m_stGlobalStatus;
	ServiceInfo_S    m_stServiceStatus;
	unsigned char			m_bStreamCount;
    unsigned short    	    m_wStrInfoStreamPid[MAX_ECMSERVICE_STREAMS];
    unsigned short    		m_wStrInfoEcmPid[MAX_ECMSERVICE_STREAMS];
	ServiceInfo_S   	 m_stStrInfoStatus[MAX_ECMSERVICE_STREAMS];
	unsigned char			m_bRscCount;
	unsigned short      	m_awRscType[MAX_SERVICE_RESOURCES];
	ServiceInfo_S   	 m_stRscStatus[MAX_SERVICE_RESOURCES];
    unsigned char			m_abEcmData[MAX_SRC_ECM_MONITOR_LEN];
    unsigned short      	m_abEcmMonitorCount;
    unsigned int      		m_dwEcmResourceID; 
}DESSRVSTATUS_S;

//emm数据
typedef struct _MONIEMMSTATUS_S
{
	unsigned int       m_wEmmHandle;
	unsigned short     m_wServiceHandle;
	unsigned char      m_acEmmString[MAX_SRC_EMM_MONITOR_LEN];
}MONIEMMSTATUS_S;

//emm数据更新
typedef struct _MONIDESSTATUS_S
{
	unsigned int       m_wGroupHandle;
	unsigned short     m_wServiceHandle;
	unsigned short     m_wEcmPid;
	unsigned char      m_abEcmData[MAX_SRC_ECM_MONITOR_LEN];
}MONIDESSTATUS_S;


typedef struct _DATETIME_ST
{
    unsigned char    m_bYear;
    unsigned char    m_bMonth;
    unsigned char    m_bDate;
    unsigned char    m_bHour;
    unsigned char    m_bMintue;
    unsigned char    m_bSecond;
}IRDETO_DATETIME_ST;

typedef struct _CAFINGERPRINT_ST  
{
	unsigned char    	m_cInfoNo;     	
	int     			m_nOvertime;  	
	unsigned char    	m_acMsg[CA_MAX_SIZE_FINGERPRINT]; 
}IRDETO_CAFINGERPRINT_ST;

typedef struct _CACOVERTFINGERPRINT_S 
{
	unsigned char    	m_cInfoNo;     	
	unsigned short     	m_wDuration;  	
	ADI_BOOL        	m_bFlash;       
    ADI_BOOL        	m_bBanner;      
    unsigned char       m_bCoverPer;    
    ADI_BOOL        	m_bCovert;      
	unsigned char    	m_acMsg[CA_MAX_SIZE_FINGERPRINT]; 
	
	unsigned int		m_ucLocationX;	
    unsigned int		m_ucLocationY;  
    unsigned char       m_ucBgTransAlpha; 
    unsigned int	    m_dwBgColour;		
    unsigned char       m_ucFontTransAlpha; 
    unsigned int	    m_dwFontColour;	  
    unsigned char		m_ucFontType;	  

}CACOVERTFINGERPRINT_S;

//EMM OTA类型
typedef struct _CAEMMOTA_S
{
	ADI_BOOL    m_bDownLoadAllowed; 
	ADI_BOOL    m_bForced; 
}CAEMMOTA_S;


//Irdeto Loader status 界面信息
typedef struct _LOADERSTATUS_S
 {
    unsigned char        m_bManufacturerId;
    unsigned char        m_bHardwareVersion;
    unsigned short       m_bVariant;

    unsigned short       m_wSystemId;
    unsigned short       m_wKeyVersion;
    unsigned short       m_wSignatureVersion;

    unsigned int         m_dLdSECSSN;

    unsigned short        m_usDownLoadID;

    unsigned char        m_bFirmVersion[CA_MAX_SIZE_FIRMWARE];

    unsigned char        m_bLoadVersion[CA_MAX_SIZE_LOASER];

    unsigned char        m_bSerialNO[CA_MAX_SIZE_IRD_SERIALNUMBER];

    unsigned short       m_wSpecInfo;
    IRDETO_DATETIME_ST 	 m_stSignDateTime;
    IRDETO_DATETIME_ST 	 m_stDownloadDateTime;
    
}LOADERSTATUS_S;

//远程控制
typedef struct _REMOTECHANNEL_S
{
	unsigned int       	 m_wResourceId;
	unsigned char        m_bPayloadLengthMax;
	unsigned char       *pbPayload; 
}REMOTECHANNEL_S;
 
//sc 的sector数目
typedef struct _SCNUMBEROFSECTOR_S
{
    unsigned int         m_wResourceId;
    unsigned char        m_bsectorCount;
    unsigned char        m_bSector[MAX_SC_NUMSECTOR_SIZE];
    unsigned char        m_bActive[MAX_SC_NUMSECTOR_SIZE];
    unsigned char        m_bReserverd[MAX_SC_NUMSECTOR_SIZE];
}SCNUMBEROFSECTOR_S;

//区域化操作
typedef struct _CAREGION_S
{
	unsigned int       	m_wResourceId;
	unsigned char       m_bRequestType;
	unsigned char		m_bSector;
	unsigned char		m_bSectorStatus;
	unsigned char		m_bRegion;
	unsigned char		m_bSubRegion;
}CAREGION_S;

//卡userdata区域数据
typedef struct _SCUSERDATA_S
{
	unsigned int     	 m_wResourceId;
	unsigned char        m_abUserData[MAX_SC_USERINFO_LEN]; 
}SCUSERDATA_S;

//suflock信息结构体
typedef struct _SurfLock_S
{
	unsigned char      m_bRequestType;
	unsigned int       m_wResourceId;
	ADI_BOOL           m_fSurfLocked;
	unsigned int       m_wGroupHandle;
} SurfLock_S;

//emm user data结构体
typedef struct _EMMUSERPAYLOAD_S
{
	unsigned int           m_wEmmHandle; 
	unsigned short         m_wMessageLength; 
	unsigned char          m_abMsgData[MAX_EMM_USERLOAD_LEN]; 
} EMMUSERPAYLOAD_S;

//cover指纹结构体
typedef struct _ATTRIBCOVERT_S
{
	unsigned char      m_bIndex; 
	unsigned int       m_wEmmHandle; 
	unsigned short     m_wServiceHandle; 
	unsigned short     m_wMsgLength;  
	unsigned char      m_bMessageData[MAX_ATTRIBDATA_LEN]; 
	IRDETO_TMSTYPE_EN  m_bType; 
	ADI_BOOL       	   m_bFlash;	  
    ADI_BOOL           m_bBanner;    
    unsigned char      m_bCoverPer; 
	unsigned short     m_wDuration; 
	ADI_BOOL       	   m_bCovert;   
	unsigned int	   m_ucLocationX;	 
   	unsigned int	   m_ucLocationY;   
    unsigned char      m_ucBgTransAlpha; 
    unsigned int	   m_dwBgColour;	 
    unsigned char      m_ucFontTransAlpha;  
    unsigned int	   m_dwFontColour;	   
    unsigned char	   m_ucFontType;	   

}ATTRIBCOVERT_S;

//强制跳转某一节目三要素信息
typedef struct _SwitchTSInfo_S
{
	unsigned int       	  m_wGroupHandle; 
	unsigned short        m_wNetworkID; 
	unsigned short        m_wTransportStreamID; 
	unsigned short        m_wServiceID; 
}SwitchTSInfo_S;


//当前所有的业务状态信息，emm和节目 
typedef struct _DVBDESCRABLE_INFO_ST
{
    unsigned int  		 	m_dwClientHandle; 
    unsigned short    	 	m_wIndex; 
    IRDETO_SERVICETYPE_EN   m_eServiceType; 
    unsigned char   		m_bInstance;  
}IRDETO_DVBDESCRABLE_INFO_ST;


typedef struct
{
    unsigned char   			m_bServiceCount; 
    IRDETO_DVBDESCRABLE_INFO_ST m_sSrvInfo[CA_DEMUX_MAX+CA_SRV_MAX];
}DVBDESCRABLE_S;


 //国家码结构体
typedef struct _COUNTRYBL0CK_INFO_ST
{
	unsigned char    m_cFlag;        
	unsigned char    m_acCountry[3]; 
}IRDETO_COUNTRY_INFO_ST;

 //国家码列表
typedef struct _CountryCodeList_S
{
    unsigned short   		m_wCountryNum;     
	IRDETO_COUNTRY_INFO_ST  m_acCountryList[CA_MAX_COUNTRY_NUM];  
}CountryCodeList_S;

//IrdetoCA 配置信息
typedef struct _CaConfig
{      			
	ADI_BOOL     			m_bIsReverseCard;         
	unsigned int    		m_unProtocol;              
	
	ADI_BOOL	 			m_bIsFTABlock;    		
	unsigned int	 		m_dwOwnerID;				
	ADI_BOOL	 			m_bIsEOF;    				
	ADI_BOOL	 			m_bIsSOL;					
		
}CaConfig_S;
typedef struct 
{
    unsigned char m_ucSectorID;
	unsigned int  m_uSectorStarCode;
    unsigned short m_usProductId;
    unsigned int m_uProductStartDate;
    unsigned char m_ucduration;
}Ird3ProductInfo_S;


typedef struct 
{
    unsigned short m_wProductCount;
    Ird3ProductInfo_S m_stProductInfo[CA_MAX_PRODUCT_COUNT];
}Ird3ProductList_S;
typedef struct
{
	unsigned int m_unPinIndex;
	unsigned char m_aucPin[16];
	unsigned int m_unPinLen;

}Ird3Pin_S;
typedef enum
{
	EM_MR_CONFIG_OK			= 0,
	EM_MR_CONFIG_CARD_ERROR,    
	EM_MR_CONFIG_CARD_MR_INCAPABLE,
	EM_MR_CONFIG_PIN_WRONG,
	EM_MR_CONFIG_PIN_BLOCK,
	EM_MR_CONFIG_DISABLE_MR_NOT_ALLOWED
} E_MrResult;
typedef enum 
{ EM_MR_USER_PROFILE_OK,
  EM_MR_USER_PROFILE_CARD_ERROR,
  EM_MR_USER_PROFILE_CARD_MR_INCAPABLE,
  EM_MR_USER_PROFILE_SUBSCRIBER_PIN_WRONG,
  EM_MR_USER_PROFILE_SUBSCRIBER_PIN_BLOCK,
  EM_MR_USER_PROFILE_UPDATE_NOT_ALLOWED,
  EM_MR_USER_PROFILE_USER_ID_OUT_OF_RANGE,
  EM_MR_USER_PROFILE_USER_NOT_EXIST, 
  EM_MR_USER_PROFILE_USER_AGE_OUT_OF_RANGE
 } E_user_profile_Result;

typedef struct 
{ 
	ServiceInfo_S    m_sCardStatus;
	ADI_BOOL  m_bCapablity; 
	ADI_BOOL  m_bEnable; 
	E_MrResult  m_eMRResult;
}MrCardInfo_S;

typedef struct
{
	unsigned char m_ucProID;
	unsigned char m_ucAge;
	unsigned char m_aucPin[ 2 ];
	E_user_profile_Result  m_eResult;  
	
}MrUserProInfo_S;
typedef struct 
{ 
  unsigned int  m_dwGroupHdl; 
  unsigned int  m_dwSrvType; 
  unsigned char m_aucPin[2];
  unsigned int  m_dwResId;
}MrPin_S;
typedef struct
{ 
	unsigned char m_aucPin[ 2 ]; 
	ADI_BOOL m_bEnable;
}MrConInfo_S;

typedef enum
{
	EM_MR_USER_PROFILE_READ = 0,
	EM_MR_USER_PROFILE_SET,     
	EM_MR_USER_PROFILE_DELETE   
	
}E_MrProInfoAction;

typedef struct 
{ 
	unsigned char  m_aucMastPin[ 2 ]; 
	E_MrProInfoAction  m_eProfileAction;  
	MrUserProInfo_S  m_stUserProfile;
 
}MrProInfo_S;



//获取卡国家码接口
int ADI_CA_GetCountryCode(unsigned char * pucBuf, unsigned int unLen);
//获取卡的状态信息
IrdetoSCStatus_E ADI_Irdeto_CheckCardStatus(void);



/*

邮件相关的函数
*/

int ADI_SetPrivateConfig(ADI_BOOL bRepeatSave,unsigned int unMaxMailNum);

int ADI_CA_Mail_Del(unsigned int dwIndex);
int ADI_CA_Mail_DelAll(void);
int ADI_CA_Mail_GetNum(void);
int ADI_CA_Mail_GetInfo(unsigned int dwIndex, CAMailMSG_S** ppstTxt);
ADI_BOOL ADI_CA_Mail_HaveNew(IRDETO_TXTTYPE_ST eType);
int ADI_CA_Mail_Save(void);
int ADI_CA_Mail_SetReadFlag(unsigned int dwIndex, ADI_BOOL bRead);
int  ADI_CA_Mail_SetLockFalg(unsigned int dwIndex, ADI_BOOL bLockFlag);
int  ADI_CA_Mail_GetLockFalg(unsigned int dwIndex, ADI_BOOL* pbLockFlag);
void ADI_CA_GetFlashMailAddress(unsigned int* pFlashMailAddr, unsigned int* pFlashMailSize);
int ADI_Irdeto_SetMailSort(IrdetoMailSort_E emStyle);
ADI_BOOL ADI_CA_GetSoftcellVerInfo(unsigned char *pucVerStrBuf, unsigned int unVerStrLen);

/*
	OTA功能相关的模块函数
*/
void ADI_CA_OTA_GetTunerParm(void);
void ADI_CA_OTA_GetUpdateInfo(void);
int  ADI_CA_OTA_SaveCfg(ADIBLOtaLoaderPt_S* pstOtaCfg);
unsigned short ADI_CA_GetOtaSrvID(void);

//=========================================================================================
//==============================IRDETOV5 OTA模块相关的函数=================================
//=========================================================================================
// 应用调用此接口获取OTA的频点参数	<<<APP调用接口>>>
// 当用户在菜单启动OTA或者收到COMMAND_EMM_OTA强制消息时调用
// 此接口异步实现如果获取频点成功会收到消息COMMAND_OTA_NEXT, 获取失败会收到消息CA_STATUS_OTA_FAILURE
void ADIIrdetoV5OTA_RequestTunerParamAsync(void);

// 应用调用此接口获取OTA所需的PID等完整参数  <<<APP调用接口>>>
// app收到COMMAND_OTA_NEXT消息锁频后调用此接口获取DownloadPID
// 此接口异步实现如果获取成功会收到消息CA_STATUS_OTA_OK, 获取失败会收到消息CA_STATUS_OTA_FAILURE
void ADIIrdetoV5OTA_RequestDownloadPIDAsync(void);

// 应用调用此接口保存LoaderPt并重启进OTA升级  <<<APP调用接口>>>
// App收到CA_STATUS_OTA_OK消息后,如果用户选择进loader启动OTA, 就调用此接口保存Loaderpt并重启
void ADIIrdetoV5OTA_SaveLrdptReboot(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt);

// 应用调用此接口中途取消OTA  <<<APP调用接口>>>
void ADIIrdetoV5OTA_Cancel(void);
//=========================================================================================
//=========================================================================================

/*
界面菜单相关函数
*/
int ADI_CA_EnterIrdetoMenu( IRDETO_MENU_STATUS_EN enumQueryDataType, unsigned int dwParam );
int ADI_CA_ExitIrdetoMenu( IRDETO_MENU_STATUS_EN enumQueryDataType );
int ADI_CA_AlarmMsg_SetCountryBlock (CountryCodeList_S* pstCountypList);

/*
界面菜单相关的一些函数
*/
int ADICAGetNvrmBackUpAddress(unsigned int * dwBackFlashAddr, unsigned int * dwBackFlashNVMSize);
void ADICAGetNvrmAddress(unsigned int* pFlashNVMAddr, unsigned int* pFlashNVMSize);
unsigned int ADI_CA_FAKE_NVM_EraseAllFlash(void);
/*
	指纹相关的函数
*/
//最多支持10种颜色指纹
void ADI_Irdeto_ConfigFingerColor(unsigned int *punColor,unsigned int unColorCnt);


/*
消息相关的函数
*/

int  ADI_CA_SetCardMrStatus (MrConInfo_S  *psMrConfigureInfo);
int  ADI_CA_MrProfileAction (MrProInfo_S  *pstMrProfile);
int  ADI_CA_VerifyMrPIN (MrPin_S  *pstPinInfo);
int ADI_Irdeto_GetSCNum(unsigned int nScIndex, unsigned char *pucBuffer, unsigned int unBufferLen);

ESCURRENTTYPE_E ADI_IRDETO3_GetSrvType(int nIndex);

extern unsigned int Get32Font(void);
extern void GetNetWorkTime(ADIOSSysTime_S *pTime);
int ADI_CA_SetFalseEncrypt(ADI_BOOL bSet);


#ifdef  __cplusplus
}
#endif

#endif 
