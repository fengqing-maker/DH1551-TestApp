#ifndef _ADI_CONAX_INTERFACE_H_
#define _ADI_CONAX_INTERFACE_H_

#include "ADI_CA_Comon.h"
#include "adi_typedef.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define MAX_TXT_LEN      (64)
#define MAX_DEBIT_NUM    (32)
#define MAX_CREDIT_NUM   (32)
#define MAX_MAILTEXT_LEN (256)
#define MAX_ECM_LEN      (1024)

typedef enum
{
	STANDARD_SECURITY_MODE = 0,
	ADVANCE_SECURITY_LPK_MODE = 2,
	ADVANCE_SECURITY_CWPK_MODE = 5,
	SECURITY_MODE_MAX
}SECURITY_MODE_E;

typedef enum
{
	MSG_ALARM_CONAX,
	MSG_COMMAND_CONAX,
}MSG_CONAX_TYPE;

// COMMOND
typedef enum
{
	CONAX_CMD_EMAIL_SHOW=0, // show new mail inco
	CONAX_CMD_EMAIL_HIDE, // hide new mail inco

	// OSM显示 (参数 & ConaxOSM_S)
	CONAX_CMD_OSM_SHOW, // show osm
	CONAX_CMD_OSM_HIDE, // hide osm

	// Accept_Viewing需要输入PIN解扰 (参数 & ConaxViewInfo_S)
	// 用户切台或者按退出键或者收到hide消息移除此Viewing
	// 调用ConaxCA_ConfirmWatchViewingProgram接口观看此节目
	// 以下是一个提示例子
	// Start viewing
	// 'Name-of-the-product'
	// Minutes viewing time left: 141
	// Enter CA PIN to start viewing: ****
	CONAX_CMD_VIEWING_DLG_SHOW, // show viewing dialog
	CONAX_CMD_VIEWING_DLG_HIDE, // hide viewing dialog

	// Tokens access需要输入PIN解扰 (参数 & ConaxTokenDebitInfo_S)
	// 用户切台或者按退出键或者收到hide消息移除此Tokens框
	// 调用ConaxCA_ConfirmWatchDebitTokensProgram接口观看此节目
	// 例子1(m_bTokensMode==1)
	// Tokens access
	// Best of Pink Floyd
	// 5 token(s) per minute
	// Purse balance: Gold 150 tokens
	// Enter CA PIN to accept: ****
	// 例子2(m_bTokensMode==0)
	// Tokens access
	// Best of Pink Floyd
	// 100 token(s)
	// Purse balance: Gold 150 tokens
	// Enter CA PIN to accept: ****
	CONAX_CMD_TOKEN_DEBIT_DLG_SHOW, // show token debit dialog
	CONAX_CMD_TOKEN_DEBIT_DLG_HIDE, // hide token debit dialog

	// Ordering只是提示性的CMD消息 (参数&ConaxOrderInfo_S)
	// 用户切台或者按退出键或者收到hide消息移除此Ordering
	// 需要包含label,price和currency
	// 以下是一个提示例子
	// Ordering
	// 'Name-of-the-file'.  GBP 3.00
	CONAX_CMD_ORDERING_DLG_SHOW, // show ordering dialog
	CONAX_CMD_ORDERING_DLG_HIDE, // hide ordering dialog

	// Maturity Lock需要输入PIN解扰 (参数为当前节目的Mat level)
	// 用户切台或者按退出键或者收到hide消息移除此Maturity Lock框
	// 节目当前level为消息参数给出, 卡的level调用ConaxCA_GetSMCInfo获取
	// 调用ConaxCA_ConfirmWatchMatLockProgram接口观看此节目
	// 以下是一个提示例子
	// Maturity Lock
	// Program rating: PG
	// Card level: A
	// Enter CA PIN to start unlock: ****
	CONAX_CMD_MATLOCK_SHOW, // show mat lock dialog
	CONAX_CMD_MATLOCK_HIDE, // hide mat lock dialog

	// URI信息通知 (参数 & ConaxURI_S)
	CONAX_CMD_URI,

	// 请求用户输入正确的PIN到CA缓存
	CONAX_CMD_REQUEST_PIN, // VSC configuration changed - Please enter PIN
	
	CONAX_CMD_MAX 
}ConaxCommandMsg_E;

