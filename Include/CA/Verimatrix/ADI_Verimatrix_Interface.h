/****************************************************************************** 
* FileName : ADI_Verimatrix_Interface.h
* Author:      Steve.hou
* Date:         2015.5.5
* Description: Verimatraix CA interface file for app integration  using,
*            
*******************************************************************************/

/*******************************************************************************
* 			                                  Revision History                                				     *
********************************************************************************
*01.01: Creat verimatrix ca porting head file    author Steve.hou @2015.5.5
*******************************************************************************/
#include "adi_typedef.h"
#include "adi_tuner.h"
#include "adi_os.h"
#include "adi_osg.h"

#ifndef _ADI_VERIMATRIX_INTERFACE_H_
#define _ADI_VERIMATRIX_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define MAX_FRE_LIST  (8)  //最多支持的频点列表
#define CA_SRV_MAX  (0x3)  //最大支持多少路解绕
#define OSM_MAX_SIZE   	(1024)
#define MAX_ESPID_PERCHL  (0x8)  //每路最大支持8个ESPID
#define MAX_BUFFER_LEN	 (1024)


typedef enum
{
	MSG_ALARM_VMX,
	MSG_COMMAND_VMX,
	MSG_STATUS_VMX
}MSG_VMX_TYPE;
typedef enum
{
	INDIVI_PARAM_ERROR,
	INDIVI_INITCOM_ERROR,
	INDIVI_RECSCDATA_ERROR,
	INDIVI_INITDATA_ERROR,
	INDIVI_RETURNFILE_ERROR,
	INDIVI_ERROR_MAX
}INDIVI_ERROR_E;
typedef struct 
{
	INDIVI_ERROR_E m_eIndiviCode;
	unsigned char  m_aucData[MAX_BUFFER_LEN];
	unsigned int m_unLen;
}IndiviError_S;

typedef enum 
{
	ALARM_VMX_Verimatrix_CA,
	ALARM_VMX_OTHER,
	ALARM_VMX_FTA,
	ALARM_VMX_CARD_RIGHT,
	ALARM_VMX_CARD_INCORRECT,
	ALARM_VMX_CARD_COMMUNICATION_ERROR,
	ALARM_VMX_CARD_INSERT,
	ALARM_VMX_CARD_REMOVE,
	ALARM_VMX_ACCESS_OK,
	ALARM_VMX_NO_RIGHT  ,
	ALARM_VMX_NO_ECMS,
	ALARM_VMX_UPDATE_REQUIRED,
	ALARM_VMX_BAD_PAIRING,
	ALARM_VMX_MS_ERROR,
	CA_VMX_MAX
}ALARAM_VMX_E;

typedef enum
{
	COMMAND_VMX_CHECKPIN,
	COMMAND_VMX_PIN_VERIFIED,
	COMMAND_VMX_PIN_CHANGED,
	COMMAND_VMX_PIN_FAILURE,
	COMMAND_VMX_PIN_BLOCKED,
	COMMAND_VMX_PIN_NOT_BE_CHANGED,
	COMMAND_VMX_ORDER_INFO,
	COMMAND_VMX_PURSE_LIST,
	COMMAND_VMX_OSM,
	COMMAND_VMX_MAIL,
	COMMAND_VMX_FORCE_UPGRADE,
	COMMAND_VMX_RESCAN_NOW,
	COMMAND_VMX_SWITCH_NOW,
	COMMAND_VMX_PIN_NUM_RESET,
	COMMAND_VMX_EAS_EVENT_START,
	COMMAND_VMX_EAS_EVENT_END,
	COMMAND_VMX_WATERMARKING,
	COMMAND_VMX_Indivi
}COMMAND_VMX_E;
typedef enum
{
	STATUS_VMX_CARD_INSERT,
	STATUS_VMX_CARD_REMOVE,
	STATUS_VMX_CARD_READY,
	STATUS_VMX_CARD_COMMUNICATION_ERROR,
	STATUS_VMX_CARD_INCORRECT
}STATUS_VMX_E;


typedef enum 				
{
	PIN_INDEX_PC					= 0,	
	PIN_INDEX_IPPV,            				
	PIN_INDEX_STB_LOCK,        				
	PIN_INDEX_HOME_SHOPPING,   				
	PIN_INDEX_NON_SMC 				= 0x80, 
	PIN_INDEX_IPPV_PURSE_UNENOUGH	= 0xFF 
}PinIndex_E;

