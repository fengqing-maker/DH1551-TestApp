/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : LoaderPartition.c                                          *
*                                                                            *
*   Description : This module supplies the functions required by             *
*                Loader Core to access the host Loader Partition.            *
*                                                                            *
*****************************************************************************/
#include <sys_config.h>
#include "LoaderCorePrivate.h"


static lc_result LC_ResetLoaderPartition(lc_loader_pt_st *pLoaderPt)
{
    /**
     * Loader pt is mandatory, thus must be created. 
     * with 
     *      enable download flag = FALSE, 
     *      download type = UART download,
     *      migration = disabled
     *      download sequence number = 0xFFFF
     * by default.
     */
     
    LC_memset(pLoaderPt, 0, sizeof(lc_loader_pt_st));

    /* Migration. */
    pLoaderPt->sharedMemory.migrationInfo.variant = 0xFFFF;
    pLoaderPt->sharedMemory.migrationInfo.subvariant = 0xFFFF;

    /* Download sequence number. */
    pLoaderPt->downloadInfo.download_sequence_number = 0xFFFF;

    return LC_SUCCESS;
}

lc_result LC_CreateLoaderPartition(void)
{
    lc_result result = LC_SUCCESS;
    lc_loader_pt_st loaderPt;

    result = LC_ResetLoaderPartition(&loaderPt);

    if (LC_SUCCESS == result)
    {
        result = LC_WriteSharedMemory(LC_TRUE, &loaderPt.sharedMemory);
    }

    if (LC_SUCCESS == result)
    {
        result = LC_StoreDownloadInformation(&loaderPt.downloadInfo);
    }

    return result;
}

