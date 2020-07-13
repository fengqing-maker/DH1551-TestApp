#include "adi_typedef.h"
#include "adi_os.h"
#ifndef _ABV_INTERFACE_H_
#define _ABV_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**< ABV字符编码 */
#define ABV_CENCODE_ASICC (0x00) //ENGLISH，INDONESIAN
#define ABV_CENCODE_ISO_8859_9 (0x05)//FRENCH，GERMAN，TURKISH，SPANISH，DUTCH，ITALIAN，PORTUGUESE
#define ABV_CENCODE_ISO_8859_7 (0x03)//GREEK
#define ABV_CENCODE_ISO_8859_5 (0x01)//RUSSIAN
#define ABV_CENCODE_ISO_8859_6 (0x02)//ARABIC， PERSIAN
#define ABV_CENCODE_ISO_8859_2 (0x06)//POLISH， CZECH
#define ABV_CENCODE_ISO_8859_11 (0x07)//THAI
#define ABV_CENCODE_GB2312 (0x12)//CHINESE

typedef enum
{
	ABV_ALARM,
	ABV_COMMAND,
	ABV_STATUS,
	ABV_MAX
}ADIAbvMsgType_E;

typedef enum 
{
	ABV_ALARM_CA_NO_ERR=0,//0 Clear topbar  屏显、IPPV提示和指纹除外,其他topbar清掉
	ABV_ALARM_STB_SC_NO_PAIRED=1,//E3:STB and Smart Card are not matched
	ABV_ALARM_SC_ERROR=2,// E4:Please use the right Smart Card 
	ABV_ALARM_NO_SC=3,// E5:Please insert Smart Card
	ABV_ALARM_READ_WRITER_ERR=4,// E9:Smart card transfer failed
	ABV_ALARM_NOT_IN_WATCH_TIME=5,// E21:Not in watching time
	ABV_ALARM_CARD_OUT_OF_DATE=6,//E22:Smart card is out of date
	ABV_ALARM_NO_ENTITLE=7,// E23:No entitlement
	ABV_ALARM_STB_AREA_RESTRECT=8,// E29:STB area restricted
	ABV_ALARM_CA_NO_PAIRED=9,// E30:STB and smart card are not paired
	ABV_ALARM_ECM_UNKNOWEN_ERROR=10,// E31:Configuration Error, Please contact the provider!
	ABV_ALARM_NOT_CONTACT_MASTER=11,// E35:not contact master card
	ABV_ALARM_IPPV_PRO_NO_ENOUGH_TOKEN=12,// E26:No enough balance
	ABV_ALARM_WAIT_ENTITLE=13,// E34:Waiting for the entitle...
	ABV_ALARM_SRV_FREE=14,// 清流节目
	ABV_ALARM_SRV_OTHER=15,// 其它CA加扰节目
	ABV_ALARM_SRV_ABV=16,// 本CA加扰节目
	ABV_ALARM_STBID_ERR=17, // E40:STBID error
	ABV_ALARM_STBID_NULL=18, // E42:STBID is empty
}ADIAbvMsgAlarm_E;

typedef enum 
{
    ABV_COMMAND_NEW_EMAIL_SHOW=0,//E17:UnRead Mail 单独的图片显示存在未读邮件  param=1显示
    ABV_COMMAND_NEW_EMAIL_HIDE=1,//新邮件图标隐藏
 	ABV_COMMAND_MAILBOX_FULL_SHOW=2,//E16:MailBox Full 单独的图标提示机顶盒，邮件已满
 	ABV_COMMAND_MAILBOX_FULL_HIDE=3,//邮件满图标隐藏
	ABV_COMMAND_IPPV_NOTIFY=4,//E25:Do you want to book this IPPV program 8IPPV购买信息 ,需要定义ADIAbvIPPV_S[2]来获取信息，即2个ADIAbvIPPV_S大小数据结构
	                        //dwParm2 = (DWORD)&ADIAbvIPPV_S[0](当前IPPV(index=0)的信息，如果ADIAbvIPPV_S[1]!=0即存在也需要显示出来)
	ABV_COMMAND_CLEAR_IPPV_SHOW=5,// E36:clear ippv menu(不显示E19)
	ABV_COMMAND_MATURE_NOTIFY=6,//E24:Please enter the password to watch this maturity level program
}ADIAbvMsgCommand_E;

