/*****************************************************************************
*    Copyright (c) 2017 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: Encrypt_pvr.h
*
*    Description: 

*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#ifndef __ENCRYPT_PVR_H__
#define __ENCRYPT_PVR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "aui_common.h"
#include "aui_pvr.h"


enum pvr_key_parity {PVR_KEY_PARITY_UNDEF, PVR_KEY_PARITY_EVEN, PVR_KEY_PARITY_ODD, PVR_KEY_PARITY_AUTO};
enum pvr_key_algo {PVR_KEY_ALGO_UNDEF, PVR_KEY_ALGO_AES, PVR_KEY_ALGO_DES, PVR_KEY_ALGO_TDES};
enum pvr_key_mode {PVR_KEY_MODE_UNDEF, PVR_KEY_MODE_ECB, PVR_KEY_MODE_CBC, PVR_KEY_MODE_OFB, PVR_KEY_MODE_CFB, PVR_KEY_MODE_CTR};


struct pvr_crypto_key
{
	int kl_level;
	
	enum pvr_key_parity e_parity;

	enum pvr_key_algo e_algo;
	enum pvr_key_mode e_mode;
	
	int key_length;
	unsigned char* p_key;
	unsigned char* p_iv;
};

struct pvr_set_crypto_key_hd
{
	aui_hdl h_dsc;
	
	aui_hdl h_kl;

	aui_hdl h_dmx;
};

struct pvr_crypto_pids
{
	int count;
	unsigned short int* p_pids;
};

/**
@brief		set or modify pvr crypto key for encrypt or decrypt

@param[in] 	p_key
			p_key->kl_level > 0, use kl mode, otherwise use clear key mode
			p_key->p_iv, if NULL, use default iv(all zero)
			p_key->p_key, if e_parity is PVR_KEY_PARITY_AUTO, p_key->p_key point memory size is (p_key->key_length*2), and odd first, followed with even.
			
@param[in/out]	p_key_hd
			p_key_hd->h_dmx must not NULL;
			p_key_hd->h_kl, if NULL, dsc use clear key mode, otherwise use kl mode;
			p_key_hd->h_dsc, if NULL, will invoke aui_dsc_open(), and return the dsc_hd by this para.

@param[in] 	p_pids, if not NULL, will record pids from this para.

@return         @b AUI_RTN_SUCCESS  = Getting of the desired set of URI information
*/
AUI_RTN_CODE set_pvr_crypto_key(const struct pvr_crypto_key* p_key, struct pvr_set_crypto_key_hd* p_key_hd, struct pvr_crypto_pids* p_pids);

/**
@brief		when error is found, recommend for clear pvr encrpty/edcrypt status and resource.  
*/
void free_pvr_crypto_key();


AUI_RTN_CODE start_pvr_encrypt(aui_pvr_crypto_general_param *p_param);
AUI_RTN_CODE stop_pvr_encrypt(aui_pvr_crypto_general_param *p_param);
AUI_RTN_CODE start_pvr_decrypt(aui_pvr_crypto_general_param *p_param);
AUI_RTN_CODE stop_pvr_decrypt(aui_pvr_crypto_general_param *p_param);

AUI_RTN_CODE pvr_crypto_set_pids(aui_pvr_crypto_pids_param *p_pids_param);



#ifdef __cplusplus
}
#endif

#endif /* __C200A_PVR_H__ */

