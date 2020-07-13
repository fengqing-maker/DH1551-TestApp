#include "adi_typedef.h"
#include "adi_os.h"
#ifndef _TF_INTERFACE_H_
#define _TF_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum
{
	TF_ALARM,
	TF_COMMAND,
	TF_STATUS,
	TF_MAX
}ADITFMsgType_E;

typedef enum 
{
	TF_ALARM_CANCEL = 0, /* 取消当前的显示 */
	TF_ALARM_BADCARD = 1, /* 无法识别卡 */
	TF_ALARM_EXPICARD = 2, /* 智能卡过期，请更换新卡 */
	TF_ALARM_INSERTCARD = 3, /* 加扰节目，请插入智能卡 */
	TF_ALARM_NOOPER = 4, /* 不支持节目运营商 */
	TF_ALARM_BLACKOUT = 5, /* 条件禁播 */
	TF_ALARM_OUTWORKTIME = 6, /* 当前时段被设定为不能观看 */
	TF_ALARM_WATCHLEVEL = 7, /* 节目级别高于设定的观看级别 */
	TF_ALARM_PAIRING = 8, /* 智能卡与本机顶盒不对应 */
	TF_ALARM_NOENTITLE = 9, /* 没有授权 */
	TF_ALARM_DECRYPTFAIL = 10, /* 节目解密失败 */
	TF_ALARM_NOMONEY = 11, /* 卡内金额不足 */
	CA_ALARM_ERRREGION = 12, /* 区域不正确 */
	TF_ALARM_NEEDFEED_TYPE = 13, /* 子卡需要和母卡对应，请插入母卡 */		
	TF_ALARM_ERRCARD_TYPE = 14,	/* 智能卡校验失败，请联系运营商 */
	TF_ALARM_UPDATE_TYPE = 15,	 /* 智能卡升级中，请不要拔卡或者关机 */	
	TF_ALARM_LOWCARDVER_TYPE = 16, /* 请升级智能卡 */
	TF_ALARM_VIEWLOCK_TYPE = 17, /* 请勿频繁切换频道 */
	TF_ALARM_MAXRESTART_TYPE = 18, /* 智能卡暂时休眠，请5分钟后重新开机 */
	TF_ALARM_FREEZE_TYPE = 19,	/* 智能卡已冻结，请联系运营商 */
	TF_ALARM_CALLBACK_TYPE = 20,  /* 智能卡已暂停，请回传收视记录给运营商 */
	TF_ALARM_CURTAIN_CANNOTPREVIEW = 21, /*高级预览节目，该阶段不能免费观看*/
	TF_ALARM_CARDUPGRADING = 22, /*升级测试卡测试中...*/
	TF_ALARM_CARDUPGRADE_FAIL = 23, /*升级测试卡测试失败，请检查机卡通讯模块*/
	TF_ALARM_CARDUPGRADE_SUCCESS = 24, /*升级测试卡测试成功*/
	TF_ALARM_NOOPER_INCARD = 25, /*卡中不存在移植库定制运营商*/
	TF_ALARM_STBLOCKED_TYPE = 26, /* 请重启机顶盒 */
	TF_ALARM_STBFRESS = 27, /* 机顶盒被冻结 */
	TF_ALARM_UNSUPPORTDEVICE = 28, /*不支持的终端类型（编号：0xXXXX）*/
	TF_ALARM_SRV_OTHER = 41,// 其它CA加扰节目
	TF_AMARM_MAX
}ADITFMsgAlarm_E;

