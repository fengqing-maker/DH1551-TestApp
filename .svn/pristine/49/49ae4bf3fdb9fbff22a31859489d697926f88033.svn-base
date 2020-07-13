
#ifndef DEMUX_MANAGER_H__INCLUDED__
#define DEMUX_MANAGER_H__INCLUDED__
/*DemuxManager will act as DVB SSU adapter and IP adapter, since they both use DEMUX SPIs.*/

#ifdef __cplusplus
extern "C" {
#endif

/** Initialize this DemuxManager.*/
lc_result LC_InitializeDemuxManager(void);

/*Open demux, i.e. open channel/filter or socket.*/
lc_result LC_OpenDemux(lc_channel_info *pChannelInfo);

/*Set filter conditions. This function is needed only when the channel is a DVB channel.*/
lc_result LC_SetFilter(lc_filter_info *pFilterInfo);

/*Start demux now.*/
lc_result LC_StartDemux(void);

/*Stop demux. */
lc_result LC_StopDemux(void);

/*This function will try to get a section or IP datagram from DEMUX. Note that the return buffer must NOT be free!!!!!!!*/
lc_result LC_ReadSection(lc_uchar **ppSectionBuffer,
                         lc_uint32 *pSectionLength,
                         lc_uint32 millisecondTimeout);


/*To finilize DemuxManager module.*/
lc_result LC_FinalizedDemuxManager(void);

#ifdef __cplusplus
}
#endif

#endif /* !DEMUX_MANAGER_H__INCLUDED__ */