typedef enum 
{
	ABV_STATUS_CARD_IN_BEGIN=0,// E6:Initializing smart card
	ABV_STATUS_CARD_IN_END_SUCCESS=1,// E7:Succeed to initialize smart card 智能卡初始化成功，需要提示此消息，并且要求提示3秒钟后自动消失
	ABV_STATUS_CARD_IN_END_FAIL=2,// E8:Failed to initialize smart card 没有机顶盒操作或者其他提示的情况下需要一直显示
	ABV_STATUS_SC_PIN_RESET=3,//E10:Succeed in modifying PIN 机顶盒可以显示此信息3秒钟后自动消失
	AVB_STATUS_STB_SC_PAIRED=4,// E11:Succeed in pairing smart card and STB  机顶盒可以显示此信息3秒钟后自动消失
	ABV_STATUS_STB_SC_FREE_PAIRED=5,//E12:Succeed in depairing smart card and 机顶盒可以显示此信息3秒钟后自动消失
	ABV_STATUS_STB_SC_PAIRED_FAILED=6,//E13:Fail to pair smart card and STB
}ADIAbvMsgStatus_E;

#define MAX_EMAIL_NUM (50)/*ABV邮件最大封数*/
#define MAX_MAIL_SIZE (2004) /*ABV邮件的最大长度2000*/
#define ABV_SC_MAX_LEN (17)
#define ABV_SC_LABEL_MAX_LEN (8)
#define ABV_SC_NAME_MAX_LEN (5)
#define ABV_SC_AREA_MAX_LEN (4)
#define ABV_SUBTITLE_MAX_LEN (1024)
#define ABVCA_MAX_LABEL_LEN (16)
#define ABVCA_MAX_PIN_LEN (14)
#define ABVCA_ProviderPPID_MAX (16)
#define ABVCA_ProviderLABEL_MAX (16)

/**< ABV CA Flash区域配置 主区域和备份区域*/
typedef struct
{
	unsigned int unMainFlashAddr;
	unsigned int unMainFlashLen;
	unsigned int unBackupFlashAddr;
	unsigned int unBackupFlashLen;
}ADIAbvFlash_S;

/**< ABV日期结构 */
typedef struct
{
	unsigned short usYear; // %d 显示
	unsigned char ucMonth; // %d 显示
	unsigned char ucDay; // %d 显示
	unsigned char ucHour; // %02x 显示
	unsigned char ucMinute; // %02x 显示
}ADIAbvDate;

/**< 邮件头信息 */
typedef struct
{
	unsigned char ucReadStatus; // 0:unreaded  1:readed
	unsigned short usMailLen;
	unsigned int unMailID; // 邮件ID
	ADIAbvDate stMailDate;
	unsigned char ucSenderLen;
	unsigned char ucSenderName[20];
	unsigned char ucTitleLen;
	unsigned char ucTitleName[50];
}ADIAbvMailHead_S;

/**< 邮件内容 */
typedef struct
{
	unsigned char  ucMailContent[MAX_MAIL_SIZE];/*注意第一个字节为编码类型, 第2个字节开始才是内容*/
	unsigned short unMailLen;
}ADIAbvMailContent_S;

/**< 智能卡信息结构体 */
typedef struct
{
	unsigned char aucLabel[ABV_SC_LABEL_MAX_LEN];/*字符串%s打印*/
	unsigned char aucName[ABV_SC_NAME_MAX_LEN];/*字符串%s打印*/
	unsigned char ucVersion;
	unsigned char ucAdultlevel;
	unsigned char aucArea[ABV_SC_AREA_MAX_LEN]; /* 转化为32bit 数值后格式化为%05d显示*/
	unsigned char ucPaired; //0:notPaired
	unsigned char ucStartHour;
	unsigned char ucStartMinute;
	unsigned char ucEndHour;
	unsigned char ucEndMinute;
	unsigned char ucIsChildSC; //1:子卡  0:母卡
	unsigned char ucCardNum[ABV_SC_MAX_LEN]; /*字符串%s打印*/
	unsigned char ucMasterCardNum[ABV_SC_MAX_LEN];/*字符串%s打印*/
}ADIAbvSCInfo_S;