typedef enum
{
	OSD_MODE_MIDDLE,	
	OSD_MODE_TOP,        
	OSD_MODE_BOTTOM,
	OSD_MODE_SUPER,
	OSD_MODE_DEFAULT
}OSD_DisplayMode_E;
/*
* 特此说明:
* 		如下命令类型都是消息通知类型接口,机顶盒收到消息后应立即返回
*		禁止在该接口中直接调用CA相关接口处理,否则会导致信号量死锁!!!
* 		例如,对于IPPV节目通知命令TF_COMMAND_IPPV_NOTIFY, 不能直接调用购买接口ADI_TF_SetIPPVBuyDlg()
*/
typedef enum 
{
    TF_COMMAND_EMAIL_ICONHIDE=0,	/* 隐藏邮件通知图标 */
 	TF_COMMAND_EMAIL_NEW,			/* 新邮件通知，显示新邮件图标 */
 	TF_COMMAND_EMAIL_SPACEEXHAUST,	/* 磁盘空间已满，显示图标闪烁*/	
	TF_COMMAND_ENTITLE_CHANGE,		/* 通知机顶盒某个运营商的授权发生变化*/
	TF_COMMAND_DETITLE_NOTIFY,		/* 更新反授权确认码空间的状态提示 ,对应ADITFDetitleStatus_E*/
	TF_COMMAND_LOCK_SERVICE,		/* 强制切换到指定频道接受节目并锁定键盘和遥控器,暂时禁止切换频道 */
	TF_COMMAND_UNLOCK_SERVICE,		/* 解除对键盘和遥控器的锁定,允许用户切换频道 */
	TF_COMMAND_IPPV_NOTIFY,			/* 收看IPPV 节目时,通过机顶盒界面通知用户,由用户选择是否购买 */
	TF_COMMAND_IPPV_CANCEL,			/* 隐藏当前IPPV 对话框; 说明:如果用户对IPPV通知对话框没有进行任何操作,则IPPV 对话框的隐藏由CA控制;如果用户对通知对话框做出选择(比如购买或不购买此IPPV节目),则该对话框的隐藏由机顶盒控制*/
	TF_COMMAND_PAIR_NEED_CHILD, 	/* 读取喂养数据成功, 可以插入子卡进行喂养,提示"请插入子卡" 5s后提示消失*/
	TF_COMMAND_PAIR_READDATA_FAIL, 	/* 读取喂养数据失败, 提示"读取喂养数据失败" 5s后提示消失*/
	TF_COMMAND_SHOW_FINGERMSG,		/* 显示或取消指纹*/
	TF_COMMAND_SHOW_PROGRESS,		/* 显示或取消相应进度条提示消息 */
	TF_COMMAND_SHOW_OSDMSG,			/* 显示或取消OSD 消息*/
	TF_COMMAND_ACTION_REQUEST,		/* 显示或取消通知, 根据行为类型不同作相应处理,参见ADITFActionRequestType_E*/
	TF_COMMAND_CURTAIN_NOTIFY,		/* 显示或取消当前节目高级预览消息,对应ADITFCurtainType_E 中高级预览状态码*/
	TF_COMMAND_CONTINUEWATCH_LIMIT,	/* 连续观看限制通知*/
	TF_COMMAND_UPDATEFAC,   		/*更新fac值*/
	TF_COMMAND_MAX
}ADITFMsgCommand_E;


#define TONGFANG_RC_OK                    0x00  /* 成功 */
#define TONGFANG_RC_UNKNOWN               0x01  /* 未知错误 */
#define TONGFANG_RC_POINTER_INVALID       0x02  /* 指针无效 */
#define TONGFANG_RC_CARD_INVALID          0x03  /* 智能卡无效 */
#define TONGFANG_RC_PIN_INVALID           0x04  /* PIN码无效 */
#define TONGFANG_RC_DATASPACE_SMALL       0x06  /* 所给的空间不足 */
#define TONGFANG_RC_CARD_PAIROTHER        0x07  /* 智能卡已经对应别的机顶盒 */
#define TONGFANG_RC_DATA_NOT_FIND         0x08  /* 没有找到所要的数据 */
#define TONGFANG_RC_PROG_STATUS_INVALID   0x09  /* 要购买的节目状态无效 */
#define TONGFANG_RC_CARD_NO_ROOM          0x0A  /* 智能卡没有空间存放购买的节目 */
#define TONGFANG_RC_WORKTIME_INVALID      0x0B  /* 设定的工作时段无效 */
#define TONGFANG_RC_IPPV_CANNTDEL         0x0C  /* IPPV节目不能被删除 */
#define TONGFANG_RC_CARD_NOPAIR           0x0D  /* 智能卡没有对应任何的机顶盒 */
#define TONGFANG_RC_WATCHRATING_INVALID   0x0E  /* 设定的观看级别无效 */
#define TONGFANG_RC_CARD_NOTSUPPORT       0x0F  /* 当前智能卡不支持此功能 */
#define TONGFANG_RC_DATA_ERROR            0x10  /* 数据错误，智能卡拒绝 */
#define TONGFANG_RC_FEEDTIME_NOT_ARRIVE   0x11  /* 喂养时间未到，子卡不能被喂养 */
#define TONGFANG_RC_CARD_TYPEERROR        0x12  /* 子母卡喂养失败，插入智能卡类型错误 */

#define TONGFANG_RC_CAS_FAILED            0x20  /* 发卡cas指令执行失败 */
#define TONGFANG_RC_OPER_FAILED           0x21  /* 发卡运营商指令执行失败 */
#define TONGFANG_RC_UNSUPPORT             0x22  /* 不支持 */
#define TONGFANG_RC_LEN_ERROR             0x23  /* 长度错误 */
#define TONGFANG_RC_SCHIP_ERROR           0x24  /* 安全芯片设置错误 */