// ALARM
typedef enum
{
	CONAX_ALA_CANCEL, // not show anything, clear all alarm message
	CONAX_ALA_CARD_OUT, // "No card insert" // SMC only
	CONAX_ALA_CARD_INVALID, // "Incorrect card" // SMC only
	CONAX_ALA_CARD_COMMUNICATION_ERROR, // "Card problem - check card" // SMC only
	CONAX_ALA_OTHER, // "Other ca service"
	CONAX_ALA_NO_ACCESS, // "No access (x)"
	CONAX_ALA_BLACKOUT , // No access - geographical balckout
	CONAX_ALA_NETWORK_NOENTILE, // No access - network block
	CONAX_ALA_PPVEXPIRED, // No access - PPV expired
	CONAX_ALA_INITIALIZATION_FAILED, // Initialization failed (x) // VSC only
	CONAX_ALA_E100, // SITI E100
	CONAX_ALA_E120, // SITI E120
	CONAX_ALA_E140, // SITI E140
    CONAX_ALA_MAX
}ConaxAlarmMsg_E;

typedef enum 
{
	EM_CONAX_SC_STA_READY = 0, // card ok
	EM_CONAX_SC_STA_OUT = 1, // card out
	EM_CONAX_SC_STA_COMMUNICATION_ERROR = 2, // card communication error
	EM_CONAX_SC_STA_NOT_VALID = 3, // card not valid
	EM_CONAX_SC_STA_UNKNOW = 4, // card status not know
}ConaxSCStatus_E;

// MatLevel级别
typedef enum
{
	EM_CNX_RAT_G = 0,
	EM_CNX_RAT_PG = 1,
	EM_CNX_RAT_A = 2,
	EM_CNX_RAT_X = 3,
	EM_CNX_RAT_XXX = 4,//Read only, cannot set to card!20170421
	EM_CNX_RAT_UNKNOW
}ConaxSCMatLevel_E;

// 日期
typedef struct 
{
    unsigned short m_wYear;
    unsigned char m_ucMonth;
    unsigned char m_ucDay;
    unsigned char m_ucHour;
    unsigned char m_ucMinute;
    unsigned char m_ucSecond;
}ConaxDateTime_S;

// 卡信息
typedef struct
{   
	unsigned short m_usLanguageIndex;
	unsigned char  m_ucCardVer;
	unsigned char  m_ucSessionNum;
	unsigned short m_usCaSysId;
	ConaxSCMatLevel_E m_eMatLevel;
	unsigned char  m_aucCardNum[16];
} ConaxCardInfo_S;


// SubscriptionStatus 信息
typedef struct
{ 
    ConaxDateTime_S	   m_sStarTime;              		 
    ConaxDateTime_S	   m_sEndTime;                		 
    unsigned int	   m_unEntitlement;          
} ConaxEntitleInfo_S;
typedef struct
{
    unsigned char      m_acEntitleTxt[MAX_TXT_LEN];  // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
    unsigned short	   m_usEntilementID;
    ConaxEntitleInfo_S  m_sEntilementInfo[2];
}ConaxSubscriptionStatus_S;


// PPVEventStatus 信息
typedef struct
{   
	// 显示的Name
    unsigned char  m_acLabel[MAX_TXT_LEN];  // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码

	unsigned int	   	m_unEventRef; 

	// Event 开始时间
    ConaxDateTime_S	   	m_sStartTime;

	// Event 结束时间
    ConaxDateTime_S	   	m_sEndTime;

	// m_usMinutesOrCreditsLeft剩余的分钟或者Credit , 当为0或者2 m_usMinutesOrCreditsLeft需要显示,否则显示空白
    unsigned short      m_usMinutesOrCreditsLeft; 

	// m_usAuthType 0:Time-limited  2:Credit-base access, 1:Unlimited access , 当为0或者2 m_usMinutesOrCreditsLeft需要显示,否则显示空白
    unsigned short      m_usAuthType;                     
} ConaxPPVEventStatus_S;


