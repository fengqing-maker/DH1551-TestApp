/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vdps.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:13:01
 *  @revision           none
 *
 *  @author              <>
 */


/**
 * This file is part of the 'persistent storage virtual driver'.
 * It contains all definitions for the smartcard virtual driver.
 **/



#include <s3_portable_types.h>
#include <s3_vd.h>
#include <s3_vdps.h>

//#include <stdio.h>
#include <api/libfs2/stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aui_flash.h>
#include "ali_vd_drv.h"

#define LOADER_PARTITION 	2 					//storage them to Loader partition.

#define BASE_PS_OFFSET 		(130*1024) 			//The start of the PS.
#define BASE_PS_LEN 		(512 + 640 * 8)

#define ID1_PS_OFFSET		(BASE_PS_OFFSET + BASE_PS_LEN)
#define ID1_PS_LEN			(5 *1024)

#define ID2_PS_OFFSET		(ID1_PS_OFFSET + ID1_PS_LEN)
#define ID2_PS_LEN			(1 *1024)

#define ID3_PS_OFFSET		(ID2_PS_OFFSET + ID2_PS_LEN)
#define ID3_PS_LEN			(512 + 640 * 8)

#define ID4_PS_OFFSET		(ID3_PS_OFFSET + ID3_PS_LEN)
#define ID4_PS_LEN			(1288)

#define MAX_PS_ID			4

static ia_word32 mem_map_offset [MAX_PS_ID + 1] = {BASE_PS_OFFSET, ID1_PS_OFFSET, ID2_PS_OFFSET, ID3_PS_OFFSET, ID4_PS_OFFSET};
static ia_word32 mem_map_len [MAX_PS_ID + 1] = {BASE_PS_LEN, ID1_PS_LEN, ID2_PS_LEN, ID3_PS_LEN, ID4_PS_LEN};


typedef struct _ps_module_
{
    vd_ref_id				node_id;
	vd_ps_error_notify_fn	pfnErrorNotify;
	ia_word32				wSoftCellVal;
	
    void 					*nodes;
}ps_module;

typedef struct _vd_ps_module_list_
{
    ia_word16				count;
	ia_byte					cleared;
	aui_hdl 				flash_handle;
    ps_module				*nodes;
}vd_ps_module_list;

#define PS_V1 1
#define PS_V2 2
static ia_word16 vd_ps_get_drv_version();
static vd_ref_id vd_ps_open (vd_rsc_id wResourceID, void *pvData);
static ia_result vd_ps_close (vd_ref_id wRefId);
static ia_result vd_ps_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead);