/*---------- 机顶盒通知行为类型: Undefined ADITFActionRequestType_E -----------*/
#define	TF_ACTIONREQUEST_RESTARTSTB			0	/* 重启机顶盒 */
#define	TF_ACTIONREQUEST_FREEZESTB			1	/* 冻结机顶盒 */
#define TF_ACTIONREQUEST_SEARCHCHANNEL		2	/* 重新搜索节目 */
#define TF_ACTIONREQUEST_STBUPGRADE			3	/* 机顶盒程序升级 */
#define TF_ACTIONREQUEST_UNFREEZESTB		4 	/* 解除冻结机顶盒 */
#define TF_ACTIONREQUEST_INITIALIZESTB		5	/* 初始化机顶盒 */
#define TF_ACTIONREQUEST_SHOWSYSTEMINFO		6	/* 显示系统信息 */
//#define TF_ACTIONREQUEST_OTHERS		/* 7-200时的定义由运营商指定 */
#define TF_ACTIONREQUEST_DISABLEEPGADINFO	201		/* 禁用EPG广告信息功能 */
#define TF_ACTIONREQUEST_ENABLEEPGADINFO	202		/* 恢复EPG广告信息功能 */
//#define TF_ACTIONREQUEST_RESERVED,	/* 未定义的行为类型, 暂做保留*/
#define TF_ACTIONREQUEST_CARDINSERTFINISH	255   /* 插卡处理完成 */


/*---------- 反授权确认码状态相关定义 --------*/
typedef enum
{
	TF_DETITLE_ALLREAD = 0x00,	/* 所有反授权确认码已经被读，隐藏图标 */
	TF_DETITLE_RECEIVED = 0x01,	/* 收到新的反授权码，显示反授权码图标 */
	TF_DETITLE_SPACESMALL = 0x02,  /* 反授权码空间不足，改变图标状态提示用户 */
	TF_DETITLE_IGNORE = 0x03,  /* 收到重复的反授权码，可忽略，不做处理 */
	TF_DETITLE_MAX
}ADITFDetitleStatus_E;

#define TF_CURTAIN_BASE		0x0000	/*高级预览状态码基础值,高字节编码0x00*/
typedef enum
{
	TF_CURTAIN_CANCLE = (TF_CURTAIN_BASE+0x00),		/*取消高级预览显示*/
	TF_CURTAIN_OK = (TF_CURTAIN_BASE+0x01),  		/*高级预览节目正常解密*/
	TF_CURTAIN_TOTTIME_ERROR = (TF_CURTAIN_BASE+0x02),		/*高级预览节目禁止解密：已经达到总观看时长*/
	TF_CURTAIN_WATCHTIME_ERROR = (TF_CURTAIN_BASE+0x03),	/*高级预览节目禁止解密：已经达到WatchTime限制*/
	TF_CURTAIN_TOTCNT_ERROR = (TF_CURTAIN_BASE+0x04),	/*高级预览节目禁止解密：已经达到总允许观看次数*/
	TF_CURTAIN_ROOM_ERROR = (TF_CURTAIN_BASE+0x05),		/*高级预览节目禁止解密：高级预览节目记录空间不足*/
	TF_CURTAIN_PARAM_ERROR = (TF_CURTAIN_BASE+0x06), 	/*高级预览节目禁止解密：节目参数错误*/
	TF_CURTAIN_TIME_ERROR = (TF_CURTAIN_BASE+0x07),		/*高级预览节目禁止解密：数据错误*/
	TF_CURTAIN_MAX
}ADITFCurtainType_E;

typedef enum 
{
	TF_STATUS_CARD_IN=0,// Succeed to initialize smart card 
	TF_STATUS_CARD_OUT=1,// No smart card 
	TF_STATUS_CARD_ERROR=2,// Failed to initialize smart card 
	TF_STATUS_SC_PIN_RESET=3,//Succeed in modifying PIN 
	TF_STATUS_STB_SC_PAIRED=4,// Succeed in pairing smart card and STB 
	TF_STATUS_STB_SC_FREE_PAIRED=5,//Succeed in depairing smart card and 
	TF_STATUS_STB_SC_PAIRED_FAILED=6,//Fail to pair smart card and STB
}ADITFMsgStatus_E;

typedef enum
{
	TFCA_EMAIL_READSTATUS_ASC = 0, // 未读邮件在后,已读邮件在前
	TFCA_EMAIL_READSTATUS_DESC = 1, // 未读邮件在前,已读邮件在后
	TFCA_EMAIL_TIME_ASC = 2, // 后接收的邮件在后,先接收的邮件在前
	TFCA_EMAIL_TIME_DESC = 3, // 后接收的邮件在前,后接收的邮件在后
	TFCA_EMAIL_COMSTATUS_ASC = 4, // 
	TFCA_EMAIL_COMSTATUS_DESC = 5, //
	TFCA_EMAIL_SORT_MAX
}TFCAEmailSortStyle_E;

#define MAX_OSD_LEN (256)

/**< TF CA Flash区域配置 主区域和备份区域*/
typedef struct
{
	unsigned int unMainFlashAddr_A;
	unsigned int unMainFlashLen_A;
	unsigned int unBackupFlashAddr_A;
	unsigned int unBackupFlashLen_A;
	
	unsigned int unMainFlashAddr_B;
	unsigned int unMainFlashLen_B;
	unsigned int unBackupFlashAddr_B;
	unsigned int unBackupFlashLen_B;
}TFCaFlash_S;

