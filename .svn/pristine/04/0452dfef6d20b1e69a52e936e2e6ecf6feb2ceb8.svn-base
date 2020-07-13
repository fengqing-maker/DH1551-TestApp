/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vd_external_storage.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:05:33
 *  @revision           none
 *
 *  @author              <>
 */


/**
 * This file contains all the definitions for the 'External Storage virtual driver'.
 **/


#include <s3_vd_external_storage.h>
#include <s3_vd.h>
#include "ali_vd_drv.h"
//#include <stdio.h>
#include <api/libfs2/stdio.h>
//#include <dirent.h>
#include <stdlib.h>
#include <string.h>



typedef struct _es_module_
{
	ia_word32               wRecordId;
	vd_es_access_mode_e     eAccessMode;
	vd_es_error_notify_fn   pfnErrorNotify;
	ia_word32               wSoftCellVal;
	FILE					*fd;
	
    void					*nodes;
}es_module;

typedef struct _vd_es_module_list_
{
    ia_word32				count;
    es_module				*nodes;
}vd_es_module_list;

#define EXTERNAL_STORAGE_PATH   "/mnt/usb/sda1/ALIDVRS2/"

static ia_word16 vd_es_get_drv_version();
static vd_ref_id vd_es_open (vd_rsc_id wResourceID, void *pvData);
static ia_result vd_es_close (vd_ref_id wRefId);
static ia_result vd_es_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead);


