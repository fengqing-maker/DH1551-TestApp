
#ifndef _ADI_TOOLSET_H_
#define _ADI_TOOLSET_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"
#include "adi_ir.h"
#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_CHIPID_MAX_LENGTH   (32)      // 主芯片的ID的最大长度
#define ADI_SERIAL_MAX_LENGTH   (64)      // 系统序列号的最大长度
#define ADI_KEY_MAX_LENGTH  	(512)     // 校验密钥的最大长度

/*工具集模块相关错误代码值。*/
enum
{
	ADITOOLSET_ERROR_BAD_PARAMETER = ADI_TOOLSET_ERROR_BASE,// 错误参数
	ADITOOLSET_ERROR_FEATURE_NOT_SUPPORTED     				// 不支持操作
};

/*主芯片的ID信息。*/
typedef struct 
{
	int 	m_nLength;						                // 主芯片的ID的长度，其长度不超过ADI_CHIPID_MAX_LENGTH
	unsigned char    m_szChipID[(ADI_CHIPID_MAX_LENGTH+1+3) & (~3)];	// 主芯片的ID。在许多具有高级安全的主芯片中，存在唯一的ID号。	
}ADICHIPID_S;

typedef struct 
{
	int 	m_nLength;						                // 主芯片的ID的长度，其长度不超过ADI_CHIPID_MAX_LENGTH
	unsigned char    m_szSTBSN[(ADI_CHIPID_MAX_LENGTH+1+3) & (~3)];	// 主芯片的ID。在许多具有高级安全的主芯片中，存在唯一的ID号。	
}ADISTBSN_S;


typedef struct 
{
	char m_szSerial[(ADI_SERIAL_MAX_LENGTH+1+3) & (~3)];	// 系统序列号标识，一台机器只具有一个唯一标识，用于校验
	char m_szPairsKey[(ADI_KEY_MAX_LENGTH+1+3) & (~3)];	    // 序列号配对码，一台机器只具有一个唯一的加密，用于校验
}ADISerialKey_S;

/*引导类型枚举*/
typedef enum
{
	EM_ADITOOLSET_EXECTYPE_UNKONWN,         // 边界值
	EM_ADITOOLSET_EXECTYPE_APP,             // 启动目标为应用
	EM_ADITOOLSET_EXECTYPE_LOADER,           // 启动目标为Loader
	EM_ADITOOLSET_EXECTYPE_LINUX
}ADIToolsetExecType_E;

/*引导信息结构*/
typedef struct
{
	ADIToolsetExecType_E    m_eType;        // 引导类型
	void*                   m_pCodeAddr;    // 需引导代码段内存首地址或Flash首地址
	int                     m_nCodeLength;	// 需引导代码段长度
}ADIToolsetExecInfo_S;


typedef enum
{
	EM_ADISYS_HDCP_OPEN,		/**< 打开HDCP */
	EM_ADISYS_HDCP_CLOSE		/**< 关闭HDCP */
}ADISYSHdcpMode_E;

typedef enum
{
	EM_ADISYS_AVSYNC_PCR,		/**<   PCR同步 */
	EM_ADISYS_AVSYNC_AUDIO,		/**<   音频同步 */
	EM_ADISYS_AVSYNC_VIDEO,		/**<   视频同步*/
	EM_ADISYS_AVSYNC_MAX		/**<   同步方式边界值 */
}ADISYSAVSyncMode_E;

typedef enum _ADISYSDolbyOption
{
	EM_ADISYS_DOLBY_BYPASS_SET_AUTO,   //驱动根据TV性能设置
	EM_ADISYS_DOLBY_BYPASS_SET_MANUAL, //应用设置
	EM_ADISYS_DOLBY_MAX  
}ADISYSDolbyOption_E;