/**< IPPV信息
IPPV_info[0].ucIPPV_Type 不为0xff时，current ippv info 是可用的。 IPPV_info[1].ucIPPV_Type 不为0xff时，next_ippv_info是可用的
*/
typedef struct
{
	unsigned char	ucIPPV_Type;/* 1 Pay per minute  2 Pay per View  0 Both types can be chosen by users*/
	unsigned int 	unIPPV_Time_Price;/*price of pay per minute --long int---*/
	unsigned int	unIPPV_View_Price;/*price of pay per view ---long int---*/
	unsigned char	aucIPPV_Name[24];/*Program instrction*/
	ADIAbvDate  	stPro_Start_Time;/*Start time*/
	ADIAbvDate  	stPro_End_Time;/*Finish time*/
	unsigned short  usIPPV_ID;
}ADIAbvIPPV_S;

/**< ABVCA第三方库调试输出 */
typedef enum
{
	E_ALL_Mesg = 0,  /*CAK显示所有的调试信息*/
	E_ERR_Mesg = 1,  /*CAK只显示错误的调试信息*/
	E_DEBUG_Mesg = 2, /*CAK只显示正确的调试信息*/
	E_NO_Mesg = 3,    /*CAK内核不显示任何信息*/
}ADIAbvPrintMode_E;

/**< 卡操作相关错误 */
typedef enum
{
	eResult_CARD_OK,
	eResult_CARD_PIN_ERROR,
	eResult_CARD_PIN_LOCK,
	eResult_CARD_PIN_NO_MATCH,
	eResult_CARD_MR_ERROR,
	eResult_CARD_WT_ERROR,
	eResult_CARD_IPPV_ERROR,
	eResult_CARD_NO_ENOUGH_TOKENS,
	eResult_CARD_OUT_ERROR,
	eResult_CARD_TYPE_ERROR,
	eResult_CARD_OTHER_ERROR,
	eResult_MAX
}ADIAbvResult_E;

/**< IPPV授权历史信息 */
typedef struct
{
	unsigned int unIPPVEntitletokens;
	ADIAbvDate stIPPVEntitletime;
}ADIAbvIPPVHistRecordInfo_S;

/**< 节目授权类型 */
typedef enum
{
	ePPID_FREE_ENTITLE,/*free entitlement*//*显示时只显示lable 和开始结束时间即可，并且时间不需要显示小时和分钟*/
	ePPID_PPC_ENTITLE,/*PPC entitlement*//*结构中的信息均需要显示*/
	ePPID_PPV_ENTITLE/*PPV entitlement*//*结构中的信息均需要显示*/
}ADIAbvPPIDEntitleType_E;

/**< 节目授权信息 */
typedef struct
{
	unsigned short usLinkID;/*Packet ID*/
	unsigned char aucLabel[ABVCA_MAX_LABEL_LEN];/*Packet name*/
	unsigned char ucPayState; /*0	Already paid	1,2 Paid by time  3  Paid by prog  4 Have not paid */
	ADIAbvDate stNDate;/*Send time*/
	ADIAbvDate stSDate;/*Start time*/
	ADIAbvDate stEDate;/*End time*/
}ADIAbvEntitleInfo_S;

/**< 节目供应商信息 */
typedef struct
{
	unsigned char aucProvider_PPID[ABVCA_ProviderPPID_MAX];/*运营商PPID*/
	unsigned char aucProvider_Lable[ABVCA_ProviderLABEL_MAX];/*运营商Lable*/
	unsigned int unBalance;
}ADIAbvProviderInfo_S;