// TokenPurse信息
typedef struct
{
	unsigned short	m_usPurseRef;

	// 显示 Balance
	unsigned short	m_unPurseBalance;

	// Purse的名称
	unsigned char 	m_acPursetTitle[MAX_TXT_LEN];  // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
}ConaxTokenPurse_S;


// 特定Purse的DebitInfo信息
typedef struct
{
	unsigned int		m_unEventID;

	// Event Tokens
	unsigned int		m_unConsumedTokens;

	// Event 名称
	unsigned char		m_acTxt[MAX_TXT_LEN];  // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码

	// Event 时间
	ConaxDateTime_S		m_sAccessTime;                 
}ConaxDebitInfo_S;


// 特定Purse的CreditInfo信息
typedef struct
{
	// Credit Tokens
	unsigned int m_unCreditTokens;

	// Credit Label
	unsigned char  	m_acTxt[MAX_TXT_LEN]; // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
}ConaxCreditInfo_S;


// PI_OUTPUT_ORDER_INFO
typedef struct
{
	unsigned int m_unProductRef;
	unsigned char m_ucProductCurrency[4]; // ISO4217 前3字节 Currency
	float  m_fProductPrice;
	unsigned char  m_acTxt[MAX_TXT_LEN] ; // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
}ConaxOrderInfo_S;

// PI_OUTPUT_ACCEPT_VIEWING_INFO
typedef struct
{
	unsigned int 	m_unProductRef;
	unsigned short  m_usMinLeft;
	unsigned char  	m_acTxt[MAX_TXT_LEN] ; // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
}ConaxViewInfo_S;

// PI_OUTPUT_TOKEN_DEBIT_INFO
typedef struct
{
	ConaxTokenPurse_S 	m_sPurseInfo;
	unsigned int	    m_unEventTag;
	ADI_BOOL 	        m_bInsufficent;
	ADI_BOOL		    m_bTokensMode;
	unsigned int        m_unEventCost;
	unsigned char 	    m_acTxt[64]; // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
}ConaxTokenDebitInfo_S;

// 邮件--Message的一种
typedef struct
{
	unsigned int		m_unReaded; // 0:未读   1:已读
	unsigned char		m_ucMailId;
	ConaxDateTime_S	    m_sTimeTime;
	unsigned int		m_unTextLen;
	unsigned char		m_aucText[MAX_MAILTEXT_LEN]; // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
}ConaxMail_S;

// ConaxCA的配置信息
typedef struct
{	
	unsigned int m_unID; 
	unsigned int m_unFlashAddr;
	unsigned int m_unFlashBackupAddr;
	unsigned int m_unFlashSize;
}ConaxFlashCfg_S;

typedef struct
{
	ConaxFlashCfg_S m_stMessageFlashCfg;
	ConaxFlashCfg_S m_stKeyStoreFlashCfg;
	SECURITY_MODE_E m_eSecurityMode;
	unsigned short m_usProtocol_id;
	Up2App_F m_MsgCallbackFn;
}ConaxSmcConfig_S;

typedef struct
{
	int m_nMode; // 0:personalization,  1:normal
	ConaxFlashCfg_S m_stMessageFlashCfg;
	unsigned int m_unDataAddr; // vsclib使用Falsh起始地址,大小固定0x10000
	unsigned int m_unConfigAddr; // vsclib使用Falsh配置文件起始地址,大小固定0x10000
	unsigned int m_unDataBackupAddr; // m_unDataAddr的备份,大小固定0x10000
	unsigned int m_unConfigBackupAddr; // m_unConfigAddr的备份,大小固定0x10000
	unsigned int m_unVscLibAddress; // vsclib_flashaddr
	unsigned int m_unVscLibLength; // vsclib_len
	Up2App_F m_MsgCallbackFn;
}ConaxVscCfg_S;

