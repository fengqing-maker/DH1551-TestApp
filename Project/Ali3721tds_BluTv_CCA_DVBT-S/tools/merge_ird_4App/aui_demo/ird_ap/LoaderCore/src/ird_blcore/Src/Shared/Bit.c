/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : Bit.c                                                      *
*                                                                            *
*   Description : Message parser and combiner bit by bit .                   *
*                                                                            *
*****************************************************************************/

#include "LoaderCorePrivate.h"


#if 0
lc_uint32 LC_GetUint32(const lc_uchar *pBufffer, lc_uint32 offset)
{
    return (lc_uint32)( (pBufffer[offset]   << 24) | 
                        (pBufffer[offset+1] << 16) |
                        (pBufffer[offset+2] <<  8) | 
                        (pBufffer[offset+3])); 
}

lc_uint16 LC_GetUint16(const lc_uchar *pBufffer, lc_uint32 offset)
{
    return (lc_uint16)( (pBufffer[offset+0] <<  8) | 
                        (pBufffer[offset+1])); 
}



/**
 * Base helper method for parsing bitfields:
 *
 * pStart is the start of the buffer
 * pEnd is the end of the buffer
 * pBitPos on input, the current bit offset from pStart. On output, the new bit position.
 * bitlength is the number of bits to read from the buffer
 * pDest points to the destination of the data. Caller provides buffer that can hold the specified
 * bit length
 */

/**
 * Helper to read a single bit value
 */
static lc_uchar ReadBit(const lc_uchar *pPtr, lc_uint32 bitoffset)
{
    lc_uint32 byteoffset = bitoffset / 8;
    return (pPtr[byteoffset] & (1 << (7-(bitoffset % 8)))) ? 1 : 0;
}

/**
 * helper to write a single bit value
 */
static void WriteBit(lc_uchar *pPtr, lc_uint32 bitoffset, lc_uchar bitvalue)
{
    lc_uint32 byteoffset = bitoffset / 8;
    if (bitvalue)
    {
        pPtr[byteoffset] |= (1 << (7-(bitoffset % 8)));
    }
    else
    {
        pPtr[byteoffset] &= ~(1 << (7-(bitoffset % 8)));
    }
}


lc_result
MessageParser_ReadBits(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_uint32 bitlength,
    void *pDest)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 i = 0;
    lc_uchar *pCur = (lc_uchar *)pDest;

    if ((pBytes->length * 8) < (*pBitPos + bitlength))
    {
        result = LC_ERROR_INSUFFICIENT_BUFFER; /**< not enough bits left */
    }
    else
    {
        /**
         * Do a straight memcpy if data is fully byte-aligned.
         */
        if ((*pBitPos % 8) == 0 && (bitlength % 8) == 0)
        {
            LC_memcpy(
                pCur,
                pBytes->bytes + ((*pBitPos) / 8),
                bitlength / 8);

            (*pBitPos) += bitlength;
        }
        /**
         * If not, we'll do a slow bit-by-bit copy.
         */
        else
        {
            /**
             * Identify the startbit of the destination. For example, if you are reading 12 bits,
             * your destination is 16 bits, and you'll start writing bits at bit 4.
             */
            lc_uint32 startbit = (8 - (bitlength % 8)) % 8;

            /**
             * zero out the first bit
             */
            *pCur = 0;

            /**
             * Copy the data, bit by bit, from the source to the destination. 
             */
            for (i=0; i<bitlength; ++i)
            {
                WriteBit(pCur, startbit + i, ReadBit(pBytes->bytes, *pBitPos));
                ++*pBitPos;
            }
        }
    }

    return result;
}

lc_result
MessageParser_ReadBytes(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBytePos, 
    lc_uint32 bytelength,
    void *pDest)
{
    lc_result result = LC_SUCCESS;
    lc_uchar *pCur = (lc_uchar *)pDest;

    if ((pBytes->length) < (*pBytePos + bytelength))
    {
        result = LC_ERROR_INSUFFICIENT_BUFFER; /**< not enough bits left */
    }
    else
    {
        /**
         * Do a straight memcpy if data is fully byte-aligned.
         */
            LC_memcpy(
                pCur,
                pBytes->bytes + (*pBytePos),
                bytelength);
            (*pBytePos) += bytelength;
    }

    return result;
}    

/**
 * In-place Endian-independent functions for converting network byte order to Host order
 */
void N2H16(lc_uint16 *pNbo)
{
    lc_uchar *ptr = (lc_uchar *)pNbo;
    lc_uint16 ho = (((lc_uint16)ptr[0]) << 8) | ((lc_uint16)ptr[1]);
    *pNbo = ho;
}

void N2H32(lc_uint32 *pNbo)
{
    lc_uchar *ptr = (lc_uchar *)pNbo;
    lc_uint32 ho = (((lc_uint32)ptr[0]) << 24) | (((lc_uint32)ptr[1]) << 16) | (((lc_uint32)ptr[2]) << 8) | ((lc_uint32)ptr[3]);
    *pNbo = ho;
}


