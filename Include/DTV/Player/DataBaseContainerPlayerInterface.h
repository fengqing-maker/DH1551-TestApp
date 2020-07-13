/*
 * DataBaseContainerPlayerInterface.h
 *
 *  Created on: 2015-5-7
 *      Author: timothy.liao
 */

#ifndef DATABASECONTAINERPLAYERINTERFACE_H_
#define DATABASECONTAINERPLAYERINTERFACE_H_
#include "PlayLockInterface.h"
#include "DataBaseContainerPlayerNotify.h"
#include "../PVR/ActPVRFileUpdateNotify.h"
#include "../PVR/TimeShiftDecoderInterface.h"
#include "AudioComponentPrioritySpec.h"
#include "TeletextRenderingInterface.h"
#include "DisplayTeletextNotify.h"
#include "Delivery.h"
#include "AntennaInterface.h"
#include "VideoFormat.h"
#include "AudioFormat.h"
#include "CheckServiceSpec.h"
#include "ChannelNumberSpec.h"
#include "CheckServiceLockSpec.h"
#include "PGLockCheckSpec.h"
#include "ServiceProgramInfoNotify.h"
#include "adi_video.h"

class DataBaseContainerPlayerInterface
{
public:
    DataBaseContainerPlayerInterface ( );
    virtual ~DataBaseContainerPlayerInterface ( );

public:
    //play
    virtual unsigned int Play ( ) = 0;
    virtual unsigned int Play ( unsigned int unChannelNumber ) = 0;
    virtual unsigned int Play ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int Play ( ServiceInterface* pNVODService, Delivery* pDelivery, AntennaInterface* pAntennaInterface ) = 0;
    virtual unsigned int Play ( Delivery* pDelivery, AntennaInterface* pAntennaInterface, unsigned short usVideoPid, VideoFormat eVideoFormat, unsigned int short usAudioPid, AudioFormat eAudioFormat, unsigned short usPCRPid ) = 0;
    virtual unsigned int PlayStartCAOnly ( unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID ) = 0;
	virtual unsigned int PlayMosaicService(unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID) = 0;
    virtual unsigned int PlayPre ( ) = 0;
    virtual unsigned int PlayNext ( ) = 0;
    virtual unsigned int ReCall ( ) = 0;
    virtual unsigned int Stop ( ) = 0;
    virtual unsigned int StopSync ( ) = 0;
    virtual unsigned int StopDecoderOnly ( ) = 0;
    virtual unsigned int StopCAOnly ( ) = 0;
    virtual unsigned int Replay ( ) = 0;
    
    virtual unsigned int PlaySwitchTVRadio ( ) = 0;
    virtual unsigned int PlayLockSignalOnly ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int PlayLockSignalOnly ( Delivery * pDelivery, AntennaInterface* pAntennaInterface ) = 0;

    virtual unsigned int IsLivePlayWorking ( ) = 0;

    virtual unsigned int ShowIFrame ( unsigned char * pcBuf, unsigned int unLen ) = 0;
    virtual unsigned int CloseIframe ( ) = 0;

    virtual unsigned int StartPCMPlay ( unsigned char aucPCMData [ ], unsigned int unLength, unsigned int unRepeatTimes ) = 0;
    virtual unsigned int StopPCMPlay ( ) = 0;

