/**
 * @file LoaderCoreSPI_DEMUX.h
 * Header for DEMUX(Demultiplexer) methods. This file contains the prototypes for all DEMUX functions 
 * that are used by the Loader Core.
 *
 */

#ifndef LOADERCORESPI_DEMUX_H__INCLUDED__
#define LOADERCORESPI_DEMUX_H__INCLUDED__

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
 * Max filter depth for filter conditions.
 *
 * Loader Core will not use filter conditions longer than this value.
 */
#define  LC_MAX_FILTER_DEPTH  (8)


/**
 * Max space size for manufacturer to save private data.
 *
 * Loader Partition module will reserve the space so that manufacturer can save some private data into the space, for example, tuner info.
 */
#define LC_MANUFACTURER_PRIVATE_INFO_LENGTH (48)


/**
 * Indicate the type of a channel.
 *
 * This type is used in ::lc_channel_info to 
 * determine what type of channel is expected.
 */
typedef enum _lc_channel_type
{
    /**
     * DVB channel type.
     *
     * DVB uses PIDs (Packet IDs) to uniquely identify a stream.
     */
    LC_CHANNEL_TYPE_DVB = 0x01,

    /**
     * IP channel type.
     *
     * IP uses IP address and IP port to uniquely identify a stream.
     */
    LC_CHANNEL_TYPE_IP = 0x02
} lc_channel_type;

/**
 * DVB channel parameters.
 *
 * This is the structure that is passed to ::lc_channel_info to carry detail channel information in order to open a DVB channel.
 */
typedef struct _lc_dvb_channel
{
    /**
     * Packet identifier.
     *
     * This is the transport stream PID (Packet ID) of the download stream.
     *
     */
    lc_uint16  pid;
}lc_dvb_channel;

/**
 * IP channel parameters.
 *
 * This is the structure that is passed to ::lc_channel to carry detail information in order to open a socket to receive download datagrams.
 */
typedef struct _lc_ip_channel
{
    /**
     * IP address.
     *
     * This is the address of the download stream where Loader Core expects to receive download datagram.
     *
     */
    lc_uint32 ipAddress;

    /**
     * IP port.
     *
     * This is the port number of the IP download stream where Loader Core expects to receive download datagram.
     *
     */

    lc_uint16 ipPort;
}lc_ip_channel;


/**
 * Channel parameters.
 *
 * This is the structure that is passed to ::lc_channel to carry detail information in order to open a socke to receive download datagrams.
 */
typedef union _lc_channel
{
    /** DVB channel with PID.*/
    lc_dvb_channel dvbChannel;

    /** IP channel with IP and port.*/
    lc_ip_channel ipChannel;
}lc_channel;


/**
 * Channel open parameters for ::LoaderCoreSPI_DEMUX_OpenChannel
 *
 * This is the structure that is passed to ::LoaderCoreSPI_DEMUX_OpenChannel to a DVB channel with PID or socket with IP and port.
 */
typedef struct _lc_channel_info
{
    /**
     * Channel type indicator.
     *
     * This field decides whether DVB channel or IP channel is needed by Loader Core.
     * See ::lc_channel_type to get a list of all possible values.
     */
    lc_channel_type  channelType;
    
    /**
     * Space for manufacturer.
     *
     * The manufacturer can use the space to save some additional private info.For example, tuner parameters for download service. 
     * The manufacturer must set up the tuner according the tunner info so that Loader Core can receive download stream correctly.
     */
    lc_uchar manufacturerPrivateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH];

    /**
     * Channel information.
     *
     * The information in this structure is used to identify the source of incoming
     * DVB sections or IP datagrams.
     * See the ::lc_channel to know more details.
     * \note This is a union. lc_channel_info::channelType decides which of the following field is valid.
     */
    lc_channel channel; 

} lc_channel_info;


