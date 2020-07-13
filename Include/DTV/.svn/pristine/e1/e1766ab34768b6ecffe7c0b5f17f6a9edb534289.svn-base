/*
 * UpdateLiveServiceInfoInterface.h
 *
 *  Created on: 2015-5-4
 *      Author: timothy.liao
 */

#ifndef UPDATELIVESERVICEINFOINTERFACE_H_
#define UPDATELIVESERVICEINFOINTERFACE_H_
#include "ServiceInterface.h"
#include "AudioFormat.h"
#include "VideoFormat.h"
#include "AudioChannel.h"
#include "TeletextType.h"

class UpdateLiveServiceInfoInterface
{
public:
    UpdateLiveServiceInfoInterface ( );
    virtual ~UpdateLiveServiceInfoInterface ( );

public:

    virtual unsigned int GetAudioTrackNumber ( ) = 0;
    virtual unsigned int GetAudioTrackLanguageCode ( unsigned int unTrackIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual AudioFormat GetAudioFromat ( unsigned int unTrackIndex ) = 0;
    virtual AudioChannel GetAudioChannel ( unsigned int unTrackIndex ) = 0;

    virtual unsigned int GetADTrackNumber ( ) = 0;
    virtual unsigned int GetADTrackLanguageCode ( unsigned int unTrackIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual AudioFormat GetADFromat ( unsigned int unTrackIndex ) = 0;
    virtual AudioChannel GetADChannel ( unsigned int unTrackIndex ) = 0;

    virtual unsigned int GetSubtitleTrackNumber ( ) = 0;
    virtual unsigned int GetSubtitleTrackLanguageCode ( unsigned int unTrackIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;

    virtual unsigned int GetTeletextTrackNumber ( ) = 0;
    virtual unsigned int GetTeletextTrackLanguageCode ( unsigned int unTrackIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual TeletextType GetTeletextType ( unsigned int unTrackIndex ) = 0;

    virtual unsigned short GetPCRPid ( ) = 0;
    virtual unsigned short GetCurrentVideoComponentPid ( ) = 0;
    virtual unsigned short GetCurrentAudioComponentPid ( ) = 0;
    virtual unsigned short GetCurrentSubtitleComponentPid ( ) = 0;
    virtual unsigned short GetCurrentTeletextComponentPid ( ) = 0;
    virtual VideoFormat GetCurrentVideoFormat ( ) = 0;
    virtual AudioFormat GetCurrentAudioFormat ( ) = 0;
    virtual AudioChannel GetCurrentAudioChannel ( ) = 0;

    virtual unsigned int GetCurrentAudioComponentLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentSubtitleComponentLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentTeletextComponentLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetCurrentTeletextComponentIndex ( unsigned int & unTeletextIndex ) = 0;
    virtual unsigned int GetCurrentAudioComponentIndex ( unsigned int & unAudioIndex ) = 0;
    virtual unsigned int GetCurrentSubtitleComponentIndex ( unsigned int & unSubtitleIndex ) = 0;

    virtual unsigned int GetServiceFreeCAMode ( ) = 0;

    virtual unsigned short GetAudioComponentPidByIndex ( unsigned int unIndex ) = 0;

    virtual unsigned short GetPMTPid ( unsigned short usServiceID ) = 0;
};

#endif /* UPDATELIVESERVICEINFO_H_ */