lc_result LC_ReadLoaderPartition(lc_loader_pt_st *pLoaderPt)
{
	lc_result result = LC_SUCCESS;
    lc_buffer_st mp_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte_clear = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_uint32 crc32 = 0;

    if (LC_NULL == pLoaderPt)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_LOADER_PT, &mp_byte);
    }

    if (LC_SUCCESS == result)
    {
        mp_byte_clear.length = mp_byte.length;
        mp_byte_clear.bytes = (lc_uchar *)LC_MALLOC(mp_byte_clear.length);
        if (LC_NULL == mp_byte_clear.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    /* Decryption. */
    if (LC_SUCCESS == result)
    {
        result = LC_CryptModule(LC_FALSE, mp_byte_clear.bytes, mp_byte.bytes, mp_byte_clear.length);
    }

    if (LC_SUCCESS == result)
    {            
        result = MessageParser_ParseSharedMemory(&mp_byte_clear, &bitpos, &pLoaderPt->sharedMemory);      
    }

    /* Parsing. */
    if (LC_SUCCESS == result)
    {                
        result= MessageParser_ParseDownloadInfo(&mp_byte_clear, &bitpos, &pLoaderPt->downloadInfo);

        /* Check crc32. */
        if (LC_SUCCESS == result)
        {
            crc32 = CRC_Code32(
                        (void *)&mp_byte_clear.bytes[LDR_SHARED_MEM_SIZE], 
                        LDR_AREA_DOWNLOAD_INFO_SIZE - 4);
            if (crc32 != pLoaderPt->downloadInfo.crc32)
            {
                result = LC_ERROR_INVALID_DATA;
            }
        }
    }

    LC_Free_Memory((void **)&mp_byte_clear.bytes);
    LC_Free_Memory((void **)&mp_byte.bytes);

    return result;
	
}


lc_result LC_ReadSharedMemory(lc_shared_memory_st *pSharedMemory)
{

    lc_result result = LC_SUCCESS;
    lc_buffer_st mp_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte_clear = {LC_NULL, 0};
    lc_uint32 bitpos = 0;


    if (LC_NULL == pSharedMemory)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_LOADER_PT, &mp_byte);
    }

    if (LC_SUCCESS == result)
    {
        mp_byte_clear.length = mp_byte.length;
        mp_byte_clear.bytes = (lc_uchar *)LC_MALLOC(mp_byte_clear.length);
        if (LC_NULL == mp_byte_clear.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    /* Decryption. */
    if (LC_SUCCESS == result)
    {
        result = LC_CryptModule(LC_FALSE, mp_byte_clear.bytes, mp_byte.bytes, mp_byte_clear.length);
    }

    if (LC_SUCCESS == result)
    {            
        result = MessageParser_ParseSharedMemory(&mp_byte_clear, &bitpos, pSharedMemory);      
    }

    LC_Free_Memory((void **)&mp_byte_clear.bytes);
    LC_Free_Memory((void **)&mp_byte.bytes);

    return result;
    
}

lc_result LC_WriteSharedMemory(lc_bool createNew, lc_shared_memory_st* pSharedMemory)   //
{
	lc_result result = LC_SUCCESS;
    lc_buffer_st module_byte = {LC_NULL, 0};
    lc_buffer_st mh_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte_clear = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_uint32 cnt = 0;
    lc_module_info_header mih_st;

    LC_memset(&mih_st, 0, sizeof(lc_module_info_header));    
    
    if (LC_NULL == pSharedMemory)
    {
        result = LC_ERROR_NULL_PARAM;
    }
    
    /* attempt to read Loader Partition first (it contains the loader pt) */
    if (LC_SUCCESS == result)
    {
        /* If you grant access to create a new one, just create it, otherwise, return an error */
        if (LC_TRUE == createNew)
        {
            /* The 1st time writing this module, just creat a new one. */
            
            mih_st.module_id = MODULE_DRV_ID_LOADER_PT;
            mih_st.header_length = SHORT_MODULE_INFO_HEADER_SIZE;   //12bytes
            mih_st.module_size = LDR_SHARED_MEM_SIZE
                                + LDR_AREA_DOWNLOAD_INFO_SIZE;      //80bytes
    
            /* build module_info_header */
            if (LC_SUCCESS == result)
            {
                mh_byte.length = mih_st.header_length;
                mh_byte.bytes = (lc_uchar *)LC_MALLOC(mh_byte.length);
                if (LC_NULL == mh_byte.bytes)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }
            }
    
            if (LC_SUCCESS == result)
            {
                /* convert the parameters into module format */
                result = MessageCombiner_CombineModuleInfoHeader(&mh_byte, &bitpos, &mih_st);
                cnt = bitpos / 8;        
            }
    
            /* allocate memory for module payload */
            if (LC_SUCCESS == result)
            {
                mp_byte.length = mih_st.module_size;
                mp_byte.bytes = (lc_uchar *)LC_MALLOC(mp_byte.length);
                if (LC_NULL == mp_byte.bytes)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }
            }           
        }
        else
        {
            /* If we already have this module, just make use of it. In this way, the module header 
             * will be kept unchanged as loader pt has a fixed size so that it it unnecessary to
             * make any change to the module_size field of this module header.
             */
            result = LC_ReadAndParseModuleInfoHeader(            
                                MODULE_DRV_ID_LOADER_PT, 
                                &mih_st, 
                                &mh_byte);
          
		   
            if (LC_SUCCESS == result)
            {
                result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_LOADER_PT, &mp_byte);
                if( LC_SUCCESS !=  result)
                {
                    TRACE_LOG1(
                        TRACE_ERROR, 
                        "[Module_mng] Error reading module payload on checking the existing module #%u!\n",
                        MODULE_DRV_ID_LOADER_PT);
                }
            }
        }
    }
    

    /* combine module_info_header and module payload into an entire module */
    if (LC_SUCCESS == result)
    {
        module_byte.length = mih_st.header_length + mih_st.module_size;
        module_byte.bytes = (lc_uchar *)LC_MALLOC(module_byte.length);
        if (LC_NULL == module_byte.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }       
    }

    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != createNew)
        {
            mp_byte_clear.length = mp_byte.length;
            mp_byte_clear.bytes = (lc_uchar *)LC_MALLOC(mp_byte_clear.length);
            if (LC_NULL == mp_byte_clear.bytes)
            {
                result = LC_ERROR_INSUFFICIENT_BUFFER;
            }

            if (LC_SUCCESS == result)
            {
                result = LC_CryptModule(
                            LC_FALSE, 
                            mp_byte_clear.bytes, 
                            mp_byte.bytes, 
                            mp_byte_clear.length);
            }
        }
        else
        {
            mp_byte_clear.length = mp_byte.length;
            mp_byte_clear.bytes = mp_byte.bytes;
        }
    }

    /* update module payload (just shared memory field) */
    if (LC_SUCCESS == result)
    {
        bitpos = 0;
        result = MessageCombiner_CombineSharedMemory(&mp_byte_clear, &bitpos, pSharedMemory);
    }
    
    /* Encryption. */
    if (LC_SUCCESS == result)
    {
        result = LC_CryptModule(
                    LC_TRUE, 
                    &module_byte.bytes[mih_st.header_length], 
                    mp_byte_clear.bytes, 
                    mih_st.module_size);
    }

    /* copy module_info_header */
    if (LC_SUCCESS == result)
    {      
        LC_memcpy(
            &module_byte.bytes[0], 
            &mh_byte.bytes[0], 
            mih_st.header_length );
    }

    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_WriteModule(MODULE_DRV_ID_LOADER_PT, &module_byte);        //enc should reserve
        if (LC_SUCCESS != result)
        {
            ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_LOADERPT);
        }
    }

    if (LC_TRUE != createNew)
    {
        LC_Free_Memory((void **)&mp_byte_clear.bytes);
    }

    LC_Free_Memory((void **)&module_byte.bytes);
    LC_Free_Memory((void **)&mp_byte.bytes);
    LC_Free_Memory((void **)&mh_byte.bytes);

    MessageParser_FreeModuleInfoHeader(&mih_st);

    return result;

}