typedef enum
{
	E_MC_HAIR = 1,
	E_MC_GX = 2,
	E_MC_MATSR = 3,
	E_MC_ALI = 4,
	E_MC_MONTAGE = 5,
	E_MC_MAX
}MCode_E;
/*
 * Description: 设置CA的flash主区域和备份区域
 *
 * Parameters : 
 *				输入参数
 *					pstNvm CA的flash主区域和备份区域信息
 *                  pstSecurityNvm  CA Security flash主区域和备份区域信息
 *
 *				输出参数
 *					无
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_SetFlashAddress(ADIAbvFlash_S *pstNvm, ADIAbvFlash_S *pstSecurityNvm);

/*
 * Description: 获取邮箱内邮件总数
 *
 * Parameters : 
 *				输入参数
 *					无
 *
 *				输出参数
 *					*pucNum 邮件总数
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetMailTotalNum(unsigned char *ucNum);

/*
 * Description: 获取邮箱未读邮件总数
 *
 * Parameters : 
 *				输入参数
 *					无
 *
 *				输出参数
 *					*pucNum 未读邮件总数
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetNewMailNum(unsigned char *pucNum);

/*
 * Description: 获取一封邮件的头信息
 *
 * Parameters : 
 *				输入参数
 *					nIndex 邮件索引 从0开始
 *
 *				输出参数
 *					pstMailHead 邮件的头信息
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetMailHead(unsigned char ucIndex, ADIAbvMailHead_S *pstMailHead);

/*
 * Description: 获取一封邮件内容
 *
 * Parameters : 
 *				输入参数
 *					nIndex 邮件索引 从0开始
 *
 *				输出参数
 *					pstMailContent 邮件内容
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetMailContent(int nIndex, ADIAbvMailContent_S *pstMailContent); 

/*
 * Description: 删除一封邮件
 *
 * Parameters : 
 *				输入参数
 *					nIndex 邮件索引 从0开始
 *
 *				输出参数
 *					void
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_DeleteMailByIndex(int nIndex); 

/*
 * Description: 清除邮件区域flash数据-------debug使用
 *
 * Parameters : 
 *				输入参数
 *					void
 *
 *				输出参数
 *					void
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_ClearMailAddr(void);

/*
 * Description: 获取ABV生产工具烧写后的STBID
 *
 * Parameters : 
 *				输入参数
 *                   ucSTBID 内存buffer
 *				输出参数
 *                   无
 * Note: buffer空间请传32
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetSTBID(unsigned char ucSTBID[32]);

/*
 * Description: 获取智能卡信息
 *
 * Parameters : 
 *				输入参数
 *                   无
 *				输出参数
 *					*pstSCInfo 卡信息
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetSmcInfo(ADIAbvSCInfo_S * pstSCInfo);

/*
 * Description: 设置第三方ABVCA库的打印-------debug使用
 *
 * Parameters : 
 *				输入参数
 *					eMode: 详细见ADIAbvPrintMode_E的描述
 *
 *				输出参数
 *					void
 *
 * Returns	  :  void
 */
void ADI_Abv_SetCaKPrintMode(ADIAbvPrintMode_E eMode);

/*
 * Description: 当节目为成人级或者IPPV节目时，不观看或者返回出错的情况下调用此接口
 *
 * Parameters : 
 *				输入参数
 *					ucFlag:1 用户主动退出密码输入菜单不观看节目--不再提示节目菜单
 *					       0 用户输入了密码但是出错了--还会再提示节目菜单要求输入密码
 *				输出参数
 *					*pucResetNum 密码可重试次数
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_CancelWatchProgram(unsigned char ucFlag);


/*
 * Description: 观看成人级节目，用户输入密码之后调用此接口
 *
 * Parameters : 
 *				输入参数
 *					pucPIN 智能卡的密码
 *					ucPINLen 密码长度
 *				输出参数
 *					*pucResetNum 密码可重试次数
 *
 * Note: 用户需要收看成人级节目时调用，密码错误的时候需要提示用户还有几次的重试机会，
 *       密码最多可重试15次。输入正确密码后，可重试次数还原
 *
 * Example: 用户输入PIN码时，例如: PIN码是4位的1234, 用户输入1234后，
 *          CA会记录PIN[0]=1,PIN[1]=2,PIN[2]=3,PIN[3]=4,PIN_LEN =4(打印数据时输出方式是%d)
 *
 * Returns: 参考ADIAbvResult_E
 */
