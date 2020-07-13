
#ifndef _ADI_DESCRAMBLE_H_
#define _ADI_DESCRAMBLE_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif 

enum
{
	ADIDSM_ERROR_BAD_PARAMETER = ADI_DESCRAMBLE_ERROR_BASE,
	ADIDSM_ERROR_INVALID_HANDLE,
	ADIDSM_ERROR_INVALID_DEVICE_ID,
	ADIDSM_ERROR_INVALID_STATUS,
	ADIDSM_ERROR_FEATURE_NOT_SUPPORTED,
	ADIDSM_ERROR_NO_FREE_DESCRAMBLER,
	ADIDSM_ERROR_NO_MEMORY
};

typedef enum
{
    E_ADIDSM_KL_TDES = 0,                                      /// < Algorithm used in key ladder: TDES
    E_ADIDSM_KL_AES,                                           /// < Algorithm used in key ladder: AES

    E_ADIDSM_KL_ALGO_MAX
} ADIDSMAlgorithm_E;

typedef enum
{
	E_ADIDSM_DK_ALGO_UNKNOWN       ,
    E_ADIDSM_DK_ALGO_DVB_CSA       , //DVB-CSA1/2.
    E_ADIDSM_DK_ALGO_AES_128_RCBC  , //AES-128 RCBC or CSA3
    E_ADIDSM_DK_ALGO_AES_128_CBC   , //AES-128 CBC(CI+AES)
    E_ADIDSM_DK_ALGO_MULTI2        , //	Multi-2 Scrambling mode, 64 bit key.
	E_ADIDSM_DK_ALGO_DES_56_ECB    , //DES-56-ECB(CI+DES)
    E_ADIDSM_DK_ALGO_DEFAULT = 0xF,
    E_ADIDSM_DK_ALGO_NUM,
} ADIDSMAlgoType_E;


typedef struct 
{
	ADIDSMAlgorithm_E eKLAlgo;
}ADIDSMKLOpenParams_S;


typedef enum
{
   
    E_ADIDSM_KEY_PROTECTION_UNKNOWN =0,
    E_ADIDSM_KEY_PROTECTION_TDES =1,
    E_ADIDSM_KEY_PROTECTION_CLEAR =2,
    E_ADIDSM_KEY_PROTECTION_AES =3
} ADIDSMKeyProtect_E;


typedef enum
{	
   E_ADIDSM_KEY_EVEN = 0,
   E_ADIDSM_KEY_ODD,
   
} ADIDSMKeyType_E;

//keyladder type
typedef enum 
{
    E_ADIDSM_KL_CW = 0,
    E_ADIDSM_KL_PVR,
} ADIDSMKLType_E;

typedef enum 
{
    E_ADIDSM_CA_INVALID = 0,
    E_ADIDSM_CA_NDS = 1,
    E_ADIDSM_CA_NAGRA = 2,
    E_ADIDSM_CA_VIACCESS = 3,
    E_ADIDSM_CA_IRDETO = 4,
    E_ADIDSM_CA_VMX = 5,
    E_ADIDSM_CA_SMI = 6,
    E_ADIDSM_CA_CONAX = 7,
    E_ADIDSM_CA_LATENS = 8,
    E_ADIDSM_CA_DRM = 9,
    E_ADIDSM_CA_DRE = 10,
    E_ADIDSM_CA_CTI = 11,
    E_ADIDSM_CA_SUMA = 12,
    E_ADIDSM_CA_TFCA = 13,
    E_ADIDSM_CA_NSTV = 14,
    E_ADIDSM_CA_BESTCAS = 15,
    E_ADIDSM_CA_CI_PLUS = 16,
    E_ADIDSM_CA_MAX,
} ADIDSMCAType_E;


typedef struct 
{
	ADIDSMKeyProtect_E  eKeyProtect;  //ADI_FALSE 为非高安，ADI_TRUE 为高安
	ADIDSMKeyType_E     eKeyType;
	ADIDSMAlgoType_E    eAlgoType;
	unsigned char       *pucKey; 
	unsigned int        unLength;
	unsigned char       *pucIV;
	unsigned int        unIVLength;
}ADIDSMKeyInfo_S;



//Only for Irdeto Cloak4.5
typedef struct IFCP_image
{
	//Activation message.
	unsigned char *m_pActivationMessage;
	unsigned int  m_nActivationMsgSize;

	//IFCP RAM image.
	unsigned char *m_pRamImage;
	unsigned int  m_nRamImageSize;
    
} ADIDSMIFCPImage_S;


typedef struct
{
	unsigned char	m_aucHeader[3];
	unsigned char 	m_ucED_Ctrl;
	unsigned char  	*m_pucExtraData;
	unsigned int 	m_nExtraDataSize;
	unsigned char 	*m_pucPayload;
	unsigned int 	m_nPayloadSize;
	unsigned char  	m_aucAppHeader[12];
	unsigned char	*m_pucAppPayload;
	unsigned int 	m_nAppPayloadSize;
	ADIDSMAlgoType_E m_eAlgoType;
} ADIDSMIFCPInput_S;

