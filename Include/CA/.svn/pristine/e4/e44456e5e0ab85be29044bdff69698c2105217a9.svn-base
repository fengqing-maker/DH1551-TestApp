/****************************************************************************** 
* FileName : ADI_Viac_Interface.h
* Author:      Steve.hou
* Date:         2015.5.5
* Description: Viacess CA interface file for app integration  using,
*            
*******************************************************************************/

/*******************************************************************************
* 			                                  Revision History                                				     *
********************************************************************************
*01.01: Creat Viacess ca porting head file    author Steve.hou @2015.5.5
*******************************************************************************/
#include "adi_typedef.h"
#include "adi_tuner.h"
#include "adi_os.h"
#include "adi_screen.h"

#ifndef _ADI_VIAC_INTERFACE_H_
#define _ADI_VIAC_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_NULL 	(0)
#define CA_SRV_MAX (3)

typedef enum
{
	Encoding_ASCII		   = 0,
	Encoding_UTF_8		   = 1,
	Encoding_UTF_16 	   = 2,
	Encoding_UTF_32 	   = 3,
	Encoding__GB2312_80    = 4
} Encoding_E;
typedef struct 
{
    unsigned short m_wYear;
    unsigned char m_ucMonth;
    unsigned char m_ucDay;
    unsigned char m_ucHour;
    unsigned char m_ucMinute;
    unsigned char m_ucSecond;
}Viac_DateTime_S;

typedef struct 
{ 
	Encoding_E	  m_eEnCoding; 
	unsigned int  m_unSoid;
	ADI_BOOL	  m_bHighPriority;
	unsigned char m_aucContent[1024+2];
	unsigned int  m_unTxtLen;
}ViacMailContent_S;


typedef struct		
{
    ADI_BOOL  m_bReadFlag;
    Viac_DateTime_S m_stArriveTime;
    ViacMailContent_S m_stMail;
} ViacMail_S;
typedef enum
{
	IPPV_NO_PROG,
	IPPV_IPPV_T,
	IPPV_IPPV_P,
}E_IPPVMODE;
typedef enum
{
    POST_PAYMENT_MODE,               
    PRE_PAYMENT_MODE,                
    UNKNOWN_PAYMENT_MODE             

} UI_PaymentMode;
typedef struct
{
    ADI_BOOL bIsPreviewPresent;  
    unsigned char   uiPreviewIndex;                                         
    unsigned short      uiPreviewNumber;                                        
    unsigned char       uiMaxCwNumber;                                        

} PreviewInfo_S;
typedef struct
{
	unsigned int    m_unPnumIppvP; 
	float           m_fIPPVPrice;
	unsigned char   m_ucIPPVPrice[64];       
}IppvPrice_S;
typedef struct
{
    unsigned int    m_unPnumIppvPt;            
    unsigned char   m_ucIPPVtPrice[64];
	float           m_fIPPVTPrice; 
	float           m_fIPPVTCeilPrice; 	
}IppvtPrice_S;

typedef struct
{
	
	unsigned char  m_unAcsID;
	ADI_HANDLE     m_hIPPVHdl;
	unsigned int   m_unSoid;
	unsigned char  m_ucRemainCredit[64];
	E_IPPVMODE     m_eIPPVMode;
	UI_PaymentMode m_ePayMentMode;
	unsigned int   m_unProgramNumber;
	IppvPrice_S    m_sIppvPrice;
	IppvtPrice_S   m_sIppvtPrice;	
}IPPVReq_S;

typedef struct 
{
	ADI_BOOL m_bSPDIFEnable;
	ADI_BOOL m_bEthernetEnable;
	ADI_BOOL m_bUSBEnable;
	ADI_BOOL m_bILinkEnable;
	ADI_BOOL m_bHddEnable;
	ADI_BOOL m_bDvdEnable;
}DigitalOut_S;


typedef struct 
{
	ADI_BOOL m_bActivedMacro;
	ADISCREENCopyControlMode_E  m_eCGMSCopyControlMode;
	ADI_BOOL m_bActivedDTCP_IP;
	ADISCREENCopyControlMode_E  m_eDTCP_IPCopyControlMode;		
}CopyControlInfo_S;

