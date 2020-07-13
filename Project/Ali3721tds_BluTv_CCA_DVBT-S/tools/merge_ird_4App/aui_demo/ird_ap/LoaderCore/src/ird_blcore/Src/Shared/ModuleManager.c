/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : ModuleManager.c                                            *
*                                                                            *
*   Description : This module supplies the functions required by             *
*                 Loader Core to access the modules.                         *
*                                                                            *
*****************************************************************************/

#include "LoaderCorePrivate.h"


/* Maximum signature size for MAC */
#define MAX_MAC_SIGNATURE_SIZE (SIGNATURE_LENGTH)
/* Minimum module ID  size for High level App */
#define MIN_MODULE_ID_APP (0x20)

lc_result LC_CryptModule(lc_bool encrypt, lc_uchar *pOut, const lc_uchar *pIn, lc_uint32 size)
{
	lc_result result = LC_SUCCESS;
    lc_bbcb_st bbcb;
    lc_uchar cryptKey[8];
    lc_uchar keyCatch[8];
    lc_uint32 cnt = 0;

    LC_memset(&bbcb, 0, sizeof(lc_bbcb_st));
    LC_memset(cryptKey, 0, sizeof(cryptKey));
    LC_memset(keyCatch, 0, sizeof(keyCatch));
    

    if (LC_NULL == pOut || LC_NULL == pIn || 0 == size || size > 0xFFFF)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        if (pOut > pIn && pOut < pIn + size)
        {
            result = LC_ERROR_INVALID_PARAMETER;
        }
    }

    if( LC_SUCCESS == result )
    {
        result = BBCB_GetBBCB(&bbcb, LC_NULL);
        if( LC_SUCCESS != result)
        {
            ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_BBCB);
            TRACE_LOG0(TRACE_ERROR, ("&[Module_mng] Error: Failed to retrieve BBCB!\n"));
        }
    }

    if( LC_SUCCESS == result )
    {
        /* The private key is combined with serial number and random number. */
        LC_memcpy(&keyCatch[0], bbcb.serial_number, 4);
        LC_memcpy(&keyCatch[4], bbcb.random_number, 4);

        if (LC_TRUE == encrypt)
        {
            LC_memcpy(cryptKey, keyCatch, sizeof(keyCatch));
        }
        else
        {
            /* Reverse the byte order. */
            for (cnt = 0; cnt < 8; cnt++)
            {
                cryptKey[cnt] = keyCatch[8 - 1 - cnt];
            }
        }
    }

    /* encrypt/decrypt */
    if (LC_SUCCESS == result)
    {
        VBCIPHER_VariBlockCipher(
            pOut, 
            pIn, 
            (lc_uint16)size, 
            cryptKey, 
            sizeof(cryptKey));
    }

    return result;

}


lc_bool LC_IsVariantValid(const lc_uint16 *pVariant, const lc_uint16 *pSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_bool ret = LC_FALSE;


    /* Check value. */
    if (LC_SUCCESS == result)
    {
        /* Valid scope for variant: 1~65534 */
        if (LC_NULL != pVariant)
        {
            if (0 == *pVariant || 65535 == *pVariant)
            {
                result = LC_ERROR_INVALID_VARIANT_VALUE;
            }
        }

        /* Valid scope for sub-variant: 0~65534 */
        if (LC_NULL != pSubVariant)
        {
            if (65535 == *pSubVariant)
            {
                result = LC_ERROR_INVALID_SUBVARIANT_VALUE;
            }
        }
    }

    if (LC_SUCCESS == result)
    {
        ret = LC_TRUE;
    }

    return ret;
}    

static lc_bool ShallUseHardwareHash(
    pkcs_hash_mode targetMode,
    lc_checksum_algorithm deviceSupportMode)
{
    lc_bool result = LC_FALSE;

    if (PKCS_SHA1_MODE == targetMode && 
        LC_CHECKSUM_ALGORITHM_SHA1 == deviceSupportMode)
    {
        result = LC_TRUE;
    }
    else if (PKCS_SHA256_MODE == targetMode && 
        LC_CHECKSUM_ALGORITHM_SHA256 == deviceSupportMode)
    {
        result = LC_TRUE;
    }
    
    return result;
}


