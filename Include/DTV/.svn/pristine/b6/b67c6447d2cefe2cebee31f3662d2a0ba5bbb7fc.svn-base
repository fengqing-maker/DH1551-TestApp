/*
 * EventInfoInterface.h
 *
 *  Created on: 2015-4-27
 *      Author: timothy.liao
 */

#ifndef EVENTINFOINTERFACE_H_
#define EVENTINFOINTERFACE_H_

#include "ADITime.h"
#include "RunningStatus.h"

class EventInfoInterface
{

public:
    EventInfoInterface ( );
    virtual ~EventInfoInterface ( );

public:
    virtual unsigned short GetOriginalNetworkID ( ) = 0;
    virtual unsigned short GetTSID ( ) = 0;
    virtual unsigned short GetServiceID ( ) = 0;

    virtual unsigned short GetEventID ( ) = 0;
    virtual unsigned int GetStartTime ( ADITime & intputTime ) = 0;
    virtual unsigned int GetDuration ( ) = 0;
	virtual RunningStatus GetRunningStatus() = 0;

    virtual unsigned int GetShortEventName ( char acName [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetShortEventText ( char acText [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetShortEventLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
	virtual unsigned int GetShortEventLanguageCode ( char acLanguageCode [ ], unsigned int unLength, unsigned int unIndex ) = 0;

    virtual unsigned int GetParentRating ( char acCountryCode [ ], unsigned int unLength, unsigned char &ucRating ) = 0;

    virtual unsigned int GetExtendedEventLanguageCode ( char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetExtendedEventTextLength ( ) = 0;
    virtual unsigned int GetExtendedEventText ( char acText [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetExtendedEventItemCount ( ) = 0;
    virtual unsigned int GetExtentedEventItem ( unsigned int unItemIndex, char acDescription [ ], unsigned int unDescriptionLength, char acText [ ], unsigned int unTextLength ) = 0;

    virtual unsigned int GetEventContentCount ( ) = 0;
    virtual unsigned int GetEventContent ( unsigned int unIndex, unsigned char &ucLevel1, unsigned char &ucLevel2, unsigned char &ucUserByte ) = 0;

    //-1 No Conflict; 0 equal to the target event; 1 Time Conflict
    virtual int CheckEventTimeConflict ( EventInfoInterface* pEvent ) = 0;
    virtual unsigned int IsEventExpired ( ADITime & inputTime ) = 0;
};

#endif /* EVENTINFOINTERFACE_H_ */
