/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vd_stream_crypto.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:17:25
 *  @revision           none
 *
 *  @author              <>
 */


/*
 * This file contains all the definitions for the 'Stream Crypto virtual driver'.
 */



#include <s3_portable_types.h>
#include <s3_vd.h>
#include <s3_vd_stream_crypto.h>
#include <s3_osdrv.h>
#include "ali_vd_drv.h"
#include <aui_dsc.h>
#include <aui_kl.h>
#include <aui_dmx.h>
#include <aui_common.h>

#define KL_V1 1
#define KL_V2 2
#define KL_V3 3
#define KL_V4 4



typedef struct kl_ref{
	vd_rsc_id						rsc_id;
	vd_ref_id						ref_id;
	aui_hdl 						kl_hld;
	aui_hdl 						dsc_hld;
	aui_hdl 						dmx_hld;
	vd_stream_crypto_open_st		kl_st;
	struct aui_attr_kl 				kl_attr;
	struct aui_cfg_kl 				cfg;
	ia_byte 						*abKey;
	//ia_byte 						*abKey;
	struct aui_list_head 			node;
} kl_ref;

static vd_ref_id ref_cnt = 0;
static AUI_LIST_HEAD(kl_ref_head);
ia_result init_s3_vdkl();

static ia_word16 vdkl_get_drv_version();

static ia_result vdkl_get_resources(void **ppvList, ia_word16 *pwCount);

static vd_ref_id vdkl_drv_open(vd_rsc_id wResourceID, void *pvData);

static ia_result vdkl_drv_close(vd_ref_id wRefId);

static ia_result vdkl_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead );
			
static ia_result destroy_vdkl_drv(void *priv_dat);

static ia_result vdkl_io_set_key(kl_ref *pref, ia_word32 wDataWriteSize, void *pin);
static ia_result vdkl_io_set_key_by_type(kl_ref *pref, ia_word32 wDataWriteSize, void *pin);

static ia_result vdkl_io_set_encrypt_key(kl_ref *pref, ia_word32 wDataWriteSize, void *pin);

static ia_result vdkl_io_set_skey(kl_ref *pref, ia_word32 wDataWriteSize, ia_byte *pin);

static struct vd_drv vdkl_drv = {
		.drv_typ 			= VD_DRIVER_STREAM_CRYPTO,
		.priv				= NULL,
		.get_drv_version 	= vdkl_get_drv_version,
		.get_resources		= vdkl_get_resources,
		.drv_open			= vdkl_drv_open,
		.drv_close			= vdkl_drv_close,
		.drv_ioctl			= vdkl_drv_ioctl,
		.destroy			= destroy_vdkl_drv,
};



/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
ia_result init_s3_vdkl()
{
	ia_result ret = IA_SUCCESS;
	
	ret = register_vd_drv(&vdkl_drv);
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_word16 vdkl_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = KL_V4;
	return ver;
}


/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               8/16/2016, Created
 *
 *  @note
 */
