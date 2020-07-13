#ifndef _ADISECURED_H_
#define _ADISECURED_H_

#include "adi_os.h"
#include "adi_typedef.h"
#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif


typedef enum _SecuredType
{
    SECURED_NACHIPSET_NASECURED,   
    SECURED_CHIPSET_SECURED,       
    SECURED_CHIPSET_NASECURED   	
}SecuredType_EM;

typedef enum _Algorithm
{
    ALGORITHM_TEDS  
}Algorithm_E;

typedef enum _SCWCaType
{
    EM_SCW_UNKNOWN_CA = 0,
    EM_SCW_CONAX_CA,  
    EM_SCW_VIACCESS_CA , 
    EM_SCW_TONGFANG_CA ,
    EM_SCW_DVN_CA , 
    EM_SCW_CRYPTOWORKS_CA , 
    EM_SCW_MEDIAGUARD_CA , 
    EM_SCW_SUMAVISION_CA ,
    EM_SCW_ST_CA,
    EM_SCW_NAGRAVISON_CA , 
    EM_SCW_IRDETO_CA 
}E_SCW_CaType;


typedef enum _SecIOCtlType
{
	EM_SEC_SET_BOOTROM = 0,  
	EM_SEC_GET_BOOTROM,	 
	EM_SEC_SET_JTAGKEY,      
	EM_SEC_GET_JTAGKEY,      
	EM_SEC_SET_JTAGLOCK,     
	EM_SEC_GET_JTAGLOCK,     
	EM_SEC_SET_SCW,          
	EM_SEC_GET_SCW,	         
	EM_SEC_SET_BY_APP,       
	EM_SEC_GET_BY_APP,       
	EM_SEC_SET_MARKETID,     
	EM_SEC_GET_MARKETID      
}E_SecIOCtlType;

#define SEC_MAX_DATA_SIZE	32
#define SEC_MAX_CONFIG_NUM	8

typedef struct _SECSetParam
{
	ADI_BOOL 	m_bBulkData;				
	int  	m_nItem;						
	unsigned int 	m_dwLocation;					
	unsigned int	m_dwSize;						
	unsigned char	m_aucData[SEC_MAX_DATA_SIZE];	
}SECSetParam_S;

typedef struct _SECConfigParam
{
	int 			m_nItemCount;          
	SECSetParam_S	m_stSetParam[SEC_MAX_CONFIG_NUM];
}SECConfigParam_S;

#ifndef SUCCESS
#define SUCCESS (0)
#endif

#ifndef FAILURE
#define FAILURE (-1)
#endif

typedef struct _SECDsmInfo
{
	unsigned int 	m_dwDescrambleID; 
	unsigned int   m_dwKeyType     : 1; 
	unsigned int 	m_dwNotSumCheck : 1;
	unsigned int   m_dwReserved    : 30;
}SECDsmInfo_S;



int ADICASCWInit(void);
int ADICASCWGetSecuredType(SecuredType_EM* pemSecuredType);
unsigned int ADICASCWGetChipId(void);
int ADICASCWProcessCW(unsigned char *pcInputKey, unsigned char cLength, unsigned char *pcOutputKey, ADI_BOOL bIsClearCW, unsigned int dwPara);
int ADICASCWLoadCWPK(unsigned char *pcKey, unsigned char cLength, unsigned int dwPara);
int ADICASCWEncryptData(unsigned char* pucCPCW, ADI_BOOL bIsCBC,ADI_BOOL bIsNeedCBCVector,int nVentorLen,unsigned char* pucVector,
						unsigned char* pucSrcBuf, int nLen,Algorithm_E emType, unsigned char* pucDesBuf);
int ADICASCWDecryptData(unsigned char* pucCPCW,ADI_BOOL bIsCBC, ADI_BOOL bIsNeedCBCVentor,int nVentorLen,unsigned char* pucVentor,
						unsigned char* pucSrcBuf, int nLen,Algorithm_E emType, unsigned char* pucDesBuf);

void ADICASCWSetCAType(E_SCW_CaType emType, unsigned int dwPara);
int ADICASecureIoctl(int nDeviceIndex, E_SecIOCtlType emSecIOCtlType, unsigned int * pParams);



#ifdef  __cplusplus
}
#endif

#endif 