lc_result
MessageCombiner_WriteBits(
    const lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_uint32 bitlength,
    const void *pSrc )
{
    lc_result result = LC_SUCCESS;
    lc_uint32 i = 0;
    lc_uchar *pCur = (lc_uchar *)pSrc;

    if ((pBytes->length * 8) < (*pBitPos + bitlength))
    {
        result = LC_ERROR_INSUFFICIENT_BUFFER; /**< not enough bits left */
    }
    else
    {
        /**
         * Do a straight memcpy if data is fully byte-aligned.
         */
        if ((*pBitPos % 8) == 0 && (bitlength % 8) == 0)
        {
            LC_memcpy(
                pBytes->bytes + ((*pBitPos) / 8),
                pCur,
                bitlength / 8);

            (*pBitPos) += bitlength;
        }
        
        /**
         * If not, we'll do a slow bit-by-bit copy.
         */
        else
        {
            /**
             * Identify the startbit of the destination. For example, if you are reading 12 bits,
             * your destination is 16 bits, and you'll start writing bits at bit 4.
             */
            lc_uint32 startbit = *pBitPos;

            /**
             * Copy the data, bit by bit, from the source to the destination. 
             */
            for (i=0; i<bitlength; ++i)
            {
                WriteBit(pBytes->bytes, startbit + i, ReadBit(pCur, (7 - (i % 8)) % 8));
                ++*pBitPos;
            }
        }
    }

    return result;
}

/**
 * In-place Endian-independent functions for converting network byte order to Host order
 */
void H2N16(lc_uint16 *pNbo)
{
    N2H16(pNbo);
}

void H2N32(lc_uint32 *pNbo)
{
    N2H32(pNbo);
}


/* serial download */

lc_result
MessageParser_ParseSDPSerialDownloadPacket(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_serial_download_packet *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 startpos = 0;
    lc_module_dg_st datagram;

    LC_memset(&datagram, 0, sizeof(lc_module_dg_st));

    /** data_id (1 byte) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->data_id);
        if (UART_DLH_ID != pParsed->data_id &&
            UART_MH_ID != pParsed->data_id &&
            UART_DG_ID != pParsed->data_id )
        {
            result = LC_ERROR_INVALID_DATA;
        }
    }

    /** length (2 bytes) */
    if (LC_SUCCESS == result)
    {
        if (UART_DLH_ID == pParsed->data_id ||
            UART_MH_ID == pParsed->data_id )
        {
            result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->length);
            N2H16(&pParsed->length); /**< need to convert big-endian to host endian */

            if (LC_SUCCESS == result)
            {
                startpos = *pBitPos;
            }
        }
        else
        {
            startpos = *pBitPos;
            
            result = MessageParser_ParseDPDatagram(pBytes, pBitPos, &datagram);
            if (LC_SUCCESS == result)
            {
                /* module_id (2 bytes), data_length, data, crc16 */
                pParsed->length = datagram.data_length + 2 + 2 + 2;
            }

            *pBitPos = startpos;
        }
    }

    /** payload (n bytes) */
    if (LC_SUCCESS == result)
    {
        pParsed->payload = pBytes->bytes + (startpos / 8);
    }

    return result;
}


lc_result MessageParser_ParseSDPSerialDownloadPacketBytes(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBytesPos, 
    lc_serial_download_packet *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 startpos = 0;
    lc_module_dg_st datagram;

    LC_memset(&datagram, 0, sizeof(lc_module_dg_st));

    /** data_id (1 byte) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBytes(pBytes, pBytesPos, 1, &pParsed->data_id);
        if (UART_DLH_ID != pParsed->data_id &&
            UART_MH_ID != pParsed->data_id &&
            UART_DG_ID != pParsed->data_id )
        {
            result = LC_ERROR_INVALID_DATA;
        }
    }

    /** length (2 bytes) */
    if (LC_SUCCESS == result)
    {
        if (UART_DLH_ID == pParsed->data_id ||
            UART_MH_ID == pParsed->data_id )
        {
            result = MessageParser_ReadBytes(pBytes, pBytesPos, 2, &pParsed->length);
            N2H16(&pParsed->length); /**< need to convert big-endian to host endian */

            if (LC_SUCCESS == result)
            {
                startpos = *pBytesPos;
            }
        }
        else
        {
            startpos = *pBytesPos;
			
            result = MessageParser_ParseDPDatagramBytes(pBytes, pBytesPos, &datagram);
            if (LC_SUCCESS == result)
            {
                /* module_id (2 bytes), data_length, data, crc16 */
                pParsed->length = datagram.data_length + 2 + 2 + 2;
            }

            *pBytesPos = startpos;
        }
    }

    /** payload (n bytes) */
    if (LC_SUCCESS == result)
    {
        pParsed->payload = pBytes->bytes + startpos;
    }

    return result;
}

/* download protocol */

