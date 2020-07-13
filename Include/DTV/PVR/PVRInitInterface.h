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

    //PVR����״̬��ֱ������һ��
    //������һ�²����˽ӿڼ���
    virtual void NotifyPVRMuteStatus ( unsigned int unMute ) = 0;
    virtual unsigned int GetLiveMuteStatus ( ) = 0;

    //����ʱ�ƻ��߻ط�ʱ��ʾ�ĵ�ָ��(�����뿴PVR_FP_TYPE)
    virtual void SetPVRFPType ( PVR_FP_TYPE enType ) = 0;
    virtual PVR_FP_TYPE GetPVRFPType ( ) = 0;

    //���ö��μ��ܷ�ʽ(�꿴ADIStreamEncryptType_E)
    virtual void SetEncryptType ( ADIStreamEncryptType_E eEncryptType ) = 0;
    virtual ADIStreamEncryptType_E GetEncryptType ( ) = 0;

    //����FTA��Ŀ�Ƿ�Ҫ���ܣ�Ĭ����Ҫ���ܵġ�
    virtual void SetEncryptFTAServiceFlag ( unsigned int unIsEncryptFTAService ) = 0;
    virtual unsigned int GetEncryptFTAServiceFlag ( ) = 0;

    //����ʱ�ƻ��߻ط�ʱ�Ƿ���ʾOSD
    virtual void SetPVROSDMode ( PVR_OSD_MODE enMode ) = 0;
    virtual PVR_OSD_MODE GetPVROSDMode ( ) = 0;

    //unRecordOnlyLiveChannel=1��ʾ��ǰ��֧�ֲ�A¼Bģʽ
    virtual void SetRecordOnlyLiveChannel ( unsigned int unRecordOnlyLiveChannel ) = 0;
    virtual unsigned int IsRecordOnlyLiveChannel ( ) = 0;

    //ucPlayLastPostion=1��ʾ�����ϴ��˳��ļ�ʱ��λ��
    virtual void SetPlayPosMode ( unsigned char ucPlayLastPostion ) = 0;
    virtual unsigned char GetPlayPosMode ( ) = 0;

    //�����û�ϲ������Ƶ���ȼ���񣬺�ֱ������һ����
    virtual unsigned int SetAudioPrioritySpec ( AudioComponentPrioritySpec* pAudioComponentPrioritySpec ) = 0;

    //���û��ı�ĵ�һ��Ƶ���ԡ��ڶ���Ƶ���ԡ�AC3Preference��PreferenceAudioType��PreferenceAudioFormat�����Audio������ʱ����ô˽ӿڡ�
    virtual unsigned int SwitchAuidoComponent ( ) = 0;

    //��Ҫ�Ǹ�play��,��Ϊstart����ʱ��Ҫ�������ȼ���ѡ����·audio���š�
    virtual AudioComponentPrioritySpec* GetAudioComponentPrioritySpec ( ) = 0;

	//���Ž�Ŀ�Ƿ���Ҫ��⵱ǰ���ŵ��ļ�������Ȩ,Ĭ��Ϊ�����
	virtual void SetCheckECMMode ( unsigned char ucCheck ) = 0;
    virtual unsigned char IsCheckECM ( ) = 0;

	//ʱ����С¼��ʱ��,С�ڴ�ʱ�䲻�ܲ���,Ĭ��Ϊ5��
	virtual void SetMinTShiftDuration ( unsigned int unSecond ) = 0;
    virtual unsigned int GetMinTShiftDuration ( ) = 0;

	//unMode:0-->PVR��Media���Թ���; 1-->PVR��Media�����ڴ�,ͬʱֻ�ܴ���һ��
	virtual void SetPVRWithMediaMode(unsigned int unMode) = 0;
 	virtual unsigned int GetPVRWithMediaMode ( ) = 0;
};
#endif /* PVRINITINTERFACE_H_ */