ADIAbvResult_E ADI_Abv_WatchMRProgram(unsigned char* pucPIN, unsigned char ucPINLen, unsigned char *pucResetNum);

/*
 * Description: 用户需要收看IPPV节目时调用
 *
 * Parameters : 
 *				输入参数
 *					pucPIN 智能卡的密码
 *					ucPINLen 密码长度
 *					ucPayType 付费类型 1表示按时间付费，2表示按次付费
 *					ucIndex 节目序号 0表示当前节目，1表示下一个节目
 *				输出参数
 *					*pucResetNum 密码可重试次数
 *
 * Note: 购买IPPV节目,用户输入密码后调用此接口
 *       密码最多可重试5次。输入正确密码后，可重试次数还原,密码的最大长度为14位
 *
 * Example: 用户输入PIN码时，例如: PIN码是4位的1234, 用户输入1234后，
 *          CA会记录PIN[0]=1,PIN[1]=2,PIN[2]=3,PIN[3]=4,PIN_LEN =4(打印数据时输出方式是%d)
 *
 * Returns: 参考ADIAbvResult_E
 */
ADIAbvResult_E ADI_Abv_WatchIPPVProgram(unsigned char* pucPIN, unsigned char ucPINLen, unsigned char ucPayType, unsigned char ucIndex, unsigned char *pucResetNum);

/*
 * Description: 获得某个供应商的购买IPPV或给智能卡充值的历史信息的总数
 *
 * Parameters : 
 *				输入参数
 *					ucPPIDNO 需要获得的哪个PPID的购买信息,编号从0开始
 *				输出参数
 *					*pusNumofRecord 历史信息的总数
 *
 * Note: STB显示消费和充值历史时调用，用户根据PPID的序号获得当前PPID的消费
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetHistRecordTotal(unsigned char ucPPIDNO, unsigned short *pusNumofRecord);

/*
 * Description: 获得某个供应商的某条消费或充值历史纪录
 *
 * Parameters : 
 *				输入参数
 *					ucPPIDNO 需要获得的哪个PPID的购买信息,编号从0开始
 *					usRecordNO 历史纪录信息的编号,从0开始
 *				输出参数
 *					*psIPPVHistoryInfo 历史纪录信息的内容
 *
 * Note: STB显示消费和充值历史时调用,用户根据PPID的序号获得当前PPID的消费和充值的历史信息
 *
 * Returns	  :  0 成功
 *				-1 失败 
 */
int ADI_Abv_GetHistRecordInfo(unsigned char ucPPIDNO, unsigned short usRecordNO, ADIAbvIPPVHistRecordInfo_S *psIPPVHistoryInfo);

/*
 * Description: 获得当前智能卡内的运营商数量,供应商的最大数量为3
 *
 * Parameters : 
 *				输入参数
 *					无
 *				输出参数
 *					*pucProviderNum 运营商数量
 *
 * Note: 当用户需要观看供应商的信息时调用,主要为集成厂商提供供应商的总数,以便于集成厂商根据此信息,显示详细的供应商信息 
 *
 * Returns	  :  0 成功
 *				-1 失败	
 */
int ADI_Abv_GetProviderTotal(unsigned char * pucProviderNum);

/*
 * Description: 得到一个特定节目供应商的信息
 *
 * Parameters : 
 *				输入参数
 *					ucPPIDNO 节目供应商的序号,从0开始
 *				输出参数
 *					*pstProviderInfo 指向节目供应商信息的指针
 *
 * Note: 显示节目供应商的信息时调用，集成厂商需要将供应商的具体信息显示在界面上，包括PPID、供应商名称、余额信息
 *
 * Returns	  :  0 成功
 *				-1 失败	
 */
int ADI_Abv_GetProviderInfo(unsigned char ucPPIDNO, ADIAbvProviderInfo_S* pstProviderInfo);

