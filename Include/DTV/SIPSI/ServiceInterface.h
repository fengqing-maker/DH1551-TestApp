/*
 * ServiceInterface.h
 *
 *  Created on: 2015-4-9
 *      Author: timothy.liao
 */

#ifndef SERVICEINTERFACE_H_
#define SERVICEINTERFACE_H_

#include "FreeCAMode.h"
#include "ServiceType.h"
#include "EventInfoInterface.h"
#include "ADITime.h"

class ServiceInterface
{

public:

    ServiceInterface ( );
    virtual ~ServiceInterface ( );

public:

    virtual unsigned short GetPHYNetworkID ( ) = 0;
    virtual unsigned short GetOriginalNetworkID ( ) = 0;
    virtual unsigned short GetTSID ( ) = 0;
    virtual unsigned short GetServiceID ( ) = 0;
    virtual unsigned short GetLCN ( ) = 0;
    virtual unsigned char GetVisible ( ) = 0;
    virtual FreeCAMode GetFreeCAMode ( ) = 0;
    virtual ServiceType GetServiceType ( ) = 0;
    virtual unsigned int SetServiceType ( ServiceType ) = 0;
    virtual unsigned int GetServiceName ( char aucName [ ], unsigned int unLength ) = 0;
	virtual unsigned int SetServiceName(char aucName[], unsigned int unLength) = 0;

	virtual EventInfoInterface* GetPresentEvent() = 0;
	virtual unsigned int FreePresentEvent(EventInfoInterface * pEvent) = 0;
	virtual EventInfoInterface* GetFollowingEvent() = 0;
	virtual unsigned int FreeFollowingEvent(EventInfoInterface * pEvent) = 0;

    virtual void* CreateEventIterator ( ADITime startTime, unsigned int unDurationInSecond, TimeZone enTimeZone ) = 0;
    virtual unsigned int DeleteEventIterator ( void* hIterator ) = 0;
    virtual unsigned int GetEventCount ( void* hIterator ) = 0;
    virtual EventInfoInterface* GetEvent ( void* hIterator, unsigned int unIndex ) = 0;
    virtual EventInfoInterface* GetEventByEventID ( unsigned short usEventID ) = 0;

    virtual unsigned short GetPMTPid ( ) = 0;

    virtual unsigned int IsRadioService ( ) = 0;
    virtual unsigned int IsTVService ( ) = 0;
    virtual unsigned int IsNVODService ( ) = 0;

    virtual unsigned short GetPCRPid ( ) = 0;
	
	virtual unsigned int GetMultiAudioTrackAttribute ( ) = 0;
};

#endif /* SERVICEINTERFACE_H_ */
