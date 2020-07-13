/*
 * ServiceComponentsSelectInterface.h
 *
 *  Created on: 2015-5-2
 *      Author: timothy.liao
 */

#ifndef SERVICECOMPONENTSSELECTINTERFACE_H_
#define SERVICECOMPONENTSSELECTINTERFACE_H_
#include "TeletextOutputMode.h"

class ServiceComponentsSelectInterface
{
public:
    ServiceComponentsSelectInterface ( );
    virtual ~ServiceComponentsSelectInterface ( );

public:
    virtual unsigned int SelectAudioTrack ( unsigned int unAudioTrackIndex ) = 0;
    virtual unsigned int SelectSubtitleTrack ( unsigned int unSubtitleTrackIndex ) = 0;
    virtual unsigned int SelectTeletextTrack ( unsigned int unTeletextTrackIndex ) = 0;
    virtual unsigned int SelectTeletextTrack ( unsigned int unTeletextTrackIndex, TeletextOutputMode eTeletextOutputMode ) = 0;
    virtual unsigned int SelectVideoTrack ( unsigned int unVideoTrackIndex ) = 0;
    virtual unsigned int AutoSelectAudioTrack ( ) = 0;
    virtual unsigned int AutoSelectSubtitleTrack ( ) = 0;
};

#endif /* SERVICECOMPONENTSSELECTINTERFACE_H_ */