lc_result
MessageParser_ParseDPDownloadHeader(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_dlh_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint32 cnt = 0;


    /** manufacturer_id (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->manufacturer_id);
        N2H16(&pParsed->manufacturer_id); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
         TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> manufacturer_id = %d\n", 
            pParsed->manufacturer_id);
    }

    /** hardware_version (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->hardware_version);
        N2H16(&pParsed->hardware_version); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> hardware_version = %d\n", 
            pParsed->hardware_version);
    }

    /** loader_gte_v4 (1 bit), must be 0b0 for Loader V5 */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->loader_gte_v4);
    }

    /** loader_gte_v3 (1 bit), must be 0b0 for Loader V5 */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->loader_gte_v3);
    }

    /** loader_gte_v5 (1 bit), must be 0b1 for Loader V5 */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->loader_gte_v5);
    }

    if (LC_SUCCESS == result)
    {
        if (0x00 != pParsed->loader_gte_v4 ||
            0x00 != pParsed->loader_gte_v3 ||
            0x01 != pParsed->loader_gte_v5 )
        {
            TRACE_LOG3(
                TRACE_ERROR, 
                "[PARSER] <DH> Not a valid download for V5. \
                loader_gte_v4 = %u, \
                loader_gte_v3 = %u, \
                loader_gte_v5 = %u\n", 
                pParsed->loader_gte_v4, 
                pParsed->loader_gte_v3, 
                pParsed->loader_gte_v5);
            
            result = LC_ERROR_INVALID_DATA;
            errCode = ERROR_CODE_INVALID_DLH_NOT_GTE_V5;
        }
        
    }

    /** reserved (5 bits) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 5, &pParsed->reserved);
    }

    /** loader_minor_version (1 byte) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->loader_minor_version);
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> Loader minor version = %d\n", 
            pParsed->loader_minor_version);
    }

    /** download_id (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->download_id);
        N2H16(&pParsed->download_id); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> Download id = 0x%04x\n", 
            pParsed->download_id);
    }

    /** variant (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->variant);
        N2H16(&pParsed->variant); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> Variant = 0x%04x\n", 
            pParsed->variant);
    }

    /** sub_variant (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->sub_variant);
        N2H16(&pParsed->sub_variant); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> Sub Variant = 0x%04x\n", 
            pParsed->sub_variant);
    }

    /** isign_version (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, pParsed->isign_version);
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> bin2ird version = %s\n", 
            pParsed->isign_version);
    }

    /** isign_serial_number (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, pParsed->isign_serial_number);
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> bin2ird serial number = %s\n", 
            pParsed->isign_serial_number);
    }

    /** download_sequence_number (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->download_sequence_number);
        N2H16(&pParsed->download_sequence_number); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> Download_sequence_number = %u\n", 
            pParsed->download_sequence_number);
    }

    /** number_of_modules (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->number_of_modules);
        N2H16(&pParsed->number_of_modules); /**< need to convert big-endian to host endian */
        if (0 == pParsed->number_of_modules)
        {
            result = LC_ERROR_INVALID_DATA;
        }
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> Number of modules = %u:\n", 
            pParsed->number_of_modules);
    }

    if (LC_SUCCESS == result)
    {
        pParsed->pModuleIdList = LC_MALLOC((pParsed->number_of_modules) * sizeof(module_id_info_st));
        if (LC_NULL == pParsed->pModuleIdList)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    if (LC_SUCCESS == result)
    {
        for (cnt = 0; cnt < (pParsed->number_of_modules); cnt++ )
        {
            /** module_id (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->pModuleIdList[cnt].module_id);
                N2H16(&pParsed->pModuleIdList[cnt].module_id); /**< need to convert big-endian to host endian */
            }

            if (LC_SUCCESS == result)
            {
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <DH> ModuleId = 0x%04x\n", 
                    pParsed->pModuleIdList[cnt].module_id);
            }
            
            /** module_version (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->pModuleIdList[cnt].module_version);
                N2H16(&pParsed->pModuleIdList[cnt].module_version); /**< need to convert big-endian to host endian */
            }

            if (LC_SUCCESS == result)
            {
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <DH> ModuleVersion = 0x%04x\n", 
                    pParsed->pModuleIdList[cnt].module_version);
            }
        }

    }

    /** header_signature_length (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->header_signature_length);
        N2H16(&pParsed->header_signature_length); /**< need to convert big-endian to host endian */
    }

    /* Signature has a fixed size. */
    if (LC_SUCCESS == result)
    {
        if (SIGNATURE_LENGTH != pParsed->header_signature_length)
        {
            TRACE_LOG1(
                TRACE_ERROR, 
                "[BLOADER] Error in download header: Invalid header signature length, %u\n", 
                pParsed->header_signature_length);
            result = LC_ERROR_INVALID_DATA;
            errCode = ERROR_CODE_INVALID_SIG_LENGTH;
        }
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> header_signature_length = %u\n", 
            pParsed->header_signature_length);
    }

    if (LC_SUCCESS == result)
    {
        pParsed->header_signature = LC_MALLOC(pParsed->header_signature_length);
        if (LC_NULL == pParsed->header_signature)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }
    
    /** header_signature (header_signature_length bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, 
                            pBitPos, 
                            (8 * pParsed->header_signature_length), 
                            pParsed->header_signature);
    }

    /** download_signature_length (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->download_signature_length);
        N2H16(&pParsed->download_signature_length); /**< need to convert big-endian to host endian */
    }

    /* Signature has a fixed size. */
    if (LC_SUCCESS == result)
    {
        if (SIGNATURE_LENGTH != pParsed->download_signature_length)
        {
            TRACE_LOG1(
                TRACE_ERROR, 
                "[BLOADER] Error in download header: Invalid global signature length, %u\n", 
                pParsed->download_signature_length);
            result = LC_ERROR_INVALID_DATA;
            errCode = ERROR_CODE_INVALID_SIG_LENGTH;
        }
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> download_signature_length = %d\n", 
            pParsed->download_signature_length);
    }

    if (LC_SUCCESS == result)
    {
        pParsed->download_signature = LC_MALLOC(pParsed->download_signature_length);
        if (LC_NULL == pParsed->download_signature)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }
    
    /** header_signature (header_signature_length bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, 
                            pBitPos, 
                            (8 * pParsed->download_signature_length), 
                            pParsed->download_signature);
    }

    /** crc16 (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->crc16);
        N2H16(&pParsed->crc16); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DH> crc16 = 0x%04x\n", 
            pParsed->crc16);
    }

    /* Report Errorcode */
    ERR_REPORT_SetErrorCode(errCode);

    return result;
}