lc_result LC_UpdateModuleSignature(
    lc_uchar targetAlgorithm,
    lc_buffer_st *pByte,
    lc_module_info_header *pMih)
{

    lc_result result = LC_SUCCESS;
    lc_uint32 bitpos = 0;
    lc_module_info_header newMih;
    lc_checksum_info checksumInfo;
    lc_buffer_st newHeaderSignature = {LC_NULL, 0};
    lc_buffer_st newPayloadSignature = {LC_NULL, 0};
    lc_buffer_st rawData[2];
    lc_checksum_algorithm hardwareAlgorithm = LC_CHECKSUM_ALGORITHM_MIN_RESERVED;
    lc_uchar finalAlgorithm = targetAlgorithm;

    LC_memset(&newMih, 0, sizeof(lc_module_info_header));
    LC_memset(&checksumInfo, 0, sizeof(lc_checksum_info));
    LC_memset(&rawData[0], 0, sizeof(lc_buffer_st));
    LC_memset(&rawData[1], 0, sizeof(lc_buffer_st));


    if (LC_BOOTCHECK_CRC32 == targetAlgorithm ||
        MODULE_DRV_ID_VARIANT == pMih->module_id)
    {
        /**
         *  variant module is a special case, CRC32 should be the choice unconditionally. 
         */
        finalAlgorithm = LC_BOOTCHECK_CRC32;
    }
    /* Otherwise, Loader Core have to check the SPI driver to see whether they match or not. */
    else if (LC_BOOTCHECK_MAC == targetAlgorithm)
    {
        /* MAC can only be calculated through SPI. */
        result = LoaderCoreSPI_Device_ChooseAlgorithm(&hardwareAlgorithm);
        if (LC_SUCCESS == result)
        {
            if (LC_CHECKSUM_ALGORITHM_MAC != hardwareAlgorithm)
            {
                result = LC_FAILURE;
            }
        }
    }
    else if (LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION == targetAlgorithm)
    {
        /* SHA can be calculated through either SPI or hardcoded software implementation. */
        if (LC_SUCCESS == LoaderCoreSPI_Device_ChooseAlgorithm(&hardwareAlgorithm))
        {
            if (LC_CHECKSUM_ALGORITHM_SHA1 != hardwareAlgorithm && 
                LC_CHECKSUM_ALGORITHM_SHA256 != hardwareAlgorithm )
            {
                result = LC_FAILURE;
            }
        }
    }
    else
    {
        result = LC_FAILURE;
    }
    
    if (LC_SUCCESS == result)
    {
        if (LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION == finalAlgorithm)
        {
            /* Do nothing. */
        }
        else
        {
            if (LC_SUCCESS == result)
            {
                newHeaderSignature.length = MAX_MAC_SIGNATURE_SIZE;
                newHeaderSignature.bytes = LC_MALLOC(newHeaderSignature.length);
                if (LC_NULL == newHeaderSignature.bytes)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }
            }

            if (LC_SUCCESS == result)
            {
                newPayloadSignature.length = MAX_MAC_SIGNATURE_SIZE;
                newPayloadSignature.bytes = LC_MALLOC(newPayloadSignature.length);
                if (LC_NULL == newPayloadSignature.bytes)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }
            }

            if (LC_SUCCESS == result)
            {
                /* Backup the original module_info_header first. */
                LC_memcpy(&newMih, pMih, sizeof(lc_module_info_header));
                    
                /* Header signature */
                rawData[0].bytes = pByte->bytes;
                rawData[0].length = pMih->header_length
                                    - 2                    /* header_signature_length */
                                    - 2                    /* module_signature_length */
                                    - 4                    /* crc32 */
                                    - pMih->module_signature_length
                                    - pMih->header_signature_length;
                                        

                /* Payload Signature */
                rawData[1].bytes = &pByte->bytes[pMih->header_length];
                rawData[1].length = pMih->module_size;
                
            }

            if (LC_SUCCESS == result)
            {
                if (LC_BOOTCHECK_MAC == finalAlgorithm)
                {
                    
                    checksumInfo.algorithm = LC_CHECKSUM_ALGORITHM_MAC;

                    /* Header Signature. */
                    if (LC_SUCCESS == result)
                    {
                        result = LoaderCoreSPI_Device_GetChecksum(
                                    &checksumInfo, 
                                    &rawData[0],
                                    &newHeaderSignature);
                    }

                    /* Payload Signature. */
                    if (LC_SUCCESS == result)
                    {                  
                        result = LoaderCoreSPI_Device_GetChecksum(
                                    &checksumInfo, 
                                    &rawData[1],
                                    &newPayloadSignature);
                    }

                }
                else if((LC_BOOTCHECK_CRC32 == finalAlgorithm) && ( pMih->module_id >= MIN_MODULE_ID_APP))
                {
                    result = LC_FAILURE;
                    
                }					
                else if ((LC_SUCCESS == result) && (LC_BOOTCHECK_CRC32 == finalAlgorithm))
                {
                    lc_uint32 crc;

                    /* Header Signature */
                    crc = CRC_Code32(rawData[0].bytes, rawData[0].length);
                    H2N32(&crc);

                    LC_memcpy(newHeaderSignature.bytes, (void *)&crc, 4);

                    /* Payload Signature */
                    crc = CRC_Code32(rawData[1].bytes, rawData[1].length);
                    H2N32(&crc);

                    LC_memcpy(newPayloadSignature.bytes, (void *)&crc, 4);
                    
                }
            }

            /* Serilize */
            if (LC_SUCCESS == result)
            {                       
                /* Update signature data. */
                LC_memcpy(
                    pMih->header_signature_data, 
                    newHeaderSignature.bytes, 
                    pMih->header_signature_length);
                LC_memcpy(
                    pMih->module_signature, 
                    newPayloadSignature.bytes, 
                    pMih->module_signature_length);
                

                /* Build a new module_info_header. */
                result = MessageCombiner_CombineModuleInfoHeader(pByte, &bitpos, pMih);
                if (LC_SUCCESS == result)
                {
                    pByte->length = pMih->header_length + pMih->module_size;

                    /* Build a new module payload. */
                    LC_memcpy(
                        &pByte->bytes[pMih->header_length], 
                        &pByte->bytes[pMih->header_length], 
                        pMih->module_size);
                }
                
            }

            LC_Free_Memory((void **)&newHeaderSignature);
            LC_Free_Memory((void **)&newPayloadSignature);

        }
    }

    if (LC_SUCCESS != result)
    {
        ERR_REPORT_SetErrorCode(ERROR_CODE_UPDATE_MODULE_SIGNATURE);
    }
    
    return result;

}



