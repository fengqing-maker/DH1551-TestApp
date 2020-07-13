/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : Pkcs.c                                                     *
*                                                                            *
*   Description : This module supplies the PKCS1 implementation required by  *
*                 Loader Core.                                               *
*                                                                            *
*****************************************************************************/

#include "LoaderCorePrivate.h"
#include "RsaPss.h"

#define countof(x) (sizeof(x)/sizeof(x[0]))
/* T length definition */
/*Hash T 
MD5 30 20 30 0c 06 08 2a 86 48 86 f7 0d 02 05 05 00 04 10 || H 
SHA-1 30 21 30 09 06 05 2b 0e 03 02 1a 05 00 04 14 || H 
SHA-256 30 31 30 0d 06 09 60 86 48 01 65 03 04 02 01 05 00 04 20 || H 
SHA-384 30 41 30 0d 06 09 60 86 48 01 65 03 04 02 02 05 00 04 30 || H 
SHA-512 30 51 30 0d 06 09 60 86 48 01 65 03 04 02 03 05 00 04 40 || H 
*/
#define T_SHA1_LENGTH   15
#define T_SHA256_LENGTH 19

#define SHA1_HASH_SIZE 20
#define SHA256_HASH_SIZE 32

/**
* Basic Rsa_GetRsaPssKey function
*/
static pkcs_result Rsa_GetRsaPssKey(const lc_uchar *pRsaKey, LC_RSA_key *pRsaPssKey)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	if(LC_NULL == pRsaKey || LC_NULL == pRsaPssKey)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}

	if(PKCS_ERROR_SUCCESS == result)
	{
		result = Rsa_OS2IP(pRsaKey, 256, &pRsaPssKey->n);

		pRsaPssKey->d_or_e.num[128] = 0x00010001;
	}

	return result;
}

/* =================================================== */

pkcs_result Rsa_CheckHashMode( pkcs_hash_mode *pPkcsHashMode)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;

	pkcs_hash_mode hashMode = PKCS_SHA256_MODE;

	*pPkcsHashMode = hashMode;

	return result;
}

pkcs_result Rsa_SignatureDataCheck(const lc_uchar *rsa_data)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	lc_uchar invalid_signature_data[SIGNATURE_LENGTH]= {0};
	LC_memset(invalid_signature_data, 0, SIGNATURE_LENGTH);

	if(LC_NULL == rsa_data)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}

	if(PKCS_ERROR_SUCCESS == result &&
		(LC_memcmp(rsa_data, invalid_signature_data, SIGNATURE_LENGTH) == 0))
	{
		result = PKCS_ERROR_SIGNATURE_VERIFICATION;
	}
	

	return result; 
}

pkcs_result Rsa_VerifyPkcs( 
	lc_uchar* pRsaKey,
	const lc_uchar signature[SIGNATURE_LENGTH],
	pkcs_buffer_st *pHash)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	LC_RSA_key RsaPssKey;

	if(LC_NULL == pHash)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}
	else if((LC_NULL == pHash->bytes) || (LC_NULL == signature) || (LC_NULL == pRsaKey))
	{
		result = PKCS_ERROR_NULL_PARAM;
	}

	if(PKCS_ERROR_SUCCESS == result)
	{
		result = Rsa_SignatureDataCheck(signature);
	}

	if(PKCS_ERROR_SUCCESS == result)
	{

		LC_memset(&RsaPssKey.n, 0x0, sizeof(pkcs_long_num));
		LC_memset(&RsaPssKey.mp, 0x0, sizeof(pkcs_long_num));
		LC_memset(&RsaPssKey.d_or_e, 0x0, sizeof(pkcs_long_num));
		result = Rsa_GetRsaPssKey(pRsaKey, &RsaPssKey);

		if(PKCS_ERROR_SUCCESS == result)
		{
			Rsa_CalcMPrime(&RsaPssKey.n,&RsaPssKey.mp);

			result = Rsa_VerifyPssSha256(pHash, signature, &RsaPssKey);
		}
	}

	return result;
}


