/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vd_loader.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:08:12
 *  @revision           none
 *
 *  @author              <>
 */

/**
 * This file is part of the 'loader virtual driver'.
 **/



#include <s3_vd_loader.h>
#include <s3_vd.h>
#include <s3_osdrv.h>
#include "ali_vd_drv.h"
#include <aui_common.h>
#include <LoaderCoreAPI_ApplicationHelper.h>
#include <LoaderCoreSPI_DEMUX.h>
#include <Bit.h>


#define LOADER_V1 1
#define LOADER_V2 2
#define LOADER_V3 3
#define LOADER_V4 4
#define LOADER_V5 5
#define LOADER_V6 6

extern lc_result LC_InitializePSVariable(void);
extern lc_result LC_UtilGetIpDownloadParameters(lc_ip_dl_info_st *pIpParameters, lc_uchar privateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH]);

ia_result init_s3_loader_vd();


static ia_word16 loader_get_drv_version();

static ia_result loader_get_resources(void **ppvList, ia_word16 *pwCount);

static vd_ref_id loader_drv_open(vd_rsc_id wResourceID, void *pvData);

static ia_result loader_drv_close(vd_ref_id wRefId);

static ia_result loader_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead );
			
static ia_result destroy_loader_drv(void *priv_dat);

static struct vd_drv loader_drv = {
		.drv_typ 			= VD_DRIVER_LOADER,
		.priv				= NULL,
		.get_drv_version 	= loader_get_drv_version,
		.get_resources		= loader_get_resources,
		.drv_open			= loader_drv_open,
		.drv_close			= loader_drv_close,
		.drv_ioctl			= loader_drv_ioctl,
		.destroy			= destroy_loader_drv,
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
ia_result init_s3_vd_loader()
{
	ia_result ret = IA_SUCCESS;

	/*here implement your own module init code*/
	
	ret = register_vd_drv(&loader_drv);
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
static ia_word16 loader_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = LOADER_V6;
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
static ia_result loader_get_resources(void **ppvList, ia_word16 *pwCount)
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
static vd_ref_id loader_drv_open(vd_rsc_id wResourceID, void *pvData)
{
	vd_ref_id ref_id = 0;
	lc_result ld_ret = LC_FAILURE;

	ld_ret = LoaderCoreAPI_InitApplicationModule();
	if(LC_FAILURE == ld_ret)
	{
		DEBUG_S3_VD_PRINTF("fail in LoaderCoreAPI_InitApplicationModule()\n");
		ref_id = VD_REF_ID_ERROR ;
		return ref_id;
	}
	ref_id = 0;
	return ref_id;
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
static ia_result loader_drv_close(vd_ref_id wRefId)
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

#define OTP_CSSN_ADDR			0x00
/************************************/
#define CRYPTO_TDES_ENABLE		0x01
#define CRYPTO_TDES_DISABLE		0x00
/************************************/
#define RSA_BOOT_SECURE_BOOT_ENABLE 		0x00000001
#define RSA_BOOT_BACKGROUND_CHECK 			0x00000002
#define RSA_BOOT_CLEAR_CONTENT_PROTECT		0x00000000

#define RSA_BOOT_MODEL		(RSA_BOOT_SECURE_BOOT_ENABLE | RSA_BOOT_BACKGROUND_CHECK | RSA_BOOT_CLEAR_CONTENT_PROTECT)
/************************************/
#define OTP_JTAG_ADDR		0xDD

#define OTP_EJTAG_MASK				0x0000000C
#define OTP_EJTAG_DISABLE 			0x00000004
#define OTP_EJTAG_PASSWD_MODEL  	0x00000008
#define OTP_EJTAG_OPEN  			0x00000000
 /************************************/
#define CW_MODEL_ENFORCE 			0x00000001
#define CW_PVR_ENFORCE 				0x00000002
#define CW_MODEL_CONFIG_VAL  		(CW_MODEL_ENFORCE | CW_PVR_ENFORCE)
static ia_result loader_drv_ioctl(vd_ref_id wRefId, ia_word16 wOpCode, ia_word32 wDataWriteSize, 
									void *pvDataWrite, ia_word32 *pwDataReadSize, 
									void *pvDataRead )
{
	ia_result ret = IA_SUCCESS;
	lc_result lc_ret = LC_SUCCESS;

	switch(wOpCode)
	{
		case VD_LOADER_GET_SYSTEM_ID:
		{
			lc_uint16 pSystemId;
			lc_uint16 pKeyVersion;
			lc_uint16 pSignatureVersion;
			vd_loader_system_id_st *pout = pvDataRead;
			lc_ret = LoaderCoreAPI_GetUKInfo(&pSystemId, &pKeyVersion, &pSignatureVersion);
			pout->wSystemId = pSystemId;
			*pwDataReadSize = sizeof(vd_loader_system_id_st);
			ret = IA_SUCCESS;
			break;
		}
	
		case VD_LOADER_GET_KEY_VERSION:
		{
			lc_uint16 pSystemId;
			lc_uint16 pKeyVersion;
			lc_uint16 pSignatureVersion;
			vd_loader_key_version_st *pout = pvDataRead;
			lc_ret = LoaderCoreAPI_GetUKInfo(&pSystemId, &pKeyVersion, &pSignatureVersion);
			pout->wKeyVersion = pKeyVersion;
			*pwDataReadSize = sizeof(vd_loader_key_version_st);
			ret = IA_SUCCESS;
			
			break;
		}
		case VD_LOADER_GET_SIGNATURE_VERSION:
		{
			lc_uint16 pSystemId;
			lc_uint16 pKeyVersion;
			lc_uint16 pSignatureVersion;
			vd_loader_signature_version_st *pout = pvDataRead;
	
			lc_ret = LoaderCoreAPI_GetUKInfo(&pSystemId, &pKeyVersion, &pSignatureVersion);
			pout->wSignatureVersion = pSignatureVersion;
			*pwDataReadSize = sizeof(vd_loader_signature_version_st);
			ret = IA_SUCCESS;
			break;
		}
		case VD_LOADER_GET_VARIANT:
		{
			lc_uint16 pVariant;
			lc_uint16 pSubVariant;
			vd_loader_variant_st *pout = pvDataRead;
			lc_ret = LoaderCoreAPI_GetVariant(&pVariant, &pSubVariant);
			pout->wVariant= pVariant;
			*pwDataReadSize = sizeof(vd_loader_variant_st);
			ret = IA_SUCCESS;
			break;
		}
		case VD_LOADER_GET_MANUFACTURER_ID:
		{
			lc_bbcb_parameters pBBCBParameters;
			lc_bool pUpdateCRC;
			lc_ret = LoaderCoreAPI_ReadBBCB(&pBBCBParameters, &pUpdateCRC);
			vd_loader_manufacturer_id_st *pout = pvDataRead;
			pout->wManufacturerId = pBBCBParameters.manufacturer_id;
			*pwDataReadSize = sizeof(vd_loader_manufacturer_id_st);
			ret = IA_SUCCESS;
			break;
		}
		case VD_LOADER_GET_HARDWARE_VERSION:
		{
			lc_bbcb_parameters pBBCBParameters;
			lc_bool pUpdateCRC;
			lc_ret = LoaderCoreAPI_ReadBBCB(&pBBCBParameters, &pUpdateCRC);
			vd_loader_hardware_version_st *pout = pvDataRead;
			pout->wHardwareVersion = pBBCBParameters.hardware_version;
			*pwDataReadSize = sizeof(vd_loader_hardware_version_st);
			ret = IA_SUCCESS;
			break;
		}
		case VD_LOADER_GET_LOAD_VERSION:
		{
			lc_uint16 DownloadSequenceNumber;
			vd_loader_load_version_st *pout = pvDataRead;
			lc_ret = LoaderCoreAPI_GetDownloadSequenceNumber(&DownloadSequenceNumber);
			pout->wLoadVersion = DownloadSequenceNumber;
			*pwDataReadSize = sizeof(vd_loader_load_version_st);
			ret = IA_SUCCESS;
			break;
		}
		case VD_LOADER_GET_SECURE_CHIP_CSSN:
		{	
			unsigned long val = 0;
			unsigned long len = 4;
			vd_loader_secure_chip_st *pout = pvDataRead;
			AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;

			len = 4;
			aui_rtn = aui_otp_read(OTP_CSSN_ADDR, (unsigned char *)(&val), len);
			if(AUI_RTN_SUCCESS != aui_rtn)
			{
				ret = IA_FAIL;
				break;
			}
			pout->wCSSN = val;
			pout->bCrypto = CRYPTO_TDES_ENABLE;
			pout->wRsaBoot = RSA_BOOT_MODEL;
			aui_rtn = aui_otp_read(OTP_JTAG_ADDR, (unsigned char *)(&val), len);
			if(AUI_RTN_SUCCESS != aui_rtn)
			{
				ret = IA_FAIL;
				break;
			}
			val &= OTP_EJTAG_MASK;
			if(OTP_EJTAG_DISABLE == val)
			{
				pout->wJtag = 0x00000002;
			}
			else if(OTP_EJTAG_PASSWD_MODEL == val)
			{
				pout->wJtag = 0x00000001;
			}
			else if(OTP_EJTAG_OPEN == val)
			{
				pout->wJtag = 0x00000000;
			}
			else
			{
				ret = IA_FAIL;
				break;
			}
			pout->wCwMode = CW_MODEL_CONFIG_VAL;
			*pwDataReadSize = sizeof(vd_loader_secure_chip_st);
			ret = IA_SUCCESS;
			break;
		}
		case VD_LOADER_GET_LOADER_VERSION:
		{
		/* Fixed SCR#152574: [3.14]SoftCell3 need to support Enforce Firmware Upgrade */
			lc_bbcb_parameters pBBCBParameters;
			lc_bool pUpdateCRC;
			lc_ret = LoaderCoreAPI_ReadBBCB(&pBBCBParameters, &pUpdateCRC);
			vd_loader_loader_version_st *pout = pvDataRead;
			pout->bMajor= pBBCBParameters.loader_major_version;
			pout->bMinor = pBBCBParameters.loader_minor_version;
			*pwDataReadSize = sizeof(vd_loader_loader_version_st);
			ret = IA_SUCCESS;
			break;
		}
	/*SCR#192479: [Global Pairing]SoftCell3 shall read private data before synchronizing with smart card.*/
		case VD_LOADER_GET_PRIVATE_DATA:
		{
			lc_result lc_ret;
			lc_dvbssu_dl_info_st DvbSsuParameters;

			lc_ret = LC_InitializePSVariable();
			lc_ret = LC_UtilGetDvbssuDownloadParameters(DvbSsuParameters, (lc_uchar *) (pvDataRead));
			*pwDataReadSize = LC_MANUFACTURER_PRIVATE_INFO_LENGTH ;
			ret = IA_SUCCESS;
			break;
		}
	/*Support CCA private data feature*/	
		case VD_LOADER_GET_EXTERNAL_PRIVATE_DATA:
		{
			ret = IA_INVALID_PARAMETER;
			break;
		}
	/*To support CCC for TSC1.1*/
		case VD_LOADER_GET_CHIP_CONFIGURATION_CHECK_MAC:
		{
			ret = IA_INVALID_PARAMETER;
			break;
		}
	/*SCR#389959: [STB Firmware Enforcement] Softcell shall calculate encrypted STB attributes (S').*/
		case VD_LOADER_GET_IMAGE_VERSION:
		{
			ret = IA_INVALID_PARAMETER;
			break;
		}
			
		default:
		{
			ret = IA_INVALID_PARAMETER;
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
 *  @date               8/14/2016, Created
 *
 *  @note
 */
static ia_result destroy_loader_drv(void *priv_dat)
{
	ia_result ret = IA_SUCCESS;


	return ret;

}