static
lc_result LC_VerifyDigitalSignature(
    const lc_checksum_algorithm_status *pStatus,
    lc_uchar* pBuffer, 
    lc_uint32 length, 
    lc_uchar* pSignature)
{
 
    lc_result result = LC_SUCCESS;
    lc_bool useHardwareHash = LC_FALSE;
    lc_checksum_algorithm hardwareAlgorithm = LC_CHECKSUM_ALGORITHM_MIN_RESERVED;
    lc_sha_controller sha;  
    lc_uchar hash[32];
    lc_uint32 hashLength = 0;
    lc_uchar *pEm = LC_NULL;
    pkcs_result pkcsRet = PKCS_ERROR_SUCCESS;
    pkcs_buffer_st stHash;
    lc_checksum_algorithm shaMode = LC_CHECKSUM_ALGORITHM_MIN_RESERVED;

    LC_memset(&sha, 0x0, sizeof(sha));
    LC_memset(&stHash, 0x0, sizeof(stHash));
    LC_memset(hash, 0x0, sizeof(hash));


    LC_ASSERT(LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION == pStatus->algorithm);

    if (LC_SUCCESS == result)
    {
        pkcsRet = Rsa_CheckHashMode( &sha.mode);

        if(PKCS_SHA1_MODE == sha.mode)
        {
            hashLength = LC_SHA1_HASH_LEN;
            shaMode = LC_CHECKSUM_ALGORITHM_SHA1;
        }
        else if(PKCS_SHA256_MODE == sha.mode)
        {
            hashLength = LC_SHA256_HASH_LEN;
            shaMode = LC_CHECKSUM_ALGORITHM_SHA256;
        }
        else
        {
            result = LC_FAILURE; /* unsupported sha mode */
        }

    }

    /* Can we use hardware hash? */
    if (LC_SUCCESS == result)
    {
        if (LC_SUCCESS == LoaderCoreSPI_Device_ChooseAlgorithm(&hardwareAlgorithm))
        {
            useHardwareHash = ShallUseHardwareHash(sha.mode, hardwareAlgorithm);
        }
    }
    
    /* Calculate Hash */
    if (LC_SUCCESS == result)
    {
        /* If this device supports the hash mode, make use of it; otherwise, use software algorithm instead. */
        if (LC_TRUE == useHardwareHash)
        {
            lc_checksum_info checksumInfo;
            lc_buffer_st rawData;
            lc_buffer_st hashData;
                
            checksumInfo.algorithm = shaMode;
            rawData.bytes = pBuffer;
            rawData.length = length;
            hashData.bytes = hash; 
            hashData.length = sizeof(hash);

            result = LoaderCoreSPI_Device_GetChecksum(&checksumInfo, &rawData, &hashData);
            
        }
        else    /* If device does not support the required hash mode, use software algorithm instead. */
        {
            if (LC_SUCCESS == result)
            {
                result = LC_SHAInit(&sha);
            }
            
            if (LC_SUCCESS == result)
            {
                result = LC_SHAUpdate(&sha, pBuffer, length);
            }
           
            if (LC_SUCCESS == result)
            {  
                result = LC_SHAFinal(&sha, hash);
                if (LC_SUCCESS != result)
                {
                    TRACE_LOG0(TRACE_ERROR, ("[Module_mng] Error: Failed to retrieve hash for buffer\n"));
                }
            }
        }
    }

    /* Verify with the given key, if the key is NULL it is only a hash comparison */ 
    if (LC_SUCCESS == result)
    {
        stHash.bytes = hash;
        stHash.length = hashLength;
        pkcsRet = Rsa_VerifyPkcs(pStatus->pRsaKey, pSignature, &stHash);
        if(PKCS_ERROR_SUCCESS != pkcsRet)
        {
            TRACE_LOG0(TRACE_ERROR, ("[Module_mng] Error: PKCS Signature verified Failed(RSA)!\n"));
            result = LC_FAILURE; /* unsupported sha mode */
        }   
    }

    
    return result;

}

static
lc_result LC_VerifyCrc32Signature(
    const lc_checksum_algorithm_status *pStatus,
    lc_uchar* pBuffer, 
    lc_uint32 length, 
    lc_uchar* pSignature)
{
	lc_result result = LC_SUCCESS;
    lc_uint32 sigCrc = 0;
    lc_uint32 calCrc = 0;

    LC_ASSERT(LC_BOOTCHECK_CRC32 == pStatus->algorithm);

    /* Calculate CRC32 */
    if (LC_SUCCESS == result)
    {
        /* Get the actual CRC value. */
        calCrc = CRC_Code32(pBuffer, length);

        /* Get the value from signature. */
        LC_memcpy((void *)&sigCrc, (void *)pSignature, 4);
        N2H32(&sigCrc);
    }

    /* Verify signature by making comparison. */
    if (LC_SUCCESS == result)
    {
        if ((sigCrc != calCrc) || (0 == sigCrc))
        {
            result = LC_FAILURE;
        }
    }
    
    return result;

}

