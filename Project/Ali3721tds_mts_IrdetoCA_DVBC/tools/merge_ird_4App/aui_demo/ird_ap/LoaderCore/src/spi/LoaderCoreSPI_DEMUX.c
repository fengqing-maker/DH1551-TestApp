/**
 * @file LoaderCoreSPI_DEMUX.h
 * Header for DEMUX(Demultiplexer) methods. This file contains the prototypes for all DEMUX functions 
 * that are used by the Loader Core.
 *
 */

#include "LoaderCoreSPI.h"
#include <aui_dmx.h>

//#define LC_SPI_DMX_DEBUG LoaderCoreSPI_Stdlib_printf
#define LC_SPI_DMX_DEBUG(...)
#define LC_DMX_MAGIC_CODE       (0x444c4d58)


typedef struct _lc_filter_st_
{
    void* channel_ptr;
    aui_hdl filter_hdl;
	aui_attr_dmx_filter attr_filter;
    struct _lc_filter_st_ *next;
}lc_filter_st;

typedef struct _lc_channel_st_
{
    lc_channel_info *channel_info;
    lc_demux_data_notify_callback notify_cb;
    lc_uint32 magic_code;   //always to be LC_DMX_MAGIC_CODE ascii of CDMX
    lc_bool   is_start;     // start = 1, stop =0;
    aui_hdl dmx_hdl;
    aui_hdl channel_hdl;
    lc_filter_st  *filter_st;
    lc_uint32 filter_count;
    lc_uint32 state;        

	struct _lc_channel_st_ *next;	
}lc_channel_st;

typedef struct _oem_private_data_
{
    lc_uint32   dmx_id;       // 0~1
    lc_uint32   nim_id;       // 0~3
    lc_uint32   dmod_type;    // 
    lc_uint32   freq;         //
    lc_uint32   bit_rate;     //

    lc_char     resver[28];
}oem_private_data;// size in LC_MANUFACTURER_PRIVATE_INFO_LENGTH

lc_channel_st *channel_list = LC_NULL;

static lc_channel_st *  get_channel_st_by_filter_hdl(aui_hdl filter_handle)
{
	lc_channel_st *cur_channel_st = channel_list;
	lc_channel_st *channel_st = LC_NULL;

	while (cur_channel_st != LC_NULL)
	{
		lc_filter_st *cur_filter_st = cur_channel_st->filter_st;

		while (cur_filter_st != LC_NULL)
		{
			if (cur_filter_st->filter_hdl == filter_handle)
			{
				channel_st = cur_channel_st;
				break;
			}
			cur_filter_st = cur_filter_st->next;
		}

		if (channel_st != LC_NULL)
		{
			break;
		}
		cur_channel_st = cur_channel_st->next;
	}

	return channel_st;
}