typedef enum 						
{
	PIN_TEXT_PC						= 0,    
	PIN_TEXT_IPPV,            				
	PIN_TEXT_PC_NONSMC 				= 3,   	
	PIN_TEXT_RESUME,          				
	PIN_TEXT_SELECT,           				
	PIN_TEXT_IPPV_PURSE_UNENOUGH 	= 0xFF 	
}PinText_E;

//搜索节目模式
typedef enum 					
{
	TRIGGER_ERASE_ALL_ADD_ALL		= 0, 	
	TRIGGER_ERASE_ALL_ADD_CA,    			
	TRIGGER_ADD_ALL ,            			
	TRIGGER_ADD_CA              				
}RescanMode_E;

//结构体颜色集
typedef enum 
{
	BG_DARKGREEN ,        
    BG_BLUE , 
	BG_SKYBLUE , 	
	BG_GREEN , 
	BG_DULLORANGE ,
	BG_SLATE ,
	BG_ORANGE ,
	BG_TRANSPERENT 
}WATERMARKING_BG_COLOR_E;

typedef enum 
{
	FONT_NAVYBLUE ,        
    FONT_BLACK , 
	FONT_BROWN , 
	FONT_BLUE , 
	FONT_SLATE ,
	FONT_DULLORANGE,
	FONT_LIGHTYELLOW ,
	FONT_GREEN ,
	FONT_ORANGE ,
	FONT_WHITE 
}WATERMARKING_FRONT_COLOR_E;

typedef enum
{
	FP_CUSTOM_DEFAULT,
	FP_CUSTOM_1,
	FP_CUSTOM_2,
	FP_CUSTOM_3,
	FP_CUSTOM_4,
	FP_CUSTOM_5,
	FP_CUSTOM_6,
	FP_CUSTOM_7,
	FP_CUSTOM_MAX
}FP_CUSTOM_E;

enum  //pin的sector区域
{
	E_PIN_SC_SECTOR = 0,
	E_PIN_IPPV_SECTOR = 1,
	E_PIN_NSC_SECTOR = 3
};

//密码结构体
typedef struct 
{
	unsigned int m_nPinIndex ;
	unsigned int m_nPinSector;
	unsigned char m_aucPin[4];
	unsigned int m_nSrvIndex;
}Pin_Info_S;


//IPPV结构体
typedef struct
{
	Pin_Info_S m_sPinInfo;
	unsigned char m_aucCost[32];
	unsigned char m_aucPurse[32];
}IRD_Order_S;

//钱包列表
typedef struct 			
{
	unsigned int	m_nPurseNumber;										
	unsigned char	m_acPurseInfo[24][32];	
}IRD_Purse_S;  

//升级trigger结构体
typedef struct 				
{
	unsigned int 				   m_nTriggerNum;				
	ADITunerSRCDeliver_U     	m_stDlySys[MAX_FRE_LIST];	
	unsigned char				   m_ucDesNum;					
}Forced_Upgrade_S;

//搜索trigger结构体
typedef struct 					
{
	unsigned int               m_dwTriggerNum;			
	ADITunerSRCDeliver_U	m_stDlySys[MAX_FRE_LIST];		
	RescanMode_E		m_eRescanMode;		
	unsigned char		m_ucDesNum;	
}Rescan_S;

//switch trigger结构体
typedef struct 					
{
	unsigned int	m_nTriggerNum;					
	unsigned int	m_nOriginalNetworkID;			
	unsigned int	m_nServiceID;					
}Switch_S;

//密码重置tigger结构体
typedef struct 				
{
	unsigned char	m_aucPin[4];
	unsigned int    m_nLen;
}PinReset_S;
//EAS trigger结构体
typedef struct 
{
	unsigned int	m_nTriggerNum;					
	unsigned int	m_nOriginalNetworkID;			
	unsigned int	m_nServiceID;					
	unsigned char	m_aucCode[3];					
}EASEvent_S;

