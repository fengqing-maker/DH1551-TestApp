/**
 * @file LoaderCoreSPI_Device.h
 * This file contains the prototypes for all chipset-specific or device-specific functions 
 * that are used by the Loader Core.
 *
 */

#include "LoaderCoreSPI.h"
#include <aui_dsc.h>
#include <string.h>

#define UC_SPI_DEVICE_DEBUG LoaderCoreSPI_Stdlib_printf

#define LC_SHA1_HASH_LEN    (20)
#define LC_SHA256_HASH_LEN    (32)

/*
 *  3529 no need to align 4 bytes, but 3733 still need to 4 bytes align
 */
#define LC_SHA_ALIGN
#define LC_HW_SHA_ALIGN_BYTES  (0x4)

/**
 *  Boot Check Algorithm. 
 */

/** 0x00 refers to CRC32 */
#define LC_BOOTCHECK_CRC32              (0x00)

/** 0x01 refers to MAC */
#define LC_BOOTCHECK_MAC                (0x01)
    
/** 0x02 refers to Digital Signature Verification  */
#define LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION  (0x02)

/** 0x03 reserved */
#define LC_BOOTCHECK_MIN_RESERVED       (0x03)



/** @defgroup loadercoredevicespis Loader Core Device SPIs
 *  Loader Core Device SPIs
 *
 *  Chipset-specific or device-specific methods, mainly about algorithms that are supported by the device.
 *  Device SPIs are mainly used for checksum calculation. Hardware is used for checksum calculation in order to improve performance (reduce calculation time).
 *  Loader may adopt several algorithms, but a device may choose one of the algorithms that will be used.
 *
 *  @{
 */

/** 
 * Get the algorithm chosen by the manufacturer.
 * 
 * The SPI is to get the algorithm chosen by the manufacturer. This algorithm will later be used for checksum calculation. 
 * The SPI driver must set the selected algorithm to * pSelectedAlgorithm.
 * \note The algorithm is used for checksum calculation. It has nothing to do with descrambling key ladder.
 *
 * @param[out] pSelectedAlgorithm To save the checksum algorithm chosen by the manufacturer
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Device_ChooseAlgorithm(lc_checksum_algorithm *pSelectedAlgorithm)
{
    lc_uchar bootcheckalgo = LC_BOOTCHECK_MIN_RESERVED;
    bootcheckalgo = LC_UtilGetBootcheckAlgorithm();
    if (LC_BOOTCHECK_MAC == bootcheckalgo)
    {
        *pSelectedAlgorithm = LC_CHECKSUM_ALGORITHM_MAC;
    }
    else if(LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION == bootcheckalgo)
    {
        /* SHA -256
          * IRDETO Loader v5.1 ONLY support SHA-256
          */
        *pSelectedAlgorithm = LC_CHECKSUM_ALGORITHM_SHA256;
        /* SHA1 
          * IRDETO Loader v5.1 must use SHA-256 to check check moudle header and payloader signature
          * If return SHA1, Loader will use software SHA-256 algorithm to check moudle header and payloader signature!!!
          */
        //*pSelectedAlgorithm = LC_CHECKSUM_ALGORITHM_SHA1;
    }
    else
    {
        UC_SPI_DEVICE_DEBUG("%s() in Line(%d) NOT SUPPORT BOOTCHECKALGO!!! \n ",__FUNCTION__,__LINE__);
    }
    return LC_SUCCESS;

}

