/*
 * FilePlayerInterface.h
 *
 *  Created on: 2015-6-23
 *      Author: cl
 */

#ifndef FILEPLAYERINTERFACE_H_
#define FILEPLAYERINTERFACE_H_

#include "adi_player.h"
#include "PlayError.h"
#include "PlayStatus.h"
#include "EventInfoInterface.h"
#include "FreeCAMode.h"
#include "ServiceType.h"
#include "ActPVRFileUpdateNotify.h"
#include "PlayLockType.h"
#include "AudioFormat.h"
#include "DisplayTeletextNotify.h"
#include "TeletextRenderingInterface.h"
#include "AudioComponentPrioritySpec.h"

class FilePlayerInterface
{
public:
    FilePlayerInterface ( );
    virtual ~FilePlayerInterface ( );

    virtual PlayError Start ( unsigned int unFileIndex ) = 0;
    virtual PlayError Stop ( ) = 0;
	virtual PlayError Stop(unsigned int unReplay) = 0;
	virtual PlayError Stop(unsigned int unReplay, unsigned int unSync) = 0;
    virtual PlayError Pause ( ) = 0;
    virtual PlayError Resume ( ) = 0;
    virtual PlayStatus PlayOrPause ( ) = 0;
    virtual unsigned int SetPlayerSpeed ( ADIPlayerSpeed_E eSpeed ) = 0;
    virtual unsigned int GetPlayerSpeed ( ADIPlayerSpeed_E & eSpeed ) = 0;
    virtual unsigned int SetPosition ( const int nPosInSec, const ADIPlayPosition_E ePlayPosFlag ) = 0;
    virtual unsigned int GetCurPosition ( int & nPosInSec ) = 0;
    virtual unsigned int GetDuration ( int & nDuration ) = 0;

    virtual unsigned int IsPlayBackWorking ( ) = 0;
    virtual unsigned int IsPlayBackWorking ( unsigned int unFileIndex ) = 0;
	virtual unsigned int IsPlayBackWorking ( char * pPath, int nLen ) = 0;
    virtual unsigned int CheckPlayBackWorking ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int GetPresentEventInfo ( char acEventName [ ], unsigned int unEventNameLen, char acEventText [ ], unsigned int unEventTextLen, char acLanguageCode [ ], unsigned int unLanguageCodeLen ) = 0;

    virtual unsigned int GetAudioTrackCount ( ) = 0;
    virtual unsigned int GetAudioTrackLanguageCode ( unsigned int unIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurAudioTrackLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurAudioTrackLanguageIndex ( unsigned int & unIndex ) = 0;

    virtual unsigned int SelectAudioTrackLanguageCode ( unsigned int unIndex ) = 0;
    virtual AudioFormat GetCurrentAudioFormat ( ) = 0;
    virtual AudioFormat GetAudioFormat ( unsigned int unIndex ) = 0;

    virtual unsigned int GetSubtitleTrackCount ( ) = 0;
    virtual unsigned int GetSubtitleTrackLanguageCode ( unsigned int unIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentSubtitleTrackLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentSubtitleTrackLanguageIndex ( unsigned int & unIndex ) = 0;
    virtual unsigned int SelectSubtitleTrackLanguageCode ( unsigned int unIndex ) = 0;
	virtual void EnablePVRSubtitle(unsigned int unEnable) = 0;

    virtual unsigned int GetTeltextTrackCount ( ) = 0;
    virtual unsigned int GetTeletextType ( unsigned int unIndex ) = 0;
    virtual unsigned int GetTeletextLanguageCode ( unsigned int unIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentTeletextTrackLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentTeletextTrackIndex ( ) = 0;
    virtual unsigned int SelectTeltextTrack ( unsigned int unIndex ) = 0;

    virtual unsigned int GetServiceInfo ( unsigned short * uspServiceID, unsigned short * uspLCN, FreeCAMode * enpFreeCAMode,
        ServiceType * enpServiceType, char acServiceName [ ], unsigned int unServiceNameLen ) = 0;
    virtual unsigned int GetPVRLockInfo ( PlayLockType & enLockType, unsigned char & ucLockLevel, unsigned int unFileIndex ) = 0;
    virtual unsigned int CheckPVRLock ( ) = 0;

    virtual unsigned int AddActPVRFileUpdateNotify ( ActPVRFileUpdateNotify * pNotify ) = 0;
    virtual unsigned int RemoveActPVRFileUpdateNotify ( ActPVRFileUpdateNotify * pNotify ) = 0;

    virtual PlayStatus GetPlayBackStatus ( ) = 0;

    virtual unsigned int GetAudioChannel ( void ) = 0;
    virtual unsigned int SetAudioChannel ( unsigned int unAudioChannel ) = 0;

    virtual TeletextRenderingInterface *GetTextRenderingInterface ( ) = 0;

    virtual unsigned int SetTeletextDisplayNotify ( DisplayTeletextNotify * pNotify ) = 0;

    virtual unsigned int SetIFrameDecoder ( unsigned int unIndex, unsigned char * pcBuf, unsigned int unLen ) = 0;

	virtual unsigned int SwitchAuidoComponent ( AudioComponentPrioritySpec* pAudioComponentPrioritySpec ) = 0;

    virtual void CheckRecordingExpire ( ) = 0;

	virtual void NotifyUpdateRECInfo ( ) = 0;
};

#endif /* FILEPLAYERINTERFACE_H_ */