    //Rendering
    virtual unsigned int EnableVideo ( ) = 0;
    virtual unsigned int DisableVideo ( ) = 0;
    virtual unsigned int EnableVideo ( unsigned short usMultiSource ) = 0;
    virtual unsigned int DisableVideo ( unsigned short usMultiSource ) = 0;
    virtual unsigned int SetActiveWindow ( int nX, int nY, unsigned int unW, unsigned int unH ) = 0;
    virtual unsigned int SetAspectRatio ( unsigned int unAspectRatio ) = 0;
    virtual unsigned int GetAspectRatio ( ) = 0;
    virtual unsigned int SetMatchMethod ( unsigned int unMatchMethod ) = 0;
    virtual unsigned int GetMatchMethod ( ) = 0;
    virtual unsigned int EnableAudio ( ) = 0;
    virtual unsigned int DisableAudio ( ) = 0;
    virtual unsigned int EnableAudio ( unsigned short usMultiSource ) = 0;
    virtual unsigned int DisableAudio ( unsigned short usMultiSource ) = 0;
    virtual unsigned int IsAudioMute ( ) = 0;
    virtual unsigned int TurnUpVolume ( ) = 0;
    virtual unsigned int TurnDownVolume ( ) = 0;
    virtual unsigned int SetVolume ( unsigned int unVolume ) = 0;
    virtual unsigned int GetVolume ( ) = 0;
    virtual unsigned int TurnUpADVolume ( ) = 0;
    virtual unsigned int TurnDownADVolume ( ) = 0;
    virtual unsigned int SetADVolume ( unsigned int unVolume ) = 0;
    virtual unsigned int GetADVolume ( ) = 0;
    virtual unsigned int SetAudioChannel ( unsigned int unChannel ) = 0;
    virtual unsigned int GetAudioChannel ( ) = 0;
    virtual unsigned int SetAudioOutputMode ( unsigned int unAOutMode ) = 0;
    virtual unsigned int GetAudioOutputMode ( ) = 0;
    virtual unsigned int EnableSubtitle ( ) = 0;
    virtual unsigned int DisableSubtitle ( ) = 0;
    virtual unsigned int EnableSubtitle ( unsigned short usMultiSource ) = 0;
    virtual unsigned int DisableSubtitle ( unsigned short usMultiSource ) = 0;
    virtual unsigned int EnableTeletext ( ) = 0;
    virtual unsigned int DisableTeletext ( ) = 0;
    virtual unsigned int EnableTeletext ( unsigned short usMultiSource ) = 0;
    virtual unsigned int DisableTeletext ( unsigned short usMultiSource ) = 0;
    virtual unsigned int EnableClosedCaption ( ) = 0;
    virtual unsigned int DisableClosedCaption ( ) = 0;

    //Standby
	virtual void Standby ( unsigned int unPassiveStandby, int nStandbyTime, unsigned int unIsShowTime ) = 0;
    virtual void Activate ( unsigned int unServiceGroup, unsigned int unServiceIndex ) = 0;
    virtual void Activate ( ) = 0;
    virtual unsigned int GetStandbyState ( ) = 0;

    //Screen Setting
    virtual unsigned int SetScreenResolution ( unsigned int unScreenDevice, unsigned int unResolution ) = 0;
    virtual unsigned int GetScreenResolution ( unsigned int unScreenDevice ) = 0;
    virtual unsigned int SetOSDTransparency ( int nTransparency ) = 0;
    virtual unsigned int GetOSDTransparency ( ) = 0;
    virtual unsigned int SetBrightness ( int nBrightness ) = 0;
    virtual unsigned int GetBrightness ( ) = 0;
    virtual unsigned int SetContrast ( int nContrast ) = 0;
    virtual unsigned int GetContrast ( ) = 0;
    virtual unsigned int SetSaturation ( int nSaturation ) = 0;
    virtual unsigned int GetSaturation ( ) = 0;

