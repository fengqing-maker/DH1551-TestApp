

#include "LoaderCoreAPI_ApplicationHelper.h"
#include "LoaderCorePrivate.h"


lc_result LoaderCoreAPI_InitApplicationModule(void)
{
    lc_result result = LC_SUCCESS;

    /*Create CRC tables that will be referenced later.*/
#ifdef USE_DYNAMIC_LOOKUP_TABLES
    CRC_CreateTables();
#endif

    return result;
}


lc_result LoaderCoreAPI_WriteBBCB(lc_bool updateCRC, const lc_bbcb_parameters *pBBCBParameters)
{
    lc_result result = LC_SUCCESS;
    lc_bbcb_st bbcb;


    if (LC_NULL == pBBCBParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if( LC_SUCCESS == result)
    {
        LC_memcpy(bbcb.OUI, pBBCBParameters->OUI, sizeof(bbcb.OUI));
        bbcb.manufacturer_id = pBBCBParameters->manufacturer_id;
        bbcb.hardware_version = pBBCBParameters->hardware_version;
        bbcb.loader_major_version = pBBCBParameters->loader_major_version;
        bbcb.loader_minor_version = pBBCBParameters->loader_minor_version;
        bbcb.loader_version_buildnumber = pBBCBParameters->loader_version_buildnumber;
        bbcb.boot_check_algorithm = pBBCBParameters->boot_check_algorithm;
        LC_memcpy(bbcb.serial_number, pBBCBParameters->serial_number, sizeof(bbcb.serial_number));
        LC_memcpy(bbcb.random_number, pBBCBParameters->random_number, sizeof(bbcb.random_number));
        bbcb.crc32 = pBBCBParameters->crc32;
        
        result = BBCB_SetBBCB(updateCRC, &bbcb);
    }

    return result;
}

lc_result LoaderCoreAPI_ReadBBCB(lc_bbcb_parameters *pBBCBParameters, lc_bool *pUpdateCRC)
{
    lc_result result = LC_SUCCESS;
    lc_bbcb_st bbcb;

    if (LC_NULL == pBBCBParameters
        || LC_NULL == pUpdateCRC)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if( LC_SUCCESS == result)
    {        
        result = BBCB_GetBBCB(&bbcb, pUpdateCRC);
    }

    if( LC_SUCCESS == result)
    {
        LC_memcpy(pBBCBParameters->OUI, bbcb.OUI, sizeof(bbcb.OUI));
        pBBCBParameters->manufacturer_id = bbcb.manufacturer_id;
        pBBCBParameters->hardware_version = bbcb.hardware_version;
        pBBCBParameters->loader_major_version = bbcb.loader_major_version;
        pBBCBParameters->loader_minor_version = bbcb.loader_minor_version;
        pBBCBParameters->loader_version_buildnumber = bbcb.loader_version_buildnumber;
        pBBCBParameters->boot_check_algorithm = bbcb.boot_check_algorithm;
        LC_memcpy(pBBCBParameters->serial_number, bbcb.serial_number, sizeof(bbcb.serial_number));
        LC_memcpy(pBBCBParameters->random_number, bbcb.random_number, sizeof(bbcb.random_number));
        pBBCBParameters->crc32 = bbcb.crc32;
    }


    return result;

}

lc_result LoaderCoreAPI_WriteDVBSSUParameters( 
    const lc_dvb_ssu_parameters *pDvbssuParameters, 
    const lc_buffer_st *pPrivateData)

{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;

    if (LC_NULL == pDvbssuParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        result = LC_CheckType_Bytes(pPrivateData);
    }

    if (LC_SUCCESS == result)
    {
        if (pDvbssuParameters->pid > 0x1FFF || 
            pPrivateData->length > LC_MANUFACTURER_PRIVATE_INFO_LENGTH)
        {
            result = LC_ERROR_INVALID_PARAMETER;
        }
    }

    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }

    /* Write DVB-SSU parameters into Loader Pt */
    if (LC_SUCCESS == result)
    {
        result = LC_ReadSharedMemory(pShardMem);
        if( LC_SUCCESS == result)
        {
        
            pShardMem->otaDownloadPara.dvbssuInfo.pid = pDvbssuParameters->pid;
            LC_memcpy(pShardMem->otaDownloadPara.privateInfo, pPrivateData->bytes, pPrivateData->length);
            
            result = LC_WriteSharedMemory(LC_FALSE, pShardMem);
        }
        
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}


lc_result LoaderCoreAPI_ReadDVBSSUParameters( lc_dvb_ssu_parameters *pDvbssuParameters)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;

    if (LC_NULL == pDvbssuParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }

    /* read IP parameters from NVRAM Loader Pt */
    if (LC_SUCCESS == result)
    {         
        result = LC_ReadSharedMemory(pShardMem);
    }

    if (LC_SUCCESS == result)
    {         
        pDvbssuParameters->pid = pShardMem->otaDownloadPara.dvbssuInfo.pid;
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}


lc_result LoaderCoreAPI_WriteMigrationVariant(lc_uint16 migrationVariant)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;


    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_IsVariantValid(&migrationVariant, LC_NULL))
        {
            result = LC_FAILURE;
        }
    }

    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }

    if (LC_SUCCESS == result)
    {
        result = LC_ReadSharedMemory(pShardMem);
        if( LC_SUCCESS == result)
        {  
            pShardMem->migrationInfo.variant = migrationVariant;
            
            result = LC_WriteSharedMemory(LC_FALSE, pShardMem);
        }
        
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}



