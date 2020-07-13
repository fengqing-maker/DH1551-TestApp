/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\softcell\buildroot\output\build\ird_vd-undefined\virtual_driver\ali_vd_drv.h
 *  @brief              
 *
 *  @version            1.0
 *  @date               8/16/2016 15:40:01
 *  @revision           none
 *
 *  @author              <>
 */




#ifndef _ALI_VD_DRV_H
#define _ALI_VD_DRV_H

#include "s3_portable_types.h"
#include "s3_status.h"
#include <stdlib.h>
//#include <stdio.h>
#include <api/libfs2/stdio.h>
#include <s3_vd.h>

#define DEBUG_S3_VD 

#ifdef  DEBUG_S3_VD
#define DEBUG_S3_VD_PRINTF  libc_printf
#else
#define DEBUG_S3_VD_PRINTF(...)  do{} while(0)
#endif /* DEBUG_S3_VD*/

typedef struct vd_drv{
	vd_driver_type_e drv_typ;
	void *priv;
	
	ia_word16 (*get_drv_version)();
	ia_result (*get_resources)(void **ppvList, ia_word16 *pwCount);
	vd_ref_id (*drv_open)(vd_rsc_id wResourceID, void *pvData);
	ia_result (*drv_close)(vd_ref_id wRefId);
	ia_result (*drv_ioctl)(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
							void *pvDataWrite, ia_word32 *pwDataReadSize, 
							void *pvDataRead );
	ia_result (*destroy)(void *priv_dat);
} vd_drv;

#define MAX_NR_OF_VD_TYPE  22
extern struct vd_drv *  vd_drv_arr[];

extern ia_result init_all_vd_drv();

extern ia_result  register_vd_drv(struct vd_drv *pdrv);

/*here is all vd module's init function*/

// extern ia_result init_s3_copycontrol();
extern ia_result init_s3_vddd();
extern ia_result init_s3_vddf();
// extern ia_result init_s3_vd_dvb_oob();
extern ia_result init_s3_vd_external_storage();
// extern ia_result init_s3_vdhgb();
extern ia_result init_s3_vd_loader();
// extern ia_result init_s3_vd_macrovision();
// extern ia_result init_s3_vdpd();
extern ia_result init_s3_vdps();
extern ia_result init_s3_vd_smc();
// extern ia_result init_s3_vd_stream_crypto();
extern ia_result init_s3_vdtmr();
// extern ia_result init_s3_demo_vd();
#endif  /* _ALI_VD_DRV_H */

