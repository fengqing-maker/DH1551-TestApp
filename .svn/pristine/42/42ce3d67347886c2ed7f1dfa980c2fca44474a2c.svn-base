/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vddf.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:03:49
 *  @revision           none
 *
 *  @author              <>
 */

/**
 * This file contains all external definitions for versions 1,2 and 3 of the 'Transport DeMUX and
 * Filter driver'. Corresponding vd_driver_type_e is VD_DRIVER_DVB_FILTER.
 * Version 1 was known as the 'DVB DeMUX and Filter driver'.
 **/


#include <s3_vddf.h>
#include <s3_vd.h>
#include <s3_osdrv.h>
#include "ali_vd_drv.h"
#include "s3_ansi_functions.h"

#include <aui_dmx.h>
#include <aui_common.h>

#define DMX_V1 1
#define DMX_V3 3
#define DMX_MAX_RES 1

#define HARDWARE_DMX_DEV_ID (0)
#define SOFTWARE_DMX_DEV_ID (2)

typedef struct chn_ref{
	vd_df_open_v2_st 				chn_st;
	vd_rsc_id						rsc_id;
	vd_ref_id						ref_id;
	vd_df_config_event_st			ev_cb;
	aui_hdl 						chn_hld;
	aui_attr_dmx_channel 			chn_attr;
	vd_df_filter_id					filter_id_cnt;
	struct aui_list_head 			filter_head;
	struct aui_list_head 			node;
} chn_ref;
typedef struct _vd_filter_hdl{
	vd_df_filter_id id;
	vd_df_alloc_filter_st ft_st;
	aui_hdl aui_hdl_filter;
	aui_attr_dmx_filter attr_filter;
	struct aui_list_head node;
	ia_word16 wSectionLength;
	ia_byte *sect_buf;
} _vd_filter_hdl;

static vd_ref_id ref_cnt = 0;
static AUI_LIST_HEAD(chn_ref_head);
ia_result init_s3_vddf();

static ia_word16 vddf_get_drv_version();

static ia_result vddf_get_resources(void **ppvList, ia_word16 *pwCount);

static vd_ref_id vddf_drv_open(vd_rsc_id wResourceID, void *pvData);

static ia_result vddf_drv_close(vd_ref_id wRefId);

static ia_result vddf_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead );
			
static ia_result destroy_vddf_drv(void *priv_dat);

static ia_result vd_open_filter(struct chn_ref *pref, vd_df_alloc_filter_st *pin, 
									vd_df_filter_st *pout);

static ia_result vd_close_filter(struct chn_ref *pref, vd_df_filter_st *pin); 

static ia_result vd_set_pid(struct chn_ref *pref, vd_df_pid_st *pin);	

static long aui_filter_section_cb
(
	aui_hdl filter_handle,
	unsigned char *p_section_data_buf_addr,
	unsigned long ul_section_data_len,
	void *usr_data,
	void *reserved
);

static ia_result vd_set_filter(struct chn_ref *pref, ia_word32 wDataWriteSize, void *pin); 

static ia_result vd_read_sect(struct chn_ref *pref, ia_word32 *pwDataReadSize,void *pout); 

static ia_result vd_start_all_filters(struct chn_ref *pref);

static ia_result vd_stop_all_filters(struct chn_ref *pref);

static ia_result vd_reset_all_sect_buf(struct chn_ref *pref);

static ia_result vd_reg_event_cb(struct chn_ref *pref, vd_df_config_event_st *pin);

