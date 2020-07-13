/*
 * PVRInitInterface.h
 *
 *  Created on: 2016-8-5
 *      Author: linc
 */

#ifndef PVRINITINTERFACE_H_
#define PVRINITINTERFACE_H_
#include "PVRSolutionType.h"
#include "PVROSDMode.h"
#include "PVRFingerPrintType.h"
#include "adi_record.h"
#include "AudioComponentPrioritySpec.h"


class PVRInitInterface
{
public:

    PVRInitInterface ( );
    virtual ~PVRInitInterface ( );

    virtual PVRSolutionType GetPVRSolutionType ( ) = 0;

    virtual void SetTShiftBufSize ( unsigned int unTShiftBufSize ) = 0;
    virtual unsigned int GetTShiftBufSize ( ) = 0;
    virtual void SetEITLockLevel ( unsigned char ucEITLockLevel ) = 0;
    virtual unsigned char GetEITLockLevel ( ) = 0;
    virtual void SetSMCLockLevel ( unsigned char ucSMCLockLevel ) = 0;
    virtual unsigned char GetSMCLockLevel ( ) = 0;

    virtual unsigned int CheckPVRWorking ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    //PVR静音状态与直播保持一致
    //若不想一致不调此接口即可
    virtual void NotifyPVRMuteStatus ( unsigned int unMute ) = 0;
    virtual unsigned int GetLiveMuteStatus ( ) = 0;

    //设置时移或者回放时显示哪的指纹(具有请看PVR_FP_TYPE)
    virtual void SetPVRFPType ( PVR_FP_TYPE enType ) = 0;
    virtual PVR_FP_TYPE GetPVRFPType ( ) = 0;

    //设置二次加密方式(详看ADIStreamEncryptType_E)
    virtual void SetEncryptType ( ADIStreamEncryptType_E eEncryptType ) = 0;
    virtual ADIStreamEncryptType_E GetEncryptType ( ) = 0;

    //设置FTA节目是否要加密，默认是要加密的。
    virtual void SetEncryptFTAServiceFlag ( unsigned int unIsEncryptFTAService ) = 0;
    virtual unsigned int GetEncryptFTAServiceFlag ( ) = 0;

    //设置时移或者回放时是否显示OSD
    virtual void SetPVROSDMode ( PVR_OSD_MODE enMode ) = 0;
    virtual PVR_OSD_MODE GetPVROSDMode ( ) = 0;

    //unRecordOnlyLiveChannel=1表示当前不支持播A录B模式
    virtual void SetRecordOnlyLiveChannel ( unsigned int unRecordOnlyLiveChannel ) = 0;
    virtual unsigned int IsRecordOnlyLiveChannel ( ) = 0;

    //ucPlayLastPostion=1表示播放上次退出文件时的位置
    virtual void SetPlayPosMode ( unsigned char ucPlayLastPostion ) = 0;
    virtual unsigned char GetPlayPosMode ( ) = 0;

    //设置用户喜爱的音频优先级规格，和直播大致一样。
    virtual unsigned int SetAudioPrioritySpec ( AudioComponentPrioritySpec* pAudioComponentPrioritySpec ) = 0;

    //当用户改变的第一音频语言、第二音频语言、AC3Preference、PreferenceAudioType、PreferenceAudioFormat等相关Audio操作的时候调用此接口。
    virtual unsigned int SwitchAuidoComponent ( ) = 0;

    //主要是给play用,因为start的是时候要根据优先级来选择哪路audio播放。
    virtual AudioComponentPrioritySpec* GetAudioComponentPrioritySpec ( ) = 0;

	//加扰节目是否需要检测当前播放的文件有无授权,默认为不检测
	virtual void SetCheckECMMode ( unsigned char ucCheck ) = 0;
    virtual unsigned char IsCheckECM ( ) = 0;

	//时移最小录制时间,小于此时间不能播放,默认为5秒
	virtual void SetMinTShiftDuration ( unsigned int unSecond ) = 0;
    virtual unsigned int GetMinTShiftDuration ( ) = 0;

	//unMode:0-->PVR与Media可以共存; 1-->PVR与Media共用内存,同时只能存在一个
	virtual void SetPVRWithMediaMode(unsigned int unMode) = 0;
 	virtual unsigned int GetPVRWithMediaMode ( ) = 0;
};
#endif /* PVRINITINTERFACE_H_ */
