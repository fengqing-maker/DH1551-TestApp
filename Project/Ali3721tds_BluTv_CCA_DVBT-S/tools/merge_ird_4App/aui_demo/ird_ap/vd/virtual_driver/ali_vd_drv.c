/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\softcell\buildroot\output\build\ird_vd-1.0.0-20160728\virtual_driver\ali_vd_res.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/28/2016 14:58:29
 *  @revision           none
 *
 *  @author              <>
 */

#include <s3_osdrv.h>
#include "ali_vd_drv.h"

struct vd_drv *  vd_drv_arr[MAX_NR_OF_VD_TYPE + 1];
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_result init_all_vd_drv()
{
	int i,j;
	ia_result ret = IA_SUCCESS;
	
	for(i = 1; i < MAX_NR_OF_VD_TYPE + 1; i++)
	{
		vd_drv_arr[i] = NULL;
	}
	// ret = init_s3_copycontrol();
	ret = init_s3_vddd();
	ret = init_s3_vddf();
	// ret = init_s3_vd_dvb_oob();
	ret = init_s3_vd_external_storage();
	// ret = init_s3_vdhgb();
	ret = init_s3_vd_loader();
	// ret = init_s3_vd_macrovision();
	// ret = init_s3_vdpd();
	ret = init_s3_vdps();
	ret = init_s3_vd_smc();
	// ret = init_s3_vd_stream_crypto();
	ret = init_s3_vdtmr();
	for(i = 1; i < MAX_NR_OF_VD_TYPE + 1; i++)
	{
	//	DEBUG_S3_VD_PRINTF("type %d dsc is 0x%x \n",i, vd_drv_arr[i]);
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_result  register_vd_drv(struct vd_drv *pdrv)
{
	ia_result ret = IA_SUCCESS;
	vd_driver_type_e drv_typ;
	struct vd_drv *tmp_drv = NULL;
	
	if(NULL == pdrv)
	{
		ret = IA_INVALID_PARAMETER;
		return ret;
	}
	drv_typ = pdrv->drv_typ;
	tmp_drv = vd_drv_arr[drv_typ];
	if(NULL == tmp_drv)
	{
		vd_drv_arr[drv_typ] = pdrv;
		ret = IA_SUCCESS;
	}
	else
	{
		DEBUG_S3_VD_PRINTF("driver type: %d have already registered \n", drv_typ);
		ret = IA_INVALID_PARAMETER;
	}
	return ret;
}