lc_result LC_GetDownloadSequence(lc_uint16 *pDsn)
{
    lc_result result = LC_SUCCESS;
    lc_last_download_info_st dlInfo;

    LC_memset(&dlInfo, 0, sizeof(lc_last_download_info_st));
    
    /* Load the first part of the download info */
    if (LC_SUCCESS == result)
    {
        result = LC_GetDownloadInformation(&dlInfo);
    }

    if (LC_SUCCESS == result)
    {
        /* no verification required for download sequence number for V5 */
        *pDsn = dlInfo.download_sequence_number;
    }
    
    return result;
}

lc_result LC_CheckDownloadSequence(lc_uint16 newDsn, lc_uint16 deviceDsn)
{
    lc_result result = LC_SUCCESS;


    /* values 0 and 255 are never receivable. */
    if( (0x0000 == newDsn) || (0xFFFF == newDsn) )
    {
        result = LC_ERROR_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER;
    }

    /* If the load sequence number of the STB cannot be discerned due to blank
     * or corrupt flash, then the value shall be assumed to be 0xFFFF and the 
     * download window shall run from 1 to 65534 inclusive. 
     */
    if(LC_SUCCESS == result)
    {
        /* If the device has a download sequence value of 0xFFFF, Loader Core does not need a further check.  */
        if (0xFFFF != deviceDsn)
        {
            if(newDsn > deviceDsn)
            {
                /* The window runs from 1 above the current value to 
                    99 above the current value inclusive. */
                if((newDsn - deviceDsn) > DEFAULT_MAX_INCREMENT_FOR_LOAD_SEQ_NUM)
                {
                    result = LC_ERROR_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER;
                }
            }
            else if(newDsn < deviceDsn)
            {
                /* If the window extends beyond 65536 then modulus 63356
                    should be applied to calculate the limit of the window.*/
                if((65534 - (deviceDsn - newDsn)) > DEFAULT_MAX_INCREMENT_FOR_LOAD_SEQ_NUM)
                {
                    result = LC_ERROR_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER;
                }
            }
            else
            {
                result = LC_ERROR_SAME_DOWNLOAD_SEQUENCE_NUMBER;
            }
        }
    }

    return result;
}