typedef enum
{
	MSG_ALARM_VIAC,
	MSG_COMMAND_VIAC,
	MSG_STATUS_VIAC
}MSG_VIAC_TYPE;

typedef enum
{
	VIAC_CMD_COPYPROTECT,
	VIAC_CMD_DIGITALPROTECT,
	VIAC_CMD_PROGPGLEVEL,
	VIAC_CMD_FPSHOW,
	VIAC_CMD_FPHIDE,
	VIAC_CMD_PAUSEFTA,
	VIAC_CMD_RESUMEFTA,
	VIAC_CMD_CHECKPCPIN,
	VIAC_CMD_CHECKPPVPIN,	
	VIAC_CMD_SECURITY,
	VIAC_CMD_PAIRING,
	VIAC_CMD_FORBIDDEN_SOID_LIST,
	VIAC_CMD_DETECTION_CONFIG,
	VIAC_CMD_SOID_LIST,
	VIAC_CMD_SOID_LABEL,
	VIAC_CMD_ATTEMPT_PINCODE,
	VIAC_CMD_PPVVIEW_PROGRESS,
	VIAC_CMD_SUBLIST_CLASS,
	VIAC_CMD_SUBLIST_THEME,
	VIAC_CMD_PPVP_LIST,
	VIAC_CMD_PPVT_LIST,
	VIAC_CMD_STB_ID,
	VIAC_CMD_PREBOOKLIST,
	VIAC_CMD_CAVERSION,
	VIAC_CMD_SC_INFO,
	VIAC_CMD_EXIT_ID,
	VIAC_CMD_CAMLOCK_VALUE,
	VIAC_CMD_PAIRING_MODE,
	VIAC_CMD_CARD_PAIRING_NUM,
	VIAC_CMD_CARD_PAIRD_LIST,
	VIAC_CMD_PG_LEVEL,
	VIAC_CMD_PG_REQ,
	VIAC_CMD_PPV_CREDIT,
	VIAC_CMD_THRESHOLD,
	VIAC_CMD_PRESELECTLIST,
	VIAC_CMD_CA_VERSION_DETAIL,
	VIAC_CMD_OPERATOR_MSG,
	VIAC_CMD_OPERATOR_TEL,
	VIAC_CMD_OPERATOR_CALLING_PRICE,
	VIAC_CMD_OPERATOR_WEB,
	
	VIAC_CMD_PREVIEW_OK,
	VIAC_CMD_PREVIEW_AND_IPPV_OFFER_OK,
	VIAC_CMD_IPPV_PROGRAM,
	VIAC_CMD_MAX
}VIACCommandMsg_S;
typedef enum 
{
	VIAC_STA_OK,
	VIAC_STA_CARD_OK,
	VIAC_STA_CARDIN,
	VIAC_STA_CARDOUT,
	VIAC_STA_CARDERROR,
	VIAC_STA_WRONGSLOT,
	VIAC_STA_WRONG_MODE,
	VIAC_STA_CARD_COM_ERROR,
	VIAC_STA_ARRY_TOO_SMALL,
	VIAC_STA_BAD_PIN,
	VIAC_STA_LOCK_PIN,
	VIAC_STA_CHANGE_PIN,
	VIAC_STA_FORBIDDEN_PIN,
	VIAC_STA_NO_PINCODE,
	VIAC_STA_INVALID_PG_LEVEL,
	VIAC_STA_MEMORY_NO_ENOUGH,
	VIAC_STA_NO_CARD,
	VIAC_STA_BAD_SOID,
	VIAC_STA_INVALID_OPERATION,
	VIAC_STA_PRESELECTION_FULL,
	VIAC_STA_REFERENCE_ALREADY_STORED_IN_PRESELECTION_AREA,
	VIAC_STA_REFERENCE_NOT_FOUND_IN_PRESELECTION_AREA,
	VIAC_STA_PRESELECTION_MODE_NOT_ACCEPTED,
	VIAC_STA_CONSULTATION_LOCKED_ACCEPTED,
	VIAC_STA_WRONG_HANDLE,
	VIAC_STA_NO_IPPV_OFFER_AVAILABLE,
	VIAC_STA_ITEM_FOUND,
	VIAC_STA_NO_ITEM_FOUND,
	VIAC_STA_INSUFFICIENT_MEMORY,
	VIAC_STA_INFO_NOT_AVAILABLE,
	VIAC_STA_BAD_ACS_ID,
	VIAC_STA_RESOURCE_BUSY,
	VIAC_STA_OPERATING_ERROR,
	VIAC_STA_MODE_NOT_SETUP,
	VIAC_STA_BAD_MODE,
	VIAC_STA_NO_STB_ID,
	VIAC_STA_PVR_NO_RIGHT,
	VIAC_STA_CONNECTION_ERROR,
	VIAC_STA_WRONG_ACTIVATION_ERROR,
	VIAC_STA_ACTIVATION_ERROR,
	VIAC_STA_TERMINAL_NOT_ACTIVATED,
	VIAC_STA_TERMINAL_LOCKED,
	VIAC_STA_ENTILE_UPDATE,
	VIAC_STA_ERROR,
	VIAC_STA_MAX
}VIACStatusMsg_E;

