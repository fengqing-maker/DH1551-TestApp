/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\softcell\buildroot\output\build\ird_vd-undefined\virtual_driver\s3_demo_vd.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               8/16/2016 17:18:36
 *  @revision           none
 *
 *  @author              <>
 */


#include <s3_portable_types.h>
#include <s3_vd.h>
#include "ali_vd_drv.h"
// #include <s3_demo_vd.h> <-- shoule include the real head file in s3 vd documents

ia_result init_s3_demo_vd();

static ia_word16 demo_get_drv_version();

static ia_result demo_get_resources(void **ppvList, ia_word16 *pwCount);

static vd_ref_id demo_drv_open(vd_rsc_id wResourceID, void *pvData);

static ia_result demo_drv_close(vd_ref_id wRefId);

static ia_result demo_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead );
			
static ia_result destroy_demo_drv(void *priv_dat);

static struct vd_drv demo_drv = {
		.drv_typ 			= VD_DRIVER_PROXIMITY_DETECTION,
		.priv				= NULL,
		.get_drv_version 	= demo_get_drv_version,
		.get_resources		= demo_get_resources,
		.drv_open			= demo_drv_open,
		.drv_close			= demo_drv_close,
		.drv_ioctl			= demo_drv_ioctl,
		.destroy			= destroy_demo_drv,
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
ia_result init_s3_demo_vd()
{
	ia_result ret = IA_SUCCESS;

	/*here implement your own module init code*/
	
	ret = register_vd_drv(&demo_drv);
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
static ia_word16 demo_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;


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
static ia_result demo_get_resources(void **ppvList, ia_word16 *pwCount)
{
	ia_result ret = IA_SUCCESS;


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
static vd_ref_id demo_drv_open(vd_rsc_id wResourceID, void *pvData)
{
	ia_result ret = IA_SUCCESS;


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
static ia_result demo_drv_close(vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;


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
static ia_result demo_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead )
{
	ia_result ret = IA_SUCCESS;


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
static ia_result destroy_demo_drv(void *priv_dat)
{
	ia_result ret = IA_SUCCESS;


	return ret;

}