    //Configuration
    virtual unsigned int SetTimeZoneMode ( unsigned int unAutoTimeZone ) = 0;
    virtual unsigned int GetTimeZoneMode ( ) = 0;
    virtual unsigned int SetTimeZone ( unsigned int unTimeZone ) = 0;
    virtual unsigned int GetTimeZone ( ) = 0;
    virtual unsigned int SetSummerTime ( unsigned int unSummerTimeOn ) = 0;
    virtual unsigned int GetSummerTime ( ) = 0;
    virtual unsigned int SetCountryCode ( char aucCountryCode [ 3 ], unsigned char ucRegionId ) = 0;
    virtual unsigned int GetCountryCode ( char aucCountryCode [ 3 ], unsigned char &rucRegionId ) = 0;
    virtual unsigned int SetFirstAudioLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int GetFirstAudioLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int SetSecondAudioLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int GetSecondAudioLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int SetFirstSubtitleLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int GetFirstSubtitleLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int SetSecondSubtitleLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int GetSecondSubtitleLanguage ( char acLanguage [ 3 ] ) = 0;
    virtual unsigned int SetSubtitleOnOff ( unsigned int unOn ) = 0;
    virtual unsigned int GetSubtitleOnOff ( ) = 0;
    virtual unsigned int SetAC3Preference ( unsigned int unAC3Preference ) = 0;
    virtual unsigned int GetAC3Preference ( ) = 0;
    virtual unsigned int SetPreferenceAudioType ( unsigned int unPreferenceAudioType, unsigned int unNOT ) = 0;
    virtual unsigned int GetPreferenceAudioType ( unsigned int &unPreferenceAudioType, unsigned int &unNOT ) = 0;
    virtual unsigned int SetPreferenceAudioFormat ( unsigned int unPreferenceAudioFormat ) = 0;
    virtual unsigned int GetPreferenceAudioFormat ( ) = 0;
    virtual unsigned int SetAudioSubtitleSelectMode ( unsigned int unAudioSubtlSelectMode ) = 0;
    virtual unsigned int GetAudioSubtitleSelectMode ( ) = 0;
    virtual unsigned int SetAudioDescriptionOnOff ( unsigned int unOn ) = 0;
    virtual unsigned int GetAudioDescriptionOnOff ( ) = 0;
    virtual unsigned int SetSTBPGControlOff ( unsigned int ucOff ) = 0;
    virtual unsigned char GetSTBPGControlOff ( ) = 0;
    virtual unsigned int SetSTBPGLevel ( unsigned char ucPGLevel ) = 0;
    virtual unsigned char GetSTBPGLevel ( ) = 0;
    virtual unsigned int SetIndividualVolumeOnOff ( unsigned int unIndividualVolume ) = 0;
    virtual unsigned int GetIndividualVolumeOnOff ( ) = 0;
    virtual unsigned int SetIndividualAudioChannelOnOff ( unsigned int unIndividualAudioChannel ) = 0;
    virtual unsigned int GetIndividualAudioChannelOnOff ( ) = 0;
    virtual unsigned int SetIndividualAudioLanguageOnOff ( unsigned int unIndividualAudioLanguage ) = 0;
    virtual unsigned int GetIndividualAudioLanguageOnOff ( ) = 0;
    virtual unsigned int SetIndividualSubtitleLanguageOnOff ( unsigned int unIndividualSubtitleLanguage ) = 0;
    virtual unsigned int GetIndividualSubtitleLanguageOnOff ( ) = 0;
    virtual unsigned int SetHDMICECOnOff ( unsigned int unHDMICECOn ) = 0;
    virtual unsigned int GetHDMICECOnOff ( ) = 0;
    virtual unsigned int SetSTBPosition ( short sLongtitude, short sLatitude ) = 0;
    virtual unsigned int GetSTBPosition ( short &rsLongtitude, short &rsLatitude ) = 0;
    virtual unsigned int SetTeletextVBIOutput ( unsigned int unVBIOutputEnable ) = 0;
    virtual unsigned int GetTeletextVBIOutput ( ) = 0;
    virtual unsigned int SetClosedCaptionVBIOutput ( unsigned int unVBIOutputEnable ) = 0;
    virtual unsigned int GetClosedCaptionVBIOutput ( ) = 0;
    virtual unsigned int SetAutoVideoStandardMode ( unsigned int unAutoVideoStandardMode ) = 0;
    virtual unsigned int GetAutoVideoStandardMode ( ) = 0;
    virtual unsigned int SetVideoStopMode ( unsigned int unVideoStopMode ) = 0;
    virtual unsigned int GetVideoStopMode ( ) = 0;
    virtual unsigned int SetSCRUserBand ( unsigned int unTunerID, unsigned char ucUBNo, unsigned short usUBCenterFreq ) = 0;
    virtual unsigned int GetSCRUserBand ( unsigned int unTunerID, unsigned char & ucUBNo, unsigned short & usUBCenterFreq ) = 0;
    virtual unsigned int FlushSetting ( ) = 0;

    virtual unsigned int ResetPlayer ( ) = 0;

