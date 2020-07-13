
#ifndef CAROUSEL_H__INCLUDED__
#define CAROUSEL_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


/** 
 * Set up DVB-SSU download by opening demux and tunning.
 */
lc_result LC_SetupCarousel(nim_setup func);

/** 
 * Main DVB-SSU download process.
 */
lc_result LC_ProcessCarousel(void);

/** 
 * Close DVB-SSU download.
 */
lc_result LC_FinalizeCarousel(void);

/** 
 * Parse download file format obtained from SSU stream and get the raw data.
 */
lc_result 
LC_AcquireUpgradeDataFromSSUStream(
    lc_uart_packet_type dataId,
    lc_buffer_st* pBytes);

/** 
 * Get the global SSU download buffer structure information.
 */
lc_result 
LC_GetSSUStreamData(lc_buffer_st* pBytes);


#ifdef __cplusplus
}
#endif

#endif /* CAROUSEL_H__INCLUDED__ */