lc_result
MessageParser_FreeDPDownloadHeader( 
    lc_module_dlh_st *pParsed)
{
    lc_result result = LC_SUCCESS;

    if (LC_NULL == pParsed)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        LC_Free_Memory((void **)&pParsed->pModuleIdList);
        LC_Free_Memory((void **)&pParsed->header_signature);
        LC_Free_Memory((void **)&pParsed->download_signature);
    }

    return result;
}

lc_result
MessageParser_ParseDPModuleHeader(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_mh_st *pParsed)
{
    lc_result result = LC_SUCCESS;

    
    /** module_id (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->module_id);
        N2H16(&pParsed->module_id); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> Module id 0x%04x\n", 
            pParsed->module_id);
    }

    /** compressed (1 bit) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->compressed);
        pParsed->compressed = (0 == pParsed->compressed)? LC_FALSE : LC_TRUE;
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> Compressed %d\n", 
            pParsed->compressed);
    }

    /** obscured (1 bit) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->obscured);
        pParsed->obscured = (0 == pParsed->obscured)? LC_FALSE : LC_TRUE;
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> Obscured %d\n", 
            pParsed->obscured);
    }

    /** encrypted (1 bit) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->encrypted);
        pParsed->encrypted = (0 == pParsed->encrypted)? LC_FALSE : LC_TRUE;
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> Encrypted %d\n", 
            pParsed->encrypted);
    }

    /** reserved (5 bits) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 5, &pParsed->reserved);
    }

    /** original_size (4 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->original_size);
        N2H32(&pParsed->original_size); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> original_size = 0x%x\n", 
            pParsed->original_size);
    }

    if ( LC_TRUE == pParsed->compressed )
    {
        /** compressed_size (4 bytes) */
        if (LC_SUCCESS == result)
        {
            result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->compressed_size);
            N2H32(&pParsed->compressed_size); /**< need to convert big-endian to host endian */
        }

        if (LC_SUCCESS == result)
        {
            TRACE_LOG1(
                TRACE_DEBUG, "[PARSER] <MH> compressed_size = 0x%x\n", 
                pParsed->compressed_size);
        }

        /** C_CRC_32 (4 bytes) */
        if (LC_SUCCESS == result)
        {
            result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->crc32);
            N2H32(&pParsed->crc32); /**< need to convert big-endian to host endian */
        }

        if (LC_SUCCESS == result)
        {
            TRACE_LOG1(
                TRACE_DEBUG, 
                "[PARSER] <MH> crc32 = 0x%x\n", 
                pParsed->crc32);
        }
    }

    /** block_size (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->block_size);
        N2H16(&pParsed->block_size); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> Block_size = 0x%x\n", 
            pParsed->block_size);
    }

    /** block_count (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->block_count);
        N2H16(&pParsed->block_count); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> Block_count = %d\n", 
            pParsed->block_count);
    }

    /** CRC16 (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->crc16);
        N2H16(&pParsed->crc16); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MH> CRC16 = 0x%04x\n", 
            pParsed->crc16);
    }

    return result;
}


lc_result
MessageParser_ParseDPDatagram(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_dg_st *pParsed)
{
    lc_result result = LC_SUCCESS;


    /** module_id (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->module_id);
        N2H16(&pParsed->module_id); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DG> module id = 0x%04x\n", 
            pParsed->module_id);
    }

    /** data_length (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->data_length);
        N2H16(&pParsed->data_length); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DG> data_length = %u\n", 
            pParsed->data_length);
    }

    if (LC_SUCCESS == result)
    {
        pParsed->data_byte = &pBytes->bytes[(*pBitPos)/8];
        /* skip this buffer */
        *pBitPos += 8 * pParsed->data_length;
    }
    
    /** CRC16 (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->crc16);
        N2H16(&pParsed->crc16); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DG> crc16 = 0x%04x\n", 
            pParsed->crc16);
    }

    return result;
}    


 lc_result MessageParser_ParseDPDatagramBytes(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBytePos, 
    lc_module_dg_st *pParsed)
{
    lc_result result = LC_SUCCESS;


    /** module_id (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBytes(pBytes, pBytePos, 2, &pParsed->module_id);
        N2H16(&pParsed->module_id); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DG> module id = 0x%04x\n", 
            pParsed->module_id);
    }

    /** data_length (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBytes(pBytes, pBytePos, 2, &pParsed->data_length);
        N2H16(&pParsed->data_length); /**< need to convert big-endian to host endian */
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DG> data_length = %u\n", 
            pParsed->data_length);
    }

    if (LC_SUCCESS == result)
    {
        pParsed->data_byte = &pBytes->bytes[*pBytePos];
        /* skip this buffer */
        *pBytePos += pParsed->data_length;
    }
    
    /** CRC16 (2 bytes) */
    if (LC_SUCCESS == result)
    {          
        result = MessageParser_ReadBytes(pBytes, pBytePos, 2, &pParsed->crc16);
        N2H16(&pParsed->crc16); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DG> crc16 = 0x%04x\n", 
            pParsed->crc16);
    }

    return result;
}
	
