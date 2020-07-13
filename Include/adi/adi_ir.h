
#ifndef _ADI_IR_PLUS_H_
#define _ADI_IR_PLUS_H_

#include  "adi_hdicommon.h"
#include  "adi_typedef.h"
#include  "adi_error.h"
#ifdef __cplusplus
extern "C" {
#endif

/*���ң��������*/
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
	EM_ADIIR_PROTOCOL_NEC,			// NECЭ��		
	EM_ADIIR_PROTOCOL_PHILIPS_RC6,	// Philips_RC6Э��
	EM_ADIIR_PROTOCOL_PHILIPS,		// PhilipsЭ��
	EM_ADIIR_PROTOCOL_TOPWAY,		// ��ͨ����1  ��ң����
	EM_ADIIR_PROTOCOL_RC5,			// Philips_RC5Э��
	EM_ADIIR_PROTOCOL_TOPWAY_II,	// ����2��ң����
	EM_ADIIR_PROTOCOL_TOPWAY_GZ,	// ��������Э��
	EM_ADIIR_PROTOCOL_GD,  			// �㶫ʡ���µ�Э������
	EM_ADIIR_PROTOCOL_GD2000,		// GD2000Э�� ���ױ���
	EM_ADIIR_PROTOCOL_TC9012,		// TC9012Э�� ӡ��A3
	EM_ADIIR_PROTOCOL_RCMM,         // Philips rcmmң����Э��(ī�������telmex��Ŀ)
	EM_ADIIR_PROTOCOL_RF0,			// RFң����
	EM_ADIIR_PROTOCOL_READI80,		// Philips recs-80Э��(ABSCBN��Ŀ)
	EM_ADIIR_PROTOCOL_PHILIPS_RCMM,	// Philips RCMMЭ��
	EM_ADIIR_PROTOCOL_NUM
}ADIIRProtocol_E;


typedef struct _ADIIRDebug_t
{
	ADIKeyStatus_E	m_ucKeyStatus;		/**< ����״̬����ʾ�������»��� */
	unsigned int	m_dwUserID;			/**< ң���������룬����ʶ��ң�������� */
	int  			m_dwKeyCode;		/**< ң���������ĵ������� */
}ADIIRDebug_t;


typedef struct _ADIIRDecode_S
{
	int 		m_nKeyValue;     		// real key value(scan code)
	int	 		m_nLogicValue;   		// logic value
	ADI_BOOL  	    m_bIsRepeat;     		// whether to generate repeat keys
}ADIIRDecode_S;

typedef struct _ADIIREquipList_S
{
	ADIIRProtocol_E	m_enmIRProtocol; // Э��
	unsigned int	m_dwUserID;		 // �û���
    int 			m_nKeyNumber;	 // ������
	ADIIRDecode_S *	m_ptKey;		 // ӳ���
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