typedef union
{
	ConaxSmcConfig_S m_SMC;
	ConaxVscCfg_S m_VSC;
}ConaxCfg_U;

typedef enum
{
	EM_PRJ_CT = 0,
	EM_PRJ_SITI = 1,
	EM_PRJ_MAX
}PRJSETTING_E;

typedef struct
{
	PRJSETTING_E m_Prj_Tpye; // project type
	unsigned int m_Reserved1;
	unsigned int m_Reserved2;
	unsigned int m_Reserved3;
}GlobalSetting_S;

// CpSpec.pdf - pg75 - 6.3.3
typedef struct
{
	// 0: Copy protection encoding off
	// 1: AGC process on; split burst off
	// 2: AGC process on; 2 line split burst on
	// 3: AGC process on; 4 line split burst on
	unsigned char m_ucAPSCopyControl; 

	// 0: Copy Freely - Copying is not restricted
	// 1: Copy No more - No futher copying is permitted (not used in the ECm)
	// 2: Copy Noce - One generation copy is permitted
	// 3: Copy Never - Copying is prohibited
	unsigned char m_ucEMICopyControl;

	// 0: No image constraint asserted
	// 1: Image constraint required (<520K pixels)
	unsigned char m_ucImageConstraint;

	// 0: No redistribution control asserted
	// 1: Redistribution control asserted
	unsigned char m_ucRedistributionControl; 

	// Time-shifted content: retention_limit - emi_copy_control
	// 0: No retention limit
	// 1: Retention limit of 1 week applies
	// 2: Retention limit of 2 days applies
	// 3: Retention limit of 1 day applies
	// 4: Retention limit of 12 hours applies
	// 5: Retention limit of 6 hours applies
	// 6: Retention limit of 3 hours applies
	// 7: Retention limit of 90 minutes applies
	//===========================
	// Long-term stored content: retention_limit - emi_copy_control
	// 0: No expiry limit
	// 1: Content expiry after 360 days applies
	// 2: Content expiry after 90 days applies
	// 3: Content expiry after 30 days applies
	// 4: Content expiry after 14 days applies
	// 5: Content expiry after 7 days applies
	// 6: Content expiry after 2 days applies
	// 7: Content expiry after 1 day applies
	unsigned char m_ucRetention; 

	// 0: No restriction
	// 1: No jumping allowed; fast forward limited to maximun 2x speed with visible content
	// 2: No jumping allowed; fast forward limited to maximun 4x speed with visible content
	// 3: No jumping allowed; fast forward limited to maximun 8x speed with visible content
	// 6: No jumping or fast forward allowed
	// 7: No pause, jumping, or fast forward allowed
	unsigned char m_ucTrickPlayControl;

	// 0: No restriction
	// 1: Conax G: 0 year
	// 2: Conax PG: 10 year
	// 3: Conax A: 18 year
	// 4: Conax X: 18 year, erotic content
	// 5: Conax XXX: 18 year, erotic content, PIN required
	unsigned char m_ucMaturityRating; 

	// 0: Analogue output allowed
	// 1: Analogue output forbidden
	unsigned char  m_ucDisableAnalogueOutputs;
}ConaxURI_S;

typedef struct
{
	unsigned char m_pucEcmData[MAX_ECM_LEN];
	unsigned int m_unEcmDataLen;
	unsigned short m_usServiceID;
}ConaxECMSection_S;

typedef struct
{
	unsigned char m_aucText[MAX_MAILTEXT_LEN]; // 如果第一个字节为latin alphabet编码 0或1或5, 第二个字节开始为实际内容, 如果第一个字符不是0不是1也不是5则默认用table05编码
	unsigned int m_unTextLen;
}ConaxOSM_S;