static
lc_result LC_VerifyMACSignature(
    const lc_checksum_algorithm_status *pStatus,
    lc_uchar* pBuffer, 
    lc_uint32 length, 
    lc_uchar* pSignature)
{
    lc_result result = LC_SUCCESS;
    lc_checksum_info checksumInfo;
    lc_buffer_st rawData = {LC_NULL, 0};
    lc_buffer_st hashData = {LC_NULL, 0};


    /* MAC should only be supported by hardware. */
    LC_ASSERT(LC_BOOTCHECK_MAC == pStatus->algorithm)

    LC_memset(&checksumInfo, 0, sizeof(lc_checksum_info));

    if (LC_SUCCESS == result)
    {
        hashData.length = MAX_MAC_SIGNATURE_SIZE;
        hashData.bytes = LC_MALLOC(hashData.length);
        if (LC_NULL == hashData.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    /* Calculate MAC */
    if (LC_SUCCESS == result)
    {
        checksumInfo.algorithm = pStatus->algorithm;
        rawData.bytes = pBuffer;
        rawData.length = length;

        result = LoaderCoreSPI_Device_GetChecksum(&checksumInfo, &rawData, &hashData);
    }

    /* Verify signature by making comparison. */
    if (LC_SUCCESS == result)
    {
        if (0 != LC_memcmp(pSignature, hashData.bytes, hashData.length))
        {
            result = LC_FAILURE;
        }
    }

    LC_Free_Memory((void **)&hashData.bytes);
    
    return result;
}



lc_result LC_VerifySignature(
    const lc_checksum_algorithm_status *pStatus,
    lc_uchar* pBuffer, 
    lc_uint32 length, 
    lc_uchar* pSignature)
{
   
	lc_result result = LC_SUCCESS;
    

    switch (pStatus->algorithm)
    {
        /** SHA1 or SHA256 */
        case LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION:
        {
            result = LC_VerifyDigitalSignature(pStatus, pBuffer, length, pSignature);
            break;
        }

         /** CRC32 */
        case LC_BOOTCHECK_CRC32:
        {
            result = LC_VerifyCrc32Signature(pStatus, pBuffer, length, pSignature);
            break;
        }

         /** MAC */
        case LC_BOOTCHECK_MAC:
        {
            result = LC_VerifyMACSignature(pStatus, pBuffer, length, pSignature);
            break;
        }

         /** Unsupported */
        default:
        {
            result = LC_ERROR_INVALID_PARAMETER;
            break;
        }
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "&[Module_mng] Success: Signature verification OK! algorithm = %u\n", 
            pStatus->algorithm);
    }
    else
    {
        TRACE_LOG1(
            TRACE_ERROR, 
            "&[Module_mng] Error: Signature verification failed! algorithm = %u\n", 
            pStatus->algorithm);
    }


    return result;

}


lc_result LC_ReadAndParseModuleInfoHeader(
    lc_uint16 moduleId, 
    lc_module_info_header *pStModuleInfoHeader,
    lc_buffer_st *pByteModuleInfoHeader)
{

    lc_result result = LC_SUCCESS;
    lc_module_info_header mih_st; 
    lc_uint32 bitpos = 0;
    lc_buffer_st mih_byte = {LC_NULL, 0};
    lc_uint32 crc32 = 0;

    LC_memset(&mih_st, 0, sizeof(lc_module_info_header));    

    TRACE_LOG1(TRACE_DEBUG, "[Module_mng] Verifying module #%u\n", moduleId);
      
    /* Get and parse module header */
    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_ReadModuleHeader(moduleId, &mih_byte);
        if( LC_SUCCESS != result)
        {
            TRACE_LOG1(TRACE_ERROR, "[Module_mng] Error loading module header #%u\n", moduleId);
        }
    }

    if (LC_SUCCESS == result)
    {
        result = MessageParser_ParseModuleInfoHeader(
                    LC_FALSE,
                    &mih_byte, 
                    &bitpos, 
                    &mih_st);
    }

    /* check crc32 */
    if (LC_SUCCESS == result)
    {

        if (0 == mih_st.crc32)
        {
            result = LC_ERROR_ILLEGAL_MODULE_CONTENT;
        }
        else
        {   
            crc32 = CRC_Code32(mih_byte.bytes, (mih_st.header_length - 4));
            if (crc32 != mih_st.crc32)
            {
                result = LC_ERROR_ILLEGAL_MODULE_CONTENT;
            }
			
        }

    }

    /* Check if the module ID matches */
    if (LC_SUCCESS == result)
    {
        if( moduleId != mih_st.module_id )
        {
            TRACE_LOG1(
                TRACE_ERROR, 
                "[Module_mng] Error: Existing modules ID #%u is not correct!\n", 
                mih_st.module_id);
            result = LC_ERROR_ILLEGAL_MODULE_CONTENT;
        }
    }

    /* module_info_header in the form of parsed structure */
    if (LC_SUCCESS == result && LC_NULL != pStModuleInfoHeader)
    {
        LC_memcpy(pStModuleInfoHeader, &mih_st, sizeof(mih_st));
    }
    else
    {
        MessageParser_FreeModuleInfoHeader(&mih_st);
    }

    /* module_info_header in the form of raw data */
    if (LC_SUCCESS == result && LC_NULL != pByteModuleInfoHeader)
    {
        LC_memcpy(pByteModuleInfoHeader, &mih_byte, sizeof(mih_byte));
    }
    else
    {
        LC_Free_Memory((void **)&mih_byte.bytes);
    }


    return result;

}


