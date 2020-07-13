
#ifndef _ADI_PANEL_H_
#define _ADI_PANEL_H_

#include "adi_typedef.h"
#include "adi_error.h"
#include "adi_hdicommon.h"


#ifdef  __cplusplus
extern "C" {
#endif

/*PANEL �豸��ش������ֵ*/
enum
{
	ADIPANEL_ERROR_BAD_PARAMETER = ADI_PANEL_ERROR_BASE,
	ADIPANEL_ERROR_FEATURE_NOT_SUPPORTED,
	ADIPANEL_ERROR_UNKNOWN_ERROR,
	ADIPANEL_ERROR_INVALID_DEVICE_ID
};


/*�����ʾ����ö�ٶ���*/
typedef enum
{
	EM_ADIPANEL_CTRLSTART,       	// ���Ʒ�����ʾ������ʼֵ,����Ϊ���ͱ�ʶ
	
	EM_ADIPANEL_MAIL,     	        // Mail��
	EM_ADIPANEL_SIGNAL,  	        // Signal��
	EM_ADIPANEL_AUDIO, 	       		// Audio��
	EM_ADIPANEL_PLAY, 				// ���� 
	EM_ADIPANEL_PAUSE, 	        	// ��ͣ 
	EM_ADIPANEL_STOP, 				// ֹͣ 
	EM_ADIPANEL_HDTV,				// HDTV 
	EM_ADIPANEL_BACKWARD,           // ����
	EM_ADIPANEL_FORWARD, 	        // ��� 
	EM_ADIPANEL_BALL, 				// Բ
	EM_ADIPANEL_DUBY, 				// �ű� 
	EM_ADIPANEL_PREVIOUS, 	        // ǰһ��
	EM_ADIPANEL_NEXT, 				// ��һ��
	EM_ADIPANEL_IR, 				// ң����
	EM_ADIPANEL_USB, 				// USB
	EM_ADIPANEL_N,					// N
	EM_ADIPANEL_VOD, 				// VOD
	EM_ADIPANEL_POWER, 	        	// ��Դ
	EM_ADIPANEL_TV, 				// ����
	EM_ADIPANEL_NETWORK, 	        // ����
	EM_ADIPANEL_RADIO, 	        	// �㲥
	EM_ADIPANEL_CLOCK,				// ʱ��
	EM_ADIPANEL_MODEM,	        	// MODEM 
	EM_ADIPANEL_REC,				// ¼�� 
	EM_ADIPANEL_UP,					// ��
	EM_ADIPANEL_DOWN,				// ��
	EM_ADIPANEL_LEFT,				// ��
	EM_ADIPANEL_RIGHT,				// ��			
	
	EM_ADIPANEL_CTRLALL,       		// ���Ʒ�����ʾ���ͽ���ֵ
	
	EM_ADIPANEL_TEXTSTART ,         // �ı�����ʾ������ʼֵ,����Ϊ���ͱ�ʶ,TEXT0-TEXT4����������˳������
	
	EM_ADIPANEL_TEXT0,	    	    // ��һ���ı�
	EM_ADIPANEL_TEXT1,              // �ڶ����ı�
	EM_ADIPANEL_TEXT2,	    	    // �������ı�	
	EM_ADIPANEL_TEXT3,              // �������ı�
	EM_ADIPANEL_TEXT4,              // �������ı�
	
	EM_ADIPANEL_TEXTALL,            // �ı�����ʾ���ͽ���ֵ
	
	EM_ADIPANEL_RED,
	EM_ADIPANEL_GREEN,

	EM_ADIPANEL_MAX             // �߽�ֵ	
}ADIPanelLightName_E;

#define ADI_PANEL_IS_TEXT(name)	(  ( (name) > EM_ADIPANEL_TEXTSTART &&  (name) < EM_ADIPANEL_TEXTALL ) || ( (name) > EM_ADIPANEL_EXT_TEXT_START &&  (name) < EM_ADIPANEL_EXT_TEXT_END )  )    // �ж�name�Ƿ����ı�����ʾ����
#define ADI_PANEL_IS_CTRL(name)   (  (  (name) > EM_ADIPANEL_CTRLSTART &&  (name) < EM_ADIPANEL_CTRLALL ) || (  (name) > EM_ADIPANEL_EXT_CTRL_START &&  (name) < EM_ADIPANEL_EXT_CTRL_END ) ) // �ж�name�Ƿ��ǿ��Ʒ�����ʾ����
#define ADI_PANEL_IS_SUIT(name)   (  (  (name) > EM_ADIPANEL_SUITSTART &&  (name) < EM_ADIPANEL_SUITALL ) || (  (name) > EM_ADIPANEL_EXT_SUIT_START &&  (name) < EM_ADIPANEL_EXT_SUIT_END ) ) // �ж�name�Ƿ�����ϵ���ʾ����

/*�ı�����ʾ����������Ϣ*/
typedef struct
{
	int             m_nTextCount;                 // �����ı�֧����ʾ���ַ�����	
}ADIPanelTextLightAttr_S;

/*��ϵ���ʾ����������Ϣ*/
typedef struct
{	
	int m_nSuitCount;                 // ��ϵ��ӵ�����
}ADIPanelSuitLightAttr_S;

/*���Ʒ�����ʾ���͹���ö�ٶ���*/
typedef enum
{
	EM_ADIPANEL_CTRL_OFF		 = 1 << 0,		// �ÿ��Ƶƿ���Ϩ��
	EM_ADIPANEL_CTRL_ON			 = 1 << 1,		// �ÿ��Ƶƿ��Ե���,���֧��color2��ʹ��Ĭ����ɫ��ʾ
	EM_ADIPANEL_CTRL_FLASH		 = 1 << 2,		// �ÿ��Ƶƿ�����˸��Ĭ����ɫ����˸
	EM_ADIPANEL_CTRL_COLOR2		 = 1 << 3,		// �ÿ��Ƶ�֧�ֵڶ�����ɫ
	EM_ADIPANEL_CTRL_COLOR2FLASH = 1 << 4,		// �ÿ��Ƶ�֧���Եڶ�����ɫ��˸
	EM_ADIPANEL_CTRL_COLORSWITCH = 1 << 5       // ���Ƶ�֧��������ɫ������˸
}ADIPanelCtrlLightFun_E;

/*���Ʒ�����ʾ����������Ϣ*/
typedef struct
{
	unsigned int	m_dwCtrFunMask;   // ��ӦλΪ1��ʾ���иù���ֵ,ȡֵΪADIPanelCtrlLightFun_E�и�ֵ���, ����(EM_ADIPANEL_FLASH |EM_ADIPANEL_COLOR2)
}ADIPanelCtrlLightAttr_S;

/*�豸������Ϣ*/
typedef struct
{
	ADIPanelLightName_E m_eLightName;         // ��ʾ�����ƣ���Ҫ����ȷ�ϵ����ͣ����ADIPanelLightName_E
	union
	{
		ADIPanelTextLightAttr_S	m_sText;    // �ı�����ʾ����
		ADIPanelSuitLightAttr_S	m_sSuit;	// ��ϵ���ʾ����
		ADIPanelCtrlLightAttr_S	m_sCtrl;	// ���Ʒ�����ʾ����
	}m_uProperty;                               // ��ʾ�����������Ͻṹ��,����m_eLightName�ֶε�����ȡ��Ӧ��ʾ�豸���������ֶ�
}ADIPanelLightCapability_S;

/*�ı�����ʾ����ö��*/
typedef enum
{
	EM_ADIPANEL_TEXT_STRING,			// �ַ�������
	EM_ADIPANEL_TEXT_TIME			// ʱ������
}ADIPanelTextType_E;

/*�ı�����ʾ���͵���ʾֵ*/
typedef struct
{
	ADIPanelTextType_E  m_eDisplayType;	    // ��ʾ����
	char				m_szStr[32];        // ��m_eDisplayTypeΪ�ı�������Ϊ��ʾ�ַ���,�ַ���������0��β,��Ӧ�ֽ�Ϊ�ո��ʾϨ����ַ�;���ַ������������ӵ��������Գ�������
											// ��m_eDisplayTypeΪʱ������������Ϊyyyymmddhhmmss��ʽ��ʱ��,������ʾ��ʽ��������ŵ���˸��ʽ����ֲ�����и���������ȷ��
    int 				m_nStrCount;        // Ҫ��ʾ���ַ���������󲻳���32���ַ�
}ADIPanelTextValue_S;

/*��ϵ���ʾ���͵���ʾֵ*/
typedef struct
{
	unsigned int	m_dwSuitValueMask;         // �ӵ͵��ߵ�nλ��ֵ��ʾ����е�n���Ƶ�״̬,0��ʾϨ��,1��ʾ����	
}ADIPanelSuitValue_S;


/*���Ʒ�����ʾ���͵���ʾֵ*/
typedef struct
{
	ADIPanelCtrlLightFun_E	m_eCtrlValue;	// ��ʾ�ÿ��ƵƵ���ʾ״̬
}ADIPanelCtrlValue_S;

/*��ʾ���͵���ʾֵ */
typedef struct
{
	ADIPanelLightName_E m_eLightName;         // ��ʾ�����ƣ����ADIPanelLightName_E
	union
	{
		ADIPanelTextValue_S		m_sTextValue;
		ADIPanelSuitValue_S		m_sSuitValue;
		ADIPanelCtrlValue_S		m_sCtrlValue;
	}m_uValue;                         // ��ʾ������ʾֵ���Ͻṹ��,����m_eLightName�ֶε�����ȡ��Ӧ��ʾ�豸���������ֶ�	
}ADIPanelLightValule_S;

/*ǰ������Ͷ���*/
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



