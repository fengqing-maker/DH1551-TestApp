/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vd.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 14:25:07
 *  @revision           none
 *
 *  @author              <clarence.chow@alitech.com>
 */
#include <s3_vd.h>
#include "ali_vd_drv.h"


/*  */
/**
 *  Function Name:      
 *  @brief    
 *		Initialise the virtual driver.          
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
ia_result VD_Initialise( void )
{
	ia_result ret = IA_SUCCESS;

	ret = init_all_vd_drv();
	if(IA_SUCCESS != ret)
	{
		DEBUG_S3_VD_PRINTF("s3 vd init fail! \n");
						
	}
	
	return ret;
}


/*  */
/**
 *  Function Name:      
 *  @brief              
 *		Terminate the virtual driver.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
void VD_Terminate( void )
{
	int i,j;
	ia_result ret = IA_SUCCESS;
	struct vd_drv *tmp_drv = NULL;
	for(i = 1; i < MAX_NR_OF_VD_TYPE + 1; i++)
	{
		tmp_drv = vd_drv_arr[i];
		if(NULL != tmp_drv)
		{
			if(NULL != tmp_drv->destroy)
			{
				ret = tmp_drv->destroy(tmp_drv->priv);
			}
		}
	}
	DEBUG_S3_VD_PRINTF("s3 vd terminate success! \n");

}

/*  */
/* Version numbers start with 1. 0 (VD_NOT_IMPLEMENTED) Means driver not implemented. */
/**
 *  Function Name:      
 *  @brief              
 *		Return the driver version for that virtual driver.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
ia_word16 VD_GetDriverVersion( vd_driver_type_e eDriverType )
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;
	struct vd_drv *tmp_drv = NULL;

	if((eDriverType < VD_DRIVER_SMARTCARD) || (VD_DRIVER_SMARTCARD > VD_DRIVER_PROXIMITY_DETECTION))
	{
		ver = VD_NOT_IMPLEMENTED;
		return ver;
	}
	tmp_drv = vd_drv_arr[eDriverType];
	if(NULL == tmp_drv)
	{
		ver = VD_NOT_IMPLEMENTED;
		return ver;
	}
	ver = tmp_drv->get_drv_version();
	return ver;
}

/*  */
/**
 *  Function Name:      
 *  @brief              
 *		Return the resources available for that virtual driver.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
ia_result VD_GetResources( vd_driver_type_e eDriverType, void **ppvList, ia_word16 *pwCount)
{
	ia_result ret = IA_SUCCESS;
	struct vd_drv *tmp_drv = NULL;

	if((eDriverType < VD_DRIVER_SMARTCARD) 
	|| (eDriverType > VD_DRIVER_PROXIMITY_DETECTION))
	{
		ret = IA_FAIL;
		*ppvList = NULL;
		*pwCount = 0;
		return ret;
	}
	tmp_drv = vd_drv_arr[eDriverType];
	if(NULL == tmp_drv)
	{
		ret = IA_FAIL;
		*ppvList = NULL;
		*pwCount = 0;
		return ret;
	}
	if(NULL != tmp_drv->get_resources)
	{
		DEBUG_S3_VD_PRINTF("call vd get resources!\n");
		ret = tmp_drv->get_resources(ppvList, pwCount);
	}
	else
	{
		ret = IA_INVALID_PARAMETER;
	}
	return ret;
}

/*  */
/**
 *  Function Name:      
 *  @brief              
 *		Open a resource.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
vd_ref_id VD_Open( vd_driver_type_e eDriverType, vd_rsc_id wResourceID, void *pvData )
{
	vd_ref_id id = VD_REF_ID_ERROR ;
	struct vd_drv *tmp_drv = NULL;

	if((eDriverType < VD_DRIVER_SMARTCARD) 
	|| (eDriverType > VD_DRIVER_PROXIMITY_DETECTION))
	{
		id = VD_REF_ID_ERROR;
		return id;
	}
	tmp_drv = vd_drv_arr[eDriverType];
	if(NULL == tmp_drv)
	{
		id = VD_REF_ID_ERROR;
		return id;
	}
	DEBUG_S3_VD_PRINTF("call vd drv_open!\n");
	id = tmp_drv->drv_open(wResourceID, pvData);
	return id;
}

/*  */
/**
 *  Function Name:      
 *  @brief              
 *		Close a resource.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
ia_result VD_Close( vd_driver_type_e eDriverType, vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;
	struct vd_drv *tmp_drv = NULL;

	if((eDriverType < VD_DRIVER_SMARTCARD) 
	|| (eDriverType > VD_DRIVER_PROXIMITY_DETECTION))
	{
		ret = IA_FAIL;
		return ret;
	}
	tmp_drv = vd_drv_arr[eDriverType];
	if(NULL == tmp_drv)
	{
		ret = IA_FAIL;
		return ret;
	}
	DEBUG_S3_VD_PRINTF("call vd drv_close!\n");
	ret = tmp_drv->drv_close(wRefId);
	return ret;
}

/*  */
/**
 *  Function Name:      
 *  @brief              
 *		send control messages to a resource.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/26/2016, Created
 *
 *  @note
 */
ia_result VD_IO( vd_driver_type_e eDriverType, vd_ref_id wRefId, ia_word16 wOpCode,
	ia_word32 wDataWriteSize, void *pvDataWrite, ia_word32 *pwDataReadSize, void *pvDataRead )
{
	ia_result ret = IA_SUCCESS;
	struct vd_drv *tmp_drv = NULL;

	if((eDriverType < VD_DRIVER_SMARTCARD) 
	|| (eDriverType > VD_DRIVER_PROXIMITY_DETECTION))
	{
		ret = IA_FAIL;
		return ret;
	}
	tmp_drv = vd_drv_arr[eDriverType];
	if(NULL == tmp_drv)
	{
		ret = IA_FAIL;
		return ret;
	}
	
	ret = tmp_drv->drv_ioctl(wRefId, wOpCode,
							wDataWriteSize, pvDataWrite, 
							 pwDataReadSize, pvDataRead); 
	return ret;
}