/*
 * Description: 用户修改智能卡的工作时间时调用
 *
 * Parameters : 
 *				输入参数
 *					pucPinCode PIN码
 *					ucPinLen PIN码长度
 *					ucStartTime_H 开始时间-时
 *					ucStartTime_M 开始时间-分
 *					ucEndTime_H 结束时间-时
 *					ucEndTime_M 结束时间-分
 *				输出参数
 *					*pucRetryTimes 还剩下几次重试机会
 *
 * Note: 工作时段为 00:00 --  23:59
 *       密码最多可重试15次。输入正确密码后，可重试次数还原,密码的最大长度为14位
 *
 *
 * Example: 用户输入PIN码时，例如: PIN码是4位的1234, 用户输入1234后，
 *          CA会记录PIN[0]=1,PIN[1]=2,PIN[2]=3,PIN[3]=4,PIN_LEN =4(打印数据时输出方式是%d)
 *          当开始时间时12:14 结束时间时18:58,那么ucStartTime_H=12, ucStartTime_M=14, ucEndTime_H=18, ucEndTime_M=58,
 *
 * Returns: 参考ADIAbvResult_E
 *			
 */
ADIAbvResult_E ADI_Abv_SetWorkTime(unsigned char *pucPinCode, unsigned char ucPinLen, unsigned char ucStartTime_H, unsigned char ucStartTime_M, 
						       unsigned char ucEndTime_H, unsigned char ucEndTime_M, unsigned char *pucRetryTimes);

/*
 * Description: 用户修改智能卡的成人级时调用
 *
 * Parameters : 
 *				输入参数
 *					pucPinCode PIN码
 *					ucPinLen PIN码长度
 *					ucRate 成人级别
 *				输出参数
 *					*pucRetryTimes 还剩下几次重试机会
 *
 * Note: 输入智能卡密码和新的成人级,如果密码正确,智能卡上的成人级改变;如果密码错误,提示用户还有几次重试机会.
 *       密码最多可重试15次。输入正确密码后，可重试次数还原,密码的最大长度为14位
 *       成人级级别(6~21岁以及No Restriction)
 *       建议集成时No Restriction的值设为22, 大于22岁或者小于6岁代表成人级无效.
 *
 *
 * Example: 用户输入PIN码时，例如: PIN码是4位的1234, 用户输入1234后，
 *          CA会记录PIN[0]=1,PIN[1]=2,PIN[2]=3,PIN[3]=4,PIN_LEN =4(打印数据时输出方式是%d)
 *
 * Returns: 参考ADIAbvResult_E
 *			
 */
ADIAbvResult_E ADI_Abv_SetAdultlevel(unsigned char *pucPinCode, unsigned char ucPinLen, unsigned char ucRate, unsigned char *pucRetryTimes);

/*
 * Description: 修改智能卡的PIN码
 *
 * Parameters : 
 *				输入参数
 *					pucOldPin 旧PIN码
 *					ucOldPinLen 旧PIN码长度
 *					pucNewPin 新PIN码
 *					ucNewPinLen 新PIN码长度
 *					pucMatchPin 确认的新PIN码
 *					ucMatchPinLen 确认的新PIN码长度
 *				输出参数
 *					*pucRetryTimes 还剩下几次重试机会
 *
 * Note: 输入密码错误时需要提示用户还有几次重试机会,密码最多可重试15次,输入正确密码后,可重试次数还原
 *       当机顶盒用户修改PIN码时调用，用户需要根据不同的返回状态，显示相应的状态信息。密码的最大长度为14位
 *       修改智能卡的PIN码，需要输入两次新的密码，以确定输入的新密码正确
 *
 * Example: 用户输入PIN码时，例如: PIN码是4位的1234, 用户输入1234后，
 *          CA会记录PIN[0]=1,PIN[1]=2,PIN[2]=3,PIN[3]=4,PIN_LEN =4(打印数据时输出方式是%d)
 *
 * Returns: 参考ADIAbvResult_E
 *			
 */