#define MAIL_CONTENT_MAX_LEN (256)
typedef struct
{
	char m_acEmailContent[MAIL_CONTENT_MAX_LEN];
}TFCAEmailContent_S;

#define MAX_EMAIL_NUM (100)
#define MAX_EMAIL_TITLE_LEN (64)

typedef struct
{
	unsigned int m_dwYear;
	unsigned int m_dwMonth;
	unsigned int m_dwDay;
	unsigned int m_dwHour;
	unsigned int m_dwMinute;
	unsigned int m_dwSecond;
}TFCaDate_S;

typedef struct
{
	unsigned int m_dwEmailID; // Email ID
	unsigned char m_cNewEmail; // 新邮件标记：0－已读邮件；1－新邮件 
	unsigned short m_wImportance; // 重要性： 0－普通，1－重要
	TFCaDate_S m_dwCreateTime; // EMAIL创建的时间
	char m_acEmailHead[MAX_EMAIL_TITLE_LEN]; // 邮件标题 
}TFCaEmailHead_S;

typedef enum
{
	E_PROGRESS_RECEIVEPATCH,/* 正在接收升级数据包CDCA_SCALE_RECEIVEPATCH, 标题: 数据包接收进度*/
	E_PROGRESS_PATCHING,	/* 正在升级智能卡CDCA_SCALE_PATCHING, 标题: 智能卡升级进度*/
	E_PROGRESS_RESERVED,	/* 保留类型, 暂时不做显示*/
}TFProgress_Type_E;

typedef struct
{
	unsigned char m_ucProgress;	/* 显示进度值, 0表示开始显示, 100表示相应操作已成功,大于100表示关闭或隐藏进度条显示*/
	TFProgress_Type_E m_eType;	/* 显示进度条类型*/
}TFCaPrggressStrip_S;

#define MAX_COMPONENT_NUM (5)	/* 节目组件最大个数 */

/*-- 节目组件信息 --*/
typedef struct
{
	unsigned short	m_wCompPID;		/* 组件PID */
	unsigned short	m_wECMPID;		/* 组件对应的ECM包的PID，如果组件是不加扰的，则应取0。 */
	unsigned char	m_ucCompType;	/* 组件类型*/
}TFCaComponent_S;

/*-- 频道参数信息 --*/
typedef struct
{	
	unsigned int	m_unFrequency;	/* 频率, 单位KHz*/
	unsigned int	m_unModulation;	/* 调制方式 */
	unsigned int	m_unSymbolrate;	/* 符号率*/
	unsigned int	m_unPcrPID;		/* PCR PID */
	unsigned char	m_ucFecOuter;	/* 前项纠错外码 */
	unsigned char	m_ucFecInner;	/* 前项纠错内码 */
	unsigned char	m_ucComponentNum;/* 节目组件个数 */
	TFCaComponent_S m_stComponent[MAX_COMPONENT_NUM];	/* 节目组件列表 */
}TFCaLockServiceParam_S;


typedef enum
{
	TFCA_IPPV_FREEVIEWED_SEGMENT = 0, 	/* IPPV 免费预览阶段，等待购买 */
	TFCA_IPPV_PAYVIEWED_SEGMENT = 1, 	/* IPPV 收费阶段，是否购买 */
	TFCA_IPPT_PAYVIEWED_SEGMENT = 2, 	/* IPPT 收费阶段，是否购买 ---> 注意:在IPPV节目购买提示框中,除了向用户说明该节目的单位时间价格外, 还应提示用户此节目为按时付费节目,收看过程中系统将自动扣费 */
	TFCA_IPPV_MAX_MSGTYPE
}TFCAIppvMsgType_E;

/*-- IPPV/IPPT节目的价格 --*/
typedef struct
{
	unsigned  char 	m_cPriceCode;/* 节目价格类型*/
	unsigned  short m_wPrice;	/* 节目价格（点数）*/
}TFCaPrice_S;

#define MAX_PRICE_NUM (2)	/* 最多的IPPV价格个数 */

/*-- IPPV/IPPT节目购买提示信息 --*/
typedef struct
{
	unsigned int 	m_wOperatorId;		/* 运营商ID */
	unsigned int 	m_cSlotID;			/* 钱包ID */
	unsigned int 	m_dwProductId;		/* 节目的ID */
	unsigned int 	m_dwRemainCredit;	/* 剩余点数, 等于信用度减去已花的点数*/
	TFCaDate_S	 	m_sExpiredDate;	/* IPPV 专用节目过期日期*/
	unsigned int 	m_wIntervalMin;	/* IPPT 专用的过期时间间隔, 单位分钟*/
	unsigned int 	m_cPriceNum;		/* 节目价格个数 , <= MAX_PRICE_NUM*/
	TFCaPrice_S 	m_stPrice[MAX_PRICE_NUM];	/* IPPV节目价格类型: 0－不可以录像; 1－可以录像, 参见CDCA_IPPVPRICETYPE_TPPVVIEW*/
}TFCaIppvProgram_S;