typedef enum
{
	VIAC_ALA_VIAC,
	VIAC_ALA_OTHER,
	VIAC_ALA_FTA,
	VIAC_ALA_SC_IN,
	VIAC_ALA_SC_OUT =4,
	VIAC_ALA_SC_OK,					
	VIAC_ALA_SC_NOT_FOUND,	
	VIAC_ALA_SC_NEEDED,
	VIAC_ALA_SC_INSUFFICIENT_MEMORY, 
	VIAC_ALA_SC_NOT_ACCEPTED,
	VIAC_ALA_SC_FAILED = 10,
	VIAC_ALA_SC_INVALIDATED,
	VIAC_ALA_SC_LOCKED,
	VIAC_ALA_PAIRING_MISMATCH,
	VIAC_ALA_TERMINAL_INSUFFICIENT_MEMORY,
	VIAC_ALA_TERMINAL_CONFIGURATION_ERROR,
	VIAC_ALA_TERMINAL_NOT_ACTIVATED,
	VIAC_ALA_TERMINAL_INVALIDATED,
	VIAC_ALA_PERSONALIZATION_KO,
	VIAC_ALA_RIGHT_OK,
	VIAC_ALA_NO_RIGHT =20,
	VIAC_ALA_GEOGRAPHICAL_BLACKOUT,
	VIAC_ALA_MISSING_KEY,
	VIAC_ALA_IPPV_OFFER_EXPIRED,
	VIAC_ALA_FORBIDDEN_MODE,
	VIAC_ALA_INSUFFICIENT_CREDIT,
	VIAC_ALA_RIGHT_EXPIRED,
	VIAC_ALA_RIGHT_CONSUMED,
	VIAC_ALA_CW_PROTECTION_MISMATCH,
	VIAC_ALA_RECORD_RIGHT_KO,
	VIAC_ALA_TIMESHIFT_RIGHT_KO =30,
	VIAC_ALA_THRESHOLD_REACHED,
	VIAC_ALA_OVERDRAFT_REACHED,
	VIAC_ALA_MATURITY_RATING,
	VIAC_ALA_RECORD_RIGHT_OK,
	VIAC_ALA_TIMESHIFT_RIGHT_OK,
	VIAC_ALA_RECORD_INFO_CHANGE,
	VIAC_ALA_CAMLOCK_ACTIVATED_KO,
	VIAC_ALA_CAMLOCK_ACTIVATED_OK,
	VIAC_ALA_CAMLOCK_NOT_ACTIVATED,
	VIAC_ALA_CAMLOCK_DISABLED = 40,
	VIAC_ALA_CAMLOCK_ACTIVATED_NO_CARD,
	VIAC_ALA_START_SECURITY_RESTRICTION,
	VIAC_ALA_STOP_SECURITY_RESTRICTION,
	VIAC_ALA_FREECHL_STOP,
	VIAC_ALA_FREECHL_RESUME,
	VIAC_ALA_PLAYBACK_KO,
	VIAC_ALA_PLAYBACK_OK,
	VIAC_ALA_MAX

}ViacAlarmMsg_E;

