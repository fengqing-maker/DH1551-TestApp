/*
 * ServicesGroupInterface.h
 *
 *  Created on: 2015-5-6
 *      Author: HXC
 */

#ifndef SERVICESGROUPINTERFACE_H_
#define SERVICESGROUPINTERFACE_H_

#include "ServiceInterface.h"

class ServicesGroupInterface
{

public:

	ServicesGroupInterface( );
	virtual ~ServicesGroupInterface( );

public:

    virtual unsigned int GetName ( char acName [ ], unsigned int unNameLen ) = 0;
	virtual unsigned int SetName ( char acName [ ], unsigned int unNameLen ) = 0;

    virtual unsigned int GetCount ( ) = 0;
    virtual ServiceInterface * GetServiceInterface ( unsigned int unIndex ) = 0;

    virtual unsigned int GetServiceLCN ( unsigned int unServiceIndex ) = 0;

};

#endif /* SERVICESGROUPINTERFACE_H_ */