typedef enum
{
	/** ADICFG_TUNER_MODE
	Tuner串行并行, ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_TUNER_MODE
		nDeviceIndex: 	tuner index
		unValue1:		CSHDITsMode枚举
		unValue1:		0
	*/
	ADICFG_TUNER_MODE ,	

	/** ADICFG_TUNER_TSIN
	设置TUNER对应的TSIN, ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_TUNER_TSIN
		nDeviceIndex: 	tuner index
		unValue1:		TSIN index
		unValue1:		0
	*/
	ADICFG_TUNER_TSIN, 
	
	/** ADICFG_TSIN_DMX
	设置TSIN对应的DMX, ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_TSIN_DMX
		nDeviceIndex: 	TSIN index
		unValue1:		Demux index
		unValue1:		0
	*/
	ADICFG_TSIN_DMX,

	/** ADICFG_HDMI_I2C
	设置HDMI对应的I2C, ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_HDMI_I2C
		nDeviceIndex: 	HDMI index, 一般为0
		unValue1:		I2C index
		unValue1:		0
	*/
	ADICFG_HDMI_I2C,

	/** ADICFG_HDMI_PIO
	设置HDMI对应的I2C, ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_HDMI_PIO
		nDeviceIndex: 	HDMI index, 一般为0
		unValue1:		GPIO index
		unValue1:		0
	*/
	ADICFG_HDMI_PIO,

	/** ADICFG_HDMI_HDCP
	设置平台初始化时是否打开HDCP 功能, ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_HDMI_HDCP
		nDeviceIndex: 	HDMI index, 一般为0
		unValue1:		ADISYSHdcpMode_E,详情见该枚举的说明
		unValue1:		0
	*/
	ADICFG_HDMI_HDCP,

	/** ADICFG_SCREEN_RESOLUTION
	设置平台初始化时的分辩率,  ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_SCREEN_RESOLUTION
		nDeviceIndex: 	ADISCREENType_E, 具体见该枚举的说明
		unValue1:		ADISCREENResolution_E, 具体见该枚举的说明
		unValue1:		0
	*/
	ADICFG_SCREEN_RESOLUTION,

	/*ADICFG_PIXEL_FORMAT
	设置显存颜色模式
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_PIXEL_FORMAT
	nDeviceIndex：默认为0
	unValue1	：ADIOSGPixelFormat_E，具体见该枚举的说明
	unValue2	：0
	*/
	ADICFG_PIXEL_FORMAT,
	
	/*ADICFG_BOARD_NO
	设置主板号
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_BOARD_NO
	nDeviceIndex：不关注，无意义
	unValue1	：主板号字符串指针
	unValue2	：不关注，无意义
	*/
	ADICFG_BOARD_NO,

	/*ADICFG_AVSYNC_MOD
	设置音 视频同步方式
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_AVSYNC_MOD
	nDeviceIndex：0
	unValue1	：ADISYSAVSyncMode_E
	unValue2	：0
	*/
	ADICFG_AVSYNC_MOD,

	/*ADICFG_MUTE_IOLEVEL
	设置控制静音电路的GPIO和电平状态
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_MUTE_IOLEVEL
	nDeviceIndex：用来控制静音电路的GPIO索引值
	unValue1	：控制静音的GPIO电平状态
	unValue2	：无意义
	*/
	ADICFG_MUTE_IOLEVEL,

	/*ADICFG_DOLBY_OPTION
	设置杜比功能选项,默认驱动根据TV性能设置
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_DOLBY_OPTION
	nDeviceIndex：预留
	unValue1	：ADISYSDolbyOption_E枚举值
	unValue2	：预留
	*/
	ADICFG_DOLBY_OPTION,

	/*ADICFG_CGMS_MODE
	??CGMS??
	ADISYSSetCfg ????:
	eCfgType	:ADICFG_CGMS_MODE
	nDeviceIndex:??
	unValue1	:ADISYSCGMSMode_E???
	unValue2	:??
	*/
	ADICFG_CGMS_MODE,

	/*ADICFG_PANEL_TYPE
	设置前面板型号
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_PANEL_TYPE
	nDeviceIndex：预留
	unValue1	：ADIPANELType_E枚举值
	unValue2	：预留
	*/
	ADICFG_PANEL_TYPE,

	/*ADICFG_BOOTLOGO_DISPLAY
	mstar平台设置bootlogo显示方式
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_BOOTLOGO_DISPLAY
	nDeviceIndex：预留
	unValue1	：1   boot中使用GOP3显示logo
	                    0   boot中使用非GOP3显示logo
	unValue2	：预留
	*/
	ADICFG_BOOTLOGO_DISPLAY,

	/*ADICFG_ETHER_TYPE
	mstar平台设置网络类型
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_ETHER_TYPE
	nDeviceIndex：预留
	unValue1	：ADIEtherType_E枚举类型
	unValue2	：预留
	*/
	ADICFG_ETHER_TYPE,

	/*ADICFG_DOLBY_SUPPORT
	mstar平台设置网络类型
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_DOLBY_SUPPORT
	nDeviceIndex：预留
	unValue1	：1   支持杜比
	                    0   不支持杜比
	unValue2	：预留
	*/
	ADICFG_DOLBY_SUPPORT,

	/*ADICFG_FLASH_PARAM
	mstar平台设置网络类型
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_FLASH_PARAM
	nDeviceIndex：预留
	unValue1	：nandinfo (unsigned char *)
	unValue2	：nandpartitioninfo(unsigned char *)
	*/
	ADICFG_FLASH_PARAM,

	ADICFG_LIGHT_INVERT,
	/*ADICFG_LIGHT_INVERT
	平台GPIO特殊配置
	ADISYSSetCfg 参数说明：
	eCfgType	：ADICFG_LIGHT_INVERT
	nDeviceIndex：预留
	unValue1	：ADIPanelLightName_E
	unValue2	：0 不反转  1反转
	*/
	
	/** ADICFG_TUNER_TYPE
	ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_TUNER_TYPE
		nDeviceIndex: 	预留
		unValue1:		ADITunerType_E枚举
		unValue2:		ADITunerType_E枚举
	*/
	ADICFG_TUNER_TYPE,

	/** ADICFG_SOUNDBAR_SUPPORT
	ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_SOUNDBAR_SUPPORT
		nDeviceIndex: 	预留
		unValue1:		1:支持soundbar，0:不支持soundbar
		unValue2:		预留
	*/
	ADICFG_SOUNDBAR_SUPPORT,

	/** ADICFG_SOUNDBAR_SUPPORT
	ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_VIDEO_HEVC_SUPPORT
		nDeviceIndex: 	预留
		unValue1:		1:支持hevc，0:不支持hevc
		unValue2:		预留
	*/
	ADICFG_VIDEO_HEVC_SUPPORT,

     /** ADICFG_YPBPR_SUPPORT
	ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_YPBPR_SUPPORT
		nDeviceIndex: 	预留
		unValue1:		1:支持YPBPR，0:不支持YPBPR
		unValue2:		预留
	*/
	ADICFG_YPBPR_SUPPORT,

    /** ADICFG_SCREEN_PARAM_ADJUST
	ADIPlatformInit之前设置
	ADISYSSetCfg参数说明:
		eCfgType:		ADICFG_SCREEN_PARAM_ADJUST
		nDeviceIndex: 	预留
		unValue1:		1:支持自动调整，0:不支持自动调整
		unValue2:		预留
	*/
	ADICFG_SCREEN_PARAM_ADJUST,

	ADICFG_MAX_NUM
}ADISYSCfg_E;