void ConaxCA_GlobalConfig(GlobalSetting_S *GlobalSetting);
/*
 * Description: 初始化ConaxCA
 *
 * Note: pVscCfg, pSmcCfg只有一个有效, 无效的设置为NULL
 *
 * Parameters : pUConfig[IN]: 参数配置
 *              nVscEnable[IN]: 1:无卡   0:有卡
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_Init(int nVscEnable, ConaxCfg_U *pUConfig);


/*
 * Description: 获取Conax vsc lib版本信息
 *
 * Note: 输入参数Buffer空间需要不小于32
 *
 * Parameters :   acConaxLib[IN/OUT] : 版本信息
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetCaLibVersion(char acConaxLib[32]);


/*
 * Description: 获取ConaxCA卡信息 [About Conax CA界面]
 *
 * Note: 
 *
 * Parameters : psCardInfo[IN/OUT]: m_usLanguageIndex 显示例子为Language: 47
 *								    m_ucCardVer 显示例子为Interface version: 0x40
 *								    m_ucSessionNum 显示例子为Number of sessions: 5
 *								    m_usCaSysId 显示例子为CA_SYS_ID: 0x0B00
 *								    m_eMatLevel 不在ConaxCA界面显示
 *								    m_aucCardNum 显示例子为Card Number: 011 0903 1050 - 2
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetSMCInfo(ConaxCardInfo_S *psCardInfo);


/*
 * Description: 获取当前ConaxCA卡状态
 *
 * Note: 进CA菜单可以先检查卡状态
 *
 * Parameters : VOID
 *
 * Returns    :  EM_CONAX_SC_STA_READY 卡就绪可以卡读写操作
 *				 EM_CONAX_SC_STA_OUT 卡没有插入不能读写操作
 *				 EM_CONAX_SC_STA_COMMUNICATION_ERROR 卡插入但还没有就绪不能读写操作
 *			   
 */
ConaxSCStatus_E ConaxCA_GetSMCStatus();


/*
 * Description: 获取当前ConaxCA卡的SubscriptionStatus
 *
 * Note: 进CA菜单可以先检查卡状态, 请传最小支持40个SubscriptionStatus
 *
 * Parameters : psConaxEntitleList[IN/OUT] Subscription具体信息
 *              punCnt[IN/OUT] Subscription个数
 * 
 example
 {
 	ConaxSubscriptionStatus_S stConaxSubscriptionStatus[40];
 	unsigned int unCount = 40;

 	if(0 == ConaxCA_GetAllSubscriptionStatus(&stConaxSubscriptionStatus, &unCount))
 	{
 		// Show SubscriptionStatus GUI
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetAllSubscriptionStatus(ConaxSubscriptionStatus_S *psSubscriptionList, unsigned int *punCnt);

/*
 * Description: 获取当前ConaxCA卡的PPVEventStatus
 *
 * Note: 进CA菜单可以先检查卡状态, 请传最小支持100个PPVEvent
 *
 * Parameters : psConaxEntitleList[IN/OUT] PPVEvent具体信息
 *              punCnt[IN/OUT] PPVEvent个数
 * 
 example
 {
 	ConaxPPVEventStatus_S stEvent[100];
 	unsigned int unCount = 100;

 	if(0 == ConaxCA_GetAllPPVEventStatus(&stEvent, &unCount))
 	{
 		// Show EventStatus GUI
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetAllPPVEventStatus(ConaxPPVEventStatus_S* psPPVEventList, unsigned int *punCnt);

/*
 * Description: 获取当前ConaxCA卡的TokensStatus
 *
 * Note: 进CA菜单可以先检查卡状态, 请传最小支持100个TokensStatus
 *
 * Parameters : pTokenPurseInfoList[IN/OUT] TokensStatus具体信息
 *              punCnt[IN/OUT] Subscription个数
 * 
 example
 {
 	ConaxTokenPurse_S stTokenPurse[100];
 	unsigned int unCount = 100;

 	if(0 == ConaxCA_GetAllTokensPurseStatus(&stTokenPurse, &unCount))
 	{
 		// Show TokensStatus GUI
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetAllTokensPurseStatus(ConaxTokenPurse_S* pTokenPurseInfoList,unsigned int * punCnt);

/*
 * Description: 获取当前ConaxCA卡的TokensStatus具体一项的DebitStatus
 *
 * Note: 进CA菜单可以先检查卡状态, 请传最小支持100个DebitStatus
 *
 * Parameters : usRef 具体某个purse_ref
 *				psCaDebitList[IN/OUT] DebitStatus具体信息
 *              punCnt[IN/OUT] DebitStatus个数
 * 
 example
 {
 	ConaxDebitInfo_S stTokenDebit[100];
 	unsigned int unCount = 100;

 	if(0 == ConaxCA_GetSepcificDebitStatus(0x1122, &stTokenDebit, &unCount))  // 为具体purse_ref
 	{
 		// Show TokensStatus GUI
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetSepcificDebitStatus(unsigned short usRef, ConaxDebitInfo_S * psCaDebitList,unsigned int * punCnt);


/*
 * Description: 获取当前ConaxCA卡的TokensStatus具体一项的CreditStatus
 *
 * Note: 进CA菜单可以先检查卡状态, 请传最小支持20个CreditStatus
 *
 * Parameters : usRef 具体某个purse_ref
 *				psCaDebitList[IN/OUT] DebitStatus具体信息
 *              punCnt[IN/OUT] DebitStatus个数
 * 
 example
 {
 	ConaxCreditInfo_S stDebit[20];
 	unsigned int unCount = 20;

 	if(0 == ConaxCA_GetSepcificCreditStatus(0x1122, &stDebit, &unCount))  // 为具体purse_ref
 	{
 		// Show TokensStatus GUI
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetSepcificCreditStatus(unsigned short usRef, ConaxCreditInfo_S * psCaCreditList,unsigned int * punCnt);

/*
 * Description: 获取当前ConaxCA邮件个数
 *
 * Parameters : void
 *
 * Returns	  :    mail count
 *			   
 */