static vd_drv vdps_res = {
		.drv_typ 			= VD_DRIVER_PERSISTENT_STORAGE,
		.priv				= NULL,
		.get_drv_version 	= vd_ps_get_drv_version,
		.get_resources		= NULL,
		.drv_open			= vd_ps_open,
		.drv_close			= vd_ps_close,
		.drv_ioctl			= vd_ps_ioctl,
		.destroy			= NULL,
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

static ia_word16 vd_ps_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = PS_V2;
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
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static vd_ref_id vd_ps_open (vd_rsc_id wResourceID, void *pvData)
{
	vd_ps_module_list *pPsModList = (vd_ps_module_list *) vdps_res.priv;
	vd_ps_open_st *data = (vd_ps_open_st *) pvData;
	ia_word32 i = 0;

	if (NULL == pvData)
	{
		return -1;//IA_INVALID_PARAMETER;
	}

	if (NULL == pPsModList ||NULL == pPsModList->flash_handle)
	{
		return -1;//IA_FAIL;
	}

	ps_module *ppsm = pPsModList->nodes;
	if (NULL == ppsm)
	{
		ppsm = pPsModList->nodes = (ps_module *)malloc (sizeof (ps_module));
		if (NULL == ppsm)
		{
			return VD_OUT_OF_MEMORY;
		}
		
		memset (ppsm, 0, sizeof (ps_module));
		ppsm->node_id = (vd_ref_id)pPsModList->nodes;
		ppsm->wSoftCellVal = data->wSoftCellVal;
		ppsm->pfnErrorNotify = data->pfnErrorNotify;
			
	}
	else
	{
		for (i = 0; i < pPsModList->count; i++)
		{
			if (NULL == ppsm->nodes)
			{
				ppsm->nodes = (ps_module *)malloc (sizeof (ps_module));
				if (NULL == ppsm->nodes)
				{
					return VD_OUT_OF_MEMORY;
				}
				
				ppsm = ppsm->nodes;
				memset (ppsm, 0, sizeof (ps_module));
				ppsm->node_id = (vd_ref_id)ppsm->nodes;
				ppsm->wSoftCellVal = data->wSoftCellVal;
				ppsm->pfnErrorNotify = data->pfnErrorNotify;
				
				break;
			}
			else
			{
				ppsm = ppsm->nodes;
			}
		}
	}
	pPsModList->count++;

	return ppsm->node_id;
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
static ia_result vd_ps_close (vd_ref_id wRefId)
{
	vd_ps_module_list *pPsModList = (vd_ps_module_list *) vdps_res.priv;
	ia_result ret = IA_FAIL;
	
	if (wRefId <= 0)
	{
		return VD_WRONG_REF_ID;
	}

	if (pPsModList->count <= 0)
	{
		return ret;
	}
	else if (1 == pPsModList->count)
	{
		free (pPsModList->nodes);
		pPsModList->nodes = NULL;
		pPsModList->count--;
		ret = IA_SUCCESS;
	}
	else
	{
		ia_word32 i = 0;
		ps_module *pCurPSM, *pPrePSM;
		pCurPSM = pPrePSM = pPsModList->nodes;
		while (i < pPsModList->count && NULL != pCurPSM)
		{
			if (wRefId == pCurPSM->node_id)
			{//find right id, remove this node;
				ret = IA_SUCCESS;
				pPrePSM->nodes = pCurPSM->nodes;
				free (pCurPSM);
				pPsModList->count--;
				break;
			}
			pPrePSM = pCurPSM;
			pCurPSM = pCurPSM->nodes;
			i++;
		}

		ret = VD_WRONG_REF_ID;
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
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vd_ps_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead)
{
	vd_ps_module_list *pPsModList = (vd_ps_module_list *) vdps_res.priv;
	ps_module *pPSM = pPsModList->nodes;
	ia_word32 i = 0;
	ia_result ret = IA_FAIL;
	AUI_RTN_CODE atn = AUI_RTN_SUCCESS;

	if (0 == pPsModList->count ||NULL == pPSM)
	{
		return ret;
	}

	for (i = 0; i < pPsModList->count; i++)
	{
		if (wRefId == pPSM->node_id)
		{
			break;
		}
		pPSM = pPSM->nodes;
		if (NULL == pPSM || (i + 1) == pPsModList->count)
		{
			return ret;
		}
	}


	switch (wOpCode)
	{
		case VD_PS_WRITE:
		{
			vd_ps_write_st *pw = (vd_ps_write_st *) pvDataWrite;
			ia_byte *buf = pvDataWrite;
			ia_word32 actual_size;
			ia_word32 write_size;
			
			buf += sizeof (vd_ps_write_st);

			if ((0x1 & pPsModList->cleared) == 1)
			{
				ret = VD_NO_ACCESS;
				break;
			}

			if (NULL == pvDataWrite || pw->wStart > BASE_PS_LEN)
			{
				ret = IA_INVALID_PARAMETER;
				break;
			}
	
			if (pw->wStart + pw->wLength > BASE_PS_LEN)
			{
				write_size = BASE_PS_LEN - pw->wStart;
			}
			
			atn = aui_flash_write(pPsModList->flash_handle, pw->wStart + BASE_PS_OFFSET, write_size, &actual_size, buf);
			if (atn)
			{
				ret = IA_FAIL;
			}
			else if (actual_size < pw->wLength)
			{
				ret = VD_WRITE_INCOMPLETE;
			}
			else
			{
				ret = IA_SUCCESS;
			}
			
			break;
		}

		case VD_PS_READ:
		{
			vd_ps_read_st *pr = (vd_ps_read_st *) pvDataWrite;
			ia_word32 actual_size;
			ia_word32 read_size;

			if ((0x1 & pPsModList->cleared) == 1)
			{
				ret = VD_NO_ACCESS;
				break;
			}

			if (NULL == pvDataRead || NULL == pvDataWrite || pr->wStart > BASE_PS_LEN)
			{
				return IA_INVALID_PARAMETER;
			}
			
			if (pr->wStart + pr->wLength > BASE_PS_LEN)
			{
				read_size = BASE_PS_LEN - pr->wStart;
			}
			
			atn = aui_flash_read(pPsModList->flash_handle, pr->wStart + BASE_PS_OFFSET, read_size, &actual_size, pvDataRead);
			if (atn)
			{
				ret = IA_FAIL;
			}
			else if (actual_size < pr->wLength)
			{
				*pwDataReadSize = actual_size;
				ret = VD_READ_INCOMPLETE;
			}
			else
			{
				ret = IA_SUCCESS;
			}
			
			break;
		}

		case VD_PS_DELETE:
		{
			if ((0x1 & pPsModList->cleared) == 1)
			{
				ret = VD_NO_ACCESS;
				break;
			}
			
			if (pPsModList->count > 1)
			{
				ret = VD_NO_ACCESS;
			}
			else
			{
				
				atn = aui_flash_erase(pPsModList->flash_handle, BASE_PS_OFFSET, BASE_PS_LEN);
				if (atn)
				{
					ret = IA_FAIL;
				}
				else
				{
					pPsModList->cleared |= 0x1;
					ret = IA_SUCCESS;
				}
			}
			
			break;
		}

		case VD_PS_WRITE_V2:
		{
			vd_ps_write_v2_st *pw2 = (vd_ps_write_v2_st *) pvDataWrite;
			ia_byte *buf = pvDataWrite;// + sizeof (vd_ps_write_v2_st);
			ia_word32 actual_size;
			ia_word32 write_size;
			ia_word32 file_len;
			ia_word32 file_offset;

			buf += sizeof (vd_ps_write_st);
			
			if (pw2->wIndex < 1 ||pw2->wIndex > MAX_PS_ID || NULL == pvDataWrite)
			{
				ret = IA_INVALID_PARAMETER;
				break;
			}

			if (((0x1<< pw2->wIndex) & pPsModList->cleared) == 1)
			{
				ret = VD_NO_ACCESS;
				break;
			}

			file_offset = mem_map_offset [pw2->wIndex];
			file_len = mem_map_len [pw2->wIndex];

			if (pw2->wStart > file_len)
			{
				ret = IA_INVALID_PARAMETER;
				break;
			}

			if (pw2->wStart + pw2->wLength > file_len)
			{
				write_size = file_len - pw2->wStart;
			}

			atn = aui_flash_write(pPsModList->flash_handle, pw2->wStart + file_offset, write_size, &actual_size, buf);
			if (atn)
			{
				ret = IA_FAIL;
			}
			else if (actual_size < pw2->wLength)
			{
				ret = VD_WRITE_INCOMPLETE;
			}
			else
			{
				ret = IA_SUCCESS;
			}
			
			break;
		}

		case VD_PS_READ_V2:
		{
			vd_ps_read_v2_st *pr2 = (vd_ps_read_v2_st *) pvDataWrite;
			ia_word32 actual_size;
			ia_word32 read_size;
			ia_word32 file_len;
			ia_word32 file_offset;

			if (pr2->wIndex < 1 ||pr2->wIndex > MAX_PS_ID || NULL == pvDataRead || NULL == pvDataWrite)
			{
				ret = IA_INVALID_PARAMETER;
				break;
			}

			if (((0x1<< pr2->wIndex) & pPsModList->cleared) == 1)
			{
				ret = VD_NO_ACCESS;
				break;
			}

			file_offset = mem_map_offset [pr2->wIndex];
			file_len = mem_map_len [pr2->wIndex];

			if (pr2->wStart > file_len)
			{
				ret = IA_INVALID_PARAMETER;
				break;
			}
			
			if (pr2->wStart + pr2->wLength > file_len)
			{
				read_size = file_len - pr2->wStart;
			}
			
			atn = aui_flash_read(pPsModList->flash_handle, pr2->wStart + file_offset, read_size, &actual_size, pvDataRead);
			if (atn)
			{
				ret = IA_FAIL;
			}
			else if (actual_size < pr2->wLength)
			{
				*pwDataReadSize = actual_size;
				ret = VD_READ_INCOMPLETE;
			}
			else
			{
				ret = IA_SUCCESS;
			}
			
			break;
		}

		case VD_PS_DELETE_V2:
		{
			vd_ps_delete_v2_st *pd2 = (vd_ps_delete_v2_st *) pvDataWrite;
			ia_word32 file_len;
			ia_word32 file_offset;
			
			if (((0x1<< pd2->wIndex) & pPsModList->cleared) == 1)
			{
				ret = VD_NO_ACCESS;
				break;
			}

			file_offset = mem_map_offset [pd2->wIndex];
			file_len = mem_map_len [pd2->wIndex];
			
			if (pPsModList->count > 1)
			{
				ret = VD_NO_ACCESS;
			}
			else
			{
				
				atn = aui_flash_erase(pPsModList->flash_handle, file_offset, file_len);
				if (atn)
				{
					ret = IA_FAIL;
				}
				else
				{
					pPsModList->cleared |= (0x1<< pd2->wIndex);
					ret = IA_SUCCESS;
				}
			}
			
			break;
		}

		default:
		{
			ret = VD_NOT_SUPPORTED;
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
 *  @date               7/29/2016, Created
 *
 *  @note
 */

ia_result init_s3_vdps()
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE atn = AUI_RTN_SUCCESS;
	aui_flash_open_param open_param;
	aui_flash_info flash_info;
	vd_ps_module_list *pPSM = NULL;

	/*here implement your own module init code*/
	vdps_res.priv = (void*)malloc (sizeof (vd_ps_module_list));
	memset (vdps_res.priv, 0, sizeof (vd_ps_module_list));

	pPSM = (vd_ps_module_list *) vdps_res.priv;

	aui_flash_init (NULL, NULL);
	
	memset(&open_param, 0, sizeof (aui_flash_open_param));
	open_param.flash_id = LOADER_PARTITION;
	open_param.flash_type = FLASH_TYPE_NOR;
	atn = aui_flash_open(&open_param, &pPSM->flash_handle);
	if (atn)
	{
		free (vdps_res.priv);
		vdps_res.priv = NULL;
		return IA_FAIL;
	}
	
	atn = aui_flash_info_get(pPSM->flash_handle, &flash_info);
	if (atn)
	{
		free (vdps_res.priv);
		vdps_res.priv = NULL;
		return IA_FAIL;
	}
	printf ("\n\nblock_cnt: %d, block_size: %#x, flash_size: %#x\n\n",
			flash_info.block_cnt, flash_info.block_size, flash_info.flash_size);
	
	ret = register_vd_drv(&vdps_res);
	
	return ret;
}