//return 0 if success
static long ld_section_callback(aui_hdl filter_handle,
                            unsigned char *p_section_data_buf_addr,
				            unsigned long ul_section_data_len,
				            void *usr_data,
				            void *reserved)
{
    //lc_filter_st *filter_st = LC_NULL;
    lc_channel_st * channel_st = LC_NULL;
    lc_buffer_st buffer_st = {0};
    lc_uint32 state =0;

	channel_st = get_channel_st_by_filter_hdl(filter_handle);
	LC_SPI_DMX_DEBUG ("section_callback``````````\n");

    if((LC_NULL != filter_handle) && (LC_NULL != channel_st)
        && (LC_DMX_MAGIC_CODE == ((lc_channel_st *)(channel_st))->magic_code))
    {
        state = channel_st->state;
        if(0 != state)// the filter is running.
        {
			LC_SPI_DMX_DEBUG ("\r\n filter[%08x] Got data length[%d], first 5 bytes:\n[%02x][%02x][%02x][%02x][%02x]\n",
		        filter_handle,ul_section_data_len,
		        (lc_uchar)*p_section_data_buf_addr, (lc_uchar)*(p_section_data_buf_addr + 1), (lc_uchar)*(p_section_data_buf_addr + 2),
		        (lc_uchar)*(p_section_data_buf_addr + 3), (lc_uchar)*(p_section_data_buf_addr + 4));
			
            buffer_st.bytes = p_section_data_buf_addr;
            buffer_st.length = ul_section_data_len;
            return channel_st->notify_cb(channel_st, &buffer_st);
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        return -1;
    }
}

static void add_channel_st_to_list (lc_channel_st *pchannel_st)
{
	lc_channel_st *ch = channel_list;
	lc_channel_st *prev_ch = LC_NULL;

	if (LC_NULL == channel_list)
	{
		channel_list = pchannel_st;
	}
	else
	{
		while (LC_NULL != ch)
		{
			prev_ch = ch;
			ch = ch->next;
		}			
		prev_ch->next = pchannel_st;
	}
	return;
}

static void remove_channel_st_from_list (lc_channel_st *pchannel_st)
{
	lc_channel_st *ch = channel_list;
	lc_channel_st *prev_ch = LC_NULL;

	if (pchannel_st == channel_list)
	{
		channel_list = LC_NULL;
	}
	else
	{
		while (pchannel_st != ch)
		{
			prev_ch = ch;
			ch = ch->next;
		}			
		prev_ch->next = ch->next;
	}
	
	return;
}

static void release_rescourse(aui_hdl *dmx_hdl,aui_hdl *channel_hdl,lc_channel_st **pchannel_st)
{
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    
    if(LC_NULL != channel_hdl)
    {
        rtn = aui_dmx_channel_stop(*channel_hdl, LC_NULL);
        if(AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("aui_dmx_channel_stop failed\n");
        }
        rtn = aui_dmx_channel_close(*channel_hdl);
        if(AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("aui_dmx_channel_close\n");
        }
        *channel_hdl =LC_NULL;
    }
#if 0 //the dmx device will not be close.
    if(LC_NULL != dmx_hdl)
    {
        rtn = aui_dmx_stop(*dmx_hdl,LC_NULL);
        if(AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("aui_dmx_stop failed\n");
        }
        rtn = aui_dmx_close(*dmx_hdl);
        if(AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("aui_dmx_close failed\n");
        }
        *dmx_hdl = LC_NULL;
    }
#endif    
    if((LC_NULL != pchannel_st) && (LC_NULL != *pchannel_st))
    {
		remove_channel_st_from_list (*pchannel_st);
        LoaderCoreSPI_Memory_Free(*pchannel_st);
        *pchannel_st = LC_NULL;
    }
}

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
lc_result LoaderCoreSPI_DEMUX_OpenChannel(lc_handle *pChannelHandle, lc_channel_info *pChannelInfo, lc_demux_data_notify_callback callbackFunction)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_channel_st *pchannel_st = LC_NULL;
    oem_private_data *priv_data = LC_NULL;
	int dmx_id = 0;
    aui_attr_dmx attr_dmx;
    aui_hdl dmx_hdl = LC_NULL;
    aui_hdl channel_hdl = LC_NULL;
    aui_attr_dmx_channel attr_dmx_channel = { 0 };
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;

    if((LC_NULL == pChannelHandle)|| (LC_NULL == pChannelInfo) || ( LC_CHANNEL_TYPE_IP < pChannelInfo->channelType))
    {
        LC_SPI_DMX_DEBUG("Invalid Input\n");
        lc_ret = LC_ERROR_NULL_PARAM;
    }
    else
    {
        pchannel_st = (lc_channel_st *)LoaderCoreSPI_Memory_Malloc(sizeof(lc_channel_st));
        if(LC_NULL == pchannel_st)
        {
            LC_SPI_DMX_DEBUG("MALLOC FAIL!!!!\n");
            lc_ret = LC_FAILURE;
        }
        else
        {
			LoaderCoreSPI_Stdlib_memset(pchannel_st, 0, sizeof(lc_channel_st));
			
            pchannel_st->magic_code = LC_DMX_MAGIC_CODE;
            pchannel_st->channel_info = pChannelInfo;
            pchannel_st->notify_cb = callbackFunction;

            priv_data = (oem_private_data *)pchannel_st->channel_info->manufacturerPrivateInfo;
            //dmx_id = priv_data->dmx_id;                    //
            dmx_id = 1;                 
            LC_SPI_DMX_DEBUG("dmx_id = %d,nim_id = %d,dmod_type = %d,freq = %d!\n",dmx_id,priv_data->nim_id,priv_data->dmod_type,priv_data->freq);
            if(AUI_RTN_SUCCESS != aui_find_dev_by_idx(AUI_MODULE_DMX, dmx_id, &dmx_hdl))
            {
	            LoaderCoreSPI_Stdlib_memset(&attr_dmx, 0, sizeof(attr_dmx));
	            attr_dmx.uc_dev_idx = (unsigned char)dmx_id;
                if (AUI_RTN_SUCCESS != aui_dmx_open(&attr_dmx, &dmx_hdl))
                {
                    LC_SPI_DMX_DEBUG("dmx open failed\n");
                    lc_ret = LC_FAILURE;
                    release_rescourse(&dmx_hdl,&channel_hdl,&pchannel_st);
                    return lc_ret;
                }
                LC_SPI_DMX_DEBUG("aui_dmx_open success\n");
            }
            
            if (AUI_RTN_SUCCESS != aui_dmx_start(dmx_hdl, LC_NULL))
            {
                LC_SPI_DMX_DEBUG("dmx start failed\n");
                lc_ret =  LC_FAILURE;
                release_rescourse(&dmx_hdl,&channel_hdl,&pchannel_st);
                return lc_ret;
            }
            pchannel_st->dmx_hdl = dmx_hdl;
            
            LoaderCoreSPI_Stdlib_memset(&attr_dmx_channel, 0, sizeof(attr_dmx_channel));
            attr_dmx_channel.us_pid = pchannel_st->channel_info->channel.dvbChannel.pid;
            attr_dmx_channel.dmx_data_type = AUI_DMX_DATA_SECT;
			//attr_dmx_channel.dmx_channel_sec_sync_get_data_support = 1;
            rtn = aui_dmx_channel_open( dmx_hdl, \
                                        &attr_dmx_channel, \
                                        &channel_hdl);
            if (AUI_RTN_SUCCESS != rtn)
            {
                LC_SPI_DMX_DEBUG("ERROR: %s: %d\n", __FUNCTION__, __LINE__);
                lc_ret = LC_FAILURE;
                release_rescourse(&dmx_hdl,&channel_hdl,&pchannel_st);
                return lc_ret;
            }
            
            rtn = aui_dmx_channel_start(channel_hdl, &attr_dmx_channel);
            if (AUI_RTN_SUCCESS != rtn)
            {
                LC_SPI_DMX_DEBUG("ERROR: %s: %d\n", __FUNCTION__, __LINE__);
                lc_ret = LC_FAILURE;
                release_rescourse(&dmx_hdl,&channel_hdl,&pchannel_st);
                return lc_ret;
            }
            pchannel_st->channel_hdl = channel_hdl;

			add_channel_st_to_list (pchannel_st);
            *pChannelHandle = (lc_handle)pchannel_st;
        }
        
    }
	return lc_ret;
}


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
lc_result LoaderCoreSPI_DEMUX_CloseChannel(lc_handle channelHandle)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_channel_st *pchannel_st = LC_NULL;
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    aui_hdl channel_hdl =LC_NULL;

    
    pchannel_st = (lc_channel_st *)channelHandle;
    if((LC_NULL != pchannel_st) && (LC_DMX_MAGIC_CODE == pchannel_st->magic_code))
    {
        if(1 == pchannel_st->state)
        {
            LoaderCoreSPI_DEMUX_StopChannel(channelHandle);
        }
        channel_hdl = pchannel_st->channel_hdl;
        release_rescourse(LC_NULL,&channel_hdl,&pchannel_st);
    }
    else
    {
        lc_ret = LC_ERROR_NULL_PARAM;
        LC_SPI_DMX_DEBUG("The input hannel is invalid\n");
    }
	return lc_ret;
}


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
lc_result LoaderCoreSPI_DEMUX_StartChannel(lc_handle channelHandle)
{
    lc_channel_st *pchannel_st = LC_NULL;
    lc_result lc_ret = LC_SUCCESS;
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_filter_st  *filter_st = LC_NULL;
    lc_uint16 i =0;
    
    pchannel_st = (lc_channel_st *)channelHandle;
    if((LC_NULL != pchannel_st) && (LC_DMX_MAGIC_CODE == pchannel_st->magic_code))
    {

        //start all the filter
        filter_st = pchannel_st->filter_st;
        while(LC_NULL != filter_st)
        {
            rtn = aui_dmx_filter_start(filter_st->filter_hdl, &filter_st->attr_filter);
            if (AUI_RTN_SUCCESS != rtn)
            {
                LC_SPI_DMX_DEBUG("ERROR: the (%d) filter can not be start!%s: %d\n",i, __FUNCTION__, __LINE__);
            }
            filter_st = filter_st->next;
            i++;
        }
        pchannel_st->state =1;
    }
    else
    {
        lc_ret = LC_ERROR_NULL_PARAM;
    }
	return lc_ret;
}


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
 
 /* --This function will be return LC_SUCCESS
 The SPI driver can just simply return LC_SUCCESS to Loader Core, 
 and then Loader Core will wait for the callback event 
 which is triggered by lc_demux_data_notify_callback 
 passed through LoaderCoreSPI_DEMUX_OpenChannel.
 */