lc_result LC_VerifyModuleInfoHeaderSignature(
    const lc_checksum_algorithm_status *pStatus,
    const lc_buffer_st *pByteModuleInfoHeader, 
    const lc_module_info_header *pStModuleInfoHeader)
{
    lc_result result = LC_SUCCESS;
    lc_checksum_algorithm_status status;


    /* Verify header signature */
    
    /* None of BBCB, Loader Partition and Loader Core needs such verification.*/
    if ( (MODULE_DRV_ID_BBCB != pStModuleInfoHeader->module_id) &&
         (MODULE_DRV_ID_LOADER_PT != pStModuleInfoHeader->module_id) &&
         (MODULE_DRV_ID_LOADER_CORE != pStModuleInfoHeader->module_id) )
    {
        
        LC_memcpy(&status, pStatus, sizeof(lc_checksum_algorithm_status));

        /* Rsa key is not necessary for key module verification. */
        if (MODULE_DRV_ID_UK == pStModuleInfoHeader->module_id)
        {
            /* UK do not need RSA key for signature verification. */
            status.pRsaKey = (lc_uchar*)loaderEnhancedSecureKey;
        }
            
        /* Verify the module_info_header() before we trust it */
        if (LC_SUCCESS == result)
        {
            result = LC_VerifySignature(
                            &status,
                            &pByteModuleInfoHeader->bytes[0],/* start from the beginning of module_info_header */
                            pStModuleInfoHeader->header_length
                            - 2                    /* header_signature_length */
                            - 2                    /* module_signature_length */
                            - 4                    /* crc32 */
                            - pStModuleInfoHeader->module_signature_length
                            - pStModuleInfoHeader->header_signature_length,
                            pStModuleInfoHeader->header_signature_data);
            if(LC_SUCCESS != result)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "&[Module_mng] Error: Header signature for module #%u did not verify okey!\n",
                    pStModuleInfoHeader->module_id);
                                       
            }
        }

    }

    return result;
}


/** 
 * This functions read and verifies an specified module, if the 
 * module verifies ok LC_SUCCESS is returned
 */

lc_result LC_ReadAndVerifyExistingModule(
    lc_uint16 moduleId, 
    lc_bool bootcheck,
    lc_uchar bootcheckAlgorithm,
    lc_uchar *pKey,
    lc_module_info_header *pStModuleHeader,
    lc_buffer_st *pByteModuleHeader, 
    lc_buffer_st *pByteModulePayload)
{

    lc_result result = LC_SUCCESS;
    lc_module_info_header mih_st; 
    lc_buffer_st mih_byte = {LC_NULL, 0};
    lc_buffer_st mp_byte = {LC_NULL, 0};
    lc_checksum_algorithm_status status = {LC_BOOTCHECK_MIN_RESERVED, LC_NULL};

    LC_memset(&mih_st, 0, sizeof(lc_module_info_header));
    
    TRACE_LOG1(TRACE_INFO, "#[Module_mng] Verifying module #%u\n", moduleId);

	/* Get and parse module header */
    if (LC_SUCCESS == result)
    {
        result = LC_ReadAndParseModuleInfoHeader(moduleId, &mih_st, &mih_byte);
    }	
      
    /* Verify process */
    if (LC_SUCCESS == result)
    {
        if ( (LC_FALSE == bootcheck) ||
                ( LC_TRUE == bootcheck && 
                  LC_TRUE == mih_st.boot_check) )
        {
			/* Choose checksum algorithm */
            if (LC_SUCCESS == result)
            {
                /* Choose a checksum algorithm. */
                if (MODULE_DRV_ID_VARIANT == mih_st.module_id)
                {
                    status.algorithm = LC_BOOTCHECK_CRC32;
                }
                else
                {
                    status.algorithm = bootcheckAlgorithm;

                    if (LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION == bootcheckAlgorithm)
                    {
                        if (MODULE_DRV_ID_UK != mih_st.module_id)
                        {
                            status.pRsaKey = pKey;
                        }
						else
						{
							status.pRsaKey = (lc_uchar*)loaderEnhancedSecureKey;
						}
                    }
                }
            }
            
            /* Verify. */
            
            /*  step 1. verify the module header using module_header_signature */
            if (LC_SUCCESS == result)
            {
                result = LC_VerifyModuleInfoHeaderSignature(&status, &mih_byte, &mih_st);    //
            }
			
            /* step 2. Verify the module payload using module_signature_data */
            if (LC_SUCCESS == result)
            {
                result = LoaderCoreSPI_Module_ReadModulePayload(moduleId, &mp_byte);
                if( LC_SUCCESS !=  result)
                {
                    TRACE_LOG1(
                        TRACE_ERROR, 
                        "[Module_mng] Error reading module payload on checking the existing module #%u!\n",
                        moduleId);
                }
            }

            if (LC_SUCCESS == result)
            {
                
                /* None of BBCB, Loader Partition and Loader Core needs such verification.*/
                if ((MODULE_DRV_ID_BBCB != mih_st.module_id) &&
                    (MODULE_DRV_ID_LOADER_PT != mih_st.module_id) &&
                    (MODULE_DRV_ID_LOADER_CORE != mih_st.module_id) )
                {
                                           
                    result = LC_VerifySignature(
                                &status,
                                &mp_byte.bytes[0], 
                                mih_st.module_size, 
                                mih_st.module_signature);
                    if ( LC_SUCCESS != result )
                    {
                        TRACE_LOG1(
                            TRACE_ERROR, 
                            "[Module_mng] Error checking module payload on checking the existing module #%u!\n",
                            mih_st.module_id);
                    }

                }
                    
            }
            
        }
    
    }

    /* module_info_header in the form of parsed structure */
    if ((LC_SUCCESS == result && LC_NULL != pStModuleHeader) || 
        ( MODULE_DRV_ID_USERFS1 == moduleId && LC_NULL != pStModuleHeader) || 
	( MODULE_DRV_ID_USERFS2 == moduleId && LC_NULL != pStModuleHeader) )
    {
        LC_memcpy(pStModuleHeader, &mih_st, sizeof(mih_st));
    }
    else
    {
        MessageParser_FreeModuleInfoHeader(&mih_st);
    }

    /* module_info_header in the form of raw data */
    if (LC_SUCCESS == result && LC_NULL != pByteModuleHeader)
    {
        LC_memcpy(pByteModuleHeader, &mih_byte, sizeof(mih_byte));
    }
    else
    {
        LC_Free_Memory((void **)&mih_byte.bytes);
    }

    /* module payload in the form of raw data */
    if (LC_SUCCESS == result && LC_NULL != pByteModulePayload)
    {
        LC_memcpy(pByteModulePayload, &mp_byte, sizeof(mp_byte));
    }
    else
    {
        LC_Free_Memory((void **)&mp_byte.bytes);
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(TRACE_DEBUG, "[Module_mng] Module #%u verifyed OK\n", moduleId);
    }

    return result;

}