lc_result LC_StoreDownloadInformation(lc_last_download_info_st *pDownloadInformation)  //#201803
{

	lc_result result = LC_SUCCESS;
    lc_buffer_st module_byte = {LC_NULL, 0};
    lc_buffer_st mh_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte_clear = {LC_NULL, 0};
    lc_module_info_header mih_st;
    lc_uint32 bitpos = 0;

    LC_memset(&mih_st, 0, sizeof(lc_module_info_header));

    
    if (LC_SUCCESS == result)
    {

		result = LC_ReadAndParseModuleInfoHeader(
                            MODULE_DRV_ID_LOADER_PT, 
                            &mih_st, 
                            &mh_byte);
        
        if (LC_SUCCESS == result)
        {
            LC_ASSERT(mih_st.header_length == mh_byte.length);
            
            result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_LOADER_PT, &mp_byte);
            if( LC_SUCCESS != result)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "[Module_mng] Error reading module payload on checking the existing module #%u!\n",
                    MODULE_DRV_ID_LOADER_PT);
            }
         }
    }

    if (LC_SUCCESS == result)
    {
        mp_byte_clear.length = LDR_SHARED_MEM_SIZE + LDR_AREA_DOWNLOAD_INFO_SIZE;
        mp_byte_clear.bytes = (lc_uchar *)LC_MALLOC(mp_byte_clear.length);
        if (LC_NULL == mp_byte_clear.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    if (LC_SUCCESS == result)
    {
        result = LC_CryptModule(
                    LC_FALSE, 
                    mp_byte_clear.bytes, 
                    mp_byte.bytes, 
                    mp_byte.length);
    }

    
    if (LC_SUCCESS == result)
    {
        /* update module_size of module_info_header */
        mih_st.module_size = LDR_SHARED_MEM_SIZE + LDR_AREA_DOWNLOAD_INFO_SIZE;

        /* update module buffer size and allocate memory for the new module */
        module_byte.length = mih_st.header_length + mih_st.module_size;
        module_byte.bytes = (lc_uchar *)LC_MALLOC(module_byte.length);
        if (LC_NULL == module_byte.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }        
    }
    
    /* build this new module */
    if (LC_SUCCESS == result)
    {
        /* 1. Shared Memory field, don't make any change. */
        
        /* 2. Update Download Information field. */
        if (LC_SUCCESS == result)
        {
            bitpos = 8 * (LDR_SHARED_MEM_SIZE);
            result = MessageCombiner_CombineDownloadInfo(
                        &mp_byte_clear, 
                        &bitpos, 
                        pDownloadInformation);
        }

        /* 3. Encrypt Loader Partition. */
        if (LC_SUCCESS == result)
        {
            result = LC_CryptModule(
                        LC_TRUE, 
                        &module_byte.bytes[mih_st.header_length], 
                        mp_byte_clear.bytes, 
                        mih_st.module_size);
        }

        /* 4. module_info_header */
        if (LC_SUCCESS == result)
        {
            LC_memcpy(module_byte.bytes, mh_byte.bytes, mih_st.header_length);
        }
    }

    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_WriteModule(MODULE_DRV_ID_LOADER_PT, &module_byte);
        if (LC_SUCCESS != result)
        {
            ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_LOADERPT);
        }
    }

    LC_Free_Memory((void **)&module_byte.bytes);
    LC_Free_Memory((void **)&mp_byte_clear.bytes);
    LC_Free_Memory((void **)&mp_byte.bytes);
    LC_Free_Memory((void **)&mh_byte.bytes);
    
    return result;
}

lc_result LC_GetDownloadInformation(lc_last_download_info_st *pDownloadInformation)
{

    lc_result result = LC_SUCCESS;
    lc_buffer_st mp_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte_clear = {LC_NULL, 0};
    lc_buffer_st downInfo = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_buffer_st mh_byte = {LC_NULL, 0};
    lc_module_info_header mih_st;
    lc_uint32 crc32 = 0;

    LC_memset(&mih_st, 0, sizeof(lc_module_info_header));

    /* attempt to read Loader Partition first (it contains the loader pt) */
    if (LC_SUCCESS == result)
    {
		result = LC_ReadAndParseModuleInfoHeader(
                    MODULE_DRV_ID_LOADER_PT, 
                    &mih_st, 
                    &mh_byte);

        if (LC_SUCCESS == result)
        {
            result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_LOADER_PT, &mp_byte);
            if( LC_SUCCESS !=  result)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "[Module_mng] Error reading module payload on checking the existing module #%u!\n",
                    MODULE_DRV_ID_LOADER_PT);
            }
        }

        /* Check if module size is large enough. */
        if (LC_SUCCESS == result)
        {
            if (mih_st.module_size < (LDR_SHARED_MEM_SIZE + LDR_AREA_DOWNLOAD_INFO_SIZE))
            {
                result = LC_ERROR_ILLEGAL_MODULE_CONTENT;
            }
        }
    }

    /* Decryption. */
    if (LC_SUCCESS == result)
    {
        mp_byte_clear.length = mp_byte.length;
        mp_byte_clear.bytes = (lc_uchar *)LC_MALLOC(mp_byte_clear.length);
        if (LC_NULL == mp_byte_clear.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }
    
    if (LC_SUCCESS == result)
    {
        result = LC_CryptModule(
                    LC_FALSE, 
                    mp_byte_clear.bytes, 
                    mp_byte.bytes, 
                    mp_byte.length);
    }

    /* Parsing. */
    if (LC_SUCCESS == result)
    {
        downInfo.length = mih_st.module_size - LDR_SHARED_MEM_SIZE;
        downInfo.bytes = &mp_byte_clear.bytes[LDR_SHARED_MEM_SIZE];
                
        result= MessageParser_ParseDownloadInfo(&downInfo, &bitpos, pDownloadInformation);
    }

    /* Check crc32. */
    if (LC_SUCCESS == result)
    {

        crc32 = CRC_Code32((void *)downInfo.bytes, downInfo.length - 4);
        if (crc32 != pDownloadInformation->crc32)
        {
            result = LC_ERROR_INVALID_DATA;
        }
	 
    }

    /* clear memory blocks */
    LC_Free_Memory((void **)&mp_byte_clear.bytes);
    LC_Free_Memory((void **)&mp_byte.bytes);
    LC_Free_Memory((void **)&mh_byte.bytes);

    MessageParser_FreeModuleInfoHeader(&mih_st);

    return result;
	
}

