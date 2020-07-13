/**
 * @file LoaderCoreSPI_Device.h
 * This file contains the prototypes for all chipset-specific or device-specific functions 
 * that are used by the Loader Core.
 *
 */

#ifndef LOADERCORESPI_DEVICE_H__INCLUDED__
#define LOADERCORESPI_DEVICE_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  
 *  @{
 */

/**
 * Indicate the checksum algorithm used by a client device.
 *
 * This type is used in ::lc_checksum_info to 
 * determine what algorithm is used by this client device.
 */
typedef enum _lc_checksum_algorithm
{
    /**
     * CRC32.
     *
     * It shall be used only on non secure box. 
     * The CRC32 value is generated locally by loader during download procedure. 
     * And it will then overwrite the initial module signature.
     */
    LC_CHECKSUM_ALGORITHM_CRC32 = 0x00,

    /**
     * MAC.
     *
     * It is for secure box.
     * The MAC value is generated locally by loader during download procedure. 
     * And it will then overwrite the initial module signature.
     */
    LC_CHECKSUM_ALGORITHM_MAC = 0x01,

    /**
     * SHA1.
     *
     * It is for secure box.
     */
    LC_CHECKSUM_ALGORITHM_SHA1 = 0x02,

    /**
     * SHA256.
     *
     * It is for secure box.
     */
    LC_CHECKSUM_ALGORITHM_SHA256 = 0x03,

    /**
     * The minimum value of reserved.
     *
     */
    LC_CHECKSUM_ALGORITHM_MIN_RESERVED = 0x04
    
} lc_checksum_algorithm;

/**
 * Checksum information.
 *
 * It contains the checksum information, at least the selected checksum algorithm.
 */
typedef struct _lc_checksum_info
{
    /**
     * checksum algorithm.
     *
     * This is the algorithm used for checksum calculation.
     *
     */
    lc_checksum_algorithm  algorithm;
    
}lc_checksum_info;


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
lc_result LoaderCoreSPI_Device_ChooseAlgorithm(lc_checksum_algorithm *pSelectedAlgorithm);

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
lc_result LoaderCoreSPI_Device_GetChecksum(lc_checksum_info *pChecksumInfo, lc_buffer_st * pRawData, lc_buffer_st * pChecksum);

/** @} */ /* End of Loader Core Device SPIs */

/** @} */ /* End of Loader Core SPIs */


#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_DEVICE_H__INCLUDED__ */

