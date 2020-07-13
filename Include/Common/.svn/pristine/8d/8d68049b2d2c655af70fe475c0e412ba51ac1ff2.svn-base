

#ifndef __APSAFESTRING_H
#define __APSAFESTRING_H

#define STRINGMAXCOUNT 100
#define STRINGMAXLEN   32

enum SafeString
{
	E_PVR_PATH,						//"PVR"
	E_RECORD_PATH,					//"REC"
	E_TSHIFT_PATH,					//"TSHIFT"
	E_REC_FILE_NAME,				//"record"
	E_PVR_INFO_FILE_NAME,			//"RECInfo.bin"
	E_PVR_FP_INFO_FILE_NAME,		//"FPInfo.dvr"
	E_PVR_OSD_INFO_FILE_NAME,		//"OSDInfo.dvr"
	E_PVR_URI_INFO_FILE_NAME,		//"URIInfo.dvr"
	E_MEDIA_SCAN_THREAD,			//"MediaScanThread"
	E_MEDIA_SCAN_QUEUE,				//"MediaScanQueue"
	
	E_MP3_THREAD,					//"Mp3Thread"
	E_MP3_QUEUE,					//"Mp3Queue"
	E_MP3_DECODER_THREAD,			//"Mp3DecoderThread"
	E_MP3_DECODER_QUEUE,			//"Mp3DecoderQueue"
	E_PVRSCAN_THREAD,				//"PVRScanThread"
	E_PVRSCAN_QUEUE,				//"PVRScanQueue"
	E_ASYNCFLASH_THREAD,			//"AsyncFlashThread"
	E_CONTAINERPLAYER_THREAD,		//"ContainerPlayerThread"
	E_CONTAINERPLAYER_QUEUE,		//"ContainerPlayerQueue"
	E_TUNERSEARCHER_THREAD,			//"TunerSearcherThread"
	
	E_TUNERSEARCHER_QUEUE,			//"TunerSearcherQueue"
	E_SERVICEPLAYER_THREAD,			//"ServicesPlayerThread"
	E_SERVICEPLAYER_QUEUE,			//"ServicesPlayerQueue"
	E_TIMER_THREAD,					//"TimerThread
	E_SUBTITLE_THREAD,				//"SubTitleThread"
	E_PES_THREAD,					//"PESThread"
	E_TELETEST_QUEUE,				//"TeletextQueue"
	E_PCM_THREAD,					//"PCMThread"
	E_PCM_QUEUE,					//"PCMQueue"
	E_7SLED_THREAD,					//"7SLEDThread"
	
	E_REDLED_THREAD,				//"RedLEDThread"
	E_PHOTO_THREAD,					//"PhotoThread"
	E_SSURGACE_THREAD,				//"SSurfaceThread"
	E_ASURGACE_THREAD,				//"ASurfaceThread"
	E_ADMS_THREAD,					//"ADMSThread"
	E_PVR_PLAY,						//"PvrPlay"
	E_OTA,							//"OTA"
	E_RT,							//"RT "
	E_3DOT,							//"..."
	E_SPACE,						//" -"

	E_CASTPAL_STB,					//"CASTPAL-STB"
	E_PSIA,							//"PSIA"
	E_EPG,							//"EPG"
	E_PES,							//"PES"
	E_CA,							//"CA"
	E_BOUQUETID,					//"BouquetID"
	E_BOUQUETNAME,					//"BouquetName"
	E_CUSTOM,						//"Custom"
	E_FREQUENCY,					//"Frequency"
	E_LOCALNETWORK,					//"LocalNetwork"

	E_SERVICEID,					//"ServicesID"
	E_NETWORKID,					//"NetworkID"
	E_ORINETWORKID,					//"OriNetworkID"
	E_SERVICEAUXLOGICNUM,			//"ServiceAuxLogicNum"
	E_SERVICELOGICNUM,				//"ServiceLogicNum"
	E_SERVICENAME,					//"ServiceName"
	E_SATELLITE_S,					//"Satellite"
	E_TSID,							//"TSID"
    E_LOCK2UNLOCK,                  //"Lock2Unlock"
    E_PAY2FTA,                      //"Pay2FTA"
    E_TV2RADIO,                     //"TV2Radio"

    E_000TS_NAME,                   //"000.ts"
	E_PVR_ECM_INFO_FILE_NAME,		//"ECMInfo.dvr"
    E_DEFAULT_NETWORK_NAME,          //"Castpal Default"
    PVR_ECM_POS_FILE_NAME           //"ECMIndex.dvr"
};


#include <stdio.h>
#include "string.h"


class APSafeString
{

public:

	APSafeString ( );
	virtual ~APSafeString ( );

public:
	char * GetSafeString ( unsigned int unSafeStringIndex );

	unsigned int GetSafeString ( unsigned int unSafeStringIndex, char acSafeString [ ], unsigned int unSafeStringLen );

	unsigned int GetSafeStringLen ( unsigned int unSafeStringIndex );

private:

	char m_acString [ STRINGMAXLEN + 1 ];
};


#endif