/**
 * Filter definition
 *
 * This structure contains the definition of a filter for DVB section
 * that is sent to Loader Core for processing. This structure is passed to
 * ::LoaderCoreSPI_DEMUX_SetFilter to notify SPI driver with the pattern
 * of section it should deliver on the filter. 
 *
 * When a section arrives, the driver should match the first filterDepth 
 * bytes of the section against the filter pattern. 
 * The filter pattern is defined as a 'mask', which specifies which bits are relevant
 * for the comparison, and a 'match', which specifies the value the corresponding bits
 * should have in order to have successfully matched the pattern. 
 *
 * Here is some sample code for performing the comparison to illustrate how it is used: 
 *
 *
 * \note Filter conditions from this structure DO NOT include 2 bytes after table_id, i.e. reserved bits and section_length. 
 */
typedef struct _lc_filter_info {
    /**
     * Specifies which bits are important for the pattern match. 
     *
     * This points to a buffer whose length is determined by the \a filterDepth member.
     */
    lc_uchar  mask[LC_MAX_FILTER_DEPTH];

    /**
     * Specifies which bits to compare the masked bits against. 
     *
     * This points to a buffer whose length is determined by the \a filterDepth member.
     */
    lc_uchar  match[LC_MAX_FILTER_DEPTH];

    /**
     * Specifies the number of bytes in the \a mask and \a match buffers
     *
     * A filterDepth of 0 means "match all sections". 
     */
    lc_uint32 filterDepth;
} lc_filter_info;


/**
 * Function pointer type used to notify Loader Core with sections or datagrams.
 *
 * A function pointer of this type is passed to ::LoaderCoreSPI_DEMUX_OpenChannel method.
 * The SPI driver implementation is expected to deliver new sections or datagrams that match the currently active set
 * of filters (see ::LoaderCoreSPI_DEMUX_OpenFilter) to this function, 
 * after a call to ::LoaderCoreSPI_DEMUX_StartChannel and until a call to ::LoaderCoreSPI_DEMUX_StopChannel occurs. 
 *
 * \note The SPI driver must pass a section or a datagram one at a time.
 *
 * @param[in] channelHandle The value of the channel handle previously returned to ::LoaderCoreSPI_DEMUX_OpenChannel method.
 * @param[in] pData Containing one section or one IP datagram to process.
 *     The uc_buffer_st::bytes member must point to a buffer containing the raw data of 
 *     the section or datagram, and the uc_buffer_st::length member must be set to the number of bytes
 *     in the section or datagram.\note The SPI driver must free the buffer used. Loader Core will make a copy of the data and push it into a list.
 */

typedef lc_result (*lc_demux_data_notify_callback)(lc_handle channelHandle, lc_buffer_st *pData);


/** @defgroup loadercoredemuxspis Loader Core DEMUX SPIs
 *  Loader Core DEMUX SPIs
 *
 *  Methods to receive data through DEMUX channel/filter.
 *  
 *  @{
 */