//watermarking trigger结构体
typedef struct 					
{
    ADI_BOOL           			 			 m_bFixed;             
	unsigned char						 	m_ucX_percentage;   
	unsigned char   						 m_ucY_percentage;	 
	WATERMARKING_BG_COLOR_E              	m_eBackGroundColor;   
	WATERMARKING_FRONT_COLOR_E          	 m_eFontColor;         
	ADI_BOOL                    			 m_bCovert;            
	unsigned short     						 m_usHideFrames;        
	unsigned short      					 m_usShowFrames;        
	ADI_BOOL            					 m_bEcmBased;          
	unsigned short      					 m_usServiceId;         
	unsigned int 	     					 m_unDuration;        
	unsigned char           				 m_aucContent[32]; 
}WaterMarking_S;

//IPPV结构体
typedef struct 
{
    unsigned char          m_ucPinIndex;
    unsigned long          m_lPurse;
    unsigned long          m_lCost;
    unsigned short         m_wMult;
    unsigned short         m_wDiv;
    unsigned char          m_bLocation;
    unsigned char          m_bSign0;
    unsigned char          m_bSign1000;
    unsigned char          m_bCount;
    unsigned char          m_bLen;
    unsigned char          m_abText[16];
    unsigned long          m_lEventId;
} IPPV_INFO_S;

typedef struct 			
{
	unsigned char		m_bXOriginLeft;
	unsigned char		m_bXAnchorCenter;
	unsigned short int	m_nXPosition;
	unsigned char		m_bYOriginTop;
	unsigned char		m_bYAnchorCenter;
	unsigned int		m_nYPosition;
}OsmPosition_S;

typedef enum 				
{
	TEXT_LEFT_E			 	= 0,   	
	TEXT_RIGH_E,		 				
	TEXT_CENTER_E,					
	TEXT_BOTH_E
}AlignText_E;

typedef struct 
{
	unsigned char m_paucTxt[1024];
	unsigned char m_nDataLen ;
	ADIOSSysTime_S m_sDateTime;
	ADI_BOOL m_bRead ;
}Mail_Info_S;

typedef struct 			
{
	ADI_BOOL 					  m_bIsMail;					
	ADI_BOOL					  m_bIsRemoved;				
	unsigned short int            m_nDuration;				
	OsmPosition_S				  m_sOsmPosition;				
	AlignText_E  				  m_eTextAlign;				
	unsigned char            	  m_bBgColor;
	unsigned char 				  m_bBkAlpha;
	unsigned char 				  m_bDisplayMode;
	unsigned char     			  m_ucText[OSM_MAX_SIZE];	
}OnScreenMessage_S;
typedef struct
{
   unsigned int m_unCADataAddr;
   unsigned int m_unCADataLen;
   unsigned int m_unCADataBackAddr;
   unsigned int m_unCADataBackLen;   
   unsigned int m_unCAMailAddr;
   unsigned int m_unCAMailLen;
}VMXDataFlash_S;

/**************************************************************************
*		以下接口函数为个性化相关的函数
*   
***************************************************************************/
/**************************************************************************
* Function Name: ADI_VMX_InitNscComm
*  CA个性化写入函数第一个被调用
*
*Parameters:
*	pucPtr [output]:	返回CA库获取的字符串，此字符串需要发送给个性化服务器
*	pwLen [ output] : 	 pucptr的长度
*	pucbBoxSerNo[input] :机顶盒chipid
*	pucManuId[input] :  机顶盒厂商ID
*    pucManuData[input]: 机顶盒厂商ID对应的数据
*    pucProvId[input] : 提供商ID
*    pucProvData[intput]: 提供商对应的数据
*Return Values:
*	成功返回值为0，否则返回值-1
*
**************************************************************************/

int ADI_VMX_InitNscComm(unsigned char* pucbPtr, unsigned short int* pnLen,
					unsigned char * pucbBoxSerNo,
					unsigned char * pucManuId,
					unsigned char * pucManuData,
					unsigned char * pucProvId,
					unsigned char * pucProvData);

/**************************************************************************
* Function Name: ADI_VMX_InitNsc
*  CA个性化初始化函数第二个被调用
*
*Parameters:
*	pucPtr [input output]:输入时为个性化服务器返回的数据，输出时为盒子返回的48的字节
*	 pwLen [ nLen] : 	 pucptr的长度
*Return Values:
*	成功返回值为0，否则返回值-1
*
**************************************************************************/