/** 
 * Get the algorithm chosen by the manufacturer.
 * 
 * This SPI will require the device to return the checksum to Loader Core. 
 * ::lc_checksum_info must at least contain checksum algorithm and necessary control fields if needed.
 * \note The algorithm is used for checksum calculation. It has nothing to do with descrambling key ladder.
 *
 * @param[in] pChecksumInfo Pointer to structure that describes necessary checksum information, at least 
 *     the selected checksum algorithm.
 * @param[in] pRawData Pointer to buffer containing raw data for calculating checksum. The lc_buffer_st::bytes member 
 *     points to the start of the buffer, and the lc_buffer_st::length member contains the number of bytes in the buffer
 *     to write.
 * @param[in,out] pChecksum To save the checksum result. The lc_buffer_st::bytes member points to the start of the buffer, 
 *     whose memory should be allocated by Loader Core, and the lc_buffer_st::length member contains the actual number of 
 *     bytes in the buffer.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Device_GetChecksum(lc_checksum_info *pChecksumInfo, lc_buffer_st * pRawData, lc_buffer_st * pChecksum)
{
    lc_checksum_algorithm hardwareAlgorithm = LC_CHECKSUM_ALGORITHM_MIN_RESERVED;
    lc_result lc_ret = LC_SUCCESS;
    lc_uchar * align_addr = LC_NULL;
	int ret = AUI_RTN_SUCCESS;
    
    if((LC_NULL == pChecksum) || (LC_NULL == pChecksumInfo) || (LC_NULL == pRawData))
    {
        lc_ret = LC_FAILURE;
        goto EXIT;
    }
    if((LC_NULL == pRawData->bytes) || (0 == pRawData->length) ||  (LC_NULL == pChecksum->bytes))
    {
        lc_ret = LC_FAILURE;
        goto EXIT;
    }  
    
    LoaderCoreSPI_Device_ChooseAlgorithm(&hardwareAlgorithm);
    /* SHA1
    /*
     * Which will never use!!!
     */
    if(LC_CHECKSUM_ALGORITHM_SHA1 == hardwareAlgorithm)
    {
        if (LC_CHECKSUM_ALGORITHM_SHA1 == pChecksumInfo->algorithm)
        {
            pChecksum->length = LC_SHA1_HASH_LEN;

            /*
              * check pRawData->bytes is 4 bytes align?
              */
#ifdef LC_SHA_ALIGN
            if((lc_uint32)pRawData->bytes & (LC_HW_SHA_ALIGN_BYTES - 1))
            {
                align_addr = (lc_uchar*)LoaderCoreSPI_Memory_AlignedMalloc(pRawData->length, LC_HW_SHA_ALIGN_BYTES);
                if(LC_NULL == align_addr)
                {                
                    UC_SPI_DEVICE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_AlignedMalloc failed!!!\n:", __FUNCTION__, __LINE__);
                    lc_ret = LC_FAILURE;
                    goto EXIT;
                }
                LoaderCoreSPI_Stdlib_memcpy(align_addr, pRawData->bytes, pRawData->length);
               
                ret = aui_dsc_sha_digest(AUI_SHA_SRC_FROM_DRAM, align_addr, pRawData->length, AUI_SHA_1, pChecksum->bytes);
                
            }
            else
#endif
            {
                ret = aui_dsc_sha_digest(AUI_SHA_SRC_FROM_DRAM, pRawData->bytes, pRawData->length, AUI_SHA_1, pChecksum->bytes);
            }

            if (AUI_RTN_SUCCESS != ret)
            {
                UC_SPI_DEVICE_DEBUG("%s() in line(%d) aui_dsc_sha_digest failed!!!\n:", __FUNCTION__, __LINE__);
                lc_ret = LC_FAILURE;
                goto EXIT;
            }
        }
        else
        {
            lc_ret = LC_FAILURE;
            goto EXIT;
        }

    }
    /*  SHA-256 */
    else if(LC_CHECKSUM_ALGORITHM_SHA256 == hardwareAlgorithm)
    {
    	if (LC_CHECKSUM_ALGORITHM_SHA256 == pChecksumInfo->algorithm)
    	{
    		pChecksum->length = LC_SHA256_HASH_LEN;
            
            /*
              * check pRawData->bytes is 4 bytes align?
              */
#ifdef LC_SHA_ALIGN
            if((lc_uint32)pRawData->bytes & (LC_HW_SHA_ALIGN_BYTES - 1))
            {
                align_addr = LoaderCoreSPI_Memory_AlignedMalloc(pRawData->length, LC_HW_SHA_ALIGN_BYTES);
                if(LC_NULL == align_addr)
                {                
                    UC_SPI_DEVICE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_AlignedMalloc failed!!!\n:", __FUNCTION__, __LINE__);
                    lc_ret = LC_FAILURE;
                    goto EXIT;
                }
                LoaderCoreSPI_Stdlib_memcpy(align_addr, pRawData->bytes, pRawData->length);
                
                ret = aui_dsc_sha_digest(AUI_SHA_SRC_FROM_DRAM, align_addr, pRawData->length, AUI_SHA_256, pChecksum->bytes);
                
            }
            else
#endif
            {
                ret = aui_dsc_sha_digest(AUI_SHA_SRC_FROM_DRAM, pRawData->bytes, pRawData->length, AUI_SHA_256, pChecksum->bytes);
            }

            if (AUI_RTN_SUCCESS != ret)
            {
                UC_SPI_DEVICE_DEBUG("%s() in line(%d) aui_dsc_sha_digest failed!!!\n:", __FUNCTION__, __LINE__);
                lc_ret = LC_FAILURE;
                goto EXIT;
            }
    	}
    	else
    	{
            lc_ret = LC_FAILURE;
            goto EXIT;
    	}
        
    }
    else
    {
        // TODO: FULLFILL MAC CHECKSUM
        UC_SPI_DEVICE_DEBUG("%s() in line(%d) NOT SUPPORT MAC hardware CheckSum!\n:", __FUNCTION__, __LINE__);
        lc_ret = LC_FAILURE;
        goto EXIT;
    }
    
EXIT:   
    if(LC_NULL != align_addr)
    {
        LoaderCoreSPI_Memory_AlignedFree(align_addr);
    }
    return lc_ret;
}

/** @} */ /* End of Loader Core Device SPIs */

/** @} */ /* End of Loader Core SPIs */