typedef struct
{
	TFCAIppvMsgType_E m_eMessageType;	/* 需要显示的IPPV 消息类型 */
	unsigned int	m_unEcmPid;			/* 对应的ECM PID, 提交购买时需要*/
	TFCaIppvProgram_S  m_stIppvProgram;	/* IPPV详细信息*/
}TFCaIppv_S;


typedef enum
{
	E_CARD_OUT,
	E_CARD_IN,
	E_CARD_ERROR
}SMC_Status_E;

typedef struct
{
	SMC_Status_E  m_eCardStatus;
	unsigned char  m_aucCardNum[32];	//sizeof(m_aucCardNum) >= CDCA_MAXLEN_SN+1
}TFCardInfo_S;

typedef struct
{
	unsigned int   m_unCAVer;
	unsigned char  m_aucCATypeStr[0x10];
}TFCAInfo_S;

typedef enum
{
	E_CARDPAIRED_OK,	/* 当前机卡对应 */
	E_CARDPAIRED_INVALID,		/* 检测不到有效智能卡 */
	E_CARDPAIRED_NOPAIR,		/* 智能卡没有对应任何的机顶盒,请设置机卡对应 */
	E_CARDPAIRED_PAIROTHER,	/* 智能卡已经对应其它机顶盒 */
	E_CARDPAIRED_MAX
}CardPaired_Status_E;

typedef struct
{
	unsigned char  m_ucListNum;		//Max value is 0x5
	unsigned char  m_aucSTBIDList[5][6];
}TFSTBIDListInfo_S;

typedef struct
{
	unsigned short m_unTVSID;		//Operator ID's Max Num == CDCA_MAXNUM_OPERATOR
	unsigned char  m_ucTVSPriInfo[32+1];	//CDCA_MAXLEN_TVSPRIINFO+1
}TFOperatorInfo_S;

/* 运营商信息列表*/
typedef struct
{
	unsigned int	 m_unOperatorNum;
    TFOperatorInfo_S m_sOperatorInfo[4];   /* 最多的运营商个数 为CDCA_MAXNUM_OPERATOR*/
}TFOperatorList;
typedef struct
{	
  	unsigned short m_unTVSID;
	unsigned int	m_unAreaCode;		/* 区域码*/
       unsigned int	m_unBouquetID;		/* Bouquet ID*/
	unsigned int  m_aunACArray[16]; 
}FACInfo_S;

typedef enum
{
   E_TF_FAC_MENU,
   E_TF_ENTILE_MENU,
   E_TF_DEFAUTL_MENU
}TF_MENU_E;

/*-- 授权信息 --*/
typedef struct
{
    unsigned int	m_unProductID;   /* 普通授权的节目ID */    
    unsigned short	m_usBeginDate;   /* 授权的起始时间 */
    unsigned short	m_usExpireDate;  /* 授权的过期时间 */
    unsigned char	m_ucCanTape;      /* 用户是否购买录像：1－可以录像；0－不可以录像 */
    unsigned char	m_ucReserved[3]; /* 保留 */
}TFSCDCAEntitle;

/*-- 授权信息集合 --*/
typedef struct
{
    unsigned short m_usProductCount;	
    unsigned char  m_ucReserved[2];    	/* 保留 */
    TFSCDCAEntitle m_sEntitleList[300]; /* 授权列表*/	//Max Num == CDCA_MAXNUM_ENTITLE
}TFEntitlesInfo;

/* 授权ID 列表*/
typedef struct
{
	unsigned int	m_unEntitleIDNum;
    unsigned int	m_aunEntitleIDList[300];   /* 授权产品的最大个数为CDCA_MAXNUM_ENTITLE*/
}TFEntitleIDList;

/* 用户特征*/
typedef struct
{
	unsigned int	m_unAreaCode;		/* 区域码*/
    unsigned int	m_unBouquetID;		/* Bouquet ID*/
    unsigned int	m_aunACArray[16];   /* 特征值列表,具体各数组的含义请与运营商联系 */
}TFACListInfo;

/* 钱包信息*/
typedef struct
{
	unsigned char m_ucSlotID;		/* 钱包ID */
    unsigned int  m_unCreditLimit;	/* 信用度（点数）*/
    unsigned int  m_unBalance;    	/* 已花的点数 */
}TFTVSSlotInfo;

/* 钱包信息列表*/
typedef struct
{
    unsigned int	m_unSlotNum;
    TFTVSSlotInfo	m_sSlotInfo[20]; /* 卡存储的最大钱包数为CDCA_MAXNUM_SLOT*/
}TFTVSSlotList;


