#ifndef REQUEST_VIDEO_AND_AUDIO_FRAME_H_
#define REQUEST_VIDEO_AND_AUDIO_FRAME_H_

#include "RequestTableNotify.h"
#include "APSafeThread.h"
#include "AVConfig.h"
#include "APLock.h"
#include "adi_public.h"

#define VID_STREAM_MPEG1 1
#define VID_STREAM_MPEG2 2
#define VID_STREAM_H264 27
#define VID_STREAM_VC1 234
#define AUD_STREAM_MPEG1 3
#define AUD_STREAM_MPEG2 4
#define AUD_STREAM_MPEG_AAC 17
#define AUD_STREAM_LPCM 128
#define AUD_STREAM_AC3 129
#define AUD_STREAM_AC3_2 6
#define AUD_STREAM_DTS 130
#define AUD_STREAM_AC3_PLUS 132
#define AUD_STREAM_DTS_HD 133

class RequestVideoAndAudioFrame : public APSafeThread
{
public:
	RequestVideoAndAudioFrame(unsigned int unTunerID, RequestTableNotify *pRequestTableNotify);
	~RequestVideoAndAudioFrame();

public:
	void OnceProcess();
	unsigned int StartLock(ADITunerSRCDeliver_U* pDelivery);
	unsigned int StartPlayer(int nVideoPid, int nAudioPid);
	unsigned int StartPlayer(ServiceInfo_S * pServiceList);
	ADIVIDStreamType_E MapVideoType(int nVideoType);
	ADIAUDStreamType_E MapAudioType(int nAudioType);
	void VideoFrameComingNotify();
	void AudioFrameComingNotify();
	void SetAVConfig(AVConfig *pAVConfig);
	unsigned int Stop();

public:
	RequestTableNotify *m_pRequestTableNotify;
	unsigned int m_unTunerID;
	unsigned int m_unLockStatus;
	ADI_HANDLE m_hDecoder;
	unsigned int m_unDecoderStatus; //1<<0, video frame coming; 1<<1, audio frame coming
	AVConfig m_AVConfig;
	unsigned int m_unTickCount;
	APLock m_APLock;
	ADITunerSRCDeliver_U m_curLockDelivery;
	unsigned int m_unPlayerStatus;
};

#endif/*REQUEST_VIDEO_AND_AUDIO_FRAME_H_*/