lc_result LoaderCoreAPI_ReadMigrationVariant( lc_uint16 *pMigrationVariant, lc_uint16 *pMigrationSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;

    if (LC_NULL == pMigrationVariant)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }

    if (LC_SUCCESS == result)
    {         
        result = LC_ReadSharedMemory(pShardMem);
    }

    if (LC_SUCCESS == result)
    {         
        *pMigrationVariant = pShardMem->migrationInfo.variant;
        *pMigrationSubVariant = pShardMem->migrationInfo.subvariant;
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}


lc_result LoaderCoreAPI_WriteMigrationSubVariant(lc_uint16 migrationSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;


    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_IsVariantValid(LC_NULL, &migrationSubVariant))
        {
            result = LC_FAILURE;
        }
    }

    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }
    
    if (LC_SUCCESS == result)
    {
        result = LC_ReadSharedMemory(pShardMem);
        if( LC_SUCCESS == result)
        {   
            pShardMem->migrationInfo.subvariant = migrationSubVariant;
            
            result = LC_WriteSharedMemory(LC_FALSE, pShardMem);
        }
        
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}



lc_result LoaderCoreAPI_ReadMigrationSubVariant( lc_uint16 *pMigrationSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;

    if (LC_NULL == pMigrationSubVariant)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }

    if (LC_SUCCESS == result)
    {         
        result = LC_ReadSharedMemory(pShardMem);
    }

    if (LC_SUCCESS == result)
    {         
        *pMigrationSubVariant = pShardMem->migrationInfo.subvariant;
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}

lc_result LoaderCoreAPI_SetDownloadFlag( lc_bool enableDl, lc_download_type dlType)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st *pShardMem = LC_NULL;

    if (OTA_DOWNLOAD != dlType)
    {
        result = LC_ERROR_INVALID_PARAMETER;
    }
	
    if (LC_SUCCESS == result)
    {
        pShardMem = LC_MALLOC(sizeof(lc_shared_memory_st));
    }

    if (LC_SUCCESS == result)
    {
        result = LC_ReadSharedMemory(pShardMem);
        if( LC_SUCCESS == result)
        {
            result = LC_SetDownloadIndicator(enableDl, dlType, pShardMem);

            if( LC_SUCCESS == result )
            {
                result = LC_WriteSharedMemory(LC_FALSE, pShardMem);
            }
        }        
    }

    LC_Free_Memory((void **)&pShardMem);

    return result;
}


lc_result LoaderCoreAPI_GetUKInfo(lc_uint16* pSystemId, lc_uint16* pKeyVersion, lc_uint16* pSignatureVersion)
{
    lc_result result = LC_SUCCESS;
    lc_key_update_message *pKeyUpdateMsg = LC_NULL;

    if (LC_NULL == pSystemId || LC_NULL == pKeyVersion || LC_NULL == pSignatureVersion)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        pKeyUpdateMsg = LC_MALLOC(sizeof(lc_key_update_message));
    }

    if (LC_SUCCESS == result)
    {
        result = LC_GetClearKeyData(pKeyUpdateMsg);
    }

    if (LC_SUCCESS == result)   /* UK module is authenticated. */
    {        
        /* Get system ID and  key version from abClearControl */
		*pSystemId = ((pKeyUpdateMsg->loaderRealInfoControl[0] << 8) | pKeyUpdateMsg->loaderRealInfoControl[1]);
        *pKeyVersion = ((pKeyUpdateMsg->loaderRealInfoControl[2] << 8) | pKeyUpdateMsg->loaderRealInfoControl[3]);
        *pSignatureVersion = 0;
    }

    LC_Free_Memory((void **)&pKeyUpdateMsg);

    return result;
}

lc_result LoaderCoreAPI_GetDownloadSequenceNumber(lc_uint16 *pDownloadSequenceNumber)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 dsn = 0;
    
    result = LC_GetDownloadSequence(&dsn);
    if (LC_SUCCESS == result)
    {
        *pDownloadSequenceNumber = dsn;
    }
    
    return result;
}

lc_result LoaderCoreAPI_GetVariant(lc_uint16 *pVariant, lc_uint16 *pSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 variant = 0;
    lc_uint16 subVariant = 0;
    
    result = LC_GetVariant(&variant, &subVariant);
    if (LC_SUCCESS == result)
    {
        *pVariant = variant;
        *pSubVariant = subVariant;
    }
    
    return result;
}

lc_result LoaderCoreAPI_GetISignInfo(lc_char iSignVersion[4], lc_char iSignSN[4])
{
    lc_result result = LC_SUCCESS;
    lc_last_download_info_st dlInfo;
    
    /* Load the first part of the download info */
    if (LC_SUCCESS == result)
    {
        result = LC_GetDownloadInformation(&dlInfo);
    }

    /* Read ISIGN information from download_header */
    if (LC_SUCCESS == result)
    {
        LC_memcpy(iSignVersion, dlInfo.isign_version, 4);
        LC_memcpy(iSignSN, dlInfo.isign_serial_number, 4);
    }
    
    return result;
}