lc_result
MessageParser_ParseModuleInfoHeader(
    lc_bool atDownloadPhase, 
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_info_header *pParsed)
{
    lc_result result = LC_SUCCESS;


    /** module_id (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->module_id);
        N2H16(&pParsed->module_id); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MIH> module id = 0x%04x\n", 
            pParsed->module_id);
    }

    /** header_length (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->header_length);
        N2H16(&pParsed->header_length); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MIH> header length = %u\n", 
            pParsed->header_length);
    }

    /** module_size (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->module_size);
        N2H32(&pParsed->module_size); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MIH> module size = %u\n", 
            pParsed->module_size);

        if (MODULE_DRV_ID_VARIANT == pParsed->module_id)
        {
            /* fixed size of 4 bytes(2 bytes for variant, 2 bytes for sub-variant) for variant module */
            if (4 != pParsed->module_size)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "[PARSER] <MIH> Invalid module size = %u, variant module has a fixed module size: 4 bytes. \n", 
                    pParsed->header_length);
                    
                result = LC_ERROR_INVALID_DATA;
            }
        }
    }


    /* segments below are not applicable for BBCB, Loader Core and Loader Partition */
    if (LC_SUCCESS == result)
    {
        if (MODULE_DRV_ID_BBCB != pParsed->module_id &&
            MODULE_DRV_ID_LOADER_PT != pParsed->module_id &&
            MODULE_DRV_ID_LOADER_CORE != pParsed->module_id)
        {
            /** boot_check (1 bit) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->boot_check);
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> boot check = %u\n", 
                    pParsed->boot_check);
            }
            
            /** addressable (1 bit) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 1, &pParsed->addressable);
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> addressable = %u\n", 
                    pParsed->addressable);
            }
            
            /** reserved (6 bits) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 6, &pParsed->reserved);
            }
            
            /** module_version (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->module_version);
                N2H16(&pParsed->module_version); /**< need to convert big-endian to host endian */
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> module version = 0x%04x\n", 
                    pParsed->module_version);
            }
            
            /** variant (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->variant);
                N2H16(&pParsed->variant); /**< need to convert big-endian to host endian */
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> variant = 0x%04x\n", 
                    pParsed->variant);
            }
            
            /** sub_variant (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->sub_variant);
                N2H16(&pParsed->sub_variant); /**< need to convert big-endian to host endian */
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> sub variant = 0x%04x\n", 
                    pParsed->sub_variant);
            }
            
            /** download_sequence_number (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->download_sequence_number);
                N2H16(&pParsed->download_sequence_number); /**< need to convert big-endian to host endian */
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> download seq num = 0x%04x\n", 
                    pParsed->download_sequence_number);
            }
            
            /** memory_type (1 byte) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->memory_type);
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> memory type = 0x%02x\n", 
                    pParsed->memory_type);
            }
            
            /** start_address (4 bytes), only applicable when addressable = 1 */
            if (LC_SUCCESS == result)
            {
                if (0x01 == pParsed->addressable)
                {
                    result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->start_address);
                    N2H32(&pParsed->start_address); /**< need to convert big-endian to host endian */
                    TRACE_LOG1(
                        TRACE_DEBUG, 
                        "[PARSER] <MIH> start address = 0x%08x\n", 
                        pParsed->start_address);
                }
            }
            
            /** header_signature_length (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->header_signature_length);
                N2H16(&pParsed->header_signature_length); /**< need to convert big-endian to host endian */
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> header signature length = 0x%04x\n", 
                    pParsed->header_signature_length);
            }

            /* Signature has a fixed size. */
            if (LC_SUCCESS == result)
            {
                if (LC_TRUE == atDownloadPhase)
                {
                    if (SIGNATURE_LENGTH != pParsed->header_signature_length)
                    {
                        TRACE_LOG2(
                            TRACE_ERROR, 
                            "[BLOADER] Error updating module #%u: Invalid header signature length, %u\n", 
                            pParsed->module_id,
                            pParsed->header_signature_length);
                        result = LC_ERROR_INCORRECT_SIGNATURE_LENGTH;
                    }
                }
            }

            if (LC_SUCCESS == result)
            {
                if (0 != pParsed->header_signature_length)
                {
                    if (LC_SUCCESS == result)
                    {
                        pParsed->header_signature_data = LC_MALLOC(pParsed->header_signature_length);
                        if (LC_NULL == pParsed->header_signature_data)
                        {
                            result = LC_ERROR_INSUFFICIENT_BUFFER;
                        }
                    }
                    
                    /** header_signature_data (header_signature_length bytes) */
                    if (LC_SUCCESS == result)
                    {
                        result = MessageParser_ReadBits(pBytes, 
                                            pBitPos, 
                                            (8 * pParsed->header_signature_length), 
                                            pParsed->header_signature_data);
                    }
                }
            }
            
            /** module_signature_length (2 bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->module_signature_length);
                N2H16(&pParsed->module_signature_length); /**< need to convert big-endian to host endian */
                TRACE_LOG1(
                    TRACE_DEBUG, 
                    "[PARSER] <MIH> module signature length = 0x%04x\n", 
                    pParsed->module_signature_length);
            }

            /* Signature has a fixed size. */
            if (LC_SUCCESS == result)
            {
                if (LC_TRUE == atDownloadPhase)
                {
                    if (SIGNATURE_LENGTH != pParsed->module_signature_length)
                    {
                        TRACE_LOG2(
                            TRACE_ERROR, 
                            "[BLOADER] Error updating module #%u: Invalid module signature length, %u\n", 
                            pParsed->module_id,
                            pParsed->module_signature_length);
                        result = LC_ERROR_INCORRECT_SIGNATURE_LENGTH;
                    }
                }
            }

            if (LC_SUCCESS == result)
            {
                if (0 != pParsed->module_signature_length)
                {
                    if (LC_SUCCESS == result)
                    {
                        pParsed->module_signature = LC_MALLOC(pParsed->module_signature_length);
                        if (LC_NULL == pParsed->module_signature)
                        {
                            result = LC_ERROR_INSUFFICIENT_BUFFER;
                        }
                    }
                    
                    /** module_signature (module_signature_length bytes) */
                    if (LC_SUCCESS == result)
                    {
                        result = MessageParser_ReadBits(pBytes, 
                                            pBitPos, 
                                            (8 * pParsed->module_signature_length), 
                                            pParsed->module_signature);
                    }
                }
            }
        }
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->crc32);
        N2H32(&pParsed->crc32); /**< need to convert big-endian to host endian */
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <MIH> crc32 = 0x%08x\n", 
            pParsed->crc32);
    }

    return result;
}


