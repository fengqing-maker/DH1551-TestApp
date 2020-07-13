/*
 * ServicesDeletedNotify.h
 *
 *  Created on: 2015-7-10
 *      Author: HXC
 */

#ifndef SERVICESDELETEDNOTIFY_H_
#define SERVICESDELETEDNOTIFY_H_

#include "NetworkInterface.h"
#include "TransponderInterface.h"
#include "ServiceInterface.h"

class ServicesDeletedNotify
{

public:

	ServicesDeletedNotify( );
	virtual ~ServicesDeletedNotify( );

public:

    virtual void AllServicesDataWillBeDeletedNotify ( ) = 0;
    virtual void NetworkWillBeDeletedNotify ( NetworkInterface * pNetworkInterface ) = 0;
    virtual void TransponderWillBeDeletedNotify ( TransponderInterface * pTransponderInterface ) = 0;
    virtual void ServiceWillBeDeletedNotify ( ServiceInterface * pServiceInterface ) = 0;
    virtual void ModifyTransponder ( TransponderInterface * pTransponderInterface ) = 0;

};

#endif /* SERVICESDELETEDNOTIFY_H_ */