typedef struct
{
	unsigned char m_ucManufacturerId;
	unsigned char m_ucModelId;
	unsigned char m_ucHardwareType;
	unsigned char m_ucHardwareVer;
	unsigned char m_ucSoftwareType;
	unsigned char m_ucSoftwareVer;
	unsigned char m_aucSerialNumber[12];

}STBInfo_S;
typedef struct 
{
	unsigned int m_unMailAddr;
	unsigned int m_unMailLen;
	unsigned int m_unACS1DataAddr;
	unsigned int m_unACS1DataLen;
	unsigned int m_unACS2DataAddr;
	unsigned int m_unACS2DataLen;
	unsigned int m_unCADataAddr;
	unsigned int m_unCADataLen;
}ViacAddress;

typedef enum
{
	SRV_MODE_E,
	COMPONT_MODE_E,
	SRV_SCRAMBLING_E
}ServiceScrambleMode_E;

typedef enum
{
	THEME_LEVEL_REFERENCE =1,
	UI_CLASS_REFERENCE,
	UI_PREBOOKED_REFERENCE,
	UI_IPPVP_REFERENCE,
	UI_IPPVT_REFERENCE

}SelectSub_E ;
typedef struct
{
  ADI_BOOL  	 m_bProgOrCom;
  unsigned int   m_unSrvIndex;
  ViacAlarmMsg_E m_eAlaram;
  unsigned short m_usESID; 
  unsigned int   m_unNetWorkID;
  unsigned int   m_unTSID;
  unsigned int   m_unSrvID;
}Service_MSG_S;

typedef struct
{
    unsigned char   m_ucPreviewIndex;
    unsigned short  m_usPreviewNumber;
	unsigned int    m_unSoid;
} ViacIPPVProgInfo_S;
typedef struct
{
	ADI_BOOL   m_bSCOK;
	unsigned char m_ucCardID[64];
	unsigned int  m_unDataLen;
	unsigned int  m_unSCPGLevel;
	
}SmartCardInfo;
typedef struct
{
	unsigned char m_aucWebSite[128];
	unsigned int  m_unLen;
}OperatorWebSite_S;
typedef struct
{
	float  m_fCallingPrice;
}OperatorCallingPrice;
typedef struct
{
	unsigned char m_aucPhone[128];
	unsigned int  m_unLen;
}OperatorPhone_S;
typedef struct
{
	unsigned int m_unDeliverVerNum;
	unsigned int m_unEditVersionNum;
	unsigned int m_unMajorVerNum;
	unsigned int m_unMinorVerNum;
	unsigned int m_unOptionMask;
	unsigned int m_unRevsionNum;
	unsigned char m_unCaVariant[64];
	unsigned char m_unOperatorName[64];
}CaVersion_Detail_S;
typedef enum
{
	PRESELECTION_THEMELEVEL,
	PRESELECTION_CLASS,
	PRESELECTION_PREBOOKED,
	PRESELECTION_PPVP,
	PRESELECTION_PPVT

}PreSelection_E;

typedef struct
{
    ADIOSDate_S     m_sDate;
    unsigned char   m_ucTheme;
    unsigned char   m_ucLevel;

} ThemeLevel_S;

typedef struct
{
    ADIOSDate_S     m_sDate;
    unsigned char   m_ucClass;

} ClassReference_S;
typedef struct 
{
	ADIOSDate_S     m_sBeginDate;
	ADIOSDate_S     m_sEndDate;
	unsigned int    m_unMaskCnt ;
	unsigned char   m_ucMask[256];
	unsigned int 	m_unSoidID;
}ClassItem_S;
typedef struct 
{
	unsigned int m_unClassCnt;
	ClassItem_S m_sClassItem[700];
}ClassList_S;

typedef struct 
{
    unsigned int    m_unProgramNumber;
    unsigned int    m_unInteger; 
    unsigned short  m_usFraction; 

} IPPVReference_S;

