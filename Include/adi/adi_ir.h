
#ifndef _ADI_IR_PLUS_H_
#define _ADI_IR_PLUS_H_

#include  "adi_hdicommon.h"
#include  "adi_typedef.h"
#include  "adi_error.h"
#ifdef __cplusplus
extern "C" {
#endif

/*最大遥控器数量*/
#define MAX_IR_EQUIPMENT	10


enum
{
	ADIIR_ERROR_BAD_PARAMETER = ADI_IR_ERROR_BASE,
	ADIIR_ERROR_ALREADY_INIT,
	ADIIR_ERROR_EQUIPMENT_FULL,
	ADIIR_ERROR_EQUIPMENT_EXIST,
	ADIIR_ERROR_SEMPHA_CREATE,
	ADIIR_ERROR_TASK_CREATE,
	ADIIR_ERROR_PIO_SET
};


/*enum of IR protocols */ 
typedef  enum _ADIIRProtocol_E
{
	EM_ADIIR_PROTOCOL_NEC,			// NEC协议		
	EM_ADIIR_PROTOCOL_PHILIPS_RC6,	// Philips_RC6协议
	EM_ADIIR_PROTOCOL_PHILIPS,		// Philips协议
	EM_ADIIR_PROTOCOL_TOPWAY,		// 普通天威1  型遥控器
	EM_ADIIR_PROTOCOL_RC5,			// Philips_RC5协议
	EM_ADIIR_PROTOCOL_TOPWAY_II,	// 天威2型遥控器
	EM_ADIIR_PROTOCOL_TOPWAY_GZ,	// 天威广州协议
	EM_ADIIR_PROTOCOL_GD,  			// 广东省网新的协议类型
	EM_ADIIR_PROTOCOL_GD2000,		// GD2000协议 哥伦比亚
	EM_ADIIR_PROTOCOL_TC9012,		// TC9012协议 印度A3
	EM_ADIIR_PROTOCOL_RCMM,         // Philips rcmm遥控器协议(墨西哥电信telmex项目)
	EM_ADIIR_PROTOCOL_RF0,			// RF遥控器
	EM_ADIIR_PROTOCOL_READI80,		// Philips recs-80协议(ABSCBN项目)
	EM_ADIIR_PROTOCOL_PHILIPS_RCMM,	// Philips RCMM协议
	EM_ADIIR_PROTOCOL_NUM
}ADIIRProtocol_E;


typedef struct _ADIIRDebug_t
{
	ADIKeyStatus_E	m_ucKeyStatus;		/**< 按键状态，表示按键按下或弹起 */
	unsigned int	m_dwUserID;			/**< 遥控器厂家码，用于识别遥控器类型 */
	int  			m_dwKeyCode;		/**< 遥控器按键的电气编码 */
}ADIIRDebug_t;


typedef struct _ADIIRDecode_S
{
	int 		m_nKeyValue;     		// real key value(scan code)
	int	 		m_nLogicValue;   		// logic value
	ADI_BOOL  	    m_bIsRepeat;     		// whether to generate repeat keys
}ADIIRDecode_S;

typedef struct _ADIIREquipList_S
{
	ADIIRProtocol_E	m_enmIRProtocol; // 协议
	unsigned int	m_dwUserID;		 // 用户码
    int 			m_nKeyNumber;	 // 按键数
	ADIIRDecode_S *	m_ptKey;		 // 映射表
} ADIIREquipList_S;	

ADI_Error_Code ADIIRInitialize( int nPriority, int nStackSize );

ADI_Error_Code ADIIRAddEquipment( const ADIIREquipList_S	* ptIREquip, unsigned int * phIRHandle );

ADI_Error_Code ADIIRDelEquipment( unsigned int phIRHandle );

ADI_Error_Code ADIIRAddKeySendCallback( ADIKeyCallback_F KeySendCallback );

ADI_Error_Code ADIIRAddKeyDebugCallback( ADIKeyCallback_F KeyDebugCallback );


#ifdef __cplusplus
}
#endif


#endif   

