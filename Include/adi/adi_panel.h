
#ifndef _ADI_PANEL_H_
#define _ADI_PANEL_H_

#include "adi_typedef.h"
#include "adi_error.h"
#include "adi_hdicommon.h"


#ifdef  __cplusplus
extern "C" {
#endif

/*PANEL 设备相关错误代码值*/
enum
{
	ADIPANEL_ERROR_BAD_PARAMETER = ADI_PANEL_ERROR_BASE,
	ADIPANEL_ERROR_FEATURE_NOT_SUPPORTED,
	ADIPANEL_ERROR_UNKNOWN_ERROR,
	ADIPANEL_ERROR_INVALID_DEVICE_ID
};


/*面板显示类型枚举定义*/
typedef enum
{
	EM_ADIPANEL_CTRLSTART,       	// 控制符灯显示类型起始值,不作为类型标识
	
	EM_ADIPANEL_MAIL,     	        // Mail灯
	EM_ADIPANEL_SIGNAL,  	        // Signal灯
	EM_ADIPANEL_AUDIO, 	       		// Audio灯
	EM_ADIPANEL_PLAY, 				// 播放 
	EM_ADIPANEL_PAUSE, 	        	// 暂停 
	EM_ADIPANEL_STOP, 				// 停止 
	EM_ADIPANEL_HDTV,				// HDTV 
	EM_ADIPANEL_BACKWARD,           // 快退
	EM_ADIPANEL_FORWARD, 	        // 快进 
	EM_ADIPANEL_BALL, 				// 圆
	EM_ADIPANEL_DUBY, 				// 杜比 
	EM_ADIPANEL_PREVIOUS, 	        // 前一个
	EM_ADIPANEL_NEXT, 				// 后一个
	EM_ADIPANEL_IR, 				// 遥控器
	EM_ADIPANEL_USB, 				// USB
	EM_ADIPANEL_N,					// N
	EM_ADIPANEL_VOD, 				// VOD
	EM_ADIPANEL_POWER, 	        	// 电源
	EM_ADIPANEL_TV, 				// 电视
	EM_ADIPANEL_NETWORK, 	        // 网络
	EM_ADIPANEL_RADIO, 	        	// 广播
	EM_ADIPANEL_CLOCK,				// 时钟
	EM_ADIPANEL_MODEM,	        	// MODEM 
	EM_ADIPANEL_REC,				// 录制 
	EM_ADIPANEL_UP,					// 上
	EM_ADIPANEL_DOWN,				// 下
	EM_ADIPANEL_LEFT,				// 左
	EM_ADIPANEL_RIGHT,				// 右			
	
	EM_ADIPANEL_CTRLALL,       		// 控制符灯显示类型结束值
	
	EM_ADIPANEL_TEXTSTART ,         // 文本灯显示类型起始值,不作为类型标识,TEXT0-TEXT4按由主到次顺序排列
	
	EM_ADIPANEL_TEXT0,	    	    // 第一行文本
	EM_ADIPANEL_TEXT1,              // 第二行文本
	EM_ADIPANEL_TEXT2,	    	    // 第三行文本	
	EM_ADIPANEL_TEXT3,              // 第四行文本
	EM_ADIPANEL_TEXT4,              // 第五行文本
	
	EM_ADIPANEL_TEXTALL,            // 文本灯显示类型结束值
	
	EM_ADIPANEL_RED,
	EM_ADIPANEL_GREEN,

	EM_ADIPANEL_MAX             // 边界值	
}ADIPanelLightName_E;

#define ADI_PANEL_IS_TEXT(name)	(  ( (name) > EM_ADIPANEL_TEXTSTART &&  (name) < EM_ADIPANEL_TEXTALL ) || ( (name) > EM_ADIPANEL_EXT_TEXT_START &&  (name) < EM_ADIPANEL_EXT_TEXT_END )  )    // 判断name是否是文本灯显示类型
#define ADI_PANEL_IS_CTRL(name)   (  (  (name) > EM_ADIPANEL_CTRLSTART &&  (name) < EM_ADIPANEL_CTRLALL ) || (  (name) > EM_ADIPANEL_EXT_CTRL_START &&  (name) < EM_ADIPANEL_EXT_CTRL_END ) ) // 判断name是否是控制符灯显示类型
#define ADI_PANEL_IS_SUIT(name)   (  (  (name) > EM_ADIPANEL_SUITSTART &&  (name) < EM_ADIPANEL_SUITALL ) || (  (name) > EM_ADIPANEL_EXT_SUIT_START &&  (name) < EM_ADIPANEL_EXT_SUIT_END ) ) // 判断name是否是组合灯显示类型

/*文本灯显示类型能力信息*/
typedef struct
{
	int             m_nTextCount;                 // 该行文本支持显示的字符个数	
}ADIPanelTextLightAttr_S;

/*组合灯显示类型能力信息*/
typedef struct
{	
	int m_nSuitCount;                 // 组合灯子灯数量
}ADIPanelSuitLightAttr_S;

/*控制符灯显示类型功能枚举定义*/
typedef enum
{
	EM_ADIPANEL_CTRL_OFF		 = 1 << 0,		// 该控制灯可以熄灭
	EM_ADIPANEL_CTRL_ON			 = 1 << 1,		// 该控制灯可以点亮,如果支持color2，使用默认颜色显示
	EM_ADIPANEL_CTRL_FLASH		 = 1 << 2,		// 该控制灯可以闪烁，默认颜色的闪烁
	EM_ADIPANEL_CTRL_COLOR2		 = 1 << 3,		// 该控制灯支持第二种颜色
	EM_ADIPANEL_CTRL_COLOR2FLASH = 1 << 4,		// 该控制灯支持以第二种颜色闪烁
	EM_ADIPANEL_CTRL_COLORSWITCH = 1 << 5       // 控制灯支持两种颜色交替闪烁
}ADIPanelCtrlLightFun_E;

/*控制符灯显示类型能力信息*/
typedef struct
{
	unsigned int	m_dwCtrFunMask;   // 相应位为1表示具有该功能值,取值为ADIPanelCtrlLightFun_E中各值相或, 例如(EM_ADIPANEL_FLASH |EM_ADIPANEL_COLOR2)
}ADIPanelCtrlLightAttr_S;

/*设备能力信息*/
typedef struct
{
	ADIPanelLightName_E m_eLightName;         // 显示灯名称，主要用于确认灯类型，详见ADIPanelLightName_E
	union
	{
		ADIPanelTextLightAttr_S	m_sText;    // 文本灯显示类型
		ADIPanelSuitLightAttr_S	m_sSuit;	// 组合灯显示类型
		ADIPanelCtrlLightAttr_S	m_sCtrl;	// 控制符灯显示类型
	}m_uProperty;                               // 显示类型能力联合结构体,根据m_eLightName字段的类型取对应显示设备类型描述字段
}ADIPanelLightCapability_S;

/*文本灯显示类型枚举*/
typedef enum
{
	EM_ADIPANEL_TEXT_STRING,			// 字符串类型
	EM_ADIPANEL_TEXT_TIME			// 时间类型
}ADIPanelTextType_E;

/*文本灯显示类型的显示值*/
typedef struct
{
	ADIPanelTextType_E  m_eDisplayType;	    // 显示类型
	char				m_szStr[32];        // 若m_eDisplayType为文本类型则为显示字符串,字符串必须以0结尾,对应字节为空格表示熄灭该字符;若字符数量超过总子灯数，忽略超过部分
											// 若m_eDisplayType为时间类型则内容为yyyymmddhhmmss格式的时间,具体显示方式及间隔符号的闪烁方式由移植层自行根据面板情况确定
    int 				m_nStrCount;        // 要显示的字符个数，最大不超过32个字符
}ADIPanelTextValue_S;

/*组合灯显示类型的显示值*/
typedef struct
{
	unsigned int	m_dwSuitValueMask;         // 从低到高第n位的值表示组合中第n个灯的状态,0表示熄灭,1表示点亮	
}ADIPanelSuitValue_S;


/*控制符灯显示类型的显示值*/
typedef struct
{
	ADIPanelCtrlLightFun_E	m_eCtrlValue;	// 表示该控制灯的显示状态
}ADIPanelCtrlValue_S;

/*显示类型的显示值 */
typedef struct
{
	ADIPanelLightName_E m_eLightName;         // 显示灯名称，详见ADIPanelLightName_E
	union
	{
		ADIPanelTextValue_S		m_sTextValue;
		ADIPanelSuitValue_S		m_sSuitValue;
		ADIPanelCtrlValue_S		m_sCtrlValue;
	}m_uValue;                         // 显示类型显示值联合结构体,根据m_eLightName字段的类型取对应显示设备类型描述字段	
}ADIPanelLightValule_S;

/*前面板类型定义*/
typedef enum
{
	EM_ADIPANEL_TYPE_SAR,
	EM_ADIPANEL_TYPE_TM1628,
	EM_ADIPANEL_TYPE_GPIO,
	EM_ADIPANEL_TYPE_MAX
}ADIPANELType_E;

ADI_Error_Code ADIPanelDisplay(int nPanelIndex,const ADIPanelLightValule_S * psValue);

ADI_Error_Code ADIPanelClear(int nPanelIndex,ADIPanelLightName_E eName);

ADI_Error_Code ADIPanelAddKeySendCallback(ADIKeyCallback_F KeySendCallback );

//for ali boot
ADI_Error_Code ADIPanelScan(int *pnLogicKey,int nTimeout);


#ifdef __cplusplus
}
#endif

#endif



