#include "adi_typedef.h"



#ifndef _ADI_COMMON_INTERFACE_H_
#define _ADI_COMMON_INTERFACE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_MAX_PID_NUM     	(10)

typedef enum 
{
	LIVE_E,
	TIMESHIFT_E,
	RECORD_E,
	TIMESHIFT_PLAYBACK_E,
	RECORD_PLAYBACK_E,
	PLAYTYPE_MAX
}PLAYTYPE_E;

typedef enum 
{
	E_SATELLITE = 0x43, // satellite_delivery_system_descriptor
	E_CABLE = 0x44,	// cable_delivery_system_descriptor
	E_TERRESTRIAL = 0x5A // terrestrial_delivery_system_descriptor
}E_Style;


typedef struct 
{
	unsigned short    m_wDemuxId;          
	unsigned short    m_wOrginalNetworkId; 
	unsigned short    m_wTsId;             
	unsigned short    m_wServiceId;        
	unsigned short    m_wPidNum;           
	unsigned short    m_awPid[ADI_MAX_PID_NUM];  
	PLAYTYPE_E   m_ePlayType ;
	void*   m_pUserData;        
}ADICaFtaService_S;

#define MAX_ADIATTRIBDATA_LEN (511)

typedef struct 
{
    unsigned short m_wMsgLength; 
    unsigned char m_aucMessageData[MAX_ADIATTRIBDATA_LEN+1];
    unsigned int  m_eType;		//TMS Type
    
    unsigned int m_bFlash; 
    unsigned int m_bBanner; 
    unsigned char m_ucCoverPer;
    unsigned short m_wDuration;
    unsigned int m_bCovert;	
	
	unsigned short		m_ucLocationX;	
    unsigned short		m_ucLocationY;  
    unsigned char       m_ucBgTransAlpha; 
    unsigned int	    m_dwBgColour;		
    unsigned char       m_ucFontTransAlpha; 
    unsigned int	    m_dwFontColour;	  
    unsigned char		m_ucFontType;
	unsigned int		m_ucResreved;
}ADIAttribCovert_S;

typedef struct
{
	//Copy control Info
	unsigned char   	m_ucMvMode;
    unsigned char   	m_ucMvVersion;
	unsigned char   	m_aucMvData[8];
	unsigned int    	m_unMvLength;
    unsigned char   	m_ucCCIProtocolVersion;
    unsigned char  		m_ucCCIApsInfo;		//uc_copycontrol_cci
    unsigned char 		m_ucCCIEmiInfo;		//uc_copycontrol_cci
    unsigned char   	m_ucCCIIctInfo;
    unsigned char   	m_ucCCIRtcInfo;
    unsigned char   	m_ucCCIRlInfo;
    unsigned char		m_aucReserved[8];
}ADIPVRCopyControlInfo_S;

typedef struct 
{
    unsigned char *m_pcBytes;
    unsigned int m_unLength;
}ADIPVRDataBuffer_S;
typedef struct 
{
	unsigned short    m_wDemuxId;          
	unsigned short    m_wOrginalNetworkId; 
	unsigned short    m_wTsId;             
	unsigned short    m_wServiceId;      
}ADICaServiceInfo_S;
typedef struct 
{
	unsigned short  m_usECMPID;
	unsigned int    m_unECMType; //0 录制 1时移
	unsigned char  *m_pucData;
	unsigned int    m_unDataLen;
	unsigned int    m_unParam;
}ECMData_S;

typedef struct 
{
	ADI_BOOL 	 m_bCAShowOSD;		//是否由CA 显示OSD
	ADI_BOOL 	 m_bCAShowFinger;	//是否由CA 显示Finger
	unsigned int m_unResrvParam;
	unsigned int m_unResrvparam1;
}CACOMMANCONFIG_S;


/*
初始化相关的函数
*/
int ADI_CA_Initialize(void);

/*
	播放相关的接口函数
*/
ADI_HANDLE ADI_CA_StartService(ADICaFtaService_S* pstService);

int ADI_CA_StopService(ADI_HANDLE hService);

int ADI_CA_NewPmtSectionNotify(int nSrvIndex, unsigned char* pcSectionData, int nLen);

int ADI_CA_NewCatSectionNotify (unsigned char* pcSectionData, int nLen, unsigned char cDemux);

int ADI_CA_NewBatSectionNotify (unsigned char* pcSectionData, int nLen, unsigned char cDemux);

int ADI_CA_NewNitSectionNotify (unsigned char* pcSectionData, int nLen, unsigned char cDemux);

int ADI_CA_NewSdtSectionNotify(unsigned char* pcSectionData, int nLen, unsigned char cDemux);

typedef void (*Up2App_F)(unsigned int dwType, unsigned int dwParm1, unsigned int dwParm2, unsigned int dwParm3);
int ADI_CA_RegisterMsgCallback(Up2App_F hcbMsg);

E_Style  ADI_CA_GetFTAType(void);

ADI_BOOL ADI_CA_ShowFingerPrint(ADI_BOOL bShowFlag, ADIAttribCovert_S* p_sPVRFPInfo);
unsigned int ADI_CA_GetFPInfo(ADIAttribCovert_S* p_sPVRFPInfo);
unsigned int ADI_CA_SubPVRMetadata(unsigned char * pucPVRMetadata, unsigned int unPVRMetaLen);
unsigned int ADI_CCA_SetPlaybackStatus(ADI_BOOL bPlaybackStatus);

void StartMenuTest(void);

void ADI_CA_SetCAPrivateConfig(CACOMMANCONFIG_S sCAPrivateConfig);


#ifdef  __cplusplus
}
#endif

#endif 
