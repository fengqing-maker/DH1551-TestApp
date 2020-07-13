/*
 * NVODReferenceServiceContainerInterface.h
 *
 *  Created on: 2015-11-27
 *      Author: HXC
 */

#ifndef NVODREFERENCESERVICECONTAINERINTERFACE_H_
#define NVODREFERENCESERVICECONTAINERINTERFACE_H_
#include "ADITime.h"
#include "RunningStatus.h"

class NVODReferenceServiceContainerInterface
{

public:

    NVODReferenceServiceContainerInterface ( );
    virtual ~NVODReferenceServiceContainerInterface ( );

public:

    virtual unsigned int GetNVODReferenceServiceCount ( ) = 0;
    
    virtual unsigned short GetReferenceServiceOriNetworkID ( unsigned int unReferenceServiceIndex ) = 0;
    virtual unsigned short GetReferenceServiceTSID ( unsigned int unReferenceServiceIndex ) = 0;
    virtual unsigned short GetReferenceServiceID ( unsigned int unReferenceServiceIndex ) = 0;
    virtual unsigned int GetReferenceServiceName ( unsigned int unReferenceServiceIndex, char acServiceName [ ], unsigned int unNameLength ) = 0;

    virtual unsigned int GetTimeShiftServiceCount ( unsigned int unReferenceServiceIndex ) = 0;

    virtual unsigned short GetTimeShiftServiceOriNetworkID ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftServiceIndex ) = 0;
    virtual unsigned short GetTimeShiftServiceTSID ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftServiceIndex ) = 0;
    virtual unsigned short GetTimeShiftServiceID ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftServiceIndex ) = 0;

    virtual unsigned int GetPresentReferenceShortEventName ( unsigned int unReferenceServiceIndex, char acName [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetPresentReferenceShortEventText ( unsigned int unReferenceServiceIndex, char acText [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetPresentReferenceShortEventLanguageCode ( unsigned int unReferenceServiceIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetPresentReferenceEventParentRating ( unsigned int unReferenceServiceIndex, char acCountryCode [ ], unsigned int unLength, unsigned char & ucRating ) = 0;
    virtual unsigned int GetPresentReferenceEventDuration ( unsigned int unReferenceServiceIndex ) = 0;
    virtual unsigned int GetPresentReferenceTimeShiftEventCount ( unsigned int unReferenceServiceIndex, ADITime CurrentTime ) = 0;
    virtual RunningStatus GetPresentReferenceTimeShiftEventRunningStatus ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftEventIndex ) = 0;
    virtual void GetPresentReferenceTimeShiftEventStartTime ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftEventIndex, ADITime & inputADITime ) = 0;

    virtual unsigned int GetFollowingReferenceShortEventName ( unsigned int unReferenceServiceIndex, char acName [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetFollowingReferenceShortEventText ( unsigned int unReferenceServiceIndex, char acText [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetFollowingReferenceShortEventLanguageCode ( unsigned int unReferenceServiceIndex, char acLanguageCode [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetFollowingReferenceEventParentRating ( unsigned int unReferenceServiceIndex, char acCountryCode [ ], unsigned int unLength, unsigned char & ucRating ) = 0;
    virtual unsigned int GetFollowingReferenceEventDuration ( unsigned int unReferenceServiceIndex ) = 0;
    virtual unsigned int GetFollowingReferenceTimeShiftEventCount ( unsigned int unReferenceServiceIndex ) = 0;
    virtual RunningStatus GetFollowingReferenceTimeShiftEventRunningStatus ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftEventIndex ) = 0;
    virtual void GetFollowingReferenceTimeShiftEventStartTime ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftEventIndex, ADITime & inputADITime ) = 0;

};

#endif /* NVODREFERENCESERVICECONTAINER_H_ */
