/**
 * @file LoaderCoreSPI_UART.h
 * Header for UART(Universal Asynchronous Receiver/Transmitter) communication methods. This file contains the prototypes for all UART functions 
 * that are used by the Loader Core.
 *
 */

#include "LoaderCoreSPI.h"
#include <aui_uart.h>

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
// #define LC_SPI_UART_DEBUG(...)
#define LC_SPI_UART_DEBUG    LoaderCoreSPI_Stdlib_printf

static aui_hdl g_p_hdl_uart = LC_NULL;
static lc_handle g_sema_hdl = LC_NULL;

static void lc_uart_init()
{
    aui_hdl hdl_uart = LC_NULL;    
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_handle sema_hdl = LC_NULL;
    
    if(LC_NULL == g_p_hdl_uart)
    {
    	aui_find_dev_by_idx(AUI_MODULE_UART, 0, &hdl_uart);
    	if(LC_NULL == hdl_uart )
        {
    		rtn = aui_uart_open(0, LC_NULL,&hdl_uart);
            if(AUI_RTN_SUCCESS != rtn)
            {
                LC_SPI_UART_DEBUG("uart can not be open\n");
                return;
            }
            if( LC_SUCCESS != LoaderCoreSPI_Semaphore_Open(0,&sema_hdl))
            {
                LC_SPI_UART_DEBUG("semaphore_open_fail\n");
                aui_uart_close(hdl_uart);
                return;
            }
            aui_uart_enable(hdl_uart, AUI_UART_READ_WRITE);
            g_sema_hdl = sema_hdl;
            g_p_hdl_uart = hdl_uart;
            LC_SPI_UART_DEBUG("lc_uart_init OK\n");
            if(LC_SUCCESS != LoaderCoreSPI_Semaphore_Post(g_sema_hdl))
            {
                LC_SPI_UART_DEBUG(" lc_uart_init LoaderCoreSPI_Semaphore_Post fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
            }
    	}
    }
    else
    {
        LC_SPI_UART_DEBUG("uart has been open, no need to init again\n");
    }
}
lc_result LoaderCoreSPI_UART_Read(lc_buffer_st * pUARTPacket)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_uint32 time_out = 500;
    lc_uint32 readed_len = 0;

    if((LC_NULL == pUARTPacket) || (LC_NULL == pUARTPacket->bytes) || (LC_NULL == pUARTPacket->length))
    {
        LC_SPI_UART_DEBUG("Invalid Input\n"); 
        lc_ret = LC_FAILURE;
        return lc_ret;
    }
    lc_uart_init();
    if(LC_SUCCESS != LoaderCoreSPI_Semaphore_WaitTimeout(g_sema_hdl,time_out))
    {
        LC_SPI_UART_DEBUG("LoaderCoreSPI_Semaphore_WaitTimeout fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
    }
    
    if(AUI_RTN_SUCCESS != aui_uart_enable(g_p_hdl_uart, AUI_UART_READ_WRITE))
    {
        LC_SPI_UART_DEBUG("aui_uart_enable fail\n"); 
        if(LC_SUCCESS != LoaderCoreSPI_Semaphore_Post(g_sema_hdl))
        {
            LC_SPI_UART_DEBUG("LoaderCoreSPI_Semaphore_Post fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
        }
        lc_ret = LC_FAILURE;
        return lc_ret;
    }
    //timeout=0 means return right now
// <- T713-Oliver-2016/11/08-Commented by Oliver.
    //if(AUI_RTN_SUCCESS != aui_uart_read(g_p_hdl_uart,pUARTPacket->bytes,pUARTPacket->length,&readed_len,0))
    if(AUI_RTN_SUCCESS != aui_uart_read(g_p_hdl_uart,pUARTPacket->bytes,pUARTPacket->length,&readed_len,10000))
// -> T713-Oliver
    {
        LC_SPI_UART_DEBUG("aui_uart_read fail\n");
        if(AUI_RTN_SUCCESS != aui_uart_disable(g_p_hdl_uart, AUI_UART_READ_WRITE))
        {
            LC_SPI_UART_DEBUG("aui_uart_disable fail\n"); 
        }
        lc_ret = LC_FAILURE;
    }
    else
    {
        if(AUI_RTN_SUCCESS != aui_uart_disable(g_p_hdl_uart, AUI_UART_READ_WRITE))
        {
            LC_SPI_UART_DEBUG("aui_uart_disable fail\n"); 
        }
    }
    
    if(LC_SUCCESS != LoaderCoreSPI_Semaphore_Post(g_sema_hdl))
    {
        LC_SPI_UART_DEBUG("LoaderCoreSPI_Semaphore_Post fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
    }
	return lc_ret;
}

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
lc_result LoaderCoreSPI_UART_Write(lc_buffer_st *pUARTPacket)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_uint32 time_out = 500;
    lc_uint32 write_len = 0;

    if((LC_NULL == pUARTPacket) || (LC_NULL == pUARTPacket->bytes) || (0 == pUARTPacket->length))
    {
        LC_SPI_UART_DEBUG("LoaderCoreSPI_UART_Write Invalid Input in %s() Line(%d)\n",__FUNCTION__, __LINE__); 
        lc_ret = LC_FAILURE;
        return lc_ret;
    }
    lc_uart_init();
    if(LC_SUCCESS != LoaderCoreSPI_Semaphore_WaitTimeout(g_sema_hdl,time_out))
    {
        LC_SPI_UART_DEBUG("LoaderCoreSPI_Semaphore_WaitTimeout fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
    }
    
    if(AUI_RTN_SUCCESS != aui_uart_enable(g_p_hdl_uart, AUI_UART_READ_WRITE))
    {
        LC_SPI_UART_DEBUG("aui_uart_enable fail in %s() Line(%d)\n",  __FUNCTION__, __LINE__); 
        if(LC_SUCCESS != LoaderCoreSPI_Semaphore_Post(g_sema_hdl))
        {
            LC_SPI_UART_DEBUG("LoaderCoreSPI_Semaphore_Post fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
        }
        lc_ret = LC_FAILURE;
        return lc_ret;
    }
    //timeout=0 means return right now
    if(AUI_RTN_SUCCESS != aui_uart_write(g_p_hdl_uart,pUARTPacket->bytes,pUARTPacket->length,&write_len,0))
    {
        LC_SPI_UART_DEBUG("aui_uart_write fail\n");
        if(AUI_RTN_SUCCESS != aui_uart_disable(g_p_hdl_uart, AUI_UART_READ_WRITE))
        {
            LC_SPI_UART_DEBUG("aui_uart_disable fail\n"); 
        }
        LC_SPI_UART_DEBUG("aui_uart_write fail\n");
    }
    else
    {
        if(AUI_RTN_SUCCESS != aui_uart_disable(g_p_hdl_uart, AUI_UART_READ_WRITE))
        {
            LC_SPI_UART_DEBUG("aui_uart_disable fail\n"); 
        }
    }
    
   if(LC_SUCCESS !=LoaderCoreSPI_Semaphore_Post(g_sema_hdl))
   {
        LC_SPI_UART_DEBUG("LoaderCoreSPI_Semaphore_Post fail in %s() Line(%d)\n", __FUNCTION__, __LINE__); 
   }

   return lc_ret;
}




