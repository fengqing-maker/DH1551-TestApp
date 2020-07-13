/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : Bbcb.c                                                     *
*                                                                            *
*   Description : Boot Block Control Block handling.                         *
*                                                                            *
*****************************************************************************/

#include "LoaderCorePrivate.h"


lc_result BBCB_GetBBCB(lc_bbcb_st *pBBCB, lc_bool *pIsCrcCorrect)
{
    lc_result result = LC_SUCCESS;
    lc_buffer_st mp_byte_bbcb = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_bbcb_st bbcbSt;
    lc_uint32 crc32 = 0;
    lc_buffer_st mp_byte_bl = {LC_NULL, 0};

    LC_memset(&bbcbSt, 0, sizeof(lc_bbcb_st));

    if (LC_NULL == pBBCB)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_Module_ReadModulePayload(MODULE_DRV_ID_BBCB, &mp_byte_bbcb);
    }

    if (LC_SUCCESS == result)
    {
        bitpos = 0;
        result = MessageParser_ParseBBCB(
                            &mp_byte_bbcb,
                            &bitpos, 
                            &bbcbSt );
    }

    /* Verify whether CRC32 is correct (optional). */
    if (LC_SUCCESS == result)
    {    
        if (LC_NULL != pIsCrcCorrect)
        {
            *pIsCrcCorrect = LC_FALSE;
            bitpos = 0;

            if( LC_SUCCESS == result)
            {
                result = LoaderCoreSPI_Module_ReadModulePayload(
                            MODULE_DRV_ID_LOADER_CORE, 
                            &mp_byte_bl);
            }            
            
            if( LC_SUCCESS == result)
            {

                /* calculate CRC32 */
                
                /* 1. BBCB itself */
                crc32 = CRC_Code32(&mp_byte_bbcb.bytes[0], mp_byte_bbcb.length - 4);

                /*2. Boot strap and boot loader images are also needed for CRC calculation..*/
                crc32 = CRC_Code32_Seq(mp_byte_bl.bytes, mp_byte_bl.length, crc32);
                
				libc_printf("CRC: <%s:%d> crc32 = 0x%x,bbcbSt.crc32 = 0x%x\n", __func__, __LINE__,crc32,bbcbSt.crc32);
                
                /* make comparison */
                if(crc32 == bbcbSt.crc32)
                {
                    *pIsCrcCorrect = LC_TRUE;
                }  
            }

            /* clear memory blocks */
            LC_Free_Memory((void **)&mp_byte_bl.bytes);
        }
    }

    /* output bbcb struct */
    if (LC_SUCCESS == result)
    {
        LC_memcpy(pBBCB, &bbcbSt, sizeof(lc_bbcb_st));
    }

    /* clear memory blocks */
    LC_Free_Memory((void **)&mp_byte_bbcb.bytes);

    return result;
}


