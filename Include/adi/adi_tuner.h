
#ifndef _ADI_TUNER_H_
#define _ADI_TUNER_H_

#include "adi_typedef.h"
#include "adi_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

    /*tuner模块相关错误代码值*/
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

    /*QAM 星座类型枚举定义*/
    typedef enum
    {
        EM_ADITUNER_NOT_DEFINED,	// 未定义的QAM星座，一般情况下标是无效参数
        EM_ADITUNER_QAM16,			// 16QAM星座
        EM_ADITUNER_QAM32,			// 32QAM星座
        EM_ADITUNER_QAM64,			// 64QAM星座
        EM_ADITUNER_QAM128,			// 128QAM星座
        EM_ADITUNER_QAM256,			// 256QAM星座 
        EM_ADITUNER_QAMAUTO
    }ADITunerQAMMode_E;

    /*有线数字电视(DVB-C)tuner的信号参数数据结构*/
    typedef struct
    {
        unsigned int m_uFrequency;					  // 频率，单位KHz
        unsigned int m_uSymbolRate_24 : 24;  // 符号率，单位Kbps
        unsigned int m_uModulation_8 : 8;	  // ADITunerQAMMode_E类型枚举
    }ADITunerCableDeliver_S;

    /*tuner模块开关类型枚举定义*/
    typedef enum
    {
        EM_ADITUNER_SWITCH_OFF,	// 开关关闭
        EM_ADITUNER_SWITCH_ON	// 开关打开
    }ADITunerSwitchStatus_E;


    /*cofdm 信号带宽类型枚举定义*/
    typedef enum
    {
        EM_ADITUNER_BAND_8M,    //带宽8M 
        EM_ADITUNER_BAND_7M,    //带宽7M
        EM_ADITUNER_BAND_6M     //带宽6M
    }ADITunerBanuidth_E;

	typedef enum
	{
		EM_ADITUNER_DVBT,
		EM_ADITUNER_DVBT2,
		EM_ADITUNER_AUTO	
	}ADITunerDVBTType_E;

    /*地面数字电视(DVB-T)tuner的信号参数数据结构*/
    typedef struct
    {
        unsigned int m_uFrequency;					    // 频率，单位KHz
        unsigned int m_uBanuidth_3 : 3;	 	// ADITunerBanuidth_E类型枚举
        unsigned int m_uFlag_2 : 2;		///DVB-T/DVB-T2标志:请参考ADITunerDVBTType_E类型枚举
        unsigned int m_uPlpID_8 : 8;     ///T2存储PLPID
        unsigned int m_uReserved_19 : 19;  	// 保留使用 
    }ADITunerTerrestrialDeliver_S;

    /*QPSK驱动Diseqc1.0端口类型枚举定义*/
    typedef enum
    {
        EM_ADITUNER_DISEQC10_OFF,	// diseqc1.0通道选择关闭
        EM_ADITUNER_PORT_4_A,		// diseqc1.0四选一开关的A通道
        EM_ADITUNER_PORT_4_B,		// diseqc1.0四选一开关的B通道
        EM_ADITUNER_PORT_4_C,		// diseqc1.0四选一开关的C通道
        EM_ADITUNER_PORT_4_D,		// diseqc1.0四选一开关的D通道
        EM_ADITUNER_PORT_2_A,		// diseqc1.0二选一开关的A通道
        EM_ADITUNER_PORT_2_B		// diseqc1.0二选一开关的B通道
    }ADITunerSwitchDisqec10Port_E;

    /*QPSK驱动信号极化方向枚举定义*/
    typedef enum
    {
        EM_ADITUNER_POLARISATION_H,		// 线极化方向-水平极化
        EM_ADITUNER_POLARISATION_V,		// 线极化方向-垂直极化
        EM_ADITUNER_POLARISATION_L,     // 圆极化方向-左旋极化
        EM_ADITUNER_POLARISATION_R      // 圆极化方向-右旋极化
    }ADITunerChannelPolar_E;

    /*QPSK驱动Tone burst 定义*/
    typedef enum
    {
        EM_ADITUNER_TONEBURST_NONE,		// Tone burst选择关闭
        EM_ADITUNER_TONEBURST_A,		// Tone burst选择A通道
        EM_ADITUNER_TONEBURST_B			// Tone burst选择B通道
    }ADITunerSwitchToneBurst_E;

    /*QPSK驱动Diseqc命令重复次数定义*/
    typedef enum
    {
        EM_ADITUNER_NOREPEAT,		// 没有DiSEqC Repeat 
        EM_ADITUNER_ONCEREPEAT,		// 需要一次DiSEqC Repeat
        EM_ADITUNER_TWICEREPEAT		// 需要两次DiSEqC Repeat
    }ADITunerRepeatTime_E;

    /*QPSK驱动Diseqc1.2中天线转动方向定义*/
    typedef enum
    {
        EM_ADITUNER_EASTERN,		// 向东转动
        EM_ADITUNER_WESTERN		    // 向西转动
    }ADITunerRotateDirection_E;

    /*QPSK驱动LNB类型定义*/
    typedef enum
    {
        EM_ADITUNER_SINGLE,				    // 单本振LNB 
        EM_ADITUNER_UNIVERSAL,				// 双本振通用LNB:  高本振22K打开，低本振22K关闭
        EM_ADITUNER_UNIVERSAL_NEGLOGIC		// 双本振LNB: 高本振22K关闭，低本振22K打开
    }ADITunerLNBType_E;

    /*QPSK驱动12伏电压选择的LNB电压定义*/
    typedef enum
    {
        EM_ADITUNER_SWITCH_0V,		// 0伏特电压选择 
        EM_ADITUNER_SWITCH_12V		// 12伏特电压选择
    }ADITunerSwitch012V_E;

    /*QPSK驱动中的FEC的类型定义*/
    typedef enum
    {
        EM_ADITUNER_FEC_AUTO,		// FEC方式自动选择 
        EM_ADITUNER_FEC1_2,			// 1/2方式的FEC
        EM_ADITUNER_FEC2_3,			// 2/3方式的FEC
        EM_ADITUNER_FEC3_4,			// 3/4方式的FEC
        EM_ADITUNER_FEC5_6,			// 5/6方式的FEC 
        EM_ADITUNER_FEC7_8,			// 7/8方式的FEC
        EM_ADITUNER_FEC8_9,			// 8/9方式的FEC
        EM_ADITUNER_FEC3_5,			// 3/5方式的FEC 
        EM_ADITUNER_FEC4_5,			// 4/5方式的FEC
        EM_ADITUNER_FEC9_10,		// 9/10方式的FEC
        EM_ADITUNER_FEC6_7			// 6/7方式的FEC 
    }ADITunerQPSKFECRates_E;

    /*DVB-S/S2中常用的调制方式定义*/
    typedef enum
    {
        EM_ADITUNER_AUTO_PSK,		// QPSK和8PSK自动识别方式
        EM_ADITUNER_QPSK,	        // QPSK调制方式
        EM_ADITUNER_8PSK		    // 8PSK调制方式
    }ADITunerQPSKModulation_E;

    /*卫星数字电视的标准定义*/
    typedef enum
    {
        EM_ADITUNER_DVBS_STANDARD,		    // DVB-S标准信号 
        EM_ADITUNER_DVBS2_STANDARD,		    // DVB-S2标准信号
        EM_ADITUNER_DVBS_AUTO_STANDARD  	// DVB-S和DVB-S2自动识别
    }ADITunerQPSKStandard_E;


    /*QPSK驱动Unicable中的卫星序号选择(一个Unicable LNB 同时最多支持2个卫星, 卫星A和卫星B)*/
    typedef enum
    {
        EM_ADITUNER_OPTION_NONE,		// 没有可选卫星 
        EM_ADITUNER_OPTION_A,			// Unicable选择卫星A
        EM_ADITUNER_OPTION_B			// Unicable选择卫星B
    }ADITunerQPSKOption_E;

    /*QPSK驱动Unicable中的卫星天线类型选择，一个Unicable LNB 最多支持8种类型*/
    typedef enum
    {
        EM_ADITUNER_UNICABLE_NONE,			    // Unicable LNB 未定义
        EM_ADITUNER_UNICABLE_A_LB_VP,			// Unicable LNB 选择:satellite A, Low Band, Vertical Polarization
        EM_ADITUNER_UNICABLE_A_HB_VP,			// Unicable LNB 选择:satellite A, High Band, Vertical Polarization
        EM_ADITUNER_UNICABLE_A_LB_HP,			// Unicable LNB 选择:satellite A, Low Band, Horizontal Polarization
        EM_ADITUNER_UNICABLE_A_HB_HP,			// Unicable LNB 选择:satellite A, High  Band, Horizontal Polarization
        EM_ADITUNER_UNICABLE_B_LB_VP,			// Unicable LNB 选择:satellite B, Low Band,  Vertical Polarization
        EM_ADITUNER_UNICABLE_B_HB_VP,			// Unicable LNB 选择:satellite B, High  Band, Vertical Polarization
        EM_ADITUNER_UNICABLE_B_LB_HP,			// Unicable LNB 选择:satellite B, Low Band, Horizontal Polarization
        EM_ADITUNER_UNICABLE_B_HB_HP			// Unicable LNB 选择:satellite B, High  Band, Horizontal Polarization
    }ADITunerQPSKUnicableLNBType_E;

    /*QPSK驱动Unicable中的UB Number*/
    typedef enum
    {
        EM_ADITUNER_UNICABLE_UB_NONE,		// Unicable UB 未定义
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

    /*QPSK驱动中的LNB电压状态定义*/
    typedef enum
    {
        EM_ADITUNER_LNB_OFF,		// LNB电压关闭
        EM_ADITUNER_LNB_AUTO,		// LNB电压选择自动 
        EM_ADITUNER_LNB_14V,		// LNB电压选择14伏特
        EM_ADITUNER_LNB_18V		    // LNB电压选择18伏特
    }ADITunerQPSKLNBStatus_E;

    /*QPSK驱动中用于DVB-S2中的导频开关定义*/
    typedef enum
    {
        EM_ADITUNER_PILOT_OFF,		// 导频打开 
        EM_ADITUNER_PILOT_ON		// 导频关闭 
    }ADITunerQPSKPilot_E;

    /*卫星电视tuner的信号数据结构(同时满足DVB-S/S2)*/
    typedef struct
    {
        unsigned int	m_uFrequency;					// 频率，单位KHz
        unsigned int	m_uSymbolRate_24 : 24;	// 符号率，单位Kbps
        unsigned int	m_uFECInner_4 : 4;		// ADITunerQPSKFECRates_E 类型枚举
        unsigned int	m_uPolar_4 : 4;		// ADITunerChannelPolar_E 类型枚举
        unsigned int	m_uPilot;                      	// ADITunerQPSKPilot_E 类型枚举,DVB_S2信号专用
        unsigned int	m_uModulations_2 : 2;			// ADITunerQPSKModulation_E 类型枚举
        unsigned int    m_uStandards_2 : 2;			// ADITunerQPSKStandard_E 类型枚举 
        unsigned int	m_uReserved_28 : 28;		// 保留使用
    }ADITunerSatelliteDeliver_S;

    /*卫星数字电视(DVB-S/S2)tuner中DiSEqC1.0标准的参数*/
    typedef struct
    {
        unsigned int m_uCommitted : 4;		// ADITunerSwitchDisqec10Port_E 类型枚举
        unsigned int m_uToneburst : 2;		// ADITunerSwitchToneBurst_E 类型枚举
        unsigned int m_uRepeatedTimes : 2;		// 重复次数ADITunerRepeatTime_E 类型枚举
        unsigned int m_uReserved : 24;	// 保留使用
    }ADITunerDiSEqC1020_S;

    /*卫星数字电视(DVB-S/S2)tuner中DiSEqC1.1标准的参数*/
    typedef struct
    {
        unsigned int m_uCommitted : 4;		// DiSEqC1.0端口,见ADITunerSwitchDisqec10Port_E 类型枚举
        unsigned int m_uUncommitted : 8;		// DiSEqC1.1端口, 1----16
        unsigned int m_uToneburst : 2;     // ADITunerSwitchToneBurst_E 类型枚举
        unsigned int m_uRepeatedTimes : 2;		// 重复次数ADITunerRepeatTime_E 类型枚举
        unsigned int m_uReserved : 16;	// 保留使用
    }ADITunerDiSEqC1121_S;

    /*卫星数字电视(DVB-S/S2)tuner中DiSEqC1.2标准的参数*/
    typedef struct
    {
        unsigned int m_uUsals : 2;		// 需转位置，位置值取自m_uIndex 2 -根据用户设置的经纬度进行相应转锅操作
        unsigned int m_uIndex : 5;		// 需转到的位置值。
        unsigned int m_uReserved : 25;	// 保留使用
    }ADITunerDiSEqC1222_S;


    /*卫星数字电视(DVB-S/S2)tuner的卫星位置参数结构(同时满足DVB-S/S2)*/
    typedef struct
    {
        double m_dLocalLongitude;					// 本地的经度位置(经度值*10,和DTV中定义一致)
        double m_dLatitude;							// 本地的纬度位置(纬度值*10,和DTV中定义一致)
        double m_dSatLongitude;						// 卫星所在的经度位置(经度值*10,和DTV中定义一致)
        unsigned int m_uWestEastFlag : 1;		// 卫星所在的位置的东西方标志：0 -EM_ADITUNER_EASTERN, 1 - EM_ADITUNER_WESTERN
        unsigned int m_uReserved : 31;	// 保留使用
    }ADITunerSatellitePar_S;

    /*卫星数字电视(DVB-S/S2)tuner的LNB参数数据结构*/
    typedef struct
    {
        unsigned int m_uLowFrequency;				// low LNB frequency in Universal Mod or LNB frequency in Single Mod [unit:KHz]
        unsigned int m_uHighFrequency;				// high LNB frequency in Universal Mod [unit:KHz]
        unsigned int m_uCenterFrequency;			// middle LNB frequency in Universal Mod [unit:KHz]
        unsigned int m_uSatCRNo : 16;        // 多户联用的信道路由器(SatCR)的通道选择, ADITunerQPSKUnicableUB_E
        unsigned int m_uSatCRLNBNo : 16;		// 多户联用的信道路由器(SatCR)的LNB选择, ADITunerQPSKOption_E枚举类型定义
        unsigned int m_uLnbType : 4;			// 高频头类型ADITunerLNBType_E 类型枚举
        unsigned int m_uLnbPower : 2;			// ADITunerSwitchStatus_E 类型枚举
        unsigned int m_uOptions : 2;     	//多户联用的信道路由器(SatCR)的卫星选择, ADITunerQPSKOption_E枚举类型定义
        unsigned int m_uReserved : 24;		// 保留使用
    }ADITunerLNB_S;

    /*卫星数字电视(DVB-S/S2)tuner的天线参数据结构(同时满足DVB-S/S2)*/
    typedef struct
    {
        unsigned int m_uSwitch22k : 1;  // ADITunerSwitchStatus_E 类型枚举
        unsigned int m_uSwith12v : 1;  // ADITunerSwitch012V_E类型枚举
        unsigned int m_uDisEqCType : 1;  // 扩展使用
        unsigned int m_uAntennaKey : 8;  // 扩展使用
        unsigned int m_uReserved : 21; // 保留使用
    }ADITunerAntennaPar_S;

    /*tuner模块统一的信号频率、符号率偏移数据结构*/
    typedef struct
    {
        unsigned int m_uOffsetFrequency_23 : 23;	// 频率的偏移值，单位KHz
        unsigned int m_uOffsetSymbolRate_8 : 8;		// 符号率的偏移值，单位Kbps
        unsigned int m_uIQ_1 : 1;		// 0-Normal; 1-Inverse
    }ADITunerTransponderOffset_S;

    /*卫星电视tuner的带disqec信息的信号数据结构(同时满足DVB-S/S2)*/
    typedef struct
    {
        ADITunerSatelliteDeliver_S  m_sSatelliteDeliver;	 // 卫星机频点信息结构体
        ADITunerLNB_S				m_sLNB;			         // 高频头信息结构体
        ADITunerDiSEqC1020_S		m_sDiSEqC1020;           // diseq1.0信息结构体
        ADITunerDiSEqC1121_S		m_sDiSEqC1121;           // diseq1.1信息结构体
        ADITunerDiSEqC1222_S		m_sDiSEqC1222;           // diseq1.2信息结构体
        ADITunerSatellitePar_S		m_sSatellitePar;	     // 卫星参数信息结构体
        ADITunerAntennaPar_S		m_sAntennaPar;           // 天线参数信息结构体
        ADITunerTransponderOffset_S	m_sTransponderOffset;	 // 频点偏移值信息结构体
    }ADITunerSRCSatelliteDeliver_S;


    /*tuner模块统一信号参数定义*/
    typedef union
    {
        ADITunerCableDeliver_S			m_sCableDeliver;            // 有线机频点信息结构体
        ADITunerSRCSatelliteDeliver_S	m_sSourceSatelliteDeliver;	// 卫星机频点信息结构体
        ADITunerTerrestrialDeliver_S	m_sTerrestrialDeliver;      // 地面机频点信息结构体
    }ADITunerSRCDeliver_U;

    /*tuner 类型定义*/
    typedef enum
    {
        EM_ADITUNER_TYPE_UNKNOWN,
        EM_ADITUNER_TYPE_QAM,		//  有线tuner类型,主要采用QAM调制方式
        EM_ADITUNER_TYPE_COFDM,	   	//  地面tuner类型,主要采用COFDM调制方式
        EM_ADITUNER_TYPE_QPSK		//  卫星tuner类型,主要采用QPSK,8PSK调制方式
    }ADITunerType_E;

    /*tuner数据传输类型定义*/
    typedef enum
    {
        EM_ADITUNER_DATATRANSFER_UNKNOWN,	// 非法值
        EM_ADITUNER_DATATRANSFER_DMA,		// DMA数据传输模式高频头，即数据以DMA形式直接传输到Demux，这种情况下需要使用DMA类型的Demux进行后处理
        EM_ADITUNER_DATATRANSFER_SOFT		// 软注入数据传输模式的高频头，即数据以软件形式注入到Demux，这种情况下需要使用INJECT类型的Demux进行后处理，并自行将数据注入到Demux
    }ADITunerDataTransferType_E;

    /*Tuner信号信息类型枚举定义 */
    typedef enum
    {
        EM_ADITUNER_SIGNAL_QUALITY = 1 << 0,       //信号质量
        EM_ADITUNER_SIGNAL_STRENGTH = 1 << 1,       // 信号强度，等级
        EM_ADITUNER_ERROR_RATE = 1 << 2,       // 误码率
        EM_ADITUNER_SIGNAL_LEVEL = 1 << 3,       // 信号输入电平
        EM_ADITUNER_SIGNAL_CN = 1 << 4,       //信号载噪比
        EM_ADITUNER_CUR_FREQU = 1 << 5        //信号频率
    }ADITunerSignalInfoType_E;

    /*tuner设备能力信息定义*/
    typedef struct
    {
        ADITunerType_E m_eType;	   					// Tuner类型
        ADITunerDataTransferType_E m_eTransferType;	// Tuner数据传输模式
        ADI_BOOL m_bPIDFilterSupport;				// 是否支持PID过滤，部分高频头可支持仅将部分PID的数据输出，以减少带宽，对软注入形式的高频头，DVB-TH，CMMB等形式的高频头特别有用
    }ADITunerInfo_S;


    typedef enum
    {
        EM_ADITUNER_SIGNAL_CONNECTED,   // 频点锁定成功
        EM_ADITUNER_SIGNAL_LOST,        // 由锁定转为失锁时发送此消息
        EM_ADITUNER_SIGNAL_SEARCHING    // 此消息表示锁频失败，但会继续尝试锁频，直到锁频成功。正常情况下在两个能锁定的频点间切换，不需要发此消息。
    }ADITunerCallbackEvent_E;

    /*tuner回调消息数据结构定义*/
    typedef struct
    {
        unsigned int  			m_unTunerId;	// 回调消息对应的Tuner设备号
        ADITunerCallbackEvent_E m_eEvent;		// 见前面ADITunerCallbackEvents_E定义 
        ADITunerSRCDeliver_U    m_unDeliver;
        void *        			m_pvUserData;	// 用户在注册回调函数时传入的指针
    }ADITunerCallbackMessage_S;

    typedef  void ( *ADITunerCallback )( ADITunerType_E eType, ADITunerCallbackMessage_S* psMessage );

    /*tuner信号信息数据结构定义*/
    typedef struct
    {
        int 		 m_nQuality;			// 信号质量（0～100）
        int		     m_nStrength;		    // 信号强度（0 ～100）
        int		     m_nErrorRate;	        // 误码率，1*10^7个码元中错误码元的个数．(除以10^7就得到误码率）,失锁时，误码率为1*10^7，即100%误码。	
        unsigned int m_nCurrentFreq;	    // 用来保存获取的信号频率,unit[KHz]
        double 		 m_dSignalLevel;	    // 信号电平,精确到小数点后一位,unit(QAM: dBuv; COFDM: dBm; QPSK:dBm)	
        double 		 m_dSignalCN;	        // 载噪比,精确到小数点后一位, unit[dB]
        int		     m_nReserved [ 3 ];	    // 保留参数 m_nReserved[0]:误码率底数的整数部分
                                            //m_nReserved[1]:误码率底数的小数部分乘以1000
                                            //m_nReserved[2]:误码率指数部分取绝对值
                                            //例如:误码率为2.156E-7，那么三个元素的取值分别为
                                            //2、156和7
    }ADITunerSignalInfo_S;


    /* 盲扫得到的频点信息 */
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


    /* 传给盲扫callback 的信息 */
    typedef struct _ADITunerBlindScanCallBackPar
    {
        unsigned char  	m_ucLNBType;						// SINGLE | UNIVERSAL 
        unsigned short 	m_wBlindScanedChanNum;				// the blind scaned channels number 
        ADITunerBlindScanStatus_E m_eBlindScanStatus;	// the blind scan status
        unsigned int	m_dwBlindScanCurrFreq_KHz;			// the blind scan current frequency
        unsigned int 	m_dwLNBLowFreq_KHz;					// low LNB frequency in Universal Mod or LNB frequency in Single Mod [unit:KHz] 
        unsigned int 	m_dwLNBMidFreq_KHz;					// middle LNB frequency in Universal Mod  [unit:KHz] 
        unsigned int 	m_dwLNBHighFreq_KHz;				// high LNB frequency in Universal Mod   [unit:KHz] 
        ADITunerBlindScanTPInfo_S *m_psBlindScanTPInfo;	// the blind scaned channel's TP information ,它是 m_wBlindScanedChanNum 个CSQPSKBlindScanTPInfo_S信息数组的首地址
    }ADITunerBlindScanCallBackPar_S;


    /* 针对盲扫的callback，用于对扫到的信息做相应的处理,实现callback 的开发者必须及时把m_psBlindScanTPInfo 中的数据copy 走*/
    typedef  void ( *ADITunerBlindScanCallback )( unsigned int, const ADITunerBlindScanCallBackPar_S * ,void *pvUserdata);


    /*卫星电视tuner的盲扫信号数据结构(同时满足DVB-S/S2)*/
    typedef struct _ADITunerBlindScanPar
    {
        unsigned char		m_ucFECInner;				// ADITunerQPSKFECRates_E 类型枚举
        unsigned char		m_ucPolar;					// ADITunerChannelPolar_E 类型枚举
        unsigned char		m_ucPilot;					// ADITunerQPSKPilot_E 类型枚举,DVB_S2信号专用
        unsigned char		m_ucModulations;			// ADITunerQPSKModulation_E 类型枚举
        unsigned char		m_ucStandards;				// ADITunerQPSKStandard_E 类型枚举 
        unsigned char		m_ucBSMode;					//  The Blind scan mode.	Fast Mode = 0,Slow Mode = 1
        //    0: Freq Step forward is 20.7MHz      1: Freq Step forward is 10MHz    
        unsigned char		m_ucReserved;				// reserved for future use

        unsigned short		m_wMinSymbolrate_Kbps;		// The minimum symbol rate to be scanned in units of kbps. The minimum value is 1000 kbps,default value is seted 1000 kbps.
        unsigned short		m_wMaxSymbolrate_Kbps;		// The maximum symbol rate to be scanned in units of kbps. The maximum value is 45000 kbps.default value is seted 45000 kbps.
        unsigned int		m_dwStartFreq_KHz;			// The start scan frequency in units of KHz. The minimum value depends on the tuner specification. 
        unsigned int		m_dwEndFreq_KHz;			// The stop scan frequency in units of KHz. The maximum value depends on the tuner specification.
        unsigned char		m_ucIsHiLOF;				// 高低本振选择，TRUE:高本振；FALSE:低本振.
    }ADITunerBlindScanPar_S;


    typedef struct _ADITunerBlindScanDeliver
    {
        ADITunerBlindScanPar_S		m_sBlindscanPar;		//卫星电视tuner的信号数据结构(同时满足DVB-S/S2)
        ADITunerLNB_S				m_sLNB;					// 高频头信息结构体
        ADITunerDiSEqC1020_S		m_sDiSEqC1020;			// diseq1.0信息结构体
        ADITunerDiSEqC1121_S		m_sDiSEqC1121;			// diseq1.1信息结构体
        ADITunerDiSEqC1222_S		m_sDiSEqC1222;			// diseq1.2信息结构体
        ADITunerSatellitePar_S		m_sSatellitePar;		// 卫星参数信息结构体
        ADITunerAntennaPar_S		m_sAntennaPar;			// 天线参数信息结构体
        ADITunerTransponderOffset_S	m_sTransponderOffset;	// 频点偏移值信息结构体
        ADITunerBlindScanCallback	m_pBlindScanCallback;	// the blind scan callback function to handle scaned TP information.Should be seted by the app.  
        void *						pvCallbackUserData;		// 回调函数时传入的指针
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

	//LockStatus:0 表示已锁定；1 表示未锁定
    ADI_Error_Code ADITunerGetLockStatus ( unsigned int unTunerId, int *pnLockStatus );

	ADI_Error_Code ADITunerSetAntennaPowerEnable( unsigned int unTunerId, ADI_BOOL bEnable );
	
	ADI_Error_Code ADITunerGetAntennaPowerEnable( unsigned int unTunerId, ADI_BOOL *bEnable );

	ADI_Error_Code ADITunerSetSaTCRBPF(ADITunerQPSKUnicableUB_E nSatCRNo, unsigned int nBPF);
	
	//-----------------------------------------------------------------------------------------
//本接口为DVB-T2专用
//-----------------------------------------------------------------------------------------
	ADI_Error_Code ADITunerT2GetPlpInfo ( unsigned int unTunerId, unsigned char ucPlpIds[ ], int nPlpIdsCount, int *pnRetIdCount );

#ifdef __cplusplus
}
#endif

#endif 