static vd_drv vdes_res = {
		.drv_typ 			= VD_DRIVER_EXTERNAL_STORAGE,
		.priv				= NULL,
		.get_drv_version 	= vd_es_get_drv_version,
		.get_resources		= NULL,
		.drv_open			= vd_es_open,
		.drv_close			= vd_es_close,
		.drv_ioctl			= vd_es_ioctl,
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
static ia_word16 vd_es_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = 1;
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
static vd_ref_id vd_es_open (vd_rsc_id wResourceID, void *pvData)
{
	vd_es_module_list *pEsModList = (vd_es_module_list *) vdes_res.priv;
	vd_es_open_st *data = (vd_es_open_st *) pvData;
	ia_word32 i = 0;
	DIR *Dir = NULL;
	ia_byte *AcMode = NULL;
	ia_byte *FilePath = NULL;
	FILE *Fd;
	
	if (NULL == pvData || NULL == pEsModList)
	{
		return -1;
	}

    if (NULL == (Dir = opendir(EXTERNAL_STORAGE_PATH))) {
        printf ("opendir failed!try to create a new one\n");
		if (-1 == mkdir(EXTERNAL_STORAGE_PATH, 0755))
		{
			printf ("mkdir error\n");
			return -1;
		}
    }
	closedir(Dir);

	if (data->eAccessMode == VD_ES_ACCESS_MODE_READONLY)
		AcMode = "rb";
	else if (data->eAccessMode == VD_ES_ACCESS_MODE_WRITEONLY)
		AcMode = "ab";
	else if (data->eAccessMode == VD_ES_ACCESS_MODE_READWRITE)
		AcMode = "ab+";
	else
		return -1;

	sprintf (FilePath, EXTERNAL_STORAGE_PATH"record_%08x_%08x", wResourceID, data->wRecordId);
	Fd = fopen (FilePath, AcMode);
	if (NULL== Fd)
	{
		printf ("open file %s failed\n", FilePath);
		return -1;
	}

	es_module *pEsm = pEsModList->nodes;
	if (NULL == pEsm)
	{
		pEsm = pEsModList->nodes = (es_module *)malloc (sizeof (es_module));
		if (NULL == pEsm)
		{
			return VD_OUT_OF_MEMORY;
		}
		
		memset (pEsm, 0, sizeof (es_module));
	}
	else
	{
		for (i = 0; i < pEsModList->count; i++)
		{
			if (NULL == pEsm->nodes)
			{
				pEsm->nodes = (void *)malloc (sizeof (es_module));
				if (NULL == pEsm->nodes)
				{
					return VD_OUT_OF_MEMORY;
				}
				
				pEsm = (es_module *)pEsm->nodes;
				memset (pEsm, 0, sizeof (es_module));
				break;
			}
			else
			{
				pEsm = (es_module *)pEsm->nodes;
			}
		}
	}

	pEsm->wRecordId = data->wRecordId;
	pEsm->eAccessMode = data->eAccessMode;
	pEsm->wSoftCellVal = data->wSoftCellVal;
	pEsm->pfnErrorNotify = data->pfnErrorNotify;
	pEsm->fd = Fd;
		
	pEsModList->count++;

	return pEsm->wRecordId;
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
static ia_result vd_es_close (vd_ref_id wRefId)
{
	vd_es_module_list *pEsModList = (vd_es_module_list *) vdes_res.priv;
	ia_result ret = IA_SUCCESS;
	
	if (wRefId <= 0)
	{
		return VD_WRONG_REF_ID;
	}

	if (pEsModList->count <= 0)
	{
		return ret;
	}
	else if (1 == pEsModList->count)
	{
		free (pEsModList->nodes);
		pEsModList->nodes = NULL;
		pEsModList->count--;
		ret = IA_SUCCESS;
	}
	else
	{
		ia_word32 i = 0;
		es_module *pCurESM, *pPreESM;
		pCurESM = pPreESM = pEsModList->nodes;
		while (i < pEsModList->count && NULL != pCurESM)
		{
			if (wRefId == pCurESM->wRecordId)
			{//find right id, remove this node;
				ret = IA_SUCCESS;
				if (NULL != pCurESM->fd)
					fclose (pCurESM->fd);
				pPreESM->nodes = pCurESM->nodes;
				free (pCurESM);
				pEsModList->count--;
				break;
			}
			pPreESM = pCurESM;
			pCurESM = pCurESM->nodes;
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
static ia_result vd_es_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead)
{
	vd_es_module_list *pEsModList = (vd_es_module_list *) vdes_res.priv;
	es_module *pEsm = pEsModList->nodes;
	ia_word32 i = 0;
	ia_result ret = IA_FAIL;
	FILE *Fd = NULL;

	if (0 == pEsModList->count ||NULL == pEsm)
	{
		return ret;
	}

	if (NULL== pvDataWrite)
	{
		return IA_INVALID_PARAMETER;
	}

	for (i = 0; i < pEsModList->count; i++)
	{
		if (wRefId == pEsm->wRecordId)
		{
			break;
		}
		pEsm = pEsm->nodes;
		if (NULL == pEsm || (i + 1) == pEsModList->count)
		{
			return ret;
		}
	}

	Fd = pEsm->fd;
	if (NULL == Fd)
		return IA_FAIL;

	switch (wOpCode)
	{
		case VD_ES_WRITE:
		{
			vd_es_write_st *pEw = pvDataWrite;
			ia_byte *buff = (ia_byte *)pEw;
			buff += sizeof (vd_es_write_st);

			fseek (Fd, pEw->wStart, SEEK_SET);
			fwrite (buff, pEw->wLength, 1, Fd);
			break;
		}

		case VD_ES_READ:
		{
			vd_es_read_st *pEr = pvDataWrite;
			
			if (NULL == pvDataRead)
			{
				ret = IA_INVALID_PARAMETER;
				break;
			}

			fseek (Fd, pEr->wStart, SEEK_SET);
			*pwDataReadSize = (ia_word32) fread (pvDataRead, pEr->wLength, 1, Fd);
			if (*pwDataReadSize < pEr->wLength)
			{
				 ret = VD_READ_INCOMPLETE;
			}

			break;
		}
		
		default:
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
 *  @date               7/29/2016, Created
 *
 *  @note
 */

ia_result init_s3_vd_external_storage()
{
	ia_result ret = IA_SUCCESS;
	//vd_es_module_list *pESM = NULL;

	/*here implement your own module init code*/
	vdes_res.priv = (void*)malloc (sizeof (vd_es_module_list));
	memset (vdes_res.priv, 0, sizeof (vd_es_module_list));
	//pESM = (vd_es_module_list *) vdes_res.priv;
	
	ret = register_vd_drv(&vdes_res);
	
	return ret;
}


