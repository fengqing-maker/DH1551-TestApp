/**
 * @file LoaderCoreSPI_UART.h
 * Header for UART(Universal Asynchronous Receiver/Transmitter) communication methods. This file contains the prototypes for all UART functions 
 * that are used by the Loader Core.
 *
 */

#ifndef LOADERCORESPI_UART_H__INCLUDED__
#define LOADERCORESPI_UART_H__INCLUDED__

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


/** @defgroup loadercoreuartspis Loader Core UART SPIs
 *  Loader Core UART SPIs
 *
 *  Methods to read/write through UART connection.
 *
 * 
 * Loader Core supports the download over UART/USB connection. Both UART connection and USB connection reuse the same protocol.
 * Loader Core uses 3 pairs of sequences to communicate with TEMU(Terminal Emulator) which should be implemented by the manufacturers.
 *
 * - 1.1. Loader Core sends a byte sequence to check whether TEMU is present. \n
 *   Loader Core ->-----------------------::STX,::CMD_STB_START, ::ETX----------------------------------------------------------> TEMU \n
 * - 1.2. TEMU will response with the following byte sequence to Loader Core to indicate the TEMU is present. In case of timeout or unexpected byte sequence, Loader Core will regard that no TEMU is present.\n
 *   Loader Core <------------------------::STX,::CMD_TEMU_START,::DATA_TEMU_START,::ETX--------------------------------------<- TEMU \n
 * \n
 * - 2.1. Loader Core sends a byte sequence to request current time.\n
 *   Loader Core ->-----------------------::STX,::CMD_STB_TIME_REQUEST, ::ETX---------------------------------------------------> TEMU \n
 * - 2.2. TEMU will reply the following byte sequence to feed back the current time to Loader Core. \n
 *   Loader Core <------------------------::STX,::CMD_TEMU_TIME_REPLY,5 bytes Date Time, ::ETX---------------------------------<- TEMU \n
 * \n
 * 5 bytes date time is in the following format Date Time is in the following format. \n
 *   [0] - Date MSB (UTC and MJD) \n
 *   [1] - Date LSB (UTC and MJD) \n
 *   [2] - Hour     (BCD) \n
 *   [3] - Minute   (BCD) \n
 *   [4] - Second   (BCD) \n
 * \n
 * - 3.1. Loader Core sends a byte sequence to request download file data. \n
 *   Loader Core ->-----------------------::STX,::CMD_STB_DATA_REQUEST,2 bytes length, 4 bytes offset, ::ETX-------------------> TEMU \n
 * - 3.2. TEMU will reply RAW data bytes which are read from download file according to the length and offset. \n
 *   Loader Core <------------------------RAW data bytes(no header and no tailer)--------------------------------------------<- TEMU \n
 *  @{
 */

/** 
 *  UART Protocol Flags
 *
 *  Flags that are used in the UART communication.
 */
typedef enum _lc_uart_protocol_flag
{
    /**
     * 0x02
     * 
     * Flag to indicate transmission start.
      */
    STX = 0x02,

    /**
     * 0x03
     * 
     * Flag to indicate transmission end.
     */
    ETX = 0x03,

    /**
     * 0x01
     * 
     * Flag to indicate the device has started.
     */
    CMD_STB_START = 0x01,

    /**
     * 0x01
     * 
     * Flag to indicate the TEMU has started.
     */
    CMD_TEMU_START = 0x01,

    /**
     * 0x02
     * 
     * Flag to indicate that STB is requesting data.
     */
    CMD_STB_DATA_REQUEST = 0x02,

    /**
     * 0x03
     * 
     * Flag to indicate that STB is requesting current time.
     */
    CMD_STB_TIME_REQUEST = 0x03,

    /**
     * 0x03
     * 
     * Flag to indicate that TEMU replies the current time to the device.
     */
    CMD_TEMU_TIME_REPLY = 0x03,

    /**
     * 0x03
     * 
     * Flag to indicate that TEMU has started.
     */
    DATA_TEMU_START = 0x0A

} lc_uart_protocol_flag;


/** 
 * Read data from TEMU via UART communication.
 * 
 * Loader Core will read data from TEMU via this SPI.
 * Loader Core allocates the buffer and will also free the buffer inside. 
 *
 * @param[in,out] pUARTPacket Structure containing a buffer to save the read-in data, and length indicating how many bytes to read in.
 *     The lc_buffer_st::bytes member points to a buffer to store data, and
 *     the lc_buffer_st::length member is be set to the number of bytes to read.
 *     \note The SPI driver must set lc_buffer_st::length to indicate how many bytes have been really read in.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_UART_Read(lc_buffer_st * pUARTPacket);

/** 
 * Write data to TEMU via UART communication.
 * 
 * Loader Core will write data to TEMU via this SPI.
 * Loader Core allocates the buffer and will also free the buffer inside. 
 *
 * @param[in,out] pUARTPacket Structure containing a buffer to save the data to TEMU, and length in the structure indicates how many bytes to read in.
 *     The lc_buffer_st::bytes member points to a buffer containing data to write to TEMU, and
 *     the lc_buffer_st::length member is be set to the number of bytes to write.
 *     \note The SPI driver must set lc_buffer_st::length to indicate how many bytes have been really written to TEMU successfully.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_UART_Write(lc_buffer_st *pUARTPacket);

/** @} */

/** @} */ /* End of Loader Core SPIs */


#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_UART_H__INCLUDED__ */

