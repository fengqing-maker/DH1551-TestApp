/*
 * TimeShiftDecoderInterface.h
 *
 *  Created on: 2015-8-3
 *      Author: linc
 */

#ifndef TIMESHIFTDECODERINTERFACE_H_
#define TIMESHIFTDECODERINTERFACE_H_

#include "adi_player.h"
#include "PlayStatus.h"
#include "ADITime.h"
#include "ActPVRFileUpdateNotify.h"
#include "PlayLockType.h"
#include "PlayError.h"
#include "AudioFormat.h"
#include "AudioComponentPrioritySpec.h"

class TimeShiftDecoderInterface
{

public:

    TimeShiftDecoderInterface ( );
    virtual ~TimeShiftDecoderInterface ( );

public:
    virtual unsigned int Stop ( ) = 0;
	virtual unsigned int Stop ( unsigned int unReplay, unsigned int unSync ) = 0;
    virtual PlayError Pause ( ) = 0;
    virtual  unsigned int Resume ( ) = 0;
    virtual PlayStatus PlayOrPause ( ) = 0;
    virtual unsigned int SetPlayerSpeed ( ADIPlayerSpeed_E eSpeed ) = 0;
    virtual unsigned int GetPlayerSpeed ( ADIPlayerSpeed_E & eSpeed ) = 0;
    virtual unsigned int SetPosition ( const int nPosInSec, const ADIPlayPosition_E ePlayPosFlag ) = 0;
    virtual unsigned int GetTimeShiftStartTime ( ADITime &startTime ) = 0;
    virtual unsigned int GetTimeShiftEndTime ( ADITime &endTime ) = 0;
    virtual unsigned int GetCurPosition ( int & nPosInSec ) = 0;
    virtual unsigned int GetStartPosition ( int & nPosInSec ) = 0;
    virtual unsigned int GetDuration ( int & nDuration ) = 0;
    virtual unsigned int AddActPVRFileUpdateNotify ( ActPVRFileUpdateNotify * pNotify ) = 0;
    virtual unsigned int RemoveActPVRFileUpdateNotify ( ActPVRFileUpdateNotify * pNotify ) = 0;

    virtual unsigned int IsTimeShiftWorking ( ) = 0;
	virtual unsigned int IsTimeShiftRecordWorking ( ) = 0;
    virtual unsigned int CheckTimeShiftWorking ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int SetPVRLockInfo ( PlayLockType enLockType, unsigned char ucLockLevel, int nDuration ) = 0;
    virtual unsigned int GetPVRLockInfo ( PlayLockType & enLockType, unsigned char & ucLockLevel ) = 0;
    virtual unsigned int CheckPVRLock ( ) = 0;

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
    virtual unsigned int SelectTeltextTrack ( unsigned int nIndex ) = 0;

    virtual PlayStatus GetTimeShiftStatus ( ) = 0;

    virtual unsigned int SwitchAuidoComponent ( AudioComponentPrioritySpec* pAudioComponentPrioritySpec ) = 0;
    virtual unsigned int GetTimeShiftFileSize ( unsigned long long & ullFileSize ) = 0;
};

#endif /* TIMESHIFTDECODERINTERFACE_H_ */