lc_result
MessageParser_FreeModuleInfoHeader( 
    lc_module_info_header *pParsed)
{
    lc_result result = LC_SUCCESS;

    if (LC_NULL == pParsed)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        LC_Free_Memory((void **)&pParsed->header_signature_data);
        LC_Free_Memory((void **)&pParsed->module_signature);
    }

    return result;
}

lc_result
MessageCombiner_CombineModuleInfoHeader(
    const lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    const lc_module_info_header *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_module_info_header parsed;
    
    lc_uint32 startingBitPos = *pBitPos;

    LC_memcpy(&parsed, pParsed, sizeof(lc_module_info_header));

    /** module_id (2 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.module_id); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.module_id);
    }

    /** header_length (2 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.header_length); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.header_length);
    }

    /** module_size (4 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N32(&parsed.module_size); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 32, &parsed.module_size);
    }

    /* segments below are not applicable for BBCB, Loader Core and Loader Partition */
    if (LC_SUCCESS == result)
    {
        if (MODULE_DRV_ID_BBCB != pParsed->module_id &&
            MODULE_DRV_ID_LOADER_PT != pParsed->module_id &&
            MODULE_DRV_ID_LOADER_CORE != pParsed->module_id)
        {
            /** boot_check (1 bit) */
            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 1, &parsed.boot_check);
            }
            
            /** addressable (1 bit) */
            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 1, &parsed.addressable);
            }
            
            /** reserved (6 bits) */
            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 6, &parsed.reserved);
            }
            
            /** module_version (2 bytes) */
            if (LC_SUCCESS == result)
            {
                H2N16(&parsed.module_version); /**< need to convert host endian to big-endian */
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.module_version);
            }
            
            /** variant (2 bytes) */
            if (LC_SUCCESS == result)
            {
                H2N16(&parsed.variant); /**< need to convert host endian to big-endian */
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.variant);
            }
            
            /** sub_variant (2 bytes) */
            if (LC_SUCCESS == result)
            {
                H2N16(&parsed.sub_variant); /**< need to convert host endian to big-endian */
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.sub_variant);
            }
            
            /** download_sequence_number (2 bytes) */
            if (LC_SUCCESS == result)
            {
                H2N16(&parsed.download_sequence_number); /**< need to convert host endian to big-endian */
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.download_sequence_number);
            }
            
            /** memory_type (1 byte) */
            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 8, &parsed.memory_type);
            }
            
            /** start_address (4 bytes), only applicable when addressable = 1 */
            if (LC_SUCCESS == result)
            {
                if (0x01 == pParsed->addressable)
                {
                    H2N32(&parsed.start_address); /**< need to convert host endian to big-endian */
                    result = MessageCombiner_WriteBits(pBytes, pBitPos, 32, &parsed.start_address);
                }
            }
            
            /** header_signature_length (2 bytes) */
            if (LC_SUCCESS == result)
            {
                H2N16(&parsed.header_signature_length); /**< need to convert host endian to big-endian */
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.header_signature_length);
            }
                        
            /** header_signature_data (header_signature_length bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_WriteBits(
                            pBytes, 
                            pBitPos, 
                            (8 * pParsed->header_signature_length), 
                            parsed.header_signature_data);
            }
            
            /** module_signature_length (2 bytes) */
            if (LC_SUCCESS == result)
            {
                H2N16(&parsed.module_signature_length); /**< need to convert host endian to big-endian */
                result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.module_signature_length);
            }
                        
            /** module_signature (module_signature_length bytes) */
            if (LC_SUCCESS == result)
            {
                result = MessageCombiner_WriteBits(
                            pBytes, 
                            pBitPos, 
                            (8 * pParsed->module_signature_length), 
                            parsed.module_signature);
            }
        }
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        /* re-calculate and fill the 4 bytes "crc32 field" */
        parsed.crc32 = CRC_Code32(&pBytes->bytes[0], (*pBitPos - startingBitPos) / 8);
        H2N32(&parsed.crc32); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 32, &parsed.crc32);
	    
    }

    /* check header length */
    if (LC_SUCCESS == result)
    {
        LC_ASSERT((lc_uint16)((*pBitPos - startingBitPos) / 8) 
                        == pParsed->header_length);
    }

    return result;
}



