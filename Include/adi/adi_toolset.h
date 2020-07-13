
#ifndef _ADI_TOOLSET_H_
#define _ADI_TOOLSET_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"
#include "adi_ir.h"
#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_CHIPID_MAX_LENGTH   (32)      // ��оƬ��ID����󳤶�
#define ADI_SERIAL_MAX_LENGTH   (64)      // ϵͳ���кŵ���󳤶�
#define ADI_KEY_MAX_LENGTH  	(512)     // У����Կ����󳤶�

/*���߼�ģ����ش������ֵ��*/
enum
{
	ADITOOLSET_ERROR_BAD_PARAMETER = ADI_TOOLSET_ERROR_BASE,// �������
	ADITOOLSET_ERROR_FEATURE_NOT_SUPPORTED     				// ��֧�ֲ���
};

/*��оƬ��ID��Ϣ��*/
typedef struct 
{
	int 	m_nLength;						                // ��оƬ��ID�ĳ��ȣ��䳤�Ȳ�����ADI_CHIPID_MAX_LENGTH
	unsigned char    m_szChipID[(ADI_CHIPID_MAX_LENGTH+1+3) & (~3)];	// ��оƬ��ID���������и߼���ȫ����оƬ�У�����Ψһ��ID�š�	
}ADICHIPID_S;

typedef struct 
{
	int 	m_nLength;						                // ��оƬ��ID�ĳ��ȣ��䳤�Ȳ�����ADI_CHIPID_MAX_LENGTH
	unsigned char    m_szSTBSN[(ADI_CHIPID_MAX_LENGTH+1+3) & (~3)];	// ��оƬ��ID���������и߼���ȫ����оƬ�У�����Ψһ��ID�š�	
}ADISTBSN_S;


typedef struct 
{
	char m_szSerial[(ADI_SERIAL_MAX_LENGTH+1+3) & (~3)];	// ϵͳ���кű�ʶ��һ̨����ֻ����һ��Ψһ��ʶ������У��
	char m_szPairsKey[(ADI_KEY_MAX_LENGTH+1+3) & (~3)];	    // ���к�����룬һ̨����ֻ����һ��Ψһ�ļ��ܣ�����У��
}ADISerialKey_S;

/*��������ö��*/
typedef enum
{
	EM_ADITOOLSET_EXECTYPE_UNKONWN,         // �߽�ֵ
	EM_ADITOOLSET_EXECTYPE_APP,             // ����Ŀ��ΪӦ��
	EM_ADITOOLSET_EXECTYPE_LOADER,           // ����Ŀ��ΪLoader
	EM_ADITOOLSET_EXECTYPE_LINUX
}ADIToolsetExecType_E;

/*������Ϣ�ṹ*/
typedef struct
{
	ADIToolsetExecType_E    m_eType;        // ��������
	void*                   m_pCodeAddr;    // ������������ڴ��׵�ַ��Flash�׵�ַ
	int                     m_nCodeLength;	// ����������γ���
}ADIToolsetExecInfo_S;


typedef enum
{
	EM_ADISYS_HDCP_OPEN,		/**< ��HDCP */
	EM_ADISYS_HDCP_CLOSE		/**< �ر�HDCP */
}ADISYSHdcpMode_E;

typedef enum
{
	EM_ADISYS_AVSYNC_PCR,		/**<   PCRͬ�� */
	EM_ADISYS_AVSYNC_AUDIO,		/**<   ��Ƶͬ�� */
	EM_ADISYS_AVSYNC_VIDEO,		/**<   ��Ƶͬ��*/
	EM_ADISYS_AVSYNC_MAX		/**<   ͬ����ʽ�߽�ֵ */
}ADISYSAVSyncMode_E;

typedef enum _ADISYSDolbyOption
{
	EM_ADISYS_DOLBY_BYPASS_SET_AUTO,   //��������TV��������
	EM_ADISYS_DOLBY_BYPASS_SET_MANUAL, //Ӧ������
	EM_ADISYS_DOLBY_MAX  
}ADISYSDolbyOption_E;