static ia_result vdkl_get_resources(void **ppvList, ia_word16 *pwCount)
{
	ia_result ret = IA_INVALID_PARAMETER;

	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static vd_ref_id vdkl_drv_open(vd_rsc_id wResourceID, void *pvData)
{
    AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_hdl kl_hld = NULL;
	struct aui_attr_kl kl_attr;
	struct aui_cfg_kl cfg;
	struct kl_ref *pref = NULL;
	vd_stream_crypto_open_st *o_st = pvData;
	
	if(NULL == pvData)
	{
		return VD_REF_ID_ERROR;
	}
	
	kl_attr.uc_dev_idx = 0;
	kl_attr.en_key_pattern = AUI_KL_OUTPUT_KEY_PATTERN_64_ODD_EVEN;
	kl_attr.en_level = AUI_KL_KEY_TWO_LEVEL;
	kl_attr.en_root_key_idx = 0;
	aui_rtn = aui_kl_open(&kl_attr, &kl_hld);
	if(NULL == pref)
	{
		DEBUG_S3_VD_PRINTF("No mem to alloc\n");
		aui_kl_close(kl_hld);
		return VD_REF_ID_ERROR;
	}
	cfg.run_level_mode = AUI_KL_RUN_LEVEL_MODE_LEVEL_ALL;
	switch(o_st->eAlgorithm)
	{
		case VD_CRYPTO_ALGORITHM_AES:
			cfg.en_kl_algo = AUI_KL_ALGO_AES;
			break;
		case VD_CRYPTO_ALGORITHM_3DES:
			cfg.en_kl_algo = AUI_KL_ALGO_TDES;
			break;

		default:
			cfg.en_kl_algo = AUI_KL_ALGO_NB;
			break;
	}
	
	switch(o_st->eOperation)
	{
		case VD_CRYPTO_OPERATION_ENCRYPT:
			cfg.en_crypt_mode = AUI_KL_ENCRYPT;
			break;
		case VD_CRYPTO_OPERATION_DECRYPT:
			cfg.en_crypt_mode = AUI_KL_DECRYPT;
			break;

		default:
			cfg.en_crypt_mode = AUI_KL_NB;
			break;
	}
	cfg.en_cw_key_attr = AUI_KL_CW_KEY_SINGLE;
	
	pref = OS_DRV_AllocateMemory(sizeof(struct kl_ref));
	pref->rsc_id = wResourceID;
	pref->kl_hld = kl_hld;
	pref->abKey = NULL;
	ansi_memcpy(&pref->kl_attr, &kl_attr, sizeof(aui_attr_dsc));
	ansi_memcpy(&pref->cfg, &cfg, sizeof(aui_cfg_kl));
	pref->ref_id = ref_cnt++;
	aui_list_add_tail(&pref->node, &kl_ref_head);
	return pref->ref_id;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vdkl_drv_close(vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;
	struct kl_ref *pref = NULL;
	int find_flag = 0;
		
	aui_list_for_each_entry(pref, &kl_ref_head, node)
	{
		if(wRefId == pref->ref_id)
		{
			
			aui_list_del(&pref->node);
			find_flag = 1;
			break;
		}
	}
	if(0 == find_flag)
	{
		return IA_INVALID_PARAMETER;

	}
	aui_kl_close(pref->kl_hld);
	OS_DRV_FreeMemory(pref);
	pref = NULL;
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vdkl_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead)
{
	ia_result ret = IA_SUCCESS;
	struct kl_ref *pref = NULL;
	int find_flag = 0;

	aui_list_for_each_entry(pref, &kl_ref_head, node)
	{
		if(wRefId == pref->ref_id)
		{
			find_flag = 1;
			break;
		}

	}
	if(0 == find_flag)
	{
		return IA_INVALID_PARAMETER;

	}
	switch(wOpCode)
	{
		case VD_STREAM_CRYPTO_SET_KEY:
			ret = vdkl_io_set_key(pref, wDataWriteSize, pvDataWrite);
			break;
		case VD_STREAM_CRYPTO_SET_KEY_BY_TYPE:
			ret = vdkl_io_set_key_by_type(pref, wDataWriteSize, pvDataWrite);
			break;
		
		case VD_STREAM_CRYPTO_SET_SKEY:
			ret = vdkl_io_set_skey(pref, wDataWriteSize, pvDataWrite);
			break;
		
		case VD_STREAM_CRYPTO_SET_ENCRYPTED_KEY:
			ret = vdkl_io_set_encrypt_key(pref, wDataWriteSize, pvDataWrite);
			break;
		case VD_STREAM_CRYPTO_KEY_COMMAND:
			ret = IA_INVALID_PARAMETER;
			break;	
		default:
			ret = IA_INVALID_PARAMETER;
			break;
	}
	
	return ret;

}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               8/14/2016, Created
 *
 *  @note
 */
static ia_result destroy_vdkl_drv(void *priv_dat)
{
	ia_result ret = IA_SUCCESS;

	if(NULL != priv_dat)
	{
		OS_DRV_FreeMemory(priv_dat);
	}

	return ret;

}



//#define AUI_DSC_KL_API
#ifdef AUI_DSC_KL_API

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_key(kl_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_stream_crypto_key_st key_st;
	void *dat_pos = NULL;
	struct aui_attr_kl kl_attr;
	struct aui_cfg_kl cfg;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		ret = IA_FAIL;
		return ret;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_stream_crypto_key_st));
    dat_pos = pin + sizeof(vd_stream_crypto_key_st);
    if(NULL == pref->abKey)
    {
    	pref->abKey = OS_DRV_AllocateMemory(key_st.wKeyLength * sizeof(ia_byte));
    	if(NULL == pref->abKey)
		{
			DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        	ret = IA_FAIL;	
			return ret;
		}
    	ansi_memset(pref->abKey, 0x00, key_st.wKeyLength * sizeof(ia_byte));
    }
	ansi_memcpy(pref->abKey, dat_pos, key_st.wKeyLength * sizeof(ia_byte));
	ret = IA_SUCCESS;
	return ret;
	

}
/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_key_by_type(kl_ref *pref, ia_word32 wDataWriteSize, void *pin)
{

	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_stream_crypto_key_by_type_st key_st;
	void *dat_pos = NULL;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		ret = IA_FAIL;
		return ret;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_stream_crypto_key_by_type_st));
    dat_pos = pin + sizeof(vd_stream_crypto_key_by_type_st);
    if(NULL == pref->abKey)
    {
    	pref->abKey = OS_DRV_AllocateMemory(key_st.wKeyLength * sizeof(ia_byte));
    	if(NULL == pref->abKey)
		{
			DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        	ret = IA_FAIL;	
			return ret;
		}
    	ansi_memset(pref->abKey, 0x00, key_st.wKeyLength * sizeof(ia_byte));
    }
	ansi_memcpy(pref->abKey, dat_pos, key_st.wKeyLength * sizeof(ia_byte));
	switch(key_st.eKeyType)
	{
		case VD_DD_KEY_ODD:
			pref->dsc_attr.ul_key_pattern = AUI_DSC_KEY_PATTERN_ODD;
			break;
		case VD_DD_KEY_EVEN:
			pref->dsc_attr.ul_key_pattern = AUI_DSC_KEY_PATTERN_EVEN;
			break;
		default:
			pref->dsc_attr.ul_key_pattern = AUI_DSC_KEY_PATTERN_SINGLE;
			break;
	}
    switch(key_st.eAlgorithm)
	{
		case VD_DD_FAST_I:
			pref->dsc_attr.uc_algo = AUI_DSC_ALGO_NB;
			break;
		case VD_DD_DVB:
			pref->dsc_attr.uc_algo = AUI_DSC_ALGO_CSA;
			break;
		case VD_DD_AES64:
			pref->dsc_attr.uc_algo = AUI_DSC_ALGO_NB;
			break;
		case VD_DD_AES128_RCBC_CTS:
			pref->dsc_attr.uc_algo = AUI_DSC_ALGO_NB;
			break;
		case VD_DD_AES128_CBC_IA:
			pref->dsc_attr.uc_algo = AUI_DSC_ALGO_AES;
			break;
		default:
			pref->dsc_attr.uc_algo = AUI_DSC_ALGO_NB;
			break;
	}
	return ret;

}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_encrypt_key(kl_ref *pref, ia_word32 wDataWriteSize, void *pin)
{

}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_skey(kl_ref *pref, ia_word32 wDataWriteSize, ia_byte *pin)
{

}