unsigned int ConaxCA_GetMailCount(void);

/*
 * Description: 获取某一封邮件
 *
 *
 * Parameters : unIndex[IN] 邮件索引, 范围0~15之间
 *              psMail[IN/OUT] 邮件具体内容
 * 
 example
 {
 	// 获取第一封邮件(index=0)内容
 	ConaxMail_S stMail;
 	memset(&stMail, 0, sizeof(stMail));
 	if(0 == ConaxCA_GetMailByIndex(0, &stMail))
 	{
 		// Show Mail Box index 0
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetMailByIndex(unsigned int unIndex, ConaxMail_S * psMail);

/*
 * Description: 获取当前ConaxCA的所有邮件列表
 *
 * Note: 请传最小支持16个ConaxMail
 *
 * Parameters : psMailList[IN/OUT] 邮件列表
 *              punCnt[IN/OUT] 邮件个数
 * 
 example
 {
 	ConaxMail_S stMail[16];
 	unsigned int unCount = 16;

 	if(0 == ConaxCA_GetAllMails(&stMail, &unCount))
 	{
 		// Show Mail Box
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_GetAllMails(ConaxMail_S * psMailList,unsigned int * punCnt);

/*
 * Description: 对邮箱按照时间降序(最新的在最前面)
 *
 * Note: 调用ConaxCA_GetAllMails后得到所有邮件, 再调用此接口对邮箱排序
 *
 * Parameters : psMailList[IN/OUT] 邮件列表
 *              unCount[IN] 邮件个数
 * 
 example
 {
 	ConaxMail_S stMail[16];
 	unsigned int unCount = 16;

	if(0 == ConaxCA_GetAllMails(&stMail, &unCount))
	{
 		if(0 == ConaxCA_SortAllMailsTimeDescend(&stMail, unCount))
 		{
 			// Show Mail Box
 		}
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_SortAllMailsTimeDescend(ConaxMail_S * psMailList,unsigned int unCnt);

/*
 * Description: 设置一封邮件为已读状态
 *
 * Note: 读取某一封邮件时调用此接口 设置为已读状态
 *
 * Parameters : m_ucMailId[IN] 邮件ID
 * 
 example
 {
 	unsigned char ucID = 0x02;

 	if(0 == ConaxCA_SetMailReadFlag(m_ucMailId))
 	{
 	}
 }
 *
 * Returns	  :    0: 成功
 *             other: 失败
 *			   
 */