/** 
 * Open a channel or socket.
 * 
 * Loader Core will request to create a DVB channel with PID or an IP socket with IP address and port number.
 * \note When this method is called and DVB is used, the SPI driver must set up tuner according to the manufacturer private info in lc_channel_info::manufacturerPrivateInfo. 
 *
 * @param[out] pChannelHandle To save a unique identifier that can identify this channel. A channel is uniquely identified by a PID or IP address plus port number.
 * @param[in] pChannelInfo Pointer to structure that describes
 *      the parameters needed to open the channel. See ::lc_channel_info to get more detail info.
 * @param[in] callbackFunction Callback function that is expected to be called by the SPI driver when data has been received.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_OpenChannel(lc_handle *pChannelHandle, lc_channel_info *pChannelInfo, lc_demux_data_notify_callback callbackFunction);

/**
 * Method to stop and close a channel.
 *
 * This method is called when the channel is being closed by Loader Core and is 
 * intended to give the SPI driver a chance to clean up any leftover resources set 
 * up during a call to open.
 *
 * @param[in] channelHandle Points to a channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_CloseChannel(lc_handle channelHandle);

/**
 * Starts this channel.
 *
 * This function is called to start all filters that were allocated and set for this channel
 * using ::LoaderCoreSPI_DEMUX_OpenFilter. 
 * 
 * Once this method is called, the SPI driver is free to call the ::lc_demux_data_notify_callback 
 * function originally passed to ::LoaderCoreSPI_DEMUX_OpenChannel for this channel.
 *
 *
 * @param[in] channelHandle Channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_StartChannel(lc_handle channelHandle);

/**
 * Request data.
 *
 * This function is called \b each \b time Loader Core expects to receive data from demux.
 * 
 * \note This function is a helper interface. It is added in order to make it convenient for those platforms that don't have multiple task support 
 * and also for those platforms whose demux driver doesn't use callback mechanism to notify incoming data to the data requester.
 * The SPI driver can just simply return ::LC_SUCCESS to Loader Core, 
 * and then Loader Core will wait for the callback event which is triggered by ::lc_demux_data_notify_callback passed through ::LoaderCoreSPI_DEMUX_OpenChannel.
 * 
 * \n
 * 
 * \note For those platforms that don't have multiple task support or don't use callback mechanism, the SPI driver can request data from SPI driver in this function.
 * When data is ready, the SPI driver can directly notify the incoming data to Loader Core via ::lc_demux_data_notify_callback.
 *
 *
 *
 * @param[in] channelHandle Channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 * @param[in] millisecondTimeout Timeout in millisecond that Loader Core expects to wait. If it is 0, Loader Core will wait infinitely.
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_RequestData(lc_handle channelHandle, lc_uint32 millisecondTimeout);

/**
 * Stops this channel.
 *
 * This function is called to stop all filters that were allocated and set for this channel
 * using ::LoaderCoreSPI_DEMUX_OpenFilter. 
 * 
 * \note Once this method is called, then no more data should be passed to ::lc_demux_data_notify_callback function 
 * originally passed to ::LoaderCoreSPI_DEMUX_OpenChannel for this channel.
 *
 * 
 * @param[in] channelHandle Channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_StopChannel(lc_handle channelHandle);

/**
 * Open a filter.
 *
 * \note This SPI is for DVB channel only. Channel with IP address and port number will not be called using this method.
 *
 * This method is called to add a filter to an existing channel.
 *
 * After this method is called, ::LoaderCoreSPI_DEMUX_SetFilter is called to provide or change the filter
 * rules on the filter handle. After all filters are initially set up, ::LoaderCoreSPI_DEMUX_StartChannel is called.
 *
 *
 *
 * @param[in] channelHandle Channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 * @param[out] pFilterHandle Receives an implementation defined filter handle that can be used to 
 *      identify the filter in a subsequent call to ::LoaderCoreSPI_DEMUX_CloseFilter.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_OpenFilter(lc_handle channelHandle, lc_handle *pFilterHandle);

/**
 * Set filter conditions.
 * 
 * This method is called after ::LoaderCoreSPI_DEMUX_OpenFilter for each filter.  This method is also
 * called when a message is received that requires changing of filter rules. 
 *
 * \note Mask/match/filterDepth used by LoaderCoreSPI_DEMUX_SetFilter DOES NOT includes 2 bytes after table_id, i.e. section_syntax_indicator and section_length.
 *
 * @param[in] channelHandle Channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 * @param[in] filterHandle Filter handle previously allocated by ::LoaderCoreSPI_DEMUX_OpenFilter.
 * @param[in] pFilterInfo The rule set of the filter to create. See ::lc_filter_info to get more details.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_DEMUX_SetFilter(lc_handle channelHandle, lc_handle filterHandle, lc_filter_info *pFilterInfo);

/**
 * Close a filter
 *
 * This function is called to close an existing filter from a channel that was previously
 * added by a call to ::LoaderCoreSPI_DEMUX_OpenChannel.  
 *
 *
 * @param[in] channelHandle Channel handle originally returned from ::LoaderCoreSPI_DEMUX_OpenChannel method.
 * @param[in] filterHandle Handle of filter to close, which is previously allocated by 
 *      ::LoaderCoreSPI_DEMUX_OpenFilter.  Any private data 
 *      associated with filterHandle should be cleaned up by this method. 
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */

lc_result LoaderCoreSPI_DEMUX_CloseFilter(lc_handle channelHandle, lc_handle filterHandle);

/** @} */ /* End of Loader Core DEMUX SPIs */

/** @} */ /* End of Loader Core SPIs */



#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_DEMUX_H__INCLUDED__ */