#else
#include "encrypt_pvr.h"

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_key(kl_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_stream_crypto_key_st key_st;
	void *dat_pos = NULL;
	struct pvr_crypto_key pvr_key;
	struct pvr_set_crypto_key_hd pvr_key_hd;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		return IA_FAIL;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_stream_crypto_key_st));
    dat_pos = pin + sizeof(vd_stream_crypto_key_st);

	memset(&pvr_key_hd, 0, sizeof(pvr_key_hd));
	pvr_key_hd.h_dsc = pref->dsc_hld;
	pvr_key_hd.h_kl = pref->kl_hld;
	pvr_key_hd.h_dmx = pref->dmx_hld;

	memset(&pvr_key, 0, sizeof(pvr_key)); 
	if (NULL != pvr_key_hd.h_kl)
	{
		pvr_key.kl_level = 5;
	}
	else
	{
		pvr_key.kl_level = 0;
	}
	pvr_key.e_parity = PVR_KEY_PARITY_EVEN;
	pvr_key.e_algo = PVR_KEY_ALGO_AES;
	pvr_key.e_mode = PVR_KEY_MODE_ECB;
	pvr_key.key_length = key_st.wKeyLength;
	pvr_key.p_key = dat_pos;

	aui_rtn = set_pvr_crypto_key(&pvr_key, &pvr_key_hd, NULL);
	if (AUI_RTN_SUCCESS != aui_rtn)
	{
		DEBUG_S3_VD_PRINTF("set_pvr_crypto_key %d error.\n", aui_rtn);
		return IA_FAIL;
	}

	if (NULL == pref->dsc_hld)
	{
		pref->dsc_hld = pvr_key_hd.h_dsc;
	}
	if (NULL == pref->kl_hld)
	{
		pref->kl_hld = pvr_key_hd.h_kl;
	}

	return IA_SUCCESS;
	

}
/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_key_by_type(kl_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_stream_crypto_key_by_type_st key_st;
	void *dat_pos = NULL;
	struct pvr_crypto_key pvr_key;
	struct pvr_set_crypto_key_hd pvr_key_hd;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		return IA_FAIL;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_stream_crypto_key_by_type_st));
    dat_pos = pin + sizeof(vd_stream_crypto_key_by_type_st);


	memset(&pvr_key_hd, 0, sizeof(pvr_key_hd));
	pvr_key_hd.h_dsc = pref->dsc_hld;
	pvr_key_hd.h_kl = pref->kl_hld;
	pvr_key_hd.h_dmx = pref->dmx_hld;

	memset(&pvr_key, 0, sizeof(pvr_key)); 
	if (NULL != pvr_key_hd.h_kl)
	{
		pvr_key.kl_level = 5;
	}
	else
	{
		pvr_key.kl_level = 0;
	}
	pvr_key.e_parity = PVR_KEY_PARITY_EVEN;
	pvr_key.e_algo = PVR_KEY_ALGO_AES;
	pvr_key.e_mode = PVR_KEY_MODE_ECB;
	pvr_key.key_length = key_st.wKeyLength;
	pvr_key.p_key = dat_pos;

	if(VD_CRYPTO_ALGORITHM_AES == key_st.eAlgorithm)
    {
		pvr_key.e_algo = PVR_KEY_ALGO_AES;
    }
	else if(VD_CRYPTO_ALGORITHM_3DES == key_st.eAlgorithm)
	{
		pvr_key.e_algo = PVR_KEY_ALGO_TDES;
	}
	else
	{
        DEBUG_S3_VD_PRINTF("key_st.eAlgorithm %d error.\n", key_st.eAlgorithm);
		return IA_FAIL;
	}

	if(VD_STREAM_CRYPTO_KEY_ODD == key_st.eKeyType)
    {
		pvr_key.e_algo = PVR_KEY_PARITY_ODD;
    }
	else if(VD_STREAM_CRYPTO_KEY_EVEN == key_st.eKeyType)
	{
		pvr_key.e_algo = PVR_KEY_PARITY_EVEN;
	}
	else
	{
        DEBUG_S3_VD_PRINTF("key_st.eKeyType %d error.\n", key_st.eKeyType);
		return IA_FAIL;
	}


	aui_rtn = set_pvr_crypto_key(&pvr_key, &pvr_key_hd, NULL);
	if (AUI_RTN_SUCCESS != aui_rtn)
	{
		DEBUG_S3_VD_PRINTF("set_pvr_crypto_key %d error.\n", aui_rtn);
		return IA_FAIL;
	}

	if (NULL == pref->dsc_hld)
	{
		pref->dsc_hld = pvr_key_hd.h_dsc;
	}
	if (NULL == pref->kl_hld)
	{
		pref->kl_hld = pvr_key_hd.h_kl;
	}

	return IA_SUCCESS;


}