lc_result LoaderCoreSPI_DEMUX_RequestData(lc_handle channelHandle, lc_uint32 millisecondTimeout)
{    
    lc_result lc_ret = LC_SUCCESS;
    
    return lc_ret;
}



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
lc_result LoaderCoreSPI_DEMUX_StopChannel(lc_handle channelHandle)
{
    lc_filter_st  *filter_st = LC_NULL;
    lc_result lc_ret = LC_SUCCESS;
    lc_channel_st *pchannel_st = LC_NULL;
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_uint16 i =0;
    
    pchannel_st = (lc_channel_st *)channelHandle;
    if((LC_NULL != pchannel_st) && (LC_DMX_MAGIC_CODE == pchannel_st->magic_code))
    {
        filter_st = pchannel_st->filter_st;
        while(LC_NULL != filter_st->next)
        {
            rtn = aui_dmx_filter_stop(filter_st->filter_hdl, LC_NULL);
            if (AUI_RTN_SUCCESS != rtn)
            {
                LC_SPI_DMX_DEBUG("ERROR: the (%d) filter can not be stop!%s: %d\n",i, __FUNCTION__, __LINE__);
            }
            filter_st = filter_st->next;
            i++;
        }
        pchannel_st->state =0;
    }
    else
    {
        lc_ret = LC_ERROR_NULL_PARAM;
    }
    return lc_ret;
}



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
lc_result LoaderCoreSPI_DEMUX_OpenFilter(lc_handle channelHandle, lc_handle *pFilterHandle)
{
    
    lc_result lc_ret = LC_SUCCESS;
    lc_channel_st *pchannel_st = LC_NULL;
	int dmx_id = 0;
    aui_attr_dmx attr_dmx;
    aui_hdl dmx_hdl = LC_NULL;
    aui_hdl filter_hdl = LC_NULL;
    aui_attr_dmx_filter attr_dmx_filter = { 0 };
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_filter_st *filter_st = LC_NULL;
    lc_filter_st *filter_add = LC_NULL;

    
    pchannel_st = (lc_channel_st *)channelHandle;
    if((LC_NULL != pchannel_st) && (LC_DMX_MAGIC_CODE == pchannel_st->magic_code))
    {
        LoaderCoreSPI_Stdlib_memset(&attr_dmx_filter, 0, sizeof(aui_attr_dmx_filter));
        //attr_dmx_filter.usr_data = LC_NULL; // we do not use the usr data in the callback.
        //attr_dmx_filter.ul_mask_val_len = 0;
		//attr_dmx_filter.dmx_fil_sec_data_sync_get_support = 1;
        rtn = aui_dmx_filter_open(pchannel_st->channel_hdl,
                                    &attr_dmx_filter, &filter_hdl);
        if (AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("ERROR: %s: %d\n", __FUNCTION__, __LINE__);
            return LC_FAILURE;
        }
        
        filter_st = (lc_filter_st*)LoaderCoreSPI_Memory_Malloc(sizeof(lc_filter_st));
        if(LC_NULL == filter_st)
        {
            rtn = aui_dmx_filter_close(&filter_hdl);
            if (AUI_RTN_SUCCESS != rtn)
            {
                LC_SPI_DMX_DEBUG(   "dmx filter close fail filter_hdl(0x%08x)\n", \
                                    (lc_uint32)filter_hdl);
            }
            filter_hdl = LC_NULL;
            LC_SPI_DMX_DEBUG("filter malloc fail\n");
            return LC_FAILURE;
        }
        else
        {
			LoaderCoreSPI_Stdlib_memcpy (&filter_st->attr_filter, &attr_dmx_filter, sizeof (attr_dmx_filter));//filter_st->attr_filter = attr_dmx_filter;
            filter_st->channel_ptr = pchannel_st;
            filter_st->next = LC_NULL;
            filter_st->filter_hdl = filter_hdl;
        }
        
        filter_add = pchannel_st->filter_st;

        if(LC_NULL == filter_add)
        {
            pchannel_st->filter_st = filter_st;
        }
        else
        {
            while(LC_NULL != filter_add->next)
            {
                filter_add = filter_add->next;
            }
            filter_add = filter_st;
        }
        
        pchannel_st->filter_count++;
        *pFilterHandle = filter_st;
    }
    return lc_ret;
}


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
lc_result LoaderCoreSPI_DEMUX_SetFilter(lc_handle channelHandle, lc_handle filterHandle, lc_filter_info *pFilterInfo)
{
	lc_uint32 i = 0;
    lc_result lc_ret = LC_SUCCESS;
    lc_channel_st *pchannel_st = LC_NULL;
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_bool is_crc_check = LC_FALSE;
    lc_bool is_continual = LC_TRUE;;
    lc_filter_st *filter_st = LC_NULL;
    lc_char reserve[LC_MAX_FILTER_DEPTH] ={0};

    filter_st = (lc_filter_st *)filterHandle;
    pchannel_st = (lc_channel_st *)channelHandle;
    if((LC_NULL != pchannel_st) && (LC_NULL != filter_st)    // handle of filter and channel is valid.
        &&  (LC_DMX_MAGIC_CODE == pchannel_st->magic_code)   // the channel has been initalized.
        &&  (pchannel_st == filter_st->channel_ptr)          // filter is belong to the channel
        &&  LC_NULL != pFilterInfo)         
    {
		lc_uchar mask[LC_MAX_FILTER_DEPTH + 2] = {0};//aui max depth is 32.
		lc_uchar match[LC_MAX_FILTER_DEPTH + 2] = {0};
		lc_uint32 filterDepth = pFilterInfo->filterDepth;
		
        rtn = aui_dmx_reg_sect_call_back(filter_st->filter_hdl, ld_section_callback);
        if (AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("ERROR: %s: %d\n", __FUNCTION__, __LINE__);
            return LC_FAILURE;
        }

		//irdeto do not care about the section length bytes. skip it.
		if (pFilterInfo->filterDepth > 1)
		{
			filterDepth = pFilterInfo->filterDepth + 2;
		}
		
		for (i = 0; i < pFilterInfo->filterDepth; i++)
		{
			if (i == 0)
			{
				mask[i] = pFilterInfo->mask[i];
				match[i] = pFilterInfo->match[i];
			}
			else
			{
				mask[i+2] = pFilterInfo->mask[i];
				match[i+2] = pFilterInfo->match[i];
			}
		}

		
		LC_SPI_DMX_DEBUG ("\r\n filter[%08x] filterDepth[%d]\nmask 5 bytes:[%02x][%02x][%02x][%02x][%02x]\nmatch 5 bytes:[%02x][%02x][%02x][%02x][%02x]\n",
	        filter_st->filter_hdl, filterDepth,
	        (lc_uchar)mask[0], (lc_uchar)mask[1], (lc_uchar)mask[2], (lc_uchar)mask[3], (lc_uchar)mask[4],
	        (lc_uchar)match[0], (lc_uchar)match[1], (lc_uchar)match[2], (lc_uchar)match[3], (lc_uchar)match[4]);

        //in aui when rserver is 0, mask will be used. or mask will not be used.
        rtn = aui_dmx_filter_mask_val_cfg( filter_st->filter_hdl,
                                    mask,
                                    match,
                                    reserve,   
                                    filterDepth,
                                    is_crc_check,
                                    is_continual);
        if (AUI_RTN_SUCCESS != rtn)
        {
            LC_SPI_DMX_DEBUG("ERROR: %s: %d\n", __FUNCTION__, __LINE__);
            return LC_FAILURE;
        }
                    
    }
    return lc_ret;
}


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