/*定义真待机唤醒模式*/
typedef enum 
{
	ADISYS_WAKEUPE_MODE_IR, // 通过遥控器唤醒
	ADISYS_WAKEUPE_MODE_RTC,//定时待机唤醒
	ADISYS_WAKEUPE_MODE_GPIO,//面板唤醒
	ADISYS_WAKEUPE_MODE_NONE,//上电启动
	ADISYS_WAKEUPE_MODE_MAX
}ADISYSWakeUpMode_E;

/*定义遥控器键值结构*/
typedef struct
{
	ADIIRProtocol_E	    m_eIRProtocol; 	    // 协议 
	unsigned int 		m_nUserID; 			// 遥控器厂家码，用于识别遥控器类型 
	unsigned int 		m_nKeyCode;			// 遥控器按键的电气编码 
}ADISYSWakeUpKey_S;

#define ADI_MAX_WAKEUP_KEY_NUM 16

/*定义真待机唤醒参数*/
typedef struct
{
	ADISYSWakeUpMode_E m_eWakeUpMode; 	// 唤醒模式
	ADI_BOOL 	m_bModeEnable;	            // 是否启用这种模式
	union 
	{
		struct
		{
			ADISYSWakeUpKey_S m_astKeys[ADI_MAX_WAKEUP_KEY_NUM];
			int m_nKeyNum;
		} 
		m_stIRKeys; // IR唤醒模式对应的键值参数 
	} 
	m_uWakeupParams; // 唤醒模式对应的参数， m_bModeEnable为FALSE时，忽略这些参数
}ADISYSWakeupParams_S;