    virtual unsigned int SetAudioPrioritySpec ( AudioComponentPrioritySpec* pAudioComponentPrioritySpec ) = 0;
    virtual unsigned int SetHDServiceSpec ( CheckServiceSpec* pCheckHDServiceSpec ) = 0;
    virtual unsigned int SetUHDServiceSpec ( CheckServiceSpec* pCheckHDServiceSpec ) = 0;
    virtual unsigned int SetChannelNumberSpec ( ChannelNumberSpec* pChannelNumberSpec ) = 0;
    virtual unsigned int SetCheckServiceLockSpec ( CheckServiceLockSpec* pCheckServiceLockSpec ) = 0;
    virtual unsigned int SetCheckPGLockSpec ( PGLockCheckSpec* pPGLockCheckSpec ) = 0;
    virtual unsigned int SetRadioIFrame ( unsigned char* pcDateBuf, unsigned int unLen ) = 0;
	virtual unsigned int CreateIFrameSurface( unsigned int unPixelFormat, unsigned int unWidth, unsigned int unHeight ) = 0;

    //Get Service
    virtual unsigned int GetInitialService ( unsigned int &runGroupIndex, unsigned int &runServiceIndex ) = 0;
    virtual ServiceInterface* GetPlayingService ( ) = 0;
    virtual unsigned int GetPlayingService ( unsigned int &runGroupIndex, unsigned int &runServiceIndex ) = 0;
    virtual unsigned int GetPlayHistoryServiceCount ( ) = 0;
    virtual unsigned int GetPlayHistoryServiceByIndex ( unsigned int & unGroupIndex, unsigned int & unServiceIndex, unsigned int unIndex ) = 0;
    virtual unsigned short GetServiceChannelNumber ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int GetPlayingServiceVideoSource ( unsigned int & unWidth, unsigned int & unHeight, unsigned int & unIsInterlaced ) = 0;
    virtual unsigned int GetPlayingServiceCARating ( ) = 0;
	virtual unsigned int GetPlayingVideoSource ( ADIVIDEOStreamStatus_S & sVideoSource ) = 0;
	virtual unsigned int IsCurServiceScrambledForFTAProject ( ) = 0;

    //PlayLock
    virtual PlayLockInterface* GetPlayLockInterface ( ) = 0;
    virtual unsigned int TriggerPlayLock ( ) = 0;

    virtual TimeShiftDecoderInterface * GetTimeShiftDecoderInterface ( ) = 0;

    virtual unsigned int AddDataBaseContainerPlayerNotify ( DataBaseContainerPlayerNotify* pPlayerNotify ) = 0;
    virtual unsigned int RemoveDataBaseContainerPlayerNotify ( DataBaseContainerPlayerNotify* pPlayerNotify ) = 0;

    virtual unsigned int AddServiceIndexUpdateMonitor ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int RemoveServiceIndexUpdateMonitor ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int AddServiceProgramInfoNotify ( ServiceProgramInfoNotify * pProgramInfoNotify, unsigned short unExpectedCASystemID ) = 0;
    virtual unsigned int RemoveServiceProgramInfoNotify ( ServiceProgramInfoNotify * pProgramInfoNotify, unsigned short unExpectedCASystemID ) = 0;

    //Teletext Rendering
    virtual TeletextRenderingInterface* GetTeletextRenderingInterface ( ) = 0;
    virtual unsigned int AddTeletextDisplayNotify ( DisplayTeletextNotify* pNotify ) = 0;
    virtual unsigned int RemoveTeletextDisplayNotify ( DisplayTeletextNotify* pNotify ) = 0;
    
    //Subtitle Rendering
    virtual void ConfigSubtitleDisplay ( unsigned int unSync, unsigned int unHPositionAdjust ) = 0;

    virtual unsigned int GetCAPGDSCLockStatus ( ServiceInterface* pServiceInterface, unsigned int &runPGService, unsigned int &runUnlock ) = 0;

	virtual AudioComponentPrioritySpec* BuildAudioPrioritySpec ( AudioComponentPrioritySpec * pUserAudioComponentPrioritySpec ) = 0;

    virtual void PlayingServiceDeliveryChanged ( Delivery * pDelivery ) = 0;
};

#endif /* DATABASECONTAINERPLAYERINTERFACE_H_ */
