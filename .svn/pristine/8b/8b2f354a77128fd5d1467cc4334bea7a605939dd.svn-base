
/******************************************************************************
 *                    COPYRIGHT (C) 2011 IRDETO B.V.                          *
 ******************************************************************************
 * FILENAME   : Utilizatioin.c                                                *
 *                                                                            *
 ******************************************************************************/
#include <sys_config.h>
#include "../Shared/LoaderCorePrivate.h"
#include "Utilization.h"



/* Loader Pt information */
static lc_loader_pt_st gstLdrPt;

/* BBCB infomation */
static lc_bbcb_st gstBBCB;

/* Variant & Sub-variant stored in variant module. */
static lc_uint16 gVariant;
static lc_uint16 gSubVariant;


lc_result LC_InitializePSVariable(void)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    int info_type =0;
    int info_size=0;
    lc_uint16 var_array[2] ={0};
    
    /* for IA support code retrieve the STB specific bbcb data */
    if( LC_SUCCESS == result )
    {
        result = BBCB_GetBBCB(&gstBBCB, LC_NULL);
        if( LC_SUCCESS != result)
        {
            TRACE_LOG0(TRACE_ERROR, ("[BLOADER] Error retrieving BBCB!\n"));
            errCode = ERROR_CODE_INVALID_BBCB;
        }
    }

    info_type = UI_INFO_TYPE_BBCB_INFO;
    info_size = sizeof(gstBBCB);
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&gstBBCB));


    /*Read reset type and download type from driver first.*/
   
    /* In Loader V5, Loader pt should exist before real download procedure. */
    if( LC_SUCCESS == result )
    {
        result = LC_ReadLoaderPartition(&gstLdrPt);      
        if (LC_SUCCESS != result)
        {
            errCode = ERROR_CODE_INVALID_LOADERPT;
        }
    }

    /* Initialize variables for variant & sub-variant. */
    if (LC_SUCCESS == result)
    {
        gVariant = 0xFFFF;
        gSubVariant = 0xFFFF;
        /* Attempt to get variant & sub-variant. */
        LC_GetVariant(&gVariant, &gSubVariant);       
    }

    var_array[0]=gVariant;
    var_array[1]=gSubVariant;
    info_type = UI_INFO_TYPE_VAR;
    info_size = sizeof(lc_uint16)*2;
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(var_array));

    ERR_REPORT_SetErrorCode(errCode);

    return result;
}

lc_result LC_FinalizePSVariable(void)
{
    lc_result result = LC_SUCCESS;
    
    return result;
}



lc_bool LC_UtilGetDownloadFlag(void)
{
    return LC_GetDownloadFlag(&gstLdrPt.sharedMemory);
}

lc_result LC_UtilSetDownloadFlag(lc_bool enable)
{
    return LC_SetDownloadFlag(enable, &gstLdrPt.sharedMemory);
}

lc_uchar LC_UtilGetDownloadType(void)
{
    return LC_GetDownloadType(&gstLdrPt.sharedMemory);
}

lc_result LC_UtilSetDownloadType(lc_uchar dlType)
{
    return LC_SetDownloadType(dlType,&gstLdrPt.sharedMemory);
}

lc_result LC_UtilGetDvbssuDownloadParameters(
    lc_dvbssu_dl_info_st *pDvbSsuParameters, 
    lc_uchar privateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH])
{
    LC_memcpy(pDvbSsuParameters, &gstLdrPt.sharedMemory.otaDownloadPara.dvbssuInfo, sizeof(lc_dvbssu_dl_info_st));
    LC_memcpy(privateInfo, gstLdrPt.sharedMemory.otaDownloadPara.privateInfo, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
    
    return LC_SUCCESS;
}

void LC_UtilResetMigrationVariant(void)
{
    gstLdrPt.sharedMemory.migrationInfo.variant = 0xFFFF;
    gstLdrPt.sharedMemory.migrationInfo.subvariant = 0xFFFF;
}

lc_bool LC_UtilCheckMigrationMode(void)
{
    lc_result result = LC_SUCCESS;
    lc_bool isMigration = LC_FALSE;
    lc_migration_info_st migrationMsg;

    LC_memcpy(
        &migrationMsg, 
        &gstLdrPt.sharedMemory.migrationInfo, 
        sizeof(lc_migration_info_st));

    /* Check validity of the new variant and sub-variant. */
    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_IsVariantValid(
                        &migrationMsg.variant, 
                        &migrationMsg.subvariant))
        {
            result = LC_FAILURE;
        }
    }
    
    /**
     * Should have different value with the existing ones, 
     * but not required to check the validity of the existing ones as they are to be overwritten. 
     */
    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_CheckVariant(LC_FALSE, migrationMsg.variant, gVariant))
        {
            result = LC_ERROR_INVALID_VARIANT_VALUE;
        }
    }

    if (LC_SUCCESS == result)
    {
        /**
         * If the incoming sub-variant equals ZERO, that means this download can be applied to 
         * every client device regardless of its sub-variant. In this case there is 
         * no need to compare it with the exisiting one. 
         */
        if (LC_TRUE != LC_CheckVariant(LC_TRUE, migrationMsg.subvariant, gSubVariant))
        {
            result = LC_ERROR_INVALID_SUBVARIANT_VALUE;
        }
    }

    if (LC_ERROR_INVALID_VARIANT_VALUE == result ||
        LC_ERROR_INVALID_SUBVARIANT_VALUE == result)
    {
        isMigration = LC_TRUE;
    }

    return isMigration;
}