static lc_bool IsValidSsuPid(lc_uint16 ssuPid)
{
    /*Get the first byte of address. */
    lc_bool result = LC_TRUE;

    /* valid range of PID value for DVB-SSU streams: 
     *    0x00 ~ 0x1F are reserved in DVB standard.
     *    0x1FFF is reserved for null package in DVB standard.
     */
    if((ssuPid <= (lc_uint16)0x1F) || ( ssuPid == 0x1FFF))
    {
        result = LC_FALSE;
    }

    return result;
}

lc_result LC_VerifyDVBSSUParameters( const lc_dvbssu_dl_info_st *pDvbParameters )
{
    lc_result result = LC_SUCCESS;

    if (LC_TRUE != IsValidSsuPid(pDvbParameters->pid))
    {
        result = LC_ERROR_INVALID_PARAMETER;
    }

    /* To be defined by manufacturer for further verification. */

    return result;
}


lc_result LC_VerifyOtaDownloadParameters(const lc_ota_dl_para_st *pOtaParameters)
{
    lc_result result = LC_SUCCESS;
    lc_buffer_st otaParaByte = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_ota_dl_para_st comparision;

    LC_memcpy(&comparision, pOtaParameters, sizeof(lc_ota_dl_para_st));

    otaParaByte.length = 64;
	otaParaByte.bytes = (lc_uchar *)LC_MALLOC(otaParaByte.length);
	if (LC_NULL == otaParaByte.bytes)
	{
		result = LC_ERROR_INSUFFICIENT_BUFFER;
	}

    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_CombineOtaDownloadParameters(&otaParaByte, &bitpos, &comparision);
    }

    /* Check crc32. */
    if (LC_SUCCESS == result)
    {
        if (comparision.crc32 != pOtaParameters->crc32)
        {
            result = LC_ERROR_INVALID_DATA;
        }
    }

    LC_Free_Memory((void **)&otaParaByte.bytes);

    return result;
}

lc_result LC_SetDownloadFlag( lc_bool enableDl, lc_shared_memory_st *pSharedMemory )
{
    lc_result result = LC_SUCCESS;

    if (LC_NULL == pSharedMemory)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    /* serialize */
    if (LC_SUCCESS == result)
    {
        pSharedMemory->downloadIndicator &= 0x0f;
        
        /* enable or disable */
        if (LC_TRUE == enableDl)
        {
            pSharedMemory->downloadIndicator |= (lc_uchar)(1 << 4);
        }
    }

    return result;
}

lc_result LC_SetDownloadType( lc_uchar dlType, lc_shared_memory_st *pSharedMemory )
{
    lc_result result = LC_SUCCESS;

    if (dlType > OTA_DOWNLOAD)
    {
        result = LC_ERROR_INVALID_PARAMETER;
    }

    if (LC_SUCCESS == result)
    {
    	pSharedMemory->downloadIndicator &= 0xf0;
		pSharedMemory->downloadIndicator |= (0x0f & dlType);		
    }

    return result;

}

lc_result LC_SetDownloadIndicator(lc_bool enableDl, lc_uchar dlType, lc_shared_memory_st *pSharedMemory)
{
    lc_result result = LC_SUCCESS;

    /* enable or disable */
    result = LC_SetDownloadFlag(enableDl, pSharedMemory);

    /* download type */
    if (LC_SUCCESS == result)
    {
        result = LC_SetDownloadType(dlType, pSharedMemory);
    }

    return result;
}

lc_bool LC_GetDownloadFlag( const lc_shared_memory_st *pSharedMemory )
{
    lc_bool result = LC_TRUE;

	/* enable or disable */
	if ( 0 != ((pSharedMemory->downloadIndicator >> 4) & 0x01) )
	{
		result = LC_TRUE;
	}
	else
	{
		result = LC_FALSE;
	}

    return result;
}

lc_uchar LC_GetDownloadType( const lc_shared_memory_st *pSharedMemory )
{
    lc_uchar dlType = NONE_DOWNLOAD;

    dlType = (pSharedMemory->downloadIndicator) & 0x0f;
    
    if (dlType > OTA_DOWNLOAD)
    {
        dlType = NONE_DOWNLOAD;
    }

    return dlType;
}