lc_result BBCB_SetBBCB(lc_bool updateCRC, const lc_bbcb_st *pBBCB)
{
    lc_result result = LC_SUCCESS;
    lc_buffer_st mp_byte_bl = {LC_NULL, 0};
    lc_buffer_st module_byte_bbcb = {LC_NULL, 0};
    lc_module_info_header mh_st_bbcb;
    lc_uchar *pBuffer = LC_NULL;
    lc_uint32 cnt = 0;
    lc_uint32 crc32 = 0;
    
    LC_memset(&mh_st_bbcb, 0, sizeof(lc_module_info_header));
    
    if (LC_NULL == pBBCB)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if( LC_SUCCESS == result)
    {
        /* Read and verify the Loader Core module. */
        if (LC_SUCCESS == result)
        {
            if(LC_TRUE == updateCRC)
            {
                result = LoaderCoreSPI_Module_ReadModulePayload(
                        MODULE_DRV_ID_LOADER_CORE, 
                        &mp_byte_bl);
            }
        }

        /* BBCB module has a fixed module_info_header */
        if( LC_SUCCESS == result)
        {
            mh_st_bbcb.module_id = MODULE_DRV_ID_BBCB;
            mh_st_bbcb.header_length = SHORT_MODULE_INFO_HEADER_SIZE;
            mh_st_bbcb.module_size = 24;
        }

        if (LC_SUCCESS == result)
        {
            pBuffer = (lc_uchar *)LC_MALLOC(
                                    mh_st_bbcb.header_length
                                    + mh_st_bbcb.module_size );
            if (LC_NULL == pBuffer)
            {
                result = LC_ERROR_INSUFFICIENT_BUFFER;
            }
        }

        /* convert the parameters into module format */
        if (LC_SUCCESS == result)
        {
            lc_buffer_st bbcb_bytes;
            lc_uint32 bitpos = 0;
            bbcb_bytes.bytes = pBuffer;
            bbcb_bytes.length = mh_st_bbcb.header_length
                                    + mh_st_bbcb.module_size;
            result = MessageCombiner_CombineModuleInfoHeader(&bbcb_bytes, &bitpos, &mh_st_bbcb);

            cnt = bitpos / 8;
            
        }

        if (LC_SUCCESS == result)
        {
            /*Convert the parameters into a byte array.*/

            /* Skip 2 bytes CRC16. */
            lc_uint32 startOffset = cnt;

            /* Format the byte array from index 2.*/
            LC_memcpy(&pBuffer[cnt], pBBCB->OUI, sizeof(pBBCB->OUI));
            cnt += sizeof(pBBCB->OUI);
            
            pBuffer[cnt++] = (lc_uchar)((pBBCB->manufacturer_id >> 8) & 0xFF);
            pBuffer[cnt++] = (lc_uchar)((pBBCB->manufacturer_id >> 0) & 0xFF);
            
            pBuffer[cnt++] = (lc_uchar)((pBBCB->hardware_version >> 8) & 0xFF);
            pBuffer[cnt++] = (lc_uchar)((pBBCB->hardware_version >> 0) & 0xFF);
            
            pBuffer[cnt++] = (lc_uchar)((pBBCB->loader_major_version >> 0) & 0xFF);
            
            pBuffer[cnt++] = (lc_uchar)((pBBCB->loader_minor_version >> 0) & 0xFF);
            
            pBuffer[cnt++] = (lc_uchar)((pBBCB->loader_version_buildnumber >> 8) & 0xFF);
            pBuffer[cnt++] = (lc_uchar)((pBBCB->loader_version_buildnumber >> 0) & 0xFF);

            pBuffer[cnt++] = (lc_uchar)((pBBCB->boot_check_algorithm >> 0) & 0xFF);

            LC_memcpy(&pBuffer[cnt], pBBCB->serial_number, sizeof(pBBCB->serial_number));
            cnt += sizeof(pBBCB->serial_number);

            LC_memcpy(&pBuffer[cnt], pBBCB->random_number, sizeof(pBBCB->random_number));
            cnt += sizeof(pBBCB->random_number);

            if(LC_TRUE == updateCRC)
            {
                /* recalculate CRC32 if needed. */

                /* calculate CRC32 for BBCB. */

                crc32 = CRC_Code32(&pBuffer[startOffset], cnt - startOffset);

                /*Boot strap and boot loader are also needed for CRC calculation..*/
                crc32 = CRC_Code32_Seq(mp_byte_bl.bytes, mp_byte_bl.length, crc32);
				
            }
            else
            {
                /*Use the input CRC16 directly.*/
                crc32 = pBBCB->crc32;
            }

            /*Set CRC32 now.*/
            pBuffer[cnt++] = (lc_uchar)((crc32 >> 24) & 0xFF);
            pBuffer[cnt++] = (lc_uchar)((crc32 >> 16) & 0xFF);
            pBuffer[cnt++] = (lc_uchar)((crc32 >> 8) & 0xFF);
            pBuffer[cnt++] = (lc_uchar)(crc32 & 0xFF);
                        
        }
        
        /* Debug code for checking the BBCB module size */
        if (LC_SUCCESS == result)
        {
            LC_ASSERT( cnt == (mh_st_bbcb.header_length + mh_st_bbcb.module_size) );
        }
        
        /* update BBCB module */
        if (LC_SUCCESS == result)
        {
            module_byte_bbcb.bytes = pBuffer;
            module_byte_bbcb.length = cnt;
            result = LoaderCoreSPI_Module_WriteModule(MODULE_DRV_ID_BBCB, &module_byte_bbcb);
        }

        /* clear memory blocks */
        if(LC_TRUE == updateCRC)
        {
            LC_Free_Memory((void **)&mp_byte_bl.bytes);
        }

        LC_Free_Memory((void **)&pBuffer);

    }

    /* clear memory blocks */
    MessageParser_FreeModuleInfoHeader(&mh_st_bbcb);
    
    return result;
}