typedef struct 
{
	unsigned int 	m_nSize;
	unsigned char 	*m_pucBuffer;
	unsigned int 	m_nAppSize;
	unsigned char 	*m_pucAppBuffer;
} ADIDSMIFCPOutput_S;

ADI_Error_Code ADIDSMAllocate(int nDemuxIndex, ADI_HANDLE * phDSM);


ADI_Error_Code ADIDSMFree(ADI_HANDLE hDSM );

ADI_Error_Code ADIDSMSetPID(ADI_HANDLE hDSM,  unsigned int unPID );

ADI_Error_Code ADIDSMClearPID(ADI_HANDLE hDSM, unsigned int unPID );

ADI_Error_Code ADIDSMKeyLadderOpen(ADIDSMKLOpenParams_S *psKLParams);

ADI_Error_Code ADIDSMKeyLadderClose(void);


ADI_Error_Code ADIDSMSetKey(ADI_HANDLE hDSM, ADIDSMKeyInfo_S *psKeyInfo );


ADI_Error_Code ADIDSMSetOddKey(ADI_HANDLE hDSM, const unsigned char * pucOddKey, unsigned int unOddLength);

ADI_Error_Code ADIDSMSetEvenKey(ADI_HANDLE hDSM, const unsigned char * pucEvenKey, unsigned int unEvenLength);

ADI_Error_Code ADIDSMLoadSSUK(unsigned char *pcKey, unsigned char cLength);

ADI_Error_Code ADIDSMSetSecureOddKey(ADI_HANDLE hDSM, const unsigned char * pucOddKey, unsigned int unOddLength);

ADI_Error_Code ADIDSMSetSecureEvenKey(ADI_HANDLE hDSM, const unsigned char * pucEvenKey, unsigned int unEvenLength);
ADI_Error_Code ADIDSMGetDscmbIdByPID(int nPid, int *pnDsmId);

ADI_Error_Code ADIDSMSetSecureOddKeyExt(ADI_HANDLE hDSM, const unsigned char * pucOddKey, unsigned int unOddLength,const unsigned char * pucIV, unsigned int unIVLength, ADIDSMAlgoType_E m_eAlgoType);

ADI_Error_Code ADIDSMSetSecureEvenKeyExt(ADI_HANDLE hDSM, const unsigned char * pucEvenKey, unsigned int unEvenLength, const unsigned char * pucIV, unsigned int unIVLength,ADIDSMAlgoType_E m_eAlgoType);


//Only for Irdeto Cloak4.5

ADI_Error_Code ADIDSMLoadIFCPImage(ADIDSMIFCPImage_S *p_sIFCPImage);

ADI_Error_Code ADIDSMSetIFCPOddKey(ADI_HANDLE hDSM, ADIDSMIFCPInput_S *psIFCPInput,ADIDSMIFCPOutput_S *psIFCPOutput);

ADI_Error_Code ADIDSMSetIFCPEvenKey(ADI_HANDLE hDSM, ADIDSMIFCPInput_S *psIFCPInput,ADIDSMIFCPOutput_S *psIFCPOutput);

ADI_Error_Code ADIDSMSetPVRKey( ADIDSMKeyInfo_S *psKeyInfo);

ADI_Error_Code ADIDSMLoadSSUKExt( ADIDSMKLType_E eKLType, unsigned char *pcKey, unsigned char cLength);

ADI_Error_Code ADIDSMSetIFCPPVRKey(ADI_HANDLE hDSM, ADIDSMIFCPInput_S *psIFCPInput,ADIDSMIFCPOutput_S *psIFCPOutput);

ADI_Error_Code ADIDSMSetCAType(ADIDSMCAType_E eCAType);


// Only for Secure ABV
ADI_Error_Code ADIDSMSetSecureABVKey1(unsigned char ucKey1[16], ADIDSMAlgorithm_E eKey1_type,  ADIDSMAlgorithm_E eCW_type);

ADI_Error_Code ADIDSMSetSecureABVKey2(unsigned char ucKey2[16], ADIDSMAlgorithm_E eKey2_type, unsigned char ucIndex);

// Only for Conax_VSC
ADI_Error_Code ADIDSMConaxVSCInit(int nMode, void *pFnReadFalsh, void *pFnWriteFlash);

ADI_Error_Code ADIDSMConaxVSCSetECW(ADI_HANDLE hDSM, ADIDSMKeyType_E eType, unsigned int unKeyID, const unsigned char * pucCW, unsigned int unCWLength);

ADI_Error_Code ADIDSMConaxVSCDataExchange(unsigned char ucSessionID, unsigned char* pucDataIn, unsigned int unDataInLen, unsigned char* pucDataOut, unsigned int *punDataOutLen, unsigned short* pusStatusWord);

#ifdef  __cplusplus
}
#endif

#endif