lc_result LC_UtilFlushLoaderPartition(void)
{
    return LC_WriteSharedMemory(LC_FALSE, &gstLdrPt.sharedMemory);
}


lc_result LC_UtilCheckOUI(lc_uchar oui[3])
{
    return (0 == LC_memcmp(oui, gstBBCB.OUI, 3))? LC_SUCCESS : LC_FAILURE;
}

lc_result LC_UtilCheckManufacturerId(lc_uint16 manufacturerId)  //#201803
{

	lc_result result = LC_SUCCESS;

    if( manufacturerId != gstBBCB.manufacturer_id &&
        gstBBCB.manufacturer_id != 0xFFFF)
    {
        result = LC_FAILURE;
    }

    return result;
}

lc_result LC_UtilCheckHardwareVersion(lc_uint16 hardwareVersion) //#201803
{
	lc_result result = LC_SUCCESS;

    if( hardwareVersion != gstBBCB.hardware_version &&
            gstBBCB.hardware_version != 0xFFFF)
    {
        result = LC_FAILURE;
    }

    return result;
	return LC_SUCCESS;
}

lc_uchar LC_UtilGetBootcheckAlgorithm(void)
{
    return gstBBCB.boot_check_algorithm;
}

lc_bool LC_UtilIsStringPrintable(const lc_char *pString, lc_uint32 size)
{
    lc_bool result = LC_TRUE;
    lc_uint32 cnt = 0;
    const lc_char *pStr = pString;
    
    for (cnt = 0; cnt < size; cnt ++)
    {
        if( (pStr[cnt] < 0x20) || (pStr[cnt] > 0x7E) )
        {
            result = LC_FALSE;
            break;
        }
    }
    
    return result;
}

lc_result LC_UtilGetDownloadSequence(lc_uint16 *pDownloadSequenceNumber)
{
    lc_result result = LC_SUCCESS;

    /* Get current download_sequence_number. */
    *pDownloadSequenceNumber = gstLdrPt.downloadInfo.download_sequence_number;;

    return result;
}


lc_result LC_UtilCheckVariant(lc_bool migration, const lc_uint16 *pVariant, const lc_uint16 *pSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint16 variant = 0;
    lc_uint16 subVariant = 0;

    /* Check value. */
    if (LC_TRUE != LC_IsVariantValid(pVariant, pSubVariant))
    {
        result = LC_FAILURE;
    }

    /* Compare it with the existing one. */
    if (LC_SUCCESS == result)
    {
        if (LC_TRUE == migration)
        {
            variant = gstLdrPt.sharedMemory.migrationInfo.variant;
            subVariant = gstLdrPt.sharedMemory.migrationInfo.subvariant;
        }
        else
        {
            variant = gVariant;
            subVariant = gSubVariant;
        }
        
        if (LC_TRUE != LC_IsVariantValid(&variant, &subVariant))
        {
            result = LC_ERROR_INVALID_VARIANT_VALUE;
            errCode = ERROR_CODE_RESIDENT_VARIANT_INVALID;
        }
    }

    if(LC_SUCCESS == result)
    {
        if (LC_NULL != pVariant)
        {
            if (LC_TRUE != LC_CheckVariant(LC_FALSE, *pVariant, variant))
            {
                result = LC_ERROR_INVALID_VARIANT_VALUE;
            }
        }
    }

    if(LC_SUCCESS == result)
    {
        if (LC_NULL != pSubVariant)
        {
            if (LC_TRUE != LC_CheckVariant(LC_TRUE, *pSubVariant, subVariant))
            {
                result = LC_ERROR_INVALID_SUBVARIANT_VALUE;
            }
        }
    }

    /* Report Errorcode */
    ERR_REPORT_SetErrorCode(errCode);

    return result;
}

lc_result LC_UtilMigrationUpdateVariant(void)
{
    return LC_SetVariant(
                LC_FALSE,
                &gstLdrPt.sharedMemory.migrationInfo.variant,
                &gstLdrPt.sharedMemory.migrationInfo.subvariant);
}

lc_result LC_UtilCheckModuleId(lc_uchar downloadType, lc_uint32 moduleId)
{
    lc_result result = LC_SUCCESS;
    
    /* BBCB is read-only, so it is strictly prohibited to be updated. */ 
    if ( MODULE_DRV_ID_BBCB == moduleId )
    {
        result = LC_ERROR_MODULE_UPDATE_DISALLOWED;
    }

    /* It it not allowed to update Loader Partition and Loadercore. */
    if (LC_SUCCESS == result)
    {
        if (MODULE_DRV_ID_LOADER_CORE == moduleId || 
            MODULE_DRV_ID_LOADER_PT == moduleId )
        {
            result = LC_ERROR_MODULE_UPDATE_DISALLOWED;
        }
    }

    if (LC_SUCCESS == result)
    {
        /* UK and variant ONLY can be updated via serial download */
        if(SERIAL_DOWNLOAD != downloadType)
        {
            if(MODULE_DRV_ID_UK == moduleId ||
                MODULE_DRV_ID_VARIANT == moduleId )
            {
                result = LC_ERROR_MODULE_UPDATE_DISALLOWED;
            }
        }

    }

    return result;
}


lc_result LC_UtilCheckHashMode(lc_bool rsaOn, lc_uchar signatureByte[SIGNATURE_LENGTH], pkcs_hash_mode *pPkcsHashMode)
	
{
    lc_result result = LC_SUCCESS;

    *pPkcsHashMode = PKCS_SHA256_MODE;
  
    return result;
}