struct pvr_kl_key
{
	vd_stream_crypto_key_by_type_st encrypted_key;
	ia_byte* p_encrypted_key_data;

	ia_word32 s_key_length;
	ia_byte* p_s_key_data;
};
static struct pvr_kl_key g_pvr_kl_key =
{
	{VD_STREAM_CRYPTO_KEY_ODD, VD_CRYPTO_ALGORITHM_AES, 0},
	NULL,
	NULL
};

void clr_pvr_kl_key()
{
	if (NULL != g_pvr_kl_key.p_s_key_data)
	{
		free(g_pvr_kl_key.p_s_key_data);
		g_pvr_kl_key.p_s_key_data = NULL;
	}

	if (NULL != g_pvr_kl_key.p_encrypted_key_data)
	{
		free(g_pvr_kl_key.p_encrypted_key_data);
		g_pvr_kl_key.p_encrypted_key_data = NULL;
	}

	memset(&g_pvr_kl_key, 0, sizeof(g_pvr_kl_key));
}


static ia_result touch_pvr_kl_encrypt(kl_ref *pref)
{
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct pvr_crypto_key pvr_key;
	struct pvr_set_crypto_key_hd pvr_key_hd;	
	
	if (NULL == g_pvr_kl_key.p_encrypted_key_data
		|| NULL == g_pvr_kl_key.p_s_key_data)
	{
		return IA_SUCCESS;
	}

	if (g_pvr_kl_key.s_key_length != g_pvr_kl_key.encrypted_key.wKeyLength)
	{
		DEBUG_S3_VD_PRINTF("wKeyLength %d != %d error.\n", g_pvr_kl_key.s_key_length, g_pvr_kl_key.encrypted_key.wKeyLength);

		goto touch_pvr_kl_encrypt_fail;
	}

	memset(&pvr_key_hd, 0, sizeof(pvr_key_hd));
	pvr_key_hd.h_dsc = pref->dsc_hld;
	pvr_key_hd.h_kl = pref->kl_hld;
	pvr_key_hd.h_dmx = pref->dmx_hld;

	memset(&pvr_key, 0, sizeof(pvr_key)); 
	pvr_key.kl_level = 5;	//force kl mode
	pvr_key.e_parity = PVR_KEY_PARITY_EVEN;
	pvr_key.e_algo = PVR_KEY_ALGO_AES;
	pvr_key.e_mode = PVR_KEY_MODE_ECB;
	pvr_key.key_length = g_pvr_kl_key.encrypted_key.wKeyLength;
	pvr_key.p_key = g_pvr_kl_key.p_encrypted_key_data;

	if(VD_CRYPTO_ALGORITHM_AES == g_pvr_kl_key.encrypted_key.eAlgorithm)
    {
		pvr_key.e_algo = PVR_KEY_ALGO_AES;
    }
	else if(VD_CRYPTO_ALGORITHM_3DES == g_pvr_kl_key.encrypted_key.eAlgorithm)
	{
		pvr_key.e_algo = PVR_KEY_ALGO_TDES;
	}
	else
	{
        DEBUG_S3_VD_PRINTF("key_st.eAlgorithm %d error.\n", g_pvr_kl_key.encrypted_key.eAlgorithm);
		goto touch_pvr_kl_encrypt_fail;
	}

	if(VD_STREAM_CRYPTO_KEY_ODD == g_pvr_kl_key.encrypted_key.eKeyType)
    {
		pvr_key.e_algo = PVR_KEY_PARITY_ODD;
    }
	else if(VD_STREAM_CRYPTO_KEY_EVEN == g_pvr_kl_key.encrypted_key.eKeyType
		|| VD_STREAM_CRYPTO_KEY_SINGLE == g_pvr_kl_key.encrypted_key.eKeyType)
	{
		pvr_key.e_algo = PVR_KEY_PARITY_EVEN;
	}
	else
	{
        DEBUG_S3_VD_PRINTF("key_st.eKeyType %d error.\n", g_pvr_kl_key.encrypted_key.eKeyType);
		goto touch_pvr_kl_encrypt_fail;
	}

	if (NULL == pref->kl_hld)
	{
		DEBUG_S3_VD_PRINTF("pref->kl_hld NULL error.\n");
		goto touch_pvr_kl_encrypt_fail;
	}
	
	aui_rtn = set_pvr_crypto_key(&pvr_key, &pvr_key_hd, NULL);
	if (AUI_RTN_SUCCESS != aui_rtn)
	{
		DEBUG_S3_VD_PRINTF("set_pvr_crypto_key %d error.\n", aui_rtn);
		goto touch_pvr_kl_encrypt_fail;
	}

	if (NULL == pref->dsc_hld)
	{
		pref->dsc_hld = pvr_key_hd.h_dsc;
	}
	if (NULL == pref->kl_hld)
	{
		pref->kl_hld = pvr_key_hd.h_kl;
	}

	return IA_SUCCESS;

touch_pvr_kl_encrypt_fail:
	clr_pvr_kl_key();

	return IA_FAIL;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_encrypt_key(kl_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_stream_crypto_key_by_type_st key_st;
	void *dat_pos = NULL;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		return IA_FAIL;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_stream_crypto_key_by_type_st));
    dat_pos = pin + sizeof(vd_stream_crypto_key_by_type_st);

	if (key_st.wKeyLength <= 0)
	{
		DEBUG_S3_VD_PRINTF("key_st.wKeyLength %d.\n", key_st.wKeyLength);
		return IA_FAIL;
	}

	if (NULL != g_pvr_kl_key.p_encrypted_key_data)
	{
		free(g_pvr_kl_key.p_encrypted_key_data);
		g_pvr_kl_key.p_encrypted_key_data = NULL;
	}

	g_pvr_kl_key.p_encrypted_key_data = malloc(key_st.wKeyLength);
	if (NULL == g_pvr_kl_key.p_encrypted_key_data)
	{
		DEBUG_S3_VD_PRINTF("g_pvr_kl_key.p_encrypted_key_data NULL.\n");
		return IA_FAIL;
	}
	memcpy(g_pvr_kl_key.p_encrypted_key_data, dat_pos, key_st.wKeyLength);
	
	g_pvr_kl_key.encrypted_key = key_st;
	
	return touch_pvr_kl_encrypt(pref);

}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/2/2016, Created
 *
 *  @note
 */
static ia_result vdkl_io_set_skey(kl_ref *pref, ia_word32 wDataWriteSize, ia_byte *pin)
{
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		return IA_FAIL;
    }

	if (wDataWriteSize <= 0)
	{
		DEBUG_S3_VD_PRINTF("wDataWriteSize %d.\n", wDataWriteSize);
		return IA_FAIL;
	}

	if (NULL != g_pvr_kl_key.p_s_key_data)
	{
		free(g_pvr_kl_key.p_s_key_data);
		g_pvr_kl_key.p_s_key_data = NULL;
	}

	g_pvr_kl_key.p_s_key_data = malloc(wDataWriteSize);
	if (NULL == g_pvr_kl_key.p_s_key_data)
	{
		DEBUG_S3_VD_PRINTF("g_pvr_kl_key.p_s_key_data NULL.\n");
		return IA_FAIL;
	}
	memcpy(g_pvr_kl_key.p_s_key_data, pin, wDataWriteSize);
	
	g_pvr_kl_key.s_key_length = wDataWriteSize;
	
	return touch_pvr_kl_encrypt(pref);
}

#endif