lc_result
MessageParser_ParseBBCB(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_bbcb_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    

    /** OUI (3 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 24, pParsed->OUI);
    }

    /** manufacturer_id (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->manufacturer_id);
        N2H16(&pParsed->manufacturer_id); /**< need to convert big-endian to host endian */
    }

    /** hardware_version (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->hardware_version);
        N2H16(&pParsed->hardware_version); /**< need to convert big-endian to host endian */
    }

    /** loader_major_version (1 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->loader_major_version);
    }

    if (LC_SUCCESS == result)
    {
        if ( 0x05 != pParsed->loader_major_version )
        {
            result = LC_ERROR_INVALID_DATA;
        }
    }

    /** loader_minor_version (1 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->loader_minor_version);
    }

    /** loader_version_buildnumber (12 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->loader_version_buildnumber);
        N2H16(&pParsed->loader_version_buildnumber); /**< need to convert big-endian to host endian */
    }

    /** boot_check_algorithm (1 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->boot_check_algorithm);
    }

    if (LC_SUCCESS == result)
    {
        if ( LC_CHECKSUM_ALGORITHM_MIN_RESERVED <= (lc_checksum_algorithm)pParsed->boot_check_algorithm )
        {
            result = LC_ERROR_INVALID_DATA;
        }
    }

    /** serial_number (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, pParsed->serial_number);
    }

    /** random_number (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, pParsed->random_number);
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->crc32);
        N2H32(&pParsed->crc32); /**< need to convert big-endian to host endian */
    }
    

    return result;
}


lc_result
MessageParser_ParseOtaDownloadParameters(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_ota_dl_para_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    

    /** ipInfo.address (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->ipInfo.address);
        N2H32(&pParsed->ipInfo.address); /**< need to convert big-endian to host endian */
    }

    /** ipInfo.port (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->ipInfo.port);
        N2H16(&pParsed->ipInfo.port); /**< need to convert big-endian to host endian */
    }

    /** dvbssuInfo.pid (13 bits) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->dvbssuInfo.pid);
        N2H16(&pParsed->dvbssuInfo.pid); /**< need to convert big-endian to host endian */
        pParsed->dvbssuInfo.pid &= 0x1FFF;  /* low 13 bits */
    }

    /** privateInfo (LC_MANUFACTURER_PRIVATE_INFO_LENGTH bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(
                    pBytes, 
                    pBitPos, 
                    8 * LC_MANUFACTURER_PRIVATE_INFO_LENGTH, 
                    pParsed->privateInfo);
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->crc32);
        N2H32(&pParsed->crc32); /**< need to convert big-endian to host endian */
    }

    return result;
}    

lc_result
MessageCombiner_CombineOtaDownloadParameters(
    lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_ota_dl_para_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_ota_dl_para_st parsed;
    
    lc_uint32 startingBitPos = *pBitPos;
    
    LC_memcpy(&parsed, pParsed, sizeof(lc_ota_dl_para_st));

    /** ipInfo.address (4 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N32(&parsed.ipInfo.address); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 32, &parsed.ipInfo.address);
    }

    /** ipInfo.port (2 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.ipInfo.port); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.ipInfo.port);
    }

    /** dvbssuInfo.pid (13 bits) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.dvbssuInfo.pid); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.dvbssuInfo.pid);
    }
    
    /** privateInfo (LC_MANUFACTURER_PRIVATE_INFO_LENGTH bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_WriteBits(
                    pBytes, 
                    pBitPos, 
                    8 * LC_MANUFACTURER_PRIVATE_INFO_LENGTH, 
                    &parsed.privateInfo);
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        /* re-calculate and fill the 4 bytes "crc32 field" */
	                        
        parsed.crc32 = CRC_Code32(&pBytes->bytes[startingBitPos / 8], (*pBitPos - startingBitPos) / 8);
        pParsed->crc32 = parsed.crc32;  /* Update and return the new crc32. */
        H2N32(&parsed.crc32); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 32, &parsed.crc32);

    }

    return result;
}

lc_result
MessageParser_ParseSharedMemory(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_shared_memory_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    

    /** downloadIndicator (1 byte) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->downloadIndicator);
    }

    /** reserved (1 byte) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 8, &pParsed->reserved);
    }

    /** OTA download parameters (n bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ParseOtaDownloadParameters(pBytes, pBitPos, &pParsed->otaDownloadPara);
    }

    /** migrationInfo.variant (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->migrationInfo.variant);
        N2H16(&pParsed->migrationInfo.variant); /**< need to convert big-endian to host endian */
    }

    /** migrationInfo.subvariant (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->migrationInfo.subvariant);
        N2H16(&pParsed->migrationInfo.subvariant); /**< need to convert big-endian to host endian */
    }

    return result;
}    


