
#ifndef PVRFINGERPRINTTYPE_H_
#define PVRFINGERPRINTTYPE_H_

enum PVR_FP_TYPE{
    E_NO_SHOW_FP,				//不显示指纹
    E_SHOW_LIVE_FP,				//显示直播节目的指纹
    E_SHOW_PLAYBACK_CHANNEL_FP, //显示时移或回放节目的实时指纹
    E_SHOW_RECORD_FP,			//显示录制下来的指纹
    E_SHOW_RECORD_AND_LIVE_FP,   //显示录制下来的指纹和直播指纹
    E_PVR_FP_TYPE_MAX
};

#endif /* PVRFINGERPRINTTYPE_H_ */