/*-- IPPV节目信息 --*/
typedef struct
{
    unsigned int   m_unProductID;   /* 节目的ID */
    unsigned char  m_ucBookEdFlag;  /* 产品状态：BOOKING，VIEWED */ 
    unsigned char  m_ucCanTape;      /* 是否可以录像：1－可以录像；0－不可以录像 */
    unsigned short m_usPrice;        /* 节目价格 */
    unsigned short m_usExpiredDate;  /* 节目过期时间,IPPV用 */
    unsigned char  m_ucSlotID;      /* 钱包ID */
    unsigned char  m_ucReserved;    /* 保留 */
}TFIppvInfo;

/* IPPV 节目信息列表*/
typedef struct
{
	unsigned short m_wIPPVNum;
	TFIppvInfo	 m_sIPPVList[300]; /* 智能卡保存最多IPPV节目的个数为CDCA_MAXNUM_IPPVP*/
}TFIppvList;

typedef struct 
{
    unsigned char m_ucHour;
    unsigned char m_ucMinute;
    unsigned char m_ucSecond;
}TFWorkTime_S;

#define MAX_FINGERMSG_LEN	0x10	//17-1


/*
* 指纹显示信息说明: 参见超级指纹与超级OSD移植库接口变动说明文档
* 1. 任何时候屏幕上不应显示多于1个的指纹,所以每次要显示指纹之前都应该清除屏幕上次的显示
* 2. 若指纹区域超出显示界面, 需自动调整坐标保证指纹区域完全显示(如指纹坐标为99-99时指纹需在右下角完全显示)
* 3. 颜色值(0xAARRGGBB) 表示一个颜色的RGB值,其中0xAA无意义,0xRR表示R值, 0xGG表示G值, 0xBB表示B值
* 4. 当指纹要求强制显示时, 要求机顶盒在每轮显示期间锁屏,在每轮取消当前显示或从强制切换到非强制指纹显示时解除锁屏
* 5. 点阵指纹为隐性显示时, 机顶盒应使用插帧方式显示指纹,要求流中1分钟只有1帧指纹信息, 此时肉眼无法捕捉、需用专业设备分析
* 6. 点阵显示方案: 点阵为1个10*10均匀分布的点构成的正方形矩阵,最外层为只显示矩阵的4个顶点作为边界判断；
*	内部是8*8点阵表示要表达的指纹内容,由长度为16的字符串指纹内容控制其中的点是否显示
*	点的形状和大小、颜色不做要求,但要求与背景能够明显区分开
* 7. 矩阵指纹是一个16*16的矩阵,指纹内容要求依次显示在矩阵的指定位置
*/
typedef struct 
{
	unsigned char	m_ucShowType;	//显示方式0：字符串; 1：点阵；2：矩阵；其他值保留。
	unsigned char	m_ucContentType;	//显示类型 0: 卡号, 1:机顶盒号，其他值保留
	ADI_BOOL		m_bIsVisible; 	//可见性0：显性；1：隐性
	ADI_BOOL		m_bIsForcedShow;	//是否强制显示 0：非强制显示 1：强制显示。	
	unsigned char	m_ucXPos;		//指纹显示位置的X轴坐标，取值范围0~100
	unsigned char	m_ucYPos;			//指纹显示位置的Y轴坐标，取值范围0~100
	unsigned char	m_ucFontSize; 	//指纹字体大小，取值范围[0,255]，0表示默认字体大小，1表示大字体，2表示小字体，3~255表示实际字体大小，如果机顶盒不支持3~255则按照默认字体大小显示。byShowType为1和2时表示指纹区域的大小。
	unsigned int	m_unFontColor;		//字体颜色，标准RGB值。byShowType为1时该值无意义。
	unsigned int	m_unBackgroundColor;	//背景颜色，标准RGB值，byShowType为1和2时不做要求。
	unsigned char	m_aucFingerMsg[MAX_FINGERMSG_LEN+1]; //需要显示的指纹内容，用0结尾的字符串
}TFFingerMsg_S;

#define MAX_TFOSDMSG_LEN	320	//>=CDCA_MAXLEN_OSD+4

/*
* OSD 显示信息说明: 参见超级指纹与超级OSD移植库接口变动说明文档\
* 1. 当显示类型为强制OSD, 显示该消息时要求锁屏,遥控器和STB面板(除待机键和电源键以外)都是失效的,且保证OSD信息显示期间无法换台或进行其他操作
* 2. 关于颜色值(0xAARRGGBB) 表示一个颜色的RGB值,其中0xAA无意义
* 3. m_bShowCardSN 为TRUE时需要在OSD显示的左下角同时显示智能卡卡号m_aucCardSN
* 4. 超级指纹信息兼容Unicode编码字符,要求根据运营商下发的字符编码格式处理
*/
typedef	struct
{
	unsigned char   m_unOSDMsgType; //指纹属性 0，Mormal 指纹，1 Super 
	unsigned char	m_ucDisplayMode; //显示模式， 0：表示屏幕正中央显示，1：表示屏幕上方滚动显示，2：表示屏幕下方滚动显示，其他值保留
	//以下5个参数只有byDisplayMode为0时才有效。
	unsigned char	m_ucShowType; //是否强制显示 0:非强制显示，1:强制显示。
	unsigned char	m_ucFontSize;	//超级OSD字体大小 0：默认，1：大号，2：小号，3~255表示实际字号大小。如果机顶盒不支持3~255则按照默认字体大小显示
	unsigned char	m_ucBackgroundArea; //占屏幕正中央部分的面积百分比，范围（20~100）。
	ADI_BOOL		m_bShowCardSN; //是否要求在超级OSD的左下角显示卡号， 0：不显示 1：显示
	unsigned char	m_aucCardSN[17]; //智能卡卡号，用0结尾的字符串，bShowCardSN为1时显示。注：卡号字体大小为机顶盒默认字体大小。
	//以下3个参数对byDisplayMode为0,1,2都有效。
	unsigned int	m_unFontColor;		//字体颜色
	unsigned int	m_unBackgroundColor;	//背景颜色
	unsigned char	m_aucContent[MAX_TFOSDMSG_LEN]; //超级OSD内容。注：滚动显示时字体大小为机顶盒默认字体大小。
}TFOSDMsgInfo_S;