ADIAbvResult_E ADI_Abv_ChangePin(unsigned char *pucOldPin, unsigned char ucOldPinLen, unsigned char *pucNewPin, unsigned char ucNewPinLen,
						  unsigned char *pucMatchPin, unsigned char ucMatchPinLen, unsigned char *pucRetryTimes);
/*
 * Description: 得到当前供应商, 当前授权类型的某个授权的内容
 *
 * Parameters : 
 *				输入参数
 *					ucPPIDNO 节目供应商的序号，从0开始
 *					usEntitleINO  需要获得第几个授权的序号，编号从0开始
 *					ePPIDEntitleType 授权信息的类型分为三种:Free、PPC、PPV 详细见ADIAbvPPIDEntitleType_E
 *				输出参数
 *					*pstServiceEntitles 运营商授权信息
 *
 * Note: 用户阅读授权信息时调用, Free Entitle只存在开始和结束时间,并且最小单位为天,无授权时间和LinkID
 *
 * Returns	  :  0 成功
 *				-1 失败
 */
int ADI_Abv_GetServiceEntitles(unsigned char ucPPIDNO, unsigned short usEntitleINO, ADIAbvPPIDEntitleType_E ePPIDEntitleType, ADIAbvEntitleInfo_S* pstServiceEntitles);

/*
 * Description: 得到一个特定运营商的某类授权的信息的授权总数(用户显示的时候可根据提供的授权数量做分页显示)
 *
 * Parameters : 
 *				输入参数
 *					ucPPIDNO 节目供应商的序号，从0开始
 *					ePPIDEntitleType 授权信息的类型分为三种:Free、PPC、PPV 详细见ADIAbvPPIDEntitleType_E
 *				输出参数
 *					*pusNum 某类授权的信息的授权总数
 *
 * Note: 用户需要获得授权信息前，调用此接口得到当前供应商的授权总数
 *
 * Returns	  :  0 成功
 *				-1 失败
 */
int ADI_Abv_GetServiceEntitlesTotal(unsigned char ucPPIDNO, ADIAbvPPIDEntitleType_E ePPIDEntitleType, unsigned short* pusNum);

/*
 * Description: 获取ABVCA库版本信息
 *
 * Parameters : 
 *				输入参数
 *					
 *				输出参数
 *					*pusVersion: 版本号 %04x显示
 *					*paucBuildDate: 编译日期 建议分配64字节 %s显示
 *					*paucBuildTime: 编译时间 建议分配64字节 %s显示
 *
 * Note: 
 *
 * Returns	  : VOID 
 *				
 */
void ADI_Abv_GetCALibVersion(unsigned short* pusVersion, unsigned char *paucBuildDate, unsigned char *paucBuildTime);

/*
 * Description: 获取ABVCA UA信息
 *
 * Parameters : 
 *				输入参数
 *					
 *				输出参数
 *					aucUA: 5个字节的UA,每个字节建议按照%02x输出
 *
 * Note: 
 *
 * Returns	  : VOID 
 *				
 */
void ADI_Abv_GetUA(unsigned char aucUA[5]);

/*
 * Description: 获取是否有全屏消息在显示, 如果有全屏消息就不响应除待机键,上下翻页键之外的任何按键
 *
 * Parameters : 
 *				输入参数  无
 *					
 *				输出参数  无
 *
 * Note: 
 *
 * Returns	  : 1 全屏消息在显示中;    0当前没有全屏消息
 *				
 */
int ADI_Abv_FullScreenMsgIsOn(void);

/*
 * Description: 进菜单
 *
 * Parameters : 
 *				输入参数  无
 *					
 *				输出参数  无
 *
 * Note: 
 *
 * Returns	  : 
 *				
 */
void ADI_Abv_EnterMenu(void);

/*
 * Description: 出菜单
 *
 * Parameters : 
 *				输入参数  无
 *					
 *				输出参数  无
 *
 * Note: 
 *
 * Returns	  : 
 *				
 */
void ADI_Abv_ExitMenu(void);

#ifdef  __cplusplus
}
#endif

#endif

