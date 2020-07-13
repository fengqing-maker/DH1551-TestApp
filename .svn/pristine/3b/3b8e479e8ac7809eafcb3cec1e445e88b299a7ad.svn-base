
#ifndef UART_INTERFACE__INCLUDED__
#define UART_INTERFACE__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/**************************** Function Declarations ***************************/

/** Loader Core calls this function to make connection with TEMU. */
lc_result LC_TemuStart( void );

/** Loader Core calls this function to request data from TEMU. */
lc_result 
LC_TemuDataRequest(
    lc_uchar *pData, 
    lc_uint32 length, 
    lc_uint32 offset, 
    lc_uint32 maxRetry);
lc_result ird_dump_data_to_usb(lc_char* addr, lc_uint32 length);


/******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* UART_INTERFACE__INCLUDED__ */