lc_result LoaderCoreSPI_DEMUX_CloseFilter(lc_handle channelHandle, lc_handle filterHandle)
{
    
    lc_result lc_ret = LC_SUCCESS;
    lc_channel_st *pchannel_st = LC_NULL;
    lc_uint16 depth =0;
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_bool is_crc_check = LC_TRUE;
    lc_bool is_continual = LC_TRUE;
    lc_filter_st *filter_st = LC_NULL;
    lc_filter_st *filter_priv = LC_NULL;

    filter_st = (lc_filter_st *)filterHandle;
    pchannel_st = (lc_channel_st *)channelHandle;
    if((LC_NULL != pchannel_st) && (LC_NULL != filter_st)         // handle of filter and channel is valid.
        &&  (LC_DMX_MAGIC_CODE == pchannel_st->magic_code)  // the channel has been initalized.
        &&  (pchannel_st == filter_st->channel_ptr))        // filter is belong to the channel
    {
        rtn = aui_dmx_filter_close(&filter_st->filter_hdl);
        if (AUI_RTN_SUCCESS != rtn)
        {
           //the function should not be return here.
           LC_SPI_DMX_DEBUG(   "dmx filter close fail filter_hdl(0x%08x)\n", \
                               (lc_uint32)filter_st->filter_hdl);
        }
        filter_st->filter_hdl = 0;
        if(1 == pchannel_st->filter_count)
        {
            LoaderCoreSPI_Memory_Free(filter_st);
            filter_st = LC_NULL;
            pchannel_st->filter_st = LC_NULL;
        }
        else
        {
            filter_priv = pchannel_st->filter_st;
            while(filter_st != filter_priv->next)
            {
                filter_priv= filter_priv->next;
            }
            filter_priv->next = filter_st->next;
            LoaderCoreSPI_Memory_Free(filter_st);
            filter_st = LC_NULL;
        }
        pchannel_st->filter_count--;
    }
    return lc_ret;
}


/** @} */ /* End of Loader Core DEMUX SPIs */

/** @} */ /* End of Loader Core SPIs */