static struct vd_drv vddf_drv = {
		.drv_typ 			= VD_DRIVER_DVB_FILTER,
		.priv				= NULL,
		.get_drv_version 	= vddf_get_drv_version,
		.get_resources		= vddf_get_resources,
		.drv_open			= vddf_drv_open,
		.drv_close			= vddf_drv_close,
		.drv_ioctl			= vddf_drv_ioctl,
		.destroy			= destroy_vddf_drv,
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
ia_result init_s3_vddf()
{
	ia_result ret = IA_SUCCESS;
	
	ret = register_vd_drv(&vddf_drv);
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
static ia_word16 vddf_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = DMX_V3;
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
static ia_result vddf_get_resources(void **ppvList, ia_word16 *pwCount)
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
static vd_ref_id vddf_drv_open(vd_rsc_id wResourceID, void *pvData)
{
	struct vd_df_open_v2_st *param = NULL;
	aui_hdl dmx_hdl = NULL;
	aui_hdl dmx_chn_hdl = NULL;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_attr_dmx attr_dmx;
	aui_attr_dmx_channel channel_attr;
	int devid = 0;
	struct chn_ref *pref = NULL;

	
	if((wResourceID > DMX_MAX_RES) || (NULL == pvData))
	{
		return VD_REF_ID_ERROR;
	}
	param = (struct vd_df_open_v2_st *) pvData;
	ansi_memset(&attr_dmx, 0, sizeof(attr_dmx));
	ansi_memset(&channel_attr, 0, sizeof(channel_attr));
	switch(wResourceID)
	{
		case 0:
				devid = HARDWARE_DMX_DEV_ID;
				break;
		case 1:
				devid = SOFTWARE_DMX_DEV_ID ;
				break;
				
		default:
				return VD_REF_ID_ERROR;
	}
	attr_dmx.uc_dev_idx = (unsigned char) devid;
	aui_rtn = aui_find_dev_by_idx(AUI_MODULE_DMX, devid, &dmx_hdl);
	if(AUI_RTN_FAIL == aui_rtn)
	{	
		aui_rtn = aui_dmx_open(&attr_dmx, &dmx_hdl);
		if (AUI_RTN_FAIL == aui_rtn) 
		{
			DEBUG_S3_VD_PRINTF("dmx open failed\n");
			return VD_REF_ID_ERROR;
		}
		DEBUG_S3_VD_PRINTF("aui_dmx_open success\n");
		aui_rtn = aui_dmx_start(dmx_hdl, NULL);
		if(AUI_RTN_FAIL == aui_rtn)
    	{
    		DEBUG_S3_VD_PRINTF("dmx %d start fail", devid);
        	return VD_REF_ID_ERROR;
    	}
	}	
  	channel_attr.us_pid = 0;
    channel_attr.dmx_data_type = AUI_DMX_DATA_SECT;
    aui_rtn = aui_dmx_channel_open(dmx_hdl, &channel_attr, &dmx_chn_hdl);
    if (AUI_RTN_FAIL == aui_rtn) 
    {
		DEBUG_S3_VD_PRINTF("channel type %d allocate fail!\n", AUI_DMX_DATA_SECT);
		return VD_REF_ID_ERROR;
	}

	aui_rtn = aui_dmx_channel_start(dmx_chn_hdl, &channel_attr);
	if (AUI_RTN_SUCCESS != aui_rtn)
	{
		DEBUG_S3_VD_PRINTF("ERROR: %s: %d\n", __FUNCTION__, __LINE__);
		return VD_REF_ID_ERROR;
	}
	pref = OS_DRV_AllocateMemory(sizeof(struct chn_ref));
	if(NULL == pref)
	{
		DEBUG_S3_VD_PRINTF("No mem to alloc\n");
		aui_dmx_channel_stop(dmx_chn_hdl, &channel_attr);
		aui_dmx_channel_close(&dmx_chn_hdl);
		return VD_REF_ID_ERROR;
	}
	ansi_memcpy(&pref->chn_st, param, sizeof(vd_df_open_v2_st));
	pref->chn_hld = dmx_chn_hdl;
	ansi_memcpy(&pref->chn_attr, &channel_attr, sizeof(aui_attr_dmx_channel));
	pref->filter_id_cnt = 0;
	AUI_INIT_LIST_HEAD(&pref->filter_head);
	AUI_INIT_LIST_HEAD(&pref->node);
	pref->ev_cb.pfnEventNotify = NULL;
	pref->rsc_id = wResourceID;
	pref->ref_id = ref_cnt;
	ref_cnt++;
	aui_list_add_tail(&pref->node, &chn_ref_head);
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
static ia_result vddf_drv_close(vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;
	struct chn_ref *pref = NULL;
	int find_flag = 0;
		
	aui_list_for_each_entry(pref, &chn_ref_head, node)
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
	ret = vd_stop_all_filters(pref);
	ret = vd_reset_all_sect_buf(pref);
	aui_dmx_channel_stop(pref->chn_hld, NULL);	
	aui_dmx_channel_close(&pref->chn_hld);
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
static ia_result vddf_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead)
{
	ia_result ret = IA_SUCCESS;
	struct chn_ref *pref = NULL;
	int find_flag = 0;

	aui_list_for_each_entry(pref, &chn_ref_head, node)
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
		case VD_DF_ALLOCATE_FILTER:
			ret = vd_open_filter(pref, pvDataWrite, pvDataRead);
			break;
		case VD_DF_FREE_FILTER:
			ret = vd_close_filter(pref, pvDataWrite);
			break;
		
		case VD_DF_SET_PID:
			ret = vd_set_pid(pref, pvDataWrite);
			break;
		
		case VD_DF_SET_FILTER:
			ret = vd_set_filter(pref, wDataWriteSize, pvDataWrite);
			break;
		case VD_DF_READ_SECTION:
			ret = vd_read_sect(pref, pwDataReadSize, pvDataRead);
			break;
			
		case VD_DF_START:
			ret = vd_start_all_filters(pref);
			break;

		
		case VD_DF_STOP:
			ret = vd_stop_all_filters(pref);
			break;
			
		case VD_DF_RESET:
			ret = vd_reset_all_sect_buf(pref);
			break;
			
		case VD_DF_SET_IP_SOCKET:
			ret = IA_INVALID_PARAMETER;
			break;
			
		case VD_DF_SET_IPV6_SOCKET:
			ret = IA_INVALID_PARAMETER;
			break;
			
		case VD_DF_SET_SUBCHID_PA:
			ret = IA_INVALID_PARAMETER;
			break;
			
		case VD_DF_SET_CMMB_CONFIG:
			ret = IA_INVALID_PARAMETER;
			break;
			
		case VD_DF_CONFIG_EVENT_CALLBACK:
			ret = vd_reg_event_cb(pref, pvDataWrite);
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
static ia_result destroy_vddf_drv(void *priv_dat)
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
 *  @date               8/24/2016, Created
 *
 *  @note
 */
static ia_result vd_open_filter(struct chn_ref *pref, vd_df_alloc_filter_st *pin, 
									vd_df_filter_st *pout)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_attr_dmx_filter attr_filter;
    aui_hdl aui_hdl_filter = NULL;
    struct _vd_filter_hdl *tmp_filter_hld = NULL;
    unsigned char mask[] = {0xff};
    unsigned char value[] = {0x00};
    unsigned char reverse[] = {0x0};
     // Just care for the first BYTE
    unsigned long ul_mask_val_len=1;
    // Dont do CRC check for the section data
	unsigned char uc_crc_check=0;
    // Muti-times capture the section,if uc_continue_capture_flag==0,then just the first section will call the user callback
	unsigned char uc_continue_capture_flag=1;

	// have ignored the struct vd_df_alloc_filter_st *pin 
	if((NULL == pref) || (NULL == pout))
	{
		ret = IA_FAIL;
		return ret;
	}
	attr_filter.puc_mask = mask;
    attr_filter.puc_reverse = reverse;
    attr_filter.puc_val = value;
    attr_filter.ul_mask_val_len = ul_mask_val_len;
  	attr_filter.usr_data = (void *) pref;
    aui_rtn = aui_dmx_filter_open(pref->chn_hld,&attr_filter,&aui_hdl_filter);
    if(AUI_RTN_SUCCESS != aui_rtn)
    {
    	DEBUG_S3_VD_PRINTF("aui filter open fail\n");
    	ret = IA_FAIL;
    	return ret;
    }
    //The fun_sectionCB are the callback for app and implement by user
    aui_rtn = aui_dmx_reg_sect_call_back(aui_hdl_filter, aui_filter_section_cb);    
    //Configure the filter:user want to continue get all the table that the first byte equal 0x00
    // aui_rtn = aui_dmx_filter_mask_val_cfg(aui_hdl_filter,mask,value,reverse, ul_mask_val_len,uc_crc_check,uc_continue_capture_flag);
	tmp_filter_hld  = (struct _vd_filter_hdl *) OS_DRV_AllocateMemory(sizeof(struct _vd_filter_hdl));
	if((NULL == tmp_filter_hld))
	{
		DEBUG_S3_VD_PRINTF("ERROR: No mem to malloc!\n");
    	ret = IA_FULL;
    	return ret;
	}
    tmp_filter_hld->aui_hdl_filter = aui_hdl_filter;
    tmp_filter_hld->ft_st.eFilterType = pin->eFilterType;
    tmp_filter_hld->ft_st.wFilterLength = pin->wFilterLength;
    ansi_memcpy(&tmp_filter_hld->attr_filter, &attr_filter, sizeof(aui_attr_dmx_filter));
    tmp_filter_hld->id = pref->filter_id_cnt;
    tmp_filter_hld->wSectionLength = 0;
    tmp_filter_hld->sect_buf = NULL;
    pout->wFilterId = tmp_filter_hld->id;
    pref->filter_id_cnt++;
    aui_list_add_tail(&tmp_filter_hld->node, &pref->filter_head);
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
 *  @date               8/24/2016, Created
 *
 *  @note
 */
static long aui_filter_section_cb
(
	aui_hdl filter_handle,
	unsigned char *p_section_data_buf_addr,
	unsigned long ul_section_data_len,
	void *usr_data,
	void *reserved
)
{
	struct chn_ref *pref = (struct chn_ref *) usr_data;
	vd_df_receive_notify_v2_fn nt_cb = NULL;
	struct _vd_filter_hdl *tmp_filter_hld = NULL;
	
	if(NULL == pref)
	{
		return -1;
	}
	if(ul_section_data_len <= pref->chn_st.wMaxSectionSize)
	{
		
		aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
		{
			if(filter_handle == tmp_filter_hld->aui_hdl_filter)
			{
				tmp_filter_hld->wSectionLength = ul_section_data_len;
				if(NULL != tmp_filter_hld->sect_buf)
				{
					OS_DRV_FreeMemory(tmp_filter_hld->sect_buf);
					tmp_filter_hld->sect_buf = NULL;
				}
				tmp_filter_hld->sect_buf = OS_DRV_AllocateMemory(tmp_filter_hld->wSectionLength * sizeof(ia_byte));
				if(NULL == tmp_filter_hld->sect_buf)
				{
					DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        			tmp_filter_hld->wSectionLength = 0;	
        			tmp_filter_hld->sect_buf = NULL;
				}
				else
				{
					ansi_memcpy(tmp_filter_hld->sect_buf, p_section_data_buf_addr, tmp_filter_hld->wSectionLength * sizeof(ia_byte));
				}
				break;
			}
		}	
		if(NULL != pref->chn_st.pfnReceiveNotify)
		{
			nt_cb = pref->chn_st.pfnReceiveNotify;
			nt_cb(pref->ref_id, pref->chn_st.wSoftCellVal,
				ul_section_data_len, p_section_data_buf_addr);
		}
	}
	
	return 0;  
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
 *  @date               8/24/2016, Created
 *
 *  @note
 */
static ia_result vd_close_filter(struct chn_ref *pref, vd_df_filter_st *pin)
{
	ia_result ret = IA_SUCCESS;
    AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
    struct _vd_filter_hdl *tmp_filter_hld = NULL;


 	if((NULL == pref) || (NULL == pin))
	{
		ret = IA_FAIL;
		return ret;
	}
	aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
	{
		if(pin->wFilterId == tmp_filter_hld->id)
		{
			aui_list_del(&tmp_filter_hld->node);
			break;
		}

	}
  	if(AUI_DMX_FILTER_STOP == tmp_filter_hld->attr_filter.dmx_filter_status)
  	{
		
		aui_rtn = aui_dmx_filter_close(&tmp_filter_hld->aui_hdl_filter);
		if(AUI_RTN_SUCCESS != aui_rtn)
    	{
    		DEBUG_S3_VD_PRINTF("aui filter close fail\n");
        	ret = IA_FAIL;
    		return ret;
    	}
    	if(NULL != tmp_filter_hld->sect_buf)
    	{
    		OS_DRV_FreeMemory(tmp_filter_hld->sect_buf);
    	}
    	OS_DRV_FreeMemory(tmp_filter_hld);
    	tmp_filter_hld = NULL;
    	ret = IA_SUCCESS;
  	}
  	else
  	{
  		aui_rtn = aui_dmx_filter_stop(tmp_filter_hld->aui_hdl_filter, NULL);
	
		aui_rtn = aui_dmx_filter_close(&tmp_filter_hld->aui_hdl_filter);
		if(AUI_RTN_SUCCESS != aui_rtn)
    	{
    		DEBUG_S3_VD_PRINTF("aui filter close fail\n");
        	ret = IA_FAIL;
    		return ret;
    	}
    	if(NULL != tmp_filter_hld->sect_buf)
    	{
    		OS_DRV_FreeMemory(tmp_filter_hld->sect_buf);
    	}
     	OS_DRV_FreeMemory(tmp_filter_hld);
    	tmp_filter_hld = NULL;
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
 *  @date               8/24/2016, Created
 *
 *  @note
 */
static ia_result vd_set_pid(struct chn_ref *pref, vd_df_pid_st *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_hdl chn_hld = NULL;
	aui_attr_dmx_channel channel_attr;

	if((NULL == pref) || (NULL == pin))
	{
		ret = IA_FAIL;
		return ret;
	}
	chn_hld = pref->chn_hld;
	aui_rtn = aui_dmx_channel_set(chn_hld, AUI_DMX_CHANNEL_PID_SET, pin->wPid);
	if(AUI_RTN_SUCCESS != aui_rtn)
    {
    	DEBUG_S3_VD_PRINTF("pid set fail\n");
        ret = IA_FAIL;
    	return ret;
    }
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
 *  @date               8/25/2016, Created
 *
 *  @note
 */
static ia_result vd_set_filter(struct chn_ref *pref, ia_word32 wDataWriteSize, void *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct _vd_filter_hdl *tmp_filter_hld = NULL;
	vd_df_filter_st ft_st;
	ia_byte *abMatch = NULL;
	ia_byte *abMask = NULL;
	void *dat_pos = NULL;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		ret = IA_FAIL;
		return ret;
    }
    ansi_memcpy(&ft_st, pin, sizeof(vd_df_filter_st));
    dat_pos = pin + sizeof(vd_df_filter_st);
    aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
    {
		if((NULL != tmp_filter_hld) && (tmp_filter_hld->id == ft_st.wFilterId))
		{
			abMatch = OS_DRV_AllocateMemory(tmp_filter_hld->ft_st.wFilterLength * sizeof(ia_byte));
			if(NULL == abMatch)
			{
				DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        		ret = IA_FAIL;	
				break;
			}
			abMask = OS_DRV_AllocateMemory(tmp_filter_hld->ft_st.wFilterLength * sizeof(ia_byte));
			if(NULL == abMatch)
			{
				DEBUG_S3_VD_PRINTF("aui filter no mem to alloc\n");
        		ret = IA_FAIL;	
				break;
			}
			ansi_memcpy(abMatch, dat_pos, tmp_filter_hld->ft_st.wFilterLength * sizeof(ia_byte));
			dat_pos = pin + (tmp_filter_hld->ft_st.wFilterLength * sizeof(ia_byte));
			ansi_memcpy(abMask, dat_pos, tmp_filter_hld->ft_st.wFilterLength * sizeof(ia_byte));
			aui_rtn = aui_dmx_filter_stop(tmp_filter_hld->aui_hdl_filter, NULL);
			if(AUI_RTN_SUCCESS != aui_rtn)
    		{
    			DEBUG_S3_VD_PRINTF("aui filter id %d stop fail\n", tmp_filter_hld->id);
        		ret = IA_FAIL;
        		break;
    		}
			tmp_filter_hld->attr_filter.puc_mask = abMask;
			tmp_filter_hld->attr_filter.puc_val = abMatch;
			tmp_filter_hld->attr_filter.ul_mask_val_len = tmp_filter_hld->ft_st.wFilterLength;
			aui_rtn  = aui_dmx_filter_start(tmp_filter_hld->aui_hdl_filter, &tmp_filter_hld->attr_filter);
			if(AUI_RTN_SUCCESS != aui_rtn)
			{
				DEBUG_S3_VD_PRINTF("aui filter id %d start fail\n", tmp_filter_hld->id);
        		ret = IA_FAIL;
        		break;
			}
			ret = IA_SUCCESS;
			break;
		}
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
 *  @date               8/25/2016, Created
 *
 *  @note
 */
static ia_result vd_read_sect(struct chn_ref *pref, ia_word32 *pwDataReadSize,void *pout)
{
	ia_result ret = IA_SUCCESS;
	vd_df_read_st rd_st;
	ia_byte *abSection = NULL;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct _vd_filter_hdl *tmp_filter_hld = NULL;
	void *dat_pos = NULL;

	aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
	{
		if((0 != tmp_filter_hld->wSectionLength) && (NULL != tmp_filter_hld->sect_buf))
		{
			rd_st.wFilterId = tmp_filter_hld->id;
			rd_st.wSectionLength = tmp_filter_hld->wSectionLength;
			*pwDataReadSize = sizeof(vd_df_read_st) + (sizeof(ia_byte) * tmp_filter_hld->wSectionLength);
			ansi_memcpy(pout, &rd_st, sizeof(vd_df_read_st));
			dat_pos = pout + sizeof(vd_df_read_st);
			ansi_memcpy(dat_pos, tmp_filter_hld->sect_buf, sizeof(ia_byte) * rd_st.wSectionLength);
			tmp_filter_hld->wSectionLength = 0;
			OS_DRV_FreeMemory(tmp_filter_hld->sect_buf);
			tmp_filter_hld->sect_buf = NULL;
			ret = IA_SUCCESS;
			return ret;
		}
	}	
	*pwDataReadSize = 0;
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
 *  @date               8/25/2016, Created
 *
 *  @note
 */
static ia_result vd_start_all_filters(struct chn_ref *pref)
{
    ia_result ret = IA_SUCCESS;
    AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct _vd_filter_hdl *tmp_filter_hld = NULL;
	
    if(NULL == pref)
    {
		ret = IA_FAIL;
		return ret;
    }
    aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
    {
		if((tmp_filter_hld != NULL) 
		&& (AUI_DMX_FILTER_RUN != tmp_filter_hld->attr_filter.dmx_filter_status))
		{
			
			aui_rtn  = aui_dmx_filter_start(tmp_filter_hld->aui_hdl_filter, &tmp_filter_hld->attr_filter);
			if(AUI_RTN_SUCCESS != aui_rtn)
			{
				DEBUG_S3_VD_PRINTF("aui filter id %d start fail\n", tmp_filter_hld->id);
        		ret = IA_FAIL;
			}
	
		}
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
 *  @date               8/25/2016, Created
 *
 *  @note
 */
static ia_result vd_stop_all_filters(struct chn_ref *pref)
{
    ia_result ret = IA_SUCCESS;
    AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct _vd_filter_hdl *tmp_filter_hld = NULL;

    if(NULL == pref)
    {
		ret = IA_FAIL;
		return ret;
    }
	aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
	{
		if(AUI_DMX_FILTER_STOP == tmp_filter_hld->attr_filter.dmx_filter_status)
		{
			continue;
		}
		aui_rtn = aui_dmx_filter_stop(tmp_filter_hld->aui_hdl_filter, NULL);
		if(AUI_RTN_SUCCESS != aui_rtn)
    	{
    		DEBUG_S3_VD_PRINTF("aui filter id %d stop fail\n", tmp_filter_hld->id);
        	ret = IA_FAIL;
    	}
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
 *  @date               8/25/2016, Created
 *
 *  @note
 */
static ia_result vd_reset_all_sect_buf(struct chn_ref *pref)
{
	ia_result ret = IA_SUCCESS;
	ia_byte *abSection = NULL;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	struct _vd_filter_hdl *tmp_filter_hld = NULL;

	if(NULL == pref)
    {
		ret = IA_FAIL;
		return ret;
    }
	aui_list_for_each_entry(tmp_filter_hld, &pref->filter_head, node)
	{
		if((0 != tmp_filter_hld->wSectionLength) || (NULL != tmp_filter_hld->sect_buf))
		{
			tmp_filter_hld->wSectionLength = 0;
			if(NULL != tmp_filter_hld->sect_buf)
			{
				OS_DRV_FreeMemory(tmp_filter_hld->sect_buf);
				tmp_filter_hld->sect_buf = NULL;
			}
		}
	}	
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
 *  @date               8/25/2016, Created
 *
 *  @note
 */
static ia_result vd_reg_event_cb(struct chn_ref *pref, vd_df_config_event_st *pin)
{
	ia_result ret = IA_SUCCESS;

	if((NULL == pref) || (NULL == pin))
    {
		ret = IA_FAIL;
		return ret;
    }
    pref->ev_cb.pfnEventNotify = pin->pfnEventNotify;
    ret = IA_SUCCESS;
	return ret;
}