lc_result LC_GetVariant(lc_uint16 *pVariant, lc_uint16 *pSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_buffer_st mp_variant = {LC_NULL, 0};
    lc_uchar clearVariant[4];

    LC_memset(clearVariant, 0, sizeof(clearVariant));

    TRACE_LOG0(TRACE_DEBUG, ("[Module_mng] Get Variant\n"));

    if (LC_NULL == pVariant && LC_NULL == pSubVariant)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    /* Retrieve the Variant module */
    if (LC_SUCCESS == result)
    {
        result = LC_ReadAndVerifyExistingModule(
                    MODULE_DRV_ID_VARIANT, 
                    LC_FALSE,
                    LC_BOOTCHECK_CRC32, 
                    LC_NULL, 
                    LC_NULL,
                    LC_NULL,
                    &mp_variant);
        if (LC_SUCCESS != result)
        {
            TRACE_LOG0(TRACE_ERROR, ("[Module_mng] Error loading existing variant!\n"));
        }
    }

    /* Decrypt and Get clear variant and sub-variant */
    if (LC_SUCCESS == result)
    {
        result = LC_CryptModule(LC_FALSE, clearVariant, mp_variant.bytes, sizeof(clearVariant));
    }

    if (LC_SUCCESS == result)
    {
        if (LC_NULL != pVariant)
        {
            *pVariant = (lc_uint16)((clearVariant[0] << 8) | (clearVariant[1] & 0xFF)); 
        }

        if (LC_NULL != pSubVariant)
        {
            *pSubVariant = (lc_uint16)((clearVariant[2] << 8) | (clearVariant[3] & 0xFF)); 
        }
    }

    LC_Free_Memory((void **)&mp_variant.bytes);

    return result;

}

