#ifndef _ADI_SECURE_H_
#define _ADI_SECURE_H_

#include "adi_typedef.h"
#include "adi_error.h"
#ifdef  __cplusplus
extern "C" {
#endif


ADI_Error_Code ADISecureSetJtagEnable(void);

ADI_Error_Code ADISecureReadJtagMode(ADI_BOOL *pbReal);

ADI_Error_Code ADISecureBootEnable(void);

ADI_Error_Code ADISecureBootReadMode(ADI_BOOL *pbReal);

ADI_Error_Code ADISecureCWEnable(void);

ADI_Error_Code ADISecureCWReadMode(ADI_BOOL *pbReal);

ADI_Error_Code ADISecureSetMarketId(unsigned long u32MarketId);

ADI_Error_Code ADISecureGetMarketId(unsigned long *pu32MarketId);

ADI_Error_Code ADISecureReadOtp(unsigned long u32Addr,unsigned long * pu32Value);

ADI_Error_Code ADISecureWriteOtp(unsigned long u32Addr,unsigned long u32Value);

ADI_Error_Code ADIEncryptAES_CBC_Mac(unsigned char *pu8BufIn, unsigned char *pu8BufOut,unsigned long u32BufSize);

ADI_Error_Code ADISecureVMXCheckFusesStatus(void);

ADI_Error_Code ADISecureVMXEnableFuses(void);



/**
@brief          Function used to generate a number of random keys.

@param[in]      u32KeyLen      = The length of a key in byte
@param[in]      u32KeyNum      = The total amount of the random keys to be  generated
@param[out]     pu8Key         = Pointer to the keys buffer, where the keys
                                 generated have been saved

@return         @b ADI_SUCCESS  = The keys have been generated successfully
@return         @b ADI_FAILURE     = Generating of the keys failed for some
                                      reasons
*/
ADI_Error_Code ADISecureGenerateKeys(unsigned int u32KeyLen,unsigned int u32KeyNum,unsigned char *pu8Key);

typedef struct
{	
    unsigned char *pu8BufOut;   //Pointer to the post processed data
    unsigned char *pu8BufIn;    //Pointer to the data to be processed
    unsigned int u32BufLen;     //Length  of pu8BufOut and pu8BufIn
    unsigned char *pu8Key;      //Pointer to the key for encryption/decryption 
    unsigned int u32KeyLen;     //Length of the key in byte unit
    unsigned char *pu8IV;       //Pointer to Initial Vector (IV) for some specific algorithms
	unsigned int u32IVLen;      //Length of pu8IV ,Caution: Generally, The length of the pu8IV is fixed in 16 bytes
    unsigned char u8CryptoMode; //Reserved for feature used, user can ignore currently
    unsigned char u8Encrypt;    //Flag to indicate encryption/decryption,in particular: 1 = Encryption ,0 = Decryption
}ADISecureCrypto_S;

ADI_Error_Code ADISecureCrypto(ADISecureCrypto_S *psSecureCrypto);

typedef struct
{
	unsigned char *pu8Input;      //Pointer to the meta data memory address
	unsigned long u32InputLen;    //The length of the meta data memory address
	unsigned char *pu8Output;     //The HMAC result of the input buffer,Caution: Generally, The length of the output is fixed in 32 bytes
	unsigned long *pu32OutputLen; //In:the length of the onput buffer, Out:The HMAC result length
	unsigned char *pu8Key;        //Pointer to the HMAC Key,Caution: Generally, The length of the output is fixed in 16 bytes
	unsigned long u32KeyLen;      //The length of the HMAC key in byte
}ADISecureCalHmac_S;

ADI_Error_Code ADISecureCalculateHmac(ADISecureCalHmac_S *psSecureCalHmac);
ADI_Error_Code ADISecureGetMACData(unsigned char *  pucData, unsigned int * pDataLen);
ADI_Error_Code ADISecureGetCCCKDataAndMACData(unsigned char *  pucCCCKData, unsigned int * pCCCKDataLen, unsigned char *  pucMACData, unsigned int * pMACDataLen);



#ifdef  __cplusplus
}
#endif

#endif