ADI_Error_Code ADISYSDolbyEnable(ADI_BOOL bEnable);


/*设置HDCP Key，此接口要在ADIPlatformInit之前调用*/
ADI_Error_Code ADISYSSetHDCPKey(void *pHDCPKey,int nHDCPKeySize);

ADI_Error_Code ADISYSSetCfg(ADISYSCfg_E eCfgType, int nDeviceIndex, unsigned int unValue1, unsigned int unValue2);

ADI_Error_Code ADISYSInit(void);

ADI_Error_Code ADIPlatformInit(void);

ADI_Error_Code ADIPlatformInitDelay(void);

ADI_Error_Code ADIOTPRead(unsigned long ulAddr,unsigned char *pucData,unsigned long ulDataLen);

ADI_Error_Code ADIOTPWrite(unsigned long ulAddr,unsigned char *pucData,unsigned long ulDataLen);

ADI_Error_Code ADIGetChipID(ADICHIPID_S * psChipID);
ADI_Error_Code ADIGetStbSn(ADISTBSN_S * psStbSn);


ADI_Error_Code ADIGetSerialKey(ADISerialKey_S * psSerialKey);

ADI_Error_Code ADISYSSetWakeupParams(const ADISYSWakeupParams_S* pstWakeupParams);

ADI_Error_Code ADISYSGetWakeupParams(ADISYSWakeupParams_S* pstWakeupParams);

typedef ADI_Error_Code (*ADIChipStandbyHookFunc_F)(ADI_BOOL bStandby,int nStandbyTime, ADI_BOOL *pbSkipDefault);

ADI_Error_Code ADISYSSetChipStandbyHook(ADIChipStandbyHookFunc_F fnHook); 

ADI_Error_Code ADISYSStandby(ADI_BOOL bStandby,int nStandbyTime,ADI_BOOL *pbReal);

ADI_Error_Code ADIToolsetSetExecInfo(ADIToolsetExecType_E eType,void* pExecParam);

ADI_Error_Code ADIToolsetExec(ADIToolsetExecInfo_S *psExecInfo);

ADI_Error_Code ADISYSReboot(void);

//only for ali
ADI_Error_Code ADIToolsetLoadSeeCode(unsigned char *see_code_buf,unsigned int see_code_len);
ADI_Error_Code ADIToolsetLoadMainCode(unsigned char *maincode_buf,unsigned int maincode_len);


//only for conax_vsc
ADI_Error_Code ADIOTPWriteVscSWEK(unsigned char *pucSWEK, unsigned int unSWEKLen);
ADI_Error_Code ADIOTPReadVscSWEK(unsigned char *pucSWEK, unsigned int unSWEKLen);

#ifdef  __cplusplus
}
#endif

#endif