typedef enum
{
	/** ADICFG_TUNER_MODE
	Tuner���в���, ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_TUNER_MODE
		nDeviceIndex: 	tuner index
		unValue1:		CSHDITsModeö��
		unValue1:		0
	*/
	ADICFG_TUNER_MODE ,	

	/** ADICFG_TUNER_TSIN
	����TUNER��Ӧ��TSIN, ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_TUNER_TSIN
		nDeviceIndex: 	tuner index
		unValue1:		TSIN index
		unValue1:		0
	*/
	ADICFG_TUNER_TSIN, 
	
	/** ADICFG_TSIN_DMX
	����TSIN��Ӧ��DMX, ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_TSIN_DMX
		nDeviceIndex: 	TSIN index
		unValue1:		Demux index
		unValue1:		0
	*/
	ADICFG_TSIN_DMX,

	/** ADICFG_HDMI_I2C
	����HDMI��Ӧ��I2C, ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_HDMI_I2C
		nDeviceIndex: 	HDMI index, һ��Ϊ0
		unValue1:		I2C index
		unValue1:		0
	*/
	ADICFG_HDMI_I2C,

	/** ADICFG_HDMI_PIO
	����HDMI��Ӧ��I2C, ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_HDMI_PIO
		nDeviceIndex: 	HDMI index, һ��Ϊ0
		unValue1:		GPIO index
		unValue1:		0
	*/
	ADICFG_HDMI_PIO,

	/** ADICFG_HDMI_HDCP
	����ƽ̨��ʼ��ʱ�Ƿ��HDCP ����, ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_HDMI_HDCP
		nDeviceIndex: 	HDMI index, һ��Ϊ0
		unValue1:		ADISYSHdcpMode_E,�������ö�ٵ�˵��
		unValue1:		0
	*/
	ADICFG_HDMI_HDCP,

	/** ADICFG_SCREEN_RESOLUTION
	����ƽ̨��ʼ��ʱ�ķֱ���,  ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_SCREEN_RESOLUTION
		nDeviceIndex: 	ADISCREENType_E, �������ö�ٵ�˵��
		unValue1:		ADISCREENResolution_E, �������ö�ٵ�˵��
		unValue1:		0
	*/
	ADICFG_SCREEN_RESOLUTION,

	/*ADICFG_PIXEL_FORMAT
	�����Դ���ɫģʽ
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_PIXEL_FORMAT
	nDeviceIndex��Ĭ��Ϊ0
	unValue1	��ADIOSGPixelFormat_E���������ö�ٵ�˵��
	unValue2	��0
	*/
	ADICFG_PIXEL_FORMAT,
	
	/*ADICFG_BOARD_NO
	���������
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_BOARD_NO
	nDeviceIndex������ע��������
	unValue1	��������ַ���ָ��
	unValue2	������ע��������
	*/
	ADICFG_BOARD_NO,

	/*ADICFG_AVSYNC_MOD
	������ ��Ƶͬ����ʽ
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_AVSYNC_MOD
	nDeviceIndex��0
	unValue1	��ADISYSAVSyncMode_E
	unValue2	��0
	*/
	ADICFG_AVSYNC_MOD,

	/*ADICFG_MUTE_IOLEVEL
	���ÿ��ƾ�����·��GPIO�͵�ƽ״̬
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_MUTE_IOLEVEL
	nDeviceIndex���������ƾ�����·��GPIO����ֵ
	unValue1	�����ƾ�����GPIO��ƽ״̬
	unValue2	��������
	*/
	ADICFG_MUTE_IOLEVEL,

	/*ADICFG_DOLBY_OPTION
	���öűȹ���ѡ��,Ĭ����������TV��������
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_DOLBY_OPTION
	nDeviceIndex��Ԥ��
	unValue1	��ADISYSDolbyOption_Eö��ֵ
	unValue2	��Ԥ��
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
	����ǰ����ͺ�
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_PANEL_TYPE
	nDeviceIndex��Ԥ��
	unValue1	��ADIPANELType_Eö��ֵ
	unValue2	��Ԥ��
	*/
	ADICFG_PANEL_TYPE,

	/*ADICFG_BOOTLOGO_DISPLAY
	mstarƽ̨����bootlogo��ʾ��ʽ
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_BOOTLOGO_DISPLAY
	nDeviceIndex��Ԥ��
	unValue1	��1   boot��ʹ��GOP3��ʾlogo
	                    0   boot��ʹ�÷�GOP3��ʾlogo
	unValue2	��Ԥ��
	*/
	ADICFG_BOOTLOGO_DISPLAY,

	/*ADICFG_ETHER_TYPE
	mstarƽ̨������������
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_ETHER_TYPE
	nDeviceIndex��Ԥ��
	unValue1	��ADIEtherType_Eö������
	unValue2	��Ԥ��
	*/
	ADICFG_ETHER_TYPE,

	/*ADICFG_DOLBY_SUPPORT
	mstarƽ̨������������
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_DOLBY_SUPPORT
	nDeviceIndex��Ԥ��
	unValue1	��1   ֧�ֶű�
	                    0   ��֧�ֶű�
	unValue2	��Ԥ��
	*/
	ADICFG_DOLBY_SUPPORT,

	/*ADICFG_FLASH_PARAM
	mstarƽ̨������������
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_FLASH_PARAM
	nDeviceIndex��Ԥ��
	unValue1	��nandinfo (unsigned char *)
	unValue2	��nandpartitioninfo(unsigned char *)
	*/
	ADICFG_FLASH_PARAM,

	ADICFG_LIGHT_INVERT,
	/*ADICFG_LIGHT_INVERT
	ƽ̨GPIO��������
	ADISYSSetCfg ����˵����
	eCfgType	��ADICFG_LIGHT_INVERT
	nDeviceIndex��Ԥ��
	unValue1	��ADIPanelLightName_E
	unValue2	��0 ����ת  1��ת
	*/
	
	/** ADICFG_TUNER_TYPE
	ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_TUNER_TYPE
		nDeviceIndex: 	Ԥ��
		unValue1:		ADITunerType_Eö��
		unValue2:		ADITunerType_Eö��
	*/
	ADICFG_TUNER_TYPE,

	/** ADICFG_SOUNDBAR_SUPPORT
	ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_SOUNDBAR_SUPPORT
		nDeviceIndex: 	Ԥ��
		unValue1:		1:֧��soundbar��0:��֧��soundbar
		unValue2:		Ԥ��
	*/
	ADICFG_SOUNDBAR_SUPPORT,

	/** ADICFG_SOUNDBAR_SUPPORT
	ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_VIDEO_HEVC_SUPPORT
		nDeviceIndex: 	Ԥ��
		unValue1:		1:֧��hevc��0:��֧��hevc
		unValue2:		Ԥ��
	*/
	ADICFG_VIDEO_HEVC_SUPPORT,

     /** ADICFG_YPBPR_SUPPORT
	ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_YPBPR_SUPPORT
		nDeviceIndex: 	Ԥ��
		unValue1:		1:֧��YPBPR��0:��֧��YPBPR
		unValue2:		Ԥ��
	*/
	ADICFG_YPBPR_SUPPORT,

    /** ADICFG_SCREEN_PARAM_ADJUST
	ADIPlatformInit֮ǰ����
	ADISYSSetCfg����˵��:
		eCfgType:		ADICFG_SCREEN_PARAM_ADJUST
		nDeviceIndex: 	Ԥ��
		unValue1:		1:֧���Զ�������0:��֧���Զ�����
		unValue2:		Ԥ��
	*/
	ADICFG_SCREEN_PARAM_ADJUST,

	ADICFG_MAX_NUM
}ADISYSCfg_E;

