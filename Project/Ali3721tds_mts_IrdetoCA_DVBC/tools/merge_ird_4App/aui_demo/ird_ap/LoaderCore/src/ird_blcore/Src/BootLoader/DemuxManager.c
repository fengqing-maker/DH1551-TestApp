
/******************************************************************************
 *                    COPYRIGHT (C) 2011 IRDETO B.V.                          *
 ******************************************************************************
 * FILENAME   : DemuxManager.c                                                *
 *                                                                            *
 ******************************************************************************/


#include "../Shared/LoaderCorePrivate.h"
#include "List.h"

/**
 * Global variable to save channel handle and filter handle.
 * In most case, we will only need one channel and one filter, since sections are transmitted in the same PID or IP/port.
 */
static lc_handle gChannelHandle = LC_INVALID_HANDLE;
static lc_handle gFilterHandle = LC_INVALID_HANDLE;

/** Let's use semaphore to act as mutex to protect the data list.*/
static lc_handle gDemuxMutex = LC_INVALID_HANDLE;

/** Use a semaphore to signal that a section or packet has been received.*/
static lc_handle gDemuxSemaphore = LC_INVALID_HANDLE;

/** A list to hold incoming data section/packet.*/
static List *gDataList = LC_NULL;

/*Global buffer for section or IP datagram.*/
static lc_uchar gSectionBuffer[5000];

static lc_result LC_NotifyDemuxData(lc_handle channelHandle, lc_buffer_st *pData)
{
    lc_result result = LC_SUCCESS;
    ListNode *pNewDataNode = LC_NULL;
    lc_result tmp_result = LC_FAILURE;

    LC_UNUSED(channelHandle);

    if(LC_NULL == pData)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if(LC_SUCCESS == result)
    {
        result = LC_CheckType_Bytes(pData);
    }

    if(LC_SUCCESS == result && LC_INVALID_HANDLE != gDemuxSemaphore)
    {
        /*To protect the list.*/
        LoaderCoreSPI_Semaphore_WaitTimeout(gDemuxMutex,0);
        
        /*Save the data.*/
        tmp_result = ListAppend(gDataList,pData->bytes,pData->length);
        
        /*End of protecting the list.*/
        LoaderCoreSPI_Semaphore_Post(gDemuxMutex);

        if(LC_SUCCESS == tmp_result)
        {
            /*If the data is saved successfully, now we can signal an incoming data.*/
            LoaderCoreSPI_Semaphore_Post(gDemuxSemaphore);
        }
    }

    return result;
}