typedef struct 
{
    unsigned int    m_unProgramNumber;
    unsigned int    m_unInteger; 
    unsigned short  m_usFraction; 

} IPPVTReference_S;

typedef union
{
    ThemeLevel_S   			 m_sThemeLevelReference;
    ClassReference_S         m_sClassReference;
    unsigned int             m_unPrebookedReference;
    IPPVReference_S          m_sIppvPReference;
    IPPVTReference_S         m_sIppvTReference;

} ReferenceInfo_U;

typedef struct 
{
	unsigned int  		m_unSoid;
	PreSelection_E 		m_ePreSelectioin;
	ReferenceInfo_U     m_uReferenInfo;

}PreSelectionContent_S;

typedef struct
{
	unsigned int 		m_unReferenCnt;
	PreSelectionContent_S m_PreSelectionList[12];
}PreselectList_S;

typedef struct 
{
	unsigned int m_unUnitPrice;
	unsigned int m_unFloatPrice;
}ViacPrice_S;
typedef struct
{
	ViacPrice_S   m_sViacPrice;
	unsigned char m_aucCurrency[64];
}PPVCredit_S;
typedef struct 
{
	unsigned char m_aucPin[16];
	unsigned char m_ucLen;
}PinStruct_S;
typedef struct 
{
	PinStruct_S  m_sMatRating;
	unsigned int m_unACSID;
	unsigned int m_unPGLevel;

}MatRatingProg_S;

typedef struct 
{
	unsigned int m_unPGLevel;
	unsigned int m_unMaxPGInputAllow;
}MatRatingInfo_S;

typedef struct
{
	unsigned int m_unMaxPairNum;
	unsigned int m_unCurPairNum;
}SmartCardPairNum_S;
typedef enum
{
    STB_NO_MODE           = 0,
    STB_AUTOPAIRING_MODE  = 1,
    STB_PAIRING_MODE      = 4

} PairMode_E;

typedef struct
{
	unsigned int  m_unLockStatus;
	unsigned char m_aucLockValue[64];
	unsigned int  m_unLockLen;
}CamLockValue_S;

typedef struct 
{
	unsigned char m_aucBuf[256];
	unsigned int  m_unLen;
}Buffer_S;

typedef struct
{
	unsigned int m_unBeginNumber;
	unsigned int m_unEndNumber;
}BookNumber_S;
typedef struct 
{
	BookNumber_S m_sBookNumber[60];
	unsigned int m_unBookNumber;
}PreSubBookList_S;


typedef struct 
{
	ADI_BOOL m_bInvalid;
	ADIOSSysTime_S m_sDate;
	Buffer_S m_sBuffer;
}STBID_S;


typedef struct 
{
	Buffer_S m_sCurrency;
	ViacPrice_S m_sPrice;
	unsigned int m_unProgram;
}PPVTItem_S;
typedef struct 
{
	PPVTItem_S   m_sPPVRItem[50];
	unsigned int m_unItemCnt;
}PPVTList_S;

typedef struct 
{
	Buffer_S m_sCurrency;
	ViacPrice_S m_sPrice;
	unsigned int m_unProgram;
}PPVPItem_S;
typedef struct 
{
	PPVPItem_S   m_sPPVPItem[50];
	unsigned int m_unItemCnt;
}PPVPList_S;

typedef struct
{
	unsigned char m_ucLevel;
	unsigned char m_ucTheme;
	ADIOSDate_S   m_sBeginDate;
	ADIOSDate_S   m_sEndDate;
}ThemeSubItem_S;
typedef struct 
{
	ThemeSubItem_S  m_sThemeSubItem[50];
	unsigned int  m_unCnt;
}ThemeSubItemList;
typedef struct 
{
    unsigned int    m_RemainingAttemptsCount;
    unsigned int    m_MaxAttempts;
}PinCodeAttemptsRequest_S;
typedef struct
{
	Buffer_S  m_sLabel;
    unsigned int   m_unSoid;
} SubLabel_S;
typedef struct
{
	unsigned long m_unSoid[32];
	unsigned int m_unSoidNum;
} SoidList_S;
typedef struct 
{
	ADI_BOOL     m_bExceed;
	unsigned int m_unSoid;
	unsigned int m_unPGValue;	
}PG_REQ_S;