/*�������������ģʽ*/
typedef enum 
{
	ADISYS_WAKEUPE_MODE_IR, // ͨ��ң��������
	ADISYS_WAKEUPE_MODE_RTC,//��ʱ��������
	ADISYS_WAKEUPE_MODE_GPIO,//��廽��
	ADISYS_WAKEUPE_MODE_NONE,//�ϵ�����
	ADISYS_WAKEUPE_MODE_MAX
}ADISYSWakeUpMode_E;

/*����ң������ֵ�ṹ*/
typedef struct
{
	ADIIRProtocol_E	    m_eIRProtocol; 	    // Э�� 
	unsigned int 		m_nUserID; 			// ң���������룬����ʶ��ң�������� 
	unsigned int 		m_nKeyCode;			// ң���������ĵ������� 
}ADISYSWakeUpKey_S;

#define ADI_MAX_WAKEUP_KEY_NUM 16

/*������������Ѳ���*/
typedef struct
{
	ADISYSWakeUpMode_E m_eWakeUpMode; 	// ����ģʽ
	ADI_BOOL 	m_bModeEnable;	            // �Ƿ���������ģʽ
	union 
	{
		struct
		{
			ADISYSWakeUpKey_S m_astKeys[ADI_MAX_WAKEUP_KEY_NUM];
			int m_nKeyNum;
		} 
		m_stIRKeys; // IR����ģʽ��Ӧ�ļ�ֵ���� 
	} 
	m_uWakeupParams; // ����ģʽ��Ӧ�Ĳ����� m_bModeEnableΪFALSEʱ��������Щ����
}ADISYSWakeupParams_S;

ADI_Error_Code ADISYSDolbyEnable(ADI_BOOL bEnable);


/*����HDCP Key���˽ӿ�Ҫ��ADIPlatformInit֮ǰ����*/
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


