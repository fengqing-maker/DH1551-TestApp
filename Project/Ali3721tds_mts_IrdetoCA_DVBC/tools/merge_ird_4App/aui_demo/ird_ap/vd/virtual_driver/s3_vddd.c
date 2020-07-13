/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vddd.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 14:56:48
 *  @revision           none
 *
 *  @author              <>
 */

#include <s3_vd.h>
#include <s3_vddd.h>
#include <s3_osdrv.h>
#include "ali_vd_drv.h"
#include <aui_dsc.h>
#include <aui_kl.h>
#include <aui_dmx.h>
#include <aui_common.h>

#define DSC_V1 1
#define DSC_V2 2
#define DSC_V3 3
#define DSC_V4 4
#define DSC_V5 5


typedef struct dsc_ref{
	vd_rsc_id						rsc_id;
	vd_ref_id						ref_id;
	aui_hdl 						dsc_hdl;
	aui_attr_dsc 					dsc_attr;
	ia_byte							*encrypt_cssk;
	ia_word32						cssk_size;
	struct aui_cfg_kl 				cfg;
	aui_hdl 						kl_hdl;
	struct aui_attr_kl 				kl_attr;
	struct aui_list_head 			node;
} dsc_ref;

static vd_ref_id ref_cnt = 0;
static AUI_LIST_HEAD(dsc_ref_head);
ia_result init_s3_vddd();

static ia_word16 vddd_get_drv_version();

static ia_result vddd_get_resources(void **ppvList, ia_word16 *pwCount);

static vd_ref_id vddd_drv_open(vd_rsc_id wResourceID, void *pvData);

static ia_result vddd_drv_close(vd_ref_id wRefId);

static ia_result vddd_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead );
			
static ia_result destroy_vddd_drv(void *priv_dat);

static ia_result vddd_io_set_pid(dsc_ref *pref, vd_dd_pid_st *pin);

static ia_result vddd_io_set_key(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin);

static ia_result vddd_io_set_arib_data(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin);

static ia_result vddd_io_set_skey(dsc_ref *pref, ia_word32 wDataWriteSize, ia_byte *pin);

static ia_result vddd_io_add_pid(dsc_ref *pref, vd_dd_pid_st *pin);

static ia_result vddd_io_rm_pid(dsc_ref *pref, vd_dd_pid_st *pin);

static ia_result vddd_io_set_encrypt_key(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin);

static ia_result vddd_io_set_session_key(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin);

