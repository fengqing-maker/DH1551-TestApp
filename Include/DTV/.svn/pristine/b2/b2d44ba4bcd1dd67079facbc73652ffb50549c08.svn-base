/*
 * ServicesDataBasePlayerServiceUpdateNotify.h
 *
 *  Created on: 2016-2-1
 *      Author: Timothy.Liao
 */

#ifndef SERVICESDATABASEPLAYERSERVICEUPDATENOTIFY_H_
#define SERVICESDATABASEPLAYERSERVICEUPDATENOTIFY_H_
#include "Delivery.h"

class ServicesDataBasePlayerServiceUpdateNotify
{

public:

    ServicesDataBasePlayerServiceUpdateNotify ( );
    virtual ~ServicesDataBasePlayerServiceUpdateNotify ( );

public:

    virtual void ServiceDeletedNotify ( unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID ) = 0;
    virtual void DeliveryChangedNotify ( unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID, Delivery* pDelivery ) = 0;

};

#endif /* SERVICESDATABASEPLAYERSERVICEUPDATENOTIFY_H_ */