lc_result
MessageCombiner_CombineSharedMemory(
    lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_shared_memory_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_shared_memory_st parsed;
        
    LC_memcpy(&parsed, pParsed, sizeof(lc_shared_memory_st));

    /** downloadIndicator (1 byte) */
    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 8, &parsed.downloadIndicator);
    }

    /** reserved (1 byte) */
    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 8, &parsed.reserved);
    }

    /** OTA download parameters (n bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_CombineOtaDownloadParameters(pBytes, pBitPos, &parsed.otaDownloadPara);
    }

    /** migrationInfo.variant (2 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.migrationInfo.variant); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.migrationInfo.variant);
    }

    /** migrationInfo.subvariant (2 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.migrationInfo.subvariant); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.migrationInfo.subvariant);
    }

    return result;
}    


lc_result
MessageParser_ParseLoaderPt(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_loader_pt_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    
    result = MessageParser_ParseSharedMemory(pBytes, pBitPos, &pParsed->sharedMemory);

    if (LC_SUCCESS == result)
    {
        result = MessageParser_ParseDownloadInfo(pBytes, pBitPos, &pParsed->downloadInfo);
    }
    

    return result;
}    

lc_result
MessageParser_ParseDownloadInfo(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_last_download_info_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    
    /** isign_version (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, pParsed->isign_version);
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DI> bin2ird version = %s\n", 
            pParsed->isign_version);
    }

    /** isign_serial_number (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, pParsed->isign_serial_number);
        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DI> bin2ird serial number = %s\n", 
            pParsed->isign_serial_number);
    }

    /** download_sequence_number (2 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 16, &pParsed->download_sequence_number);
        N2H16(&pParsed->download_sequence_number); /**< need to convert big-endian to host endian */

        TRACE_LOG1(
            TRACE_DEBUG, 
            "[PARSER] <DI> Download_sequence_number = %u\n", 
            pParsed->download_sequence_number);
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pBytes, pBitPos, 32, &pParsed->crc32);
        N2H32(&pParsed->crc32); /**< need to convert big-endian to host endian */
    }

    return result;
}    


lc_result
MessageCombiner_CombineDownloadInfo( 
    lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_last_download_info_st *pParsed)
{
    lc_result result = LC_SUCCESS;
    lc_last_download_info_st parsed;
    
    lc_uint32 startingBitPos = *pBitPos;
    
    LC_memcpy(&parsed, pParsed, sizeof(lc_last_download_info_st));
    

    /** isign_version (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_WriteBits(
                    pBytes, 
                    pBitPos, 
                    8 * sizeof(parsed.isign_version), 
                    &parsed.isign_version);
    }

    /** isign_serial_number (4 bytes) */
    if (LC_SUCCESS == result)
    {
        result = MessageCombiner_WriteBits(
                    pBytes, 
                    pBitPos, 
                    8 * sizeof(parsed.isign_serial_number), 
                    &parsed.isign_serial_number);
    }

    /** download_sequence_number (2 bytes) */
    if (LC_SUCCESS == result)
    {
        H2N16(&parsed.download_sequence_number); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 16, &parsed.download_sequence_number);
    }

    /** crc32 (4 bytes) */
    if (LC_SUCCESS == result)
    {
        /* re-calculate and fill the 4 bytes "crc32 field" */
        parsed.crc32 = CRC_Code32(&pBytes->bytes[startingBitPos / 8], (*pBitPos - startingBitPos) / 8);
        pParsed->crc32 = parsed.crc32;  /* Update and return the new crc3.2 */
        H2N32(&parsed.crc32); /**< need to convert host endian to big-endian */
        result = MessageCombiner_WriteBits(pBytes, pBitPos, 32, &parsed.crc32);

    }

    return result;
}



/* TODO: move to other file like debug.c ? */

lc_result LC_CheckType_Bytes(
    const lc_buffer_st *pBytes )
{
    lc_result result = LC_SUCCESS;
    
    /* Verify the input paramaters */
    if(LC_NULL == pBytes)
    {
        TRACE_LOG0(TRACE_ERROR, ("[DBG] Check input parameters: Error, LC_ERROR_NULL_PARAM.\n"));
        result = LC_ERROR_NULL_PARAM;
    } 
    
    if (LC_SUCCESS == result)
    {
        if(LC_NULL == pBytes->bytes || 0 == pBytes->length)
        {
            TRACE_LOG0(TRACE_ERROR, ("[DBG] Check input parameters: Error, LC_ERROR_MISSING_DATA.\n"));
            result = LC_ERROR_MISSING_DATA;
        }
    }

    return result;
}    

void LC_Free_Memory( void **ppMem )
{  
//  if((LC_NULL != *ppMem))
    if( (LC_NULL != ppMem) &&  (LC_NULL != *ppMem)) //amu debug
    {
        LoaderCoreSPI_Memory_Free(*ppMem);
        *ppMem = LC_NULL;
    }
}


void* LC_MALLOC(lc_uint32 bufferSize)
{
    void *pBuffer = LoaderCoreSPI_Memory_Malloc(bufferSize);
    LC_ASSERT(pBuffer);
    if(pBuffer)
    {
        /*Init it.*/
        LC_memset(pBuffer, 0x0, bufferSize);
    }
    else
    {
        TRACE_LOG0(TRACE_FATAL, "[DBG] Not enough memory!!!")
    }

    return pBuffer;
}
#endif