static struct vd_drv vddd_drv = {
		.drv_typ 			= VD_DRIVER_DVB_DESCRAMBLER,
		.priv				= NULL,
		.get_drv_version 	= vddd_get_drv_version,
		.get_resources		= vddd_get_resources,
		.drv_open			= vddd_drv_open,
		.drv_close			= vddd_drv_close,
		.drv_ioctl			= vddd_drv_ioctl,
		.destroy			= destroy_vddd_drv,
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
ia_result init_s3_vddd()
{
	ia_result ret = IA_SUCCESS;
	
	ret = register_vd_drv(&vddd_drv);
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
static ia_word16 vddd_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = DSC_V5;
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
static ia_result vddd_get_resources(void **ppvList, ia_word16 *pwCount)
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
static vd_ref_id vddd_drv_open(vd_rsc_id wResourceID, void *pvData)
{
    AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct dsc_ref *pref = NULL;
	

	pref = OS_DRV_AllocateMemory(sizeof(struct dsc_ref));
	if(NULL == pref)
	{
		DEBUG_S3_VD_PRINTF("No mem to alloc\n");;
		return VD_REF_ID_ERROR;
	}
	pref->rsc_id = wResourceID;
	pref->dsc_hdl = NULL;
	pref->kl_hdl = NULL;
	ansi_memset(&pref->kl_attr, 0x00, sizeof(struct aui_attr_kl));
	ansi_memset(&pref->dsc_attr, 0x00, sizeof(aui_attr_dsc));
	ansi_memset(&pref->cfg, 0x00, sizeof(struct aui_cfg_kl));
	pref->cssk_size = 0;
	pref->encrypt_cssk = NULL;
	pref->ref_id = ref_cnt++;
	aui_list_add_tail(&pref->node, &dsc_ref_head);
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
static ia_result vddd_drv_close(vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;
	struct dsc_ref *pref = NULL;
	int find_flag = 0;
		
	aui_list_for_each_entry(pref, &dsc_ref_head, node)
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
	if(NULL != pref->dsc_hdl)
	{
		aui_dsc_close(pref->dsc_hdl);
		pref->dsc_hdl = NULL;
	}
	if(NULL != pref->kl_hdl)
	{
		aui_kl_close(pref->dsc_hdl);
		pref->kl_hdl = NULL;
	}
	if(NULL != pref->encrypt_cssk)
	{
		OS_DRV_FreeMemory(pref->encrypt_cssk);
		pref->encrypt_cssk = NULL;
	}
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
static ia_result vddd_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead)
{
	ia_result ret = IA_SUCCESS;
	struct dsc_ref *pref = NULL;
	int find_flag = 0;
	int local_refid = 0;

	if(VD_REF_ID_GLOBAL == wRefId)
	{
		local_refid = 0;
	}
	else
	{
		local_refid = wRefId;
	}

	
	aui_list_for_each_entry(pref, &dsc_ref_head, node)
	{
		if(local_refid == pref->ref_id)
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
		case VD_DD_SET_PID:
			ret = vddd_io_set_pid(pref, pvDataWrite);
			break;
		case VD_DD_SET_KEY:
			ret = vddd_io_set_key(pref, wDataWriteSize, pvDataWrite);
			break;
		
		case VD_DD_SET_ARIB_DATA:
			ret = vddd_io_set_arib_data(pref, wDataWriteSize, pvDataWrite);
			break;
		
		case VD_DD_SET_SKEY:
			ret = vddd_io_set_skey(pref, wDataWriteSize, pvDataWrite);
			break;
		case VD_DD_ADD_PID:
			ret = vddd_io_add_pid(pref, pvDataWrite);
			break;
			
		case VD_DD_REMOVE_PID:
			ret = vddd_io_rm_pid(pref, pvDataWrite);
			break;
		case VD_DD_SET_SESSION_KEY:
			ret = vddd_io_set_encrypt_key(pref, wDataWriteSize, pvDataWrite);
			break;
		case VD_DD_SET_ENCRYPTED_KEY:
			ret = vddd_io_set_session_key(pref, wDataWriteSize, pvDataWrite);
			break;
		case VD_DD_KEY_COMMAND:
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
static ia_result destroy_vddd_drv(void *priv_dat)
{
	ia_result ret = IA_SUCCESS;

	if(NULL != priv_dat)
	{
		OS_DRV_FreeMemory(priv_dat);
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_set_pid(dsc_ref *pref, vd_dd_pid_st *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_hdl dsc_hdl = NULL;

	if((NULL == pref) || (NULL == pin) || (NULL == pref->dsc_hdl))
	{
		ret = IA_FAIL;
		return ret;
	}
	if(0 == pref->dsc_attr.ul_pid_cnt)
	{
		pref->dsc_attr.pus_pids[0] = pin->wPid;
		pref->dsc_attr.ul_pid_cnt++;
		ret = IA_SUCCESS;
	}
	else if(1 == pref->dsc_attr.ul_pid_cnt)
	{
		pref->dsc_attr.pus_pids[0] = pin->wPid;
		ret = IA_SUCCESS;
	}
	else
	{
		DEBUG_S3_VD_PRINTF("pid set fail\n");
        ret = IA_FAIL;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_set_key(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_dd_key_st key_st;
	void *dat_pos = NULL;
	ia_byte *abKey = NULL;
	unsigned char iv[16 * 2];
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		ret = IA_FAIL;
		return ret;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_dd_key_st));
    dat_pos = pin + sizeof(vd_dd_key_st);

    abKey = OS_DRV_AllocateMemory(key_st.wKeyLength * sizeof(ia_byte));
    if(NULL == abKey)
	{
		DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        ret = IA_FAIL;	
		return ret;
	}
    ansi_memset(abKey, 0x00, key_st.wKeyLength * sizeof(ia_byte));
	ansi_memcpy(abKey, dat_pos, key_st.wKeyLength * sizeof(ia_byte));
	if(NULL == pref->dsc_hdl)
	{	
		pref->dsc_attr.uc_dev_idx = pref->rsc_id;
		pref->dsc_attr.dsc_data_type = AUI_DSC_DATA_TS;
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
		aui_rtn = aui_dsc_open(&pref->dsc_attr, &pref->dsc_hdl);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc open error\n");
			ret = IA_FAIL;
			return ret;
		}
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
		pref->dsc_attr.puc_key = abKey;
		pref->dsc_attr.ul_key_len = key_st.wKeyLength * sizeof(ia_byte);
		pref->dsc_attr.dsc_key_type = AUI_DSC_HOST_KEY_SRAM;
		pref->dsc_attr.en_parity = AUI_DSC_PARITY_MODE_EVEN_PARITY_MODE; // raw mode not used
		pref->dsc_attr.uc_mode = AUI_DSC_WORK_MODE_IS_ECB;
		pref->dsc_attr.en_residue = AUI_DSC_RESIDUE_BLOCK_IS_NO_HANDLE;
		/* zero IV */
		ansi_memset(iv, 0, sizeof(iv));
		pref->dsc_attr.puc_iv_ctr = iv;
		aui_rtn = aui_dsc_attach_key_info2dsc(pref->dsc_hdl, &pref->dsc_attr);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc attach key error\n");
			goto des_close;
		}
		ret = IA_SUCCESS;
	}
	else
	{
		aui_dsc_close(pref->dsc_hdl);
		pref->dsc_hdl = NULL;
		ansi_memset(&pref->dsc_attr, 0x00, sizeof(aui_attr_dsc));
    	pref->dsc_attr.uc_dev_idx = pref->rsc_id;
		pref->dsc_attr.dsc_data_type = AUI_DSC_DATA_TS;
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
		aui_rtn = aui_dsc_open(&pref->dsc_attr, &pref->dsc_hdl);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc open error\n");
			ret = IA_FAIL;
			return ret;
		}
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
		pref->dsc_attr.puc_key = abKey;
		pref->dsc_attr.ul_key_len = key_st.wKeyLength * sizeof(ia_byte);
		pref->dsc_attr.dsc_key_type = AUI_DSC_HOST_KEY_SRAM;
		pref->dsc_attr.en_parity = AUI_DSC_PARITY_MODE_EVEN_PARITY_MODE; // raw mode not used
		pref->dsc_attr.uc_mode = AUI_DSC_WORK_MODE_IS_ECB;
		pref->dsc_attr.en_residue = AUI_DSC_RESIDUE_BLOCK_IS_NO_HANDLE;
		/* zero IV */
		ansi_memset(iv, 0, sizeof(iv));
		pref->dsc_attr.puc_iv_ctr = iv;
		aui_rtn = aui_dsc_attach_key_info2dsc(pref->dsc_hdl, &pref->dsc_attr);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc attach key error\n");
			goto des_close;
		}
		ret = IA_SUCCESS;
	}
	return ret;
des_close:
	if(NULL != abKey)
	{
		OS_DRV_FreeMemory(abKey);
		abKey = NULL;
	}
	if(NULL != pref->dsc_hdl)
	{
		aui_dsc_close(pref->dsc_hdl);
		pref->dsc_hdl = NULL;
	}
	ret = IA_FAIL;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_set_arib_data(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	ia_result ret = IA_SUCCESS;

	ret = IA_FAIL;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_set_skey(dsc_ref *pref, ia_word32 wDataWriteSize, ia_byte *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	unsigned long key_dst_pos;
	
	if(NULL == pref)
    {
		ret = IA_FAIL;
		return ret;
    }
    if(0 == wDataWriteSize)
    {
    	if(NULL != pref->encrypt_cssk)
    	{
			ansi_memset(pref->encrypt_cssk, 0x00, pref->cssk_size);
    	}
    	else
    	{
			pref->encrypt_cssk = OS_DRV_AllocateMemory(128);
			pref->cssk_size = 128;
			ansi_memset(pref->encrypt_cssk, 0x00, pref->cssk_size);
    	}
    	if(NULL != pref->kl_hdl)
		{
			/*gen fake key to reset*/
			pref->cfg.en_kl_algo = AUI_KL_ALGO_TDES;
			pref->cfg.en_crypt_mode = AUI_KL_DECRYPT;
			pref->cfg.en_cw_key_attr = AUI_KL_CW_KEY_EVEN;	
			ansi_memcpy(pref->cfg.ac_key_val, pref->encrypt_cssk, 
				(sizeof(pref->cfg.ac_key_val) > pref->cssk_size)? pref->cssk_size : sizeof(pref->cfg.ac_key_val));
			aui_rtn = aui_kl_gen_key_by_cfg(pref->kl_hdl, &pref->cfg, &key_dst_pos);
			aui_kl_close(pref->kl_hdl);
			pref->kl_hdl = NULL;
		}
		OS_DRV_FreeMemory(pref->encrypt_cssk);
		pref->encrypt_cssk = NULL;
		pref->cssk_size = 0;
		ret = IA_SUCCESS;
    }
    else if(NULL == pin)
    {
		ret = IA_FAIL;
    }
    else
    {
    	if(NULL != pref->encrypt_cssk)
		{
			OS_DRV_FreeMemory(pref->encrypt_cssk);
			pref->encrypt_cssk = NULL;
			pref->cssk_size = 0;
		}
		pref->encrypt_cssk = OS_DRV_AllocateMemory(wDataWriteSize);
		if(NULL == pref->encrypt_cssk)
		{
			DEBUG_S3_VD_PRINTF("aui  no mem to alloc\n");
        	ret = IA_FAIL;	
			return ret;
		}
		ansi_memset(pref->encrypt_cssk, 0x00, wDataWriteSize);
		ansi_memcpy(&pref->encrypt_cssk, pin, wDataWriteSize);
		pref->cssk_size = wDataWriteSize;
		pref->cfg.run_level_mode = AUI_KL_RUN_LEVEL_MODE_LEVEL_ALL;
		pref->cfg.en_kl_algo = AUI_KL_ALGO_TDES;
		pref->cfg.en_crypt_mode = AUI_KL_DECRYPT;
		/*generate EVEN key*/
		pref->cfg.en_cw_key_attr = AUI_KL_CW_KEY_EVEN;
		ret = IA_SUCCESS;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_add_pid(dsc_ref *pref, vd_dd_pid_st *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_hdl dsc_hdl = NULL;
	int i = 0;

	if((NULL == pref) || (NULL == pin) || (NULL == pref->dsc_hdl))
	{
		ret = IA_FAIL;
		return ret;
	}
	if(pref->dsc_attr.ul_pid_cnt >= AUI_DMX_STREAM_PIDS_CNT_MAX)
	{
		DEBUG_S3_VD_PRINTF("can not add more pid\n");
		ret = IA_FAIL;
		return ret;
	}
	for(i = 0; i < pref->dsc_attr.ul_pid_cnt; i++)
	{
		if(pref->dsc_attr.pus_pids[i]  == pin->wPid)
		{
			ret = IA_SUCCESS;
			return ret;
		}
	}
	pref->dsc_attr.pus_pids[pref->dsc_attr.ul_pid_cnt] = pin->wPid;
	pref->dsc_attr.ul_pid_cnt++;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_rm_pid(dsc_ref *pref, vd_dd_pid_st *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_hdl dsc_hdl = NULL;
	int i,j;
	

	if((NULL == pref) || (NULL == pin) || (NULL == pref->dsc_hdl))
	{
		ret = IA_FAIL;
		return ret;
	}
	for(i = 0; i < pref->dsc_attr.ul_pid_cnt; i++)
	{
		if(pref->dsc_attr.pus_pids[i]  == pin->wPid)
		{
			for(j = i; j < (pref->dsc_attr.ul_pid_cnt-1); j++)
			{
				pref->dsc_attr.pus_pids[j] = pref->dsc_attr.pus_pids[j+1];
			}
			pref->dsc_attr.ul_pid_cnt--;
			ret = IA_SUCCESS;
			return ret;
		}
	}
	/*can not find this pid*/
	ret = IA_FAIL;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_set_encrypt_key(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_dd_key_st key_st;
	void *dat_pos = NULL;
	unsigned char *key_map = NULL;
	unsigned long key_dst_pos;
	unsigned char iv[16 * 2];
	

	if((NULL == pref) || (0 == wDataWriteSize) 
	|| (NULL == pin) || (0 == pref->cssk_size) 
	|| (NULL == pref->encrypt_cssk))
    {
		ret = IA_FAIL;
		return ret;
    }
    ansi_memcpy(&key_st, pin, sizeof(vd_dd_key_st));
    dat_pos = pin + sizeof(vd_dd_key_st);
    key_map = OS_DRV_AllocateMemory(key_st.wKeyLength * sizeof(ia_byte) + pref->cssk_size);
    if(NULL == key_map)
	{
		DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        ret = IA_FAIL;	
		return ret;
	}
    ansi_memset(key_map, key_st.wKeyLength * sizeof(ia_byte) + pref->cssk_size);
	ansi_memcpy(key_map, dat_pos, key_st.wKeyLength * sizeof(ia_byte));
	dat_pos = key_map + key_st.wKeyLength * sizeof(ia_byte);
	ansi_memcpy(dat_pos, pref->encrypt_cssk, pref->cssk_size);
	if(NULL == pref->kl_hdl)
	{
		pref->kl_attr.uc_dev_idx = pref->rsc_id;
		if(128 == key_st.wKeyLength)
		{
			pref->kl_attr.en_key_pattern = AUI_KL_OUTPUT_KEY_PATTERN_128_ODD_EVEN;
		}
		else if(64 == key_st.wKeyLength)
		{
			pref->kl_attr.en_key_pattern = AUI_KL_OUTPUT_KEY_PATTERN_64_ODD_EVEN;
		}
		else
		{	
			pref->kl_attr.en_key_pattern = AUI_KL_OUTPUT_KEY_PATTERN_NB;
		}
		pref->kl_attr.en_level = AUI_KL_KEY_TWO_LEVEL;
		pref->kl_attr.en_root_key_idx = AUI_KL_ROOT_KEY_0_0;
		aui_rtn = aui_kl_open(&pref->kl_attr, &pref->kl_hdl);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("aui_kl_open error\n");
			ret = IA_FAIL;	
			return ret;
		}
	}
	ansi_memcpy(pref->cfg.ac_key_val, key_map, 
				(sizeof(pref->cfg.ac_key_val) > (pref->cssk_size + key_st.wKeyLength * sizeof(ia_byte)))? pref->cssk_size + key_st.wKeyLength * sizeof(ia_byte) : sizeof(pref->cfg.ac_key_val));

	aui_rtn = aui_kl_gen_key_by_cfg(pref->kl_hdl, &pref->cfg, &key_dst_pos);
	if (AUI_RTN_SUCCESS != aui_rtn) 
	{
		DEBUG_S3_VD_PRINTF("aui_kl_gen_key_by_cfg error\n");
		goto error;
	}
	if(NULL == pref->dsc_hdl)
	{	
		pref->dsc_attr.uc_dev_idx = pref->rsc_id;
		pref->dsc_attr.dsc_data_type = AUI_DSC_DATA_TS;
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
		aui_rtn = aui_dsc_open(&pref->dsc_attr, &pref->dsc_hdl);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc open error\n");
			goto error;
		}
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
		pref->dsc_attr.ul_key_pos = key_dst_pos;
		pref->dsc_attr.ul_key_len = key_st.wKeyLength * sizeof(ia_byte);
		pref->dsc_attr.dsc_key_type = AUI_DSC_CONTENT_KEY_KL;
		pref->dsc_attr.en_parity = AUI_DSC_PARITY_MODE_EVEN_PARITY_MODE; // raw mode not used
		pref->dsc_attr.uc_mode = AUI_DSC_WORK_MODE_IS_ECB;
		pref->dsc_attr.en_residue = AUI_DSC_RESIDUE_BLOCK_IS_NO_HANDLE;
		/* zero IV */
		ansi_memset(iv, 0, sizeof(iv));
		pref->dsc_attr.puc_iv_ctr = iv;
		aui_rtn = aui_dsc_attach_key_info2dsc(pref->dsc_hdl, &pref->dsc_attr);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc attach key error\n");
			goto error;
		}
		ret = IA_SUCCESS;
	}
	else
	{
		aui_dsc_close(pref->dsc_hdl);
		pref->dsc_hdl = NULL;
		ansi_memset(&pref->dsc_attr, 0x00, sizeof(aui_attr_dsc));
    	pref->dsc_attr.uc_dev_idx = pref->rsc_id;
		pref->dsc_attr.dsc_data_type = AUI_DSC_DATA_TS;
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
		aui_rtn = aui_dsc_open(&pref->dsc_attr, &pref->dsc_hdl);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc open error\n");
			goto error;
		}
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
		pref->dsc_attr.ul_key_pos = key_dst_pos;
		pref->dsc_attr.ul_key_len = key_st.wKeyLength * sizeof(ia_byte);
		pref->dsc_attr.dsc_key_type = AUI_DSC_CONTENT_KEY_KL;
		pref->dsc_attr.en_parity = AUI_DSC_PARITY_MODE_EVEN_PARITY_MODE; // raw mode not used
		pref->dsc_attr.uc_mode = AUI_DSC_WORK_MODE_IS_ECB;
		pref->dsc_attr.en_residue = AUI_DSC_RESIDUE_BLOCK_IS_NO_HANDLE;
		/* zero IV */
		ansi_memset(iv, 0, sizeof(iv));
		pref->dsc_attr.puc_iv_ctr = iv;
		aui_rtn = aui_dsc_attach_key_info2dsc(pref->dsc_hdl, &pref->dsc_attr);
		if (AUI_RTN_SUCCESS != aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dsc attach key error\n");
			goto error;
		}
		ret = IA_SUCCESS;
	}
	return ret;
error:
	if(NULL != key_map)
	{	
		OS_DRV_FreeMemory(key_map);
		key_map = NULL;
	}
	if(NULL != pref->dsc_hdl)
	{
		aui_dsc_close(pref->dsc_hdl);
		pref->dsc_hdl = NULL;
	}
	if(NULL != pref->kl_hdl)
	{
		aui_kl_close(pref->kl_hdl);
		pref->kl_hdl = NULL;
	}
	ret = IA_FAIL;
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
 *  @date               8/31/2016, Created
 *
 *  @note
 */
static ia_result vddd_io_set_session_key(dsc_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_dd_scp3_skey_st cssk_st;
	void *dat_pos = NULL;
	unsigned long key_dst_pos;

	if(NULL == pref)
    {
		ret = IA_FAIL;
		return ret;
    }
    if(0 == wDataWriteSize)
    {
    	if(NULL != pref->encrypt_cssk)
    	{
			ansi_memset(pref->encrypt_cssk, 0x00, pref->cssk_size);
    	}
    	else
    	{
			pref->encrypt_cssk = OS_DRV_AllocateMemory(128);
			pref->cssk_size = 128;
			ansi_memset(pref->encrypt_cssk, 0x00, pref->cssk_size);
    	}
    	if(NULL != pref->kl_hdl)
		{
			/*gen fake key to reset*/
			pref->cfg.en_kl_algo = AUI_KL_ALGO_TDES;
			pref->cfg.en_crypt_mode = AUI_KL_DECRYPT;
			pref->cfg.en_cw_key_attr = AUI_KL_CW_KEY_EVEN;	
			ansi_memcpy(pref->cfg.ac_key_val, pref->encrypt_cssk, 
				(sizeof(pref->cfg.ac_key_val) > pref->cssk_size)? pref->cssk_size : sizeof(pref->cfg.ac_key_val));
			aui_rtn = aui_kl_gen_key_by_cfg(pref->kl_hdl, &pref->cfg, &key_dst_pos);
			aui_kl_close(pref->kl_hdl);
			pref->kl_hdl = NULL;
		}
		OS_DRV_FreeMemory(pref->encrypt_cssk);
		pref->encrypt_cssk = NULL;
		pref->cssk_size = 0;
		ret = IA_SUCCESS;
    }
    else if(NULL == pin)
    {
		ret = IA_FAIL;
    }
    else
    {
    	if(NULL != pref->encrypt_cssk)
		{
			OS_DRV_FreeMemory(pref->encrypt_cssk);
			pref->encrypt_cssk = NULL;
			pref->cssk_size = 0;
		}
		ansi_memcpy(&cssk_st, pin, sizeof(vd_dd_scp3_skey_st));
		dat_pos = pin + sizeof(vd_dd_scp3_skey_st);
		pref->encrypt_cssk = OS_DRV_AllocateMemory(cssk_st.wKeyLength);
		if(NULL == pref->encrypt_cssk)
		{
			DEBUG_S3_VD_PRINTF("aui no mem to alloc\n");
        	ret = IA_FAIL;	
			return ret;
		}
		ansi_memset(pref->encrypt_cssk, 0x00, wDataWriteSize);
		ansi_memcpy(&pref->encrypt_cssk, dat_pos, cssk_st.wKeyLength);
		pref->cssk_size = cssk_st.wKeyLength;
		pref->cfg.run_level_mode = AUI_KL_RUN_LEVEL_MODE_LEVEL_ALL;
		switch(cssk_st.eAlgorithm)
		{
			case VD_DD_2TDES:
				pref->cfg.en_kl_algo = AUI_KL_ALGO_TDES;
				break;
			case VD_DD_AES:
				pref->cfg.en_kl_algo = AUI_KL_ALGO_AES;
				break;
			default:
				pref->cfg.en_kl_algo = AUI_KL_ALGO_NB;
				break;
		}
		pref->cfg.en_crypt_mode = AUI_KL_DECRYPT;
		/* generate EVEN key */
		pref->cfg.en_cw_key_attr = AUI_KL_CW_KEY_EVEN;
		ret = IA_SUCCESS;
    }
	return ret;
}
