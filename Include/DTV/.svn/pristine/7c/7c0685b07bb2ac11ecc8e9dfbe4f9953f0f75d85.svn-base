/*
 * NetworkTimeInterface.h
 *
 *  Created on: 2015-6-16
 *      Author: timothy.liao
 */
#include "ADITime.h"

#ifndef NETWORKTIMEINTERFACE_H_
#define NETWORKTIMEINTERFACE_H_
#include "TDTUpdatedNotify.h"
#include "CheckNetworkValidationNotify.h"

class NetworkTimeInterface
{
public:

    NetworkTimeInterface ( );
    virtual ~NetworkTimeInterface ( );

public:

    virtual unsigned int ConfigManualTimeZone ( unsigned int unManualTimeZoneIndex ) = 0;
    virtual unsigned int ConfigCountryCode ( char acCountryCode [ ], unsigned int unLength, unsigned char ucRegionId ) = 0;
    virtual unsigned int ConfigTimeZoneMode ( unsigned int unAuto ) = 0;

    virtual unsigned int GetLocalTimeOffset ( char acCountryCode [ ], unsigned int unLength, unsigned char unRegionId, int & nTimeOffsetInMinutes ) = 0;
    virtual unsigned int GetLocalTimeZone ( char acCountryCode [ ], unsigned int unLength, unsigned char unRegionId, TimeZone &eTimeZOne ) = 0;
    virtual int GetLocalTimOffset ( ) = 0;
    virtual TimeZone GetLocalTimeZone ( ) = 0;
    
    virtual unsigned int GetNetworkTime ( ADITime &rTime ) = 0;
    virtual unsigned int GetNetworkTimeWithOffset ( ADITime &rTime ) = 0;

    virtual unsigned int EnableManualSetTime ( ADITime &rTime, unsigned int unTimeZone ) = 0; 
    virtual unsigned int DisableManualSetTime ( ) = 0;

    virtual unsigned int AddTDTUpdatedNotify ( TDTUpdatedNotify * pTDTUpdatedNotify ) = 0;
    virtual unsigned int RemoveTDTUpdatedNotify ( TDTUpdatedNotify * pTDTUpdatedNotify ) = 0;

    virtual unsigned int AddCheckNetworkValidationNotify ( CheckNetworkValidationNotify * pCheckNetworkValidationNotify ) = 0;
    virtual unsigned int RemoveCheckNetworkValidationNotify ( CheckNetworkValidationNotify * pCheckNetworkValidationNotify ) = 0;

};

#endif /* NETWORKTIMEINTERFACE_H_ */