int ADI_VMX_InitNsc(unsigned char * pucPtr, unsigned short int* pwLen );

/**************************************************************************
*		以下接口为常用的基本功能函数
*   
***************************************************************************/
/**************************************************************************
* Function Name: ADI_VMX_CheckNsc
*  校验STB是否支持无卡功能
*
*Parameters:
*	 
*Return Values:
*	返回0则表明STB已经个性化返回-1则表示机顶盒未做个性化动作
*
**************************************************************************/

int ADI_VMX_CheckNsc(void);

/**************************************************************************
* Function Name: ADI_VMX_CheckCardPin
*  校验stb卡密码功能此函数是异步过程校验密码的结果信息
*  通过回调消息的形式通知给app
*Parameters:
*	 
*Return Values:
*	成功返回0失败返回-1 
*
**************************************************************************/
int  ADI_VMX_CheckCardPin(Pin_Info_S sPinInfo);
/**************************************************************************
* Function Name: ADI_VMX_QueryPurseInfo
*  查询stb的机顶盒钱包信息通过回调消息方式将结果反馈到app中
*  
*Parameters:
*	 
*Return Values:
*	成功返回0失败返回-1 
*
**************************************************************************/

int ADI_VMX_QueryPurseInfo(void);
/**************************************************************************
* Function Name: ADI_VMX_GetCardNumber
*  获取机顶盒卡号信息函数
*  
*Parameters:
*pucSCNumber[output] : 机顶盒卡号参数信息
*nLen[input] : pucSCNumber  buffer的缓冲长度
*Return Values:
*	成功返回0失败返回-1 
*
**************************************************************************/

int  ADI_VMX_GetCardNumber(unsigned char* pucSCNumber,unsigned int nLen);

/**************************************************************************
* Function Name: ADI_VMX_GetCaSystemId
*  获取ca system id
*  
*Parameters:
*
*
*Return Values:
*	返回当前机顶盒的systemid 
*
**************************************************************************/

unsigned short ADI_VMX_GetCaSystemId(void);
/**************************************************************************
* Function Name: ADI_VMX_GetBCLibVersion
*  获取机顶盒库版本信息
*  
*Parameters:
*pucLibVer[outPut]: 库版本信息
*pucLibDate[output]: 库日期信息
*pucLibTime[output]: 库时间信息
*Return Values:
*	无
*
**************************************************************************/

void  ADI_VMX_GetBCLibVersion(unsigned char * pucLibVer, unsigned char* pucLibDate, unsigned char* pucLibTime);

/**************************************************************************
* Function Name: ADI_VMX_GetChipID
*  获取或者设置机顶盒chipid
*  高级安全的盒子app通过此函数获取机顶盒chipid
*  非高安盒子app通过此函数设置chipid给ca库
*  由app实现此函数功能
*Parameters:
*pucLibVer[outPut/input]:高级安全时，作为输出参数传递chipid给app使用，
* 非高级安全时作为输入参数传递chipid给app
*nBufLen[input]: buffer 数据长度
*Return Values:
*	无
*
**************************************************************************/

unsigned short ADI_Vmx_GetPairingStatus(void);

int ADI_Vmx_SetCurityFlag(ADI_BOOL bSecurityFlag );
int ADI_Vmx_GetChipID(unsigned char *paucChip,unsigned int *punLen);
int ADI_VMX_SetStandardCSSN(unsigned char * paucChip,unsigned int unLen);
void ADI_VMX_EraseCAData();//擦出完整的CA区域数据
unsigned int ADI_VMX_SetAddress(VMXDataFlash_S pCaDataPartition);
int ADI_VMX_DelMail(unsigned int nIndex);
int ADI_VMX_GetNum(void);
int ADI_VMX_DelAllmail(void);
int ADI_VMX_ReadMail(int nIndex, Mail_Info_S * pSMail);
ADI_BOOL ADI_VMX_HaveNewMail(void);
int ADI_VMX_SetReadFlag(int nIndex, ADI_BOOL bRead);
void ADI_SetFp_Type(FP_CUSTOM_E eCustom);
unsigned int ADI_CA_SetFPUISurface(ADIOSGRect_S * psUpdateRect, unsigned int unFontSize);

#ifdef  __cplusplus
}
#endif

#endif