lc_result LC_SetVariant(lc_bool createNew, const lc_uint16 *pVariant, const lc_uint16 *pSubVariant)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_buffer_st module_header_byte = {LC_NULL, 0};
    lc_buffer_st module_payload_byte = {LC_NULL, 0};
    lc_buffer_st newModule = {LC_NULL, 0};
    lc_module_info_header mh_st_variant;
    lc_uchar clearVariant[4];
    lc_uint32 bitpos = 0;

    LC_memset(&mh_st_variant, 0, sizeof(lc_module_info_header));

    TRACE_LOG0(TRACE_DEBUG, ("[Module_mng] Set Variant\n"));

    if (LC_NULL == pVariant && LC_NULL == pSubVariant)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    /* Check variant value first. */
    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_IsVariantValid(pVariant, pSubVariant))
        {
            result = LC_FAILURE;
        }
    }

    /* Create a new variant module or Get the existing one. */
    if (LC_SUCCESS == result)
    {
        if (LC_TRUE == createNew)
        {      
            /* module_info_header */
            mh_st_variant.module_id = MODULE_DRV_ID_VARIANT;
            mh_st_variant.module_size = 4;
            mh_st_variant.module_version = 0;
            mh_st_variant.boot_check = 0x01;
            
            mh_st_variant.header_signature_length = SIGNATURE_LENGTH;
            mh_st_variant.header_signature_data = LC_MALLOC(mh_st_variant.header_signature_length);
            if (LC_NULL == mh_st_variant.header_signature_data)
            {
                result = LC_ERROR_INSUFFICIENT_BUFFER;
            }

            if (LC_SUCCESS == result)
            {
                mh_st_variant.module_signature_length = SIGNATURE_LENGTH;
                mh_st_variant.module_signature = LC_MALLOC(mh_st_variant.module_signature_length);
                if (LC_NULL == mh_st_variant.module_signature)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }
            }

            if (LC_SUCCESS == result)
            {
                mh_st_variant.header_length = TYPICAL_MODULE_INFO_HEADER_SIZE +
                                              mh_st_variant.header_signature_length +
                                              mh_st_variant.module_signature_length;
            }

            if (LC_SUCCESS == result)
            {
                module_header_byte.length = mh_st_variant.header_length;
                module_header_byte.bytes = LC_MALLOC(module_header_byte.length);
                if (LC_NULL == mh_st_variant.module_signature)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }

                if (LC_SUCCESS == result)
                {
                    module_payload_byte.length = mh_st_variant.module_size;
                    module_payload_byte.bytes = LC_MALLOC(module_payload_byte.length);
                    
                    if (LC_NULL == module_payload_byte.bytes)
                    {
                        result = LC_ERROR_INSUFFICIENT_BUFFER;
                    }
                }
            }

            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_CombineModuleInfoHeader(&module_header_byte, &bitpos, &mh_st_variant);
            }
        }
        else
        {
    
            /* Read Variant module. */
            if (LC_SUCCESS == result)
            {
                result = LC_ReadAndParseModuleInfoHeader(
                            MODULE_DRV_ID_VARIANT, 
                            &mh_st_variant, 
                            &module_header_byte);

                if (LC_SUCCESS == result)
                {
                    result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_VARIANT, &module_payload_byte);
                    if( LC_SUCCESS !=  result)
                    {
                        TRACE_LOG1(
                            TRACE_ERROR, 
                            "[Module_mng] Error reading module payload on checking the existing module #%u!\n",
                            MODULE_DRV_ID_VARIANT);
                    }
                }
            }

            /* If variant module exists, replace it with the new one. */
            if (LC_SUCCESS == result)
            {
                /* Get current variant. */
                result = LC_CryptModule(LC_FALSE, clearVariant, module_payload_byte.bytes, sizeof(clearVariant));  
            }
        }
    }

    
    /* Overwrite it if required. */
    if (LC_SUCCESS == result)
    {            
        if(LC_NULL != pVariant)
        {
            clearVariant[0] = (lc_uchar)(*pVariant >> 8);
            clearVariant[1] = (lc_uchar)(*pVariant >> 0);
        }

        if(LC_NULL != pSubVariant)
        {
            clearVariant[2] = (lc_uchar)(*pSubVariant >> 8);
            clearVariant[3] = (lc_uchar)(*pSubVariant >> 0);
        }

        TRACE_LOG0(TRACE_DEBUG, ("[MODULE_MNG] Encrypt variant before saving.\n"));
                            
        /* Encrypt and take the place of the field in variant module. */
        result = LC_CryptModule(
                    LC_TRUE,
                    module_payload_byte.bytes, 
                    clearVariant, 
                    sizeof(clearVariant));
    }
            

    /* Rebuild variant module. */
    if (LC_SUCCESS == result)
    {
        newModule.bytes = LC_MALLOC(mh_st_variant.header_length + mh_st_variant.module_size);
        newModule.length = mh_st_variant.header_length + mh_st_variant.module_size;
        if (LC_NULL == newModule.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }

        if (LC_SUCCESS == result)
        {
            LC_memcpy(
                &newModule.bytes[0], 
                module_header_byte.bytes, 
                mh_st_variant.header_length);
                
            LC_memcpy(
                &newModule.bytes[mh_st_variant.header_length], 
                module_payload_byte.bytes, 
                mh_st_variant.module_size);
        }
    }

    /* Update signature. */
    if (LC_SUCCESS == result)
    {
        result = LC_UpdateModuleSignature(LC_BOOTCHECK_CRC32, &newModule, &mh_st_variant);
    }

    /* Write the new one. */
    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_WriteModule(
                    MODULE_DRV_ID_VARIANT, 
                    &newModule );
        if( LC_SUCCESS != result )
        {
            TRACE_LOG1(TRACE_ERROR, "[MODULE_MNG] Error writing module #%u\n", MODULE_DRV_ID_VARIANT);
            errCode = ERROR_CODE_MODIFY_MODULE;
        }
    }

    /* Report Errorcode */
    ERR_REPORT_SetErrorCode(errCode);
    
    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(TRACE_DEBUG, "[Module_mng] Module #%u updated.\n", MODULE_DRV_ID_VARIANT);
    }

    MessageParser_FreeModuleInfoHeader(&mh_st_variant);
    LC_Free_Memory((void **)&module_header_byte.bytes);
    LC_Free_Memory((void **)&module_payload_byte.bytes);
    LC_Free_Memory((void **)&newModule.bytes);

    return result;
}