/** Initialize this DemuxManager.*/
lc_result LC_InitializeDemuxManager(void)
{
    lc_result result = LC_SUCCESS;

    if(LC_SUCCESS == result)
    {
        /*Init variables.*/
        gChannelHandle = LC_INVALID_HANDLE;
        gFilterHandle = LC_INVALID_HANDLE;
        gDemuxSemaphore = LC_INVALID_HANDLE;
        gDemuxMutex = LC_INVALID_HANDLE;
        gDataList = LC_NULL;
    }

    if(LC_SUCCESS == result)
    {
        /*Create a semaphore to act as a mutex. Note that the initial value is 1.*/
        result = LoaderCoreSPI_Semaphore_Open(1, &gDemuxMutex);
    }

    if(LC_SUCCESS == result)
    {
        /*Create a list to hold sections/packets.*/
        gDataList = ListCreate();
    }

    if(LC_SUCCESS == result)
    {
        if(LC_NULL == gDataList)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    return result;

}


/*Open demux, i.e. open channel/filter or socket.*/
lc_result LC_OpenDemux(lc_channel_info *pChannelInfo)
{
    lc_result result = LC_SUCCESS;

    /*Check whether we need to open the channel.*/
    if(LC_INVALID_HANDLE == gChannelHandle)
    {
        /*Open a channel for the first time.*/
        result = LoaderCoreSPI_DEMUX_OpenChannel(&gChannelHandle, pChannelInfo,LC_NotifyDemuxData);
    }

    /*Check whether the handle is valid.*/
    if(LC_INVALID_HANDLE == gChannelHandle)
    {
        result = LC_ERROR_INVALID_HANDLE;
    }

    if(LC_SUCCESS == result)
    {
        /*If it is a DVB channel, we will need to open a filter for it.*/
        if(LC_CHANNEL_TYPE_DVB == pChannelInfo->channelType)
        {
            result = LoaderCoreSPI_DEMUX_OpenFilter(gChannelHandle,&gFilterHandle);
            if(LC_SUCCESS == result)
            {
                /*Check whether the filter handle has been allocated successfully.*/
                if(LC_INVALID_HANDLE == gFilterHandle)
                {
                    result = LC_ERROR_INVALID_HANDLE;
                }
            }
        }
    }
    return result;
}

/*Set filter conditions. This function is needed only when the channel is a DVB channel.*/
lc_result LC_SetFilter(lc_filter_info *pFilterInfo)
{
    lc_result result = LC_SUCCESS;

    /*Check whether the handle is valid.*/
    if(LC_INVALID_HANDLE == gFilterHandle)
    {
        result = LC_ERROR_INVALID_HANDLE;
    }

    if(LC_SUCCESS == result)
    {
        /*Set the conditions to the SPI driver.*/
        result = LoaderCoreSPI_DEMUX_SetFilter(gChannelHandle, gFilterHandle, pFilterInfo);
    }

    return result;
}

/*Start demux now.*/
lc_result LC_StartDemux(void)
{
    lc_result result = LC_SUCCESS;

    /*Check whether the handle is valid.*/
    if(LC_INVALID_HANDLE == gChannelHandle)
    {
        result = LC_ERROR_INVALID_HANDLE;
    }

    if(LC_SUCCESS == result)
    {
        /*Create a semaphore to signal incoming data.*/
        result = LoaderCoreSPI_Semaphore_Open(0, &gDemuxSemaphore);
    }

    if(LC_SUCCESS == result)
    {
        /*Start the channel now. Once the channel is started, you can call LC_GetSection to read in a section/packet.*/
        result = LoaderCoreSPI_DEMUX_StartChannel(gChannelHandle);
    }

    return result;

}

/*Stop demux now.*/
lc_result LC_StopDemux(void)
{
    lc_result result = LC_SUCCESS;
    ListNode *pNode = LC_NULL;

    /*Check whether the handle is valid.*/
    if(LC_INVALID_HANDLE == gChannelHandle)
    {
        result = LC_ERROR_INVALID_HANDLE;
    }

    if(LC_SUCCESS == result)
    {
        /*Stop the channel now. Once the channel is started, you can call LC_GetSection to read in a section/packet.*/
        result = LoaderCoreSPI_DEMUX_StopChannel(gChannelHandle);
    }

    if(LC_SUCCESS == result)
    {
        if(LC_INVALID_HANDLE != gDemuxSemaphore)
        {
            LoaderCoreSPI_Semaphore_Close(&gDemuxSemaphore);
        }
    }

    if(LC_SUCCESS == result)
    {
        
        /*To protect the list.*/
        LoaderCoreSPI_Semaphore_WaitTimeout(gDemuxMutex, 0);

        /* Empty the data buffer list */
        if(gDataList)
        {
            while (LC_NULL != (pNode = ListGetFirst(gDataList)) )
            {
                /*Remove it from the list and also free the buffer. */
                ListDeleteNode(gDataList, pNode, LC_TRUE);
            }
        }
                
        /*End of protecting the list.*/
        LoaderCoreSPI_Semaphore_Post(gDemuxMutex);
        
    }

    return result;

}


/*This function will try to get a section from DEMUX.*/
lc_result LC_ReadSection(lc_uchar **ppSectionBuffer,
                         lc_uint32 *pSectionLength,
                         lc_uint32 millisecondTimeout)
{
    lc_result result = LC_SUCCESS;
    ListNode *pNode = LC_NULL;
    lc_uchar *pDataBuffer = LC_NULL;
    lc_uint32 dataLength = 0;

    *ppSectionBuffer = LC_NULL;
    *pSectionLength = 0;

    /*Give the SPI driver a chance to request data in case they don't have multiple task support or the demux driver doesn't use callback mechanism.*/
    result = LoaderCoreSPI_DEMUX_RequestData(gChannelHandle, millisecondTimeout);

    if(LC_SUCCESS == result)
    {
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!OK. We can wait for the semaphore indicating an incoming section or packet.*/
        result = LoaderCoreSPI_Semaphore_WaitTimeout(gDemuxSemaphore,millisecondTimeout);
    }

    if(LC_SUCCESS == result)
    {
        /*OK. We have got a section here.*/

        /*To protect the list.*/
        LoaderCoreSPI_Semaphore_WaitTimeout(gDemuxMutex, 0);

        LC_ASSERT(0 != ListGetCount(gDataList));

        /*Get the first key event from the list.*/
        pNode = ListGetFirst(gDataList);
        if(pNode)
        {
            /* Just set the pointer to the buffer. Reuse the buffer allocated previously. 
             * Keep the logic simple, so that we will not block others from pushing data into the list.
             */
            pDataBuffer = pNode->pData;
            dataLength = pNode->dataLength;

            /*Remove it from the list. Set the last parameter to FALSE.*/
            ListDeleteNode(gDataList,pNode,LC_FALSE);
        }
 
        LoaderCoreSPI_Semaphore_Post(gDemuxMutex);

        /*Make a copy and free the old one.*/
        if(pDataBuffer)
        {            
            LC_memset(gSectionBuffer, 0x0, sizeof(gSectionBuffer));

            LC_memcpy(gSectionBuffer, pDataBuffer, dataLength);

            /*Free the old buffer.*/
            LC_Free_Memory((void **)&pDataBuffer);

            /*Make a copy to global section buffer so that we will not overflow in some special case.*/
            *ppSectionBuffer = gSectionBuffer;
            *pSectionLength = dataLength;
        }
    }

    return result;
}

/*To finilize DemuxManager module.*/
lc_result LC_FinalizedDemuxManager(void)
{
    lc_result result = LC_SUCCESS;

    if(LC_INVALID_HANDLE != gChannelHandle)
    {
        /*Free all demux related resources.*/
        LoaderCoreSPI_DEMUX_StopChannel(gChannelHandle);
        if(LC_INVALID_HANDLE != gFilterHandle)
        {
            LoaderCoreSPI_DEMUX_CloseFilter(gChannelHandle, gFilterHandle);
        }
        LoaderCoreSPI_DEMUX_CloseChannel(gChannelHandle);
    }

    if(LC_INVALID_HANDLE != gDemuxSemaphore)
    {
        LoaderCoreSPI_Semaphore_Close(&gDemuxSemaphore);
    }

    if(LC_INVALID_HANDLE != gDemuxMutex)
    {
        LoaderCoreSPI_Semaphore_Close(&gDemuxMutex);
    }

    if(gDataList)
    {
        ListDestroy(gDataList, LC_TRUE);
    }

    return result;
}