int ConaxCA_SetMailReadFlag(unsigned char m_ucMailId);


/*
 * Description: 修改当前ConaxCA卡的MatLevel
 *
 * Note: 进CA菜单可以先检查卡状态
 *
 * Parameters : eLevel[IN] 新的MatLevel
 *				aucPin[IN] 卡的PIN码
 * 
 example
 {
 	ConaxSCMatLevel_E eLevel = EM_CNX_RAT_X
 	unsigned char aucPIN[4] = {'1','2','3','4'};

 	if(0 == ConaxCA_ModifyMatLevel(eLevel, aucPin)) 
 	{
 	}
 }
 *
 * Returns	  :    0: "Maturity rating level has been changed!"
 *                 1: "Incorrect PIN."
 *             other: "Modify Maturity rating level failed."
 *			   
 */
int ConaxCA_ModifyMatLevel(ConaxSCMatLevel_E eLevel, unsigned char aucPin[4]);

/*
 * Description: 修改当前ConaxCA卡的PIN码
 *
 * Note: 进CA菜单可以先检查卡状态, 需要输入2次新PIN,如果2次新密码不一致请提示 "PIN confirmation does not match."
 *
 * Parameters : aucOldPin[IN] 旧PIN
 *				aucNewPin[IN] 新PIN
 *
 example
 {
 	unsigned char aucOldPIN[4] = {'1','2','3','4'};
	unsigned char aucNewPIN[4] = {'4','5','6','7'};

 	if(0 == ConaxCA_ModifySMCPin(aucOldPIN, aucNewPIN)) 
 	{
 	}
 }
 *
 * Returns	  :    0: "CA PIN has been changed!"
 *                 1: "Incorrect old PIN."
 *             other: "Change CA PIN failed."
 *			   
 */
int ConaxCA_ModifySMCPin(unsigned char aucOldPin[4], unsigned char aucNewPin[4]);

/*
 * Description: 校验输入PIN是否正确
 *
 * Note: 
 *
 * Parameters : aucPin[IN] pin
 *
 example
 {
 	unsigned char pin[4] = {'1','2','3','4'};

 	if(0 == ConaxCA_CheckPin(pin)) 
 	{
 	}
 }
 *
 * Returns	  :    0: PIN OK
 *                 other: Incorrect PIN
 *			   
 */
int ConaxCA_CheckPin(unsigned char aucPin[4]);

/*
 * Description: 校验CA缓存的PIN是否正确, 不正确会有异步消息CONAX_CMD_REQUEST_PIN
 *
 * Note: 
 *
 * Parameters : void
 *
 example
 {
 	ConaxCA_CheckCachedPin()
 }
 *
 * Returns	  :    0: PIN OK
 *                 other: Incorrect PIN
 *			   
 */
void ConaxCA_CheckCachedPin(void);

/*
 * Description: 输入PIN观看MatLock节目
 *
 * Note: 
 *
 * Parameters : aucPin[IN] 卡的PIN码
 *				ucSessionID[IN] 当前节目的session ID
 * 
 example
 {
 	unsigned char aucPIN[4] = {'1','2','3','4'};
	unsigned char ucSessionID = 0;

 	if(0 == ConaxCA_ConfirmWatchMatLockProgram(aucPIN, ucSessionID)) 
 	{
 	}
 }
 *
 * Returns	  :    0: "Confirm OK"
 *                 1: "Incorrect PIN."
 *             other: "Confirm failed."
 *
 *			   
 */
int ConaxCA_ConfirmWatchMatLockProgram(unsigned char aucPin[4], unsigned char ucSessionID);

