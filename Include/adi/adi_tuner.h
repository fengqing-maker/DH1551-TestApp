
#ifndef _ADI_TUNER_H_
#define _ADI_TUNER_H_

#include "adi_typedef.h"
#include "adi_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

    /*tunerģ����ش������ֵ*/
    enum
    {
        ADITUNER_ERROR_BAD_PARAMETER = ADI_TUNER_ERROR_BASE,
        ADITUNER_ERROR_FEATURE_NOT_SUPPORTED,
        ADITUNER_ERROR_UNKNOWN,
        ADITUNER_ERROR_NO_MEMORY,
        ADITUNER_ERROR_INVALID_DEVICE_ID,
        ADITUNER_ERROR_I2C_ERROR,
        ADITUNER_ERROR_NO_CALLBACK,
        ADITUNER_ERROR_NO_DATA,
        ADITUNER_ERROR_ALREADY_ADDED,
        ADITUNER_ERROR_BUSY
    };

    /*QAM ��������ö�ٶ���*/
    typedef enum
    {
        EM_ADITUNER_NOT_DEFINED,	// δ�����QAM������һ������±�����Ч����
        EM_ADITUNER_QAM16,			// 16QAM����
        EM_ADITUNER_QAM32,			// 32QAM����
        EM_ADITUNER_QAM64,			// 64QAM����
        EM_ADITUNER_QAM128,			// 128QAM����
        EM_ADITUNER_QAM256,			// 256QAM���� 
        EM_ADITUNER_QAMAUTO
    }ADITunerQAMMode_E;

    /*�������ֵ���(DVB-C)tuner���źŲ������ݽṹ*/
    typedef struct
    {
        unsigned int m_uFrequency;					  // Ƶ�ʣ���λKHz
        unsigned int m_uSymbolRate_24 : 24;  // �����ʣ���λKbps
        unsigned int m_uModulation_8 : 8;	  // ADITunerQAMMode_E����ö��
    }ADITunerCableDeliver_S;

    /*tunerģ�鿪������ö�ٶ���*/
    typedef enum
    {
        EM_ADITUNER_SWITCH_OFF,	// ���عر�
        EM_ADITUNER_SWITCH_ON	// ���ش�
    }ADITunerSwitchStatus_E;


    /*cofdm �źŴ�������ö�ٶ���*/
    typedef enum
    {
        EM_ADITUNER_BAND_8M,    //����8M 
        EM_ADITUNER_BAND_7M,    //����7M
        EM_ADITUNER_BAND_6M     //����6M
    }ADITunerBanuidth_E;

	typedef enum
	{
		EM_ADITUNER_DVBT,
		EM_ADITUNER_DVBT2,
		EM_ADITUNER_AUTO	
	}ADITunerDVBTType_E;

    /*�������ֵ���(DVB-T)tuner���źŲ������ݽṹ*/
    typedef struct
    {
        unsigned int m_uFrequency;					    // Ƶ�ʣ���λKHz
        unsigned int m_uBanuidth_3 : 3;	 	// ADITunerBanuidth_E����ö��
        unsigned int m_uFlag_2 : 2;		///DVB-T/DVB-T2��־:��ο�ADITunerDVBTType_E����ö��
        unsigned int m_uPlpID_8 : 8;     ///T2�洢PLPID
        unsigned int m_uReserved_19 : 19;  	// ����ʹ�� 
    }ADITunerTerrestrialDeliver_S;

    /*QPSK����Diseqc1.0�˿�����ö�ٶ���*/
    typedef enum
    {
        EM_ADITUNER_DISEQC10_OFF,	// diseqc1.0ͨ��ѡ��ر�
        EM_ADITUNER_PORT_4_A,		// diseqc1.0��ѡһ���ص�Aͨ��
        EM_ADITUNER_PORT_4_B,		// diseqc1.0��ѡһ���ص�Bͨ��
        EM_ADITUNER_PORT_4_C,		// diseqc1.0��ѡһ���ص�Cͨ��
        EM_ADITUNER_PORT_4_D,		// diseqc1.0��ѡһ���ص�Dͨ��
        EM_ADITUNER_PORT_2_A,		// diseqc1.0��ѡһ���ص�Aͨ��
        EM_ADITUNER_PORT_2_B		// diseqc1.0��ѡһ���ص�Bͨ��
    }ADITunerSwitchDisqec10Port_E;

    /*QPSK�����źż�������ö�ٶ���*/
    typedef enum
    {
        EM_ADITUNER_POLARISATION_H,		// �߼�������-ˮƽ����
        EM_ADITUNER_POLARISATION_V,		// �߼�������-��ֱ����
        EM_ADITUNER_POLARISATION_L,     // Բ��������-��������
        EM_ADITUNER_POLARISATION_R      // Բ��������-��������
    }ADITunerChannelPolar_E;

    /*QPSK����Tone burst ����*/
    typedef enum
    {
        EM_ADITUNER_TONEBURST_NONE,		// Tone burstѡ��ر�
        EM_ADITUNER_TONEBURST_A,		// Tone burstѡ��Aͨ��
        EM_ADITUNER_TONEBURST_B			// Tone burstѡ��Bͨ��
    }ADITunerSwitchToneBurst_E;

    /*QPSK����Diseqc�����ظ���������*/
    typedef enum
    {
        EM_ADITUNER_NOREPEAT,		// û��DiSEqC Repeat 
        EM_ADITUNER_ONCEREPEAT,		// ��Ҫһ��DiSEqC Repeat
        EM_ADITUNER_TWICEREPEAT		// ��Ҫ����DiSEqC Repeat
    }ADITunerRepeatTime_E;

    /*QPSK����Diseqc1.2������ת��������*/
    typedef enum
    {
        EM_ADITUNER_EASTERN,		// ��ת��
        EM_ADITUNER_WESTERN		    // ����ת��
    }ADITunerRotateDirection_E;

    /*QPSK����LNB���Ͷ���*/
    typedef enum
    {
        EM_ADITUNER_SINGLE,				    // ������LNB 
        EM_ADITUNER_UNIVERSAL,				// ˫����ͨ��LNB:  �߱���22K�򿪣��ͱ���22K�ر�
        EM_ADITUNER_UNIVERSAL_NEGLOGIC		// ˫����LNB: �߱���22K�رգ��ͱ���22K��
    }ADITunerLNBType_E;

    /*QPSK����12����ѹѡ���LNB��ѹ����*/
    typedef enum
    {
        EM_ADITUNER_SWITCH_0V,		// 0���ص�ѹѡ�� 
        EM_ADITUNER_SWITCH_12V		// 12���ص�ѹѡ��
    }ADITunerSwitch012V_E;

    /*QPSK�����е�FEC�����Ͷ���*/
    typedef enum
    {
        EM_ADITUNER_FEC_AUTO,		// FEC��ʽ�Զ�ѡ�� 
        EM_ADITUNER_FEC1_2,			// 1/2��ʽ��FEC
        EM_ADITUNER_FEC2_3,			// 2/3��ʽ��FEC
        EM_ADITUNER_FEC3_4,			// 3/4��ʽ��FEC
        EM_ADITUNER_FEC5_6,			// 5/6��ʽ��FEC 
        EM_ADITUNER_FEC7_8,			// 7/8��ʽ��FEC
        EM_ADITUNER_FEC8_9,			// 8/9��ʽ��FEC
        EM_ADITUNER_FEC3_5,			// 3/5��ʽ��FEC 
        EM_ADITUNER_FEC4_5,			// 4/5��ʽ��FEC
        EM_ADITUNER_FEC9_10,		// 9/10��ʽ��FEC
        EM_ADITUNER_FEC6_7			// 6/7��ʽ��FEC 
    }ADITunerQPSKFECRates_E;

    /*DVB-S/S2�г��õĵ��Ʒ�ʽ����*/
    typedef enum
    {
        EM_ADITUNER_AUTO_PSK,		// QPSK��8PSK�Զ�ʶ��ʽ
        EM_ADITUNER_QPSK,	        // QPSK���Ʒ�ʽ
        EM_ADITUNER_8PSK		    // 8PSK���Ʒ�ʽ
    }ADITunerQPSKModulation_E;

    /*�������ֵ��ӵı�׼����*/
    typedef enum
    {
        EM_ADITUNER_DVBS_STANDARD,		    // DVB-S��׼�ź� 
        EM_ADITUNER_DVBS2_STANDARD,		    // DVB-S2��׼�ź�
        EM_ADITUNER_DVBS_AUTO_STANDARD  	// DVB-S��DVB-S2�Զ�ʶ��
    }ADITunerQPSKStandard_E;


    /*QPSK����Unicable�е��������ѡ��(һ��Unicable LNB ͬʱ���֧��2������, ����A������B)*/
    typedef enum
    {
        EM_ADITUNER_OPTION_NONE,		// û�п�ѡ���� 
        EM_ADITUNER_OPTION_A,			// Unicableѡ������A
        EM_ADITUNER_OPTION_B			// Unicableѡ������B
    }ADITunerQPSKOption_E;

    /*QPSK����Unicable�е�������������ѡ��һ��Unicable LNB ���֧��8������*/
    typedef enum
    {
        EM_ADITUNER_UNICABLE_NONE,			    // Unicable LNB δ����
        EM_ADITUNER_UNICABLE_A_LB_VP,			// Unicable LNB ѡ��:satellite A, Low Band, Vertical Polarization
        EM_ADITUNER_UNICABLE_A_HB_VP,			// Unicable LNB ѡ��:satellite A, High Band, Vertical Polarization
        EM_ADITUNER_UNICABLE_A_LB_HP,			// Unicable LNB ѡ��:satellite A, Low Band, Horizontal Polarization
        EM_ADITUNER_UNICABLE_A_HB_HP,			// Unicable LNB ѡ��:satellite A, High  Band, Horizontal Polarization
        EM_ADITUNER_UNICABLE_B_LB_VP,			// Unicable LNB ѡ��:satellite B, Low Band,  Vertical Polarization
        EM_ADITUNER_UNICABLE_B_HB_VP,			// Unicable LNB ѡ��:satellite B, High  Band, Vertical Polarization
        EM_ADITUNER_UNICABLE_B_LB_HP,			// Unicable LNB ѡ��:satellite B, Low Band, Horizontal Polarization
        EM_ADITUNER_UNICABLE_B_HB_HP			// Unicable LNB ѡ��:satellite B, High  Band, Horizontal Polarization
    }ADITunerQPSKUnicableLNBType_E;

    /*QPSK����Unicable�е�UB Number*/
    typedef enum
    {
        EM_ADITUNER_UNICABLE_UB_NONE,		// Unicable UB δ����
        EM_ADITUNER_UNICABLE_UB_1,			// Unicable UB 1
        EM_ADITUNER_UNICABLE_UB_2,			// Unicable UB 2
        EM_ADITUNER_UNICABLE_UB_3,			// Unicable UB 3
        EM_ADITUNER_UNICABLE_UB_4,			// Unicable UB 4
        EM_ADITUNER_UNICABLE_UB_5,			// Unicable UB 5
        EM_ADITUNER_UNICABLE_UB_6,			// Unicable UB 6
        EM_ADITUNER_UNICABLE_UB_7,			// Unicable UB 7
        EM_ADITUNER_UNICABLE_UB_8,			// Unicable UB 8
        EM_ADITUNER_UNICABLE_UB_MAX
    }ADITunerQPSKUnicableUB_E;

    /*QPSK�����е�LNB��ѹ״̬����*/
    typedef enum
    {
        EM_ADITUNER_LNB_OFF,		// LNB��ѹ�ر�
        EM_ADITUNER_LNB_AUTO,		// LNB��ѹѡ���Զ� 
        EM_ADITUNER_LNB_14V,		// LNB��ѹѡ��14����
        EM_ADITUNER_LNB_18V		    // LNB��ѹѡ��18����
    }ADITunerQPSKLNBStatus_E;

    /*QPSK����������DVB-S2�еĵ�Ƶ���ض���*/
    typedef enum
    {
        EM_ADITUNER_PILOT_OFF,		// ��Ƶ�� 
        EM_ADITUNER_PILOT_ON		// ��Ƶ�ر� 
    }ADITunerQPSKPilot_E;

    /*���ǵ���tuner���ź����ݽṹ(ͬʱ����DVB-S/S2)*/
    typedef struct
    {
        unsigned int	m_uFrequency;					// Ƶ�ʣ���λKHz
        unsigned int	m_uSymbolRate_24 : 24;	// �����ʣ���λKbps
        unsigned int	m_uFECInner_4 : 4;		// ADITunerQPSKFECRates_E ����ö��
        unsigned int	m_uPolar_4 : 4;		// ADITunerChannelPolar_E ����ö��
        unsigned int	m_uPilot;                      	// ADITunerQPSKPilot_E ����ö��,DVB_S2�ź�ר��
        unsigned int	m_uModulations_2 : 2;			// ADITunerQPSKModulation_E ����ö��
        unsigned int    m_uStandards_2 : 2;			// ADITunerQPSKStandard_E ����ö�� 
        unsigned int	m_uReserved_28 : 28;		// ����ʹ��
    }ADITunerSatelliteDeliver_S;

    /*�������ֵ���(DVB-S/S2)tuner��DiSEqC1.0��׼�Ĳ���*/
    typedef struct
    {
        unsigned int m_uCommitted : 4;		// ADITunerSwitchDisqec10Port_E ����ö��
        unsigned int m_uToneburst : 2;		// ADITunerSwitchToneBurst_E ����ö��
        unsigned int m_uRepeatedTimes : 2;		// �ظ�����ADITunerRepeatTime_E ����ö��
        unsigned int m_uReserved : 24;	// ����ʹ��
    }ADITunerDiSEqC1020_S;

    /*�������ֵ���(DVB-S/S2)tuner��DiSEqC1.1��׼�Ĳ���*/
    typedef struct
    {
        unsigned int m_uCommitted : 4;		// DiSEqC1.0�˿�,��ADITunerSwitchDisqec10Port_E ����ö��
        unsigned int m_uUncommitted : 8;		// DiSEqC1.1�˿�, 1----16
        unsigned int m_uToneburst : 2;     // ADITunerSwitchToneBurst_E ����ö��
        unsigned int m_uRepeatedTimes : 2;		// �ظ�����ADITunerRepeatTime_E ����ö��
        unsigned int m_uReserved : 16;	// ����ʹ��
    }ADITunerDiSEqC1121_S;

    /*�������ֵ���(DVB-S/S2)tuner��DiSEqC1.2��׼�Ĳ���*/
    typedef struct
    {
        unsigned int m_uUsals : 2;		// ��תλ�ã�λ��ֵȡ��m_uIndex 2 -�����û����õľ�γ�Ƚ�����Ӧת������
        unsigned int m_uIndex : 5;		// ��ת����λ��ֵ��
        unsigned int m_uReserved : 25;	// ����ʹ��
    }ADITunerDiSEqC1222_S;


    /*�������ֵ���(DVB-S/S2)tuner������λ�ò����ṹ(ͬʱ����DVB-S/S2)*/
    typedef struct
    {
        double m_dLocalLongitude;					// ���صľ���λ��(����ֵ*10,��DTV�ж���һ��)
        double m_dLatitude;							// ���ص�γ��λ��(γ��ֵ*10,��DTV�ж���һ��)
        double m_dSatLongitude;						// �������ڵľ���λ��(����ֵ*10,��DTV�ж���һ��)
        unsigned int m_uWestEastFlag : 1;		// �������ڵ�λ�õĶ�������־��0 -EM_ADITUNER_EASTERN, 1 - EM_ADITUNER_WESTERN
        unsigned int m_uReserved : 31;	// ����ʹ��
    }ADITunerSatellitePar_S;

    /*�������ֵ���(DVB-S/S2)tuner��LNB�������ݽṹ*/
    typedef struct
    {
        unsigned int m_uLowFrequency;				// low LNB frequency in Universal Mod or LNB frequency in Single Mod [unit:KHz]
        unsigned int m_uHighFrequency;				// high LNB frequency in Universal Mod [unit:KHz]
        unsigned int m_uCenterFrequency;			// middle LNB frequency in Universal Mod [unit:KHz]
        unsigned int m_uSatCRNo : 16;        // �໧���õ��ŵ�·����(SatCR)��ͨ��ѡ��, ADITunerQPSKUnicableUB_E
        unsigned int m_uSatCRLNBNo : 16;		// �໧���õ��ŵ�·����(SatCR)��LNBѡ��, ADITunerQPSKOption_Eö�����Ͷ���
        unsigned int m_uLnbType : 4;			// ��Ƶͷ����ADITunerLNBType_E ����ö��
        unsigned int m_uLnbPower : 2;			// ADITunerSwitchStatus_E ����ö��
        unsigned int m_uOptions : 2;     	//�໧���õ��ŵ�·����(SatCR)������ѡ��, ADITunerQPSKOption_Eö�����Ͷ���
        unsigned int m_uReserved : 24;		// ����ʹ��
    }ADITunerLNB_S;

    /*�������ֵ���(DVB-S/S2)tuner�����߲����ݽṹ(ͬʱ����DVB-S/S2)*/
    typedef struct
    {
        unsigned int m_uSwitch22k : 1;  // ADITunerSwitchStatus_E ����ö��
        unsigned int m_uSwith12v : 1;  // ADITunerSwitch012V_E����ö��
        unsigned int m_uDisEqCType : 1;  // ��չʹ��
        unsigned int m_uAntennaKey : 8;  // ��չʹ��
        unsigned int m_uReserved : 21; // ����ʹ��
    }ADITunerAntennaPar_S;

    /*tunerģ��ͳһ���ź�Ƶ�ʡ�������ƫ�����ݽṹ*/
    typedef struct
    {
        unsigned int m_uOffsetFrequency_23 : 23;	// Ƶ�ʵ�ƫ��ֵ����λKHz
        unsigned int m_uOffsetSymbolRate_8 : 8;		// �����ʵ�ƫ��ֵ����λKbps
        unsigned int m_uIQ_1 : 1;		// 0-Normal; 1-Inverse
    }ADITunerTransponderOffset_S;

    /*���ǵ���tuner�Ĵ�disqec��Ϣ���ź����ݽṹ(ͬʱ����DVB-S/S2)*/
    typedef struct
    {
        ADITunerSatelliteDeliver_S  m_sSatelliteDeliver;	 // ���ǻ�Ƶ����Ϣ�ṹ��
        ADITunerLNB_S				m_sLNB;			         // ��Ƶͷ��Ϣ�ṹ��
        ADITunerDiSEqC1020_S		m_sDiSEqC1020;           // diseq1.0��Ϣ�ṹ��
        ADITunerDiSEqC1121_S		m_sDiSEqC1121;           // diseq1.1��Ϣ�ṹ��
        ADITunerDiSEqC1222_S		m_sDiSEqC1222;           // diseq1.2��Ϣ�ṹ��
        ADITunerSatellitePar_S		m_sSatellitePar;	     // ���ǲ�����Ϣ�ṹ��
        ADITunerAntennaPar_S		m_sAntennaPar;           // ���߲�����Ϣ�ṹ��
        ADITunerTransponderOffset_S	m_sTransponderOffset;	 // Ƶ��ƫ��ֵ��Ϣ�ṹ��
    }ADITunerSRCSatelliteDeliver_S;


    /*tunerģ��ͳһ�źŲ�������*/
    typedef union
    {
        ADITunerCableDeliver_S			m_sCableDeliver;            // ���߻�Ƶ����Ϣ�ṹ��
        ADITunerSRCSatelliteDeliver_S	m_sSourceSatelliteDeliver;	// ���ǻ�Ƶ����Ϣ�ṹ��
        ADITunerTerrestrialDeliver_S	m_sTerrestrialDeliver;      // �����Ƶ����Ϣ�ṹ��
    }ADITunerSRCDeliver_U;

    /*tuner ���Ͷ���*/
    typedef enum
    {
        EM_ADITUNER_TYPE_UNKNOWN,
        EM_ADITUNER_TYPE_QAM,		//  ����tuner����,��Ҫ����QAM���Ʒ�ʽ
        EM_ADITUNER_TYPE_COFDM,	   	//  ����tuner����,��Ҫ����COFDM���Ʒ�ʽ
        EM_ADITUNER_TYPE_QPSK		//  ����tuner����,��Ҫ����QPSK,8PSK���Ʒ�ʽ
    }ADITunerType_E;

    /*tuner���ݴ������Ͷ���*/
    typedef enum
    {
        EM_ADITUNER_DATATRANSFER_UNKNOWN,	// �Ƿ�ֵ
        EM_ADITUNER_DATATRANSFER_DMA,		// DMA���ݴ���ģʽ��Ƶͷ����������DMA��ʽֱ�Ӵ��䵽Demux�������������Ҫʹ��DMA���͵�Demux���к���
        EM_ADITUNER_DATATRANSFER_SOFT		// ��ע�����ݴ���ģʽ�ĸ�Ƶͷ���������������ʽע�뵽Demux�������������Ҫʹ��INJECT���͵�Demux���к��������н�����ע�뵽Demux
    }ADITunerDataTransferType_E;

    /*Tuner�ź���Ϣ����ö�ٶ��� */
    typedef enum
    {
        EM_ADITUNER_SIGNAL_QUALITY = 1 << 0,       //�ź�����
        EM_ADITUNER_SIGNAL_STRENGTH = 1 << 1,       // �ź�ǿ�ȣ��ȼ�
        EM_ADITUNER_ERROR_RATE = 1 << 2,       // ������
        EM_ADITUNER_SIGNAL_LEVEL = 1 << 3,       // �ź������ƽ
        EM_ADITUNER_SIGNAL_CN = 1 << 4,       //�ź������
        EM_ADITUNER_CUR_FREQU = 1 << 5        //�ź�Ƶ��
    }ADITunerSignalInfoType_E;

    /*tuner�豸������Ϣ����*/
    typedef struct
    {
        ADITunerType_E m_eType;	   					// Tuner����
        ADITunerDataTransferType_E m_eTransferType;	// Tuner���ݴ���ģʽ
        ADI_BOOL m_bPIDFilterSupport;				// �Ƿ�֧��PID���ˣ����ָ�Ƶͷ��֧�ֽ�������PID������������Լ��ٴ�������ע����ʽ�ĸ�Ƶͷ��DVB-TH��CMMB����ʽ�ĸ�Ƶͷ�ر�����
    }ADITunerInfo_S;


    typedef enum
    {
        EM_ADITUNER_SIGNAL_CONNECTED,   // Ƶ�������ɹ�
        EM_ADITUNER_SIGNAL_LOST,        // ������תΪʧ��ʱ���ʹ���Ϣ
        EM_ADITUNER_SIGNAL_SEARCHING    // ����Ϣ��ʾ��Ƶʧ�ܣ��������������Ƶ��ֱ����Ƶ�ɹ��������������������������Ƶ����л�������Ҫ������Ϣ��
    }ADITunerCallbackEvent_E;

    /*tuner�ص���Ϣ���ݽṹ����*/
    typedef struct
    {
        unsigned int  			m_unTunerId;	// �ص���Ϣ��Ӧ��Tuner�豸��
        ADITunerCallbackEvent_E m_eEvent;		// ��ǰ��ADITunerCallbackEvents_E���� 
        ADITunerSRCDeliver_U    m_unDeliver;
        void *        			m_pvUserData;	// �û���ע��ص�����ʱ�����ָ��
    }ADITunerCallbackMessage_S;

    typedef  void ( *ADITunerCallback )( ADITunerType_E eType, ADITunerCallbackMessage_S* psMessage );

    /*tuner�ź���Ϣ���ݽṹ����*/
    typedef struct
    {
        int 		 m_nQuality;			// �ź�������0��100��
        int		     m_nStrength;		    // �ź�ǿ�ȣ�0 ��100��
        int		     m_nErrorRate;	        // �����ʣ�1*10^7����Ԫ�д�����Ԫ�ĸ�����(����10^7�͵õ������ʣ�,ʧ��ʱ��������Ϊ1*10^7����100%���롣	
        unsigned int m_nCurrentFreq;	    // ���������ȡ���ź�Ƶ��,unit[KHz]
        double 		 m_dSignalLevel;	    // �źŵ�ƽ,��ȷ��С�����һλ,unit(QAM: dBuv; COFDM: dBm; QPSK:dBm)	
        double 		 m_dSignalCN;	        // �����,��ȷ��С�����һλ, unit[dB]
        int		     m_nReserved [ 3 ];	    // �������� m_nReserved[0]:�����ʵ�������������
                                            //m_nReserved[1]:�����ʵ�����С�����ֳ���1000
                                            //m_nReserved[2]:������ָ������ȡ����ֵ
                                            //����:������Ϊ2.156E-7����ô����Ԫ�ص�ȡֵ�ֱ�Ϊ
                                            //2��156��7
    }ADITunerSignalInfo_S;


    /* äɨ�õ���Ƶ����Ϣ */
    typedef struct _ADITunerBlindScanTPInfo
    {
        unsigned char	m_ucPolarity;		// POLARISATION_H | POLARISATION_V 
        unsigned short	m_wSymbolrate_Kbps;	// The symbol rate in units of Kbps. 
        unsigned int	m_dwFrequency_KHz;	// The channel carrier frequency in units of KHz. 
    }ADITunerBlindScanTPInfo_S;


    /*  the blind scan status information. */
    typedef enum _ADITunerBlindScanStatus
    {
        EM_ADITuner_BLINDSCAN_FAILED,	// 0 Indicates that the blind scan process has failed.
        EM_ADITuner_BLINDSCAN_CANCEL,	// 1 Indicates that the blind scan process has canceled.
        EM_ADITuner_BLINDSCAN_SCANNING,	// 2 Indicates that the blind scan process is still scanning.
        EM_ADITuner_BLINDSCAN_SUCCESS	// 3 Indicates that the blind scan process has successed.
    }ADITunerBlindScanStatus_E;


    /* ����äɨcallback ����Ϣ */
    typedef struct _ADITunerBlindScanCallBackPar
    {
        unsigned char  	m_ucLNBType;						// SINGLE | UNIVERSAL 
        unsigned short 	m_wBlindScanedChanNum;				// the blind scaned channels number 
        ADITunerBlindScanStatus_E m_eBlindScanStatus;	// the blind scan status
        unsigned int	m_dwBlindScanCurrFreq_KHz;			// the blind scan current frequency
        unsigned int 	m_dwLNBLowFreq_KHz;					// low LNB frequency in Universal Mod or LNB frequency in Single Mod [unit:KHz] 
        unsigned int 	m_dwLNBMidFreq_KHz;					// middle LNB frequency in Universal Mod  [unit:KHz] 
        unsigned int 	m_dwLNBHighFreq_KHz;				// high LNB frequency in Universal Mod   [unit:KHz] 
        ADITunerBlindScanTPInfo_S *m_psBlindScanTPInfo;	// the blind scaned channel's TP information ,���� m_wBlindScanedChanNum ��CSQPSKBlindScanTPInfo_S��Ϣ������׵�ַ
    }ADITunerBlindScanCallBackPar_S;


    /* ���äɨ��callback�����ڶ�ɨ������Ϣ����Ӧ�Ĵ���,ʵ��callback �Ŀ����߱��뼰ʱ��m_psBlindScanTPInfo �е�����copy ��*/
    typedef  void ( *ADITunerBlindScanCallback )( unsigned int, const ADITunerBlindScanCallBackPar_S * ,void *pvUserdata);


    /*���ǵ���tuner��äɨ�ź����ݽṹ(ͬʱ����DVB-S/S2)*/
    typedef struct _ADITunerBlindScanPar
    {
        unsigned char		m_ucFECInner;				// ADITunerQPSKFECRates_E ����ö��
        unsigned char		m_ucPolar;					// ADITunerChannelPolar_E ����ö��
        unsigned char		m_ucPilot;					// ADITunerQPSKPilot_E ����ö��,DVB_S2�ź�ר��
        unsigned char		m_ucModulations;			// ADITunerQPSKModulation_E ����ö��
        unsigned char		m_ucStandards;				// ADITunerQPSKStandard_E ����ö�� 
        unsigned char		m_ucBSMode;					//  The Blind scan mode.	Fast Mode = 0,Slow Mode = 1
        //    0: Freq Step forward is 20.7MHz      1: Freq Step forward is 10MHz    
        unsigned char		m_ucReserved;				// reserved for future use

        unsigned short		m_wMinSymbolrate_Kbps;		// The minimum symbol rate to be scanned in units of kbps. The minimum value is 1000 kbps,default value is seted 1000 kbps.
        unsigned short		m_wMaxSymbolrate_Kbps;		// The maximum symbol rate to be scanned in units of kbps. The maximum value is 45000 kbps.default value is seted 45000 kbps.
        unsigned int		m_dwStartFreq_KHz;			// The start scan frequency in units of KHz. The minimum value depends on the tuner specification. 
        unsigned int		m_dwEndFreq_KHz;			// The stop scan frequency in units of KHz. The maximum value depends on the tuner specification.
        unsigned char		m_ucIsHiLOF;				// �ߵͱ���ѡ��TRUE:�߱���FALSE:�ͱ���.
    }ADITunerBlindScanPar_S;


    typedef struct _ADITunerBlindScanDeliver
    {
        ADITunerBlindScanPar_S		m_sBlindscanPar;		//���ǵ���tuner���ź����ݽṹ(ͬʱ����DVB-S/S2)
        ADITunerLNB_S				m_sLNB;					// ��Ƶͷ��Ϣ�ṹ��
        ADITunerDiSEqC1020_S		m_sDiSEqC1020;			// diseq1.0��Ϣ�ṹ��
        ADITunerDiSEqC1121_S		m_sDiSEqC1121;			// diseq1.1��Ϣ�ṹ��
        ADITunerDiSEqC1222_S		m_sDiSEqC1222;			// diseq1.2��Ϣ�ṹ��
        ADITunerSatellitePar_S		m_sSatellitePar;		// ���ǲ�����Ϣ�ṹ��
        ADITunerAntennaPar_S		m_sAntennaPar;			// ���߲�����Ϣ�ṹ��
        ADITunerTransponderOffset_S	m_sTransponderOffset;	// Ƶ��ƫ��ֵ��Ϣ�ṹ��
        ADITunerBlindScanCallback	m_pBlindScanCallback;	// the blind scan callback function to handle scaned TP information.Should be seted by the app.  
        void *						pvCallbackUserData;		// �ص�����ʱ�����ָ��
    }ADITunerBlindScanDeliver_S;

	typedef struct
	{
		ADITunerInfo_S m_stTunerInfo[4];
		int n_nCount; // actually supported tuner type
	}ADITunerInfoList; 
		
    ADI_Error_Code ADITunerGetAllDeviceId ( unsigned int aunTunerIds [ ], int nMaxIdCnt, int * pnActIdCnt );

    ADI_Error_Code ADITunerBlindScanStart ( unsigned int unTunerId, ADITunerBlindScanDeliver_S *psBlindScanDeliver );

    ADI_Error_Code ADITunerBlindScanStop ( unsigned int unTunerId );

    ADI_Error_Code ADITunerConnect ( unsigned int unTunerId, const ADITunerSRCDeliver_U* punDeliver );
	
	ADI_Error_Code ADITunerConnectEx ( unsigned int unTunerId, const ADITunerSRCDeliver_U* punDeliver, ADITunerType_E eType);

	ADI_Error_Code ADITunerSetPolar(unsigned int unTunerId,ADITunerChannelPolar_E ePolar);
	
    ADI_Error_Code ADITunerAddCallback ( unsigned int unTunerId, ADITunerCallback  fnTunerCallback, void *pvUserData );

    ADI_Error_Code ADITunerDelCallback ( unsigned int unTunerId, ADITunerCallback  fnTunerCallback, void *pvUserData );

    ADI_Error_Code ADITunerGetDeviceInfo ( unsigned int  unTunerId, ADITunerInfo_S*   psTunerInfo );

	ADI_Error_Code ADITunerGetDeviceInfoEx ( unsigned int  unTunerId, ADITunerInfoList *psTunerInfoList);

    ADI_Error_Code ADITunerGetSignalInfo ( unsigned int unTunerId, unsigned int u32SignalInfoMask, ADITunerSignalInfo_S *psSignalInfo );

	//LockStatus:0 ��ʾ��������1 ��ʾδ����
    ADI_Error_Code ADITunerGetLockStatus ( unsigned int unTunerId, int *pnLockStatus );

	ADI_Error_Code ADITunerSetAntennaPowerEnable( unsigned int unTunerId, ADI_BOOL bEnable );
	
	ADI_Error_Code ADITunerGetAntennaPowerEnable( unsigned int unTunerId, ADI_BOOL *bEnable );

	ADI_Error_Code ADITunerSetSaTCRBPF(ADITunerQPSKUnicableUB_E nSatCRNo, unsigned int nBPF);
	
	//-----------------------------------------------------------------------------------------
//���ӿ�ΪDVB-T2ר��
//-----------------------------------------------------------------------------------------
	ADI_Error_Code ADITunerT2GetPlpInfo ( unsigned int unTunerId, unsigned char ucPlpIds[ ], int nPlpIdsCount, int *pnRetIdCount );

#ifdef __cplusplus
}
#endif

#endif 