lc_result LC_GetAndCheckExistingModuleList(lc_uint16 **ppModuleIdList, lc_uint32 *pModuleIdCount)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 *pModuleList = LC_NULL;
    lc_uint32 moduleCount = 0;
    lc_uint32 cnt = 0;

    /* Get module list */
    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_GetModuleIdList(&pModuleList, &moduleCount);
    }

    if (LC_SUCCESS == result)
    {
        *ppModuleIdList = pModuleList;
        *pModuleIdCount = moduleCount;
    }
    else
    {
        ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_MODULE_LIST);
    }
    
    return result;
}


lc_result LC_SHAInit(lc_sha_controller *pSHAController)
{
    lc_result result = LC_SUCCESS;

    switch (pSHAController->mode)
    {
        case PKCS_SHA1_MODE:
        {
            sha1_init(&pSHAController->state.sha1);
            break;
        }
        case PKCS_SHA256_MODE:
        {
            sha256_init(&pSHAController->state.sha256);
            break;
        }

        default:
        {
            result = LC_ERROR_INVALID_PARAMETER;
            break;
        }
    }

    return result;

}


lc_result 
LC_SHAUpdate(
    lc_sha_controller *pSHAController, 
    const lc_uchar *pData,
    lc_uint32 length)
{

    lc_result result = LC_SUCCESS;

    switch (pSHAController->mode)
    {
        case PKCS_SHA1_MODE:
        {
            if( CRYPT_OK != sha1_process(
                                &pSHAController->state.sha1,
                                pData, 
                                length) )
            {
                result = LC_ERROR_INVALID_DATA;
            }
            break;
        }
        case PKCS_SHA256_MODE:
        {
            if(CRYPT_OK != sha256_process(
                                &pSHAController->state.sha256,
                                pData,
                                length) )
            {
                result = LC_ERROR_INVALID_DATA;
            }
            break;
        }

        default:
        {
            result = LC_ERROR_INVALID_PARAMETER;
            break;
        }
    }

    return result;
}


lc_result 
LC_SHAFinal(
    lc_sha_controller *pSHAController, 
    lc_uchar *pHashResult)
{
    /** Note: It is up to the user to ensure pHashResult have suffient buffer. */
    lc_result result = LC_SUCCESS;

    switch (pSHAController->mode)
    {
        case PKCS_SHA1_MODE:
        {
            if(CRYPT_OK != sha1_done(&pSHAController->state.sha1, pHashResult))
            {
                TRACE_LOG0(TRACE_ERROR, ("[Module_mng] Error: Failed to retrieve hash for buffer\n"));
                result = LC_FAILURE; /* unsupported sha mode */
            }
            break;
        }
        case PKCS_SHA256_MODE:
        {
            if(CRYPT_OK != sha256_done(&pSHAController->state.sha256, pHashResult))
            {
                TRACE_LOG0(TRACE_ERROR, ("[Module_mng] Error: Failed to retrieve hash for buffer\n"));
                result = LC_FAILURE; /* unsupported sha mode */
            }
            break;
        }

        default:
        {
            result = LC_ERROR_INVALID_PARAMETER;
            break;
        }
    }

    return result;
	
}    

lc_result 
LC_VerifySHASignature(
	lc_uchar* pRsaKey,
    pkcs_hash_mode hashMode, 
    const lc_uchar signatureClear[SIGNATURE_LENGTH], 
    lc_uchar* hash)
{
	lc_result result = LC_SUCCESS;
    pkcs_result pkcsRet = PKCS_ERROR_SUCCESS;
    lc_uint32 hashLength = 0;
    pkcs_buffer_st stHash = {LC_NULL, 0};


    if(LC_SUCCESS == result)
    {
        if(PKCS_SHA1_MODE == hashMode)
        {
            hashLength = LC_SHA1_HASH_LEN;
        }
        else if(PKCS_SHA256_MODE == hashMode)
        {
            hashLength = LC_SHA256_HASH_LEN;
        }
        else
        {
            result = LC_ERROR_INVALID_PARAMETER; /* unsupported sha mode */
        }
    }

    if(LC_SUCCESS == result)
    {
        stHash.bytes = hash;
        stHash.length = hashLength;
        pkcsRet = Rsa_VerifyPkcs(pRsaKey,signatureClear, &stHash);
        if(pkcsRet != PKCS_ERROR_SUCCESS)
        {
            TRACE_LOG0(TRACE_ERROR, ("[Module_mng] Error verifying PKCS Signature!\n"));
            result = LC_ERROR_INVALID_DATA;
        }
    }
    
    return result;
	
}


lc_bool LC_CheckVariant(lc_bool isSubVariant, lc_uint16 newValue, lc_uint16 oldValue)
{
    lc_bool match = LC_FALSE;

    if (LC_FALSE == match)
    {
        if(newValue == oldValue)
        {
            match = LC_TRUE;
        }
    }

    if (LC_FALSE == match)
    {
        if (LC_TRUE == isSubVariant)
        {
            /**
             * If the incoming sub-variant equals ZERO, that means this download can be applied to 
             * every client device regardless of its sub-variant even if it does not match 
             * the existing one. 
             */
            if (0 == newValue)
            {
                match = LC_TRUE;
            }            
        }    
    }
    return match;
}