#define MAX_ACTIONDATA_LEN	0x100
typedef struct
{
	unsigned int  m_unTVSID;	/* 运营商ID */
	unsigned char m_ucActionType;	/* 行为类型, 参见ADITFActionRequestType_E*/	
	unsigned int  m_unActionDatalen; /* 通知数据的长度*/
	unsigned char m_aucActionData[MAX_ACTIONDATA_LEN]; /* 通知数据*/
}TFCaActionRequest_S;

typedef enum
{
	TFCA_WATCHLIMIT_NONE = 0, 	/* 禁用连续观看限制 , CDCA_ContinuesWatchLimit_Disable*/
	TFCA_WATCHLIMIT_OPEN = 1, 	/* 启用连续观看限制,此时worktime/stoptime有效 , CDCA_ContinuesWatchLimit_Enable*/
	TFCA_WATCHLIMIT_CLOSE = 2, 	/* 取消当前连续观看限制 , CDCA_ContinuesWatchLimit_Clear*/
	TFCA_WATCHLIMIT_MAX
}TFWatchLimitType_E;

typedef struct
{
	TFWatchLimitType_E m_eLimitType;	/* 连续观看限制模式 */
	unsigned int	m_unWorkTime;		/* 连续工作时间, 单位:小时 */
	unsigned int	m_unStopTime;		/* 停止时间, 单位: 分钟 */
}TFContinueWatchLimit_S;

#define MAX_PARENTCARDSN_LEN (24)

typedef struct
{
	unsigned char m_ucIsChild;
	unsigned short m_usDelayHour;
	TFCaDate_S m_stLastFeedTime;
	char m_acParentCardSN[MAX_PARENTCARDSN_LEN];
	unsigned char m_ucIsCanBeFeed;
}TFCaPairCardInfo_S;


/* 获取当前工作时间--- just as a clarification*/
extern void GetNetWorkTime(ADIOSSysTime_S *pTime);

/*
 * Description: 设置CA的flash地址
 *
 * Parameters : 
 *				输入参数
 *					pstNvm  CA flash地址
 *				输出参数
 *					无
 *
 * Note: 
 *
 * Returns	  :  0     成功
 *				 其他  失败
 */
int ADI_TF_SetFlashAddress(TFCaFlash_S *pstNvm);


/*高安方案时此唯一编号取自芯片CHIPID, 非高安芯片方案则由厂商自定义此UniqueID*/
void ADI_TF_SetUniqueID(unsigned int unUniqueID);
int ADI_TF_GetSTBID(unsigned int* punPlatformID, unsigned int* punUniqueID);



/*------- 智能卡管理 -------*/

/* 读取智能卡信息*/
int ADI_TF_GetCardInfo(TFCardInfo_S *psCardInfo);

#define TFCA_PINCODE_MAXLEN 	0x6
/* PIN码管理 */
int ADI_TF_ModifySCPin(unsigned char* pucOldPin, unsigned char *pucNewPin);

/* 查询用户观看级别*/
int ADI_TF_GetRating(unsigned char* pucRating);

/* 设置用户观看级别*/
int ADI_TF_SetRating(const unsigned char *pucPinCode, unsigned char ucRating);

/* 查询智能卡当前工作时段*/
int ADI_TF_GetWorkTime(TFWorkTime_S* psStartTime, TFWorkTime_S* psEndTime);

/* 设置智能卡工作时段*/
int ADI_TF_SetWorkTime(const unsigned char *pucPinCode, TFWorkTime_S sStartTime, TFWorkTime_S sEndTime);



/*------- 基本信息查询与管理 -------*/

/* 查询CA 版本信息*/
int ADI_TF_GetCAInfo(TFCAInfo_S *psCAInfo);

/* 查询机卡对应情况 */
int ADI_TF_GetPairedSTBIDList(TFSTBIDListInfo_S *psSTBIDList, CardPaired_Status_E *pePairedStatus);