typedef struct
{
	ADIOSDate_S     m_sBeginDate;
	ADIOSDate_S     m_sEndDate;
	unsigned int  m_unMaskCnt;
	unsigned char m_ucMask[256];
}ViacClass_S;
typedef struct
{
	unsigned int m_unSoid;
	unsigned int m_unClassCnt;
	ViacClass_S   m_sViacClass[100];
}ViacSoid_S;

typedef struct
{
 	unsigned int m_unSoidCnt;
	ViacSoid_S   m_sViacSoidList[10];
}ViacEntitle_S;

int ADI_VICA_VerifyPPVPPIN(unsigned int unAcsId, unsigned int unStbStreamHandle, unsigned int unProgNum, unsigned char * pucPinCode);

int ADI_VICA_ReqPPVTPurse(unsigned int unAcsId, unsigned int unStbStreamHandle, unsigned int unProgNum, unsigned char * pucPinCode, ViacPrice_S sPrice);

int ADI_VICA_ChangePinCode(unsigned char * pucOldPin, unsigned char * pucNewPin);

int ADI_VICA_VerifyMatPinCode(unsigned int unAcsId, unsigned char * pucPinCode, int nPwdType);

int ADI_VICA_AcqPreviewProgress(unsigned int unSoid, unsigned char ucPreviewIndex, unsigned short wPreviewNumber);

int ADI_VICA_UnLockConsultation(unsigned char * pucPincode);

int ADI_VICA_ChangeMatLevel(unsigned char * pucPin, unsigned int unMaturityLevel);
int ADI_VICA_ChangeThreshold(unsigned char * pucPin, ViacPrice_S sPrice);

int ADI_VICA_AcqSubSoidList(void);

int ADI_VICA_AcqSubLabel(unsigned int unSoid);

int ADI_VICA_AcqEntitleClassList(unsigned int unSoid);

int ADI_VICA_AcqEntitleThemeList(unsigned int unSoid);

int ADI_VICA_AcqSubPreSelectBookList(unsigned int unSoid);

int ADI_VICA_AcqSubPreSelectList(void);

int ADI_VICA_AddSubPreSelect(unsigned int unSoid, unsigned char * pucCode, SelectSub_E eReferenceType, ReferenceInfo_U* uInfo);

int ADI_VICA_DelSubPreSelect(unsigned int unSoid, unsigned char * pucCode,SelectSub_E eReferenceType, ReferenceInfo_U* uInfo);

int ADI_VICA_ReqSCPairMode(void);

int ADI_VICA_ReqSCPairNumber(void);

int ADI_VICA_ReqSCPairList(void);

int ADI_VICA_AcqSCNumber(void);

int ADI_VICA_AcqCamLockValue(void);

int ADI_VICA_ReqMatRating(void);

int ADI_VICA_ReqPPVPList(unsigned int unSoid);

int ADI_VICA_ReqPPVList(unsigned int unSoid);

int ADI_VICA_ReqCredit(unsigned int unSoid);

int ADI_VICA_ReqPPV(void);

int ADI_VICA_ReqCAVersion(void);

int  ADI_VICA_ReqCAVersionDetail(void);

int ADI_VICA_AcqSTBID(void);

int ADI_VICA_AcqTerminalID(void);

void ADI_VICA_AcqSCStatus(int* pnSmcStatus);

int ADI_VICA_AcqSCMatLevel(int* pnSCPGLevel);

int ADI_VICA_AcqOperatorTel(unsigned int unSoid);

int ADI_VICA_AcqOperatorCallPrice(unsigned int unSoid);

int ADI_VICA_AcqOperatorWebsite(unsigned int unSoid);

	

void ADI_VICA_SetSTBInfo(STBInfo_S sSTBInfo);
int ADI_ViacSetAddr(ViacAddress sViacAddress);

extern void GetNetWorkTime(ADIOSSysTime_S *pTime);

int ADI_VICA_AcqEntitleList(ViacEntitle_S * psViacEntile);

#ifdef  __cplusplus
}
#endif

#endif