/*
 * Description: 输入PIN观看AcceptView节目
 *
 * Note: 
 *
 * Parameters : aucPin[IN] 卡的PIN码
 *				ucSessionID[IN] 当前节目的session ID
 * 
 example
 {
 	unsigned char aucPIN[4] = {'1','2','3','4'};
	unsigned char ucSessionID = 0;

 	if(0 == ConaxCA_ConfirmWatchViewingProgram(aucPIN, ucSessionID)) 
 	{
 	}
 }
 *
 * Returns	  :    0: "Confirm OK"
 *                 1: "Incorrect PIN."
 *             other: "Confirm failed."
 *			   
 */
int ConaxCA_ConfirmWatchViewingProgram(unsigned char aucPin[4], unsigned char ucSessionID);

/*
 * Description: 输入PIN观看TokensPPV节目
 *
 * Note: 
 *
 * Parameters : aucPin[IN] 卡的PIN码
 *				ucSessionID[IN] 当前节目的session ID
 * 
 example
 {
 	unsigned char aucPIN[4] = {'1','2','3','4'};
	unsigned char ucSessionID = 0;

 	if(0 == ConaxCA_ConfirmWatchDebitTokensProgram(aucPIN, ucSessionID)) 
 	{
 	}
 }
 *
 * Returns	  :    0: "Confirm OK"
 *                 1: "Incorrect PIN."
 *             other: "Confirm failed."
 *			   
 */
int ConaxCA_ConfirmWatchDebitTokensProgram(unsigned char aucPin[4], unsigned char ucSessionID);

/*
 * Description: 用户进入Conax CA菜单时通知CA 
 *
 * Note: 
 *			   
 */
void ConaxCA_CAMenuEnter(void);

/*
 * Description: 用户退出Conax CA菜单时通知CA
 *
 * Note: 
 *			   
 */
void ConaxCA_CAMenuLeave(void);

/*
 * Description: 通知进入小视频窗口
 *
 * Note: 指纹显示使用 
 *
 * Parameters : x[IN] 小视频窗口x坐标
 *			    y[IN] 小视频窗口y坐标
 *			    w[IN] 小视频窗口宽度
 *		        h[IN] 小视频窗口高度
 */
void ConaxCA_SmallVideoWindowEnter(int x, int y, int w, int h);

/*
 * Description: 通知退出小视频窗口
 *
 * Note: 指纹显示使用 
 *
 */
void ConaxCA_SmallVideoWindowLeave(void);

/*
 * Description: 通知视频Ratio改变
 *
 * Note: 指纹显示使用 
 *
 */
void ConaxCA_NotifyVideoRatioChange(void);

/*
 * Description: 退出Matlock框通知CA, 以便后续能再弹出框否则一直黑屏,直播sessionid=0
 */
void ConaxCA_ExitMatLockDlg(unsigned char ucSessionID);

/*
 * Description: 退出Ordering框通知CA, 以便后续能再弹出框否则一直黑屏,直播sessionid=0
 */
void ConaxCA_ExitOrderingDlg(unsigned char ucSessionID);

/*
 * Description: 退出Viewing框通知CA, 以便后续能再弹出框否则一直黑屏,直播sessionid=0
 */
void ConaxCA_ExitViewingDlg(unsigned char ucSessionID);

/*
 * Description: 退出DebitTokens框通知CA, 以便后续能再弹出框否则一直黑屏,直播sessionid=0
 */
void ConaxCA_ExitDebitTokensDlg(unsigned char ucSessionID);

/*
 * Description: 检查当前Ecm是否有授权
 *
 * Note: 
 *
 * Parameters : pucEcmData[IN]  ecm数据
 *				unEcmDataLen[IN] ecm数据长度
 * 
 example
 {
 	if(0 == ConaxCA_CheckEcmAccess(ecm, ecm_len)) 
 	{
 		// access check passed  
 	}
 	else
 	{
 		// access check failed
 	}
 }
 *
 * Returns	  :    0: "access check passed"
 *             other: "access check failed"
 *			   
 */
int ConaxCA_CheckEcmAccess(unsigned char *pucEcmData, unsigned int unEcmDataLen);

//**************************************************************************//

#ifdef  __cplusplus
}
#endif

#endif