/* 查询运营商信息 */
int ADI_TF_GetOperatorInfo(TFOperatorList *psOperatorList);

/* 查询普通授权节目购买情况 */
int ADI_TF_GetServiceEntitleInfo(unsigned short usTVSID, TFEntitlesInfo *psEntitlesInfo);



/*-------- 授权信息管理 --------*/

/* 查询授权ID列表 */
int ADI_TF_GetEntitleIDList(unsigned short usTVSID, TFEntitleIDList *psEntitleIDList);

/* 反授权确认码要以十进制显示*/
int ADI_TF_GetDetitleChkNum(unsigned short usTVSID, ADI_BOOL *pbReadFlag, unsigned int *punDetitleChkNum);

/* 查询反授权信息读取状态 */
ADI_BOOL ADI_TF_GetDetitleReadFlag(unsigned short usTVSID);

/* 删除反授权确认码 */
int ADI_TF_DelDetitleChkNum(unsigned short usTVSID, unsigned int unDetitleChkNum);

/* 查询用户特征 信息*/
int ADI_TF_GetACInfoList(unsigned short usTVSID, TFACListInfo * psACListInfo);

/* 查询钱包的详细信息*/
int ADI_TF_GetTVSSlotInfo(unsigned short usTVSID, TFTVSSlotList *psSlotList);

/*
* 用户对IPPV节目是否购买进行选择的时候调用该接口, 提交IPPV节目购买信息, bIPPVBuyFlag 为ADI_FALSE 表示不购买
* 注意: 机顶盒调用该接口时,需要同时隐藏"IPPV节目通知" 的对话框
*/
int ADI_TF_SetIPPVBuyDlg(ADI_BOOL bIPPVBuyFlag, unsigned int	unEcmPid,const unsigned char *pucPinCode, TFCaPrice_S stIppvInfo);

/* 查询IPPV节目购买情况*/
int ADI_TF_GetIPPVInfoList(unsigned short usTVSID, TFIppvList *psIPPVList);



//邮件相关操作
int ADI_TF_GetEmailTotalNum(unsigned char* pcEmailNum, unsigned char* pcUnreadNum);
int ADI_TF_GetEmailTitle(int nIndex, TFCaEmailHead_S *pstEmail);
int ADI_TF_GetEmailHeadByID(unsigned int unEmailID, TFCaEmailHead_S *psEmailInfo);
int ADI_TF_GetEmailContent(int nIndex, TFCAEmailContent_S* pstEmailContent);
int ADI_TF_GetEmailContentByID(unsigned int dwEmailId, TFCAEmailContent_S* pstEmailContent);
int ADI_TF_DelEmail(int nIndex);
int ADI_TF_DelEmailByID(unsigned int dwEmailId);
/* 设置邮件排序类型*/
int ADI_TF_SetSortStyle(TFCAEmailSortStyle_E eSortStyle);


/*
 * Description: 读取当前子母卡信息
 *
 * Parameters : 
 *				输入参数
 *					usTVSID  运营商ID
 *					pstPairCardInfo  子母卡信息指针  
 *				输出参数
 *					pstPairCardInfo  读到的子母卡信息
 *
 * Note: 
 *
 * Returns	  :     TONGFANG_RC_OK
 * 					TONGFANG_RC_POINTER_INVALID
 *					TONGFANG_RC_CARD_INVALID
 * 					TONGFANG_RC_DATA_NOT_FIND
 *
 */
int ADITFGetPairCardInfo(unsigned short usTVSID, TFCaPairCardInfo_S* pstPairCardInfo);

/*
 * Description: 进到配对界面清空配对信息缓存
 *
 * Parameters : 
 *				输入参数
 *					无
 *				输出参数
 *					无
 *
 * Note: 
 *
 * Returns	  :  VOID
 */
void ADITFClearParentPairStatus(void);

/*
 * Description: 设置子母卡配对
 *
 * Parameters : 
 *				输入参数
 *					usTVSID 运营商ID
 *					nIsChild 0:母卡   1:子卡
 *					nIsCanBeFeed 是否能喂养
 *				输出参数
 *					无
 *
 * Note: 设置子母卡配对
 *
 * Returns	  :  
 *               0 手动喂养成功消息: 喂养成功 
 *               1 手动喂养成功消息: 请插入子卡
 *               2 手动喂养成功消息: 请插入母卡
 *               3 手动喂养失败消息: 喂养时间未到,子卡不能被喂养
 *               4 手动喂养失败消息: 喂养失败
 *               5 手动喂养失败消息: 读取母卡数据失败
 */
int ADITFSetParentPair(unsigned short usTVSID, int nIsChild, int nIsCanBeFeed);
void ADI_TF_Enter_Menu(TF_MENU_E eCAMenu);
void ADI_TF_Exit_Menu(TF_MENU_E eCAMenu);



#ifdef  __cplusplus
}
#endif

#endif

